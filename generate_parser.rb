grammar = Hash.new(nil)
gram = []
$sp = "   "
$sp2 = $sp*2

def term?(tok)
  return tok =~ /^'.+'$/
end

def rule?(tok)
  return !sym?(tok)
end

def sym(tok)
  regex = Regexp.new(/^'(.*)'$/)
  match = regex.match(tok)
  return match[1]
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
  args = prod.collect { |p| p if p =~ /^\w+/ }
  return <<-CASE
   case TOK_#{prod.first}: {
      #{ toks*";\n#{$sp2}" };
      #{rule} = t_#{rule}_#{prod.first}(#{ args*', ' })
      break;
    }
  CASE
end

def functer(rule, prods)
  err_parse = prods.last.empty? ? "" : "#{$sp*3}error_parse(\"#{rule}\");\n"
  default = "#{$sp}default:\n#{err_parse}#{$sp2}break;"
  if prods.length > 1
    body = <<-BODY
  switch (code) {
#{ prods.collect {|p| caser(rule, p) if not p.empty? }*"\n" }
#{default}
  }  
  BODY
  else
    body = <<-BODY
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
  return stmt;
}



  FUNC
end


File.open("grammar-right.txt", "r") do |fl|
  $/="\n\n"
  coll = fl.collect {|g| g.split(':') }

  coll.each do |prod| 
    # puts "LINE: '#{prod.inspect}'"
    rule = prod.shift.strip
    prods = prod.last ? prod.last.split('|').collect{ |p| p.split } : []
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



