#!/usr/bin/env python3
import sys

def execute(data, noun, verb):
	# Initialize
	head = 0
	done = False
	# replace position 1 with the value 12 and replace position 2 with the value 2.
	data[1] = noun
	data[2] = verb

	# Execute the program
	while(not done):
		op = data[head]
		if (op == 99 or op not in {1, 2}): break

		# Parse the opcode
		n1_addr = data[head+1]
		n2_addr = data[head+2]
		writeback_addr = data[head+3]
		n1 = data[n1_addr]
		n2 = data[n2_addr]

		# Execute the opcode
		if (op == 1):
			result = n1 + n2
		elif (op == 2):
			result = n1 * n2

		# Write back
		data[writeback_addr] = result

		# Next op
		head += 4

	return data[0]

# determine what pair of inputs produces the output 19690720
if __name__ == "__main__":
	data = list(map(int, sys.stdin.readlines()[0].split(',')))
	for noun in range(0,100):
		for verb in range(0,100):
			data_copy = data.copy()
			answer = execute(data_copy, noun, verb)
			if (answer == 19690720): # this is a magic number
				print(100 * noun + verb)
