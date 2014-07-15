PROGS = fork inet_pton IPConversion timeDate reentrantFunc reentrantJmp
CFLAGS = -g
CC = clang

all: $(PROGS) error.o

.SECONDEXPANSION:
$(PROGS): error.o $$@.c
	$(CC) $(CFLAGS) error.o -o $@ $@.c $(LDFLAGS)  


clean:
	rm -f $(PROGS)  *.o *.out *.s  *.gch core.info

