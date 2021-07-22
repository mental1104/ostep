#!/usr/bin/env python3

import matplotlib.pyplot as plt
import numpy as np

traditional = [0.015263, 0.030379, 0.046761, 0.061528, 0.077000, 0.091352]
approximate = [0.033200, 0.274310, 0.361561, 0.598504, 0.735033, 0.952322]

a = np.arange(0, 6)


plt.plot(a, traditional, marker='x')
plt.plot(a, approximate, marker='x')
plt.margins(0)
#plt.xticks(a, s)
plt.xlabel('Threads')
plt.ylabel('Time (seconds)')
plt.legend(['Precise', 'Approximate'])
plt.savefig('simple.png', dpi=300)
plt.show()