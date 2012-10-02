from network import Network
from stage.model import Model

class NetworkConcrete(Network) :
    def __init__(self, scen_inst) :
        Network.__init__(self, scen_inst)

        for node_model in self._scen_inst.get_nodes() :
           node_model.get('interfaces')['eth0'] = Model(type='wireless', range=20, ssid='wlan0')
