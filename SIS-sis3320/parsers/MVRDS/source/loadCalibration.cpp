#include "loadCalibration.h"

//void loadCalMultipliersFromFile2D( double multAry[][NUM_COLS], string filename )
//{
//  ifstream inFile( filename.c_str() );
//  string inLine;
//  int i;
//  int modNum = 0;
//  int adcNum = 0;
//  double val;

//  if (inFile.is_open())
//  {
//    for( i=0; i < NUM_ROWS*NUM_COLS; i++ )
//    {
//      //Read the next value from the file
//      getline( inFile, inLine );
//      val = atof( inLine.c_str() );
//      multAry[modNum][adcNum] = val;
//      adcNum++;
//      if ( (i+1) % 8 == 0)
//      {
//        modNum++;
//        adcNum = 0;
//      }
//    }
//    inFile.close();
//  }
//  else
//  {
//      cout << "Warning: Calibration file not found!" << endl;
//      exit(-1);
//  }
//  return;
//}

//void loadMult1D( double multAry[NUM_DETECTORS], string filename )
//{
//  ifstream inFile( filename.c_str() );
//  string inLine;
//  int i;
//  double val;

//  if (inFile.is_open())
//  {
//    for( i=0; i < NUM_ROWS*NUM_COLS; i++ )
//    {
//      //Read the next value from the file
//      getline( inFile, inLine );
//      val = atof( inLine.c_str() );
//      multAry[i] = val;
//    }
//  inFile.close();
//  }
//  else
//  {
//    cout << "Warning: Calibration file not found!" << endl;
//    exit(-1);
//  }
//  return;
//}

//void loadCalDataFromFile( double mAry[][NUM_COLS], double bAry[][NUM_COLS],
//                     string filename )
//{
//  ifstream inFile( filename.c_str() );
//  string inLine;
//  int i;
//  int modNum = 0;
//  int adcNum = 0;
//  double mval, bval;

//  if (inFile.is_open())
//  {
//    for( i=0; i < NUM_ROWS*NUM_COLS; i++ )
//    {
//      //Read the next value from the file
//      inFile >> inLine;
//      bval = atof( inLine.c_str() );
//      inFile >> inLine;
//      mval = atof( inLine.c_str() );
//      mAry[modNum][adcNum] = mval;
//      bAry[modNum][adcNum] = bval;
//      adcNum++;
//      if ( (i+1) % 8 == 0)
//      {
//        modNum++;
//        adcNum = 0;
//      }
//    }
//    inFile.close();
//  }
//  else
//  {
//    cout << "Warning: Calibration file not found!" << endl;
//    exit(-1);
//  }
//  return;
//}

void loadData1D( double mAry[NUM_DETECTORS], double bAry[NUM_DETECTORS],
                 string filename )
{
  ifstream inFile( filename.c_str() );
  string inLine;
  int i;
  double mval, bval;

  if (inFile.is_open())
  {
    for( i=0; i < NUM_DETECTORS; i++ )
    {
      //Read the next value from the file
      inFile >> inLine;
      bval = atof( inLine.c_str() );
      inFile >> inLine;
      mval = atof( inLine.c_str() );
      mAry[i] = mval;
      bAry[i] = bval;
    }
    inFile.close();
  }
  else
  {
    cout << "Warning: Calibration file not found!" << endl;
    exit(-1);
  }
  return;
}
