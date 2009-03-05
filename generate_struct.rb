#!/usr/bin/env ruby

def tree(arg)
#   puts "arg: #{arg}"
  return "TokenCode code" if arg.match /code/
  return "Tree#{arg.capitalize} #{arg}"
end

def assgn(name, arg, len)
  return "" if arg.match /code/
  if len == 1
    return "v->#{arg} = #{arg};"
  else
    return "v->u.u_#{name}.#{arg} = #{arg};"
  end
end

def functer(sz, names, args, len)
  tname = "t_#{names[0]}_#{names[1]}"
  tok = "TOK_#{names[1]}"
  tok = "code" if args[0] and args[0].match(/code/)
  puts """
// #{names.first.capitalize} #{args.inspect}
extern Tree#{names[0].capitalize} #{tname}(#{ args.map{|a| tree(a) }*", " }) {
  ALLOC(Tree#{names[0].capitalize});
  #{ sz>1 ? "v->code = #{ tok };\n" : "" }  #{ args.map{ |a| assgn(names[1],a, sz) }*"\n  " }
  return v;
}
"""
end

def struct(name, args)
  return "/* omitting empty rule: #{name} */" if args.nil? or args.empty?
  return """struct {
      #{args.map{|a| tree(a) }*";\n      " };
    } u_#{name};"""
end

def union(rule, args)
  if args.length > 1
    puts """
// Structure: #{rule} #{args.inspect}
struct Tree#{rule.capitalize} {
  TokenCode code;
  union {
    #{args.map{ |a| struct(a[0],a[1]) }*"\n    "}
  } u;
};

"""
  elsif args.length == 1
    puts """
// Structure: #{rule} #{args.inspect}
struct Tree#{rule.capitalize} {
  #{args.first.last.map{|a| tree(a) }*";\n  " };
};
"""
  end
end

File.open("parser.c", "r") do |fl|
#   $/="\n\n"
  lines = fl.map {|g| $1 if g.match(/(t_.+?;)/) }.compact
  lines.sort!

  base = Hash.new []
  args = []
  order = %w(Program block decls decl type type_1 basic stmts stmt loc loc_1 bool bool_1 join join_1 equality equality_1 rel expr expr_1 term term_1 unary factor)
  
  cols = lines.map do |ln|
    ln.gsub!(/_\d/,"@")
    ln = ln.gsub(/\((.*)\);/,'')
    
    ars = $1.split(/\s*,\s*/)
    puts "ln: #{ln} #{ars.inspect}"
    ars = ars.map{ |a| a.gsub(/l\d/,'').gsub('@','_1') }
#   puts "ln: #{ars.inspect}"

    flds = ln.split('_')[1..-1].map{ |l| l.gsub('@','_1') }
    flds+[ars]
  end
  
  cols = cols.sort.uniq
  mpcols = Hash.new []
  cols.each{|c| mpcols[c.first] += [c] }
  
  # puts "mpcols: #{mpcols.map{|k,v| "\t#{k}: #{v.inspect}" }*"\n"}"
  # puts
  # puts "cols: #{cols.map{|c| c.inspect}*"\n"}"
  # puts
  # cols.each{ |c| base[c.first] += [c[1..-1]] }

#    puts "base:","#{base.map{|k,v| "#{k}: #{v.inspect}" }*"\n"}"
  
###### print out tree.c functions to set unions from parser
  order.each do |k| 
    l = mpcols[k].length
    puts "\n// ================= #{k.capitalize} #{l} #{"".ljust(40,'=')}"
    mpcols[k].each{|col| functer(l,col[0..2],col.last, base[col[0]].length)}
  end
  # order.each{|k| union(k,base[k])}
end
