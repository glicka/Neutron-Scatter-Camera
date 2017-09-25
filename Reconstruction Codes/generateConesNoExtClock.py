#!/usr/bin/env python2
# -*- coding: utf-8 -*-
"""
Created on Wed Aug 16 10:31:57 2017

@author: aglick
"""

def generateConesNoExtClock(slope,intercept,plane1Dets,plane2Dets,plane1Times,plane2Times,plane1NeutronPulseADC,plane2NeutronPulseADC,tic):
    import csv
    import numpy as np
    import math
    import matplotlib.pyplot as plt
    import matplotlib
    import pylab as pl
    import time
    from mpl_toolkits.mplot3d import Axes3D
    from PIL import Image
    planeSeparation = 0.6096 #meters
    detectorSeparation = 0.0889 #meters
    u = detectorSeparation #meters
    D = planeSeparation #meters
    clockSpeed = 250*10**6 #Hz
    timeScale = 1/clockSpeed #seconds
    distance = []
    x1 = []
    x2 = []
    plane1Local = np.array([[0,0,0],[0,u,0],[0,2*u,0],[u,0,0],[u,u,0],[u,2*u,0],[2*u,0,0],[2*u,u,0],[2*u,2*u,0],[3*u,0,0],[3*u,u,0],[3*u,2*u,0]],dtype='float')
    plane2Local = np.array([[0,0,D],[0,u,D],[0,2*u,D],[u,0,D],[u,u,D],[u,2*u,D],[2*u,0,D],[2*u,u,D],[2*u,2*u,D],[3*u,0,D],[3*u,u,D],[3*u,2*u,D]],dtype='float')
    neutronEnergyTOF = []
    neutronEnergyADC = []
    neutronEnergy = []
    coneAngles = []
    coneVector = []
    mu = []
    weights = []
    cones = []
    b = []
    radii = 0
    sigma = 0.1
    iteration = 0
    area = (plane1Local[2,1]-plane1Local[0,1])*(plane1Local[10,0]-plane1Local[0,0])
    totalSphere = 4*math.pi*300**2
    geomCorr = totalSphere/area
    data1Mat = np.column_stack((tuple(plane1Dets),tuple(plane1Times),tuple(plane1NeutronPulseADC)))
    data1MatSort = data1Mat[data1Mat[:,0].argsort()[::1]]
    np.savetxt("data1MatSort.csv", data1MatSort, delimiter=",")
    plane1Dets = [column[0] for column in data1MatSort]
    plane1Times = [column[1] for column in data1MatSort]
    plane1NeutronPulseADC = [column[2] for column in data1MatSort]
    data2Mat = np.column_stack((tuple(plane2Dets),tuple(plane2Times),tuple(plane2NeutronPulseADC)))
    data2MatSort = data2Mat[data2Mat[:,0].argsort()[::1]]
    plane2Dets = [column[0] for column in data2MatSort]
    plane2Times = [column[1] for column in data2MatSort]
    plane2NeutronPulseADC = [column[2] for column in data2MatSort]
    plane1Dets = np.array(plane1Dets,dtype='int')
    plane1Dets = np.array(plane1Dets,dtype='int')
    plane2Dets = np.array(plane2Dets,dtype='int')
    plane2Dets = np.array(plane2Dets,dtype='int')
    plane2DetScale = []
    
    for i in range(0,len(plane2Dets)):
        if plane2Dets[i] == 12:
            plane2DetScale += [0]
        if plane2Dets[i] == 13:
            plane2DetScale += [1]
        if plane2Dets[i] == 14:
            plane2DetScale += [2]
        if plane2Dets[i] == 15:
            plane2DetScale += [3]
        if plane2Dets[i] == 16:
            plane2DetScale += [4]
        if plane2Dets[i] == 17:
            plane2DetScale += [5]
        if plane2Dets[i] == 18:
            plane2DetScale += [6]
        if plane2Dets[i] == 19:
            plane2DetScale += [7]
        if plane2Dets[i] == 20:
            plane2DetScale +=[8]
        if plane2Dets[i] == 21:
            plane2DetScale += [9]
        if plane2Dets[i] == 22:
            plane2DetScale += [10]
        if plane2Dets[i] == 23:
            plane2DetScale += [11]
    
    plane2DetScale = np.array(plane2DetScale,dtype = 'int')
    

