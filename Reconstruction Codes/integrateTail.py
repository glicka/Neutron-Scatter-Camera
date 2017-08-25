#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Aug 22 11:03:01 2017

@author: aglick
"""

def integrateTail(pulse,thresh,peakTime):
    import numpy as np;
    import scipy as sp;
    import math;
    tailIntegral = 0;
    map(int, pulse)
    pulse1 = [int(x) for x in pulse]
    for i in range(0,len(pulse1)-1):
        if pulse1[i]<thresh and i>peakTime+8:
            tailIntegral = tailIntegral + pulse1[i];
        
    return tailIntegral;