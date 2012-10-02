import sys
from threading import Thread
from stage.model import Model
from stage.agent import Agent
from stage.api import API

class Node :
    def __init__(self, model) :
        self._model = Model.from_string(model)
        self._name = self._model.get('name')
        self._api = API(self)
        self._api.get_event_channel().subscribe('MOVEACPT', self._on_move)
        self._position = self._model.get('position')

    def _on_move(self, event) :
        if event.get_model().get('name') == self._name :
            self._position = event.get_model().get('pos')
            #print 'NODE %s HEARD ACCEPT %s' % (self._name, self._position)

    def get_position(self) :
        return self._position

    def get_name(self) :
        return self._name

    def get_model(self) :
        return self._model

    def start(self) :
        for agent_model in self._model.get('agents') :
            agent_model.set_owner(self)
            Thread(target=agent_model.run()).start()

if __name__ == '__main__' :
    Node(sys.argv[1]).start()
    while True :
        pass
