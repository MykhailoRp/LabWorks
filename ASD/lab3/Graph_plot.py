import lab_03 as lab
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from tqdm import tqdm

import random
import pickle

open_f = input("y/n ->")

if open_f == 'y':
    results = {}

    for A in tqdm([list(range(0, a)) for a in range(0, 20000, 10)]):
        random.shuffle(A)
        arr1 = lab.MyArrClass(A.copy())
        arr2 = lab.MyArrClass(A.copy())
        arr3 = lab.MyArrClass(A.copy())

        lab.QuickSortNorm(arr1)
        lab.QuickSortVar2(arr2)
        lab.QuickSortVar3(arr3)

        results[len(A)] = {
            "Norm":arr1.comps,# + arr1.swaps,
            "Second":arr2.comps,# + arr2.swaps,
            "Third":arr3.comps,# + arr3.swaps,
        }

    with open(r"E:\PythonProjects\asd_2\lab3\save.pkl", "wb") as f:
        pickle.dump(results, f)
else:
    with open(r"E:\PythonProjects\asd_2\lab3\save.pkl", "rb") as f:
        results = pickle.load(f)

# x = list(results.keys())
# y = {a: {b: results[b][a]} for a in ["Norm", "Second", "Third"] for b in results}
# y =

def ExtractType(d: dict, t):
    res = []
    for v in list(d.values()):
        res.append(v[t])

    return res

def ExtractVals(d: dict):
    res = []
    for v in list(d.values()):
        res.append(list(v.values()))

    return res

# all_res = pd.DataFrame({"Sorting types": {"Norm":ExtractType(results, "Norm"), "Second":ExtractType(results, "Second"), "Third":ExtractType(results, "Third")}}, index=list(results.keys()))
# all_res = pd.DataFrame(results).T
all_res = pd.DataFrame({
    "Arr size": list(results.keys()),
    "Norm": ExtractType(results, "Norm"),
    "Second": ExtractType(results, "Second"),
    "Third": ExtractType(results, "Third"),
})

# [a, b], res1 = curve_fit(lambda x1, a, b: a * np.exp(b * x1), x, y)
#
# print(b)
# print(x)
#
# y1 = a * np.exp(x)

# plt.plot(x, y, 'b')
# plt.plot(x, y1, 'r')


import seaborn as sns


# sns.lmplot(
#     x='Arr size', y='value', hue='variable',
#     data=pd.melt(all_res, ['Arr size']), #[["Norm", "Second", "Third"]]
#     palette=['cyan', 'magenta', 'green'],
#     scatter_kws={"s": 1}
# )
sns.lineplot(
    x='Arr size', y='value', hue='variable',
    data=pd.melt(all_res, ['Arr size']), #[["Norm", "Second", "Third"]]
    palette=['blue', 'red', 'yellow']
)

plt.show()
