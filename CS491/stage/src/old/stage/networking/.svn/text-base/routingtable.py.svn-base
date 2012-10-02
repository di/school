class RoutingEntry :
    def __init__(self, destination, netmask, interface_name, metric) :
        self._destination = destination
        self._netmask = netmask
        self._interface_name = interface_name
        self._metric = metric

    def get_destination(self) :
        return self._destination

    def get_interface_name(self) :
        return self._interface_name

class RoutingTable :
    def __init__(self) :
        self._routes = {}

    def add_entry(self, entry) :
        self._routes[entry.get_destination()] = entry

    def get_route(self, dest_ip) :
        for mask, entry in self._routes.iteritems() :
            if dest_ip in mask :
                return entry.get_interface_name()
        return None
