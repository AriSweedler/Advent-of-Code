#!/usr/bin/env python3
import sys

def place(wire, board):
	x = 0
	y = 0

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

			# Initiate row if needed
			if (x not in board): board[x] = set()

			# Add wire to board
			board[x].add(y)

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
	for row in board0:
		if row not in board1: continue
		# Set intersect to find columns where wires collide
		# The collision closest to 0 is the one we care about
		cross = board0[row] & board1[row]
		if (cross): crossings.append(abs(row) + min(map(abs, cross)))

	print(min(crossings))
