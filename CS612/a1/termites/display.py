import pygame

class display:

    def __init__(self, size=100, scale=5):
        self.size = size
        self.scale = scale
        background_color = (255,255,255)
        screen = pygame.display.set_mode((self.size*self.scale, self.size*self.scale))
        screen.fill(background_color)

        surface = pygame.display.get_surface()
        self.pxarray = pygame.PixelArray(surface)
        pygame.display.flip()

    def draw_pix(self, x, y, color=(0,0,0)):
        for _x in range(x*self.scale, x*self.scale+self.scale):
            for _y in range (y*self.scale, y*self.scale+self.scale):
                self.pxarray[_x,_y] = color

    def redraw(self, world):
        for y in range(self.size):
            for x in range(self.size):
                color = int(not world.world[y][x])*255
                self.draw_pix(x=x, y=y, color=(color, color, color))
        for t in world.termites:
            self.draw_pix(t.x, t.y, t.color())
        pygame.display.flip()
