import random


class termite:

    def __init__(self, x=0, y=0):
        self.x = x
        self.y = y
        self.wood = None
        self.direction = [0 for i in range(8)]
        self.update_direction(random.randint(0, 8))

    def tick(self, world):
        self.move(world)
        if self.wood is not None:
            self.drop_wood(world, self.x, self.y, self.wood)
        else:
            self.take_wood(world, self.x, self.y)

    def take_wood(self, world, x, y):
        if world.has_wood(x, y) and world.wood_adjacent(x, y) < 5:
            self.wood = world.take_wood(x, y)

    def drop_wood(self, world, x, y, wood):
        if not world.has_wood(x, y):
            if world.wood_adjacent(x, y, wood.wood_type) > 2:
                self.wood = world.drop_wood(x, y, wood)

    def update_direction(self, i):
        self.direction = [0 for _ in range(8)]
        for x in range(i-2, i+3):
            self.direction[x % 8] = 1

    def flip_direction(self):
        self.direction = [int(not x) for x in self.direction]

    def color(self):
        if self.wood is not None:
            return (0, 255, 0)
        else:
            return (255, 0, 0)

    def move(self, world):
        move_set = [i for i, v in enumerate(self.direction) if v is 1]

        while(True):
            if len(move_set) == 0:
                self.flip_direction()
                move_set = [i for i, v in enumerate(self.direction) if v is 1]
            new_dir = random.choice(move_set)
            x = y = 0
            if 0 <= new_dir <= 2:
                y -= 1
            if 4 <= new_dir <= 6:
                y += 1
            if 2 <= new_dir <= 4:
                x += 1
            if 6 <= new_dir <= 7 or new_dir is 0:
                x -= 1

            if world.valid_step(self.x + x, self.y + y):
                self.x += x
                self.y += y
                self.update_direction(new_dir)
                break
            else:
                move_set.remove(new_dir)
