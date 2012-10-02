from threading import Thread

class Application(Thread) :
    def __init__(self) :
        self._node = None

    def set_node(self, node) :
        assert self._node == None, 'Node already set'
        self._node = node

    def get_node(self) :
        return self._node

    def _main(self) :
        pass

    def run(self) :
        self._main()
