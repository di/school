from math import sqrt
from stage.event import Event
from stage.model import Model

class NetworkSim :
    TRANS_RANGE = 15
    def __init__(self, simulation) :
        self._simulation = simulation

    def _distance(self, n1, n2) :
        dx = n1.get('position')[0] - n2.get('position')[0]
        dy = n1.get('position')[1] - n2.get('position')[1]
        dz = n1.get('position')[2] - n2.get('position')[2]
        return sqrt(dx**2 + dy**2 + dz**2)

    def _bc_link(self, n1, n2, up) :
        if up :
            link_str = 'LINK_UP'
        else :
            link_str = 'LINK_DOWN'
        self._simulation.get_api().get_event_channel().publish(Event(link_str, Model(n1=n1, n2=n2)))

    def can_transmit(self, n1, n2) :
        if self._distance(n1, n2) <= NetworkSim.TRANS_RANGE :
            self._bc_link(n1, n2, True)
            return True
        self._bc_link(n1, n2, False)
        return False

    def on_sent_event(self, event) :
        n1 = self._simulation.get_scen().get_nodes()[int(event.get_model().get('src')[1:])]
        n2 = self._simulation.get_scen().get_nodes()[int(event.get_model().get('dest')[1:])]
        if self.can_transmit(n1, n2) :
            self._simulation.get_api().get_event_channel().publish(Event('RECV', event.get_model()))
