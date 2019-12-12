CC = g++
CFLAGS = --std=c++17
OBJECTS = SANTIAC.o
PROG = santiac

.DEFAULT: test1

$(PROG): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

SANTIAC.o: SANTIAC.h SANTIAC.cpp
	$(CC) $(CFLAGS) -c -o SANTIAC.o SANTIAC.cpp

.PHONY: test1
test: p1
	cat ../inputs/input$(T) | ./p1

SANTIAC.o: SANTIAC.cpp SANTIAC.h

.PHONY: clean
clean:
	rm $(PROG) $(OBJECTS)
