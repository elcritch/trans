prog:=$(notdir $(PWD))

gens+=$(addsuffix .c,$(basename $(wildcard *.gperf *.y *.l)))
srcs+=$(wildcard *.c *.cc) $(gens)
objs+=$(addsuffix .o,$(basename $(srcs)))

ccflags+=-MMD -g -Wall
ldflags+=

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

$(prog): $(objs)
	gcc $(ccflags) -o $@ $^ $(ldflags)

.PHONY: clean test

clean::
	rm -f $(gens) $(objs) *.d $(prog) .history *.gch

test: $(prog)
	$(test)

-include *.d
