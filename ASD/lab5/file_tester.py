import lab_05 as lab
from tqdm import tqdm

import os

inpts = "inputs"
outps = "outputs"
outps2 = "my_outputs"

wrongs = 0

for f_name in os.listdir(inpts):

    with open(os.path.join(inpts, f_name), "r") as f:
        data: [str] = f.readlines()

    arr = map(int, data[1:])

    medians = lab.Analize_Medians(arr)

    str_meds = ""

    for r in medians:
        for mid in r: str_meds += f"{mid} "
        str_meds+='\n'

    str_meds = str_meds.replace(" \n", "\n")[:-1]

    with open(os.path.join(outps, "_".join(["output", *f_name.split("_")[1:]])), "r") as f_o:
        right = "".join(f_o.readlines())

    with open(os.path.join(outps2, "_".join(["output", *f_name.split("_")[1:]])), "w") as f_o_m:
        f_o_m.write(str_meds)

    print(f_name, right == str_meds)

    if right != str_meds: wrongs+=1

print(wrongs)
