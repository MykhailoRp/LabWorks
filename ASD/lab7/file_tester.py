import lab_07 as lab
from tqdm import tqdm

import os

inpts = "inputs"
outps = "outputs"
outps2 = "my_outputs"

wrongs = 0

for f_name in os.listdir(inpts):

    with open(os.path.join(inpts, f_name), "r") as f:
        data = f.readline()

    arr = list(map(int, data.split()))

    root = lab.build_from_arr(arr)

    res = lab.parce_order(lab.inorder(root))

    res.sort()

    print(res)

    new_res = res[len(res) - res[::-1].index(0):]

    lab.fillin(root, new_res)

    chains = lab.calculate(lab.preorder(root), 9)

    for a in chains:
        while 0 in a:
            a.remove(0)

    str_meds = "\n".join([" ".join(list(map(str, a))) for a in chains])

    with open(os.path.join(outps, "_".join(["output", *f_name.split("_")[1:]])), "r") as f_o:
        right = "".join(f_o.readlines())

    with open(os.path.join(outps2, "_".join(["output", *f_name.split("_")[1:]])), "w") as f_o_m:
        f_o_m.write(str_meds)

    # print(f_name, right == str_meds)
    #
    # if right != str_meds: wrongs+=1

print(wrongs)
