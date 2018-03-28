#!/usr/bin/env python2
# -*- coding: utf-8 -*-
"""
Created on Wed Aug 16 10:31:57 2017

@author: aglick
"""

def generateCones(slope,intercept,plane1Dets,plane2Dets,plane1Times,plane2Times,plane1NeutronPulseADC,plane2NeutronPulseADC):
    import csv
    import numpy as np
    import math
    import matplotlib.pyplot as plt
    import matplotlib
    import pylab as pl
    import time
    import pandas as pd
    from mpl_toolkits.mplot3d import Axes3D
    planeSeparation = 0.6096 #meters
    detectorSeparation = 0.0889 #meters
    u = detectorSeparation #meters
    D = planeSeparation #meters
    clockSpeed = 250*10**6 #Hz
    timeScale = 1/clockSpeed #seconds
    distance = []
    x1 = []
    x2 = []
    plane2DetScale = []
    plane1Local = np.array([[0,0,0],[0,u,0],[0,2*u,0],[u,0,0],[u,u,0],[u,2*u,0],[2*u,0,0],[2*u,u,0],[2*u,2*u,0],[3*u,0,0],[3*u,u,0],[3*u,2*u,0]],dtype='float')
    plane2Local = np.array([[0,0,D],[0,u,D],[0,2*u,D],[u,0,D],[u,u,D],[u,2*u,D],[2*u,0,D],[2*u,u,D],[2*u,2*u,D],[3*u,0,D],[3*u,u,D],[3*u,2*u,D]],dtype='float')
    neutronEnergyTOF = []
    neutronEnergyADC = []
    adcValP2 = []
    neutronEnergy = []
    coneAngles = []
    cones = []
    radii = 0


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
    tic = time.time()
    for i in range(0,len(plane1Times)): #range(0,len(plane1Times))
        if i > 200:
            for n in range(i-100,i+100):
                if plane2Times[n] - plane1Times[i] <= 100000 and plane2Times[n] - plane1Times[i] > 0:
                    #print('plane1Local = ',plane1Local[i])
                    #print('plane1Dets = ',plane1Dets[i])
                    x1 = plane1Local[plane1Dets[i]]
                    x2 = plane2Local[plane2DetScale[n]]
                    #print('x1 = ',x1)
                    dist = [np.sqrt((x2[0]-x1[0])**2 + (x2[1]-x1[1])**2 + (x2[2])**2)]
                    distance += [dist]
                    timeSeparation = (plane2Times[n]-plane1Times[i])*timeScale
                    energy = (1/(1.602*10**(-13)))*0.5*(1.675*10**(-27))*(dist/timeSeparation)**2
                    neutronEnergyTOF += [energy] #MeV
                    adcValP2 += [plane2NeutronPulseADC[n]]
                    neutronEnergyADC += [slope*plane1NeutronPulseADC[i] + intercept]
                    #coneAngles += [math.degrees(math.atan(math.sqrt(neutronEnergyADC[i]/neutronEnergyTOF[i])))]
                #print('Energy = ',energy,' MeV')
                    break
        else:
            for n in range(0,i+200):
#            if n%10000 == 0:
#                print('n = ',n)
                if plane2Times[n] - plane1Times[i] <= 100000 and plane2Times[n] - plane1Times[i] > 0:
                    x1 = plane1Local[plane1Dets[i]]
                    x2 = plane2Local[plane2DetScale[n]]
                    dist = [np.sqrt((x2[0]-x1[0])**2 + (x2[1]-x1[1])**2 + (x2[2])**2)]
                    distance += [dist]
                    timeSeparation = (plane2Times[n]-plane1Times[i])*timeScale
                    energy = (1/(1.602*10**(-13)))*0.5*(1.675*10**(-27))*(dist/timeSeparation)**2 #MeV
                    neutronEnergyTOF += [energy] #MeV
                    adcValP2 += [plane2NeutronPulseADC[n]]
                    neutronEnergyADC += [slope*plane1NeutronPulseADC[i] + intercept]
                    #coneAngles += [math.degrees(math.atan(math.sqrt(neutronEnergyADC[i]/neutronEnergyTOF[i])))]
#                    if n%100 == 0:
#                        print('n = ',n)
#                        print('x1 = ',x1)
#                        print('x2 = ',x2)
                    break

        if i%100000 == 0:
            toc = time.time()
            print('i = ',i)
            print('elapsed time = ',toc-tic, 's')
    distance = np.array(distance)
    neutronEnergyTOF = np.array(neutronEnergyTOF)
    neutronEnergyTOF = neutronEnergyTOF*10**3 #keV
    neutronEnergyADC = np.array(neutronEnergyADC)
    adcValP2 = np.array(adcValP2,dtype = 'float')
    #neutronEnergy = [neutronEnergyTOF + neutronEnergyADC]
    plt.figure()
    plt.plot(neutronEnergyADC,adcValP2)
    plt.show()
    for i in range(0,len(neutronEnergyADC)):
        coneAngles += [math.degrees(math.atan(math.sqrt(neutronEnergyADC[i]/neutronEnergyTOF[i])))]

    coneAngles = np.array(coneAngles)
    neutronEnergy = np.array(neutronEnergy,dtype='float')
    neutronEnergy = neutronEnergy*10**(-3)
#    numpy.savetxt("neutron.csv", neutronEnergyTOF, delimiter=",")

