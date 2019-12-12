CC = g++
CFLAGS = --std=c++17
OBJECTS = SANTIAC.o
PROG = santiac

.DEFAULT: $(PROG)

$(PROG): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

SANTIAC.o: SANTIAC.h SANTIAC.cpp
	$(CC) $(CFLAGS) -c -o SANTIAC.o SANTIAC.cpp

.PHONY: test
test: $(PROG)
	cat ../inputs/input$(T) | ./$(PROG)

SANTIAC.o: SANTIAC.cpp SANTIAC.h

.PHONY: clean
clean:
	rm $(PROG) $(OBJECTS)
