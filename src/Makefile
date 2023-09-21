OBJS= history.o tokenizer.o

all:interface # doesn't need a body

interface:
	cc -o interface interface.c $(OBJS)

$(OBJS): tokenizer.h history.h

clean:
	rm -f *.o interface

run:interface # re-compiles the program if necessary before running it.
	./interface
