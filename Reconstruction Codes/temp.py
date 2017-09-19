#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Aug 30 07:33:21 2017

@author: aglick
"""

import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
x = np.arange(-50.0, 50, 1)
y = np.arange(-50.0, 50, 1)
X, Y = np.meshgrid(x, y)
print('X = ',X)
print('Y = ',Y)
Z = (-4823.7 + np.sqrt(abs((4823.7 ** 2) - (4 * (-240.185) * ((-5692 * Y) - (240.185 * np.multiply(X, X))
                                                              - (240.185 * np.multiply(Y, Y)) - 57607.26)))) / np.float(
    2 * (-240.185)))

ax.plot_surface(X, Y, Z)

ax.set_xlabel('X Label')
ax.set_ylabel('Y Label')
ax.set_zlabel('Z Label')
plt.show()