#### Generate the cones for image reconstruction ####
    for i in range(0,len(coneAngles)):
        radii = distance[i]*math.tan(coneAngles[i]/2)
        r = np.linspace(0, radii, 50)
        p = np.linspace(0, 2*np.pi, 50)
        R, P = np.meshgrid(r, p)
        Z = ((R**2 - 1)**2)
        X = R*np.cos(P)
        Y = R*np.sin(P)
        cones += [[radii],[distance[i]],[coneAngles[i]]]
        #ax.plot_surface(X, Y, Z)
        #ax.set_xlabel('X Label')
        #ax.set_ylabel('Y Label')
        #ax.set_zlabel('Z Label')
    #plt.legend(loc = 'best')
    #plt.show()
    df = pd.DataFrame(cones)
    #df.to_csv("ConesGenerated.csv")
    #np.savetxt('GeneratedCones.csv',cones,delimiter=",")
    #ax.plot_surface(cones[0], Y, Z, cmap=plt.cm.YlGnBu_r)
    hpindex = 912
    theta,phi = np.asarray(hp.pix2ang(16,hpindex-1)) * (180./np.pi)
    if phi > 180: phi = -(360. - phi)
    nside = 64
    [x_,y_,z_] = hp.pix2vec(nside,range(12*nside*nside))#201))
    k = np.array(list(zip(x_,y_,z_)))
    cmap_ = plt.cm.jet
    cmap_.set_under("w")
    im = np.zeros(12*nside*nside)
    angunc = 3.

    for i in range(len(mu)):#len(sequences)):
        #for n in range(0,500):#len(k[:,0])):
            #print('n = ',n)
        b += (weights[i] / (sigma * np.sqrt(2.*np.pi))) * np.exp(-(np.dot(k,unitVector[i,:]) - mu[i])**2/(2. * sigma**2))
        #b[b < 1e-5] = 0
        #val = np.array(val)
        im += b

#pixels = (pixels/normB)
#pixels = np.ravel(pixels)
#maxPix = 0
#newNorm = 0
#normPix = pixels-min(pixels[:])
#newPix = normPix/max(normPix)
#newPix = newPix.reshape([len(theta),len(phi)])
    pixels = im/max(im)
    pixels = np.ravel(pixels)
    normPix = pixels-min(pixels[:])
    newPix = normPix/max(normPix)
    newPix = newPix.reshape(12*nside*nside)
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

    energyHist = np.histogram(neutronEnergy,100)
    a = energyHist[0]
    b = energyHist[1]
    c = b[0:100]
    plt.figure(1)
    plt.plot(c,a,'r--')
    plt.xlabel('Neutron Energy [MeV]')
    plt.ylabel('Counts')
    plt.title('Neutron Spectrum')
    plt.autoscale(enable=True,axis='x',tight=True)
    pl.xticks(rotation=45)
    #plt.legend(loc='upper right')
    #plt.plot(d,f)
    plt.show()

#    numpy.savetxt("neutronEnergy.csv", c, delimiter=",")
#    numpy.savetxt("neutronCounts.csv", a, delimiter=",")

    return

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
    area = ((plane2Local[0,2] - plane1Local[0,2])*10**2)*(plane2Local[11,0]-plane1Local[0,0])*10**2 #cm2
    neutronEnergyTOF = []
    adcValP2 = []
    neutronEnergyADC = []
    neutronEnergy = []
    coneAngles = []
    coneVector = []
    mu = []
    weights = []
    coneVector1 = []
    mu1 = []
    weights1 = []
    coneVector2 = []
    mu2 = []
    weights2 = []
    coneVector3 = []
    mu3 = []
    weights3 = []
#    cones = []
    b = 0
    time1 = []
#    radii = 0
    sigma = 0.045
    iteration = 0
    area = (plane1Local[2,1]-plane1Local[0,1])*(plane1Local[10,0]-plane1Local[0,0])


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
                if plane2Times[n] - plane1Times[i] <= 1000000 and plane2Times[n] - plane1Times[i] > 0:
                    #temp = keepTrack
                    if 0 <= plane1Dets[i] <= 3 and 20 <= plane2Dets[n] <= 23:
                        #print('calculating TOF')
                        x1 = plane1Local[plane1Dets[i]]
                        x2 = plane2Local[plane2DetScale[n]]
                        dist = np.sqrt((x2[0]-x1[0])**2 + (x2[1]-x1[1])**2 + (x2[2])**2)
                        distance += [dist]
                        timeSeparation = (plane2Times[n]-plane1Times[i])*timeScale
                        #print('time separation = ',timeSeparation)
                        #print('distance = ',dist)
                        u = dist/timeSeparation
                        #print('velocity = ',u)
                        energy = (1/(1.602*10**(-16)))*0.5*(1.675*10**(-27))*(dist/timeSeparation)**2 #keV
                        energyADC = slope*plane1NeutronPulseADC[i] + intercept
                        #energyNeutronFirstScatter = (10**3)*(-0.1410 + math.sqrt(0.1410**2 + 4*0.035*plane1NeutronPulseADC[i]))/(2*0.035) #keV
                        energyNeutronFirstScatter = energyADC*((0.99*(plane1NeutronPulseADC[i]+0.0685))/(0.23*(plane1NeutronPulseADC[i]-0.008)))
                        energyTotal = energyNeutronFirstScatter + energy
                        neutronEnergyTOF += [energy] #keV
                        adcValP2 += [plane2NeutronPulseADC[n]]
                        neutronEnergyADC += [energyNeutronFirstScatter] #keV
                        neutronEnergy += [energyTotal] #keV
                        #print('Direct ADC = ',energyADC)
                        #print('Converted ADC = ', energyNeutronFirstScatter)
                        #print('angle = ',np.deg2rad(math.sqrt((slope*plane1NeutronPulseADC[i] + intercept)/energyTotal)))
                        coneAngles += [math.atan(np.deg2rad(math.sqrt((slope*plane1NeutronPulseADC[i] + intercept)/energyTotal)))]
                        mu += [np.cos(math.atan(np.deg2rad(math.sqrt((slope*plane1NeutronPulseADC[i] + intercept)/energyTotal))))]
                        weights += [1/dist**2]
                        coneVector += [x1-x2]
                        #if keepTrack == 0:
                        time1 += [plane1Times[i]*timeScale]
                        time1 += [plane2Times[n]*timeScale]
                        coneVector += [x1-x2]
                        mu1 += [np.cos(math.atan(np.deg2rad(math.sqrt((slope*plane1NeutronPulseADC[i] + intercept)/energyTotal))))]
                        weights1 += [1/dist**2]
                        coneVector1 += [x1-x2]
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
                        energy = (1/(1.602*10**(-16)))*0.5*(1.675*10**(-27))*(dist/timeSeparation)**2 #keV
                        energyADC = slope*plane1NeutronPulseADC[i] + intercept
                        energyTotal = energyADC + energy
                        neutronEnergyTOF += [energy] #keV
                        adcValP2 += [plane2NeutronPulseADC[n]]
                        neutronEnergyADC += [energyADC] #keV
                        neutronEnergy += [energyTotal] #keV
                        #print('angle = ',np.deg2rad(math.sqrt((slope*plane1NeutronPulseADC[i] + intercept)/energyTotal)))
                        coneAngles += [math.atan(np.deg2rad(math.sqrt((slope*plane1NeutronPulseADC[i] + intercept)/energyTotal)))]
                        mu += [np.cos(math.atan(np.deg2rad(math.sqrt((slope*plane1NeutronPulseADC[i] + intercept)/energyTotal))))]
                        weights += [1/dist**2]
                        coneVector += [x1-x2]
                        print('in deterctor 2 space')
                        mu2 += [np.cos(math.atan(np.deg2rad(math.sqrt((slope*plane1NeutronPulseADC[i] + intercept)/energyTotal))))]
                        weights2 += [1/dist**2]
                        coneVector2 += [x1-x2]
                        break
                    elif 4 <= plane1Dets[i] <= 7 and 16 <= plane2Dets[n] <= 19:
                        x1 = plane1Local[plane1Dets[i]]
                        x2 = plane2Local[plane2DetScale[n]]
                        dist = np.sqrt((x2[0]-x1[0])**2 + (x2[1]-x1[1])**2 + (x2[2])**2)
                        distance += [dist]
                        timeSeparation = (plane2Times[n]-plane1Times[i])*timeScale
                        energy = (1/(1.602*10**(-16)))*0.5*(1.675*10**(-27))*(dist/timeSeparation)**2 #keV
                        energyADC = slope*plane1NeutronPulseADC[i] + intercept
                        energyTotal = energyADC + energy
                        neutronEnergyTOF += [energy] #keV
                        adcValP2 += [plane2NeutronPulseADC[n]]
                        neutronEnergyADC += [energyADC] #keV
                        neutronEnergy += [energyTotal] #keV
                        #print('angle = ',np.deg2rad(math.sqrt((slope*plane1NeutronPulseADC[i] + intercept)/energyTotal)))
                        coneAngles += [math.atan(np.deg2rad(math.sqrt((slope*plane1NeutronPulseADC[i] + intercept)/energyTotal)))]
                        mu += [np.cos(math.atan(np.deg2rad(math.sqrt((slope*plane1NeutronPulseADC[i] + intercept)/energyTotal))))]
                        weights += [1/dist**2]
                        coneVector += [x1-x2]
                        print('in deterctor 3 space')
                        mu3 += [np.cos(math.atan(np.deg2rad(math.sqrt((slope*plane1NeutronPulseADC[i] + intercept)/energyTotal))))]
                        weights3 += [1/dist**2]
                        coneVector3 += [x1-x2]
                        break
                #neutronEnergyTOF += [0] #keV
                neutronEnergyADC += [slope*plane1NeutronPulseADC[i] + intercept]

        elif i<=200:
            for n in range(0,i+200):
