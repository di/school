#!/usr/bin/python
from __future__ import division
import json
import random
import hashlib
import requests
from bs4 import BeautifulSoup as bs


leet = {'l': 1, 'z': 2, 'e': 3, 'a': 4, 's': 5, 'b': 6, 't': 7, 'g': 9}


def pref_1(x):
    '''
    Preference based on the popularity. In the case of a tie, chooses a
    male-gendered agent.
    '''
    return -x.popularity, x.gender


def pref_2(x):
    '''
    Preference based on the total sum of the ASCII values of the characters in
    the name, averaged over the length of the name. Greater sum equates to
    greater preference. In the case of a tie, chooses the result from the
    previous preference.
    '''
    return sum([ord(c) for c in x.name])/len(x.name), pref_1(x)


def pref_3(x):
    '''
    Preference based on the integer value of the MD5 hash of the name. A higher
    integer value equates to greater preference. In the case of a tie, chooses
    the result from the previous preference.
    '''
    return int(hashlib.md5(x.name).hexdigest(), 16), pref_2(x)


def pref_4(x):
    '''
    Preference based on the sum of all integer values when the name is
    converted into 1337-5p34k. A higher sum equates to greater preference. In
    the case of a tie, chooses the result from the previous preference.
    '''
    return sum(map(lambda x: leet.get(x, 0), x.name.lower())), pref_3(x)


def pref_5(x):
    '''
    Preference based on the number of Google Search Results for a given name. A
    higher number of results equates to greater preference. In the case of a
    tie, chooses the result from the previous preference.
    '''
    return x.google_results, pref_4(x)


class Agent():

    def __init__(self, name, popularity, gender, google_results):
        self.name = name
        self.popularity = popularity
        self.gender = gender
        self.google_results = google_results
        self.preference = random.choice(
            [pref_1,
             pref_2,
             pref_3,
             pref_4,
             pref_5])

    def __repr__(self):
        return self.name

    def vote(self, agents):
        return list(reversed(sorted(agents, key=self.preference)))


def plurality(votes):
    first = [v[0] for v in votes]
    count = {x: first.count(x) for x in first}
    return max(count, key=lambda x: count[x])


def borda(votes):
    count = {}
    for vote in [zip(v, reversed(range(0, len(v)))) for v in votes]:
        for candidate, score in vote:
            try:
                count[candidate] += score
            except KeyError:
                count[candidate] = score
    return max(count, key=lambda x: count[x])


def pairwise(votes):
    preferred = [v[0] for v in votes]
    count = {x: preferred.count(x) for x in preferred}
    return max(count, key=lambda x: count[x])


def doge(agents):

    def choose(a, n):
        xxx = {}
        for bar in [agent.vote(agents)[:n] for agent in nine]:
            d = {x: bar.count(x) for x in bar}
            for k in d.keys():
                try:
                    xxx[k] += d[k]
                except:
                    xxx[k] = d[k]
        return sorted(xxx, key=lambda x: xxx[x])[:n]

    thirty = random.sample(agents, 30)
    nine = random.sample(thirty, 9)
    forty = choose(nine, 40)
    twelve = random.sample(forty, 12)
    twentyfive = choose(twelve, 25)
    nine = random.sample(twentyfive, 9)
    fortyfive = choose(nine, 45)
    eleven = random.sample(fortyfive, 11)
    fortyone = choose(eleven, 41)
    doge = choose(fortyone, 1).pop()
    return doge


agents = [Agent(**x) for x in json.load(open('names.json'))['agents']]
votes = [agent.vote(agents) for agent in agents]

print "Plurality result: %s" % plurality(votes)
print "Borda result: %s" % borda(votes)
print "Pairwise result: %s" % pairwise(votes)
print "Doge result: %s" % doge(agents)
