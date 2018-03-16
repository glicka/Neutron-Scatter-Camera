#!/usr/bin/env python2
# -*- coding: utf-8 -*-
"""
Created on Mon Jul 31 15:09:28 2017

@author: aglick
"""

def neutronProcessing(rawDataMat,timeVals,detData,slope,intercept):
    import h5py
    import numpy as np
    import matplotlib.pyplot as plt
    import pylab
    import time
    from nscir.generateCones import generateCones
    from nscir.PSD import PSD

#### Break up detectors into 1-24 based on adcChannel and adcBoard values ####
#### Separate data based on each plane of detectors ####
    plane1Data = []
    plane2Data = []
    plane1Times = []
    plane2Times = []
    plane1Dets = []
    plane2Dets = []
    plane1PhotonData = []
    t1 = time.time()

#### adcBoardVals and adcChannel variables need to be changed depending on parsed format
    for i in range(0,len(detData)):#10000):
#        tic = time.time()
        if adcBoardVals[i] == 1:
            if adcChannel[i] == 0:
                #detectorVal = detectorVal + [0]
                plane1Data += [rawDataMat[i,:]]
                plane1Times += [timeVals[i]]
                plane1Dets += [0]
            elif adcChannel[i] == 1:
                #detectorVal = detectorVal + [1]
                plane1Data += [rawDataMat[i,:]]
                plane1Times += [timeVals[i]]
                plane1Dets += [1]
            elif adcChannel[i] == 2:
                #detectorVal = detectorVal + [2]
                plane1Data += [rawDataMat[i,:]]
                plane1Times += [timeVals[i]]
                plane1Dets += [2]
            elif adcChannel[i] == 3:
                #detectorVal = detectorVal + [3]
                plane1Data += [rawDataMat[i,:]]
                plane1Times += [timeVals[i]]
                plane1Dets += [3]
            elif adcChannel[i] == 4:
                #detectorVal = detectorVal + [4]
                plane1Data += [rawDataMat[i,:]]
                plane1Times += [timeVals[i]]
                plane1Dets += [4]
            elif adcChannel[i] == 5:
                #detectorVal = detectorVal + [5]
                plane1Data += [rawDataMat[i,:]]
                plane1Times += [timeVals[i]]
                plane1Dets += [5]
            elif adcChannel[i] == 6:
                #detectorVal = detectorVal + [6]
                plane1Data += [rawDataMat[i,:]]
                plane1Times += [timeVals[i]]
                plane1Dets += [6]
            elif adcChannel[i] == 7:
                #detectorVal = detectorVal + [7]
                plane1Data += [rawDataMat[i,:]]
                plane1Times += [timeVals[i]]
                plane1Dets += [7]
            if adcChannel[i] == 8:
                #detectorVal = detectorVal + [8]
                plane1Data += [rawDataMat[i,:]]
                plane1Times += [timeVals[i]]
                plane1Dets += [8]
            elif adcChannel[i] == 9:
                #detectorVal = detectorVal + [9]
                plane1Data += [rawDataMat[i,:]]
                plane1Times += [timeVals[i]]
                plane1Dets += [9]
            elif adcChannel[i] == 10:
                #detectorVal = detectorVal + [10]
                plane1Data += [rawDataMat[i,:]]
                plane1Times += [timeVals[i]]
                plane1Dets += [10]
            elif adcChannel[i] == 11:
                #detectorVal = detectorVal + [11]
                plane1Data += [rawDataMat[i,:]]
                plane1Times += [timeVals[i]]
                plane1Dets += [11]
            elif adcChannel[i] == 12:
                #detectorVal = detectorVal + [12]
                plane2Data += [rawDataMat[i,:]]
                plane2Times += [timeVals[i]]
                plane2Dets += [12]
            elif adcChannel[i] == 13:
                #detectorVal = detectorVal + [13]
                plane2Data += [rawDataMat[i,:]]
                plane2Times += [timeVals[i]]
                plane2Dets += [13]
            elif adcChannel[i] == 14:
                #detectorVal = detectorVal + [14]
                plane2Data += [rawDataMat[i,:]]
                plane2Times += [timeVals[i]]
                plane2Dets += [14]
            elif adcChannel[i] == 15:
                #detectorVal = detectorVal + [15]
                plane2Data += [rawDataMat[i,:]]
                plane2Times += [timeVals[i]]
                plane2Dets += [15]
        elif adcBoardVals[i] == 2:
            if adcChannel[i] == 0:
                #detectorVal = detectorVal + [16]
                plane2Data += [rawDataMat[i,:]]
                plane2Times += [timeVals[i]]
                plane2Dets += [16]
            elif adcChannel[i] == 1:
                #detectorVal = detectorVal + [17]
                plane2Data += [rawDataMat[i,:]]
                plane2Times += [timeVals[i]]
                plane2Dets += [17]
            elif adcChannel[i] == 2:
                #detectorVal = detectorVal + [18]
                plane2Data += [rawDataMat[i,:]]
                plane2Times += [timeVals[i]]
                plane2Dets += [18]
            elif adcChannel[i] == 3:
                #detectorVal = detectorVal + [19]
                plane2Data += [rawDataMat[i,:]]
                plane2Times += [timeVals[i]]
                plane2Dets += [19]
            elif adcChannel[i] == 4:
                #detectorVal = detectorVal + [20]
                plane2Data += [rawDataMat[i,:]]
                plane2Times += [timeVals[i]]
                plane2Dets += [20]
            elif adcChannel[i] == 5:
                #detectorVal = detectorVal + [21]
                plane2Data += [rawDataMat[i,:]]
                plane2Times += [timeVals[i]]
                plane2Dets += [21]
            elif adcChannel[i] == 6:
                #detectorVal = detectorVal + [22]
                plane2Data += [rawDataMat[i,:]]
                plane2Times += [timeVals[i]]
                plane2Dets += [22]
            elif adcChannel[i] == 7:
                #detectorVal = detectorVal + [23]
                plane2Data += [rawDataMat[i,:]]
                plane2Times += [timeVals[i]]
                plane2Dets += [23]

        if i%100000 == 0:
            print('k = ',i)
            toc = time.time()
