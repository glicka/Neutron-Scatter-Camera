#!/usr/bin/env python2
# -*- coding: utf-8 -*-
"""
Created on Tue Aug  1 09:26:06 2017

@author: aglick
"""

def integratePulse1(pulse,thresh):
    import numpy as np;
    import scipy as sp;
    import math;
    pulseIntegral = 0;
    cols = pulse.shape
    for i in range(0,cols[1]-1):
        if pulse[0,i]<thresh:
            pulseIntegral = pulseIntegral + pulse[0,i];
        
    return pulseIntegral;