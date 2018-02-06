#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Aug 22 16:50:31 2017

@author: aglick
"""

def PSD(detectorData,timeData,pulseData,plane,tic):
    import numpy as np
    import matplotlib.pyplot as plt
    import time



    i = 0
    pulseIntegral = 0
    tailIntegral = 0
    peakVal = 0
    peakTime = 0
    neutronTailToTotalRatio = []

    tailToTotalRatio = []
    adcVal = []
    #tic = time.time()
    for row in pulseData:
#        peakVal, peakTime = max(enumerate(row), key=operator.itemgetter(1)) #findPeaks(row)  
        #print('temp = ',temp)
        peakTime = row.argmax()
        pulseIntegral = integratePulse(row,peakTime)
        tailIntegral = integrateTail(row,peakTime)
        tailToTotalRatio += [tailIntegral/float(pulseIntegral)]
        adcVal += [pulseIntegral]
        
        if i%100000 == 0:
            print('m = ', i) 
            print('elapsed time = ',time.time()-tic,'s')     
        i=i+1
    
    
    adcVal = np.asarray(adcVal,dtype='float')
    tailToTotalRatio = np.asarray(tailToTotalRatio,dtype='float')
    neutronTailToTotalRatio = [i for i in tailToTotalRatio if i >= 0.35]
    photonTailToTotalRatio = [i for i in tailToTotalRatio if i < 0.35]

########################################################################################
### Sum up ADC values of pulse (integrate pulse) to put into neutron/photon category ###
########################################################################################
    
    neutronADC = []
    photonADC = []
    neutronDets = []
    neutronTimes = []
    for i in range(0,len(tailToTotalRatio)):
        if tailToTotalRatio[i] >= 0.35:
            neutronADC += [adcVal[i]]
            neutronDets += [detectorData[i]]
            neutronTimes += [timeData[i]]
        else:
            photonADC += [adcVal[i]]
        
    neutronADC = np.asarray(neutronADC)
    neutronDets = np.asarray(neutronDets,dtype = 'int')
    neutronTimes = np.asarray(neutronTimes)
    photonADC = np.asarray(photonADC)
    
    a = 0
    b = 0
    c = 0
    d = 0
    e = 0
    f = 0
    #numpy.savetxt("neutron.csv", neutronTailToTotalRatio, delimiter=",")
    #numpy.savetxt("photon.csv", photonTailToTotalRatio, delimiter=",")
    histTTTPT = np.histogram(photonTailToTotalRatio,100000)

    histPADC = np.histogram(photonADC,100000)
    #histTTTRT = photonTailToTotalRatio.hist(bins=100000)
    a = histTTTPT[0]
    b = histTTTPT[1]
    c = b[0:100000]
    a1 = histPADC[0]
    b1 = histPADC[1]
    c1 = b1[0:100000]

    histTTT = np.histogram(neutronTailToTotalRatio,100000)
    histNADC = np.histogram(neutronADC,100000)
    #histTTT = neutronTailToTotalRatio.hist(bins=100000)
    d = histTTT[0]
    e = histTTT[1]
    f = e[0:100000]
    d1 = histNADC[0]
    e1 = histNADC[1]
    f1 = e1[0:100000]

    plt.figure(2)
    plt.plot(a,c,'r',label='photons')
    plt.plot(d,f,'b--',label='neutrons')
    plt.xlabel('Counts')
    plt.ylabel('Tail to Total Ratio')
    plt.legend(loc='upper right')
    plt.title(plane)
    #plt.plot(d,f)
    plt.show()
    
    plt.figure(3)
    plt.plot(c1,a1,'r',label='photons')
    plt.plot(f1,d1,'b--',label='neutrons')
    plt.xlabel('ADC Val')
    plt.ylabel('Counts')
    plt.legend(loc='upper right')
    plt.title(plane)
    #plt.plot(d,f)
    plt.show()
    


    return neutronDets, neutronTimes, neutronADC
    
    