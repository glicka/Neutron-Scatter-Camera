#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Aug 23 11:39:10 2017

@author: aglick
"""

import csv
import numpy as np
import math
import matplotlib.pyplot as plt
    #import plotly as py
import pylab

import matplotlib.pyplot as plt
import pandas as pd
data = pd.read_csv('neutron.csv', quoting=2)
data1 = pd.read_csv('photon.csv', quoting=2)
data = data.hist(bins=10000)
data1 = data1.hist(bins=10000)
plt.xlim([0,1])
plt.title("Data")
plt.xlabel("Value")
plt.ylabel("Frequency")
plt.show()