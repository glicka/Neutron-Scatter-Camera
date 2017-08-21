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
    
    f = h5py.File(datafile, 'r')
    #print(f)
    #print("Keys: %s" % f.keys())
    groupKeyVal = f.keys()[4]
    groupDetectorVal = f.keys()[1]
    detectorVals = list(f[groupDetectorVal])
    groupTimeVals = f.keys()[2]
    timeVals = list(f[groupTimeVals])
    rawData = list(f[groupKeyVal])
    #A = RawSamples.rawData
    #print(rawData)
    rawDataMat = np.matrix(rawData)
    neutronPulseData = PSD(rawDataMat,'NE204-09-21-2011-Cs137-LS-Signal.csv')
    cones = generateCones(detectorVals,timeVals,neutronPulseData)
    #for i in range(0,100):#range(0,len(rawDataMat[:,0])):
    #    print 'i = ', i
    #    fig = rawDataMat[i,:]
    #    wav = np.squeeze(np.asarray(fig))
        #plt.figure()
        #plt.plot(wav)
        #plt.show()