#            if n%10000 == 0:
#                print('n = ',n)
                if plane2Times[n] - plane1Times[i] <= 1000000 and plane2Times[n] - plane1Times[i] > 0:
                    if 0 <= plane1Dets[i] <= 3 and 20 <= plane2Dets[n] <= 23:
                        x1 = plane1Local[plane1Dets[i]]
                        x2 = plane2Local[plane2DetScale[n]]
                        dist = np.sqrt((x2[0]-x1[0])**2 + (x2[1]-x1[1])**2 + (x2[2])**2)
                        distance += [dist]
                        timeSeparation = (plane2Times[n]-plane1Times[i])#*timeScale
                        energy = (1/(1.602*10**(-16)))*0.5*(1.675*10**(-27))*(dist/timeSeparation)**2 #keV
                        energyADC = slope*plane1NeutronPulseADC[i] + intercept
                        #energyTotal = energyADC + energy
                        neutronEnergyTOF += [energy] #keV
                        adcValP2 += [plane2NeutronPulseADC[n]]
                        energyNeutronFirstScatter = energyADC*((0.99*(plane1NeutronPulseADC[i]+0.0685))/(0.23*(plane1NeutronPulseADC[i]-0.008)))
                        energyTotal = energyNeutronFirstScatter + energy
                        neutronEnergy += [energyTotal] #keV
                        #print('angle = ',np.deg2rad(math.sqrt((slope*plane1NeutronPulseADC[i] + intercept)/energyTotal)))
                        coneAngles += [math.atan(np.deg2rad(math.sqrt((slope*plane1NeutronPulseADC[i] + intercept)/energyTotal)))]
                        mu += [np.cos(math.atan(np.deg2rad(math.sqrt((slope*plane1NeutronPulseADC[i] + intercept)/energyTotal))))]
                        weights += [1/dist**2]
                        #if keepTrack == 0:
                        time1 += [plane1Times[i]*timeScale]
                        time1 += [plane2Times[n]*timeScale]
                        #keepTrack += 1
                        coneVector += [x1-x2]
                        mu1 += [np.cos(math.atan(np.deg2rad(math.sqrt((slope*plane1NeutronPulseADC[i] + intercept)/energyTotal))))]
                        weights1 += [1/dist**2]
                        coneVector1 += [x1-x2]
                        break
                    elif 8 <= plane1Dets[i] <= 11 and 12 <= plane2Dets[n] <= 15:
                        x1 = plane1Local[plane1Dets[i]]
                        x2 = plane2Local[plane2DetScale[n]]
                        dist = np.sqrt((x2[0]-x1[0])**2 + (x2[1]-x1[1])**2 + (x2[2])**2)
                        distance += [dist]
                        timeSeparation = (plane2Times[n]-plane1Times[i])*timeScale
                        energy = (1/(1.602*10**(-16)))*0.5*(1.675*10**(-27))*(dist/timeSeparation)**2 #keV
                        energyADC = slope*plane1NeutronPulseADC[i] + intercept
                        #energyTotal = energyADC + energy
                        neutronEnergyTOF += [energy] #keV
                        adcValP2 += [plane2NeutronPulseADC[n]]
                        energyNeutronFirstScatter = energyADC*((0.99*(plane1NeutronPulseADC[i]+0.0685))/(0.23*(plane1NeutronPulseADC[i]-0.008)))
                        energyTotal = energyNeutronFirstScatter + energy
                        neutronEnergy += [energyTotal] #keV
                        #print('angle = ',np.deg2rad(math.sqrt((slope*plane1NeutronPulseADC[i] + intercept)/energyTotal)))
                        coneAngles += [math.atan(np.deg2rad(math.sqrt((slope*plane1NeutronPulseADC[i] + intercept)/energyTotal)))]
                        mu += [np.cos(math.atan(np.deg2rad(math.sqrt((slope*plane1NeutronPulseADC[i] + intercept)/energyTotal))))]
                        weights += [1/dist**2]
                        coneVector += [x1-x2]
                        print('in deterctor 2 space')
                        mu2 += [np.cos(math.atan(np.deg2rad(math.sqrt((slope*plane1NeutronPulseADC[i] + intercept)/energyTotal))))]
                        weights2 += [1/dist**2]
                        coneVector2 += [x1-x2]
                        break
                    elif 4 <= plane1Dets[i] <= 7 and 16 <= plane2Dets[n] <= 19:
                        x1 = plane1Local[plane1Dets[i]]
                        x2 = plane2Local[plane2DetScale[n]]
                        dist = np.sqrt((x2[0]-x1[0])**2 + (x2[1]-x1[1])**2 + (x2[2])**2)
                        distance += [dist]
                        timeSeparation = (plane2Times[n]-plane1Times[i])*timeScale
                        energy = (1/(1.602*10**(-16)))*0.5*(1.675*10**(-27))*(dist/timeSeparation)**2 #keV
                        energyADC = slope*plane1NeutronPulseADC[i] + intercept
                        energyTotal = energyADC + energy
                        neutronEnergyTOF += [energy] #keV
                        adcValP2 += [plane2NeutronPulseADC[n]]
                        neutronEnergyADC += [energyADC] #keV
                        neutronEnergy += [energyTotal] #keV
                        #print('angle = ',np.deg2rad(math.sqrt((slope*plane1NeutronPulseADC[i] + intercept)/energyTotal)))
                        coneAngles += [math.atan(np.deg2rad(math.sqrt((slope*plane1NeutronPulseADC[i] + intercept)/energyTotal)))]
                        mu += [np.cos(math.atan(np.deg2rad(math.sqrt((slope*plane1NeutronPulseADC[i] + intercept)/energyTotal))))]
                        weights += [1/dist**2]
                        coneVector += [x1-x2]
                        print('in deterctor 3 space')
                        mu3 += [np.cos(math.atan(np.deg2rad(math.sqrt((slope*plane1NeutronPulseADC[i] + intercept)/energyTotal))))]
                        weights3 += [1/dist**2]
                        coneVector3 += [x1-x2]
                        break
                #neutronEnergyTOF += [0] #keV
                neutronEnergyADC += [slope*plane1NeutronPulseADC[i] + intercept]
                neutronEnergy += [slope*plane1NeutronPulseADC[i] + intercept] #keV
        if i%10000 == 0:
            toc = time.time()
            print('i = ',i)
            print('elapsed time = ',toc-tic, 's')

