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
    
    MeV = []
    index1 = 0
    index2 = 0
    index3 = 0
    index4 = 0
    histNADC = np.histogram(adcPlot,100000)
    d1 = histNADC[0]
    e1 = histNADC[1]
    f1 = e1[0:100000]
    #plt.figure(1)
    #plt.plot(f1,d1,'b--',label='neutrons')
    #plt.xlabel('ADC Val')
    #plt.ylabel('Counts')
    #plt.legend(loc='upper right')
    #plt.title(plane)
    #plt.plot(d,f)
    plt.show()
    #Cs = heapq.nlargest(1,range(125000,len(f1)),key=f1.__getitem__)
    #Co1 = heapq.nlargest(1,range(250000,len(f1)),key=f1.__getitem__)
    #Co2 = heapq.nlargest(1,range(315000,len(f1)),key=f1.__getitem__)
    #f1 = np.around(f1)
    #f1 = np.array(f1,dtype='int')
    #print(f1)
    index1 = (np.abs(f1 - 12500)).argmin()
    index2 = (np.abs(f1 - 25000)).argmin()
    index3 = (np.abs(f1 - 35000)).argmin()
    index4 = (np.abs(f1 - 40000)).argmin()

    Cs = np.argmax(f1[index1:index2])
    Co1 = np.argmax(f1[index2:index3])
    Co2 = np.argmax(f1[index3:index4])
    #for i in range(0,len(d1)):
    y = np.array([662,1173,1332])
    x = np.array([Cs,Co1,Co2])
    #x = np.array(x)
    #m, b = np.polyfit(x, y, 1)

    #plt.plot(x, y, '.')
    #plt.plot(x, m*x + b, '-')


    X = np.random.rand(100)
    Y = X + np.random.rand(100)*0.1

    results = sm.OLS(y,sm.add_constant(x)).fit()

    #print(results.summary())


    slope, intercept = np.polyfit(x, y, 1)
    
    abline_values = [slope * i + intercept for i in x]
    plt.plot(x, y, 'ro')
    plt.plot(x, abline_values, 'b')
    plt.title('Best Fit Line')
    plt.show()

    plt.show()

    
    return slope, intercept
    