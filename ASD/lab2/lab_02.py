import sys

def shortBubbleSort(arr):
    flag = True

    n = len(arr)
    for i in range(n):
        for j in range(n-i-1):
            if arr[j][1] > arr[j+1][1]:
                arr[j], arr[j+1] = arr[j+1].copy(), arr[j].copy()
                flag = False
        if flag:
            break

if len(sys.argv) < 3: raise Exception("Not enough command line arguments")

file_name = sys.argv[1]
user_num = int(sys.argv[2]) - 1

with open(file_name, "r") as f:
    data: [str] = f.readlines()

data.pop(0)

for i in range(len(data)):
    data[i] = [int(a)-1 for a in data[i].replace("\n", "").split(" ")[1:]]

def gen_arr(a, b):
    arr = []
    for _i in range(len(a)):
        arr.append(b[a[_i]])
    return arr

def join(a, b):
    r = []
    inv = 0
    _i = 0
    _j = 0

    while _i < len(a) and _j < len(b):
        if a[_i] > b[_j]:
            r.append(b[_j])
            _j += 1
            inv += len(a) - _i
        else:
            r.append(a[_i])
            _i += 1

    r.extend(a[_i:])
    r.extend(b[_j:])

    return r, inv

def merge_sort(arr):
    if len(arr) <= 1:
        return arr, 0

    mid = round(len(arr) / 2)

    _f, _s = arr[:mid], arr[mid:]

    f, calc_inv_f = merge_sort(_f)
    s, calc_inv_s = merge_sort(_s)

    e, calc_inv_e = join(f, s)

    return e, calc_inv_e + calc_inv_f + calc_inv_s

similarities = []

temp = True

easy_to_search = [0] * len(data[user_num])

for i, a in enumerate(data[user_num]): easy_to_search[a] = i

for i, d in enumerate(data):
    similarities.append([i, merge_sort(gen_arr(easy_to_search, d))[1]])

shortBubbleSort(similarities)

with open(".".join(sys.argv[0].split(".")[:-1]) + f"_output.txt", "w") as f:
    f.write(str(user_num+1)+"\n")

    for pos, sim in similarities:
        if pos == user_num: continue
        f.write(f"{pos+1} {sim}\n")

    f.write(str(user_num+1)+"\n")