#### Calculate neutron energy from time of flight between the 2 planes ####
    #tic = time.time()
    if len(plane1Times)>len(plane2Times):
        iteration = len(plane2Times)
    else:
        iteration = len(plane1Times)
        
    keepTrack = 0
    for i in range(0,iteration): #range(0,len(plane1Times))
        if i > 200 and i < iteration-101:
            for n in range(i-100,i+100):
                if plane2Times[n] - plane1Times[i] <= 125000 and plane2Times[n] - plane1Times[i] > 0:
                    temp = keepTrack
                    if 0 <= plane1Dets[i] <= 3 and 20 <= plane2Dets[n] <= 23:
                        x1 = plane1Local[plane1Dets[i]]
                        x2 = plane2Local[plane2DetScale[n]]
                        dist = np.sqrt((x2[0]-x1[0])**2 + (x2[1]-x1[1])**2 + (x2[2])**2)
                        distance += [dist]
                        timeSeparation = (plane2Times[n]-plane1Times[i])*timeScale
                        energy = (10**3)*(1/(1.602*10**(-13)))*0.5*(1.675*10**(-27))*(dist/timeSeparation)**2
                        neutronEnergyTOF += [energy] #keV
                        neutronEnergyADC += [slope*plane1NeutronPulseADC[i] + intercept]
                        coneAngles += [math.atan(math.sqrt((slope*plane1NeutronPulseADC[i] + intercept)/energy))]
                        mu += [np.cos(math.atan(math.sqrt((slope*plane1NeutronPulseADC[i] + intercept)/energy)))]
                        weights += [1/dist**2]
                        coneVector += [x1-x2]
                        if keepTrack == 0:
                            time1 = plane1Times[i]*timeScale
                        
                        keepTrack += 1
                        if keepTrack > temp:
                            time2 = plane1Times[keepTrack]*timeScale
                        break
                    elif 8 <= plane1Dets[i] <= 11 and 12 <= plane2Dets[n] <= 15:
                        x1 = plane1Local[plane1Dets[i]]
                        x2 = plane2Local[plane2DetScale[n]]
                        dist = np.sqrt((x2[0]-x1[0])**2 + (x2[1]-x1[1])**2 + (x2[2])**2)
                        distance += [dist]
                        timeSeparation = (plane2Times[n]-plane1Times[i])*timeScale
                        energy = (10**3)*(1/(1.602*10**(-13)))*0.5*(1.675*10**(-27))*(dist/timeSeparation)**2
                        neutronEnergyTOF += [energy] #keV
                        neutronEnergyADC += [slope*plane1NeutronPulseADC[i] + intercept]
                        coneAngles += [math.atan(math.sqrt((slope*plane1NeutronPulseADC[i] + intercept)/energy))]
                        mu += [np.cos(math.atan(math.sqrt((slope*plane1NeutronPulseADC[i] + intercept)/energy)))]
                        weights += [1/dist**2]
                        coneVector += [x1-x2]
                        break
                    elif 4 <= plane1Dets[i] <= 7 and 16 <= plane2Dets[n] <= 19:
                        x1 = plane1Local[plane1Dets[i]]
                        x2 = plane2Local[plane2DetScale[n]]
                        dist = np.sqrt((x2[0]-x1[0])**2 + (x2[1]-x1[1])**2 + (x2[2])**2)
                        distance += [dist]
                        timeSeparation = (plane2Times[n]-plane1Times[i])*timeScale
                        energy = (10**3)*(1/(1.602*10**(-13)))*0.5*(1.675*10**(-27))*(dist/timeSeparation)**2
                        neutronEnergyTOF += [energy] #keV
                        neutronEnergyADC += [slope*plane1NeutronPulseADC[i] + intercept]
                        coneAngles += [math.atan(math.sqrt((slope*plane1NeutronPulseADC[i] + intercept)/energy))]
                        mu += [np.cos(math.atan(math.sqrt((slope*plane1NeutronPulseADC[i] + intercept)/energy)))]
                        weights += [1/dist**2]
                        coneVector += [x1-x2]
                        break
                neutronEnergyTOF += [0] #keV
                neutronEnergyADC += [slope*plane1NeutronPulseADC[i] + intercept]
                    
        elif i<=200:
            for n in range(0,i+200):
