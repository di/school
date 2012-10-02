import subprocess
import sys
import time
import signal
import os
from stage.networksim import NetworkSim
from stage.api import API
from stage.event import Event
from stage.model import Model

class Simulation :
    def __init__(self, scen_def, net_def) :
        self._scen_def = scen_def
        self._net_def = net_def
        self._api = API('simulation')
        self._api.get_event_channel().subscribe('*', self._event_callback)

        self._scen_inst = None
        self._net_inst = None

        self._network_sim = NetworkSim(self)

        def quit(signal, frame) :
            os.system('pkill python')
            sys.exit(0)
        signal.signal(signal.SIGINT, quit)

    def _event_callback(self, event) :
        if event.get_type() == 'SENT' :
            self._network_sim.on_sent_event(event)
        elif event.get_type() == 'MOVEREQ' :
            #print 'SIMULATION GOT MOVEREQ %s %s' % (event.get_model().get('name'), event.get_model().get('pos'))
            self._scen_inst.get_nodes()[int(event.get_model().get('name')[1:])].set('position', event.get_model().get('pos'))
            self._api.get_event_channel().publish(Event('MOVEACPT', Model(name=event.get_model().get('name'), pos=event.get_model().get('pos'))))
            for other_node in self._scen_inst.get_nodes() :
                n1 = self.get_scen().get_nodes()[int(event.get_model().get('name')[1:])]
                n2 = self.get_scen().get_nodes()[int(other_node.get('name')[1:])]
                if other_node.get('name') != event.get_model().get('name') :
                    self._network_sim.can_transmit(n1, n2)

    def get_scen(self) :
        return self._scen_inst

    def get_api(self) :
        return self._api

    def stop(self) :
        self._running = False

    def start(self) :
        scenmod = __import__(scen_def.split('.')[0])
        self._scen_inst = getattr(scenmod, scen_def.split('.')[1])()

        netmod = __import__(net_def.split('.')[0])
        self._net_inst = getattr(netmod, net_def.split('.')[1])(self._scen_inst)
        
        for node_model in self._scen_inst.get_nodes() :
            subprocess.Popen(('python node.py ' + node_model.__str__()).split(' '))

        time.sleep(1)
        self._api.get_event_channel().publish(Event('start', Model()))

        while True :
            pass
            
if __name__ == '__main__' :
    scen_def, net_def = sys.argv[1:]
    s = Simulation(scen_def, net_def)
    s.start()