######################################################################################
####                  make lists into numpy arrays                                ####
######################################################################################
    distance = np.array(distance)
    neutronEnergyTOF = np.array(neutronEnergyTOF,dtype = 'float')
    adcValP2 = np.array(adcValP2,dtype = 'float')
    plt.figure()
    plt.plot(adcValP2,neutronEnergyTOF)
    plt.title('Energy - ADC Conversions')
    plt.show()
    #neutronEnergyTOF = neutronEnergyTOF*10**3 #keV
    neutronEnergyADC = np.array(neutronEnergyADC, dtype = 'float')
    neutronEnergy = np.array(neutronEnergy, dtype = 'float') #neutronEnergyTOF + neutronEnergyADC
    coneVector = np.array(coneVector,dtype = 'float')
    mu = np.array(mu)
    coneAngles = np.array(coneAngles)
    weights = np.array(weights)
    coneVector1 = np.array(coneVector1,dtype = 'float')
    mu1 = np.array(mu1)
    weights1 = np.array(weights1)
    coneVector2 = np.array(coneVector2,dtype = 'float')
    mu2 = np.array(mu2)
    weights2 = np.array(weights2)
    coneVector3 = np.array(coneVector3,dtype = 'float')
    mu3 = np.array(mu3)
    weights3 = np.array(weights3)
    #neutronEnergy = np.array(neutronEnergy,dtype='float')
    time1 = np.array(time1,dtype = 'float')
    time1.sort()
    np.savetxt('adcEnergy.csv',neutronEnergyADC)
    np.savetxt('neutronEnergy.csv',neutronEnergy)
    ### Checking max TOF and ADC Energies ###
    tofMaxArg = neutronEnergyTOF.argmax()
    print('Max TOF Energy = ', neutronEnergyTOF[tofMaxArg])
    adcMaxArg = neutronEnergyADC.argmax()
    print('Max ADC Energy = ', neutronEnergyADC[adcMaxArg])
    nEMax = neutronEnergy.argmax()
    print('Max Total Energy = ',neutronEnergy[nEMax])
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

    unitNorm = 0
    unitVector1 = []
    for i in range(0,len(coneVector1[:,0])):
        temp = coneVector1[i,:]
        unitNorm = np.linalg.norm(temp)
        unitVector1 += [temp/unitNorm]

    unitVector1 = np.array(unitVector1, dtype = 'float')



    if coneVector2 != 0:
        unitNorm = 0
        unitVector2 = []
        for i in range(0,len(coneVector2[:,0])):
            temp = coneVector2[i,:]
            unitNorm = np.linalg.norm(temp)
            unitVector2 += [temp/unitNorm]
        unitVector2 = np.array(unitVector2, dtype = 'float')

    if coneVector3 != 0:
        unitNorm = 0
        unitVector3 = []
        for i in range(0,len(coneVector3[:,0])):
            temp = coneVector3[i,:]
            unitNorm = np.linalg.norm(temp)
            unitVector3 += [temp/unitNorm]
        unitVector3 = np.array(unitVector3, dtype = 'float')


