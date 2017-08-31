#!/usr/bin/env python2
# -*- coding: utf-8 -*-
"""
Created on Wed Aug 16 10:31:57 2017

@author: aglick
"""

def generateCones(plane1Dets,plane2Dets,plane1Times,plane2Times,plane1NeutronPulseADC,plane2NeutronPulseADC):
    import csv
    import numpy as np
    import math
    import matplotlib.pyplot as plt
    import matplotlib
    import pylab as pl
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
    data1Mat = np.column_stack((tuple(plane1Dets),tuple(plane1Times),tuple(plane1NeutronPulseADC)))
    data1MatSort = data1Mat[data1Mat[:,0].argsort()[::1]]
    np.savetxt("data1MatSort.csv", data1MatSort, delimiter=",")
    plane1Dets = [column[0] for column in data1MatSort]
    plane1Times = [column[1] for column in data1MatSort]
    plane1NeutronPulseADC = [column[2] for column in data1MatSort]
    data2Mat = np.column_stack((tuple(plane2Dets),tuple(plane2Times),tuple(plane2NeutronPulseADC)))
    data2MatSort = data2Mat[data2Mat[:,0].argsort()[::1]]
    plane2Dets = [column[0] for column in data2MatSort]
    plane2Times = [column[1] for column in data2MatSort]
    plane2NeutronPulseADC = [column[2] for column in data2MatSort]
    plane1Dets = np.array(plane1Dets,dtype='int')
    plane1Dets = np.array(plane1Dets,dtype='int')
    plane2Dets = np.array(plane2Dets,dtype='int')
    plane2Dets = np.array(plane2Dets,dtype='int')
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
    tic = time.time()
    for i in range(0,len(plane1Times)): #range(0,len(plane1Times))
        if i > 200:
            for n in range(i-100,i+100):
                if plane2Times[n] - plane1Times[i] <= 100000 and plane2Times[n] - plane1Times[i] > 0:
                    #print('plane1Local = ',plane1Local[i])
                    #print('plane1Dets = ',plane1Dets[i])
                    x1 = plane1Local[plane1Dets[i]]
                    x2 = plane2Local[plane2DetScale[n]]
                    #print('x1 = ',x1)
                    distance = np.sqrt((x2[0]-x1[0])**2 + (x2[1]-x1[1])**2 + (x2[2])**2)
                    timeSeparation = (plane2Times[n]-plane1Times[i])*timeScale
                    energy = (1/(1.602*10**(-13)))*0.5*(1.675*10**(-27))*(distance/timeSeparation)**2
                    neutronEnergyTOF += [energy] #MeV
                #print('Energy = ',energy,' MeV') 
                    if n%100 == 0:
                        print('n = ',n)
                        print('x1 = ',x1)
                        print('x2 = ',x2)
                    break
        else:
            for n in range(0,i+200):
#            if n%10000 == 0:
#                print('n = ',n)
                if plane2Times[n] - plane1Times[i] <= 100000 and plane2Times[n] - plane1Times[i] > 0:
                    x1 = plane1Local[plane1Dets[i]]
                    x2 = plane2Local[plane2DetScale[n]]
                    distance = np.sqrt((x2[0]-x1[0])**2 + (x2[1]-x1[1])**2 + (x2[2])**2)
                    timeSeparation = (plane2Times[n]-plane1Times[i])*timeScale
                    energy = (1/(1.602*10**(-13)))*0.5*(1.675*10**(-27))*(distance/timeSeparation)**2 #MeV
                    neutronEnergyTOF += [energy] #MeV
                    
                #print('Energy = ',energy,' MeV') 
                    if n%100 == 0:
                        print('n = ',n)
                        print('x1 = ',x1)
                        print('x2 = ',x2)
                    break
        
        if i%100000 == 0:
            toc = time.time()
            print('i = ',i)
            print('elapsed time = ',toc-tic, 's')
    neutronEnergyTOF = np.array(neutronEnergyTOF)
    neutronEnergyTOF = neutronEnergyTOF*10**6
#    for i in range(0,len(neuronEnergyTOF)):
#        temp = neutronPulseData1[i]
#        neutronEnergy += [neutronEnergyTOF[i]] + [temp]

#    numpy.savetxt("neutron.csv", neutronEnergyTOF, delimiter=",")
    energyHist = np.histogram(neutronEnergyTOF,100)
    a = energyHist[0]
    b = energyHist[1]
    c = b[0:100]
    plt.figure(1)
    plt.plot(c,a,'r--')
    plt.xlabel('Neutron Energy [eV]')
    plt.ylabel('Counts')
    plt.title('Neutron Spectrum')
    plt.autoscale(enable=True,axis='x',tight=True)
    pl.xticks(rotation=45)
    #plt.legend(loc='upper right')
    #plt.plot(d,f)
    plt.show()
    
#    numpy.savetxt("neutronEnergy.csv", c, delimiter=",")
#    numpy.savetxt("neutronCounts.csv", a, delimiter=",")
    
    return
    