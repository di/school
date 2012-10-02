#!/usr/bin/python
from stage.api import API
from stage.SDTSocket import SDTSocket

class sdt_foobar :
    
    def __init__(self) :
        self._channel = API('foobar').get_event_channel()
        self._channel.subscribe('LINK_UP', self.link_up)
        self._channel.subscribe('LINK_DOWN', self.link_down)
        self._channel.subscribe('MOVEACPT', self.moveacpt)
        
        self._sock = SDTSocket('127.0.0.1', 50730)
        self._sock.setLossThresholds(100,101)

        self.lat_bot_left = 39.9534
        self.lon_bot_left = -75.1912
        self.delta = 0.0045 #deg lat/long
        self.max_altitude = 500 #meters
        self.random_scale = 100

    def link_up(self, event) :
        node1 = event.get_model().get('n1').get('name')
        node2 = event.get_model().get('n2').get('name')
        self._sock.handlePathlossEvent(node1, node2, 200)
        self.debug("link_up: %s, %s" % (node1, node2))

    def link_down(self, event) :
        node1 = event.get_model().get('n1').get('name')
        node2 = event.get_model().get('n2').get('name')
        self._sock.handlePathlossEvent(node1, node2, -200)
        #self.debug("link_down: %s, %s" % (node1, node2))

    def moveacpt(self, event) :
        node = event.get_model().get('name')
        x,y,z = event.get_model().get('pos')
        lat = self.lat_bot_left + (self.delta/self.random_scale)*y
        lon = self.lon_bot_left + (self.delta/self.random_scale)*x
        alt = (self.max_altitude/self.random_scale)*z
        self._sock.handleLocationEvent(node, lat, lon, alt)
        #self.debug("moveacpt: %s (%s, %s)" % (node, x, y))

    def debug(self, string) :
        print string

if __name__ == "__main__" :
   foo = sdt_foobar() 