#######################################################################################
####                    plot energy spectrum                                       ####
#######################################################################################
    print('nEnergy.size() = ', np.size(neutronEnergy))
    neutronEnergyAdj = [i for i in neutronEnergy if  0 < i <= 500000]
    neutronEnergyAdj = np.array(neutronEnergyAdj, dtype = 'float')
    #print(neutronEnergy)
    nEMax = neutronEnergyAdj.argmax()
    print('max n energy = ',neutronEnergyAdj[nEMax])
    energyHist = np.histogram(neutronEnergyAdj,1000)#len(neutronEnergy))
    a = energyHist[0]
    b1 = energyHist[1]
    #print('a = ',a)
    #print('a.size = ',np.size(a))
    #print('b1 = ',b1)
    #print('b1.size = ',np.size(b1))

    c = b1[1:1001]
    print('max E taken = ',c[len(c)-1])
    print('max counts = ', max(a))
    for i in range(0,len(a)-1):
        if a[i] == 0:
            a[i]=1

    plt.figure(2)
    plt.plot(c,np.log10(a),'b-')
    plt.xlabel('Neutron Energy [keV]')
    plt.ylabel('Log10(Counts)')
    plt.title('Neutron Spectrum')
    plt.autoscale(enable=True,axis='x',tight=True)
    pl.xticks(rotation=45)
    #plt.legend(loc='upper right')
    #plt.plot(d,f)
    plt.show()

#######################################################################################
####                    plot flux spectrum                                         ####
#######################################################################################
#    print('flux time = ',time1[len(time1)-1]-time1[0])
#    plt.figure()
#    flux = np.exp(a)/(area*(time1[len(time1)-1]-time1[0]))
#    plt.figure(3)
#    plt.plot(c,flux,'b-')
#    plt.xlabel('Neutron Energy [keV]')
#    plt.ylabel('Flux [Counts/cm^2s]')
#    plt.title('Neutron Flux Spectrum')
#    plt.autoscale(enable=True,axis='x',tight=True)
#    pl.xticks(rotation=45)
    #plt.legend(loc='upper right')
    #plt.plot(d,f)
#    plt.show()
########################################################################################
####         generate and plot neutron dose spectrum                                ####
########################################################################################
#    doseConversion = np.array([[260],[240],[220],[230],[240],[270],[280],[48],[14],[8.5],[7.0],[6.8],[6.8],[6.5],[6.1],[5.1],[3.6],[2.2],[1.6],[1.4]], dtype = 'float')
#    energyVals = np.array([[2.5*10**(-6)],[1*10**(-5)],[1*10**(-4)],[1*10**(-3)],[1*10**(-2)],[1*10**(-1)],[1*10**(0)],[1*10**1],[5*10],[1*10**2],[2*10**2],[5*10**2],[10*10**2],[20*10**2],[50*10**2],[10**4],[2*10**4],[5*10**4],[1*10**5],[2*10**5],[3*10**3]],dtype = 'float')
#    neutronDose = []
#    for i in range(0,len(c)):
#        for n in range(0,len(energyVals)-1):
#            if energyVals[n+1] > c[i] > energyVals[n]:
#                conv = doseConversion[n] + (c[i]-energyVals[n])*((doseConversion[n+1]-doseConversion[n])/(energyVals[n+1]-energyVals[n]))
#                neutronDose += [0.01*flux[i]/conv]
#            elif energyVals[n] == c[i]:
#                neutronDose += [0.01*flux[i]/doseConversion[n]]


#    neutronDose = np.array(neutronDose,dtype = 'float')
#    plt.figure(4)
#    plt.plot(c,neutronDose,'b-')
#    plt.xlabel('Neutron Energy [keV]')
#    plt.ylabel('Dose [mSv/hr]')
#    plt.title('Neutron Dose Rate for PuBe Source')
#    plt.autoscale(enable=True,axis='x',tight=True)
#    pl.xticks(rotation=45)
#    plt.show()

