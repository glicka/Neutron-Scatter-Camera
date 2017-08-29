#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu May  4 13:37:58 2017

@author: aglick
"""

def findPeaks(pulse):
    import numpy as np
    import scipy as sp
    import matplotlib.pyplot as plt
    import pylab
    thresh = 55
    peakVal = 0
    peakTime = 0
    lowerBound = int(round(len(pulse)/5))
    upperBound = int(round(3*len(pulse)/4))
    for i in range(lowerBound,upperBound):
        if pulse[i]>thresh:
            if np.abs(pulse[i]) < np.abs(pulse[i+1]) and peakVal < np.abs(pulse[i+1]):
                peakVal = pulse[i+1]
                peakTime = i
            elif peakVal < np.abs(pulse[i]):
                peakVal = pulse[i]
                peakTime = i
    
    return peakVal, peakTime