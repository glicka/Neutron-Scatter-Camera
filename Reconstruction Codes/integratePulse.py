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
    for i in range(0,len(pulse)):
        if pulse[i]>thresh:
            pulseIntegral = pulseIntegral + pulse[i];
        
    return pulseIntegral;
        
        