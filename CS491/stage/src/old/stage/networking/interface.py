class Interface :
    def __init__(self, mac_address, link_layer) :
        self._mac_address = mac_address
        self._ip = None
        self._subnetmask = None
        self._link_layer = link_layer

    def get_mac(self) :
        return self._mac_address

    def get_ip(self) :
        return self._ip

    def set_ip(self, ip) :
        self._ip = ip

    def set_subnetmask(self, mask) :
        self._mask = mask

    def send(self, data) :
        # TODO: send data to daemon