#            if n%10000 == 0:
#                print('n = ',n)
                if plane2Times[n] - plane1Times[i] <= 125000 and plane2Times[n] - plane1Times[i] > 0:
                    if 0 <= plane1Dets[i] <= 3 and 20 <= plane2Dets[n] <= 23:
                        x1 = plane1Local[plane1Dets[i]]
                        x2 = plane2Local[plane2DetScale[n]]
                        dist = np.sqrt((x2[0]-x1[0])**2 + (x2[1]-x1[1])**2 + (x2[2])**2)
                        distance += [dist]
                        timeSeparation = (plane2Times[n]-plane1Times[i])*timeScale
                        energy = (10**3)*(1/(1.602*10**(-13)))*0.5*(1.675*10**(-27))*(dist/timeSeparation)**2
                        neutronEnergyTOF += [energy] #keV
                        neutronEnergyADC += [slope*plane1NeutronPulseADC[i] + intercept]
                        coneAngles += [math.atan(math.sqrt((slope*plane1NeutronPulseADC[i] + intercept)/energy))]
                        mu += [np.cos(math.atan(math.sqrt((slope*plane1NeutronPulseADC[i] + intercept)/energy)))]
                        weights += [1/dist**2]
                        if keepTrack == 0:
                            time1 = plane1Times[i]*timeScale
                            
                        keepTrack += 1
                        coneVector += [x1-x2]
                        break
                    elif 8 <= plane1Dets[i] <= 11 and 12 <= plane2Dets[n] <= 15:
                        x1 = plane1Local[plane1Dets[i]]
                        x2 = plane2Local[plane2DetScale[n]]
                        dist = np.sqrt((x2[0]-x1[0])**2 + (x2[1]-x1[1])**2 + (x2[2])**2)
                        distance += [dist]
                        timeSeparation = (plane2Times[n]-plane1Times[i])*timeScale
                        energy = (10**3)*(1/(1.602*10**(-13)))*0.5*(1.675*10**(-27))*(dist/timeSeparation)**2
                        neutronEnergyTOF += [energy] #keV
                        neutronEnergyADC += [slope*plane1NeutronPulseADC[i] + intercept]
                        coneAngles += [math.atan(math.sqrt((slope*plane1NeutronPulseADC[i] + intercept)/energy))]
                        mu += [np.cos(math.atan(math.sqrt((slope*plane1NeutronPulseADC[i] + intercept)/energy)))]
                        weights += [1/dist**2]
                        coneVector += [x1-x2]
                        break
                    elif 4 <= plane1Dets[i] <= 7 and 16 <= plane2Dets[n] <= 19:
                        x1 = plane1Local[plane1Dets[i]]
                        x2 = plane2Local[plane2DetScale[n]]
                        dist = np.sqrt((x2[0]-x1[0])**2 + (x2[1]-x1[1])**2 + (x2[2])**2)
                        distance += [dist]
                        timeSeparation = (plane2Times[n]-plane1Times[i])*timeScale
                        energy = (10**3)*(1/(1.602*10**(-13)))*0.5*(1.675*10**(-27))*(dist/timeSeparation)**2
                        neutronEnergyTOF += [energy] #keV
                        neutronEnergyADC += [slope*plane1NeutronPulseADC[i] + intercept]
                        coneAngles += [math.atan(math.sqrt((slope*plane1NeutronPulseADC[i] + intercept)/energy))]
                        mu += [np.cos(math.atan(math.sqrt((slope*plane1NeutronPulseADC[i] + intercept)/energy)))]
                        weights += [1/dist**2]
                        coneVector += [x1-x2]
                        break
                neutronEnergyTOF += [0] #keV
                neutronEnergyADC += [slope*plane1NeutronPulseADC[i] + intercept]
        if i%10000 == 0:
            toc = time.time()
            print('i = ',i)
            print('elapsed time = ',toc-tic, 's')
    distance = np.array(distance)
    neutronEnergyTOF = np.array(neutronEnergyTOF)
    #neutronEnergyTOF = neutronEnergyTOF*10**3 #keV
    neutronEnergyADC = np.array(neutronEnergyADC)
    neutronEnergy = [neutronEnergyTOF + neutronEnergyADC]
#    for i in range(0,len(neutronEnergyADC)):
#        if neutronEnergyTOF[i] > 0:
            #coneAngles += [math.degrees(math.atan(math.sqrt(neutronEnergyADC[i]/neutronEnergyTOF[i])))]
