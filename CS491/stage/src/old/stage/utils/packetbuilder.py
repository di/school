class PacketBuilder :
    class DuckType : pass

    @staticmethod
    def build(struct, **values) :
        instance = PacketBuilder.DuckType()
        for attr, value in values.iteritems() :
            setattr(instance, attr, value)
        return struct.build(instance)

    @staticmethod
    def parse(struct, data) :
        return struct.parse(data)
