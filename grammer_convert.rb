
# $/="\n\n"
IO.readlines("grammar.txt","\n\n").each do |p|
  nt, prod = p.gsub("\n","").split(":")
  prod = prod.split("|")
  puts "Non term: #{nt}"
  puts "Production: count: #{prod.length} \n\t #{prod*"\n\t"}"
  puts
end