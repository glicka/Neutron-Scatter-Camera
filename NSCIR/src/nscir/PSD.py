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
    #from numpy import *


    i = 0
    pulseIntegral = 0
    tailIntegral = 0
    totalIntegral = 0
    peakVal = 0
    peakTime = 0
    neutronTailToTotalRatio = []

    tailToTotalRatio = []
    adcVal = []
    #tic = time.time()
    for row in pulseData:
#        peakVal, peakTime = max(enumerate(row), key=operator.itemgetter(1)) #findPeaks(row)
        #print('temp = ',temp)
        row = row - np.average(row[0:15])
        rowAdj = [i for i in row if i >= 0]
        rowAdj = np.array(rowAdj)
        peakTime = rowAdj.argmax()
        #pulseIntegral = integratePulse(row,peakTime)
        #tailIntegral = integrateTail(row,peakTime)
        pulseIntegral = sum(rowAdj[0:(peakTime+8)])
        totalIntegral = sum(rowAdj[0:(len(rowAdj))])

        tailIntegral = totalIntegral-pulseIntegral
        #tailIntegral = sum(rowAdj[(peakTime+9):(len(row))])
        #if tailIntegral < 0 or tailIntegral > totalIntegral:
        #    tail = row[peakTime+1:len(rowAdj)]
        #    tailMin = tail.argmin()
        #    tailMax = tail.argmax()
        #    print('peak val = ',rowAdj[peakTime])
        #    print('tail min = ',tail[tailMin])
        #    print('tail max = ',tail[tailMax])
        #if 0 < tailIntegral <= 1:
        tailToTotalRatio += [tailIntegral/float(totalIntegral)]
        adcVal += [totalIntegral]
        #if r < 0 or r > 1:
        #    print('ratio = ',r)

        if i%100000 == 0 and i!= 0:
            print('m = ', i)
            print('elapsed time = ',time.time()-tic,'s')
            print('tailIntegral = ', tailIntegral)
            print('totalIntegral = ',totalIntegral)
        i=i+1


    adcVal = np.asarray(adcVal,dtype='float')
    tailToTotalRatio = np.asarray(tailToTotalRatio,dtype='float')
    localMin = 0
    truMax = adcVal.argmax()
    np.savetxt('tailToTotalRaio.csv',tailToTotalRatio,delimiter = ",")#("neutron.csv", neutronTailToTotalRatio, delimiter=",")
    np.savetxt('adcVal.csv',adcVal,delimiter = ",")
    localMin = 999999999
    truMax = adcVal.argmax()
    truMin = adcVal.argmin()
    ttrArg = 0
    print('ratio = ',tailToTotalRatio[truMax])
    print('adc = ',adcVal[truMax])
    for i in range(0,len(tailToTotalRatio)):
        if tailToTotalRatio[truMax]-0.1 < tailToTotalRatio[i] < tailToTotalRatio[truMax]:
            if localMin > adcVal[i] and adcVal[i] > 1000:#7*adcVal[truMin]:
                localMin = adcVal[i]
                ttrArg = tailToTotalRatio[i]
    #b = (diff(sign(diff(tailToTotalRatio))) > 0).nonzero()[0] + 1 # local min
    #localMin = tailToTotalRatio[b[0]]
    neutronTailToTotalRatio = [i for i in tailToTotalRatio if i >= ttrArg]
    photonTailToTotalRatio = [i for i in tailToTotalRatio if 0 < i < ttrArg]

########################################################################################
### Sum up ADC values of pulse (integrate pulse) to put into neutron/photon category ###
########################################################################################

    neutronADC = []
    photonADC = []
    neutronDets = []
    neutronTimes = []
    nTTR = []
    pTTR = []
    for i in range(0,len(tailToTotalRatio)):
        if tailToTotalRatio[i] >= ttrArg:
            neutronADC += [adcVal[i]]
            neutronDets += [detectorData[i]]
            neutronTimes += [timeData[i]]
            nTTR += [tailToTotalRatio[i]]
        else:
            photonADC += [adcVal[i]]
            pTTR += [tailToTotalRatio[i]]

    neutronADC = np.asarray(neutronADC)
    neutronDets = np.asarray(neutronDets,dtype = 'int')
    neutronTimes = np.asarray(neutronTimes)
    photonADC = np.asarray(photonADC)
    nTTR = np.asarray(nTTR,dtype = 'float')
    pTTR = np.asarray(pTTR,dtype = 'float')
    plt.figure()
    plt.scatter(neutronADC,nTTR,c = 'r',label = 'neutrons')
    plt.scatter(photonADC,pTTR,c = 'b',label='photons')
    plt.xlabel('ADC Val')
    plt.ylabel('Tail to Total Ratio')
    plt.show()

