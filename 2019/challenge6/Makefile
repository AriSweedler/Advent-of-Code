CC = g++
CFLAGS = --std=c++17

p1: part1.cpp
	$(CC) $(CFLAGS) part1.cpp -o p1

.PHONY: test1
test1: p1
	cat input$(T) | ./p1

p2: part2.cpp
	$(CC) $(CFLAGS) part2.cpp -o p2

.PHONY: test2
test2: p2
	cat input$(T) | ./p2

.PHONY: clean
clean:
	rm p1 p2
