def parent(a): return a//2
def left(a): return a*2
def right(a): return 2*a + 1

class Pyramid:
    def __init__(self, arr):
        self.pyramid = arr.copy()
        self.size = len(arr)

    def swap(self, a, b):
        self.pyramid[a], self.pyramid[b] = self.pyramid[b], self.pyramid[a]

    def str(self):
        a, c = 0, 1
        step = 2

        res = ""

        while a < self.size:
            res += str(self.pyramid[a]) + " "
            a += 1

            if a == c:
                res += "\n"

                c = c + step
                step = step * 2

        return res

    def append(self, item):
        self.pyramid.append(item)
        self.size = len(self.pyramid)
        self.Build()

    def pop(self, key):
        res = self.pyramid.pop(key)
        self.size = len(self.pyramid)
        self.Build()
        return res

    def Build(self): pass

    def __len__(self):
        return self.size

    def __getitem__(self, item):
        if item >= self.size: return None
        return self.pyramid[item]
    def __setitem__(self, key, value):
        self.pyramid[key] = value

    def __str__(self):
        return self.str()

    def __repr__(self):
        return str(self.pyramid)

class MaxHeap(Pyramid):
    def __init__(self, arr):
        super().__init__(arr)

        self.Build()

    def Heapify(self, i):
        p = left(i)
        q = right(i)

        if p < self.size and self.pyramid[p] > self.pyramid[i]:
            largest = p
        else:
            largest = i

        if q < self.size and self.pyramid[q] > self.pyramid[largest]:
            largest = q

        if largest != i:
            self.swap(largest, i)
            self.Heapify(largest)

    def Build(self):
        for i in list(range(self.size//2))[::-1]:
            self.Heapify(i)

    def append(self, item):
        self.size += 1
        self.pyramid.append(item)

        i = self.size - 1

        while i > 0 and self[parent(i)] < self[i]:
            self.swap(i, parent(i))
            i = parent(i)


class MinHeap(Pyramid):
    def __init__(self, arr):
        super().__init__(arr)

        self.Build()

    def Heapify(self, i):
        p = left(i)
        q = right(i)

        if p < self.size and self.pyramid[p] < self.pyramid[i]:
            largest = p
        else:
            largest = i

        if q < self.size and self.pyramid[q] < self.pyramid[largest]:
            largest = q

        if largest != i:
            self.swap(largest, i)
            self.Heapify(largest)

    def Build(self):
        for i in list(range(self.size//2))[::-1]:
            self.Heapify(i)

    def append(self, item):
        self.size += 1
        self.pyramid.append(item)

        i = self.size - 1

        while i > 0 and self[parent(i)] > self[i]:
            self.swap(i, parent(i))
            i = parent(i)

def Get_Median(Low, High):
    if len(Low) == len(High): return [Low[0], High[0]]
    if len(Low) < len(High): return [High[0]]
    if len(Low) > len(High): return [Low[0]]

def Analize_Medians(arr):
    res = []
    Hlow = MaxHeap([])
    Hhigh = MinHeap([])
    # arr = [8, 6, 5, 10, 1, 7, 2, 4, 9, 3]

    for _a in arr:
        if len(Hlow) == 0:
            Hlow.append(_a)
        else:
            if _a < Hlow[0]: Hlow.append(_a)
            else: Hhigh.append(_a)

        if abs(len(Hlow) - len(Hhigh)) > 1:
            while len(Hlow) - len(Hhigh) > 1:
                Hhigh.append(Hlow.pop(0))
            while len(Hhigh) - len(Hlow) > 1:
                Hlow.append(Hhigh.pop(0))

        res.append(Get_Median(Hlow, Hhigh))

    return res

if __name__ == "__main__":
    import sys

    meds = Analize_Medians(sys.argv[1:])

    str_meds = ""

    for r in meds:
        for mid in r: str_meds += f"{mid} "
        str_meds += '\n'

    str_meds = str_meds.replace(" \n", "\n")[:-1]

    with open(f"{sys.argv[0]}_out.txt", "w") as f_o:
        f_o.write(str_meds)
