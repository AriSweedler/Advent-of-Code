
p1: part1.cpp
	g++ --std=c++17 part1.cpp -o p1

.PHONY: test
test: p1
	cat input$(T) | ./p1

.PHONY: clean
clean:
	rm p1 p2
