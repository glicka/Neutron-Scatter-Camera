#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Jul  5 10:51:45 2017

@author: aglick
"""
def PSD1(pulseData, pulseDataTraining):
    import csv
    import numpy as np
    import math
    import matplotlib.pyplot as plt
    #import plotly as py
    import pylab

    #plt.scatter(x[0:70000],neutronInfo[0:70000],y[0:70000],photonInfo[0:70000])
    i = 0
    pulseIntegralTraining = 0
    tailIntegralTraining = 0
    peakVal = 0
    peakTime = 0
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
            pulseIntegralTraining = integratePulse(row,3935)
            tailIntegralTraining = integrateTail(row,3935,peakTime)
            #print 'pulseIntegral = ', pulseIntegral
            tailToTotalRatioTraining[i] = tailIntegralTraining/float(pulseIntegralTraining)
            
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
    pulseIntegral = 0
    tailIntegral = 0
    peakVal = 0
    peakTime = 0
    neutronTailToTotalRatio = []
    #tailToTotalRatio = 0
    with open(pulseData,'r') as csvfile:
        neutronData = csv.reader(csvfile)
        #print 'photonTraining = ', photonTraining
        #map(int,photonTraining)
        #photonTraining1 = [int(x) for x in photonTraining]
        #reader = list(csv.DictReader(open(csvfile), delimiter='|'))
        #numlines = len(open('NE204-09-21-2011-PuBe-LSC-Signal.csv').readlines())
        #numlines = len(csvfile.readlines())
        numlines = len(open(pulseData).readlines())
        tailToTotalRatio = np.zeros((numlines,1))
        adcVal = np.zeros((numlines,1))
        for row in neutronData:
            #pylab.plot(row)
            #pylab.show()
            #print(row)
            peakVal, peakTime = findPeaks(row,3900)  
            #print(peakVal)
            pulseIntegral = integratePulse(row,3900)
            tailIntegral = integrateTail(row,3900,peakTime)
            #print 'pulseIntegral = ', pulseIntegral
            tailToTotalRatio[i] = tailIntegral/float(pulseIntegral)
            adcVal[i] = pulseIntegral
            
            if i%10000 == 0:
                print('m = ', i)
                #print('pulseIntegral = ', pulseIntegral)
                #print('adcVal = ', adcVal[i])
            #if i==0:
            #    print('peakTime = ', peakTime)
                
            i=i+1
    
    #n = 0
    #neutronADC = [i for i in adcVal if tailToTotalRatio[i] >= 0.7]
    #photonADC = [adcVal[i] for i in tailToTotalRatio if tailToTotalRatio[i] < 0.7]

    
    neutronTailToTotalRatio = [i for i in tailToTotalRatio if i >= 0.35]
    photonTailToTotalRatio = [i for i in tailToTotalRatio if i < 0.35]
    
    #neutronADC = np.zeros(len(neutronTailToTotalRatio))
    #photonADC = np.zeros(len(photonTailToTotalRatio))
    neutronADC = []
    photonADC = []
#    n = 0
#    m = 0
    for i in range(0,len(tailToTotalRatio)-1):
        if tailToTotalRatio[i] >= 0.35:
            neutronADC = neutronADC + [adcVal[i]]
            #n = n+1
            #print('n = ',n)
        else:
            photonADC = photonADC + [adcVal[i]]
            #m = m+1
        
    neutronADC = np.asarray(neutronADC)
    photonADC = np.asarray(photonADC)
    #photonADC = [i for i in photonADC if i < 50]
    #for i in range(0,len(tailToTotalRatio)):
    #    if tailToTotalRatio[i] > 0.65:
    #        neutronTailToTotalRatio[n] = neutronTailToTotalRatio.append(tailToTotalRatio[i])
    #        n = n+1
    #        print('tailToTotalRatio = ',tailToTotalRatio[i])
    #        print('neutronTailToTotalRatio = ', neutronTailToTotalRatio[n])
            #print('n = ',n)
            
    #neutronTailToTotalRatio = np.asfarray(neutronTailToTotalRatio,dtype=np.float)
    #neutronTailToTotalRatio = np.array(list(neutronTailToTotalRatio))
    #print('neutronTailToTotalRatio = ',neutronTailToTotalRatio)
    a = 0
    b = 0
    c = 0
    d = 0
    e = 0
    f = 0
   #numpy.savetxt("neutron.csv", neutronTailToTotalRatio, delimiter=",")
    #numpy.savetxt("photon.csv", photonTailToTotalRatio, delimiter=",")
    histTTTRT = np.histogram(photonTailToTotalRatio,100000)

    histPADC = np.histogram(photonADC,100000)
    #histTTTRT = photonTailToTotalRatio.hist(bins=100000)
    a = histTTTRT[0]
    b = histTTTRT[1]
    c = b[0:100000]
    for i in range(0,len(a)):
        if a[i] > 50:
            a[i] = 0
            
    a1 = histPADC[0]
    b1 = histPADC[1]
    c1 = b[0:100000]
    #print('a = ', a)
    #print('c = ', c)
    histTTT = np.histogram(neutronTailToTotalRatio,100000)
    histNADC = np.histogram(neutronADC,100000)
    #histTTT = neutronTailToTotalRatio.hist(bins=100000)
    d = histTTT[0]
    e = histTTT[1]
    f = e[0:100000]
    d1 = histNADC[0]
    e1 = histNADC[1]
    f1 = e1[0:100000]
    #print('c1 = ', c1)
    #print('e1 = ', e1)


    plt.figure(2)
    plt.plot(a,c,'r',label='photons')
    plt.plot(d,f,'b--',label='neutrons')
    plt.xlabel('Counts')
    plt.ylabel('Tail to Total Ratio')
    plt.legend(loc='upper right')
    #plt.plot(d,f)
    plt.show()
    
    plt.figure(3)
    plt.plot(a1,c1,'r',label='photons')
    plt.plot(d1,f1,'b--',label='neutrons')
    plt.xlabel('Counts')
    plt.ylabel('ADC Val')
    plt.legend(loc='upper right')
    #plt.plot(d,f)
    plt.show()
    

########################################################################################
### Sum up ADC values of pulse (integrate pulse) to put into neutron/photon category ###
########################################################################################

    return neutronADC