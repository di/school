#!/usr/bin/python

from __future__ import division
from glob import glob
from itertools import izip, tee, combinations
from random import choice
import string


def xor(list_a, list_b):
    """
    XOR two lists of hex values, return a list of hex values, e.g.:

    >>> xor(['0x01', '0x02'], ['0x03', '0x04'])
    ['0x2', '0x6']

    This means:
    * '0x01' XOR '0x03' = '0x02'
    * '0x02' XOR '0x04' = '0x06'
    etc.

    """
    return [hex(int(a, 16) ^ int(b, 16)) for a, b in zip(list_a, list_b)]


def search(search_str, xor):
    """
    Return a list with the search string XOR'd with all possible strings of
    equal length in the search body, as ASCII strings, e.g.:

    >>> search('cd', ['0x01', '0x02', '0x03'])
    ['bf', 'ag']

    Here, `search_str` is a string, and `xor` is a list of hex values.

    """
    s = [x.encode('hex') for x in search_str]
    ret = []
    for w in window(xor, len(search_str)):
        xl = [hex(int(a, 16) ^ int(b, 16)) for a, b in zip(s, w)]
        ret.append(''.join([x[2:].zfill(2).decode('hex') for x in list(xl)]))
    return ret


def window(iterable, size):
    """
    Utility function to return a list with all parts of a sliding window over a
    list, e.g.:

    >>> window([1, 2, 3, 4], 2)
    [(1, 2), (2, 3), (3, 4)]

    """
    iters = tee(iterable, size)
    for i in xrange(1, size):
        for each in iters[i:]:
            next(each, None)
    return list(izip(*iters))


def rank_xors(s):
    """
    Take in all encrypted messages, and rank all possible XORs by the number of
    printable characters when searching for a given string
    """

    results = dict()

    # Run through all combinations of the messages
    for m1, m2 in combinations(glob('encrypted/*.hex'), 2):

        # Open the individual message files
        l1 = open(m1, 'r').read().splitlines()
        l2 = open(m2, 'r').read().splitlines()

        # The filename is a combination of the original message filenames
        filename = "%s-%s.xor" % (m1.split('.')[0], m2.split('.')[0])

        # XOR the two messages
        lx = xor(l1, l2)

        # Search for the string in the XOR of the two messages
        res = search(s, lx)

        # Find the ratio of printable and non-printable ASCII characters
        printable = len([x for y in res for x in y if x in string.printable])
        nonprint = len(
            [x for y in res for x in y if x not in string.printable])
        ratio = printable / nonprint

        # Store the results
        results[filename] = ratio

    return results

if __name__ == '__main__':
    """
    Generate a random 6-character string of lowercase values
    Print the results as a ranked list
    """
    results = rank_xors([choice(string.lowercase) for _ in range(6)])
    for k in sorted(results, key=results.get, reverse=True):
        print "%s - %f" % (k, results[k])
