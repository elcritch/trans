#!/usr/bin/env ruby

def tree(arg)
#   puts "arg: #{arg}"
  return "Tree#{arg.capitalize} #{arg}"
end

def assgn(name, arg, len)
  if len == 1
    return "v->#{arg} = #{arg};"
  else
    return "v->u.u_#{name}.#{arg} = #{arg};"
  end
end

def functer(names, args, len)
  tname = "t_#{names[0]}_#{names[1]}"
  
  puts """
// #{names.first.capitalize} #{args.inspect}
extern Tree#{names[0].capitalize} #{tname}(#{ args.map{|a| tree(a) }*", " }) {
  ALLOC(Tree#{names[0].capitalize});
  v->code=TOK_#{names[1]};
  #{ args.map{ |a| assgn(names[1],a, len) }*"\n  " }
  return v;
}
"""
end

def struct(name, args)
  return """struct {
      #{args.map{|a| tree(a) }*";\n      " }
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
  TokenCode code;
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

  cols = lines.map do |ln|
    ln.gsub!(/_\d/,"@")
    ln = ln.gsub(/\((.*)\);/,'')
    ars = $1.split(/\s*,\s*/).map{ |a| a[2..-1].gsub('@','') }
#   puts "ln: #{ars.inspect}"

    flds = ln.split('_')[1..-1].map{ |l| l.gsub('@','_1') }
    flds+[ars]
  end
  
  cols = cols.sort.uniq
#   puts "cols: #{cols.map{|c| c.inspect}*"\n"}"

  cols.each{ |c| base[c.first] += [c[1..-1]] }

#    puts "base:","#{base.map{|k,v| "#{k}: #{v.inspect}" }*"\n"}"
  
###### print out tree.c functions to set unions from parser
  cols.each{|col| functer(col[0..2],col.last, base[col[0]].length)}
#    base.each{|k,v| union(k,v)}
end
