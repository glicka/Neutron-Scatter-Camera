#ifndef LOAD_CALIBRATION_H_
#define LOAD_CALIBRATION_H_

#include<iostream>
#include<fstream>
#include<cstdlib>
#include<string>
using namespace std;

//Cols = #ADCs/Module, Rows = # of Modules
//#define NUM_COLS 8
//#define NUM_ROWS 19
#define NUM_DETECTORS 100

//// Load calibration multipliers from *filename* into a 2D array
//void loadCalMultipliersFromFile( double multAry[][NUM_COLS], string filename );

//// Load calibration values into a 1D array instead of 2 (for use in this parser)
//void loadMult1D( double multAry[NUM_DETECTORS], string filename );

//// Load Linear calibration from file (slope and y-intercept)
//void loadCalDataFromFile( double mAry[][NUM_COLS], double bAry[][NUM_COLS],
//                     string filename );

// Same as above, but output it in 1D arrays instead of 2D
void loadData1D( double mAry[NUM_DETECTORS], double bAry[NUM_DETECTORS],
                 string filename );

#endif