#            print('tictoc = ',toc-tic)
            print('elapsed = ',toc-t1,'s')

#### Convert list into numpy array ####
    #detectorVal = np.array(detectorVal,dtype='float')
    plane1Data = np.array(plane1Data,dtype='float')
    plane1Data = plane1Data - np.average(plane1Data[0:30])
    plane2Data = np.array(plane2Data,dtype='float')
    plane2Data = plane2Data - np.average(plane2Data[0:30])
    plane1Times = np.array(plane1Times,dtype='float')
    plane2Times = np.array(plane2Times,dtype='float')
    plane1Dets = np.array(plane1Dets,dtype='int')
    plane2Dets = np.array(plane2Dets,dtype='int')
    plane1PhotonData = np.array(plane1PhotonData,dtype='float')


#### Create ADC to keV Conversion ####
    #slope, intercept = adc2keV(plane1PhotonData)
#### Perform PSD for each plane of data to extract just neutron information ####
    print('Performing PSD on Plane 1')
    plane1NeutronDets,plane1NeutronTimes,plane1NeutronPulseADC = PSD(plane1Dets,plane1Times,plane1Data,'Plane 1')
    print('Performing PSD on Plane 2')
    plane2NeutronDets,plane2NeutronTimes,plane2NeutronPulseADC = PSD(plane2Dets,plane2Times,plane2Data,'Plane 2')
    np.savetxt("plane1NeutronDets.csv", plane1NeutronDets, delimiter=",")
    np.savetxt("plane2NeutronDets.csv", plane2NeutronDets, delimiter=",")
    np.savetxt("plane1NeutronTimes.csv", plane1NeutronTimes, delimiter=",")
    np.savetxt("plane2NeutronTimes.csv", plane2NeutronTimes, delimiter=",")
    np.savetxt("plane1NeutronPulseADC.csv", plane1NeutronPulseADC, delimiter=",")
    np.savetxt("plane2NeutronPulseADC.csv", plane2NeutronPulseADC, delimiter=",")

    data1Mat = np.column_stack((tuple(plane1NeutronDets),tuple(plane1NeutronTimes),tuple(plane1NeutronPulseADC)))
    data1MatSort = data1Mat[data1Mat[:,0].argsort()[::1]]
    #np.savetxt("data1MatSort.csv", data1MatSort, delimiter=",")
    plane1DetsSort = [column[0] for column in data1MatSort]
    plane1TimesSort = [column[1] for column in data1MatSort]
    plane1NeutronPulseADCSort = [column[2] for column in data1MatSort]
    data2Mat = np.column_stack((tuple(plane2Dets),tuple(plane2Times),tuple(plane2NeutronPulseADC)))
    data2MatSort = data2Mat[data2Mat[:,0].argsort()[::1]]
    plane2DetsSort = [column[0] for column in data2MatSort]
    plane2TimesSort = [column[1] for column in data2MatSort]
    plane2NeutronPulseADCSort = [column[2] for column in data2MatSort]
    plane1DetsSort = np.array(plane1DetsSort,dtype='int')
    plane1DetsSort = np.array(plane1DetsSort,dtype='int')
    plane2DetsSort = np.array(plane2DetsSort,dtype='int')
    plane2DetsSort = np.array(plane2DetsSort,dtype='int')
    plane2DetScale = []

#### Generate cones and do energy reconstruction of neutrons ####

    cones = generateCones(slope,intercept,plane1NeutronDetsSort,plane2NeutronDetsSort,plane1NeutronTimesSort,plane2NeutronTimesSort,plane1NeutronPulseADCSort,plane2NeutronPulseADCSort)
