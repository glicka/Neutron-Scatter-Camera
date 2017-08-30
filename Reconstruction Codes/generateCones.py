#!/usr/bin/env python2
# -*- coding: utf-8 -*-
"""
Created on Wed Aug 16 10:31:57 2017

@author: aglick
"""

def generateCones(plane1Dets,plane2Dets,plane1Times,plane2Times,plane1NeutronPulseData,plane2NeutronPulseData):
    import csv
    import numpy as np
    import math
    import matplotlib.pyplot as plt
    import pylab
    import time
    planeSeparation = 0.6096 #meters
    detectorSeparation = 0.0889 #meters
    u = detectorSeparation #meters
    D = planeSeparation #meters
    clockSpeed = 250*10**6 #Hz
    timeScale = 1/clockSpeed #seconds
    distance = 0
    temp = 0
    x1 = []
    x2 = []
    plane1Local = np.array([[0,0,0],[0,u,0],[0,2*u,0],[u,0,0],[u,u,0],[u,2*u,0],[2*u,0,0],[2*u,u,0],[2*u,2*u,0],[3*u,0,0],[3*u,u,0],[3*u,2*u,0]],dtype='float')
    plane2Local = np.array([[0,0,D],[0,u,D],[0,2*u,D],[u,0,D],[u,u,D],[u,2*u,D],[2*u,0,D],[2*u,u,D],[2*u,2*u,D],[3*u,0,D],[3*u,u,D],[3*u,2*u,D]],dtype='float')
    neutronEnergyTOF = []
    neutronEnergy = []
    
    plane2DetScale = []
    for i in range(0,len(plane2Dets)):
        if plane2Dets[i] == 12:
            plane2DetScale += [0]
        if plane2Dets[i] == 13:
            plane2DetScale += [1]
        if plane2Dets[i] == 14:
            plane2DetScale += [2]
        if plane2Dets[i] == 15:
            plane2DetScale += [3]
        if plane2Dets[i] == 16:
            plane2DetScale += [4]
        if plane2Dets[i] == 17:
            plane2DetScale += [5]
        if plane2Dets[i] == 18:
            plane2DetScale += [6]
        if plane2Dets[i] == 19:
            plane2DetScale += [7]
        if plane2Dets[i] == 20:
            plane2DetScale +=[8]
        if plane2Dets[i] == 21:
            plane2DetScale += [9]
        if plane2Dets[i] == 22:
            plane2DetScale += [10]
        if plane2Dets[i] == 23:
            plane2DetScale += [11]
    
    plane2DetScale = np.array(plane2DetScale,dtype = 'int')
#### Calculate neutron energy from time of flight between the 2 planes ####
    for i in range(0,len(plane1Times)):
        tic = time.time()
        
        for n in range(0,len(plane2Times)):
#            if n%10000 == 0:
#                print('n = ',n)
            if plane2Times[n] - plane1Times[i] <= 10000 and plane2Times[n] - plane1Times[i] > 0:
                x1 = plane1Local[plane1Dets[i]]
                x2 = plane2Local[plane2DetScale[n]]
                distance = np.sqrt((x2[0]-x1[0])**2 + (x2[1]-x1[1])**2 + (x2[2])**2)
                timeSeparation = (plane2Times[n]-plane1Times[i])*timeScale
                neutronEnergyTOF += [(1/(1.602*10**(-13)))*0.5*(1.675*10**(-27))*(distance/timeSeparation)**2] #MeV
                #energy = (1/(1.602*10**(-13)))*0.5*(1.675*10**(-27))*(distance/timeSeparation)**2
                #print('Energy = ',energy,' MeV') 
                if n%10000 == 0:
                    print('n = ',n)
                    print('x1 = ',x1)
                    print('x2 = ',x2)
                break
        toc = time.time()
        if i%100 == 0:
            print('i = ',i)
            print('tictoc = ',toc-tic)
    neutronEnergyTOF = np.array(neutronEnergyTOF)
    
#    for i in range(0,len(neuronEnergyTOF)):
#        temp = neutronPulseData1[i]
#        neutronEnergy += [neutronEnergyTOF[i]] + [temp]

#    numpy.savetxt("neutron.csv", neutronEnergyTOF, delimiter=",")
    energyHist = np.histogram(neutronEnergyTOF,1000)
    a = energyHist[0]
    b = energyHist[1]
    c = b[0:1000]
    plt.figure(1)
    plt.plot(c,a,'r',label='neutron spectrum')
    plt.xlabel('Neutron Energy [MeV]')
    plt.ylabel('Counts')
    plt.legend(loc='upper right')
    #plt.plot(d,f)
    plt.show()
    
#    numpy.savetxt("neutronEnergy.csv", c, delimiter=",")
#    numpy.savetxt("neutronCounts.csv", a, delimiter=",")
    
    return
    