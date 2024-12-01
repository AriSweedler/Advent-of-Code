#!/usr/bin/env python3
import sys

def place(wire, board):
	x = 0
	y = 0
	distance = 0

	decodeX = {'U': 0, 'D': 0, 'L': -1, 'R': 1}
	decodeY = {'U': 1, 'D': -1, 'L': 0, 'R': 0}

	for w in wire:
		direction = w[0]
		dx = decodeX[direction]
		dy = decodeY[direction]
		count = int(w[1:])
		for i in range(0, count):
			# Update location
			x += dx
			y += dy
			distance += 1

			# Initiate row if needed
			if (x not in board): board[x] = dict()

			# Add wire to board
			if y not in board[x]:
				board[x][y] = distance

if __name__ == "__main__":
	wires = list()
	boards = list()
	for line in sys.stdin:
		wires.append(line.split(','))

	board0 = dict()
	board1 = dict()
	place(wires[0], board0)
	place(wires[1], board1)

	crossings = list()
	for row_number in board0:
		if row_number not in board1: continue
		for column_number in board0[row_number]:
			if column_number not in board1[row_number]: continue
			steps0 = board0[row_number][column_number]
			steps1 = board1[row_number][column_number]
			steps = steps0 + steps1
			crossings.append(steps)

	print(min(crossings))
