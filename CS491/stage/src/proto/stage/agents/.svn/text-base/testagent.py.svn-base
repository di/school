import time
from stage.agent import Agent

class TestAgent(Agent) :
    def __init__(self, model) :
        Agent.__init__(self, model)
        self._seq = 0
        print '--- Starting ---'

    def _on_message(self, src, message, iface) :
        print 'Agent on %s got %s from %s on %s' % (self._owner.get_name(), message, src, iface.get('ssid'))

    def run(self) :
        if self._model.get('job') == 'recv' :
            self._api.recv(self._owner.get_model().get('interfaces')['eth0'], self._on_message)
            while True :
                pass
        else :
            self._api.get_event_channel().block_until('start')
            while True :
                self._api.send(self._owner.get_model().get('interfaces')['eth0'], 'n1', str(self._seq))
                self._api.send(self._owner.get_model().get('interfaces')['eth0'], 'n3', str(self._seq))
                print 'Agent on %s sent %s' % (self._owner.get_name(), self._seq)
                self._seq += 1
                if self._owner.get_name() == 'n0' :
                    self._api.set_position((self._seq, self._seq, 0))
                time.sleep(1)
