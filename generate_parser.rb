#!/usr/bin/env ruby

grammar = Hash.new(nil)
gram = []
$sp = "   "
$sp2 = $sp*2

def term?(tok)
  return (tok =~ /^'.+'$/) != nil
end

def rule?(tok)
  return !term?(tok)
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
   tok = prod.collect{ |p| sym(p) if rule?(p) }.compact.first 
   return "t_#{rule.gsub(/__/,'')}_#{tok}"
end

def eater(tok)
  str = ""
  if term?(tok)
    tk = sym(tok)
    if tk.length == 1
      str = "eat('#{tk}')" 
    else 
      str = "eat(TOK_#{tk})"
    end
  else
    str = "Tree#{tok.capitalize} = p_#{tok}()"
  end
  return str
end

def caser(rule, prod)
  toks = prod.collect { |p| eater(p) }
  args = prod.collect { |p| p if rule?(p) }.compact
  cas = "TOK_#{sym(prod.first)}"
  cas = "#{prod.first}" if sym(prod.first).length == 1

  return """      case #{cas}: {
         #{ toks*";\n#{$sp*3}" };
         #{rule} = #{tp_name(rule,prod)}(#{args*', '});
         break;
      }"""
end

def functer(rule, prods)
  err_parse = prods.last.empty? ? "" : "#{$sp*3}error_parse(\"#{rule}\");\n"
  default = "#{$sp2}default:\n#{err_parse}#{$sp*3}break;"
  if prods.length > 1
    body = <<-BODY
   
   // cases
   switch (code) {
#{ prods.collect {|p| caser(rule, p) if not p.empty? }*"\n" }
#{default}
   }   
   BODY
  elsif prods.length == 1
    toks = prods.first.collect { |p| eater(p) }
    args = prods.first.collect { |p| p if rule?(p) }.compact
    
    body = <<-BODY
   // body
   #{ toks*";\n#{$sp}" };
   #{rule} = #{tp_name(rule,prods.first)}(#{args*', '});
BODY
  end
  
  return <<-FUNC
/** 
   #{rule.capitalize}
   Grammar:
      #{rule} : #{prods.collect { |p| p*' '}*" | "} #{'e'if prods.last.empty?}
*/
static Tree#{rule.capitalize} p_#{rule}(void) {
   Tree#{rule.capitalize} = 0; // set null by default
   TokenCode code = curr()->code;
#{body}
   return #{rule};
}



   FUNC
end


File.open("grammar-right.txt", "r") do |fl|
  $/="\n\n"
  coll = fl.collect {|g| g.split(':') }

  coll.each do |prod| 
    # puts "LINE: '#{prod.inspect}'"
    rule = prod.shift.strip
    prods = prod.last ? prod.last.split(/\s+\|\s+/).collect{ |p| p.split } : []
    # puts "rule: #{rule.inspect}"
    # puts "prods:\t #{prods.inspect}"
    # puts
    if not rule.empty?
      grammar[rule] = prods 
      gram << [rule, prods]
    end
  end

end

# puts "G1", grammar["factor"].inspect
puts "Grammar: "
gram.each { |g| puts functer(g.first, g.last) }



