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
    import healpy as hp
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
#    cones = []
    b = 0
    time1 = []
#    radii = 0
    sigma = 0.045
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
                    #temp = keepTrack
                    if 0 <= plane1Dets[i] <= 3 and 20 <= plane2Dets[n] <= 23:
                        x1 = plane1Local[plane1Dets[i]]
                        x2 = plane2Local[plane2DetScale[n]]
                        dist = np.sqrt((x2[0]-x1[0])**2 + (x2[1]-x1[1])**2 + (x2[2])**2)
                        distance += [dist]
                        timeSeparation = (plane2Times[n]-plane1Times[i])*timeScale
                        energy = (10**3)*(1/(1.602*10**(-13)))*0.5*(1.675*10**(-27))*(dist/timeSeparation)**2
                        energyADC = slope*plane1NeutronPulseADC[i] + intercept
                        energyTotal = energyADC + energy
                        neutronEnergyTOF += [energy] #keV
                        neutronEnergyADC += [energyADC] #keV
                        #print('angle = ',np.deg2rad(math.sqrt((slope*plane1NeutronPulseADC[i] + intercept)/energyTotal)))
                        coneAngles += [math.asin(np.deg2rad(math.sqrt((slope*plane1NeutronPulseADC[i] + intercept)/energyTotal)))]
                        mu += [np.cos(math.asin(np.deg2rad(math.sqrt((slope*plane1NeutronPulseADC[i] + intercept)/energyTotal))))]
                        weights += [1/dist**2]
                        coneVector += [x1-x2]
                        #if keepTrack == 0:
                        time1 += [plane1Times[i]*timeScale]
                        time1 += [plane2Times[n]*timeScale]
                        
                        #keepTrack += 1
                        #if keepTrack > temp:
                        #    time2 = plane1Times[keepTrack]*timeScale
                        break
                    elif 8 <= plane1Dets[i] <= 11 and 12 <= plane2Dets[n] <= 15:
                        x1 = plane1Local[plane1Dets[i]]
                        x2 = plane2Local[plane2DetScale[n]]
                        dist = np.sqrt((x2[0]-x1[0])**2 + (x2[1]-x1[1])**2 + (x2[2])**2)
                        distance += [dist]
                        timeSeparation = (plane2Times[n]-plane1Times[i])*timeScale
                        energy = (10**3)*(1/(1.602*10**(-13)))*0.5*(1.675*10**(-27))*(dist/timeSeparation)**2
                        energyADC = slope*plane1NeutronPulseADC[i] + intercept
                        energyTotal = energyADC + energy
                        neutronEnergyTOF += [energy] #keV
                        neutronEnergyADC += [energyADC] #keV
                        #print('angle = ',np.deg2rad(math.sqrt((slope*plane1NeutronPulseADC[i] + intercept)/energyTotal)))
                        coneAngles += [math.asin(np.deg2rad(math.sqrt((slope*plane1NeutronPulseADC[i] + intercept)/energyTotal)))]
                        mu += [np.cos(math.asin(np.deg2rad(math.sqrt((slope*plane1NeutronPulseADC[i] + intercept)/energyTotal))))]
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
                        energyADC = slope*plane1NeutronPulseADC[i] + intercept
                        energyTotal = energyADC + energy
                        neutronEnergyTOF += [energy] #keV
                        neutronEnergyADC += [energyADC] #keV
                        #print('angle = ',np.deg2rad(math.sqrt((slope*plane1NeutronPulseADC[i] + intercept)/energyTotal)))
                        coneAngles += [math.asin(np.deg2rad(math.sqrt((slope*plane1NeutronPulseADC[i] + intercept)/energyTotal)))]
                        mu += [np.cos(math.asin(np.deg2rad(math.sqrt((slope*plane1NeutronPulseADC[i] + intercept)/energyTotal))))]
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
                        energyADC = slope*plane1NeutronPulseADC[i] + intercept
                        energyTotal = energyADC + energy
                        neutronEnergyTOF += [energy] #keV
                        neutronEnergyADC += [energyADC] #keV
                        #print('angle = ',np.deg2rad(math.sqrt((slope*plane1NeutronPulseADC[i] + intercept)/energyTotal)))
                        coneAngles += [math.asin(np.deg2rad(math.sqrt((slope*plane1NeutronPulseADC[i] + intercept)/energyTotal)))]
                        mu += [np.cos(math.asin(np.deg2rad(math.sqrt((slope*plane1NeutronPulseADC[i] + intercept)/energyTotal))))]
                        weights += [1/dist**2]
                        #if keepTrack == 0:
                        time1 += [plane1Times[i]*timeScale]
                        time1 += [plane2Times[n]*timeScale]
                        #keepTrack += 1
                        coneVector += [x1-x2]
                        break
                    elif 8 <= plane1Dets[i] <= 11 and 12 <= plane2Dets[n] <= 15:
                        x1 = plane1Local[plane1Dets[i]]
                        x2 = plane2Local[plane2DetScale[n]]
                        dist = np.sqrt((x2[0]-x1[0])**2 + (x2[1]-x1[1])**2 + (x2[2])**2)
                        distance += [dist]
                        timeSeparation = (plane2Times[n]-plane1Times[i])*timeScale
                        energy = (10**3)*(1/(1.602*10**(-13)))*0.5*(1.675*10**(-27))*(dist/timeSeparation)**2
                        energyADC = slope*plane1NeutronPulseADC[i] + intercept
                        energyTotal = energyADC + energy
                        neutronEnergyTOF += [energy] #keV
                        neutronEnergyADC += [energyADC] #keV
                        #print('angle = ',np.deg2rad(math.sqrt((slope*plane1NeutronPulseADC[i] + intercept)/energyTotal)))
                        coneAngles += [math.asin(np.deg2rad(math.sqrt((slope*plane1NeutronPulseADC[i] + intercept)/energyTotal)))]
                        mu += [np.cos(math.asin(np.deg2rad(math.sqrt((slope*plane1NeutronPulseADC[i] + intercept)/energyTotal))))]
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
                        energyADC = slope*plane1NeutronPulseADC[i] + intercept
                        energyTotal = energyADC + energy
                        neutronEnergyTOF += [energy] #keV
                        neutronEnergyADC += [energyADC] #keV
                        #print('angle = ',np.deg2rad(math.sqrt((slope*plane1NeutronPulseADC[i] + intercept)/energyTotal)))
                        coneAngles += [math.asin(np.deg2rad(math.sqrt((slope*plane1NeutronPulseADC[i] + intercept)/energyTotal)))]
                        mu += [np.cos(math.asin(np.deg2rad(math.sqrt((slope*plane1NeutronPulseADC[i] + intercept)/energyTotal))))]
                        weights += [1/dist**2]
                        coneVector += [x1-x2]
                        break
                neutronEnergyTOF += [0] #keV
                neutronEnergyADC += [slope*plane1NeutronPulseADC[i] + intercept]
        if i%10000 == 0:
            toc = time.time()
            print('i = ',i)
            print('elapsed time = ',toc-tic, 's')

