#!/usr/bin/python
#
# SDTSocket module (for non-local instances)
# Run this module individually to send a test message.
# By: Dustin Ingram <dustin.ingram@nrl.navy.mil>
#

import getopt, sys
import socket

class SDTSocket:

    def __init__(self, addr, port):
        if None in [addr, port]:
            print 'Socket port & address must be specified'
            sys.exit()
        self.addr = addr
        self.port = port
        self.sock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
        self.verbose = False
        self.fulllossthreshold = None
        self.nolossthreshold = None

    def send_blah(self, command):
        if(self.sock.sendto(command,(self.addr, self.port))):
            return True
        return False

    def close(self):
        self.sock.close()

    def bind(self):
        self.sock.bind((self.addr,self.port))
    
    def recieve(self):
        return self.sock.recvfrom(1024)

    def verbose(self, flag):
        self.verbose = flag

    def setLossThresholds(self, fulllossthreshold, nolossthreshold) :
        self.fulllossthreshold = fulllossthreshold
        self.nolossthreshold = nolossthreshold
    
    def handleLocationEvent(self, node, lat, lon, alt):
        cmd = "node " + str(node) + " position " + str(lon) + "," + str(lat) + "," + str(float(alt)) + "\n"
        self.send_blah(cmd)

    def handlePathlossEvent(self, node1, node2, rx):
        #HARDCODED
        color = 'red'
        linktype = '802.11'
        #/HARDCODED

        if rx <= -float(self.fulllossthreshold) :
            cmd = 'delete link,%s,%s,%s\n' % (node1, node2, linktype)
        elif rx < -float(self.nolossthreshold) :
            cmd = 'link %s,%s,%s line %s,%s\n' % (node1, node2, linktype, color, '1')
            print cmd
        elif rx >= -float(self.nolossthreshold) : 
            cmd = 'link %s,%s,%s line %s,%s\n' % (node1, node2, linktype, color, '3')
            print cmd

        self.send_blah(cmd)
    
def main():

    try:
        opts, args = getopt.getopt(sys.argv[1:], "hp:a:c:", ["help", "testing"])
    except getopt.GetoptError, err:
        pass
    port = None
    adr = None
    cmd = None
    testing = False

    for o, a in opts:
        if o in ("-h", "--help"):
            usage()
        elif o in ("-p"):
            port = int(a)
        elif o in ("-a"):
            adr = str(a)
        elif o in ("-c"):
            cmd = str(a)
        elif o in ("--testing"):
            testing = True
        else:
            assert False, "unhandled option"

    if testing:
        if None in [adr,port,cmd]:
            usage()
        print "Testing the SDTSocket..."
        print "Creating UDP Socket on port " + str(port) + "..."
        sock = SDTSocket(adr, port)
        print "Sending SDTCMD to " + adr + ":" + str(port)
        if(sock.send_blah(cmd + '\n')):
            print "Sent SDTCMD \"" + cmd + "\""
        else:
            print "Send failed!"
        sock.close()
    else:
        usage()

def usage():
    print '''
    USAGE:
    \t./SDTSocket.py -h
    \t\tPrints this message
    \t./SDTSocket.py --testing -a SDT_IP_ADDRESS -p PORT -c 'SDT_COMMAND'
    \t\tSends a command to at UDP socket at the address on a port
    EXAMPLE: 
    \t$ ./SDTSocket.py --testing -a 127.0.0.1 -p 50730 -c "node 0 position -77.0210266113,38.8258006592,250.0"
    '''
    sys.exit()

if __name__ == "__main__":
    main()
