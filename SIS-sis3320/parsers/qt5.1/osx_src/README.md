# SIS3302 QT5.1 OSX Parser

Parser configured by Joey Curtis (jccurtis) to work with OSX. 

----

## Prerequisites:

1) Install XCode
2) Install 5.1
3) Install HDF5 Library for OSX (need to compile). When compiling make sure to set the C++ (cxx) flag:
- include cxx flag with `./configure` commmand.

There are a variety of static library paths which has to be set including:

1) HDF5 Build Location: 

	/usr/local/hdf5

2) CPP Library (.pro file): 
	
	/usr/local/hdf5/lib/libhdf5_cpp.a

3) parserthread.cpp line 12:
	
	/usr/local/hdf5/include/H5Cpp.h

4) H5Include.h line 17 (Qt wants "" instead of <> in the c++ compiled HDF5 library):
	
	#include "hdf5.h"
	
5) pow function is ambiguous (different inputs in the XCode 10.8.sdk). Thus I cast the inputs as floats:

	const unsigned int TRIGGERBIT = pow(2.0,24.0);
    const unsigned int PILEBIT = pow(2.0,30.0);
    const unsigned int RETRIGBIT = pow(2.0,31.0);

6) Set library not found for `-lhdf5_cpp` in .pro file lines.