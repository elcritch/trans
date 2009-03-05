#!/usr/bin/env ruby

$grammar = Hash.new(nil)
gram = []
$sp = "   "
$sp2 = $sp*2

def literal?(tok)
  return (tok =~ /^'.+'$/) != nil
end

def rule?(tok)
  return $grammar.has_key? tok
end

def sym(tok)
  regex = Regexp.new(/^'(.*)'$/)
  match = regex.match(tok)
  symtab = {
    '<='=>'LE',
    '!='=>'NE',
    '=='=>'EQ',
    '>='=>'GE',
    '&&'=>'AND',
    '||'=>'OR',
  }
  return symtab[match[1]] if match and (symtab.keys.include? match[1])
  return match ? match[1] : tok
end

def tp_name(rule, prod)
  tok = prod.map{ |p| sym(p) if sym(p).length>1 }.compact.first 
  return "t_#{rule.gsub(/__/,'').downcase}_#{tok}"
end

def lvar(tok,i)
  return "l#{i}#{tok}"
end

def reduce_tok(tok)
  return tok if not $grammar.has_key? tok
  return reduce_tok($grammar[tok][0].first)
end 

def eater(tok,i)
  str = ""
  if literal?(tok)
    tk = sym(tok)
    if tk.length == 1
      str = "eat('#{tk}')" 
    else 
      str = "eat(TOK_#{tk})"
    end
  else
    str = "Tree#{tok.capitalize} #{lvar(tok,i)} = p_#{tok}()"
  end
  return str
end

def caser(rule, prod, arg0=nil)
  toks = prod.each_with_index.map { |p,i| eater(p,i) }
  args = prod.each_with_index.map { |p,i| lvar(p,i) if rule?(p) }.compact
  args.unshift(arg0) if arg0
  
  cas = "TOK_#{ sym(prod.first) }"
  cas = "#{prod.first}" if sym(prod.first).length == 1

  if rule? prod.first
    nonterm = "//===== REDUCED #{cas}" 
    rtok = sym(reduce_tok(sym(prod.first)))
    cas = "TOK_#{ rtok }"
    cas = "'#{rtok}'" if rtok.length == 1
  end


  return """      case #{cas}: {  #{nonterm}
         #{ toks*";\n#{$sp*3}" };
         #{rule} = #{tp_name(rule,prod)}(code, #{args*', '});
         break;
      }"""
end

def functer(rule, prods)
  err_parse = prods.last.empty? ? "" : "#{$sp*3}error_parse(\"#{rule}\");\n"
  default = "#{$sp2}default:\n#{err_parse}#{$sp*3}break;"
  
  ############################################
  # Special eps production for one case
  if prods.length==2 and prods.last.empty? and rule? prods[0].first
    toks = prods.first.each_with_index.map { |p,i| eater(p,i) }
    args = prods[0].each_with_index.map{ |p,i| lvar(p,i) if ! literal?(p) }.compact
    body = <<-BODY
   // body
   #{ toks[0] }
   
   // check if we have next production
   if ( #{lvar(prods[0].first,0)} == 0 ) 
      return #{rule};

   #{ toks[1..-1]*";\n#{$sp}" };
   #{rule} = #{tp_name(rule,prods.first)}(#{args*', '});
   BODY

  ############################################
  elsif prods.length > 1 
    cmn = prods.map{|p| rule?(p[0]) and (p.first==prods[0][0]) }
    cmn = !(cmn.include? false)
    if cmn
       arg0 = lvar(prods[0].first,0)
       cmnf = "#{eater(prods[0].first, 0)}; // common"
       prods = prods.map{ |p|  p[1..-1] } if cmn
       prods[-1] = [] if not prods.last
    end
    
    body = <<-BODY   
   // cases
   #{cmnf}
   switch (code) {
#{ prods.map {|p| caser(rule, p) if not p.empty? }*"\n" }
#{default}
   }   
   BODY

  ############################################
  else
    toks = prods.first.each_with_index.map { |p,i| eater(p,i) }
    args = prods[0].each_with_index.map{ |p,i| lvar(p,i) if ! literal?(p) }.compact
    body = <<-BODY
   // body
   #{ toks*";\n#{$sp}" };
   #{rule} = #{tp_name(rule,prods.first)}(#{args*', '});
   BODY
  end
  
  return <<-FUNC
/**
==================== #{(rule.capitalize+' ').ljust(50,'=')}
   Grammar:
      #{rule} : #{prods.map { |p| p*' '}*" | "} #{'e'if prods.last.empty?}
*/
static Tree#{rule.capitalize} p_#{rule}(void) {
   Tree#{rule.capitalize} #{rule} = 0; // set null by default
   TokenCode code = curr()->code;
#{body}
   
   return #{rule};
}


   FUNC
end


File.open("grammar-right.txt", "r") do |fl|
  $/="\n\n"
  coll = fl.map {|g| g.split(':') }

  coll.each do |prod| 
    # puts "LINE: '#{prod.inspect}'"
    rule = prod.shift.strip
    prods = prod.last ? prod.last.split(/\s+\|/).map{ |p| p.split } : []
    # puts "rule: #{rule.inspect}"
    # puts "prods:\t #{prods.inspect}"
    # puts
    if not rule.empty?
      $grammar[rule] = prods 
      gram << [rule, prods]
    end
  end

end

# puts "G1", grammar["factor"].inspect
puts "Grammar: "
gram.each { |g| puts functer(g.first, g.last) }



