#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu May  4 13:37:58 2017

@author: aglick
"""

def findPeaks(pulse, thresh):
    import numpy as np
    import scipy as sp

    peakVal = 0
    map(int, pulse)
    pulse1 = [int(x) for x in pulse]
    for i in range(0,len(pulse1)-1):


        if(pulse1[i]>thresh):
            if np.abs(pulse1[i]) < np.abs(pulse1[i+1]):
                peakVal = pulse1[i+1]
            else:
                peakVal = pulse1[i]
    
    return peakVal