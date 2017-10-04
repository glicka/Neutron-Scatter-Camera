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
import healpy as hp
#start at 330000
tic = time.time()
mu = []
coneVectors = []
weights = []
neutronDose = []
neutronEnergy = []
sigma = 0.045
b = 0
with open('muValsSinTheta.csv','r') as csvfile:
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
with open('neutronDose.csv','r') as csvfile:
    temp = csv.reader(csvfile)
    for row in temp:
        neutronDose += row
with open('neutronEnergy.csv','r') as csvfile:
    temp = csv.reader(csvfile)
    for row in temp:
        neutronEnergy += row
        
mu = np.array(mu,dtype = 'float')
coneVector = np.array(coneVectors,dtype = 'float')
weights = np.array(weights,dtype = 'float')
neutronDose = np.array(neutronDose,dtype = 'float')
neutronEnergy = np.array(neutronEnergy,dtype = 'float')
totalDose = sum(neutronDose)*10**6
unitNorm = 0
unitVector = []
for i in range(0,len(coneVector[:,0])):
    temp = coneVector[i,:]
    unitNorm = np.linalg.norm(temp)
    unitVector += [temp/unitNorm]

unitVector = np.array(unitVector, dtype = 'float')
#print('unitVector = ',unitVector)
#print('coneVector = ',coneVector)
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
pixels = np.zeros([len(theta),len(phi)]) 
pixels1 = np.zeros([len(theta),len(phi)]) 
#pixels = (pixels/normB)
#sShape = len(unitSphere[:,0])
#unitSphere = np.ravel(unitSphere)
#normSphere = unitSphere-min(unitSphere[:])
#newSphere = normSphere/max(normSphere)
#newSphere = newSphere.reshape([sShape,3])
#vShape = len(coneVector[:,0])
#coneVector = np.ravel(coneVector)
#normVector = coneVector-min(coneVector[:])
#newVector = normVector/max(normVector)
#newVector = newVector.reshape([vShape,3])
print('Generating Neutron Image')
maxB = 0
normB = 0
normB1 = 0
#print('range end = ',len(unitSphere[:,0]))
print('weights = ',len(weights))
print('mu = ',len(mu))
print('unitVector = ',len(unitVector[:,0]))
print('unitSphere = ',len(unitSphere[:,0]))
#print('newSphere = ',len(newSphere[:,0]))
xfRange = np.linspace(0,len(mu)-1,len(mu),dtype = 'int')
xsRange = np.linspace(0,len(unitSphere[:,0])-1,len(unitSphere[:,0]),dtype = 'int')
#for n in range(0,len(unitSphere[:,0])):
#    b = 0
#     c = 0
#    for i in range(0,len(mu)):#xfRange:#range(0,len(mu)):
        #print('cone number = ', i)
        #print(i)
        #print(unitVector[i,:])
#        temp = mu[i]#np.cos(mu[i])
        #print('dot product = ',math.exp(((np.dot(unitSphere[n,:],unitVector[i,:])-temp)**2)/(2*sigma**2)))
#        b += (1/(weights[i]*sigma*np.sqrt(2*math.pi)))*math.exp((np.dot(unitSphere[n,:],unitVector[i,:])-temp)**2/(2*sigma**2))#math.exp((sum(p*q for p,q in zip(unitSphere[n,:],coneVector[i,:]))-temp)**2/(2*sigma**2))#math.exp((np.dot(unitSphere[n,:],coneVector[i,:])-temp)**2/(2*sigma**2))
        #c += (1/(weights[i]*sigma*np.sqrt(2*math.pi)))*math.exp((np.dot(unitSphere[n,1],coneVector[i,1])-mu[i])**2/(2*sigma**2))
#    pixels[theta.tolist().index(coords[n,1]),phi.tolist().index(coords[n,0])] = b#[[b,c]]
    #print(theta.tolist().index(coords[n,1]))
    #print('coords = ',coords[n,1])
    #print('theta = ',theta[index(coords[n,1])])
    
#    normB += b
#    if n%5000 == 0:
#        print('iter = ',n)
#        print('elapsed = ', time.time()-tic)
#        print('theta = ',theta.tolist().index(coords[n,1]))
#        print('phi = ',phi.tolist().index(coords[n,0]))
        #print('b = ',b)
        #print('cos(mu) = ',np.cos(mu[i]))
        #print('unitSphere = ',unitSphere[n,:])
        #print('unitVector = ',np.abs(unitVector[i,:]))
        #print('mu = ',temp)
        #print('exp = ',math.exp((np.dot(unitSphere[n,:],unitVector[i,:])-temp)**2/(2*sigma**2)))
#    if maxB < b:
#        maxB = b
    #recon = [[b],[b]]
    #recon = np.array(recon,dtype='float')
#    for row, colcolor in zip(recon, colors):
#        pyplot.plot(2darray, column, "-", color=colcolor)
#pixels = np.array(pixels)

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
print(len(k))
print(len(weights))
for i in range(len(mu)):#len(sequences)):
    #for n in range(0,500):#len(k[:,0])):
        #print('n = ',n)
    b += (weights[i] / (sigma * np.sqrt(2.*np.pi))) * np.exp(-(np.dot(k,unitVector[i,:]) - mu[i])**2/(2. * sigma**2))
    b[b < 1e-5] = 0
    #val = np.array(val)
    im += val

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

#subtraction = newPix1-newPix
#for row in pixels:
#    if maxPix < max(row):
#        maxPix = max(row)
#    newNorm += sum(row)
#print('maxPix = ',maxPix)
#print('newNorm = ',newNorm)
#print('total dose = ',totalDose)
#print('sum of pixels = ',newNorm)


#totalDose*(su/normB)
#totalDose*(maxPix/newNorm)
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

#plt.figure()
#plt.imshow(newPix, vmin=0, vmax=1, extent=[0,360,0,180], aspect="auto")
#plt.xlabel('Radial Angle [degrees]')
#plt.ylabel('Azimuthal Angle [degrees]')
#plt.title('Neutron Image of PuBe Source')
#    plt.pcolor(pixels, extent=[-90,90,-180,180], aspect="auto")
#cb = plt.colorbar()
#cb.set_label('Source Dose [nSv/hr]')
#plt.show()