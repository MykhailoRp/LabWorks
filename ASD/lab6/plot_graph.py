import lab_06 as lab
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from tqdm import tqdm

import random
import pickle

size_start, size_end, size_step = map(int, input("size_start size_end size_step -> ").split())

results = {}

for A in tqdm(range(size_start, size_end, size_step)):

    new_dict = lab.my_dict(A)

    for a in range(A-1):
        new_dict[lab.generate_random_string(20)] = lab.generate_random_string(200)

    new_dict["test"] = "test2"
    temp = new_dict["test"]

    results[A] = new_dict.comp

with open(r"E:\PythonProjects\asd_2\lab3\save.pkl", "wb") as f:
    pickle.dump(results, f)

plt.plot(list(results.keys()), list(results.values()))

plt.show()
