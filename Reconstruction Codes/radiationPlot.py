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
    plane1Data = []
    plane1Times = []
    plane1Dets =[]
    plane2Data = []
    plane2Times = []
    plane2Dets =[]
    i = 0
#    for row in rawDataMat:
#        if i%100000 == 0:
#            print(i)
#        peakTime = row.argmax()
#        pulseIntegral += [integratePulse(row,peakTime)]
#        i = i + 1
    
    for i in range(0,len(adcBoardVals)):#10000):
#        tic = time.time()
        if i%100000 ==0:
            print(i)
        if adcBoardVals[i] == 5:
            if adcChannel[i] == 0:
                detectorVal += [0]
                plane1Data += [rawDataMat[i,:]]
                plane1Times += [timeVals[i]]
                plane1Dets += [0]
            elif adcChannel[i] == 1:
                detectorVal += [1]
                plane1Data += [rawDataMat[i,:]]
                plane1Times += [timeVals[i]]
                plane1Dets += [1]
            elif adcChannel[i] == 2:
                detectorVal += [2]
                plane1Data += [rawDataMat[i,:]]
                plane1Times += [timeVals[i]]
                plane1Dets += [2]
            elif adcChannel[i] == 3:
                detectorVal += [3]
                plane1Data += [rawDataMat[i,:]]
                plane1Times += [timeVals[i]]
                plane1Dets += [3]
            elif adcChannel[i] == 4:
                detectorVal += [4]
                plane1Data += [rawDataMat[i,:]]
                plane1Times += [timeVals[i]]
                plane1Dets += [4]
            elif adcChannel[i] == 5:
                detectorVal += [5]
                plane1Data += [rawDataMat[i,:]]
                plane1Times += [timeVals[i]]
                plane1Dets += [5]
            elif adcChannel[i] == 6:
                detectorVal += [6]
                plane1Data += [rawDataMat[i,:]]
                plane1Times += [timeVals[i]]
                plane1Dets += [6]
            elif adcChannel[i] == 7:
                detectorVal += [7]
                plane1Data += [rawDataMat[i,:]]
                plane1Times += [timeVals[i]]
                plane1Dets += [7]
        elif adcBoardVals[i] == 7:
            if adcChannel[i] == 0:
                detectorVal += [16]
                plane2Data += [rawDataMat[i,:]]
                plane2Times += [timeVals[i]]
                plane2Dets += [16]
            elif adcChannel[i] == 1:
                detectorVal += [17]
                plane2Data += [rawDataMat[i,:]]
                plane2Times += [timeVals[i]]
                plane2Dets += [17]
            elif adcChannel[i] == 2:
                detectorVal += [18]
                plane2Data += [rawDataMat[i,:]]
                plane2Times += [timeVals[i]]
                plane2Dets += [18]
            elif adcChannel[i] == 3:
                detectorVal += [19]
                plane2Data += [rawDataMat[i,:]]
                plane2Times += [timeVals[i]]
                plane2Dets += [19]
            elif adcChannel[i] == 4:
                detectorVal += [20]
                plane2Data += [rawDataMat[i,:]]
                plane2Times += [timeVals[i]]
                plane2Dets += [20]
            elif adcChannel[i] == 5:
                detectorVal += [21]
                plane2Data += [rawDataMat[i,:]]
                plane2Times += [timeVals[i]]
                plane2Dets += [21]
            elif adcChannel[i] == 6:
                detectorVal += [22]
                plane2Data += [rawDataMat[i,:]]
                plane2Times += [timeVals[i]]
                plane2Dets += [22]
            elif adcChannel[i] == 7:
                detectorVal += [23]
                plane2Data += [rawDataMat[i,:]]
                plane2Times += [timeVals[i]]
                plane2Dets += [23]
        elif adcBoardVals[i] == 6:
            if adcChannel[i] == 0:
                detectorVal += [8]
                plane1Data += [rawDataMat[i,:]]
                plane1Times += [timeVals[i]]
                plane1Dets += [8]
            elif adcChannel[i] == 1:
                detectorVal += [9]
                plane1Data += [rawDataMat[i,:]]
                plane1Times += [timeVals[i]]
                plane1Dets += [9]
            elif adcChannel[i] == 2:
                detectorVal += [10]
                plane1Data += [rawDataMat[i,:]]
                plane1Times += [timeVals[i]]
                plane1Dets += [10]
            elif adcChannel[i] == 3:
                detectorVal += [11]
                plane1Data += [rawDataMat[i,:]]
                plane1Times += [timeVals[i]]
                plane1Dets += [11]
            elif adcChannel[i] == 4:
                detectorVal += [12]
                plane2Data += [rawDataMat[i,:]]
                plane2Times += [timeVals[i]]
                plane2Dets += [12]
            elif adcChannel[i] == 5:
                detectorVal += [13]
                plane2Data += [rawDataMat[i,:]]
                plane2Times += [timeVals[i]]
                plane2Dets += [13]
            elif adcChannel[i] == 6:
                detectorVal += [14]
                plane2Data += [rawDataMat[i,:]]
                plane2Times += [timeVals[i]]
                plane2Dets += [14]
            elif adcChannel[i] == 7:
                detectorVal += [15]
                plane2Data += [rawDataMat[i,:]]
                plane2Times += [timeVals[i]]
                plane2Dets += [15]
    
    detectorVal = np.array(detectorVal)
    pulseIntegral = np.array(pulseIntegral)
    neutronDets, neutronTimes, neutronADC = PSD(detectorVal,timeVals,rawDataMat)
    
    histNADC = np.histogram(neutronADC,100000)
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