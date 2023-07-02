import lab_03 as lab
from tqdm import tqdm

import os

inpts = "inputs"
outps = "outputs"
outps2 = "my_outputs"

wrongs = 0

for f_name in os.listdir(inpts):

    with open(os.path.join(inpts, f_name), "r") as f:
        data: [str] = f.readlines()

    arr = [int(a) for a in data[1:]]

    arr1 = lab.MyArrClass(arr)
    arr2 = lab.MyArrClass(arr)
    arr3 = lab.MyArrClass(arr)

    lab.QuickSortNorm(arr1)

    lab.QuickSortVar2(arr2)

    lab.QuickSortVar3(arr3)

    with open(os.path.join(outps, "_".join(["output", *f_name.split("_")[1:]])), "r") as f_o:
        res1, res2, res3 = [int(a) for a in f_o.readline().split(" ")]

    with open(os.path.join(outps2, "_".join(["output", *f_name.split("_")[1:]])), "w") as f_o_m:
        f_o_m.write(f"{arr1.comps} {arr2.comps} {arr3.comps}")

    print(f_name, arr1.comps == res1, arr2.comps == res2, arr3.comps == res3)

    if arr1.comps != res1: wrongs+=1
    if arr2.comps != res2: wrongs+=1
    if arr3.comps != res3: wrongs+=1

print(wrongs)
