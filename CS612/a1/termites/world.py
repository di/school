

class world:

    def __init__(self, size=100):
        self.size = 100
        self.termites = []
        self.ticks = 0

    def add_termite(self, t):
        self.termites.append(t)

    def tick(self):
        self.ticks += 1
        for t in self.termites :
            t.tick()
