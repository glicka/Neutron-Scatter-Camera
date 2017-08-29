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
    
#### Break up detectors into 1-24 based on adcChannel and adcBoard values ####    
    for i in range(0,50000):#len(adcBoardVals)):
        if i%50000 == 0:
            print('k = ',i)    
        if adcBoardVals[i] == 5:
            if adcChannel[i] == 0:
                detectorVal = detectorVal + [0]
            elif adcChannel[i] == 1:
                detectorVal = detectorVal + [1]
            elif adcChannel[i] == 2:
                detectorVal = detectorVal + [2]
            elif adcChannel[i] == 3:
                detectorVal = detectorVal + [3]
            elif adcChannel[i] == 4:
                detectorVal = detectorVal + [4]
            elif adcChannel[i] == 5:
                detectorVal = detectorVal + [5]
            elif adcChannel[i] == 6:
                detectorVal = detectorVal + [6]
            elif adcChannel[i] == 7:
                detectorVal = detectorVal + [7]
        elif adcBoardVals[i] == 7:
            if adcChannel[i] == 0:
                detectorVal = detectorVal + [16]
            elif adcChannel[i] == 1:
                detectorVal = detectorVal + [17]
            elif adcChannel[i] == 2:
                detectorVal = detectorVal + [18]
            elif adcChannel[i] == 3:
                detectorVal = detectorVal + [19]
            elif adcChannel[i] == 4:
                detectorVal = detectorVal + [20]
            elif adcChannel[i] == 5:
                detectorVal = detectorVal + [21]
            elif adcChannel[i] == 6:
                detectorVal = detectorVal + [22]
            elif adcChannel[i] == 7:
                detectorVal = detectorVal + [23]
        elif adcBoardVals[i] == 6:
            if adcChannel[i] == 0:
                detectorVal = detectorVal + [8]
            elif adcChannel[i] == 1:
                detectorVal = detectorVal + [9]
            elif adcChannel[i] == 2:
                detectorVal = detectorVal + [10]
            elif adcChannel[i] == 3:
                detectorVal = detectorVal + [11]
            elif adcChannel[i] == 4:
                detectorVal = detectorVal + [12]
            elif adcChannel[i] == 5:
                detectorVal = detectorVal + [13]
            elif adcChannel[i] == 6:
                detectorVal = detectorVal + [14]
            elif adcChannel[i] == 7:
                detectorVal = detectorVal + [15]
    
#### Convert list into numpy array ####
    detectorVal = np.array(detectorVal,dtype='float')

#### Separate data based on each plane of detectors #### 
    plane1Data = []
    plane2Data = []
    plane1Times = []
    plane2Times = []
    plane1Dets = []
    plane2Dets = []
    for i in range(0,50000):#len(adcBoardVals)):
        if i%50000 == 0:
            print('i = ',i)
            
        if detectorVal[i] <= 11:
            plane1Data = plane1Data + [rawDataMat[i,:]]
            plane1Times = plane1Times + [timeVals[i]]
            plane1Dets = plane1Dets + [detectorVal[i]]
        else:
            plane2Data = plane2Data + [rawDataMat[i,:]]
            plane2Times = plane2Times + [timeVals[i]]
            plane2Dets = plane2Dets + [detectorVal[i]]
#### Convert list into numpy array ####
    plane1Data = np.array(plane1Data,dtype='float')
    plane2Data = np.array(plane2Data,dtype='float')
    plane1Times = np.array(plane1Times,dtype='float')
    plane2Times = np.array(plane2Times,dtype='float')
    plane1Dets = np.array(plane1Dets,dtype='int')
    plane2Dets = np.array(plane2Dets,dtype='int')

#### Perform PSD for each plane of data to extract just neutron information ####
    print('Performing PSD on Plane 1')
    plane1NeutronDets,plane1NeutronTimes,neutronPulseData1 = PSD(plane1Dets,plane1Times,plane1Data)
    print('Performing PSD on Plane 2')
    plane2NeutronDets,plane2NeutronTimes,neutronPulseData2 = PSD(plane2Dets,plane2Times,plane2Data)

    print('length of plane1NeutronDets: ',len(plane1NeutronDets))
    print('length of plane1NeutronTimes: ',len(plane1NeutronTimes))
    print('length of neutronPulseData1: ',len(neutronPulseData1[:,0]))
    print('length of plane2NeutronDets: ',len(plane2NeutronDets))
    print('length of plane2NeutronTimes: ',len(plane2NeutronTimes))
    print('length of neutronPulseData2: ',len(neutronPulseData2[:,0]))
#### Generate cones and do energy reconstruction of neutrons ####
    cones = generateCones(plane1NeutronDets,plane2NeutronDets,plane1NeutronTimes,plane2NeutronTimes,neutronPulseData1,neutronPulseData2)
