
def process(text)
  first = text.index("{")
  last = text.rindex("}")
  if first && last
    prefix = text[0..(first - 1)]
    puts "Prefix is %s" % prefix
    inner = text[first..last]
    puts "Inner is %s" % inner
    if inner.length > 2
      innermore = inner[1..-2]
      puts "Innermore is %s" % innermore
      process(innermore)
    else
      puts "Inner is to small"
    end
  else
    puts "Innermost is %s" % text
  end
end


t = "test\torri { \ntest boom { \n}\ntest pa {\n}\n}"

puts "----------------------------------------------------------------"

process(t)


text = "test { }"

first = text.index("{")
last = text.index("}")

if first && last
  puts "First is %d and last is %d" % [first,last]
else
  puts "First and last is not set"
end