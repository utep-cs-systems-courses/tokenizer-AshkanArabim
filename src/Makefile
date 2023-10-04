OBJS= history.o tokenizer.o

all:interface 

# PREV MISTAKE: you forgot to include $(OBJS) as interface's dependency...
interface: $(OBJS) interface.c tester.c
	cc -Wall -g -o interface interface.c $(OBJS)
# cc -Wall -g -o tester tester.c

# $(OBJS): tokenizer.h history.h
tokenizer: tokenizer.h history.h tokenizer.c history.c
	cc -Wall -g -o tokenizer.o tokenizer.c
	cc -Wall -g -o history.o history.c

clean:
	rm -f *.o interface

run:interface # re-compiles the program if necessary before running it.
	./interface
