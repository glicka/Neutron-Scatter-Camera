#!/usr/bin/env python2
# -*- coding: utf-8 -*-
"""
Created on Tue Aug  1 09:24:10 2017

@author: aglick
"""

def findPeaks1(pulse, thresh):
    import numpy as np
    import scipy as sp
    peakVal = 0
    cols = pulse.shape
    for i in range(0,cols[1]-1):
        if(pulse[0,i]>thresh):
            if np.abs(pulse[0,i]) < np.abs(pulse[0,i+1]):
                peakVal = pulse[0,i+1]
            else:
                peakVal = pulse[0,i]
                
    return peakVal