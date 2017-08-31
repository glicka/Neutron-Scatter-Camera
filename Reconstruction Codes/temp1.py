#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Aug 30 08:06:22 2017

@author: aglick
"""

import time
import numpy as np
import csv
import time
#start at 330000

plane1NeutronDets = []
plane1NeutronPulseData = []
plane1NeutronTimes = []
plane2NeutronDets = []
plane2NeutronPulseData = []
plane2NeutronTimes = []

with open('plane1NeutronDets.csv','r') as csvfile:
    temp = csv.reader(csvfile)
    for row in temp:
        plane1NeutronDets += row

with open('plane1NeutronPulseData.csv','r') as csvfile:
    temp = csv.reader(csvfile)
    for row in temp:
        plane1NeutronPulseData += row

with open('plane1NeutronTimes.csv','r') as csvfile:
    temp = csv.reader(csvfile)
    for row in temp:
        plane1NeutronTimes += row

with open('plane2NeutronDets.csv','r') as csvfile:
    temp = csv.reader(csvfile)
    for row in temp:
        plane2NeutronDets += row

with open('plane2NeutronPulseData.csv','r') as csvfile:
    temp = csv.reader(csvfile)
    for row in temp:
        plane2NeutronPulseData += row

with open('plane2NeutronTimes.csv','r') as csvfile:
    temp = csv.reader(csvfile)
    for row in temp:
        plane2NeutronTimes += row
        
plane1NeutronDets = np.array(plane1NeutronDets,dtype = 'float')
plane1NeutronDets = np.array(plane1NeutronDets,dtype = 'int')
plane1NeutronDets = np.array(plane1NeutronDets,dtype = 'int')
plane1NeutronDets = np.array(plane1NeutronDets,dtype = 'int')
plane1NeutronPulseData = np.array(plane1NeutronPulseData,dtype = 'float')
plane1NeutronTimes = np.array(plane1NeutronTimes,dtype = 'float')
plane2NeutronDets = np.array(plane2NeutronDets,dtype = 'float')
plane2NeutronDets = np.array(plane2NeutronDets,dtype = 'int')
plane2NeutronDets = np.array(plane2NeutronDets,dtype = 'int')
plane2NeutronDets = np.array(plane2NeutronDets,dtype = 'int')
plane2NeutronPulseData = np.array(plane2NeutronPulseData,dtype = 'float')
plane2NeutronTimes = np.array(plane2NeutronTimes,dtype = 'float')

#adc2MeV(plane1NeutronPulseData)

cones = generateCones(plane1NeutronDets,plane2NeutronDets,plane1NeutronTimes,plane2NeutronTimes,plane1NeutronPulseData,plane2NeutronPulseData)