from threading import Thread
from stage.core.application import Application
from stage.networking.routingtable import *

class Node :
    def __init__(self, id) :
        self._id = id
        self._interfaces = InterfaceConfig()
        self._applications = []
        self._routing_table = RoutingTable()

    def get_routing_table(self) :
        return self._routing_table

    def add_interface(self, name, iface) :
        self._interfaces[name] = iface

    def get_interface(self, name) :
        return self._interfaces[name]

    def add_application(self, application) :
        application.set_node(self)
        self._applications.append(application)

    def start(self) :
        for application in self._applications :
            application.start()
