#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Sep 25 13:03:47 2017

@author: glicka
"""

def generateSphere(points):
    import numpy as np
    import math
    coords = []#np.zeros(180/points,360/points)
    coords1 = []
    theta = []
    phi = []
    #phi = linspace(-90,90,poins)
    #theta = linspace(-180,180,15)
    temp = np.linspace(0,180,points)
    temp1 = np.linspace(0,360,points)
    for i in temp:
        for n in temp1:
            coords += [[np.sin(np.deg2rad(i))*np.cos(np.deg2rad(n)),np.sin(np.deg2rad(i))*np.sin(np.deg2rad(n)),np.cos(np.deg2rad(i))]]
            coords1 += [[i,n]]
            if i==0:
                theta += [n]
        phi += [i]
    coords = np.asarray(coords,dtype = 'float')
    coords1 = np.asarray(coords1,dtype = 'float')
    theta = np.asarray(theta,dtype = 'float')
    phi = np.asarray(phi,dtype = 'float')
    return(coords, coords1, theta, phi)