######################################################################################
####                  make lists into numpy arrays                                ####  
######################################################################################
    distance = np.array(distance)
    neutronEnergyTOF = np.array(neutronEnergyTOF)
    #neutronEnergyTOF = neutronEnergyTOF*10**3 #keV
    neutronEnergyADC = np.array(neutronEnergyADC)
    neutronEnergy = [neutronEnergyTOF + neutronEnergyADC]
    coneVector = np.array(coneVector,dtype = 'float')
    mu = np.array(mu)
    coneAngles = np.array(coneAngles)
    weights = np.array(weights)
    neutronEnergy = np.array(neutronEnergy,dtype='float')
    time1 = np.array(time1,dtype = 'float')
    time1.sort()
#######################################################################################
####              create unit vector for cones                                     ####  
#######################################################################################
    unitNorm = 0
    unitVector = []
    for i in range(0,len(coneVector[:,0])):
        temp = coneVector[i,:]
        unitNorm = np.linalg.norm(temp)
        unitVector += [temp/unitNorm]

    unitVector = np.array(unitVector, dtype = 'float')


#######################################################################################
####                    plot energy spectrum                                       ####  
#######################################################################################
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
    

#######################################################################################
####                    plot flux spectrum                                         ####  
#######################################################################################
    plt.figure()
    flux = a/(area*geomCorr*(time1[len(time1)-1]-time1[0]))
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