#            coneAngles += [math.atan(math.sqrt(neutronEnergyADC[i]/neutronEnergyTOF[i]))]
#            mu += [math.cosine(math.atan(math.sqrt(neutronEnergyADC[i]/neutronEnergyTOF[i])))]
    mu = np.array(mu)
    coneAngles = np.array(coneAngles)
    weights = np.array(weights)
    neutronEnergy = np.array(neutronEnergy,dtype='float')
    #### Create unit sphere here ####
    unitSphere = generateSphere(15)
    pixels = [] #np.zeros([len(unitSphere[:,0]),2])
    #size = len(unitSphere[:,0])
    #unitSphere.ravel()
    for n in range(0,len(unitSphere[:,0])):
        b = 0
        c = 0
        for i in range(0,len(coneAngles)):
            b += (1/(weights[i]*sigma*np.sqrt(2*math.pi)))*math.exp((np.dot(unitSphere[n,0],coneVector[i,0])-mu[i])**2/(2*sigma**2))
            c += (1/(weights[i]*sigma*np.sqrt(2*math.pi)))*math.exp((np.dot(unitSphere[n,1],coneVector[i,1])-mu[i])**2/(2*sigma**2))
        pixels += [[b,c]]
    #recon = [[b],[b]]
    #recon = np.array(recon,dtype='float')
#    for row, colcolor in zip(recon, colors):
#        pyplot.plot(2darray, column, "-", color=colcolor)

    pixels = np.array(pixels)
    plt.figure(1)
    plt.plot(b)
    plt.show()
    #img = Image.fromarray(b, 'RGB')
#    img.save('my.png')
    #img.show()

#    np.savetxt('GeneratedCones.csv',cones,delimiter=",")
    #ax.plot_surface(cones[0], Y, Z, cmap=plt.cm.YlGnBu_r)
    energyHist = np.histogram(neutronEnergy,100)
    a = energyHist[0]
    b1 = energyHist[1]
    c = b1[0:100]
    plt.figure(2)
    plt.plot(c,a,'b-')
    plt.xlabel('Neutron Energy [keV]')
    plt.ylabel('Counts')
    plt.title('Neutron Spectrum')
    plt.autoscale(enable=True,axis='x',tight=True)
    pl.xticks(rotation=45)
    #plt.legend(loc='upper right')
    #plt.plot(d,f)
    plt.show()
    
    flux = a/(area*geomCorr*(time2-time1))
    plt.figure(3)
    plt.plot(c,flux,'b-')
    plt.xlabel('Neutron Energy [keV]')
    plt.ylabel('Flux [Counts/cm^2s]')
    plt.title('Neutron Flux Spectrum')
    plt.autoscale(enable=True,axis='x',tight=True)
    pl.xticks(rotation=45)
    #plt.legend(loc='upper right')
    #plt.plot(d,f)
    plt.show()
    
    doseConversion = np.array([[260],[240],[220],[230],[240],[270],[280],[48],[14],[8.5],[7.0],[6.8],[6.8],[6.5],[6.1],[5.1],[3.6],[2.2],[1.6],[1.4]], dtype = 'float')
    energyVals = np.array([[2.5*10**(-6)],[1*10**(-5)],[1*10**(-4)],[1*10**(-3)],[1*10**(-2)],[1*10**(-1)],[1*10**(0)],[1*10**1],[5*10],[1*10**2],[2*10**2],[5*10**2],[10*10**2],[20*10**2],[50*10**2],[10**4],[2*10**4],[5*10**4],[1*10**5],[2*10**5],[3*10**3]],dtype = 'float')
    neutronDose = []
    for i in range(0,len(c)):
        for n in range(0,len(energyVals)-1):
            if energyVals[n+1] > c[i] > energyVals[n]:
                conv = doseConversion[n] + (c[i]-energyVals[n])*(doseConversion[n+1]-doseConversion[n])/(energyVals[n+1]-energyVals[n])
                neutronDose += [0.01*flux[i]/conv]
            elif energyVals[n] == c[i]:
                neutronDose += [0.01*flux[i]/doseConversion[n]]
            
            
    neutronDose = np.array(neutronDose,dtype = 'float')
    plt.figure(4)
    plt.plot(c,neutronDose,'b-')
    plt.xlabel('Neutron Energy [keV]')
    plt.ylabel('Dose [mSv/hr]')
    plt.title('Neutron Dose Rate for PuBe Source')
    plt.autoscale(enable=True,axis='x',tight=True)
    pl.xticks(rotation=45)
#    numpy.savetxt("neutronEnergy.csv", c, delimiter=",")
#    numpy.savetxt("neutronCounts.csv", a, delimiter=",")
    
    return
    