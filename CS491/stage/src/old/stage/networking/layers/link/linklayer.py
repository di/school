class LinkLayer :
    def __init__(self, interface) :
        self._interface = interface

    def _ip_to_mac(self, ip) :
        return ip

    def _mac_to_ip(self, mac) :
        return mac

    def send(self, dest_ip, data) :
        pass

    def recv(self, data) :
        pass