########################################################################################
####             define neutron dose and flux rates                                 ####
########################################################################################
#    maxFluxRate = max(flux)
#    maxDoseRate = max(neutronDose)
#    totalDose = sum(neutronDose)
########################################################################################
###                      Generate image of neutron data                              ###
########################################################################################
    #np.savetxt("muValsSinTheta.csv", mu, delimiter=",")
    #np.savetxt("coneVectors.csv",coneVector,delimiter = ",")
    #np.savetxt("weights.csv",weights,delimiter = ",")
    #np.savetxt("neutronDose.csv",neutronDose,delimiter = ",")
    #np.savetxt("neutronEnergy.csv",c,delimiter = ",")
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
    b = 0
    for i in range(len(mu)):
        b += (weights[i] / (sigma * np.sqrt(2.*np.pi))) * np.exp(-(np.dot(k,unitVector[i,:]) - mu[i])**2/(2. * sigma**2))
        b[b < 1e-5] = 0
        pixels += b
        #print('elapsed = ',time.time()-tic, 's')

    pixels1 = np.zeros(12*nside*nside)
    #angunc = 3.
    #print(len(k))
    #print(len(weights))
    b = 0
    for i in range(len(mu1)):
        b += (weights1[i] / (sigma * np.sqrt(2.*np.pi))) * np.exp(-(np.dot(k,unitVector1[i,:]) - mu1[i])**2/(2. * sigma**2))
        b[b < 1e-5] = 0
        pixels1 += b
        #print('elapsed = ',time.time()-tic, 's')
    pixels2 = np.zeros(12*nside*nside)
    #angunc = 3.
    print(len(k))
    print(len(weights2))
    b = 0
    for i in range(len(mu2)):
        b += (weights2[i] / (sigma * np.sqrt(2.*np.pi))) * np.exp(-(np.dot(k,unitVector2[i,:]) - mu2[i])**2/(2. * sigma**2))
        b[b < 1e-5] = 0
        pixels2 += b
        #print('elapsed = ',time.time()-tic, 's')
    pixels3 = np.zeros(12*nside*nside)
    #angunc = 3.
    print(len(k))
    print(len(weights3))
    b = 0
    for i in range(len(mu3)):
        b += (weights3[i] / (sigma * np.sqrt(2.*np.pi))) * np.exp(-(np.dot(k,unitVector3[i,:]) - mu3[i])**2/(2. * sigma**2))
        b[b < 1e-5] = 0
        pixels3 += b
        #print('elapsed = ',time.time()-tic, 's')

    pixels = pixels/max(pixels)
    pixels = np.ravel(pixels)
    normPix = pixels-min(pixels[:])
    newPix = normPix/max(normPix)
    #print(res)
    newPix = newPix.reshape(12*nside*nside)#*maxDose

    pixels1 = pixels1/max(pixels1)
    pixels1 = np.ravel(pixels1)
    normPix1 = pixels1-min(pixels1[:])
    newPix1 = normPix1/max(normPix1)
    #print(res)
    newPix1 = newPix1.reshape(12*nside*nside)#*maxDose

    pixels2 = pixels2/max(pixels2)
    pixels2 = np.ravel(pixels2)
    normPix2 = pixels2-min(pixels2[:])
    newPix2 = normPix2/max(normPix2)
    #print(res)
    newPix2 = newPix2.reshape(12*nside*nside)#*maxDose

    pixels3 = pixels3/max(pixels3)
    pixels3 = np.ravel(pixels3)
    normPix3 = pixels-min(pixels3[:])
    newPix3 = normPix3/max(normPix3)
    #print(res)
    newPix3 = newPix3.reshape(12*nside*nside)#*maxDose

    latra = [-90,90]
    lonra = [-180,180]
    p = hp.cartview(newPix, rot=(90,-90), lonra=lonra,latra=latra, return_projected_map=True)
    hp.projplot(hp.pix2ang(16,hpindex-1), 'k*', markersize = 8)
    a = len(p[0,:])
    b = len(p[:,0])
    maxR = 0
    maxC = 0
    histRow = []
    histCol = []
    count = 0
    rowArg = 0
    for row in p:
        count += 1
        if max(row) > maxR: #row.mean() > maxR:
            histRow = row
            maxR = row.mean()
            rowArg = count

    count = 0
    colArg = 0
    for column in p:
        count += 1
        if max(column) > maxC: #column.mean() > maxC:
            histCol = column
            maxC = column.mean()
            colArg = count

    radAng = np.linspace(-180,180,a)
    azAng = np.linspace(-90,90,a)
    #print(radAng)
    #print(histCol)
    #print(np.size(histCol))
    #unitRow = np.linalg.norm(histRow)
    histRow = histRow/max(histRow)#(histRow - np.mean(histRow))/np.std(histRow)
    #unitCol = np.linalg.norm(histCol)
    histCol = histCol/max(histCol)

    #res = np.histogram(newPix,100)
    print(rowArg)
    print(colArg)
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
    plt.plot([rowArg, rowArg], [0, len(histCol)], 'k-', lw=4)
    plt.plot([colArg, colArg], [0, len(histRow)], 'k-', lw=2)
    #plt.xticks([-270,-225,-180,-135,-90,-45,0,45,90])
    #plt.yticks([0,45,90,135,180])
    plt.show()

#    p1 = hp.cartview(newPix1, rot=(90,-90), lonra=lonra,latra=latra, return_projected_map=True)
#    hp.projplot(hp.pix2ang(16,hpindex-1), 'k*', markersize = 8)
#    p1 = hp.cartview(p1, rot=(90,-90), lonra=lonra,latra=latra, return_projected_map=True)
#    plt.close("all")
#    plt.figure()
#    p1 = plt.imshow(p1, cmap=cmap_, origin='lower', interpolation='nearest', extent=(lonra[1],lonra[0],latra[0],latra[1]))
        #plt.scatter(phi, 90-theta, marker='x')
