#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Oct 16 17:05:08 2017

@author: glicka
"""

def calculateAbsorbedDose(neutronEnergyData,tic):
    import numpy as np
    import scipy as sp
    import matplotlib.pyplot as plt
    import time
    import csv
    
    oxyEnergyNP = []
    oxySigmaNP = []    
    oxyEnergyNA = []
    oxySigmaNA = []
    oxyEnergyNT = []
    oxySigmaNT = []    
    oxyEnergyND = []
    oxySigmaND = []
    hydroEnergyNE = []
    hydroSigmaNE = []
#    hydroEnergyNG = []
#    hydroSigmaNG = []
    inputOxyNP = "oxy16(n,p).txt"
    QoxyNP = 9.63680e+06 #eV
    inputOxyNA = "oxy16(n,a).txt"
    QoxyNA = 2.21430e+06 #eV
    inputOxyNT = "oxy16(n,t).txt"
    QoxyNT = 1.44790e+07 #eV
    inputOxyND = "oxy16(n,d).txt"
    QoxyND = 9.90300e+06 #eV
    QoxyN2A = 1.28632e+07 #eV
#    inputHydroNG = "hydro1(n,gamma).txt"
#    QHNG = 2.22463e+06 #eV
    inputHydroNE = "hydro1(n,elastic).txt"
    #inputFn2 = "sigmaAbsorbedH.txt"
    with open(inputOxyNP) as csvFile: #(n,p) reactions
        reader = csv.reader(csvFile, delimiter = ' ')
        for row in reader:
            oxyEnergyNP += [row[2]]
            oxyEnergyNP += [row[4]]
            oxyEnergyNP += [row[6]]
            oxySigmaNP += [row[3]]
            oxySigmaNP += [row[5]]
            oxySigmaNP += [row[7]]
    with open(inputOxyNA) as csvFile: #(n,alpha) reactions
        reader = csv.reader(csvFile, delimiter = ' ')
        for row in reader:
            oxyEnergyNA += [row[2]]
            oxyEnergyNA += [row[4]]
            oxyEnergyNA += [row[6]]
            oxySigmaNA += [row[3]]
            oxySigmaNA += [row[5]]
            oxySigmaNA += [row[7]]
    with open(inputOxyNT) as csvFile: #(n,p) reactions
        reader = csv.reader(csvFile, delimiter = ' ')
        for row in reader:
            oxyEnergyNT += [row[2]]
            oxyEnergyNT += [row[4]]
            oxyEnergyNT += [row[6]]
            oxySigmaNT += [row[3]]
            oxySigmaNT += [row[5]]
            oxySigmaNT += [row[7]]
    with open(inputOxyND) as csvFile: #(n,p) reactions
        reader = csv.reader(csvFile, delimiter = ' ')
        for row in reader:
            oxyEnergyND += [row[2]]
            oxyEnergyND += [row[4]]
            oxyEnergyND += [row[6]]
            oxySigmaND += [row[3]]
            oxySigmaND += [row[5]]
            oxySigmaND += [row[7]]
#    with open(inputHydroNG) as csvFile: #(n,alpha) reactions
#        reader = csv.reader(csvFile, delimiter = ' ')
#        for row in reader:
#            hydroEnergyNG += [row[2]]
#            hydroEnergyNG += [row[4]]
#            hydroEnergyNG += [row[6]]
#            hydroSigmaNG += [row[3]]
#            hydroSigmaNG += [row[5]]
#            hydroSigmaNG += [row[7]]
    with open(inputHydroNE) as csvFile:
        reader = csv.reader(csvFile, delimiter = ' ')
        for row in reader:
            hydroEnergyNE += [row[2]]
            hydroEnergyNE += [row[4]]
            hydroEnergyNE += [row[6]]
            hydroSigmaNE += [row[3]]
            hydroSigmaNE += [row[5]]
            hydroSigmaNE += [row[7]]
            
    oxyEnergyNP = np.array(oxyEnergyNP,dtype = 'float')
    oxySigmaNP = np.array(oxySigmaNP, dtype = 'float')
    oxyEnergyNA = np.array(oxyEnergyNA,dtype = 'float')
    oxySigmaNA = np.array(oxySigmaNA, dtype = 'float')
    oxyEnergyNT = np.array(oxyEnergyNT,dtype = 'float')
    oxySigmaNT = np.array(oxySigmaNT, dtype = 'float')
    oxyEnergyND = np.array(oxyEnergyND,dtype = 'float')
    oxySigmaND = np.array(oxySigmaND, dtype = 'float')
#    hydroEnergyNG = np.array(hydroEnergyNG,dtype = 'float')
#    hydroSigmaNG = np.array(hydroSigmaNG, dtype = 'float')
    hydroEnergyNE = np.array(hydroEnergyNE,dtype = 'float')
    hydroSigmaNE = np.array(hydroSigmaNE, dtype = 'float')
    #print(max(oxySigma))
    hydroN = (10**3)*6.022*10**(23)/1.00784 #atoms/kg
    oxyN = (10**3)*6.022*10**(23)/15.999 #atoms/kg
    hydroQNE = 0#931.5*(1.00866491588 + 1.00784 - 2.01410178) #MeV
    #oxyQ = 931.5*(1.00866491588 + 15.999 -16.9991315) #MeV
###########################################################################################################################
####                Start by calculating KERMA in water, Dose is absorbed KERMA                                        ####
###########################################################################################################################
#Kerma Factors of Elements and Compounds for Neutron Energies Below 30 MeV R. S. CASWELL, J. J. COYNET and M. L. RANDOLPH 2
    energyHist = np.histogram(neutronEnergyData,1000)#len(neutronEnergy))
    counts = energyHist[0]
    b1 = energyHist[1]
    energy = b1[1:1001]
    plt.plot(energy,counts)
    plt.show()
#    K = flux*kermaFactor
    #sigmaH = 
    #sigmaO =
    kFactor = []
    temp = 0        
    m = len(hydroEnergyNE)
    #### We must step through the distance we are in water which is not done here ####
    for i in range(len(energy)):
        sigmaHNE = 0
        sigmaOxyNP = 0
        sigmaOxyNA = 0
        sigmaOxyND = 0
        sigmaOxyNT = 0
        pEnergyHydroNE = 0#energy[i]/2
        pEnergyOxyNP = 0
        pEnergyOxyND = 0
        pEnergyOxyNT = 0
        pEnergyOxyNA = 0
        for n in range(len(oxyEnergy)-1):
            if n < m:
                if hydroEnergyNE[n] < energy[i] < hydroEnergyNE[n+1]:
                    sigmaHNE = hydroSigmaNE[n] + (energy[i]-hydroEnergyNE[n])*(hydroSigmaNE[n+1]-hydroSigmaNE[n])/(hydroEnergyNE[n+1]-hydroEnergyNE[n])
                    pEnergyHydroNE = energy[i]/2
                elif hydroEnergyNE[n] == energy[i]:
                    sigmaHNE = hydroSigmaNE[n]
                    pEnergyHydroNE = energy[i]/2
            
            if oxyEnergyNP[n] < energy[i] < oxyEnergyNP[n+1]:
                sigmaOxyNP = oxySigmaNP[n] + (energy[i]-oxyEnergyNP[n])*(oxySigmaNP[n+1]-oxySigmaNP[n])/(oxyEnergyNP[n+1]-oxyEnergyNP[n])
                pEnergyOxyNP = QoxyNP*15.99/(1.00866491588 + 15.999)
            elif oxyEnergyNP[n] == energy[i]:
                sigmaOxyNP = oxySigmaNP[n]
                pEnergyOxyNP = QoxyNP*15.99/(1.00866491588 + 15.999)
            
            if oxyEnergyNA[n] < energy[i] < oxyEnergyNA[n+1]:
                sigmaOxyNA = oxySigmaNA[n] + (energy[i]-oxyEnergyNA[n])*(oxySigmaNA[n+1]-oxySigmaNA[n])/(oxyEnergyNA[n+1]-oxyEnergyNA[n])
                pEnergyOxyNA = QoxyNA*15.99/(1.00866491588 + 15.999)
            elif oxyEnergyNA[n] == energy[i]:
                sigmaOxyNA = oxySigmaNA[n]
                pEnergyOxyNA = QoxyNA*15.99/(1.00866491588 + 15.999)
                
            if oxyEnergyND[n] < energy[i] < oxyEnergyND[n+1]:
                sigmaOxyND = oxySigmaND[n] + (energy[i]-oxyEnergyND[n])*(oxySigmaND[n+1]-oxySigmaND[n])/(oxyEnergyND[n+1]-oxyEnergyND[n])
                pEnergyOxyND = QoxyND*15.99/(1.00866491588 + 15.999)
            elif oxyEnergyND[n] == energy[i]:
                sigmaOxyND = oxySigmaND[n]
                pEnergyOxyND = QoxyND*15.99/(1.00866491588 + 15.999)
                
            if oxyEnergyNT[n] < energy[i] < oxyEnergyNT[n+1]:
                sigmaOxyNT = oxySigmaNT[n] + (energy[i]-oxyEnergyNT[n])*(oxySigmaNT[n+1]-oxySigmaNT[n])/(oxyEnergyNT[n+1]-oxyEnergyNT[n])
                pEnergyOxyNT = QoxyNT*15.99/(1.00866491588 + 15.999)
            elif oxyEnergyNT[n] == energy[i]:
                sigmaOxyNT = oxySigmaNT[n]
                pEnergyOxyNT = QoxyNT*15.99/(1.00866491588 + 15.999)
                
        temp += hydroN*sigmaHNE*pEnergyHydroNE + oxyN*sigmaOxyNP*pEnergyOxyNP + oxyN*sigmaOxyNA*pEnergyOxyNA + oxyN*sigmaOxyND*pEnergyOxyND + oxyN*sigmaOxyNT*pEnergyOxyNT
        
    kFactor += [1.602177*10**(-19)*temp] #J/cm^2*kg
    
    kFactor = np.array(kFactor,dtype = 'float')
    
    return kFactor
    
        