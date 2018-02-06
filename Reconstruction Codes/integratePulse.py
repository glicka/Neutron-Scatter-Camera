#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu May  4 14:15:28 2017

@author: aglick
"""

def integratePulse(pulse,peakTime):
    import numpy as np;
    import scipy as sp;
    import math;
    pulseIntegral = 0;
    thresh = pulse[peakTime-5]
    lowerBound = int(round(len(pulse)/5))
    upperBound = int(round(3*len(pulse)/4))
    for i in range(lowerBound,upperBound):
        if pulse[i]>thresh:
            pulseIntegral += pulse[i];
        
    return pulseIntegral;
        
        