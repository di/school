from stage.eventpubsub import EventPubSub
from stage.event import Event
from stage.model import Model

class API :
    EVENT_IP = '239.192.0.100'
    EVENT_PORT = 9998

    def __init__(self, node) :
        self._events = EventPubSub(self.EVENT_IP, self.EVENT_PORT)
        self._events.start()
        self._node = node

    def get_event_channel(self) :
        return self._events

    def send(self, iface, dest, message) :
        self._events.publish(Event('SENT', Model(src=self._node.get_name(), dest=dest, message=message,
        ssid=iface.get('ssid'))))

    def recv(self, iface, cb) :
        self._events.subscribe('RECV', self._on_message, iface=iface, user_cb=cb)

    def _on_message(self, event, args) :
        if event.get_model().get('dest') == self._node.get_name() and event.get_model().get('ssid') == args['iface'].get('ssid') :
            user_cb = args['user_cb']
            user_cb(event.get_model().get('src'), event.get_model().get('message'), args['iface'])

    def set_position(self, pos) :
        self.get_event_channel().publish(Event('MOVEREQ', Model(pos=pos, name=self._node.get_name())))

    def get_position(self) :
       return self._node.get_position() 