#    plt.xlim(lonra[0], lonra[1]); plt.ylim(latra[0], latra[1])
#    plt.colorbar(p, fraction=0.046, pad=0.04)
#    plt.title('Neutron Image of PuBe Source - 3320 Card 1')
#    plt.xlabel('Radial Angle [degrees]')
#    plt.ylabel('Azimuthal Angle [degrees]')
#    plt.xticks([-180,-135,-90,-45,0,45,90,135,180])
#    plt.yticks([-90,-45,0,45,90])
#    plt.plot([rowArg, rowArg], [0, len(histCol)], 'k-', lw=4)
#    plt.plot([colArg, colArg], [0, len(histRow)], 'k-', lw=2)
    #plt.xticks([-270,-225,-180,-135,-90,-45,0,45,90])
    #plt.yticks([0,45,90,135,180])
    plt.show()
    if coneVector2 != 0:
        p2 = hp.cartview(newPix2, rot=(90,-90), lonra=lonra,latra=latra, return_projected_map=True)
        plt.close("all")
        plt.figure()
        p2 = plt.imshow(p2, cmap=cmap_, origin='lower', interpolation='nearest', extent=(lonra[1],lonra[0],latra[0],latra[1]))
        #plt.scatter(phi, 90-theta, marker='x')
        plt.xlim(lonra[0], lonra[1]); plt.ylim(latra[0], latra[1])
        plt.colorbar(p, fraction=0.046, pad=0.04)
        plt.title('Neutron Image of PuBe Source - 3320 Card 2')
        plt.xlabel('Radial Angle [degrees]')
        plt.ylabel('Azimuthal Angle [degrees]')
        plt.xticks([-180,-135,-90,-45,0,45,90,135,180])
        plt.yticks([-90,-45,0,45,90])
        plt.plot([rowArg, rowArg], [0, len(histCol)], 'k-', lw=4)
        plt.plot([colArg, colArg], [0, len(histRow)], 'k-', lw=2)
    #plt.xticks([-270,-225,-180,-135,-90,-45,0,45,90])
    #plt.yticks([0,45,90,135,180])
        plt.show()
    if coneVector3 != 0:
        p3 = hp.cartview(newPix3, rot=(90,-90), lonra=lonra,latra=latra, return_projected_map=True)
        plt.close("all")
        plt.figure()
        p3 = plt.imshow(p3, cmap=cmap_, origin='lower', interpolation='nearest', extent=(lonra[1],lonra[0],latra[0],latra[1]))
        #plt.scatter(phi, 90-theta, marker='x')
        plt.xlim(lonra[0], lonra[1]); plt.ylim(latra[0], latra[1])
        plt.colorbar(p, fraction=0.046, pad=0.04)
        plt.title('Neutron Image of PuBe Source - 3320 Card 3')
        plt.xlabel('Radial Angle [degrees]')
        plt.ylabel('Azimuthal Angle [degrees]')
        plt.xticks([-180,-135,-90,-45,0,45,90,135,180])
        plt.yticks([-90,-45,0,45,90])
        plt.plot([rowArg, rowArg], [0, len(histCol)], 'k-', lw=4)
        plt.plot([colArg, colArg], [0, len(histRow)], 'k-', lw=2)
        #plt.xticks([-270,-225,-180,-135,-90,-45,0,45,90])
        #plt.yticks([0,45,90,135,180])
        plt.show()

    max_r = max(histRow)  # Find the maximum y value
    xr = [x for x in range(len(histRow)) if histRow[x] > max_r/2.0]
    print(min(xr), max(xr))
    azFWHM = radAng[max(xr)]-radAng[min(xr)]
    print('radAng1 = ',radAng[max(xr)])
    print('radAng2 = ', radAng[min(xr)])
    print('radFWHM = ', azFWHM)
    max_c = max(histCol)
    xc = [x for x in range(len(histCol)) if histCol[x] > max_c/2.0]
    radFWHM = azAng[max(xc)] - azAng[min(xr)]
    print('azFWHM = ', radFWHM)
    plt.figure()
    plt.title('Radial Resolution = %f degrees'%radFWHM)
    plt.xlabel('Radial Angle [degrees]')
    plt.plot(radAng,histCol)
    plt.show()
    print(len(histRow))
    print(len(azAng))
    plt.figure()
    plt.title('Azimuthal Resolution = %f degrees'%azFWHM)
    plt.xlabel('Azimuthal Angle [degrees]')
    plt.plot(azAng,histRow)
    return

### Real time neutron image reconstruction algorithm

def imPlotRT(plane1Dets,plane2Dets,plane1Times,plane2Times,plane1NeutronPulseADC,plane2NeutronPulseADC):
    import csv
    import numpy as np
    import math
    import matplotlib.pyplot as plt
    import matplotlib
    import pylab as pl
    import time
    import pandas as pd
    from mpl_toolkits.mplot3d import Axes3D
    import healpy as hp
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
    coneVector = []
    coneAngles = []
    cones = []
    mu = []
    weights = []
    adcCalVals = []
    radii = 0

    plane2DetScale = []
    print(plane2Dets)
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
    tic = time.time()
    L = [len(plane1Times), len(plane1Dets)]
    for i in range(0,int(min(L))-1): #range(0,len(plane1Times))
        for n in range(int(min(L))-1):
            if plane2Times[n] - plane1Times[i] <= 10000 and plane2Times[n] - plane1Times[i] > 0:
                x1 = plane1Local[plane1Dets[i]]
                x2 = plane2Local[plane2DetScale[n]]
                #print('x1 = ',x1)
                dist = np.sqrt((x2[0]-x1[0])**2 + (x2[1]-x1[1])**2 + (x2[2])**2)
                distance += [dist]
                timeSeparation = (plane2Times[n]-plane1Times[i])*timeScale
                energy = (1/(1.602*10**(-13)))*0.5*(1.675*10**(-27))*(dist/timeSeparation)**2
                neutronEnergyTOF += [energy] #MeV
                adcCalVals += [plane2NeutronPulseADC[n]]
                weights += [1/dist**2]
                coneVector += [x1-x2]
                #coneAngles += [math.degrees(math.atan(math.sqrt(neutronEnergyADC[i]/neutronEnergyTOF[i])))]
                #print('Energy = ',energy,' MeV')
                break
        if i%100000 == 0:
            toc = time.time()
            print('i = ',i)
            print('elapsed time = ',toc-tic, 's')

#                        x1 = plane1Local[plane1Dets[i]]
#                        x2 = plane2Local[plane2DetScale[n]]
#                        dist = np.sqrt((x2[0]-x1[0])**2 + (x2[1]-x1[1])**2 + (x2[2])**2)
#                        distance += [dist]
#                        timeSeparation = (plane2Times[n]-plane1Times[i])*timeScale
#                        energy = (1/(1.602*10**(-16)))*0.5*(1.675*10**(-27))*(dist/timeSeparation)**2 #keV
#                        energyADC = slope*plane1NeutronPulseADC[i] + intercept
#                        energyTotal = energyADC + energy
#                        neutronEnergyTOF += [energy] #keV
#                        adcValP2 += [plane2NeutronPulseADC[n]]
#                        neutronEnergyADC += [energyADC] #keV
#                        neutronEnergy += [energyTotal] #keV
                        #print('angle = ',np.deg2rad(math.sqrt((slope*plane1NeutronPulseADC[i] + intercept)/energyTotal)))
