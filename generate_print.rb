#!/usr/bin/env ruby

def printer(type, name)
  if not name.match(/code/)
    puts "   print_#{type}(d+1, v->#{name});"
  else
    puts "   print_tok(d, v->#{name});"
  end    
end

def printer_union(uname, type, name)
  puts "      print_#{type}(d+1, v->u.#{uname}.#{name});"
end
def print_union(uname, toks)
  toks.scan(/\s*(\w+)\s*(\w+)\s*;/).each{|t| 
    printer_union(uname, t[0], t[1]);
  }
end

File.open("tree.h", "r") do |fl|
  $/="//"
  lines = fl.map {|l| l.split("\n") }
  lines = lines.map {|ls| ls[1..-1] if ls[1].match(/^\s*struct/) }.compact
  
  
  st = lines.map do |ln| 
    func = ln[0].match(/struct (Tree\w+)/)[1]
    puts """
extern void print_#{func}( int d, #{func} v ) {
   if (!v) return;
   printer(\"#{func.gsub(/Tree|Token/,'')}:\", d);
"""
    s = [ln.shift.match(/(Tree\w+)/)[1]]
    ln, un = (ln*"\n").split('union')
    # puts "line: #{ln}"
    ln = ln.split("\n")
    # un = un.split("{") if un
    un = un.split("\n")*" " if un

    ln.each do |l| 
      m=l.match /(\w+)\s+(\w+);/
      printer(m[1], m[2]) if m
    end

    #un.each do |u|
    #  print_union(u)
    #end if un
    if un
      us = un.scan(/struct \{(.+?)\}\s*(u_\w+);/)
      us.each {|u| 
        puts "   if (v->code == TOK_#{u[1].gsub('u_','')}) \{";
        print_union(u.last,u.first);
        puts "   }"
      }
      #puts "us: #{us.inspect}"
    end
    puts "}\n"
    s+[un]
  end
  #puts "Lines: #{lines.map {|l| l.inspect}*"\nLines:"}"
  #puts "Structs:\n#{st.map {|s| s*"\n\t"}*"\nStructs:\n"}"
  #puts "Structs:\n#{st.map {|s| s.inspect}*"\nStructs:\n"}"
end
