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
    for i in range(0,len(pulse)):
        if pulse[i]>thresh and i>peakTime+3:
            tailIntegral = tailIntegral + pulse[i];
        
    return tailIntegral;