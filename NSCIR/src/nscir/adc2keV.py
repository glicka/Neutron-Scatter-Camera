#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Aug 31 11:29:52 2017

@author: aglick
"""

def adc2keV(adcPlot):
    import numpy as np
    import time
    import heapq
    import statsmodels.api as sm
    import numpy as np
    import matplotlib.pyplot as plt
    from nscir.integratePulse import integratePulse

    MeV = []
    index1 = 0
    index2 = 0
    index3 = 0
    index4 = 0
    adcVal = []
    i = 0
    for row in adcPlot:
#        peakVal, peakTime = max(enumerate(row), key=operator.itemgetter(1)) #findPeaks(row)
        #print('temp = ',temp)
        #print(row)
        peakTime = row.argmax()
        pulseIntegral = integratePulse(row,peakTime)
        #tailIntegral = integrateTail(row,peakTime)
        #tailToTotalRatio += [tailIntegral/float(pulseIntegral)]
        adcVal += [pulseIntegral]


    adcVal = np.asarray(adcVal,dtype='float')
    histNADC = np.histogram(adcVal,100000)
    d1 = histNADC[0]
    e1 = histNADC[1]
    f1 = e1[0:100000]
    plt.figure(1)
    plt.plot(f1,d1,'b-',label='Cs Plot')
    plt.xlabel('ADC Val')
    plt.ylabel('Counts')
    plt.legend(loc='upper right')
    plt.title('Cs-137 Plot')
    #plt.plot(d,f)
    plt.show()
    #Cs = heapq.nlargest(1,range(125000,len(f1)),key=f1.__getitem__)
    #Co1 = heapq.nlargest(1,range(250000,len(f1)),key=f1.__getitem__)
    #Co2 = heapq.nlargest(1,range(315000,len(f1)),key=f1.__getitem__)
    #f1 = np.around(f1)
    #f1 = np.array(f1,dtype='int')
    #print(f1)
    index1 = (np.abs(f1 - 30000)).argmin()
    index2 = (np.abs(f1 - 50000)).argmin()
    index3 = (np.abs(f1 - 100000)).argmin()
    #index4 = (np.abs(f1 - 400000)).argmin()
    CsCompton = np.argmax(f1[index1:index2])
    Cs = np.argmax(f1[index2:index3])
    #for i in range(0,len(d1)):
    y = np.array([477.7,662])
    x = np.array([f1[CsCompton],f1[Cs]])
    #x = np.array(x)
    #m, b = np.polyfit(x, y, 1)

    #plt.plot(x, y, '.')
    #plt.plot(x, m*x + b, '-')


    #X = np.random.rand(100)
    #Y = X + np.random.rand(100)*0.1

    results = sm.OLS(y,sm.add_constant(x)).fit()

    #print(results.summary())


    slope, intercept = np.polyfit(x, y, 1)

    abline_values = [slope * i + intercept for i in x]
    plt.plot(x, y, 'ro')
    plt.plot(x, abline_values, 'b')
    plt.xlabel('ADC Val')
    plt.ylabel('Energy [keV]')
    plt.title('Best Fit Line')
    plt.show()


#    plt.show()


    return slope, intercept
