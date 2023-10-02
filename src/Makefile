OBJS= history.o tokenizer.o

all:interface 

# PREV MISTAKE: you forgot to include $(OBJS) as interface's dependency...
interface: $(OBJS) interface.c
	cc -Wall -g -o interface interface.c $(OBJS)

$(OBJS): tokenizer.h history.h

clean:
	rm -f *.o interface

run:interface # re-compiles the program if necessary before running it.
	./interface
