#!/usr/bin/python


def find_pad(pA, pB, cA, cB):
    ret = ""
    for plainA, plainB, cryptA, cryptB in zip(pA, pB, cA, cB):
        for pad in range(256):
            paddedA = int(plainA.encode('hex'), 16) ^ pad
            paddedB = int(plainB.encode('hex'), 16) ^ pad
            if paddedA == int(cryptA, 16) and paddedB == int(cryptB, 16):
                ret += chr(pad)
    return ret

p2_5_a = open('./plaintext/2_XOR_5_a.txt').read()
p2_5_b = open('./plaintext/2_XOR_5_b.txt').read()
c2 = open('./encrypted/ct2.hex').read().splitlines()
c5 = open('./encrypted/ct5.hex').read().splitlines()

padA = find_pad(p2_5_a, p2_5_b, c2, c5)
print padA

padB = find_pad(p2_5_b, p2_5_a, c2, c5)
print padB
