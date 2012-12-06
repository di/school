#!/usr/bin/python
from __future__ import print_function
import sys

board_size = 4

for row in range(1, board_size + 1) :
    for col in range(1, board_size + 1) :
        for move in [(2, 1), (2, -1), (-2, 1), (-2, -1), \
            (1, 2), (-1, 2), (1, -2), (-1, -2)] :
            rpos = row + move[0]
            cpos = col + move[1]
            if 0 < rpos <= board_size and 0 < cpos <= board_size :
                print('  (valid-move %s%d %s%d)' % \
                (chr(96 + col), row, chr(96 + cpos), rpos))
