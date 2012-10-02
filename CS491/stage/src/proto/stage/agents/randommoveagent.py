import time
import random
from stage.agent import Agent

class MovingAgent(Agent) :
    def __init__(self, model) :
        Agent.__init__(self, model)
        self._moving = False
        self._seq = 0
        print '--- Starting ---'

    def _on_message(self, src, message, iface) :
        print 'Agent on %s got %s from %s on %s' % (self._owner.get_name(), message, src, iface.get('ssid'))

    def stop(self,event):
        if(event.get_model().get("n1").get("name") == self._owner.get_name() or event.get_model().get("n2").get("name")
            == self._owner.get_name()):
            print 'Agent on %s stopped' % (self._owner.get_name())
            self._moving = False

    def run(self) :
        self._api.get_event_channel().subscribe('LINK_UP', self.stop)
        self._api.get_event_channel().block_until('start')
        self._moving = True
        while self._moving :
                current_pos = self._owner.get_position();
                x = int(current_pos[0])
                y = int(current_pos[1])

                xmin = x - 2
                ymin = y - 2
                xmax = x + 2
                ymax = y + 2

                newx = max(min(random.randint(xmin,xmax),100), 0)
                newy = max(min(random.randint(ymin,ymax),100), 0)

                new_pos = (newx,newy,0)
                print 'Agent on %s at x= %s y= %s' % (self._owner.get_name(),newx,newy)
                self._api.set_position(new_pos)
                time.sleep(1)
