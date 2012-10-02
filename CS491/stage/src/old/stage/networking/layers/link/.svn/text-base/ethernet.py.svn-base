from construct import *
from stage.networking.layers.link.linklayer import LinkLayer
from stage.utils.packetbuilder import PacketBuilder

class EthernetLinkLayer(LinkLayer) :
    def __init__(self) :
        LinkLayer.__init__(self)
        self._header_struct = Struct('ethernet_header',
            Bytes('source_mac', 6),
            Bytes('destination_mac', 6),
            UBInt16('internet_proto'),
        ) # TODO: Preamble, start-of-delimiter
        self._trailer_struct = Struct('ethernet_trailer',
            UBInt32('crc32'),
        ) # TODO: Interframe gap

    def send(self, internet_proto, dest_ip, data) :
        header = PacketBuilder.build(self._header_struct, 
            source_mac = self._interface.get_mac(),
            destination_mac = self._ip_to_mac(dest_ip),
            internet_proto = IPv4)
        trailer = PacketBuilder.build(self._trailer_struct,
        crc32 = 0)
        full_frame = header + data + trailer
        self._interface.send(full_frame)

    def recv(self, data) :
        header = PacketBuilder.parse(data[0:self._header_struct.sizeof()])

        data = data[self._header_struct.sizeof():]
        data = data[:-self._trailer_struct.sizeof()]

        internet_layer = NetworkLayer.from_int(header.internet_proto)
        internet_layer.recv(self._mac_to_ip(header.source_mac), data)
