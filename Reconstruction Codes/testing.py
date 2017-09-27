#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Aug 22 11:10:23 2017

@author: aglick
"""

#testing script

import csv
import numpy as np
import math
import matplotlib.pyplot as plt
    #import plotly as py
import pylab
import time
tic = time.time()
photonData = []
with open('NE204-09-21-2011-Cs137-LS-Signal.csv','r') as csvfile:
    temp = csv.reader(csvfile)
    for row in temp:
        photonData += [row]


photonData = np.array(photonData,dtype = 'float')
#PSD1('NE204-09-21-2011-PuBe-LSC-Signal.csv','NE204-09-21-2011-Cs137-LS-Signal.csv')
dataProcessingNoExtClock('D09-11-2017T16-23-58.h5',photonData,tic)
#radiationPlot('Data-Cs137-08-04-2017-Run1.h5')
toc = time.time()
print('tictoc = ',toc-tic)