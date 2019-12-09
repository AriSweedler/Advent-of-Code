#!/usr/bin/env python3
import sys

def execute(data):
	# Initialize
	head = 0
	done = False

	print(data)

	# Execute the program
	while(not done):
		# Format string to add leading 0s until we're 5 characters long
		opcode = f'{data[head]:05}'
		op = int(opcode[-2:])
		print(f'\nopcode: {opcode}')
		if (op == 99): break
		if (op not in {1, 2, 3, 4, 5, 6, 7, 8}):
			print(f'An error occurred: opcode: {opcode}')
			print(f'op = {op}')
			print(f'data[head] = {data[head]}')
			break

		# Parse the opcode
		if (op in {1, 2}):
			# Retrieve arguments
			arg1 = data[head+1]
			if (int(opcode[-3]) == 0):
				print(f'dereferencing arg1 (from addr{arg1} to value {data[arg1]})')
				arg1 = data[arg1]
			# parameter 2
			arg2 = data[head+2]
			if (int(opcode[-4]) == 0):
				print(f'dereferencing arg2 (from addr{arg2} to value {data[arg2]})')
				arg2 = data[arg2]
			# parameter 3 (written to, never in immediate mode)
			arg3 = data[head+3]

			print(f'arg1: {arg1}')
			print(f'arg2: {arg2}')
			print(f'arg3: {arg3}')

			# Execute and write back and write back
			if (op == 1):
				print(f'data[{arg3}] = {arg1} + {arg2} = {arg1 + arg2}')
				data[arg3] = arg1 + arg2
			elif (op == 2):
				print(f'data[{arg3}] = {arg1} * {arg2} = {arg1 * arg2}')
				data[arg3] = arg1 * arg2

			# increment instruction pointer
			head += 4
		elif op == 3:
			# Retrieve arguments
			arg1 = data[head+1]

			# Execute
			giver = 5
			data[arg1] = giver
			print(f'System asks for input. We give it giver')
			print(f'arg1: {arg1}')
			print(f'data[{arg1}] = {data[arg1]}')

			# increment instruction pointer
			head += 2
		elif op == 4:
			# Retrieve arguments
			arg1 = data[head+1]
			if (int(opcode[-3]) == 0):
				print(f'dereferencing arg1 (from addr{arg1} to value {data[arg1]})')
				arg1 = data[arg1]

			# Execute
			print(f'System prints {arg1}')
			head += 2
		elif op == 5:
			arg1 = data[head+1]
			# if arg1 is non-zero, sets instruction pointer second parameter
			if (int(opcode[-3]) == 0):
				print(f'dereferencing arg1 (from addr{arg1} to value {data[arg1]})')
				arg1 = data[arg1]
			arg2 = data[head+2]
			if (int(opcode[-4]) == 0):
				print(f'dereferencing arg2 (from addr{arg2} to value {data[arg2]})')
				arg2 = data[arg2]

			# increment instruction pointer
			head += 3
			# Execute
			if (arg1 != 0):
				print(f'arg1 is not zero. set insn pointer to {arg2}')
				head = arg2
			else:
				print(f'arg1 is zero. Do nothing')

		elif op == 6:
			arg1 = data[head+1]
			# if arg1 is zero, sets instruction pointer second parameter
			if (int(opcode[-3]) == 0):
				print(f'dereferencing arg1 (from addr{arg1} to value {data[arg1]})')
				arg1 = data[arg1]
			arg2 = data[head+2]
			if (int(opcode[-4]) == 0):
				print(f'dereferencing arg2 (from addr{arg2} to value {data[arg2]})')
				arg2 = data[arg2]

			# increment instruction pointer
			head += 3
			# Execute
			if (arg1 == 0):
				print(f'arg1 is zero. set insn pointer to {arg2}')
				head = arg2
			else:
				print(f'arg1 is not zero. Do nothing')
		elif op == 7:
			# if the first parameter is less than the second parameter, it
			# stores 1 in the position given by the third parameter. Otherwise,
			# it stores 0.
			# Retrieve arguments
			arg1 = data[head+1]
			if (int(opcode[-3]) == 0):
				print(f'dereferencing arg1 (from addr{arg1} to value {data[arg1]})')
				arg1 = data[arg1]
			# parameter 2
			arg2 = data[head+2]
			if (int(opcode[-4]) == 0):
				print(f'dereferencing arg2 (from addr{arg2} to value {data[arg2]})')
				arg2 = data[arg2]
			# parameter 3 (written to, never in immediate mode)
			arg3 = data[head+3]

			print(f'arg1: {arg1}')
			print(f'arg2: {arg2}')
			print(f'arg3: {arg3}')

			# Execute and write back and write back
			result = 1 if arg1 < arg2 else 0
			print(f'data[{arg3}] = {arg1} < {arg2} = {result}')
			data[arg3] = result

			# increment instruction pointer
			head += 4
		elif op == 8:
			# Retrieve arguments
			arg1 = data[head+1]
			if (int(opcode[-3]) == 0):
				print(f'dereferencing arg1 (from addr{arg1} to value {data[arg1]})')
				arg1 = data[arg1]
			# parameter 2
			arg2 = data[head+2]
			if (int(opcode[-4]) == 0):
				print(f'dereferencing arg2 (from addr{arg2} to value {data[arg2]})')
				arg2 = data[arg2]
			# parameter 3 (written to, never in immediate mode)
			arg3 = data[head+3]

			print(f'arg1: {arg1}')
			print(f'arg2: {arg2}')
			print(f'arg3: {arg3}')

			# Execute and write back and write back
			result = 1 if arg1 == arg2 else 0
			print(f'data[{arg3}] = {arg1} == {arg2} = {result}')
			data[arg3] = result

			# increment instruction pointer
			head += 4

	return data[0]

# determine what pair of inputs produces the output 19690720
if __name__ == "__main__":
	data = list(map(int, sys.stdin.readlines()[0].split(',')))
	execute(data)
