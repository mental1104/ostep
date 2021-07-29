#! /usr/bin/env python3

import random

import matplotlib.pyplot as plt
import numpy as np

asize = 4096
psize = 16 * 1024
uList = [0] * psize

for i in range(4096):
    random.seed(i)
    for j in range(psize):
        limit = j
        vaddr = int(asize * random.random())
        if (vaddr < limit):
            uList[j] += 1

fig = plt.figure()
x = np.linspace(1, psize, psize)
plt.plot(x, [u / 4096 for u in uList], color='orange')
plt.ylim(0, 1)
plt.xlim(0, 4096)
plt.margins(0)
plt.xlabel('Limit')
plt.ylabel('Valid fraction (Average)')
plt.savefig('valid_fraction.png', dpi=227)
plt.show()