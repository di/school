import time
import random
import math
from stage.agent import Agent

class CircleWalkerAgent(Agent) :
    def __init__(self, model) :
        Agent.__init__(self, model)
        self._moving = False
        self._seq = 0
        self._step = math.pi / 10
        self._last_step = 0
        self._radius = 15
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
        radiusdir = 1
        while self._moving :

   
            nextpos = self._getnextmove(1) 
            new_pos = (nextpos[0],nextpos[1],0)

            if((new_pos[0] == self._origin[0] + self._radius) and (new_pos[1] == self._origin[1])):
                self._radius = self._radius + radiusdir
                #print 'Radius changed to %s' % self._radius

            if((self._radius => 17)  or (self._radius <= 15)):
                radiusdir = radiusdir * -1
                #print 'radiusdir now %s' % radiusdir

            print 'Agent on %s at x= %s y= %s' % (self._owner.get_name(), nextpos[0] ,nextpos[1])
            self._api.set_position(new_pos)
            time.sleep(1)


                
    def _getnextmove(self, dir):
        y0 = self._origin[1]
        x0 = self._origin[0]

        angle = self._last_step + self._step * dir
        #if(angle > 2 * math.pi):
        #    angle = 0
        #elif(angle < 0):
        #    angle = (2 * math.pi) - angle

        
        y = (y0 + self._radius * math.sin(angle))
        x = (x0 + self._radius * math.cos(angle))

        if(y - math.floor(y) < 0.5):
            y = math.floor(y)
        else:
            y = math.ceil(y)
        if(x - math.floor(x) < 0.5):
            x = math.floor(x)
        else:
            x = math.ceil(x)
        self._last_step = angle

        return (x,y)
