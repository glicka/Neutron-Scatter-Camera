#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu May  4 14:08:48 2017

@author: aglick
"""

def PSD(pulseData, pulseDataTraining):
    import csv
    import numpy as np
    import math
    import matplotlib.pyplot as plt
    #import plotly as py
    import pylab
    photonTraining = 0
    neutronPhotonDiscriminator = 0
    #plt.scatter(x[0:70000],neutronInfo[0:70000],y[0:70000],photonInfo[0:70000])
    i = 0
    with open(pulseDataTraining,'r') as csvfile:
        photonTraining = csv.reader(csvfile)
        #print 'photonTraining = ', photonTraining
        #map(int,photonTraining)
        #photonTraining1 = [int(x) for x in photonTraining]
        #reader = list(csv.DictReader(open(csvfile), delimiter='|'))
        numlines = len(open('NE204-09-21-2011-Cs137-LS-Signal.csv').readlines())
        #numlines = len(csvfile.readlines())
        tailToTotalRatioTraining = np.zeros((numlines,1))
        for row in photonTraining:
            #pylab.plot(row)
            #pylab.show()
            #print(row)
            peakVal, peakTime = findPeaks(row,3935)  
            #print(peakVal)
            pulseIntegral = integratePulse(row,3935)
            tailIntegral = integrateTail(row,3935,peakTime)
            #print 'pulseIntegral = ', pulseIntegral
            tailToTotalRatioTraining[i] = tailIntegral/float(pulseIntegral)
            
            if i%10000 == 0:
                print('i = ', i)
            #if i==0:
            #    print('peakTime = ', peakTime)
            i=i+1

#print('tailToTotalRatioTraining = ', tailToTotalRatioTraining)

    #print peakToTotalRatioTraining
    
    #if photonTraining == 0:
    #    print("this is a string")
    
    i = 0
    #with open(pulseData,'r') as csvfile1:
    #    neutronPhotonDiscriminator = csv.reader(csvfile1)
        #map(int,photonTraining)
        #photonTraining1 = [int(x) for x in photonTraining]
        #reader = list(csv.DictReader(open(csvfile), delimiter='|'))
        #numlines1 = len(open(neutronPhotonDiscriminator).readlines())
        #numlines = len(open(pulseData).readlines())
    numlines = len(pulseData[:,0])
        #numlines = len(csvfile.readlines())
    tailToTotalRatio = np.zeros((numlines,1))
    pulseValue = np.zeros((numlines,1))
    for row in pulseData[0,0:10000]:#[0,0:99999]:
            #print(row)
        peakVal = findPeaks1(row,30)  
        if i%1000 == 0:
            print('i = ', i)
            
            #print(peakVal)
        pulseIntegral = integratePulse1(row,30)
        peakToTotalRatio[i] = peakVal/float(pulseIntegral)
        pulseValue[i]=pulseIntegral
        i=i+1
            #print(i)
            
    if neutronPhotonDiscriminator == 0:
        print("this is a string")
    
    n=0
    m=0
    neutronInfo = []
    photonInfo = []
    for i in range(0,10000):
    #for i in range(0,len(peakToTotalRatioTraining)-1):
        if i%1000 == 0:
            print('n = ', i)
            
        if peakToTotalRatio[i] < peakToTotalRatioTraining[i]:
            neutronInfo[n] = neutronInfo.append(pulseValue[i])
            n = n + 1
            #print 'n = ', n
        else:
            photonInfo[m] = photonInfo.append(pulseValue[i])
            m = m + 1
            #print 'm = ', m
    #print 'photonInfo = ',photonInfo
    #print 'neutronInfo = ',neutronInfo
    x = range(0,len(neutronInfo),1)
    y = range(0,len(photonInfo),1)
    neutronInfo = np.asfarray(neutronInfo,dtype=np.float)
    neutronInfo = np.sort(neutronInfo)
    photonInfo = np.asfarray(photonInfo,dtype=np.float)
    x = np.asarray(x)
    y = np.asarray(y)
    neutronAmounts = []
    adcVal = []
    n=0
    #print 'new neutronInfo = ', neutronInfo
    for i in range(0,10000):
    #for i in range(0,len(neutronInfo)-1):
        if i%1000 ==0:
            print('i = ', i, 'n = ', n)
         
        for k in range(0,10000):   
        #for k in range(0,len(neutronInfo)-1):
            if neutronInfo[i]==neutronInfo[k] and neutronAmounts[n]>=1:
                neutronAmounts[n] = neutronAmounts[n]+1
                print('neutronAmounts = ',neutronAmounts[n])
            elif neutronInfo[i]==neutronInfo[k]:
                neutronAmounts[n] = 1
                adcVal[n] = neutronInfo[i]
                print('neutronInfo = ',neutronInfo[i])
        n = n + 1
    
    print('adcVal = ', adcVal)
    print('photon pttr = ', photonInfo)
    histTTTRT = np.histogram(tailToTotalRatioTraining,100000)
    a = histTTTRT[0]
    b = histTTTRT[1]
    c = b[0:100000]
    print('a = ', a)
    print('b = ', b)

    plt.figure(2)
    plt.plot(a,c)
    plt.show()
    #plt.plot(x[0:70000],neutronInfo[0:70000],y[0:70000],photonInfo[0:70000])
    #plt.scatter(x[0:70000],neutronInfo[0:70000],y[0:70000],photonInfo[0:70000])
    pylab.plot(adcVal, neutronAmounts, '*b', label='neutrons')
    pylab.plot(y[0:70000], photonInfo[0:70000], '--r', label='photons')
    pylab.legend(loc='upper left')
    #pylab.ylim(-1.5, 2.0)
    pylab.show()
    return neutronInfo