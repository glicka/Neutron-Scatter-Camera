#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Aug 22 11:10:23 2017

@author: aglick
"""

#testing script

import csv
import numpy as np
import math
import matplotlib.pyplot as plt
    #import plotly as py
import pylab


pulseIntegral = 0
tailIntegral = 0
peakVal = 0
peakTime = 0
i = 0
with open('NE204-09-21-2011-Cs137-LS-Signal.csv','r') as csvfile:
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
            peakVal, peakTime = findPeaks(row,3900)  
            #print(peakVal)
            pulseIntegral = integratePulse(row,3900)
            tailIntegral = integrateTail(row,3900,peakTime)
            #print 'pulseIntegral = ', pulseIntegral
            tailToTotalRatioTraining[i] = tailIntegral/float(pulseIntegral)
            
            if i%10000 == 0:
                print('i = ', i)
                print('pulseIntegral = ', pulseIntegral)
            #if i==0:
            #    print('peakTime = ', peakTime)
                
            i=i+1

pulseIntegral = 0
tailIntegral = 0
peakVal = 0
peakTime = 0
i = 0
with open('NE204-09-21-2011-PuBe-LSC-Signal.csv','r') as csvfile:
        neutronData = csv.reader(csvfile)
        #print 'photonTraining = ', photonTraining
        #map(int,photonTraining)
        #photonTraining1 = [int(x) for x in photonTraining]
        #reader = list(csv.DictReader(open(csvfile), delimiter='|'))
        numlines = len(open('NE204-09-21-2011-PuBe-LSC-Signal.csv').readlines())
        #numlines = len(csvfile.readlines())
        tailToTotalRatio = np.zeros((numlines,1))
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
            
            if i%10000 == 0:
                print('i = ', i)
                print('pulseIntegral = ', pulseIntegral)
            #if i==0:
            #    print('peakTime = ', peakTime)
                
            i=i+1

#print('tailToTotalRatioTraining = ', tailToTotalRatioTraining)
histTTTRT = np.histogram(tailToTotalRatioTraining,100000)
a = histTTTRT[0]
b = histTTTRT[1]
c = b[0:100000]
print('a = ', a)
print('c = ', c)
histTTT = np.histogram(tailToTotalRatio,100000)
d = histTTT[0]
e = histTTT[1]
f = b[0:100000]
print('d = ', d)
print('f = ', f)

#plt.figure(1)
#plt.hist(a,b)
#plt.show()
plt.figure(2)
plt.plot(a,c,'r',label='photons')
plt.plot(d,f,'b--',label='neutrons')
plt.xlabel('Counts')
plt.ylabel('Tail to Total Ratio')
plt.legend(loc='upper right')
#plt.plot(d,f)
plt.show()
