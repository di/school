from network import Network
from stage.model import Model

class NetworkConcrete(Network) :
    def __init__(self, scen_inst) :
        Network.__init__(self, scen_inst)

        ''' For each node in the scenario '''
        for node in self._scen_inst.get_nodes() :
            ''' Add a wireless interface to the node (eth0) '''
            node.get('interfaces')['eth0'] = Model(type='wireless', range=20, ssid='wlan0')