########################################################################################
####         generate and plot neutron dose spectrum                                ####  
########################################################################################
    doseConversion = np.array([[260],[240],[220],[230],[240],[270],[280],[48],[14],[8.5],[7.0],[6.8],[6.8],[6.5],[6.1],[5.1],[3.6],[2.2],[1.6],[1.4]], dtype = 'float')
    energyVals = np.array([[2.5*10**(-6)],[1*10**(-5)],[1*10**(-4)],[1*10**(-3)],[1*10**(-2)],[1*10**(-1)],[1*10**(0)],[1*10**1],[5*10],[1*10**2],[2*10**2],[5*10**2],[10*10**2],[20*10**2],[50*10**2],[10**4],[2*10**4],[5*10**4],[1*10**5],[2*10**5],[3*10**3]],dtype = 'float')
    neutronDose = []
    for i in range(0,len(c)):
        for n in range(0,len(energyVals)-1):
            if energyVals[n+1] > c[i] > energyVals[n]:
                conv = doseConversion[n] + (c[i]-energyVals[n])*((doseConversion[n+1]-doseConversion[n])/(energyVals[n+1]-energyVals[n]))
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

########################################################################################
####             define neutron dose and flux rates                                 ####  
########################################################################################
    maxFluxRate = max(flux)
    maxDoseRate = max(neutronDose)
    totalDose = sum(neutronDose)
########################################################################################
###                      Generate image of neutron data                              ###
########################################################################################
    np.savetxt("muValsSinTheta.csv", mu, delimiter=",")
    np.savetxt("coneVectors.csv",coneVector,delimiter = ",")
    np.savetxt("weights.csv",weights,delimiter = ",")
    np.savetxt("neutronDose.csv",neutronDose,delimiter = ",")
    np.savetxt("neutronEnergy.csv",c,delimiter = ",")
    print('Generating Neutron Image')
    hpindex = 912
    theta,phi = np.asarray(hp.pix2ang(16,hpindex-1)) * (180./np.pi)
    if phi > 180: phi = -(360. - phi)
    nside = 64
    [x_,y_,z_] = hp.pix2vec(nside,range(12*nside*nside))#201))
    k = np.array(list(zip(x_,y_,z_)))
    cmap_ = plt.cm.jet
    cmap_.set_under("w")
    pixels = np.zeros(12*nside*nside)
    #angunc = 3.
    print(len(k))
    print(len(weights))
    for i in range(len(mu)):
        b += (weights[i] / (sigma * np.sqrt(2.*np.pi))) * np.exp(-(np.dot(k,unitVector[i,:]) - mu[i])**2/(2. * sigma**2))
        b[b < 1e-5] = 0
        pixels += b

    
    latra = [-90,90]
    lonra = [-180,180]
    p = hp.cartview(newPix, rot=(90,0), lonra=lonra,latra=latra, return_projected_map=True)
    hp.projplot(hp.pix2ang(16,hpindex-1), 'k*', markersize = 8)
    #hp.graticule()
    plt.close("all")
    plt.figure()
    p = plt.imshow(p, cmap=cmap_, origin='lower', interpolation='nearest', extent=(lonra[1],lonra[0],latra[0],latra[1]))
    #plt.scatter(phi, 90-theta, marker='x')
    plt.xlim(lonra[0], lonra[1]); plt.ylim(latra[0], latra[1])
    plt.colorbar(p, fraction=0.046, pad=0.04)
    plt.title('Neutron Image of PuBe Source')
    plt.xlabel('Radial Angle [degrees]')
    plt.ylabel('Azimuthal Angle [degrees]')
    plt.xticks([-180,-135,-90,-45,0,45,90,135,180])
    plt.yticks([-90,-45,0,45,90])

    plt.show()
    
#    plt.figure()
#    plt.imshow(pixels, vmin=0, vmax=maxDoseRate, extent=[0,180,0,360], aspect="auto")
#    plt.xlabel('Azimuthal Angle [degrees]')
#    plt.ylabel('Radial Angle [degrees]')
#    plt.title('Neutron Dose Image of PuBe Source')
#    cb = plt.colorbar()
#    cb.set_label('Dose Rate [mSv/hr]')
#    plt.show()
    return
    