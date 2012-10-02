from stage.core.application import Application
from stage.networking.layers.internet.ipv4 import Ipv4InternetLayer

class EchoServer(Application) :
    def __init__(self) :
        EchoServer.__init__(self)

    def _main(self) :
        print 'Starting EchoServer'
        s = UdpSocket(Ipv4InternetLayer())
        ip = self.get_node().get_interface('eth0').get_ip()
        s.bind(ip, 1234)
