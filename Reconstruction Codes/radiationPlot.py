#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Aug 28 20:22:07 2017

@author: aglick
"""

def radiationPlot(datafile):
    import h5py
    import numpy as np
    import matplotlib.pyplot as plt
    import pylab

#### Extract data here ####    
    f = h5py.File(datafile, 'r')
    adcBoardKey = list(f.keys())[0]
    adcBoardVals = f[adcBoardKey]
    adcBoardVals = np.array(adcBoardVals)
    adcChannelKey = list(f.keys())[1]
    adcChannel = f[adcChannelKey]
    adcChannel = np.array(adcChannel)
    groupTimeVals = list(f.keys())[5]
    timeVals = f[groupTimeVals]
    timeVals = np.array(timeVals)
    groupKeyVal = list(f.keys())[4]
    rawData = f[groupKeyVal]
    rawDataMat = np.array(rawData,dtype='float')
    detectorVal = []
    pulseIntegral = []
    i = 0
    for i in range(0,300000):
        if i%10000 == 0:
            print(i)
        elif i == 299999:
            print(i)
        row = rawDataMat[i,:]
        peakVal, peakTime = findPeaks(row)
        pulseIntegral = pulseIntegral + [integratePulse(row,peakTime)]
        #i = i + 1
        
    pulseIntegral = np.array(pulseIntegral)
    
    histNADC = np.histogram(pulseIntegral,100000)
    d1 = histNADC[0]
    e1 = histNADC[1]
    f1 = e1[0:100000]
    
    plt.figure(1)
    #plt.plot(a1,c1,'r',label='photons')
    plt.plot(f1,d1,'b--',label='ADC Plot')
    plt.xlabel('ADC Val')
    plt.ylabel('Counts')
    plt.legend(loc='upper right')
    #plt.plot(d,f)
    plt.show()
    
    return