#                        coneAngles += [math.atan(np.deg2rad(math.sqrt((slope*plane1NeutronPulseADC[i] + intercept)/energyTotal)))]
#                        mu += [np.cos(math.atan(np.deg2rad(math.sqrt((slope*plane1NeutronPulseADC[i] + intercept)/energyTotal))))]
#                        weights += [1/dist**2]
#                        coneVector += [x1-x2]

    distance = np.array(distance)
    neutronEnergyTOF = np.array(neutronEnergyTOF)
    neutronEnergyTOF = neutronEnergyTOF*10**3 #keV
    neutronEnergy = neutronEnergyTOF
    adcCalVals = np.array(adcCalVals)
    slope, intercept = np.polyfit(adcCalVals, neutronEnergyTOF, 1)
    neutronEnergyADC += [slope*plane1NeutronPulseADC[i] + intercept]
    neutronEnergyADC = np.array(neutronEnergyADC)
    coneVector = np.array(coneVector,dtype = 'float')
    weights = np.array(weights, dtype='float')
    m = 0
    for i in range(0,int(min(L))-1): #range(0,len(plane1Times))
        for n in range(int(min(L))-1):
            if plane2Times[n] - plane1Times[i] <= 10000 and plane2Times[n] - plane1Times[i] > 0:
                x1 = plane1Local[plane1Dets[i]]
                x2 = plane2Local[plane2DetScale[n]]
                #print('x1 = ',x1)
                coneAngles += [math.degrees(math.atan(math.sqrt((slope*plane1NeutronPulseADC[i] + intercept)/neutronEnergyTOF[m])))]
                mu += [math.degrees(math.atan(math.sqrt((slope*plane1NeutronPulseADC[i] + intercept)/neutronEnergyTOF[m])))]
                m+=1
                #coneAngles += [math.degrees(math.atan(math.sqrt(neutronEnergyADC[i]/neutronEnergyTOF[i])))]
                #print('Energy = ',energy,' MeV')
                break
        if i%100000 == 0:
            toc = time.time()
            print('i = ',i)
            print('elapsed time = ',toc-tic, 's')
    mu = np.array(mu)
    coneAngles = np.array(coneAngles)
    neutronEnergy = np.array(neutronEnergy,dtype='float')
    neutronEnergy = neutronEnergy*10**(-3)
#    numpy.savetxt("neutron.csv", neutronEnergyTOF, delimiter=",")

#######################################################################################
####              create unit vector for cones                                     ####
#######################################################################################
    unitNorm = 0
    unitVector = []
    for i in range(0,len(coneVector)):
        temp = coneVector[i,:]
        unitNorm = np.linalg.norm(temp)
        unitVector += [temp/unitNorm]

    unitVector = np.array(unitVector, dtype = 'float')

#### Generate the cones for image reconstruction ####
    for i in range(0,len(coneAngles)):
        radii = distance[i]*math.tan(coneAngles[i]/2)
        r = np.linspace(0, radii, 50)
        p = np.linspace(0, 2*np.pi, 50)
        R, P = np.meshgrid(r, p)
        Z = ((R**2 - 1)**2)
        X = R*np.cos(P)
        Y = R*np.sin(P)
        cones += [[radii],[distance[i]],[coneAngles[i]]]
        #ax.plot_surface(X, Y, Z)
        #ax.set_xlabel('X Label')
        #ax.set_ylabel('Y Label')
        #ax.set_zlabel('Z Label')
    #plt.legend(loc = 'best')
    #plt.show()
    df = pd.DataFrame(cones)
    df.to_csv("ConesGenerated.csv")
    np.savetxt('GeneratedCones.csv',cones,delimiter=",")
    #ax.plot_surface(cones[0], Y, Z, cmap=plt.cm.YlGnBu_r)
    hpindex = 912
    theta,phi = np.asarray(hp.pix2ang(16,hpindex-1)) * (180./np.pi)
    if phi > 180: phi = -(360. - phi)
    nside = 64
    [x_,y_,z_] = hp.pix2vec(nside,range(12*nside*nside))#201))
    k = np.array(list(zip(x_,y_,z_)))
    cmap_ = plt.cm.jet
    cmap_.set_under("w")
    im = np.zeros(12*nside*nside)
    angunc = 3.
    b = 0
    sigma = 0.045

    for i in range(len(mu)):#len(sequences)):
        #for n in range(0,500):#len(k[:,0])):
            #print('n = ',n)
        b += (weights[i] / (sigma * np.sqrt(2.*np.pi))) * np.exp(-(np.dot(k,unitVector[i,:]) - mu[i])**2/(2. * sigma**2))
        #b[b < 1e-5] = 0
        #val = np.array(val)
        im += b

#pixels = (pixels/normB)
#pixels = np.ravel(pixels)
#maxPix = 0
#newNorm = 0
#normPix = pixels-min(pixels[:])
#newPix = normPix/max(normPix)
#newPix = newPix.reshape([len(theta),len(phi)])
    pixels = im/max(im)
    pixels = np.ravel(pixels)
    normPix = pixels-min(pixels[:])
    newPix = normPix/max(normPix)
    newPix = newPix.reshape(12*nside*nside)
    latra = [-90,90]
    lonra = [-180,180]
#    p = hp.cartview(newPix, rot=(90,0), lonra=lonra,latra=latra, return_projected_map=True)
#    hp.projplot(hp.pix2ang(16,hpindex-1), 'k*', markersize = 8)
    #hp.graticule()
#    plt.close("all")
#    plt.figure()
#    p = plt.imshow(p, cmap=cmap_, origin='lower', interpolation='nearest', extent=(lonra[1],lonra[0],latra[0],latra[1]))
    #plt.scatter(phi, 90-theta, marker='x')
#    plt.xlim(lonra[0], lonra[1]); plt.ylim(latra[0], latra[1])
#    plt.colorbar(p, fraction=0.046, pad=0.04)
#    plt.title('Neutron Image of PuBe Source')
#    plt.xlabel('Radial Angle [degrees]')
#    plt.ylabel('Azimuthal Angle [degrees]')
#    plt.xticks([-180,-135,-90,-45,0,45,90,135,180])
#    plt.yticks([-90,-45,0,45,90])

#    energyHist = np.histogram(neutronEnergy,100)
#    a = energyHist[0]
#    b = energyHist[1]
#    c = b[0:100]
#    plt.figure(1)
#    plt.plot(c,a,'r--')
#    plt.xlabel('Neutron Energy [MeV]')
#    plt.ylabel('Counts')
#    plt.title('Neutron Spectrum')
#    plt.autoscale(enable=True,axis='x',tight=True)
#    pl.xticks(rotation=45)
    #plt.legend(loc='upper right')
    #plt.plot(d,f)
#    plt.show()

#    numpy.savetxt("neutronEnergy.csv", c, delimiter=",")
#    numpy.savetxt("neutronCounts.csv", a, delimiter=",")

    return newPix, latra, lonra
