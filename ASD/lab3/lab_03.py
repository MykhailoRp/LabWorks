import sys

class MyArrClass:
    def __init__(self, inpt_arr):
        self.arr: list = inpt_arr.copy()
        self.comps = 0
        self.swaps = 0

    def swap(self, i, j):
        self.arr[i], self.arr[j] = self.arr[j], self.arr[i]
        self.swaps += 1

    def comp(self, a, b):
        self.comps += 1
        return a < b

    def __str__(self):
        return f"c:{self.comps} s:{self.swaps} : {self.arr.__str__()}"
    def __repr__(self):
        return f"c:{self.comps} s:{self.swaps} : {self.arr.__repr__()}"

    def __getitem__(self, item): return self.arr[item]

    def __setitem__(self, key, value): self.arr[key] = value

    def __len__(self): return len(self.arr)

def partition(A: MyArrClass, start_i, end_i, pivot):

    x = pivot
    i = start_i - 1
    j = start_i

    while j < end_i:
        if A.comp(A[j], x):
            i += 1
            A.swap(i, j)

        j += 1
    A.swap(i + 1, j)

    return i + 1

def insertionSort(A: MyArrClass, left, right):
    for i in range(left + 1, right + 1):
        key = A[i]

        j = i - 1
        while j >= left:
            if A.comp(key, A[j]):
                A.swaps+=1
                A[j + 1] = A[j]
                j -= 1
            else:
                break
        A.swaps += 1
        A[j + 1] = key

def QuickSortNorm(A: MyArrClass, p = 0, r = None):

    if r is None:
        r = len(A)-1

    if p < r:
        q = partition(A, p, r, A[r])
        QuickSortNorm(A, p, q - 1)
        QuickSortNorm(A, q + 1, r)

def QuickSortVar2(A, p = 0, r = None):

    if r is None:
        r = len(A)-1

    if p < r:
        if r - p > 2:
            elem_i = A.arr.index(sorted([A[p], A[(p + r) // 2], A[r]])[1])

            pivot = A[elem_i]

            A[elem_i], A[r] = A[r], A[elem_i]

            q = partition(A, p, r, pivot)

            QuickSortVar2(A, p, q - 1)
            QuickSortVar2(A, q + 1, r)
        else:
            insertionSort(A, p, r)

def partition3(A: MyArrClass, left, right):

    # print(f"beg: {left:5} {right:5} {A.__str__()}")

    a = left + 2
    b = left + 2
    c = right - 1
    d = right - 1

    left_elem = A[left]
    centre_elem = A[left+1]
    right_elem = A[right]

    while b <= c:
        A.comps = A.comps + 1
        while A[b] < centre_elem and b <= c:
            A.comps = A.comps + 1
            if A[b] < left_elem:
                A.swap(a, b)
                a = a + 1

            b = b + 1
            A.comps = A.comps + 1

        A.comps = A.comps + 1
        while A[c] > centre_elem and b <= c:
            A.comps = A.comps + 1
            if A[c] > right_elem:
                A.swap(c, d)
                d = d - 1

            c = c - 1
            A.comps = A.comps + 1

        if b <= c:
            A.comps = A.comps + 1
            if A[b] > right_elem:
                A.comps = A.comps + 1
                if A[c] < left_elem:
                    A.swap(b, a)
                    A.swap(a, c)
                    a = a + 1
                else:
                    A.swap(b, c)

                A.swap(c, d)
                b = b + 1
                c = c - 1
                d = d - 1
            else:
                A.comps = A.comps + 1
                if A[c] < left_elem:
                    A.swap(b, a)
                    A.swap(a ,c)
                    a = a + 1
                else:
                    A.swap(b, c)
                b = b + 1
                c = c - 1

    a = a - 1
    b = b - 1
    c = c + 1
    d = d + 1
    A.swap(left + 1, a)
    A.swap(a, b)

    a = a - 1

    A.swap(left, a)
    A.swap(right, d)

    # print(f"end: {a:2} {b:2} {c:2} {d:2} {A.__str__()}", left_elem, centre_elem, right_elem)

    return A.arr.index(left_elem), A.arr.index(centre_elem), A.arr.index(right_elem)


def QuickSortVar3(A: MyArrClass, p = 0, r = None):

    if r is None:
        r = len(A)-1

    if p < r:
        if r - p > 2:

            mas = [A[p], A[p+1], A[r]]

            A[p] = min(mas)
            A[p + 1] = sorted(mas)[1]
            A[r] = max(mas)

            a, b, c = partition3(A, p, r)
            QuickSortVar3(A, p, a - 1)
            QuickSortVar3(A, a + 1, b - 1)
            QuickSortVar3(A, b + 1, c - 1)
            QuickSortVar3(A, c + 1, r)
        else:
            insertionSort(A, p, r)

if __name__ == "__main__":
    file_name = sys.argv[1]

    with open(file_name, "r") as f:
        data: [str] = f.readlines()

    arr = [int(a) for a in data[1:]]

    arr1 = MyArrClass(arr)
    arr2 = MyArrClass(arr)
    arr3 = MyArrClass(arr)

    QuickSortNorm(arr1)

    QuickSortVar2(arr2)

    QuickSortVar3(arr3)

    with open(".".join(sys.argv[0].split(".")[:-1]) + f"_output.txt", "w") as f:
        f.write(f"{arr1.comps} {arr2.comps} {arr3.comps}")
