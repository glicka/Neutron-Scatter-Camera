#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu May  4 13:37:58 2017

@author: aglick
"""

def findPeaks(pulse, thresh):
    import numpy as np
    import scipy as sp
    import matplotlib.pyplot as plt
    import pylab
    
    peakVal = 0
    peakTime = 0
    for i in range(0,len(pulse)-1):
        if pulse[i]>thresh:
            if np.abs(pulse[i]) < np.abs(pulse[i+1]) and peakVal < np.abs(pulse[i+1]):
                peakVal = pulse[i+1]
                peakTime = i
            elif peakVal < np.abs(pulse[i]):
                peakVal = pulse[i]
                peakTime = i
    
    return peakVal, peakTime