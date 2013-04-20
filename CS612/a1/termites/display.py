import pygame


class display:

    def __init__(self, size=100, scale=5):
        self.size = size
        self.scale = scale
        background_color = (255, 255, 255)
        mode = (self.size*self.scale, self.size*self.scale)
        screen = pygame.display.set_mode(mode)
        screen.fill(background_color)

        surface = pygame.display.get_surface()
        self.pxarray = pygame.PixelArray(surface)
        pygame.display.flip()

    def draw_pix(self, x, y, color=(0, 0, 0)):
        for _x in range(x*self.scale, x*self.scale+self.scale):
            for _y in range(y*self.scale, y*self.scale+self.scale):
                self.pxarray[_x, _y] = color

    def redraw(self, world):
        for y in range(self.size):
            for x in range(self.size):
                cell = world.world[y][x]
                color = (255, 255, 255)
                if cell is not None:
                    color = cell.color
                self.draw_pix(x=x, y=y, color=color)
        for t in world.termites:
            self.draw_pix(t.x, t.y, t.color())
        pygame.display.flip()
