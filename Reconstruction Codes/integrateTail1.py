#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Aug 22 15:58:50 2017

@author: aglick
"""

def integrateTail1(pulse,thresh,peakTime):
    import numpy as np;
    import scipy as sp;
    import math;
    tailIntegral = 0;
    cols = pulse.shape
    for i in range(0,cols[1]-1):
        if pulse[i]<thresh and i>peakTime+3:
            tailIntegral = tailIntegral + pulse[i];
        
    return tailIntegral;