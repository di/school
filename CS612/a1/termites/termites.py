from termite import termite
from world import world
from display import display
from time import sleep
import pygame

t1 = termite()
world = world(density=0.3, size=10)
world.add_termite(t1)
disp = display(size=10, scale=20)

running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
    world.tick()
    disp.redraw(world)
    print world.pile_count()
