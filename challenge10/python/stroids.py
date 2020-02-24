#!/usr/bin/env python3
import sys
import math
from fractions import Fraction

def monitorable_asteroids(origin, field):
	xdr = 0
	xdl = 0
	vectors = set()
	y = 0
	for row in field:
		y += 1
		x = 0
		for char in row:
			x += 1
			if char != '#': continue
			xdiff = origin[0] - x
			ydiff = origin[1] - y
			if (ydiff == 0):
				if xdiff > 0: xdr = 1
				if xdiff < 0: xdl = 1
			else:
				distance = Fraction(xdiff, ydiff)
				spin = "^" if math.sin(xdiff/ydiff) > 0 else "v"
				vectors.add((distance, spin))
	return len(vectors) + xdr + xdl

def monitor(field):
	largest = 0
	y = 0
	for row in field:
		y += 1
		x = 0
		for char in row:
			x += 1
			if char != '#': continue
			position = (x, y)
			largest = max(largest, monitorable_asteroids(position, field))
	return largest

if __name__ == "__main__":
	stroid_field = list()
	for line in sys.stdin:
		stroid_field.append(list(line.rstrip()))
	answer = monitor(stroid_field)
	print(answer)
