#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Jul 31 15:09:28 2017

@author: aglick
"""

def dataProcessing(datafile):
    import h5py
    import numpy as np
    import matplotlib.pyplot as plt
    import pylab

#### Extract data here ####    
    f = h5py.File(datafile, 'r')
    #print(f)
    #print("Keys: %s" % f.keys())
    groupKeyVal = f.keys()[4]
    groupDetectorVal = f.keys()[2]
    adcBoardKey = f.keys()[0]
    adcBoardVals = list(f[adcKeyVal])
    adcChannelKey = f.keys()[1]
    adcChannel = list(f[adcChannelKey])
    detectorVals = list(f[groupDetectorVal])
    groupTimeVals = f.keys()[5]
    timeVals = list(f[groupTimeVals])
    rawData = list(f[groupKeyVal])
    
    rawDataMat = np.matrix(rawData)
    temp = 0
    temp1 = 0
    detectorVal = []
    
#### Break up detectors into 1-24 based on adcChannel and adcBoard values ####    
    for i in range(0,len(adcBoardVals)):
        if adcBoardVals[i] == 5:
            temp = temp+1
            if adcChannel[i] == 0:
                detectorVal = detectorVal + [1]
            elif adcChannel[i] == 1:
                detectorVal = detectorVal + [2]
            elif adcChannel[i] == 2:
                detectorVal = detectorVal + [3]
            elif adcChannel[i] == 3:
                detectorVal = detectorVal + [4]
            elif adcChannel[i] == 4:
                detectorVal = detectorVal + [5]
            elif adcChannel[i] == 5:
                detectorVal = detectorVal + [6]
            elif adcChannel[i] == 6:
                detectorVal = detectorVal + [7]
            elif adcChannel[i] == 7:
                detectorVal = detectorVal + [8]
        elif adcBoardVals[i] == 7:
            temp1 = temp1+1
            if adcChannel[i] == 0:
                detectorVal = detectorVal + [17]
            elif adcChannel[i] == 1:
                detectorVal = detectorVal + [18]
            elif adcChannel[i] == 2:
                detectorVal = detectorVal + [19]
            elif adcChannel[i] == 3:
                detectorVal = detectorVal + [20]
            elif adcChannel[i] == 4:
                detectorVal = detectorVal + [21]
            elif adcChannel[i] == 5:
                detectorVal = detectorVal + [22]
            elif adcChannel[i] == 6:
                detectorVal = detectorVal + [23]
            elif adcChannel[i] == 7:
                detectorVal = detectorVal + [24]
        elif adcBoardVals[i] == 6:
            if adcChannel[i] == 0:
                detectorVal = detectorVal + [9]
                temp = temp+1
            elif adcChannel[i] == 1:
                detectorVal = detectorVal + [10]
                temp = temp+1
            elif adcChannel[i] == 2:
                detectorVal = detectorVal + [11]
                temp = temp+1
            elif adcChannel[i] == 3:
                detectorVal = detectorVal + [12]
                temp = temp+1
            elif adcChannel[i] == 4:
                detectorVal = detectorVal + [13]
                temp1 = temp1+1
            elif adcChannel[i] == 5:
                detectorVal = detectorVal + [14]
                temp1 = temp1+1
            elif adcChannel[i] == 6:
                detectorVal = detectorVal + [15]
                temp1 = temp1+1
            elif adcChannel[i] == 7:
                detectorVal = detectorVal + [16]
                temp1 = temp1+1
            
    #### Convert list into numpy array ####
    detectorVal = np.asarray(detectorVal)
    #temp = [i for i in groupDetectorVal if i <= 12]
    #temp1 = [i for i in groupDetectorVal if i > 12]
    plane1Data = np.zeros((temp,len(rawDataMat[0,:])))
    plane2Data = np.zeros((temp1,len(rawDataMat[0,:])))
    plane1Times = np.zeros((temp,1))
    plane2Times = np.zeros((temp1,1))

#### Separate data based on each plane of detectors ####
    n = 0
    m = 0
    for i in range(0,len(adcBoardVals)):
        
        if detectorVal[i] <= 12:
            plane1Data[n,:] = rawDataMat[i,:]
            plane1Times[n] = timeVals[i]
            n = n+1
        else:
            plane2Data[m,:] = rawDataMat[i,:]
            plane2Times[m] = timeVals[i]
            m = m+1
            
    #A = RawSamples.rawData
    #print(rawData)

#### Perform PSD for each plane of data to extract just neutron information ####
    neutronPulseData1 = PSD(plane1Data,'NE204-09-21-2011-Cs137-LS-Signal.csv')
    neutronPulseData2 = PSD(plane2Data,'NE204-09-21-2011-Cs137-LS-Signal.csv')

#### Generate cones and do energy reconstruction of neutrons ####
    cones = generateCones(detectorVal,plane1Times,plane2Times,neutronPulseData1,neutronPulseData2)
