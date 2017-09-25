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
    #phi = linspace(-90,90,poins)
    #theta = linspace(-180,180,15)
    for i in range(-90,90,points):
        for n in range(-180,180,points):
            coords += [[np.sin(np.deg2rad(i))*np.cos(np.deg2rad(n)),np.sin(np.deg2rad(i))*np.sin(np.deg2rad(n)),np.cos(np.deg2rad(i))]]
            coords1 += [[i,n]]
    coords = np.asarray(coords,dtype = 'float')
    return(coords, coords1)