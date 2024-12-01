CC = gcc
CFLAGS =
OBJECTS = digital.o
PROG = digital

.DEFAULT: $(PROG)

$(PROG): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

digital.o: digital.h digital.c
	$(CC) $(CFLAGS) -c -o digital.o digital.c

.PHONY: test
test: $(PROG)
	cat ./inputs/input$(T) | ./$(PROG)

.PHONY: clean
clean:
	rm $(PROG) $(OBJECTS)
