/***************************************************************************/
/*                                                                         */
/*  Filename: sis3150_energy_spectrum_utils.c                              */
/*                                                                         */
/*  Funktion: energy spectrum utilitz routines                             */
/*                                                                         */
/*  Autor:                TH                                               */
/*  date:                 06.06.2005                                       */
/*  last modification:    06.06.2005                                       */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*                                                                         */
/*  SIS  Struck Innovative Systeme GmbH                                    */
/*                                                                         */
/*  Harksheider Str. 102A                                                  */
/*  22399 Hamburg                                                          */
/*                                                                         */
/*  Tel. +49 (0)40 60 87 305 0                                             */
/*  Fax  +49 (0)40 60 87 305 20                                            */
/*                                                                         */
/*  http://www.struck.de                                                   */
/*                                                                         */
/*  © 2005                                                                 */
/*                                                                         */
/***************************************************************************/

//
//--------------------------------------------------------------------------- 
// Include files                                                              
//--------------------------------------------------------------------------- 

#include <windows.h>
#include <analysis.h>
#include <formatio.h>
#include <cvirte.h>     
#include <userint.h>
#include <stdio.h> 
#include <math.h> 
#include <utility.h> 
#include <ansi_c.h>
#include <stdio.h>

#include "sis3320_NeutronGamma_uir.h"
#include "sis3320_NeutronGamma_global.h" 	// Globale Defines fuers Programm


//--------------------------------------------------------------------------- 
// Local DEFINES (to be put into Include File)                                                              
//--------------------------------------------------------------------------- 


/*******************************************************************************/
/*                                                                             */
/*                                                                             */
/*      Energy Spectrum                                                          */
/*                                                                             */
/*                                                                             */
/*******************************************************************************/


int clear_spectrum_histogram(unsigned int module_index, unsigned int channel_index)
{
	unsigned int i ;
	if (module_index >= MAX_NO_OF_MODULES) { return -1 ;}
	if (channel_index >= NO_OF_ADC_CHANNELS) { return -1 ;}
   	
   	for (i=0; i<MAX_NOF_ENERGY_SPECTRUM; i++) {
		gl_uint_EnergySpectrumArray[module_index][channel_index][i] = 0 ; 	    
		gl_uint_EnergySpectrum2Array[module_index][channel_index][i] = 0 ; 	    
		gl_uint_EnergySpectrum3Array[module_index][channel_index][i] = 0 ; 	    
		//gl_uint_EnergySpectrumArray[module_index][channel_index][i] = (module_index * 1000) + (channel_index * 100) + i; 	    
	}
	return 0;
}

//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 

int clear_all_spectrum_histograms(void)
{
 	int  module_index, channel_index   ;
   	
	for (module_index=0;module_index<8;module_index++) {
		for (channel_index=0;channel_index<8;channel_index++) { // 8 channel
				clear_spectrum_histogram(module_index, channel_index)  ;
		}
	}
	return 0;
}

