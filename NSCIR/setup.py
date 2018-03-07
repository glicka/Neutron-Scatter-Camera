# -*- coding: utf-8 -*-
"""
Python setup file for Neutron Scatter Camera Image Reconstruction

"""

#from distutils.core import setup, Extension
import os
from setuptools import setup#, Extension
import numpy

setup(
    name='NSCIR',
    description='Neutron Scatter Camera Image Reconstruction for sis3316 Data',
    author='Adam Glick',
    author_email='aglick@berkeley.edu',
    version='1.0',
    packages=['nscir'],
    package_dir={'nscir': 'src/nscir'},
)
