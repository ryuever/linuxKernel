PROGS = fork timeDate wait core_pattern_pipe_test
CFLAGS = -g

all: $(PROGS) error.o

.SECONDEXPANSION:
$(PROGS): error.o $$@.c
	$(CC) $(CFLAGS) error.o -o $@ $@.c $(LDFLAGS)  


clean:
	rm -f $(PROGS)  *.o *.out *.s  *.gch core.info

