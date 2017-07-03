#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu May  4 14:08:48 2017

@author: aglick
"""

def PSD(pulseData, pulseDataTraining):
    import csv;
    import numpy as np;
    import math
    photonTraining = 0; 
    print("this is a string")
    with open(pulseDataTraining,'rb') as csvfile:
        photonTraining = csv.reader(csvfile);
        #print(photonTraining)
        for row in photonTraining:
            findPeaks(photonTraining[row],-30)  
    print("string part 2")
    if photonTraining == 0:
        print("this is a string")
        
    return np.max(photonTraining)