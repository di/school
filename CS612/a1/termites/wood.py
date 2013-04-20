import random

class wood:

    def __init__(self, wood_type):
        self.wood_type = wood_type
        self.color = tuple([random.randint(50,200) for _ in range(3)])
