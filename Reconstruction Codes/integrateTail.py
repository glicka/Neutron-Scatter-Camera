#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Aug 22 11:03:01 2017

@author: aglick
"""

def integrateTail(pulse,peakTime):
    import numpy as np;
    import scipy as sp;
    import math;
    tailIntegral = 0;
    thresh = pulse[peakTime-5]
    lowerBound = int(round(len(pulse)/5))
    upperBound = int(round(3*len(pulse)/4))
    for i in range(lowerBound,upperBound):
        if pulse[i]>thresh and i>peakTime+3:
            tailIntegral += pulse[i];
        
    return tailIntegral;