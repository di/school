#!/usr/bin/python

from rank_xors import search
import string


def printable_string(s):
    """
    Return a boolean value if every character in the given string is in
    `string.printable`.
    """
    return len(s) == len([x for x in s if x in string.printable])


def common_string(s):
    """
    Return a boolean value if every character in the given string is in
    `string.letters` or has a couple common punctuation marks.
    """
    return len(s) == len([x for x in s if x in string.letters + " .,?;!"])

"""
First, let's open up the relevant files:
"""

xor = open('./xors/ct3-ct1.xor', 'r').read().splitlines()
common_words = open('common_words.txt', 'r').read().splitlines()
dict_words = open('/usr/share/dict/words', 'r').read().splitlines()

"""
Lets run through all the common words, and see if XOR-ing them in every
possible location of the XOR file results in any printable strings:
"""

for word in common_words:
    if len(word) > 2:
        print word
        for i, w in enumerate(search(' %s ' % (word), xor)):
            if common_string(w):
                print "\t%s (%d)" % (w, i)

"""
From this we see that the common word "make" results in a number of printable
strings:

make
    ca fgd (9)
    ,,li!h (10)
    hearts (15)
    esknti (24)
    n tong (42)
    ,hpxwe (57)
    e nego (65)
    tbe.wi (97)
     plcbe (115)

The word "hearts" looks pretty good. Let's see what we get when we search for
it surrounded in spaces (we need to subtract 1 from the index, too, since we're
adding a space to the beginning):
"""

print "'%s'" % (search(' hearts ', xor)[14])

"""
This results in:

    'd make i'

Let's go through our dictionary and see if we get anything good if we try
adding every word that starts with "i":
"""

test = [x for x in dict_words if x.startswith('i')]
for full in test:
    for i, x in enumerate(search('d make %s ' % (full), xor)):
        if i == 14 and printable_string(x):
            print "%d: %s%s%s" % (i, x.ljust(30), "d make ", full)

"""
This gives us a lot of output to pore through, but this line looks good:

14:
    hearts in love use           d make interesting

http://lmgtfy.com/?q=%22hearts+in+love+use%22

Looks like we have a hit. The next steps are finding the start, and then
tweaking the string so that both plaintexts make sense, until the length of
each is 128. We can use the search as we do this:
"""

s = "Therefore, all hearts in love use their own tongues;\nLet every eye negotiate for itself And trust no agent. William Shakespeare."
print search(s, xor)[0]

"""
This results in:

And now go, and make interesting mistakes, make amazing mistakes, make glorious and fantastic mistakes. Break rules Neil Gaiman.

And we're done!
"""
