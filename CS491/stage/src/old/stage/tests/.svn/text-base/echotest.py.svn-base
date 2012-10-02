from stage.tests.echoserver import EchoServer
from stage.core.node import Node
from stage.networking.interfaces.ethernet import EthernetInterface

servernode = Node(0)
servernode.add_interface('eth0', EthernetInterface())
servernode.add_application(EchoServer())
