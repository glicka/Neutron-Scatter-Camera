#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Jul  5 12:17:00 2017

@author: aglick
"""

def csvOpening(filename):
    import csv
    with open(filename,'r') as csvfile:

        return csv.reader(csvfile)