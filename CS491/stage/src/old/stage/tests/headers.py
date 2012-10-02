from construct import *
class PacketBuilder :
    class DuckType : pass
    @staticmethod
    def build(struct, **values) :
        instance = PacketBuilder.DuckType()
        for attr, value in values.iteritems() :
            setattr(instance, attr, value)
        return struct.build(instance)

header_a = Struct("header_a",
    UBInt16("value1"),
    UBInt16("value2"),
)

header_b = Struct("header_b",
    UBInt16("value1"),
    UBInt16("value2"),
)

packeda = PacketBuilder.build(header_a, value1 = 1, value2 = 2)
packedb = PacketBuilder.build(header_b, value1 = 3, value2 = 4)
both = packeda + packedb
print header_a.parse(both[0:header_a.sizeof()])
print header_b.parse(both[header_a.sizeof():])
