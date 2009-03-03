grammar = Hash.new(nil)
gram = []
$sp = "   "
$sp2 = $sp*2

def eater(tok)
  str = ""
  regex = Regexp.new(/'(.+)'/)
  match = regex.match(tok)
  if match
    tk = match[0]
    if tk.length == 1
      str = "eat('#{tk}')" 
    else 
      str = "eat(TOK_#{tk})"
    end
    
  else
    str = "Tree#{tok.capitalize} = p_#{tok}"
  end
  return str
end

def caser(rule, prod)
  toks = prod.collect { |p| eater(p) }
  args = prod.collect { |p| p if p =~ /^\w+/ }
  return <<-CASE
   case TOK_#{prod.first}: {
      #{ toks*";\n#{$sp2}" }
      #{rule} = t_#{rule}_#{prod.first}(#{ args*', ' })
      break;
    }
  CASE
end

def functer(rule, prods)
  if prods.last.empty? 
    default = "default:\n#{$sp2}break;"
  else
    default = "default:\n#{$sp2}error_parse(\"#{rule}\");\n#{$sp2}break;"
  end
  return <<-FUNC
/** #{rule} */
static Tree#{rule.capitalize} p_#{rule}(void) {
  Tree#{rule.capitalize} = 0; // set null by default
  TokenCode code = curr()->code;
  switch (code) {
#{ prods.collect {|p| caser(rule, p) }*"\n" }
    #{default};
    break;
  }
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
    grammar[rule] = prods if not rule.empty?
    gram << [rule, prods]
  end

end

# puts "G1", grammar["factor"].inspect
# puts "Grammar: "

gram.each { |g| puts functer(g.first, g.last) }



