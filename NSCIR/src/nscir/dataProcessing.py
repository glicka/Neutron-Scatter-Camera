#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Jul 31 15:09:28 2017

@author: aglick
"""

def dataProcessing(datafile,photonDataFile):
    import h5py
    import numpy as np
    import matplotlib.pyplot as plt
    import pylab
    import time
    from nscir.generateCones import generateCones
    from nscir.PSD import PSD

#### Extract data here ####
    f = h5py.File(datafile, 'r')
    adcBoardKey = list(f.keys())[0]
    adcBoardVals = f[adcBoardKey]
    adcBoardVals = np.array(adcBoardVals)
    adcChannelKey = list(f.keys())[1]
    adcChannel = f[adcChannelKey]
    adcChannel = np.array(adcChannel)
    groupTimeVals = list(f.keys())[5]
    timeVals = f[groupTimeVals]
    timeVals = np.array(timeVals)
    groupKeyVal = list(f.keys())[4]
    rawData = f[groupKeyVal]
    rawDataMat = np.array(rawData,dtype='float')

#### Extract photon data here for ADC conversion ####
    f1 = h5py.File(photonDataFile, 'r')
    adcGammaBoardKey = list(f1.keys())[0]
    adcGammaBoardVals = f1[adcGammaBoardKey]
    adcGammaBoardVals = np.array(adcGammaBoardVals)
    adcGammaChannelKey = list(f1.keys())[1]
    adcGammaChannel = f1[adcGammaChannelKey]
    adcGammaChannel = np.array(adcGammaChannel)
    #groupTimeVals = list(f.keys())[5]
    #timeVals = f[groupTimeVals]
    #timeVals = np.array(timeVals)
    groupKeyValGamma = list(f1.keys())[4]
    rawGammaData = f1[groupKeyValGamma]
    rawGammaDataMat = np.array(rawGammaData,dtype='float')
#    detectorVal = []

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
    for i in range(0,len(adcBoardVals)):#10000):
#        tic = time.time()
        if adcBoardVals[i] == 5:
            if adcChannel[i] == 0:
                #detectorVal = detectorVal + [0]
                plane1Data += [rawDataMat[i,:]]
                plane1Times += [timeVals[i]]
                plane1Dets += [0]
                plane1PhotonData += [rawGammaDataMat[i,:]]
            elif adcChannel[i] == 1:
                #detectorVal = detectorVal + [1]
                plane1Data += [rawDataMat[i,:]]
                plane1Times += [timeVals[i]]
                plane1Dets += [1]
                plane1PhotonData += [rawGammaDataMat[i,:]]
            elif adcChannel[i] == 2:
                #detectorVal = detectorVal + [2]
                plane1Data += [rawDataMat[i,:]]
                plane1Times += [timeVals[i]]
                plane1Dets += [2]
                plane1PhotonData += [rawGammaDataMat[i,:]]
            elif adcChannel[i] == 3:
                #detectorVal = detectorVal + [3]
                plane1Data += [rawDataMat[i,:]]
                plane1Times += [timeVals[i]]
                plane1Dets += [3]
                plane1PhotonData += [rawGammaDataMat[i,:]]
            elif adcChannel[i] == 4:
                #detectorVal = detectorVal + [4]
                plane1Data += [rawDataMat[i,:]]
                plane1Times += [timeVals[i]]
                plane1Dets += [4]
                plane1PhotonData += [rawGammaDataMat[i,:]]
            elif adcChannel[i] == 5:
                #detectorVal = detectorVal + [5]
                plane1Data += [rawDataMat[i,:]]
                plane1Times += [timeVals[i]]
                plane1Dets += [5]
                plane1PhotonData += [rawGammaDataMat[i,:]]
            elif adcChannel[i] == 6:
                #detectorVal = detectorVal + [6]
                plane1Data += [rawDataMat[i,:]]
                plane1Times += [timeVals[i]]
                plane1Dets += [6]
                plane1PhotonData += [rawGammaDataMat[i,:]]
            elif adcChannel[i] == 7:
                #detectorVal = detectorVal + [7]
                plane1Data += [rawDataMat[i,:]]
                plane1Times += [timeVals[i]]
                plane1Dets += [7]
                plane1PhotonData += [rawGammaDataMat[i,:]]
        elif adcBoardVals[i] == 7:
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
        elif adcBoardVals[i] == 6:
            if adcChannel[i] == 0:
                #detectorVal = detectorVal + [8]
                plane1Data += [rawDataMat[i,:]]
                plane1Times += [timeVals[i]]
                plane1Dets += [8]
                plane1PhotonData += [rawGammaDataMat[i,:]]
            elif adcChannel[i] == 1:
                #detectorVal = detectorVal + [9]
                plane1Data += [rawDataMat[i,:]]
                plane1Times += [timeVals[i]]
                plane1Dets += [9]
                plane1PhotonData += [rawGammaDataMat[i,:]]
            elif adcChannel[i] == 2:
                #detectorVal = detectorVal + [10]
                plane1Data += [rawDataMat[i,:]]
                plane1Times += [timeVals[i]]
                plane1Dets += [10]
                plane1PhotonData += [rawGammaDataMat[i,:]]
            elif adcChannel[i] == 3:
                #detectorVal = detectorVal + [11]
                plane1Data += [rawDataMat[i,:]]
                plane1Times += [timeVals[i]]
                plane1Dets += [11]
                plane1PhotonData += [rawGammaDataMat[i,:]]
            elif adcChannel[i] == 4:
                #detectorVal = detectorVal + [12]
                plane2Data += [rawDataMat[i,:]]
                plane2Times += [timeVals[i]]
                plane2Dets += [12]
            elif adcChannel[i] == 5:
                #detectorVal = detectorVal + [13]
                plane2Data += [rawDataMat[i,:]]
                plane2Times += [timeVals[i]]
                plane2Dets += [13]
            elif adcChannel[i] == 6:
                #detectorVal = detectorVal + [14]
                plane2Data += [rawDataMat[i,:]]
                plane2Times += [timeVals[i]]
                plane2Dets += [14]
            elif adcChannel[i] == 7:
                #detectorVal = detectorVal + [15]
                plane2Data += [rawDataMat[i,:]]
                plane2Times += [timeVals[i]]
                plane2Dets += [15]
        if i%100000 == 0:
            print('k = ',i)
            toc = time.time()
#            print('tictoc = ',toc-tic)
            print('elapsed = ',toc-t1,'s')

#### Convert list into numpy array ####
    #detectorVal = np.array(detectorVal,dtype='float')
    plane1Data = np.array(plane1Data,dtype='float')
    plane2Data = np.array(plane2Data,dtype='float')
    plane1Times = np.array(plane1Times,dtype='float')
    plane2Times = np.array(plane2Times,dtype='float')
    plane1Dets = np.array(plane1Dets,dtype='int')
    plane2Dets = np.array(plane2Dets,dtype='int')
    plane1PhotonData = np.array(plane1PhotonData,dtype='float')



#### Create ADC to keV Conversion ####
    slope, intercept = adc2keV(plane1PhotonData)
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

    return

def dataProcessingRT(adc,ttr,modules,channels,timeVals):
    import h5py
    import numpy as np
    import matplotlib.pyplot as plt
    import pylab
    import time
    from nscir.imPlot import imPlotRT
    from nscir.PSD import PSDRT as PSD
    from nscir.imPlot import imPlotRT as imPlot
#### Extract data here ####
    #rawDataMat = np.array(waves,dtype='float')


#### Break up detectors into 1-24 based on adcChannel and adcBoard values ####
#### Separate data based on each plane of detectors ####
    plane1Data = []
    plane2Data = []
    plane1Times = []
    plane2Times = []
    plane1Dets = []
    plane2Dets = []
    plane1ADC = []
    plane2ADC = []
    t1 = time.time()
    for i in range(0,len(ttr)):#10000):
#        tic = time.time()
        if modules[i] == 0:
            if channels[i] == 0:
                #detectorVal = detectorVal + [0]
                plane1Data += [ttr[i]]
                plane1Times += [timeVals[i]]
                plane1Dets += [0]
                plane1ADC += [adc[i]]
            elif channels[i] == 1:
                #detectorVal = detectorVal + [1]
                plane1Data += [ttr[i]]
                plane1Times += [timeVals[i]]
                plane1Dets += [1]
                plane1ADC += [adc[i]]
            elif channels[i] == 2:
                #detectorVal = detectorVal + [2]
                plane1Data += [ttr[i]]
                plane1Times += [timeVals[i]]
                plane1Dets += [2]
                plane1ADC += [adc[i]]
            elif channels[i] == 3:
                #detectorVal = detectorVal + [3]
                plane1Data += [ttr[i]]
                plane1Times += [timeVals[i]]
                plane1Dets += [3]
                plane1ADC += [adc[i]]
            elif channels[i] == 4:
                #detectorVal = detectorVal + [4]
                plane1Data += [ttr[i]]
                plane1Times += [timeVals[i]]
                plane1Dets += [4]
                plane1ADC += [adc[i]]
            elif channels[i] == 5:
                #detectorVal = detectorVal + [5]
                plane1Data += [ttr[i]]
                plane1Times += [timeVals[i]]
                plane1Dets += [5]
                plane1ADC += [adc[i]]
            elif channels[i] == 6:
                #detectorVal = detectorVal + [6]
                plane1Data += [ttr[i]]
                plane1Times += [timeVals[i]]
                plane1Dets += [6]
                plane1ADC += [adc[i]]
            elif channels[i] == 7:
                #detectorVal = detectorVal + [7]
                plane1Data += [ttr[i]]
                plane1Times += [timeVals[i]]
                plane1Dets += [7]
                plane1ADC += [adc[i]]
            elif channels[i] == 8:
                #detectorVal = detectorVal + [4]
                plane1Data += [ttr[i]]
                plane1Times += [timeVals[i]]
                plane1Dets += [8]
                plane1ADC += [adc[i]]
            elif channels[i] == 9:
                #detectorVal = detectorVal + [5]
                plane1Data += [ttr[i]]
                plane1Times += [timeVals[i]]
                plane1Dets += [9]
                plane1ADC += [adc[i]]
            elif channels[i] == 10:
                #detectorVal = detectorVal + [6]
                plane1Data += [ttr[i]]
                plane1Times += [timeVals[i]]
                plane1Dets += [10]
                plane1ADC += [adc[i]]
            elif channels[i] == 11:
                #detectorVal = detectorVal + [7]
                plane1Data += [ttr[i]]
                plane1Times += [timeVals[i]]
                plane1Dets += [11]
                plane1ADC += [adc[i]]
            elif channels[i] == 12:
                #detectorVal = detectorVal + [5]
                plane2Data += [ttr[i]]
                plane2Times += [timeVals[i]]
                plane2Dets += [12]
                plane2ADC += [adc[i]]
            elif channels[i] == 13:
                #detectorVal = detectorVal + [6]
                plane2Data += [ttr[i]]
                plane2Times += [timeVals[i]]
                plane2Dets += [13]
                plane2ADC += [adc[i]]
            elif channels[i] == 14:
                #detectorVal = detectorVal + [7]
                plane2Data += [ttr[i]]
                plane2Times += [timeVals[i]]
                plane2Dets += [14]
                plane2ADC += [adc[i]]
            elif channels[i] == 15:
                #detectorVal = detectorVal + [4]
                plane2Data += [ttr[i]]
                plane2Times += [timeVals[i]]
                plane2Dets += [15]
                plane2ADC += [adc[i]]
        elif modules[i] == 1:
            if channels[i] == 0:
                #detectorVal = detectorVal + [16]
                plane2Data += [ttr[i]]
                plane2Times += [timeVals[i]]
                plane2Dets += [16]
                plane2ADC += [adc[i]]
            elif channels[i] == 1:
                #detectorVal = detectorVal + [17]
                plane2Data += [ttr[i]]
                plane2Times += [timeVals[i]]
                plane2Dets += [17]
                plane2ADC += [adc[i]]
            elif channels[i] == 2:
                #detectorVal = detectorVal + [18]
                plane2Data += [ttr[i]]
                plane2Times += [timeVals[i]]
                plane2Dets += [18]
                plane2ADC += [adc[i]]
            elif channels[i] == 3:
                #detectorVal = detectorVal + [19]
                plane2Data += [ttr[i]]
                plane2Times += [timeVals[i]]
                plane2Dets += [19]
                plane2ADC += [adc[i]]
            elif channels[i] == 4:
                #detectorVal = detectorVal + [20]
                plane2Data += [ttr[i]]
                plane2Times += [timeVals[i]]
                plane2Dets += [20]
                plane2ADC += [adc[i]]
            elif channels[i] == 5:
                #detectorVal = detectorVal + [21]
                plane2Data += [ttr[i]]
                plane2Times += [timeVals[i]]
                plane2Dets += [21]
                plane2ADC += [adc[i]]
            elif channels[i] == 6:
                #detectorVal = detectorVal + [22]
                plane2Data += [ttr[i]]
                plane2Times += [timeVals[i]]
                plane2Dets += [22]
                plane2ADC += [adc[i]]
            elif channels[i] == 7:
                #detectorVal = detectorVal + [23]
                plane2Data += [ttr[i]]
                plane2Times += [timeVals[i]]
                plane2Dets += [23]
                plane2ADC += [adc[i]]
        if i%500000 == 0:
            print('k = ',i)
            toc = time.time()
#            print('tictoc = ',toc-tic)
            print('elapsed = ',toc-t1,'s')

#### Convert list into numpy array ####
    #detectorVal = np.array(detectorVal,dtype='float')
    plane1Data = np.array(plane1Data,dtype='float')
    plane2Data = np.array(plane2Data,dtype='float')
    plane1Times = np.array(plane1Times,dtype='float')
    plane2Times = np.array(plane2Times,dtype='float')
    plane1Dets = np.array(plane1Dets,dtype='int')
    plane2Dets = np.array(plane2Dets,dtype='int')
    plane1ADC = np.array(plane1ADC,dtype='int')
    plane2ADC = np.array(plane2ADC,dtype='int')


#### Create ADC to keV Conversion ####
    #slope, intercept = adc2keV(plane1PhotonData)
#### Perform PSD for each plane of data to extract just neutron information ####
    plane1NeutronDets = []
    plane1NeutronTimes = []
    plane1NeutronPulseADC = []
    print('Performing PSD on Plane 1')
    plane1NeutronDets,plane1NeutronTimes, plane1NeutronPulseADC = PSD(plane1Data, plane1Times, plane1Dets,plane1ADC,5)

    plane2NeutronDets = []
    plane2NeutronTimes = []
    plane2NeutronPulseADC = []
    print('Performing PSD on Plane 2')
    plane2NeutronDets,plane2NeutronTimes, plane2NeutronPulseADC = PSD(plane2Data,plane2Times,plane2Dets,plane2ADC,1)

    data1Mat = np.column_stack((tuple(plane1NeutronDets),tuple(plane1NeutronTimes),tuple(plane1NeutronPulseADC)))
    data1MatSort = data1Mat[data1Mat[:,0].argsort()[::1]]
    #np.savetxt("data1MatSort.csv", data1MatSort, delimiter=",")
    plane1NeutronDetsSort = [column[0] for column in data1MatSort]
    plane1NeutronTimesSort = [column[1] for column in data1MatSort]
    plane1NeutronPulseADCSort = [column[2] for column in data1MatSort]

    data2Mat = np.column_stack((tuple(plane2NeutronDets),tuple(plane2NeutronTimes),tuple(plane2NeutronPulseADC)))
    data2MatSort = data2Mat[data2Mat[:,0].argsort()[::1]]
    #np.savetxt("data2MatSort.csv", data2MatSort, delimiter=",")
    plane2NeutronDetsSort = [column[0] for column in data2MatSort]
    plane2NeutronTimesSort = [column[1] for column in data2MatSort]
    plane2NeutronPulseADCSort = [column[2] for column in data2MatSort]

    plane1NeutronDetsSort = np.array(plane1NeutronDetsSort,dtype='int')
    plane2NeutronDetsSort = np.array(plane2NeutronDetsSort,dtype='int')

    plane1NeutronTimesSort = np.array(plane1NeutronTimesSort, dtype='float')
    plane2NeutronTimesSort = np.array(plane2NeutronTimesSort, dtype='float')

    plane1NeutronPulseADCSort = np.array(plane1NeutronPulseADCSort, dtype='int')
    plane2NeutronPulseADCSort = np.array(plane2NeutronPulseADCSort, dtype='int')


#### Generate cones and do energy reconstruction of neutrons ####
    newPix, latra, lonra = imPlot(plane1NeutronDetsSort,plane2NeutronDetsSort,plane1NeutronTimesSort,plane2NeutronTimesSort,plane1NeutronPulseADCSort,plane2NeutronPulseADCSort)
    return newPix, latra, lonra

def dataProcessingNoExtClock(datafile,photonDataFile,tic):
    import h5py
    import numpy as np
    import matplotlib.pyplot as plt
    import pylab
    import time
    from nscir.adc2keV import adc2keV
    from nscir.PSD import PSD
    from nscir.imPlot import generateConesNoExtClock
   # import adc2kev
  #  import PSD

#### Extract data here ####
    f = h5py.File(datafile, 'r')
    adcBoardKey = list(f.keys())[0]
    adcBoardVals = f[adcBoardKey]
    adcBoardVals = np.array(adcBoardVals)
    adcChannelKey = list(f.keys())[1]
    adcChannel = f[adcChannelKey]
    adcChannel = np.array(adcChannel)
    groupTimeVals = list(f.keys())[5]
    timeVals = f[groupTimeVals]
    timeVals = np.array(timeVals)
    groupKeyVal = list(f.keys())[4]
    rawData = f[groupKeyVal]
    rawDataMat = np.array(rawData,dtype='float')

#### Extract photon data here for ADC conversion ####
    #f1 = h5py.File(photonDataFile, 'r')
    #adcGammaBoardKey = list(f1.keys())[0]
    #adcGammaBoardVals = f1[adcGammaBoardKey]
    #adcGammaBoardVals = np.array(adcGammaBoardVals)
    #adcGammaChannelKey = list(f1.keys())[1]
    #adcGammaChannel = f1[adcGammaChannelKey]
    #adcGammaChannel = np.array(adcGammaChannel)
    #groupTimeVals = list(f.keys())[5]
    #timeVals = f[groupTimeVals]
    #timeVals = np.array(timeVals)
    #groupKeyValGamma = list(f1.keys())[4]
    #rawGammaData = f1[groupKeyValGamma]
    rawGammaDataMat = photonDataFile#np.array(photonDataFile,dtype='float')
#    detectorVal = []

#### Break up detectors into 1-24 based on adcChannel and adcBoard values ####
#### Separate data based on each plane of detectors ####
    plane1Data = []
    plane2Data = []
    plane1Times = []
    plane2Times = []
    plane1Dets = []
    plane2Dets = []
    plane1PhotonData = []
#    t1 = time.time()
    for i in range(0,len(adcBoardVals)):#10000):
#        tic = time.time()
        if adcBoardVals[i] == 5:
            if adcChannel[i] == 0:
                #detectorVal = detectorVal + [0]
                plane1Data += [rawDataMat[i,:]]#-np.mean(np.mean(rawDataMat[i,1:20]))]
                plane1Times += [timeVals[i]]
                plane1Dets += [0]
                #plane1PhotonData += [rawGammaDataMat[i,:]]
            elif adcChannel[i] == 1:
                #detectorVal = detectorVal + [1]
                plane1Data += [rawDataMat[i,:]]#-np.mean(np.mean(rawDataMat[i,1:20]))]
                plane1Times += [timeVals[i]]
                plane1Dets += [1]
                #plane1PhotonData += [rawGammaDataMat[i,:]]
            elif adcChannel[i] == 2:
                #detectorVal = detectorVal + [2]
                plane1Data += [rawDataMat[i,:]]#-np.mean(np.mean(rawDataMat[i,1:20]))]
                plane1Times += [timeVals[i]]
                plane1Dets += [2]
                #plane1PhotonData += [rawGammaDataMat[i,:]]
            elif adcChannel[i] == 3:
                #detectorVal = detectorVal + [3]
                plane1Data += [rawDataMat[i,:]]#-np.mean(np.mean(rawDataMat[i,1:20]))]
                plane1Times += [timeVals[i]]
                plane1Dets += [3]
                #plane1PhotonData += [rawGammaDataMat[i,:]]
            elif adcChannel[i] == 4:
                #detectorVal = detectorVal + [4]
                plane2Data += [rawDataMat[i,:]]#-np.mean(np.mean(rawDataMat[i,1:20]))]
                plane2Times += [timeVals[i]]
                plane2Dets += [20]
            elif adcChannel[i] == 5:
                #detectorVal = detectorVal + [5]
                plane2Data += [rawDataMat[i,:]]#-np.mean(np.mean(rawDataMat[i,1:20]))]
                plane2Times += [timeVals[i]]
                plane2Dets += [21]
            elif adcChannel[i] == 6:
                #detectorVal = detectorVal + [6]
                plane2Data += [rawDataMat[i,:]]#-np.mean(np.mean(rawDataMat[i,1:20]))]
                plane2Times += [timeVals[i]]
                plane2Dets += [22]
            elif adcChannel[i] == 7:
                #detectorVal = detectorVal + [7]
                plane2Data += [rawDataMat[i,:]]#-np.mean(np.mean(rawDataMat[i,1:20]))]
                plane2Times += [timeVals[i]]
                plane2Dets += [23]
        elif adcBoardVals[i] == 7:
            if adcChannel[i] == 0:
                #detectorVal = detectorVal + [16]
                plane2Data += [rawDataMat[i,:]]#-np.mean(np.mean(rawDataMat[i,1:20]))]
                plane2Times += [timeVals[i]]
                plane2Dets += [16]
            elif adcChannel[i] == 1:
                #detectorVal = detectorVal + [17]
                plane2Data += [rawDataMat[i,:]]#-np.mean(np.mean(rawDataMat[i,1:20]))]
                plane2Times += [timeVals[i]]
                plane2Dets += [17]
            elif adcChannel[i] == 2:
                #detectorVal = detectorVal + [18]
                plane2Data += [rawDataMat[i,:]]#-np.mean(np.mean(rawDataMat[i,1:20]))]
                plane2Times += [timeVals[i]]
                plane2Dets += [18]
            elif adcChannel[i] == 3:
                #detectorVal = detectorVal + [19]
                plane2Data += [rawDataMat[i,:]]#-np.mean(np.mean(rawDataMat[i,1:20]))]
                plane2Times += [timeVals[i]]
                plane2Dets += [19]
            elif adcChannel[i] == 4:
                #detectorVal = detectorVal + [20]
                plane1Data += [rawDataMat[i,:]]#-np.mean(np.mean(rawDataMat[i,1:20]))]
                plane1Times += [timeVals[i]]
                plane1Dets += [4]
                #plane1PhotonData += [rawGammaDataMat[i,:]]
            elif adcChannel[i] == 5:
                #detectorVal = detectorVal + [21]
                plane1Data += [rawDataMat[i,:]]#-np.mean(np.mean(rawDataMat[i,1:20]))]
                plane1Times += [timeVals[i]]
                plane1Dets += [5]
                #plane1PhotonData += [rawGammaDataMat[i,:]]
            elif adcChannel[i] == 6:
                #detectorVal = detectorVal + [22]
                plane1Data += [rawDataMat[i,:]]#-np.mean(np.mean(rawDataMat[i,1:20]))]
                plane1Times += [timeVals[i]]
                plane1Dets += [6]
                #plane1PhotonData += [rawGammaDataMat[i,:]]
            elif adcChannel[i] == 7:
                #detectorVal = detectorVal + [23]
                plane1Data += [rawDataMat[i,:]]#-np.mean(np.mean(rawDataMat[i,1:20]))]
                plane1Times += [timeVals[i]]
                plane1Dets += [7]
                #plane1PhotonData += [rawGammaDataMat[i,:]]
        elif adcBoardVals[i] == 6:
            if adcChannel[i] == 0:
                #detectorVal = detectorVal + [8]
                plane1Data += [rawDataMat[i,:]]#-np.mean(np.mean(rawDataMat[i,1:20]))]
                plane1Times += [timeVals[i]]
                plane1Dets += [8]
                #plane1PhotonData += [rawGammaDataMat[i,:]]
            elif adcChannel[i] == 1:
                #detectorVal = detectorVal + [9]
                plane1Data += [rawDataMat[i,:]]#-np.mean(np.mean(rawDataMat[i,1:20]))]
                plane1Times += [timeVals[i]]
                plane1Dets += [9]
                #plane1PhotonData += [rawGammaDataMat[i,:]]
            elif adcChannel[i] == 2:
                #detectorVal = detectorVal + [10]
                plane1Data += [rawDataMat[i,:]]#-np.mean(np.mean(rawDataMat[i,1:20]))]
                plane1Times += [timeVals[i]]
                plane1Dets += [10]
                #plane1PhotonData += [rawGammaDataMat[i,:]]
            elif adcChannel[i] == 3:
                #detectorVal = detectorVal + [11]
                plane1Data += [rawDataMat[i,:]]#-np.mean(np.mean(rawDataMat[i,1:20]))]
                plane1Times += [timeVals[i]]
                plane1Dets += [11]
                #plane1PhotonData += [rawGammaDataMat[i,:]]
            elif adcChannel[i] == 4:
                #detectorVal = detectorVal + [12]
                plane2Data += [rawDataMat[i,:]]#-np.mean(np.mean(rawDataMat[i,1:20]))]
                plane2Times += [timeVals[i]]
                plane2Dets += [12]
            elif adcChannel[i] == 5:
                #detectorVal = detectorVal + [13]
                plane2Data += [rawDataMat[i,:]]#-np.mean(np.mean(rawDataMat[i,1:20]))]
                plane2Times += [timeVals[i]]
                plane2Dets += [13]
            elif adcChannel[i] == 6:
                #detectorVal = detectorVal + [14]
                plane2Data += [rawDataMat[i,:]]#-np.mean(np.mean(rawDataMat[i,1:20]))]
                plane2Times += [timeVals[i]]
                plane2Dets += [14]
            elif adcChannel[i] == 7:
                #detectorVal = detectorVal + [15]
                plane2Data += [rawDataMat[i,:]]#-np.mean(np.mean(rawDataMat[i,1:20]))]
                plane2Times += [timeVals[i]]
                plane2Dets += [15]
        if i%100000 == 0:
            print('k = ',i)
            toc = time.time()
#            print('tictoc = ',toc-tic)
            print('elapsed = ',toc-tic,'s')

#### Convert list into numpy array ####
    #detectorVal = np.array(detectorVal,dtype='float')
    plane1Data = np.array(plane1Data,dtype='float')
    plane2Data = np.array(plane2Data,dtype='float')
    plane1Times = np.array(plane1Times,dtype='float')
    plane2Times = np.array(plane2Times,dtype='float')
    plane1Dets = np.array(plane1Dets,dtype='int')
    plane2Dets = np.array(plane2Dets,dtype='int')
    rowTest = [i for i in plane1Data[0,:] if i >= 0]
    rowTest = np.array(rowTest)
    rowTest = rowTest - np.average(rowTest[0:30])
    #plt.plot(plane1Data[0,:])
    plt.plot(rowTest)
    plt.show()
    #plane1PhotonData = np.array(plane1PhotonData,dtype='float')
#    print('plane1Data = ',plane1Data)
#    print('plane1Times = ',plane1Times)
#    print('plane1Dets = ',plane1Dets)

#    for i in range(0,len(adcBoardVals)):#10000):
#        if i%100000 == 0:
#            print('i = ',i)
#
#        if detectorVal[i] <= 11:
#            plane1Data = plane1Data + [rawDataMat[i,:]]
#            plane1Times = plane1Times + [timeVals[i]]
#            plane1Dets = plane1Dets + [11]
#        else:
#            plane2Data = plane2Data + [rawDataMat[i,:]]
#            plane2Times = plane2Times + [timeVals[i]]
#            plane2Dets = plane2Dets + [detectorVal[i]]
#### Convert list into numpy array ####
#    plane1Data = np.array(plane1Data,dtype='float')
#    plane2Data = np.array(plane2Data,dtype='float')
#    plane1Times = np.array(plane1Times,dtype='float')
#    plane2Times = np.array(plane2Times,dtype='float')
#    plane1Dets = np.array(plane1Dets,dtype='int')
#    plane2Dets = np.array(plane2Dets,dtype='int')

    print('Creating ADC Conversion')
    toc = time.time()
#            print('tictoc = ',toc-tic)
    print('elapsed = ',toc-tic,'s')
    slope, intercept = adc2keV(rawGammaDataMat)
#### Perform PSD for each plane of data to extract just neutron information ####
    print('Performing PSD on Plane 1')
    toc = time.time()
    print('elapsed = ',toc-tic,'s')
    plane1NeutronDets,plane1NeutronTimes,plane1NeutronPulseADC = PSD(plane1Dets,plane1Times,plane1Data,'Plane 1',tic)
    print('Performing PSD on Plane 2')
    toc = time.time()
    print('elapsed = ',toc-tic,'s')
    plane2NeutronDets,plane2NeutronTimes,plane2NeutronPulseADC = PSD(plane2Dets,plane2Times,plane2Data,'Plane 2',tic)
#    np.savetxt("plane1NeutronDets.csv", plane1NeutronDets, delimiter=",")
#    np.savetxt("plane2NeutronDets.csv", plane2NeutronDets, delimiter=",")
#    np.savetxt("plane1NeutronTimes.csv", plane1NeutronTimes, delimiter=",")
#    np.savetxt("plane2NeutronTimes.csv", plane2NeutronTimes, delimiter=",")
#    np.savetxt("plane1NeutronPulseADC.csv", plane1NeutronPulseADC, delimiter=",")
#    np.savetxt("plane2NeutronPulseADC.csv", plane2NeutronPulseADC, delimiter=",")
#    print('length of plane1NeutronDets: ',len(plane1NeutronDets))
#    print('length of plane1NeutronTimes: ',len(plane1NeutronTimes))
#    print('length of neutronPulseData1: ',len(neutronPulseData1[:,0]))
#    print('length of plane2NeutronDets: ',len(plane2NeutronDets))
#    print('length of plane2NeutronTimes: ',len(plane2NeutronTimes))
#    print('length of neutronPulseData2: ',len(neutronPulseData2[:,0]))
#### Generate cones and do energy reconstruction of neutrons ####

    print('Performing Energy Reconstruction and Cone Generation')
    #toc = time.time()
#            print('tictoc = ',toc-tic)
    print('elapsed = ',toc-tic,'s')
    neutronEnergy = generateConesNoExtClock(slope,intercept,plane1NeutronDets,plane2NeutronDets,plane1NeutronTimes,plane2NeutronTimes,plane1NeutronPulseADC,plane2NeutronPulseADC,tic)
    print('elapsed = ',toc-tic,'s')
#    print('Calculating Absorbed Dose')
#    kFactor = calculateAbsorbedDose(neutronEnergy,tic)

    print('elapsed = ',toc-tic,'s')

    return
