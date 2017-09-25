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
    for i in range(-90,90,points):
        for n in range(-180,180,points):
            coords += [[np.sin(np.deg2rad(i))*np.cos(np.deg2rad(n)),np.sin(np.deg2rad(i))*np.sin(np.deg2rad(n))]]
            
    coords = np.asarray(coords,dtype = 'float')
    return(coords)