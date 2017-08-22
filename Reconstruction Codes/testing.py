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
histTTT = np.histogram(tailToTotalRatioTraining,100000)
a = histTTT[0]
b = histTTT[1]
c = b[0:100000]
print('a = ', a)
print('b = ', b)
#plt.figure(1)
#plt.hist(a,b)
#plt.show()
plt.figure(2)
plt.plot(a,c)
plt.show()
