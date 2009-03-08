#!/usr/bin/env ruby -n
BEGIN{
  # require 'rdiscount'
  $func = {}
  File.open('parser.c', 'r') do |fl|
    fl.each do |ln|
      if m = ln.match(/.+ p_(\w+)\s*\(.+\{/)
        nm, ln, cn = m[1].downcase,$., 0
        pth = File.expand_path('parser.c')
        # pth = 'parser.c'
        # func[m[1]] = "<a&file://#{par_pth}&#{$.}&0>#{m[1]}</a>" if m
        $func[nm] = "[#{nm}](txmt://open/?url=file://#{pth}&line=#{ln}&column=#{cn})" if m
        # [an example](http://example.com/ "Title")
        # puts  RDiscount.new(func[m[1]]).to_html
        # puts "#{nm}: #{$func[nm]}\n\n"
      end
    end
  end
}

print $_.gsub(/(\w+)/) { |w| $func.has_key?($1.downcase) ? $func[$1.strip.downcase] : w }
# print $_
