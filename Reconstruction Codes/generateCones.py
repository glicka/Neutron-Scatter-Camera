#!/usr/bin/env python2
# -*- coding: utf-8 -*-
"""
Created on Wed Aug 16 10:31:57 2017

@author: aglick
"""

def generateCones(plane1Dets,plane2Dets,plane1Times,plane2Times,neutronPulseData1,neutronPulseData2):
    import csv
    import numpy as np
    import math
    import matplotlib.pyplot as plt
    import pylab
    
    planeSeparation = 150 #cm
    D = planeSeparation #cm
    distance = 0
    temp = 0
    x1 = []
    x2 = []
    plane1Local = np.array([[0,0,0],[0,5,0],[0,10,0],[5,0,0],[5,5,0],[5,10,0],[10,0,0],[10,5,0],[10,10,0],[15,5,0],[15,10,0]],dtype='float')
    plane2Local = np.array([[0,0,D],[0,5,D],[0,10,D],[5,0,D],[5,5,D],[5,10,D],[10,0,D],[10,5,D],[10,10,D],[15,5,D],[15,10,D]],dtype='float')
    neutronEnergyTOF = []
    neutronEnergy = []

    plane2DetScale = []
    for i in range(0,len(plane2Dets)):
        if plane2Dets[i] == 12:
            plane2DetScale = plane2DetScale + [0]
        if plane2Dets[i] == 13:
            plane2DetScale = plane2DetScale + [1]
        if plane2Dets[i] == 14:
            plane2DetScale = plane2DetScale + [2]
        if plane2Dets[i] == 15:
            plane2DetScale = plane2DetScale + [3]
        if plane2Dets[i] == 16:
            plane2DetScale = plane2DetScale + [4]
        if plane2Dets[i] == 17:
            plane2DetScale = plane2DetScale + [5]
        if plane2Dets[i] == 18:
            plane2DetScale = plane2DetScale + [6]
        if plane2Dets[i] == 19:
            plane2DetScale = plane2DetScale + [7]
        if plane2Dets[i] == 20:
            plane2DetScale = plane2DetScale + [8]
        if plane2Dets[i] == 21:
            plane2DetScale = plane2DetScale + [9]
        if plane2Dets[i] == 22:
            plane2DetScale = plane2DetScale + [10]
        if plane2Dets[i] == 23:
            plane2DetScale = plane2DetScale + [11]
    
    plane2DetScale = np.array(plane2DetScale,dtype = 'int')
#### Calculate neutron energy from time of flight between the 2 planes ####
    for i in range(0,len(plane1Times)):
        for n in range(0,len(plane2Times)):
            if plane1Times[i] - plane2Times[n] <= 10000:
                x1 = [plane1Local[plane1Dets[i]]]
                x2 = [plane2Local[plane2DetScale[n]]]
                distance = np.sqrt((x2[0]-x1[0])**2 + (x2[1]-x1[1])**2 + (x2[2])**2)
                neutronEnergyTOF = neutronEnergyTOF + [(1/(1.602*10**(-13)))*0.5*(1.675*10**(-27))*(distance/(plane1Times[i]-plane2Times[n]))**2] #MeV
                
    neutronEnergyTOF = np.array(neutronEnergyTOF)
    
    for i in range(0,len(neuronEnergyTOF)):
        temp = neutronPulseData1[i]
        neutronEnergy = neutronEnergy + [neutronEnergyTOF[i]] + [temp]
#    dataListPlane2 = []
#    m=0
#   k=0
#   for i in range(0,len(neutronPulseData)-1):
#        if detectorVals[i] <= 11:
#            m = m + 1
            #dataListPlane1 [i,:] = np.insert([neutronPulseData[i],timeVals[i])
#        else:
#            k = k + 1
            
#    adcBit = len(neutronPulseData[0,:])        
#    dataListPlane1 = np.zeros([m,adcBit+2])
#    dataListPlane2 = np.zeros([k,adcBit+2])
    
#    for i in range(0,len(neutronPulseData)-1):
#        if detectorVals[i] <=11:
#            dataListPlane1[i,:] = [neutronPulseData[i,:],timeVals[i],detectorVals[i]]
#        else:
#            dataListPlane2[i,:] = [neutronPulseData[i,:],timeVals[i],detectorVals[i]]
    
    
#    dataListPlane1 = dataListPlane1[np.argsort(dataListPlane1[:,adcBit+1])]
#    dataListPlane2 = dataListPlane2[np.argsort(dataListPlane1[:,adcBit+1])]
    
    
#    hist = np.zeros(len(dataListPlane1[:,0]))
#    for i in range(0,len(dataListPlane1[:,0])):
#        hist[i] = dataListPlane2[i,adcBit+1]-dataListPlane1[i,adcBit+1]
    
#    plt.figure()
#    plt.plot(hist)
#    plt.show()
    