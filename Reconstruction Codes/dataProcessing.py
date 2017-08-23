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
    detectorVals = list(f[groupDetectorVal])
    groupTimeVals = f.keys()[5]
    timeVals = list(f[groupTimeVals])
    rawData = list(f[groupKeyVal])
    
    rawDataMat = np.matrix(rawData)
    temp = [i for i in groupDetectorVal if i <= 12]
    temp1 = [i for i in groupDetectorVal if i > 12]
    plane1Data = np.zeros((len(temp),len(rawDataMat[0,:])))
    plane2Data = np.zeros((len(temp1),len(rawDataMat[0,:])))
    plane1Times = np.zeros((len(temp),1))
    plane2Times = np.zeros((len(temp2),1))

#### Separate data based on each plane of detectors ####
    n = 0
    m = 0
    for i in range(0,len(groupDetectorVal)):
        if groupDetectorVal[i] <= 12:
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
    cones = generateCones(detectorVals,plane1Times,plane2Times,neutronPulseData1,neutronPulseData2)
    #for i in range(0,100):#range(0,len(rawDataMat[:,0])):
    #    print 'i = ', i
    #    fig = rawDataMat[i,:]
    #    wav = np.squeeze(np.asarray(fig))
        #plt.figure()
        #plt.plot(wav)
        #plt.show()