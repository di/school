import pickle

class Model :
    def __init__(self, **kwds) :
        self._dict = kwds

    @staticmethod
    def from_string(string) :
        return pickle.loads(string)

    def get(self, key) :
        return self._dict[key]

    def set(self, key, value) :
        self._dict[key] = value

    def __str__(self) :
        return pickle.dumps(self)
