#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu May  4 14:08:48 2017

@author: aglick
"""

def PSD(pulseData, pulseDataTraining):
    import csv
    import numpy as np
    import math
    import matplotlib.pyplot as plt
    import plotly.plotly as py
    photonTraining = 0
    neutronPhotonDiscriminator = 0
    #plt.scatter(x[0:70000],neutronInfo[0:70000],y[0:70000],photonInfo[0:70000])
    i = 0
    with open(pulseDataTraining,'r') as csvfile:
        photonTraining = csv.reader(csvfile)
        #map(int,photonTraining)
        #photonTraining1 = [int(x) for x in photonTraining]
        #reader = list(csv.DictReader(open(csvfile), delimiter='|'))
        numlines = len(open(pulseDataTraining).readlines())
        #numlines = len(csvfile.readlines())
        peakToTotalRatioTraining = np.zeros((numlines,1))
        for row in photonTraining:
            #print(row)
            peakVal = findPeaks(row,30)  
            #print(peakVal)
            pulseIntegral = integratePulse(row,30)
            #print(pulseIntegral)
            peakToTotalRatioTraining[i] = peakVal/pulseIntegral
            i=i+1
            #print(i)
        
    if photonTraining == 0:
        print("this is a string")
    
    i = 0
    with open(pulseData,'r') as csvfile1:
        neutronPhotonDiscriminator = csv.reader(csvfile1)
        #map(int,photonTraining)
        #photonTraining1 = [int(x) for x in photonTraining]
        #reader = list(csv.DictReader(open(csvfile), delimiter='|'))
        #numlines1 = len(open(neutronPhotonDiscriminator).readlines())
        numlines = len(open(pulseData).readlines())
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
            
    if neutronPhotonDiscriminator == 0:
        print("this is a string")
    
    n=0;
    m=0;
    neutronInfo = []
    photonInfo = []
    for i in range(0,len(peakToTotalRatio)):
        if peakToTotalRatio[i] < peakToTotalRatioTraining[i]:
            neutronInfo[n] = neutronInfo.append(peakToTotalRatio[i])
            n+=n
        else:
            photonInfo[m] = photonInfo.append(peakToTotalRatio[i])
            m+=m
    x = range(0,len(neutronInfo),1)
    y = range(0,len(photonInfo),1)
    neutronInfo = np.asarray(neutronInfo)
    photonInfo = np.asarray(photonInfo)
    x = np.asarray(x)
    y = np.asarray(y)
    plt.plot(x[0:70000],neutronInfo[0:70000],y[0:70000],photonInfo[0:70000])
    #plt.scatter(x[0:70000],neutronInfo[0:70000],y[0:70000],photonInfo[0:70000])
    return neutronInfo