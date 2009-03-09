prog:=$(notdir $(PWD))

gens+=$(addsuffix .c,$(basename $(wildcard *.gperf *.y *.l)))
srcs+=$(wildcard *.c *.cc) $(gens)
objs+=$(addsuffix .o,$(basename $(srcs)))
scanner_objs+=scanner/error.o scanner/scanner.o  scanner/strtab.o   scanner/token.o scanner/tokens.o

# ccflags+=-MMD -g -Wall
ccflags+=-g -Wall -std=c99
cccflags+=-g -Wall
ldflags+=-lreadline -lncurses -lstdc++

test:=./$(prog)

%.c: %.gperf
	gperf $< > $@

%.c: %.y
	bison -o $@ $<

%.c: %.l
	flex -o$@ $<

%.o: %.c
	gcc $(ccflags) -c $<

%.o: %.cc
	g++ $(cccflags) -c $<

generate: main.o generator.o printlib.o parser.o symtaben.o terminals.o tree.o symtab.o $(scanner_objs)
	gcc $(ccflags) -o $@ $^ $(ldflags)

print_parse: print_parse.o printlib.o parser.o symtaben.o terminals.o tree.o symtab.o $(scanner_objs)
	gcc $(ccflags) -o $@ $^ $(ldflags)

# bubble.java  scope.java  simple.java  source.java

bubble: print_parse 
	./print_parse < bubble.java | ruby -n liner.rb 
	cat bubble.java

scope: print_parse 
	./print_parse < scope.java | ruby -n liner.rb 
	cat scope.java

simple: print_parse 
	./print_parse < simple.java | ruby -n liner.rb 
	cat simple.java

source: print_parse 
	./print_parse < source.java | ruby -n liner.rb 
	cat source.java


$(prog): $(objs)
	gcc $(ccflags) -o $@ $^ $(ldflags)

.PHONY: clean test

clean::
	rm -f $(gens) $(objs) *.o *.d $(prog) .history *.gch

test: $(prog)
	$(test)

-include *.d
