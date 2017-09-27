#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Aug 30 08:06:22 2017

@author: aglick
"""

import time
import numpy as np
import csv
import math
import matplotlib.pyplot as plt
import matplotlib

#start at 330000
tic = time.time()
mu = []
coneVectors = []
weights = []
sigma = 0.1
b = 0
with open('muVals.csv','r') as csvfile:
    temp = csv.reader(csvfile)
    for row in temp:
        mu += row

with open('coneVectors.csv','r') as csvfile:
    temp = csv.reader(csvfile)
    for row in temp:
        coneVectors += [row]
with open('weights.csv','r') as csvfile:
    temp = csv.reader(csvfile)
    for row in temp:
        weights += row

        
mu = np.array(mu,dtype = 'float')
coneVector = np.array(coneVectors,dtype = 'float')
weights = np.array(weights,dtype = 'float')
#print('coneVector = ',coneVector)
#plane1NeutronDets = np.array(plane1NeutronDets,dtype = 'int')
#plane1NeutronDets = np.array(plane1NeutronDets,dtype = 'int')
#plane1NeutronPulseData = np.array(plane1NeutronPulseData,dtype = 'float')
#plane1NeutronTimes = np.array(plane1NeutronTimes,dtype = 'float')
#plane2NeutronDets = np.array(plane2NeutronDets,dtype = 'float')
#plane2NeutronDets = np.array(plane2NeutronDets,dtype = 'int')
#plane2NeutronDets = np.array(plane2NeutronDets,dtype = 'int')
#plane2NeutronDets = np.array(plane2NeutronDets,dtype = 'int')
#plane2NeutronPulseData = np.array(plane2NeutronPulseData,dtype = 'float')
#plane2NeutronTimes = np.array(plane2NeutronTimes,dtype = 'float')

#adc2MeV(plane1NeutronPulseData)
#slope, intercept = adc2keV(plane1NeutronPulseData)
#cones = generateCones(slope,intercept,plane1NeutronDets,plane2NeutronDets,plane1NeutronTimes,plane2NeutronTimes,plane1NeutronPulseData,plane2NeutronPulseData)

points = 100
unitSphere, coords, theta, phi = generateSphere(points)
pixels = np.zeros([len(phi),len(theta)]) 

print('Generating Neutron Image')
maxB = 0
print('range end = ',len(unitSphere[:,0]))
for n in range(0,len(unitSphere[:,0])):
    b = 0
#     c = 0

    for i in range(0,len(mu)):
        #print('cone number = ', i)
        b += (1/(weights[i]*sigma*np.sqrt(2*math.pi)))*math.exp((np.dot(unitSphere[n,:],coneVector[i,:])-mu[i])**2/(2*sigma**2))
        #c += (1/(weights[i]*sigma*np.sqrt(2*math.pi)))*math.exp((np.dot(unitSphere[n,1],coneVector[i,1])-mu[i])**2/(2*sigma**2))
    pixels[phi.tolist().index(coords[n,0]),theta.tolist().index(coords[n,1])] = b#[[b,c]]
    if n%1000 == 0:
        print('iter = ',n)
        print('elapsed = ', time.time()-tic)
        print('b = ',b)
    if maxB < b:
        maxB = b
    #recon = [[b],[b]]
    #recon = np.array(recon,dtype='float')
#    for row, colcolor in zip(recon, colors):
#        pyplot.plot(2darray, column, "-", color=colcolor)

pixels = np.array(pixels)
plt.figure()
plt.imshow(pixels, vmin=0, vmax=maxB, extent=[0,180,0,360], aspect="auto")
plt.xlabel('Azimuthal Angle [degrees]')
plt.ylabel('Radial Angle [degrees]')
plt.title('Neutron Image of PuBe Source')
#    plt.pcolor(pixels, extent=[-90,90,-180,180], aspect="auto")
cb = plt.colorbar()
cb.set_label('pixel values')
plt.show()