#    a = 0
#    b = 0
#    c = 0
#    d = 0
#    e = 0
#    f = 0
    #numpy.savetxt("neutron.csv", neutronTailToTotalRatio, delimiter=",")
    #numpy.savetxt("photon.csv", photonTailToTotalRatio, delimiter=",")
#    histTTTPT = np.histogram(photonTailToTotalRatio,100000)

#    histPADC = np.histogram(photonADC,100000)
    #histTTTRT = photonTailToTotalRatio.hist(bins=100000)
#    a = histTTTPT[0]
#    b = histTTTPT[1]
#    c = b[0:100000]
#    a1 = histPADC[0]
#    b1 = histPADC[1]
#    c1 = b1[0:100000]

#    histTTT = np.histogram(neutronTailToTotalRatio,100000)
#    histNADC = np.histogram(neutronADC,100000)
    #histTTT = neutronTailToTotalRatio.hist(bins=100000)
#    d = histTTT[0]
#    e = histTTT[1]
#    f = e[0:100000]
#    d1 = histNADC[0]
#    e1 = histNADC[1]
#    f1 = e1[0:100000]

#    plt.figure(2)
#    plt.plot(a,c,'r',label='photons')
#    plt.plot(d,f,'b--',label='neutrons')
#    plt.xlabel('Counts')
#    plt.ylabel('Tail to Total Ratio')
#    plt.legend(loc='upper right')
#    plt.title(plane)
    #plt.plot(d,f)
#    plt.show()
#    eVal = slope*f1 + intercept
#    eValP = slope*c1 + intercept
#    plt.figure(3)
#    plt.plot(eValP,a1,'r',label='photons')
#    plt.plot(eVal,d1,'b--',label='neutrons')
#    plt.xlabel('Energy [keV]')
#    plt.ylabel('Counts')
#    plt.legend(loc='upper right')
#    plt.title(plane)
    #plt.plot(d,f)
#    plt.show()



    return neutronDets, neutronTimes, neutronADC

def PSDRT(ttr,timeData,detectorData,adcVal,ttrArg):
    import numpy as np
    import matplotlib.pyplot as plt
    import time
    #from numpy import *


    i = 0
    pulseIntegral = 0
    tailIntegral = 0
    totalIntegral = 0
    peakVal = 0
    peakTime = 0
    neutronTailToTotalRatio = []

    tailToTotalRatio = []
    #adcVal = []
    #ttrArg = 5
    neutronTailToTotalRatio = [i for i in ttr if i >= ttrArg]
    photonTailToTotalRatio = [i for i in ttr if 0 < i < ttrArg]

########################################################################################
### Sum up ADC values of pulse (integrate pulse) to put into neutron/photon category ###
########################################################################################

    neutronADC = []
    photonADC = []
    neutronDets = []
    neutronTimes = []
    nTTR = []
    pTTR = []
    L = [len(ttr), len(timeData), len(detectorData), len(adcVal)]
    for i in range(0,int(min(L))-1):
        if ttr[i] >= ttrArg:
            neutronADC += [adcVal[i]]
            neutronDets += [detectorData[i]]
            neutronTimes += [timeData[i]]
            nTTR += [ttr[i]]
#        else:
#            photonADC += [adcVal[i]]
#            pTTR += [tailToTotalRatio[i]]

    neutronDets = np.array(neutronDets,dtype = 'int')
    neutronTimes = np.array(neutronTimes, dtype = 'float')
    neutronADC = np.array(neutronADC, dtype = 'int')

#    photonADC = np.asarray(photonADC)
    nTTR = np.asarray(nTTR,dtype = 'float')




    return neutronDets, neutronTimes, neutronADC
