#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Jul  5 10:51:45 2017

@author: aglick
"""
def PSD1(pulseData, pulseDataTraining):
    import csv
    import numpy as np
    import math
    photonTraining = 0
    neutronPhotonDiscriminator = 0
    i=0
    
    pulseDataTraining = csvOpening(pulseData)
        #map(int,photonTraining)
        #photonTraining1 = [int(x) for x in photonTraining]
        #reader = list(csv.DictReader(open(csvfile), delimiter='|'))
    numlines = len(open(pulseDataTraining).readlines())
        #numlines = len(csvfile.readlines())
    peakToTotalRatio = np.zeros((numlines,1))
    for row in neutronPhotonDiscriminator:
            #print(row)
        peakVal = findPeaks(row,30)  
            #print(peakVal)
        pulseIntegral = integratePulse(row,30)
            #print(pulseIntegral)
        peakToTotalRatio[i] = peakVal/pulseIntegral
        i=i+1
            #print(i)    
    n=0;
    m=0;
    
    for i in range(0,len(peaktoTotalRatio)):
        if peakToTotalRatio[i] < peakToTotalRatioTraining[i]:
            neutronInfo[n] = peakToTotalRatio[i]
            n+=n
        else:
            photonInfo[m] = peakToTotalRatio[i]
            m+=m
            
    return neutronInfo