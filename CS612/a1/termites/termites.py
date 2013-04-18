from termite import termite
from world import world
from display import display
from time import sleep
import pygame
import argparse
import random

parser = argparse.ArgumentParser()
parser.add_argument('-e', required=True)
parser.add_argument('-c', action='store_true')
args = vars(parser.parse_args())
args_e = int(args['e'])
command_line = args['c']
t1 = termite(x=random.randint(0,100-1),y=random.randint(0,100-1))
world = world(density=0.3, size=100)
world.add_termite(t1)
if not command_line:
    disp = display(size=100, scale=4)

running = True
while running:
    if not command_line:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
    world.tick()
    if world.ticks % args_e is 0:
        print "%d,%d" % (world.ticks, world.pile_count())
        if not command_line:
            disp.redraw(world)
    if world.ticks > 100000:
        running = False
