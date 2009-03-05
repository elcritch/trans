#!/usr/bin/env ruby

def tree(arg)
  return "Tree#{arg.capitalize} #{arg}"
end

def assgn(name, arg)
  return "v->u.u_#{name}.#{arg}=#{arg};"
end

def functer(names, args)
  tname = "t_#{names[0]}_#{names[1]}"
  
  puts """
extern Tree#{names[0].capitalize} #{tname}(#{ args.map{|a| tree(a) }*", " }) {
  ALLOC(Tree#{names[0].capitalize});
  v->code=TOK_#{names[1]};
  #{ args.map{ |a| assgn(names[1],a) }*"\n  " }
  return v;
}
"""
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
#     puts "ln: #{ars.inspect}"
    ln
    flds = ln.split('_')[1..-1].map{ |l| l.gsub('@','_1') }
    base[flds.first] += flds[1..-1]
    flds+[ars]
  end
  
  cols = cols.sort.uniq
#   puts "ln: #{lines*"\n"}"
#   puts "cols: #{cols*"\n"}"
#   puts "cols: #{cols.map{|c| c.inspect}*"\n"}"
#   puts "base: #{base.map{|k,v| "#{k.inspect} #{v.inspect}"}*"\n" }"
  cols.each{|col| functer(col[0..2],col.last)}
end
