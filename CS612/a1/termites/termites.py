from termite import termite
from world import world
from display import display
from time import sleep
import pygame
import argparse
import random

def run(e, n_termites=1, command_line=True):
    w = world(density=0.3, size=100)
    for _ in range(n_termites):
        w.add_termite(termite(x=random.randint(0,100-1),y=random.randint(0,100-1)))

    if not command_line:
        disp = display(size=100, scale=4)

    running = True
    out = []
    while running:
        if not command_line:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    running = False
        w.tick()
        if w.ticks % e is 0:
            out.append((w.ticks, w.pile_count()))
            if not command_line:
                disp.redraw(w)
        if w.ticks > 100000:
            running = False
    return out

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('-e', required=True)
    parser.add_argument('-c', action='store_true')
    args = vars(parser.parse_args())
    args_e = int(args['e'])
    command_line = args['c']
    print '\n'.join(["%d,%d" % x for x in run(args_e, command_line=command_line)])

