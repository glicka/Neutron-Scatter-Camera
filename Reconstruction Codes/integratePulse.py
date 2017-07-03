#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu May  4 14:15:28 2017

@author: aglick
"""

def integratePulse(pulse,thresh):
    import numpy as np;
    import scipy as sp;
    import math;
    pulseIntegral = 0;
    map(int, pulse)
    pulse1 = [int(x) for x in pulse]
    for i in range(0,len(pulse1)-1):
        if pulse1[i]>thresh:
            pulseIntegral = pulseIntegral + pulse1[i];
        
    return pulseIntegral;
        
        