#!/usr/bin/env python2
# -*- coding: utf-8 -*-
"""
Created on Wed Aug 16 10:31:57 2017

@author: aglick
"""

def generateCones(detectorVals,timeVals,neutronPulseData):
    import csv
    import numpy as np
    import math
    import matplotlib.pyplot as plt
    #import plotly as py
    import pylab
    
    
    dataListPlane2 = []
    m=0
    k=0
    for i in range(0,len(neutronPulseData)-1):
        if detectorVals[i] <= 11:
            m = m + 1
            #dataListPlane1 [i,:] = np.insert([neutronPulseData[i],timeVals[i])
        else:
            k = k + 1
            
    dataListPlane1 = np.zeros([m,len(neutronPulseData[0,:])+2])
    dataListPlane2 = np.zeros([k,len(neutronPulseData[0,:])+2])
    
    for i in range(0,len(neutronPulseData)-1):
        if detectorVals[i] <=11:
            dataListPlane1[i,:] = [neutronPulseData[i,:],timeVals[i],detectorVals[i]]
        else:
            dataListPlane2[i,:] = [neutronPulseData[i,:],timeVals[i],detectorVals[i]]
            
    dataListPlane1 = dataListPlane1[np.argsort(dataListPlane1[:,len(neutronPulseData)+1])]
    dataListPlane2 = dataListPlane2[np.argsort(dataListPlane1[:,len(neutronPulseData)+1])]
            