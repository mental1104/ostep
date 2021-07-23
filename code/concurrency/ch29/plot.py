#!/usr/bin/env python3

import matplotlib.pyplot as plt
import numpy as np

#traditional = [0.015263, 0.030379, 0.046761, 0.061528, 0.077000, 0.091352]
approximate = [5.814809,14.298914, 23.459987, 35.435726, 56.374765, 75.094495, 88.125039, 104.881222, 122.401781, 109.825442 ]

a = np.arange(1, 11)


#plt.plot(a, traditional, marker='x')
plt.plot(a, approximate, marker='x')
plt.margins(0)
#plt.xticks(a, s)
plt.xlabel('Threads')
plt.ylabel('Time (seconds)')
plt.legend(['Btree'])
plt.savefig('btree.png', dpi=300)
plt.show()