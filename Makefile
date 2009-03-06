prog:=$(notdir $(PWD))

gens+=$(addsuffix .c,$(basename $(wildcard *.gperf *.y *.l)))
srcs+=$(wildcard *.c *.cc) $(gens)
objs+=$(addsuffix .o,$(basename $(srcs)))
scanner_objs+=scanner/error.o scanner/scanner.o  scanner/strtab.o  scanner/tokens.o

# ccflags+=-MMD -g -Wall
ccflags+=-g -Wall
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
	g++ $(ccflags) -c $<

print_parse: print_parse.o parser.o symtaben.o terminals.o tree.o symtab.o $(scanner_objs)
	gcc $(ccflags) -o $@ $^ $(ldflags)

$(prog): $(objs)
	gcc $(ccflags) -o $@ $^ $(ldflags)

.PHONY: clean test

clean::
	rm -f $(gens) $(objs) *.d $(prog) .history *.gch

test: $(prog)
	$(test)

-include *.d
