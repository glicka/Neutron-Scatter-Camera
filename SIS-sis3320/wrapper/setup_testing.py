from distutils.core import setup, Extension
import numpy

setup(name='sis3320',
    description='A module to readout the SIS 3320 card',
    version='0.1.0',
    ext_modules = [
        Extension('sis',
            ['src/pywrapper.c','src/SIS3150_070317_test.c','src/SIS3302Configuration.c',\
             'src/VMECalls.c', 'src/loadCalibration.c'],
            include_dirs = [numpy.get_include(), 'include'],
            library_dirs = ['/home/glicka/SIS/lib'],
            runtime_library_dirs = ['/home/glicka/SIS/lib'],
            libraries = ['sis3150'],
            extra_compile_args=["-O3","-std=c99", "-w"],
            extra_link_args=["-O3"],
        ),
    ]
)
