'''
Метод Хеш-функції (Хешування MurmurHash2а),
вирішення колізій методом відкритої адресації з подвійним хешуванням
'''
import random
import string


def mmix(h, k, r):
    k *= 0x5bd1e995
    k ^= k >> r
    k *= 0x5bd1e995
    h *= 0x5bd1e995
    h ^= k
    return h, k

def MurmurHash2A(_key, _length, _seed):
    m = 0x5bd1e995
    r = 24
    l = _length
    data = bytearray(_key, 'utf-8')

    h = _seed

    while _length >= 4:
        k = int.from_bytes(data[:4], byteorder='little')

        h, k = mmix(h, k, r)

        data = data[4:]
        _length -= 4

    t = 0

    if _length >= 3:
        t ^= data[2] << 16
    if _length >= 2:
        t ^= data[1] << 8
    if _length >= 1:
        t ^= data[0]

    h, t = mmix(h, t, r)
    h, l = mmix(h, l, r)

    h ^= h >> 13
    h *= m
    h ^= h >> 15

    return h

class dict_element:
    def __init__(self, key, value):
        self.key = None
        self.value = None
        self.deleted = False

    def set(self, key, value):
        self.key = key
        self.value = value
        self.deleted = False

    def de(self):
        self.key = None
        self.value = None
        self.deleted = True

    def __copy__(self):
        return dict_element(self.key, self.value)

    def __str__(self): return self.value.__str__()
    def __repr__(self): return f"{self.value}; {self.deleted}"

class my_dict:
    def __init__(self, size, seed1 = 0, seed2 = 0, seed3 = 0):
        self.size = size * 50

        self._arr: [dict_element] = [dict_element(None, None) for _ in range(self.size)]

        self._seed1 = seed1
        self._seed2 = seed2

        self.comp = 0

        while self._seed1 == self._seed2:
            self._seed1 = random.randint(0, 100000)
            self._seed2 = random.randint(0, 100000)

    def _hash(self, _key, _i, k = 0):

        hash1 = MurmurHash2A(_key, len(_key), self._seed1)
        hash2 = MurmurHash2A(_key, len(_key), self._seed2)
        res_hash = hash1 + _i * (3 + k + hash2)

        return (res_hash) % self.size

    def __getitem__(self, key, k = 0):

        self.comp = 0

        _i = 0

        loop_check = None
        offset = 0

        elem: dict_element = dict_element(None, None)
        elem.deleted = True

        while _i != self.size:
            j = (self._hash(key, _i, k) + offset) % self.size

            if j == loop_check:
                offset = _i
                j = (self._hash(key, _i, k) + offset) % self.size
                loop_check = j

            if loop_check is None: loop_check = j

            elem = self._arr[j]

            self.comp += 1

            if elem.key == key and not elem.deleted: return elem.value

            _i += 1

        if k >= 100: raise IndexError(f"Failed to find {key} {self._seed1} {self._seed2}")

        self.__setitem__(key, k + 1)
        return

    def __setitem__(self, key, value, k = 0, comps = 0):
        self.comp = comps
        _i = 0

        loop_check = None
        offset = 0

        elem: dict_element = dict_element(None, None)
        elem.deleted = True

        while _i != self.size:
            j = (self._hash(key, _i, k) + offset) % self.size

            if j == loop_check:
                offset = _i
                j = (self._hash(key, _i, k) + offset) % self.size
                loop_check = j

            if loop_check is None: loop_check = j

            elem = self._arr[j]

            self.comp += 1

            if elem.key is None or elem.deleted or elem.key == key:
                elem.set(key, value)
                return

            _i += 1

        if k >= 100: raise Exception(f"Failed to find spot for {key} {self._seed1} {self._seed2}")

        self.__setitem__(key, value, k + 1, self.comp)
        return

    def get_seeds(self):
        print(f"{self._seed1}, {self._seed2}")

    def print(self):
        for a in self._arr:
            if a.key is not None:
                print(f"| {a.key} | {a.value} |")

    def __str__(self):
        res = "{" + ", ".join([f"{a.key} : {a.value}" for a in self._arr]) + "}"
        return res
    def __repr__(self):
        res = "{" + ", ".join([f"{a.key} : {a.value}" for a in self._arr]) + "}"
        return res

def generate_random_string(length):
    letters = string.ascii_letters
    random_string = ''.join(random.choice(letters) for _ in range(length))
    return random_string

if __name__ == "__main__":
    arr_size = int(input("Array size -> "))

    test_key, test_val = input("Input test key and test value (key value) -> ").split()

    new_dict = my_dict(arr_size)

    for i in range(arr_size - 1):
        new_dict[generate_random_string(20)] = generate_random_string(200)

    new_dict[test_key] = test_val

    new_dict.print()

    print(f"Retrieving {test_key} from dict ->", new_dict[test_key])

    input_key = input("Test retrieve key -> ")

    print(f"Retrieving {input_key} from dict ->", new_dict[input_key])
    print(f"Comparisons: {new_dict.comp}")
