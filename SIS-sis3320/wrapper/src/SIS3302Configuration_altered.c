#include <SIS3150.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

//#include "sis3320_NeutronGamma.h"

/*---------------------------------------------------------------------------
Read configuration parameter from file
---------------------------------------------------------------------------*/
int ReadConfiguration (char *path_file)
{
int imod,iadc ;
int i, temp, status;
char tempFile[MAX_FILENAME_LEN];
int tempErr, dummy, okSema;
int comp_err ;
FILE *used_file ;

char temp_char[MAX_FILENAME_LEN]  ;

unsigned int xaddress ;

    used_file=fopen(path_file, "r");
    if (used_file==NULL)  return FILE_ACCESS_NOT_OK;
    fgets (temp_char, MAX_FILENAME_LEN, used_file);  /* get header */
    fgets (temp_char, MAX_FILENAME_LEN, used_file);  /* get get data and time */

// get   PC Readout Mode
    fscanf(used_file,"%s\n",temp_char);	      // get KEY-STRING
    comp_err = strcmp (temp_char, STRING_RUN_READOUT_MODE); // check KEY-STRING
	if(comp_err != 0)  {
       fclose(used_file);
	   return FILE_ACCESS_NOT_OK;
	}
	fscanf(used_file,"%8x \n", &gl_uint_RunReadoutMode);


 // get Clock Module Parameter
    fscanf(used_file,"%s\n",temp_char);	      // get KEY-STRING
    comp_err = strcmp (temp_char, STRING_CLOCK_MODULE); // check KEY-STRING
	if(comp_err != 0)  {
       fclose(used_file);
	   return FILE_ACCESS_NOT_OK;
	}
	fscanf(used_file,"%8x %8x \n",&gl_uint_SIS3820EnableConf, &gl_uint_SIS3820AddrConf);   // read  Module Enable Flag / Address


// get Clock Modes
    fscanf(used_file,"%s\n",temp_char);	      // get KEY-STRING
    comp_err = strcmp (temp_char, STRING_CLOCK_MODE); // check KEY-STRING
	if(comp_err != 0)  {
       fclose(used_file);
	   return FILE_ACCESS_NOT_OK;
	}
	fscanf(used_file,"%8x \n",&gl_uint_SIS3820ClockModeConf);   // read  Clock Mode
	fscanf(used_file,"%8x \n",&gl_uint_SIS3820ClockCtrl4FlagConf);   //
	fscanf(used_file,"%8x \n",&gl_uint_SIS3820ClockCtrl3FlagConf);   //
	fscanf(used_file,"%8x \n",&gl_uint_SIS3820ClockCtrl2FlagConf);   //
	fscanf(used_file,"%8x \n",&gl_uint_SIS3820ClockTriggerMaskConf);   //

	fscanf(used_file,"%8x \n",&gl_uint_SIS3320ClockModeConf);   // read  Clock Mode



// get STRING_SIS3320_MODES
    fscanf(used_file,"%s\n",temp_char);	      // get KEY-STRING
    comp_err = strcmp (temp_char, STRING_SIS3320_MODES); // check KEY-STRING
	if(comp_err != 0)  {
       fclose(used_file);
	   return FILE_ACCESS_NOT_OK;
	}
	fscanf(used_file,"%8x %8x %8x %8x \n",&gl_uint_SIS3320_Trigger_Mode_Source_ModeConf, &gl_uint_SIS3320_DUMMY_ModeConf,
	                                      &gl_uint_SIS3320External_Lemo_Trigger_FlagConf, &gl_uint_SIS3320External_Lemo_TimestampClr_FlagConf);   // read

 // get Modules
    fscanf(used_file,"%s\n",temp_char);	      // get KEY-STRING
    comp_err = strcmp (temp_char, STRING_ADC_MODULES); // check KEY-STRING
	if(comp_err != 0)  {
       fclose(used_file);
	   return FILE_ACCESS_NOT_OK;
	}
    for (i=0;i<MAX_NO_OF_MODULES;i++) {
      fscanf(used_file,"%8x %8x \n",&gl_uint_ModEnableConf[i], &gl_uint_ModAddrConf[i]);   // read  Modules
	 }

// get SIS3150USB TS Readout Loader File
    fscanf(used_file,"%s\n",temp_char);	      // get KEY-STRING
    comp_err = strcmp (temp_char, STRING_SIS3150USB_TS_LOADER_FILE); // check KEY-STRING
	if(comp_err != 0)  {
       fclose(used_file);
	   return FILE_ACCESS_NOT_OK;
	}

    fscanf(used_file,"%s\n",gl_char_FileNameLoaderSIS3150USB_TS);	      // get


// get Sampling Parameters
    fscanf(used_file,"%s\n",temp_char);	      // get KEY-STRING
    comp_err = strcmp (temp_char, STRING_SAMPLING_PARAMETER); // check KEY-STRING
	if(comp_err != 0)  {
       fclose(used_file);
	   return FILE_ACCESS_NOT_OK;
	}

	fscanf(used_file,"%8x %8x \n",&gl_uint_MainGateLength, &gl_uint_MainGatePreTriggerDelay);   //

	fscanf(used_file,"%8x %8x \n",&gl_uint_Gate1_Length, &gl_uint_Gate1_StartIndex);   //
	fscanf(used_file,"%8x %8x \n",&gl_uint_Gate2_Length, &gl_uint_Gate2_StartIndex);   //
	fscanf(used_file,"%8x %8x \n",&gl_uint_Gate3_Length, &gl_uint_Gate3_StartIndex);   //
	fscanf(used_file,"%8x %8x \n",&gl_uint_Gate4_Length, &gl_uint_Gate4_StartIndex);   //
	fscanf(used_file,"%8x %8x \n",&gl_uint_Gate5_Length, &gl_uint_Gate5_StartIndex);   //
	fscanf(used_file,"%8x %8x \n",&gl_uint_Gate6_Length, &gl_uint_Gate6_StartIndex);   //
	fscanf(used_file,"%8x %8x \n",&gl_uint_Gate7_Length, &gl_uint_Gate7_StartIndex);   //
	fscanf(used_file,"%8x %8x \n",&gl_uint_Gate8_Length, &gl_uint_Gate8_StartIndex);   //

	fscanf(used_file,"%8x %8x \n",&gl_uint_RawSample_Length, &gl_uint_RawSample_StartIndex);   //
	fscanf(used_file,"%8x %8x \n",&gl_uint_RawDataSampleMode, &gl_uint_RawDataTestMode);   //



// get DAC Offset values
    fscanf(used_file,"%s\n",temp_char);	      // get KEY-STRING
    comp_err = strcmp (temp_char, STRING_DAC_OFFSET_VALUES); // check KEY-STRING
	if(comp_err != 0)  {
       fclose(used_file);
	   return FILE_ACCESS_NOT_OK;
	}

    for (imod=0;imod<MAX_NO_OF_MODULES;imod++) {
		fscanf(used_file,"%8x %8x %8x %8x %8x %8x %8x %8x \n",	&gl_uint_DacOffset_Conf[imod][INDEX_ADC_CHANNEL1],
                                                       			&gl_uint_DacOffset_Conf[imod][INDEX_ADC_CHANNEL2],
                                                       			&gl_uint_DacOffset_Conf[imod][INDEX_ADC_CHANNEL3],
                                                       			&gl_uint_DacOffset_Conf[imod][INDEX_ADC_CHANNEL4],
                                                       			&gl_uint_DacOffset_Conf[imod][INDEX_ADC_CHANNEL5],
                                                       			&gl_uint_DacOffset_Conf[imod][INDEX_ADC_CHANNEL6],
                                                       			&gl_uint_DacOffset_Conf[imod][INDEX_ADC_CHANNEL7],
                                                       			&gl_uint_DacOffset_Conf[imod][INDEX_ADC_CHANNEL8] );
	 }

// get FIR Trigger values
    fscanf(used_file,"%s\n",temp_char);	      // get KEY-STRING
    comp_err = strcmp (temp_char, STRING_FIR_TRIGGER_VALUES); // check KEY-STRING
	if(comp_err != 0)  {
       fclose(used_file);
	   return FILE_ACCESS_NOT_OK;
	}

    for (imod=0;imod<MAX_NO_OF_MODULES;imod++) {
    	for (iadc=0;iadc<NO_OF_ADC_CHANNELS;iadc++) {
			fscanf(used_file,"%8x %8x %8x %8x %8x \n", &gl_uint_FirTriggerP_Conf[imod][iadc],
                                                       &gl_uint_FirTriggerG_Conf[imod][iadc],
                                                       &gl_uint_FirTriggerThreshold_GtLtFlag_Conf[imod][iadc],
                                                       &gl_int_FirTriggerThresholdValue_Conf[imod][iadc],
                                                       &gl_uint_FirTriggerPulseLength_Conf[imod][iadc] );
	 	}
	 }

// get ADC_SIGNAL_INVERT_FLAGS
    fscanf(used_file,"%s\n",temp_char);	      // get KEY-STRING
    comp_err = strcmp (temp_char, STRING_ADC_SIGNAL_INVERT_FLAGS); // check KEY-STRING
	if(comp_err != 0)  {
       fclose(used_file);
	   return FILE_ACCESS_NOT_OK;
	}

    for (imod=0;imod<MAX_NO_OF_MODULES;imod++) {
		fscanf(used_file,"%8x %8x %8x %8x %8x %8x %8x %8x \n",	&gl_uint_ADC_SignalInvertConf[imod][INDEX_ADC_CHANNEL1],
                                                       			&gl_uint_ADC_SignalInvertConf[imod][INDEX_ADC_CHANNEL2],
                                                       			&gl_uint_ADC_SignalInvertConf[imod][INDEX_ADC_CHANNEL3],
                                                       			&gl_uint_ADC_SignalInvertConf[imod][INDEX_ADC_CHANNEL4],
                                                       			&gl_uint_ADC_SignalInvertConf[imod][INDEX_ADC_CHANNEL5],
                                                       			&gl_uint_ADC_SignalInvertConf[imod][INDEX_ADC_CHANNEL6],
                                                       			&gl_uint_ADC_SignalInvertConf[imod][INDEX_ADC_CHANNEL7],
                                                       			&gl_uint_ADC_SignalInvertConf[imod][INDEX_ADC_CHANNEL8] );
	 }


// get ADC_GAIN_FACTOR_FLAGS
    fscanf(used_file,"%s\n",temp_char);	      // get KEY-STRING
    comp_err = strcmp (temp_char, STRING_ADC_GAIN_FACTOR_FLAGS); // check KEY-STRING
	if(comp_err != 0)  {
       fclose(used_file);
	   return FILE_ACCESS_NOT_OK;
	}

    for (imod=0;imod<MAX_NO_OF_MODULES;imod++) {
		fscanf(used_file,"%8x %8x %8x %8x %8x %8x %8x %8x \n",	&gl_uint_ADC_Gain_FactorConf[imod][INDEX_ADC_CHANNEL1],
                                                       			&gl_uint_ADC_Gain_FactorConf[imod][INDEX_ADC_CHANNEL2],
                                                       			&gl_uint_ADC_Gain_FactorConf[imod][INDEX_ADC_CHANNEL3],
                                                       			&gl_uint_ADC_Gain_FactorConf[imod][INDEX_ADC_CHANNEL4],
                                                       			&gl_uint_ADC_Gain_FactorConf[imod][INDEX_ADC_CHANNEL5],
                                                       			&gl_uint_ADC_Gain_FactorConf[imod][INDEX_ADC_CHANNEL6],
                                                       			&gl_uint_ADC_Gain_FactorConf[imod][INDEX_ADC_CHANNEL7],
                                                       			&gl_uint_ADC_Gain_FactorConf[imod][INDEX_ADC_CHANNEL8] );
	 }

    fclose(used_file);

  return FILE_ACCESS_OK;
}

/* --------------------------------------------------------------------------
   SIS3820 Configuration
-------------------------------------------------------------------------- */
int Configuration_SIS3820Clock (void)
{
	unsigned int i, error, temp;
	unsigned int return_code;
	unsigned int data, addr;



	//if(gl_uint_SIS3820EnableConf != 0) { // wird Configuration

	// Key reset
	addr = gl_uint_SIS3820AddrConf + SIS3820CLOCK_KEY_RESET   ;
	if ((error = sub_vme_A32D32_write(addr,0x0 )) != 0) {
		sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_write");
 		return -1;
	}


//set Clock
	switch (gl_uint_SIS3820ClockModeConf)	{
			  case  0: // 100 MHz
				data = SIS3820CLOCK_CLOCK_SOURCE_100MHZ + SIS3820CLOCK_CLOCK_DIVIDE_1 ;	   //
 				break;
			  case  1: // 80 MHz
				data = SIS3820CLOCK_CLOCK_SOURCE_80MHZ  + SIS3820CLOCK_CLOCK_DIVIDE_1;	   //
 				break;
			  case  2: // 50 MHz
				data = SIS3820CLOCK_CLOCK_SOURCE_100MHZ + SIS3820CLOCK_CLOCK_DIVIDE_2;	   //
 				break;
			  case  3: // 40 MHz
				data = SIS3820CLOCK_CLOCK_SOURCE_80MHZ + SIS3820CLOCK_CLOCK_DIVIDE_2 ;	   //
 				break;
			  case  4: // 25 MHz
				data = SIS3820CLOCK_CLOCK_SOURCE_100MHZ + SIS3820CLOCK_CLOCK_DIVIDE_4 ;	   //
 				break;
			  case  5: // 20 MHz
				data = SIS3820CLOCK_CLOCK_SOURCE_80MHZ + SIS3820CLOCK_CLOCK_DIVIDE_4;	   //
 				break;
			  case  6: // extern LEMO  CTRL 1
				data = SIS3820CLOCK_CLOCK_SOURCE_EXT_CTRL;	   //
 				break;
			} // end switch (uintClockMode)

	//data = data+0x5c0 ; 	   // Timestamp clear via Key
	data = data+0x580 ; 	   // use as triggers

	addr = gl_uint_SIS3820AddrConf + SIS3820CLOCK_CLOCK_SOURCE   ;
	if ((error = sub_vme_A32D32_write(addr,data )) != 0) {
		sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_write");
 		return -1;
	}


	data = gl_uint_SIS3820ClockTriggerMaskConf ;
	addr = gl_uint_SIS3820AddrConf + SIS3820CLOCK_TRIGGERMASK   ;
	if ((error = sub_vme_A32D32_write(addr,data )) != 0) {
		sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_write");
 		return -1;
	}




// General Enable
	data = SIS3820CLOCK_GENERAL_ENABLE ;
	addr = gl_uint_SIS3820AddrConf + SIS3820CLOCK_CONTROL_STATUS   ;
	if ((error = sub_vme_A32D32_write(addr,data )) != 0) {
		sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_write");
 		return -1;
	}





// Enable  P2 and Frontpanel Outputs
	data = 0 ;

	if (gl_uint_SIS3820ClockCtrl4FlagConf == 1) {
		data = data + SIS3820CLOCK_EXT_CLR_TIMESTAMP_ENABLE ;
	}
	else {
		data = data + SIS3820CLOCK_EXT_CLR_TIMESTAMP_DISABLE ;
	}

	if (gl_uint_SIS3820ClockCtrl3FlagConf == 1) {
		data = data + SIS3820CLOCK_EXT_VETO_IN_ENABLE ;
	}
	else {
		data = data + SIS3820CLOCK_EXT_VETO_IN_DISABLE ;
	}

	if (gl_uint_SIS3820ClockCtrl2FlagConf == 1) {
		data = data + SIS3820CLOCK_EXT_TRIGGER_IN_ENABLE ;
	}
	else {
		data = data + SIS3820CLOCK_EXT_TRIGGER_IN_DISABLE ;
	}
		data = data + 0x2 ; // 16 x Clock / 16 x Timestamp clear

	addr = gl_uint_SIS3820AddrConf + SIS3820CLOCK_CONTROL_STATUS   ;
	if ((error = sub_vme_A32D32_write(addr,data )) != 0) {
		sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_write");
 		return -1;
	}


// Enable  P2 and Frontpanel Outputs
	data = SIS3820CLOCK_FP_CLOCK_OUT_ENABLE + SIS3820CLOCK_P2_OUT_ENABLE ;
	addr = gl_uint_SIS3820AddrConf + SIS3820CLOCK_CONTROL_STATUS   ;
	if ((error = sub_vme_A32D32_write(addr,data )) != 0) {
		sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_write");
 		return -1;
	}


 	return 0x0 ;


} // end function  ()



//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
int SystemConfiguration (void)
{
unsigned int i, iadc;
int temp, status, select;
int tempErr, dummy, okSema;
int run_index, conf_index, error ;
unsigned int addr, data, common_data ;
    double xmin;
    double xmax;
    double ymin;
    double ymax;


// configure SIS3820 System Controller
	if (gl_uint_SIS3820EnableConf == 1)  {
		Configuration_SIS3820Clock () ;
	}


// 1. reset all modules and define
	run_index = 0 ;
	for (i=0;i<MAX_NO_OF_MODULES;i++) {
		if  (gl_uint_ModEnableConf[i] != 0) {  // enabled
			addr = gl_uint_ModAddrConf[i] + SIS3320_KEY_RESET  ;
			if ((error = sub_vme_A32D32_write(addr,0x0 )) != 0) {
				sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_write")   ;
				gl_uint_system_status = SYSTEM_STATUS_MODULES_NOT_READY ;
				return -1 ;
			}
 			gl_uint_ModConfIndexRun[run_index] = i ;
			gl_uint_ModAddrRun[run_index] = gl_uint_ModAddrConf[i] ;
			run_index++;
		} // if enabled
	} /* for loop */

   gl_uint_NoOfModulesRun =  run_index ;


// configure all defined SIS3320 modules

	if (gl_uint_NoOfModulesRun != 0) {
		for (i=0;i<gl_uint_NoOfModulesRun;i++) {
			Configuration_SIS3320ADC(gl_uint_ModAddrRun[i], gl_uint_ModConfIndexRun[i]) ;
		}
	}

  return 0;
}


/* --------------------------------------------------------------------------
   SIS3320 Fast Trigger Out Setup
   module_addr
-------------------------------------------------------------------------- */
int sub_sis3320_fastTriggerOut_setup(unsigned int module_addr, unsigned int module_conf_index)
{
 	unsigned int error;
// 	unsigned int i, error, temp;
//	unsigned int return_code;
	unsigned int data, addr, base_addr;
	unsigned int g_value, p_value, puls_length_value;
	int threshold_value ;
	unsigned int threshold_flag;



	//Ch 1
		// Trigger G and P
		g_value           = gl_uint_FirTriggerG_Conf[module_conf_index] [INDEX_ADC_CHANNEL1] ;
		p_value           = gl_uint_FirTriggerP_Conf[module_conf_index] [INDEX_ADC_CHANNEL1] ;
		puls_length_value = gl_uint_FirTriggerPulseLength_Conf[module_conf_index] [INDEX_ADC_CHANNEL1] ;
		data = ((puls_length_value & 0xff) << 16) + ((g_value & 0xff) << 8) + (p_value & 0xff)   ; //
		addr = module_addr + SIS3320_TRIGGER_SETUP_ADC1 ;
		if ((error = sub_vme_A32D32_write(addr,data )) != 0) {
			sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_write");
			gl_uint_system_status = SYSTEM_STATUS_MODULES_NOT_READY ;
 			return -1;
		}

	//Ch 2
		// Trigger G and P
		g_value           = gl_uint_FirTriggerG_Conf[module_conf_index] [INDEX_ADC_CHANNEL2] ;
		p_value           = gl_uint_FirTriggerP_Conf[module_conf_index] [INDEX_ADC_CHANNEL2] ;
		puls_length_value = gl_uint_FirTriggerPulseLength_Conf[module_conf_index] [INDEX_ADC_CHANNEL2] ;
		data = ((puls_length_value & 0xff) << 16) + ((g_value & 0xff) << 8) + (p_value & 0xff)   ; //
		addr = module_addr + SIS3320_TRIGGER_SETUP_ADC2 ;
		if ((error = sub_vme_A32D32_write(addr,data )) != 0) {
			sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_write");
			gl_uint_system_status = SYSTEM_STATUS_MODULES_NOT_READY ;
 			return -1;
		}

	//Ch 3
		// Trigger G and P
		g_value           = gl_uint_FirTriggerG_Conf[module_conf_index] [INDEX_ADC_CHANNEL3] ;
		p_value           = gl_uint_FirTriggerP_Conf[module_conf_index] [INDEX_ADC_CHANNEL3] ;
		puls_length_value = gl_uint_FirTriggerPulseLength_Conf[module_conf_index] [INDEX_ADC_CHANNEL3] ;
		data = ((puls_length_value & 0xff) << 16) + ((g_value & 0xff) << 8) + (p_value & 0xff)   ; //
		addr = module_addr + SIS3320_TRIGGER_SETUP_ADC3 ;
		if ((error = sub_vme_A32D32_write(addr,data )) != 0) {
			sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_write");
			gl_uint_system_status = SYSTEM_STATUS_MODULES_NOT_READY ;
 			return -1;
		}

	//Ch 4
		// Trigger G and P
		g_value           = gl_uint_FirTriggerG_Conf[module_conf_index] [INDEX_ADC_CHANNEL4] ;
		p_value           = gl_uint_FirTriggerP_Conf[module_conf_index] [INDEX_ADC_CHANNEL4] ;
		puls_length_value = gl_uint_FirTriggerPulseLength_Conf[module_conf_index] [INDEX_ADC_CHANNEL4] ;
		data = ((puls_length_value & 0xff) << 16) + ((g_value & 0xff) << 8) + (p_value & 0xff)   ; //
		addr = module_addr + SIS3320_TRIGGER_SETUP_ADC4 ;
		if ((error = sub_vme_A32D32_write(addr,data )) != 0) {
			sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_write");
			gl_uint_system_status = SYSTEM_STATUS_MODULES_NOT_READY ;
 			return -1;
		}

	//Ch 5
		// Trigger G and P
		g_value           = gl_uint_FirTriggerG_Conf[module_conf_index] [INDEX_ADC_CHANNEL5] ;
		p_value           = gl_uint_FirTriggerP_Conf[module_conf_index] [INDEX_ADC_CHANNEL5] ;
		puls_length_value = gl_uint_FirTriggerPulseLength_Conf[module_conf_index] [INDEX_ADC_CHANNEL5] ;
		data = ((puls_length_value & 0xff) << 16) + ((g_value & 0xff) << 8) + (p_value & 0xff)   ; //
		addr = module_addr + SIS3320_TRIGGER_SETUP_ADC5 ;
		if ((error = sub_vme_A32D32_write(addr,data )) != 0) {
			sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_write");
			gl_uint_system_status = SYSTEM_STATUS_MODULES_NOT_READY ;
 			return -1;
		}

	//Ch 6
		// Trigger G and P
		g_value           = gl_uint_FirTriggerG_Conf[module_conf_index] [INDEX_ADC_CHANNEL6] ;
		p_value           = gl_uint_FirTriggerP_Conf[module_conf_index] [INDEX_ADC_CHANNEL6] ;
		puls_length_value = gl_uint_FirTriggerPulseLength_Conf[module_conf_index] [INDEX_ADC_CHANNEL6] ;
		data = ((puls_length_value & 0xff) << 16) + ((g_value & 0xff) << 8) + (p_value & 0xff)   ; //
		addr = module_addr + SIS3320_TRIGGER_SETUP_ADC6 ;
		if ((error = sub_vme_A32D32_write(addr,data )) != 0) {
			sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_write");
			gl_uint_system_status = SYSTEM_STATUS_MODULES_NOT_READY ;
 			return -1;
		}

	//Ch 7
		// Trigger G and P
		g_value           = gl_uint_FirTriggerG_Conf[module_conf_index] [INDEX_ADC_CHANNEL7] ;
		p_value           = gl_uint_FirTriggerP_Conf[module_conf_index] [INDEX_ADC_CHANNEL7] ;
		puls_length_value = gl_uint_FirTriggerPulseLength_Conf[module_conf_index] [INDEX_ADC_CHANNEL7] ;
		data = ((puls_length_value & 0xff) << 16) + ((g_value & 0xff) << 8) + (p_value & 0xff)   ; //
		addr = module_addr + SIS3320_TRIGGER_SETUP_ADC7 ;
		if ((error = sub_vme_A32D32_write(addr,data )) != 0) {
			sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_write");
			gl_uint_system_status = SYSTEM_STATUS_MODULES_NOT_READY ;
 			return -1;
		}

	//Ch 8
		// Trigger G and P
		g_value           = gl_uint_FirTriggerG_Conf[module_conf_index] [INDEX_ADC_CHANNEL8] ;
		p_value           = gl_uint_FirTriggerP_Conf[module_conf_index] [INDEX_ADC_CHANNEL8] ;
		puls_length_value = gl_uint_FirTriggerPulseLength_Conf[module_conf_index] [INDEX_ADC_CHANNEL8] ;
		data = ((puls_length_value & 0xff) << 16) + ((g_value & 0xff) << 8) + (p_value & 0xff)   ; //
		addr = module_addr + SIS3320_TRIGGER_SETUP_ADC8 ;
		if ((error = sub_vme_A32D32_write(addr,data )) != 0) {
			sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_write");
			gl_uint_system_status = SYSTEM_STATUS_MODULES_NOT_READY ;
 			return -1;
		}





	// Trigger Threshold
	// Ch 1
		threshold_value =  0x10000 + gl_int_FirTriggerThresholdValue_Conf[module_conf_index] [INDEX_ADC_CHANNEL1] ;
		data = (unsigned int) threshold_value ;
		threshold_flag  =  gl_uint_FirTriggerThreshold_GtLtFlag_Conf[module_conf_index] [INDEX_ADC_CHANNEL1] ;
		switch (threshold_flag)
		{
		  case  FIR_TRIGGER_THRESHOLD_CONF_GT_OUT_ENABLE: //
				data = data | 0x2000000 ;   // Bit 25
			break;
		  case  FIR_TRIGGER_THRESHOLD_CONF_GT_OUT_DISABLE: //
				data = data | 0x6000000 ; // Bit 26 and bit 25
			break;
		  case  FIR_TRIGGER_THRESHOLD_CONF_GT_ZERO_OUT_ENABLE: //
				data = data | 0x2000000 | 0x1000000 ;   // Bit 25 , bit 24
			break;
		  case  FIR_TRIGGER_THRESHOLD_CONF_GT_ZERO_OUT_DISABLE: //
				data = data | 0x6000000 | 0x1000000 ; // Bit 26 and bit 25 , bit 24
			break;
		} // end switch (threshold_flag)


		addr = module_addr + SIS3320_TRIGGER_THRESHOLD_ADC1 ;
		if ((error = sub_vme_A32D32_write(addr,data )) != 0) {
			sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_write")   ;
			gl_uint_system_status = SYSTEM_STATUS_MODULES_NOT_READY ;
			return -1 ;
		}

	// Trigger Threshold
	// Ch 2
		threshold_value =  0x10000 + gl_int_FirTriggerThresholdValue_Conf[module_conf_index] [INDEX_ADC_CHANNEL2] ;
		data = (unsigned int) threshold_value ;
		threshold_flag  =  gl_uint_FirTriggerThreshold_GtLtFlag_Conf[module_conf_index] [INDEX_ADC_CHANNEL2] ;
		switch (threshold_flag)
		{
		  case  FIR_TRIGGER_THRESHOLD_CONF_GT_OUT_ENABLE: //
				data = data | 0x2000000 ;   // Bit 25
			break;
		  case  FIR_TRIGGER_THRESHOLD_CONF_GT_OUT_DISABLE: //
				data = data | 0x6000000 ; // Bit 26 and bit 25
			break;
		  case  FIR_TRIGGER_THRESHOLD_CONF_GT_ZERO_OUT_ENABLE: //
				data = data | 0x2000000 | 0x1000000 ;   // Bit 25 , bit 24
			break;
		  case  FIR_TRIGGER_THRESHOLD_CONF_GT_ZERO_OUT_DISABLE: //
				data = data | 0x6000000 | 0x1000000 ; // Bit 26 and bit 25 , bit 24
			break;
		} // end switch (threshold_flag)
		addr = module_addr + SIS3320_TRIGGER_THRESHOLD_ADC2 ;
		if ((error = sub_vme_A32D32_write(addr,data )) != 0) {
			sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_write")   ;
			gl_uint_system_status = SYSTEM_STATUS_MODULES_NOT_READY ;
			return -1 ;
		}

	// Trigger Threshold
	// Ch 3
		threshold_value =  0x10000 + gl_int_FirTriggerThresholdValue_Conf[module_conf_index] [INDEX_ADC_CHANNEL3] ;
		data = (unsigned int) threshold_value ;
		threshold_flag  =  gl_uint_FirTriggerThreshold_GtLtFlag_Conf[module_conf_index] [INDEX_ADC_CHANNEL3] ;
		switch (threshold_flag)
		{
		  case  FIR_TRIGGER_THRESHOLD_CONF_GT_OUT_ENABLE: //
				data = data | 0x2000000 ;   // Bit 25
			break;
		  case  FIR_TRIGGER_THRESHOLD_CONF_GT_OUT_DISABLE: //
				data = data | 0x6000000 ; // Bit 26 and bit 25
			break;
		  case  FIR_TRIGGER_THRESHOLD_CONF_GT_ZERO_OUT_ENABLE: //
				data = data | 0x2000000 | 0x1000000 ;   // Bit 25 , bit 24
			break;
		  case  FIR_TRIGGER_THRESHOLD_CONF_GT_ZERO_OUT_DISABLE: //
				data = data | 0x6000000 | 0x1000000 ; // Bit 26 and bit 25 , bit 24
			break;
		} // end switch (threshold_flag)
		addr = module_addr + SIS3320_TRIGGER_THRESHOLD_ADC3 ;
		if ((error = sub_vme_A32D32_write(addr,data )) != 0) {
			sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_write")   ;
			gl_uint_system_status = SYSTEM_STATUS_MODULES_NOT_READY ;
			return -1 ;
		}

	// Trigger Threshold
	// Ch 4
		threshold_value =  0x10000 + gl_int_FirTriggerThresholdValue_Conf[module_conf_index] [INDEX_ADC_CHANNEL4] ;
		data = (unsigned int) threshold_value ;
		threshold_flag  =  gl_uint_FirTriggerThreshold_GtLtFlag_Conf[module_conf_index] [INDEX_ADC_CHANNEL4] ;
		switch (threshold_flag)
		{
		  case  FIR_TRIGGER_THRESHOLD_CONF_GT_OUT_ENABLE: //
				data = data | 0x2000000 ;   // Bit 25
			break;
		  case  FIR_TRIGGER_THRESHOLD_CONF_GT_OUT_DISABLE: //
				data = data | 0x6000000 ; // Bit 26 and bit 25
			break;
		  case  FIR_TRIGGER_THRESHOLD_CONF_GT_ZERO_OUT_ENABLE: //
				data = data | 0x2000000 | 0x1000000 ;   // Bit 25 , bit 24
			break;
		  case  FIR_TRIGGER_THRESHOLD_CONF_GT_ZERO_OUT_DISABLE: //
				data = data | 0x6000000 | 0x1000000 ; // Bit 26 and bit 25 , bit 24
			break;
		} // end switch (threshold_flag)
		addr = module_addr + SIS3320_TRIGGER_THRESHOLD_ADC4 ;
		if ((error = sub_vme_A32D32_write(addr,data )) != 0) {
			sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_write")   ;
			gl_uint_system_status = SYSTEM_STATUS_MODULES_NOT_READY ;
			return -1 ;
		}

	// Trigger Threshold
	// Ch 5
		threshold_value =  0x10000 + gl_int_FirTriggerThresholdValue_Conf[module_conf_index] [INDEX_ADC_CHANNEL5] ;
		data = (unsigned int) threshold_value ;
		threshold_flag  =  gl_uint_FirTriggerThreshold_GtLtFlag_Conf[module_conf_index] [INDEX_ADC_CHANNEL5] ;
		switch (threshold_flag)
		{
		  case  FIR_TRIGGER_THRESHOLD_CONF_GT_OUT_ENABLE: //
				data = data | 0x2000000 ;   // Bit 25
			break;
		  case  FIR_TRIGGER_THRESHOLD_CONF_GT_OUT_DISABLE: //
				data = data | 0x6000000 ; // Bit 26 and bit 25
			break;
		  case  FIR_TRIGGER_THRESHOLD_CONF_GT_ZERO_OUT_ENABLE: //
				data = data | 0x2000000 | 0x1000000 ;   // Bit 25 , bit 24
			break;
		  case  FIR_TRIGGER_THRESHOLD_CONF_GT_ZERO_OUT_DISABLE: //
				data = data | 0x6000000 | 0x1000000 ; // Bit 26 and bit 25 , bit 24
			break;
		} // end switch (threshold_flag)
		addr = module_addr + SIS3320_TRIGGER_THRESHOLD_ADC5 ;
		if ((error = sub_vme_A32D32_write(addr,data )) != 0) {
			sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_write")   ;
			gl_uint_system_status = SYSTEM_STATUS_MODULES_NOT_READY ;
			return -1 ;
		}

	// Trigger Threshold
	// Ch 6
		threshold_value =  0x10000 + gl_int_FirTriggerThresholdValue_Conf[module_conf_index] [INDEX_ADC_CHANNEL6] ;
		data = (unsigned int) threshold_value ;
		threshold_flag  =  gl_uint_FirTriggerThreshold_GtLtFlag_Conf[module_conf_index] [INDEX_ADC_CHANNEL6] ;
		switch (threshold_flag)
		{
		  case  FIR_TRIGGER_THRESHOLD_CONF_GT_OUT_ENABLE: //
				data = data | 0x2000000 ;   // Bit 25
			break;
		  case  FIR_TRIGGER_THRESHOLD_CONF_GT_OUT_DISABLE: //
				data = data | 0x6000000 ; // Bit 26 and bit 25
			break;
		  case  FIR_TRIGGER_THRESHOLD_CONF_GT_ZERO_OUT_ENABLE: //
				data = data | 0x2000000 | 0x1000000 ;   // Bit 25 , bit 24
			break;
		  case  FIR_TRIGGER_THRESHOLD_CONF_GT_ZERO_OUT_DISABLE: //
				data = data | 0x6000000 | 0x1000000 ; // Bit 26 and bit 25 , bit 24
			break;
		} // end switch (threshold_flag)
		addr = module_addr + SIS3320_TRIGGER_THRESHOLD_ADC6 ;
		if ((error = sub_vme_A32D32_write(addr,data )) != 0) {
			sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_write")   ;
			gl_uint_system_status = SYSTEM_STATUS_MODULES_NOT_READY ;
			return -1 ;
		}

	// Trigger Threshold
	// Ch 7
		threshold_value =  0x10000 + gl_int_FirTriggerThresholdValue_Conf[module_conf_index] [INDEX_ADC_CHANNEL7] ;
		data = (unsigned int) threshold_value ;
		threshold_flag  =  gl_uint_FirTriggerThreshold_GtLtFlag_Conf[module_conf_index] [INDEX_ADC_CHANNEL7] ;
		switch (threshold_flag)
		{
		  case  FIR_TRIGGER_THRESHOLD_CONF_GT_OUT_ENABLE: //
				data = data | 0x2000000 ;   // Bit 25
			break;
		  case  FIR_TRIGGER_THRESHOLD_CONF_GT_OUT_DISABLE: //
				data = data | 0x6000000 ; // Bit 26 and bit 25
			break;
		  case  FIR_TRIGGER_THRESHOLD_CONF_GT_ZERO_OUT_ENABLE: //
				data = data | 0x2000000 | 0x1000000 ;   // Bit 25 , bit 24
			break;
		  case  FIR_TRIGGER_THRESHOLD_CONF_GT_ZERO_OUT_DISABLE: //
				data = data | 0x6000000 | 0x1000000 ; // Bit 26 and bit 25 , bit 24
			break;
		} // end switch (threshold_flag)
		addr = module_addr + SIS3320_TRIGGER_THRESHOLD_ADC7 ;
		if ((error = sub_vme_A32D32_write(addr,data )) != 0) {
			sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_write")   ;
			gl_uint_system_status = SYSTEM_STATUS_MODULES_NOT_READY ;
			return -1 ;
		}

	// Trigger Threshold
	// Ch 8
		threshold_value =  0x10000 + gl_int_FirTriggerThresholdValue_Conf[module_conf_index] [INDEX_ADC_CHANNEL8] ;
		data = (unsigned int) threshold_value ;
		threshold_flag  =  gl_uint_FirTriggerThreshold_GtLtFlag_Conf[module_conf_index] [INDEX_ADC_CHANNEL8] ;
		switch (threshold_flag)
		{
		  case  FIR_TRIGGER_THRESHOLD_CONF_GT_OUT_ENABLE: //
				data = data | 0x2000000 ;   // Bit 25
			break;
		  case  FIR_TRIGGER_THRESHOLD_CONF_GT_OUT_DISABLE: //
				data = data | 0x6000000 ; // Bit 26 and bit 25
			break;
		  case  FIR_TRIGGER_THRESHOLD_CONF_GT_ZERO_OUT_ENABLE: //
				data = data | 0x2000000 | 0x1000000 ;   // Bit 25 , bit 24
			break;
		  case  FIR_TRIGGER_THRESHOLD_CONF_GT_ZERO_OUT_DISABLE: //
				data = data | 0x6000000 | 0x1000000 ; // Bit 26 and bit 25 , bit 24
			break;
		} // end switch (threshold_flag)
		addr = module_addr + SIS3320_TRIGGER_THRESHOLD_ADC8 ;
		if ((error = sub_vme_A32D32_write(addr,data )) != 0) {
			sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_write")   ;
			gl_uint_system_status = SYSTEM_STATUS_MODULES_NOT_READY ;
			return -1 ;
		}




	return 0x0 ;

} // end function  ()

//---------------------------------------------------------------------------
/* ----------------------------------------------------------------------------------------------------- */
int sub_sis3320_Configuration_DACs_setup(unsigned int module_addr, unsigned int module_conf_index)
{
	unsigned int i_adc, error, temp;
	unsigned int dac_offset[8];


	for (i_adc=0;i_adc<8;i_adc++) {
		dac_offset[i_adc]	= gl_uint_DacOffset_Conf[module_conf_index][i_adc] ;
	}

	if ((gl_uint_SIS3320_250_FlagConf[module_conf_index] == 0) && (gl_uint_SIS3302_FlagConf[module_conf_index] == 0)) {
		error=sis3320_write_dac_offset(module_addr, dac_offset)  ;
		if (error != 0) {
			sisVME_ErrorHandling (error, module_addr, "sis3320_write_dac_offset")   ;
			gl_uint_system_status = SYSTEM_STATUS_MODULES_NOT_READY ;
			return -1 ;
		}
	}
	else { // SIS3320-250
		if ((error = sis3320_250_write_dac_offset(module_addr ,dac_offset )) != 0) {
			sisVME_ErrorHandling (error, module_addr, "sis3320_250_write_dac_offset");
			return -1;
		}
	}

	return 0x0 ;

} // end function  ()



/* --------------------------------------------------------------------------
   SIS3320 DAC Offset
   module_addr			    vme module base address
   offset Value_array		DAC offset value (16 bit)
-------------------------------------------------------------------------- */

int sis3320_write_dac_offset(unsigned int module_addr, unsigned int *offset_value_array)
{
	unsigned int i, error, temp;
	unsigned int return_code;
	unsigned int data, addr, base_addr;
	unsigned int max_timeout, timeout_cnt;




 	for (i=0;i<8;i++) {

		data =  offset_value_array[7-i] ;
		addr = module_addr + SIS3320_DAC_DATA  ;
		if ((error = sub_vme_A32D32_write(addr,data )) != 0) {
			sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_write");
 			return -1;
		}


		data =  1 ; // write to DAC Register
		addr = module_addr + SIS3320_DAC_CONTROL_STATUS  ;
		if ((error = sub_vme_A32D32_write(addr,data )) != 0) {
			sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_write");
 			return -1;
		}

		max_timeout = 5000 ;
		timeout_cnt = 0 ;
		addr = module_addr + SIS3320_DAC_CONTROL_STATUS  ;
		do {
			if ((error = sub_vme_A32D32_read(addr, &data)) != 0) {
				sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_read");
				return -1;
			}
			timeout_cnt++;
		} while ( ((data & 0x8000) == 0x8000) && (timeout_cnt <  max_timeout) )    ;

		if (timeout_cnt >=  max_timeout) {
			return -2 ;
		}



		data =  2 ; // Load DACs
		addr = module_addr + SIS3320_DAC_CONTROL_STATUS  ;
		if ((error = sub_vme_A32D32_write(addr,data )) != 0) {
			sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_write");
 			return -1;
		}
		timeout_cnt = 0 ;
		addr = module_addr + SIS3320_DAC_CONTROL_STATUS  ;
		do {
			if ((error = sub_vme_A32D32_read(addr, &data)) != 0) {
				sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_read");
				return -1;
			}
			timeout_cnt++;
		} while ( ((data & 0x8000) == 0x8000) && (timeout_cnt <  max_timeout) )    ;

		if (timeout_cnt >=  max_timeout) {
			return -3 ;
		}


	}

	return 0x0 ;

} // end function  ()




//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------

int sis3320_250_write_dac_offset(unsigned int module_addr, unsigned int *offset_value_array)
{
	unsigned int i, error, temp;
	unsigned int return_code;
	unsigned int data, addr, base_addr;
	unsigned int max_timeout, timeout_cnt;


	for (i=0;i<8;i++) {

		data =  offset_value_array[i] ;
		addr = module_addr + SIS3320_DAC_DATA  ; //roe 14.12.09
		if ((error = sub_vme_A32D32_write(addr,data )) != 0) {
			sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_write");
 			return -1;
		}

		data =  1 + (i << 4); // write to DAC Register
		addr = module_addr + SIS3320_DAC_CONTROL_STATUS  ;  //roe 14.12.09
		if ((error = sub_vme_A32D32_write(addr,data )) != 0) {
			sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_write");
 			return -1;
		}

		max_timeout = 5000 ;
		timeout_cnt = 0 ;
		addr = module_addr + SIS3320_DAC_CONTROL_STATUS  ;  //roe 14.12.09
		do {
			if ((error = sub_vme_A32D32_read(addr,&data )) != 0) {
				sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_read");
				return -1;
			}
			timeout_cnt++;
		} while ( ((data & 0x8000) == 0x8000) && (timeout_cnt <  max_timeout) )    ;

		if (timeout_cnt >=  max_timeout) {
			return -2 ;
		}


		data =  2 + (i << 4); // Load DACs
		addr = module_addr + SIS3320_DAC_CONTROL_STATUS  ;   //roe 14.12.09
		if ((error = sub_vme_A32D32_write(addr,data )) != 0) {
			sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_write");
			return -1;
		}
		timeout_cnt = 0 ;
		addr = module_addr + SIS3320_DAC_CONTROL_STATUS  ;		//roe 14.12.09
		do {
			if ((error = sub_vme_A32D32_read(addr,&data )) != 0) {
				sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_read");
				return -1;
			}
			timeout_cnt++;
		} while ( ((data & 0x8000) == 0x8000) && (timeout_cnt <  max_timeout) )    ;

		if (timeout_cnt >=  max_timeout) {
			return -3 ;
		}

	}
	return 0x0 ;
} // end function  ()

/* --------------------------------------------------------------------------
   SIS3320 Configuration
-------------------------------------------------------------------------- */
int Reset_SIS3320ADC (unsigned int module_addr, unsigned int module_conf_index )
{
	unsigned int i, error, temp;
	unsigned int data, addr;
	unsigned int module_index;

	//Reset

		addr = module_addr + SIS3320_KEY_RESET ;
		if ((error = sub_vme_A32D32_write(addr,0x0 )) != 0) {
			sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_write")   ;
			gl_uint_system_status = SYSTEM_STATUS_MODULES_NOT_READY ;
			return -1 ;
		}
	return 0x0 ;


} // end function  ()

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
int Configuration_SIS3320ADC (unsigned int module_addr, unsigned int module_conf_index )
{
	unsigned int i, error, temp;
	unsigned int data, addr;
	unsigned int adc12_data, adc34_data, adc56_data, adc78_data;
	unsigned int module_index;


//Reset

	addr = module_addr + SIS3320_KEY_RESET ;
	if ((error = sub_vme_A32D32_write(addr,0x0 )) != 0) {
		sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_write")   ;
		gl_uint_system_status = SYSTEM_STATUS_MODULES_NOT_READY ;
		return -1 ;
	}


	// Broadcast setup
	gl_uint_SIS3320_BroadcastAddrConf =   ADC_MODULE_CONF_DEFAULT_BROADCAST_ADDRESS ;
	data = (gl_uint_SIS3320_BroadcastAddrConf & 0xff000000)  ;
	data = data + SIS3320_BROADCAST_ENABLE  ;

	if (module_conf_index == 0) {
		data = data + SIS3320_BROADCAST_MASTER_ENABLE  ;
	}

	addr = module_addr + SIS3320_CBLT_BROADCAST_SETUP ;
	if ((error = sub_vme_A32D32_write(addr,data )) != 0) {
		sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_write")   ;
		gl_uint_system_status = SYSTEM_STATUS_MODULES_NOT_READY ;
		return -1 ;
	}

// SIS3320_ACQUISTION_CONTROL
	//set Clock source
		data = SIS3320_ACQ_SET_CLOCK_TO_100MHZ ;	   //
		//set Clock source
		switch (gl_uint_SIS3320ClockModeConf)
		{
		  case  0: // intern 100 MHz
			data = SIS3320_ACQ_SET_CLOCK_TO_200MHZ ;	   //
			break;
		  case  1: // intern 50 MHz
			data = SIS3320_ACQ_SET_CLOCK_TO_100MHZ ;	   //
			break;
		  case  2: // intern 25 MHz
			data = SIS3320_ACQ_SET_CLOCK_TO_50MHZ ;	   //
 			break;
		  case  3: // intern 62.25 MHz
			data = SIS3320_ACQ_SET_CLOCK_TO_LEMO_X5_CLOCK_IN;	   //
 			break;
		  case  4: // extern LEMO
			data = SIS3320_ACQ_SET_CLOCK_TO_LEMO_DOUBLE_CLOCK_IN;	   //
 			break;
		  case  5: // extern P2
			data = SIS3320_ACQ_SET_CLOCK_TO_P2_CLOCK_IN;	   //
 			break;
		  case  6: // 2 x extern P2
			data = SIS3320_ACQ_SET_CLOCK_TO_LEMO_CLOCK_IN;	   //
 			break;
		  case  7: // Dived by 2 and Multi 2 extern P2
			data = SIS3320_ACQ_SET_CLOCK_TO_P2_CLOCK_IN;	   //
 			break;
		} // end switch (gl_uint_SIS9300ClockModeConf)


		if (gl_uint_SIS3320External_Lemo_Trigger_FlagConf == 1)  {
				data = data + SIS3320_ACQ_ENABLE_LEMO_TRIGGER ;	   //
		}

		if (gl_uint_SIS3320External_Lemo_TimestampClr_FlagConf == 1)  {
				data = data + SIS3320_ACQ_ENABLE_LEMO_TIMESTAMPCLR ;	   //
		}



		addr = module_addr + SIS3320_ACQUISTION_CONTROL ;
		if ((error = sub_vme_A32D32_write(addr,data )) != 0) {
			sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_write")   ;
			gl_uint_system_status = SYSTEM_STATUS_MODULES_NOT_READY ;
			return -1 ;
		}


		// SIS3320_GAIN_CONTROL
		// only supported on SIS3320


		if ((gl_uint_SIS3320_250_FlagConf[module_conf_index] == 0) && (gl_uint_SIS3302_FlagConf[module_conf_index] == 0)) {

			data = 0 ;
			if (gl_uint_ADC_Gain_FactorConf[module_conf_index][INDEX_ADC_CHANNEL1] != 0) {
				data = data + ADC1_GAIN_HALFSCALE_BIT ;	   //
			}
			if (gl_uint_ADC_Gain_FactorConf[module_conf_index][INDEX_ADC_CHANNEL2] != 0) {
				data = data + ADC2_GAIN_HALFSCALE_BIT ;	   //
			}
			if (gl_uint_ADC_Gain_FactorConf[module_conf_index][INDEX_ADC_CHANNEL3] != 0) {
				data = data + ADC3_GAIN_HALFSCALE_BIT ;	   //
			}
			if (gl_uint_ADC_Gain_FactorConf[module_conf_index][INDEX_ADC_CHANNEL4] != 0) {
				data = data + ADC4_GAIN_HALFSCALE_BIT ;	   //
			}
			if (gl_uint_ADC_Gain_FactorConf[module_conf_index][INDEX_ADC_CHANNEL5] != 0) {
				data = data + ADC5_GAIN_HALFSCALE_BIT ;	   //
			}
			if (gl_uint_ADC_Gain_FactorConf[module_conf_index][INDEX_ADC_CHANNEL6] != 0) {
				data = data + ADC6_GAIN_HALFSCALE_BIT ;	   //
			}
			if (gl_uint_ADC_Gain_FactorConf[module_conf_index][INDEX_ADC_CHANNEL7] != 0) {
				data = data + ADC7_GAIN_HALFSCALE_BIT ;	   //
			}
			if (gl_uint_ADC_Gain_FactorConf[module_conf_index][INDEX_ADC_CHANNEL8] != 0) {
				data = data + ADC8_GAIN_HALFSCALE_BIT ;	   //
			}
			addr = module_addr + SIS3320_ADC_GAIN_CONTROL ;
			if ((error = sub_vme_A32D32_write(addr,data )) != 0) {
				sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_write")   ;
				gl_uint_system_status = SYSTEM_STATUS_MODULES_NOT_READY ;
				return -1 ;
			}

		}


// Event Config (all adc-FPGAs)
		data = 0 ;	   //

// 	  	GetCtrlVal (Panels[SAMPLE_PARA_CONF],SAMPL_CONF_ACCU_DATA_FORMAT, &temp);
        temp = 1;
		if (temp != 0) {
			data = data + 0x202 ;	   //   8-Accumulator Mode
		}

		switch (gl_uint_SIS3320_Trigger_Mode_Source_ModeConf)
		{
	  		case  0: // asynch Trigger Mode
				data = data + EVENT_CONF_ADC1_INTERN_TRIGGER_ENABLE_BIT + EVENT_CONF_ADC2_INTERN_TRIGGER_ENABLE_BIT ;	   //
				break;
	  		case  1: // synch Trigger Mode / external Lemo IN3 Trigger
				data = data + EVENT_CONF_ADC1_EXTERN_TRIGGER_ENABLE_BIT + EVENT_CONF_ADC2_EXTERN_TRIGGER_ENABLE_BIT ;	   //
				break;
		} // end switch (gl_uint_SIS3150LemoOut1ModeConf)


		switch (gl_uint_RawDataSampleMode)	// 0: no raw data; 1: always; 2: first event of buffer; 3: first event of buffer or if Pileup; 4: if Pileup
		{
	  		case  0: // no raw data
				data = data  ;	   //
				break;
	  		case  1: // always
				data = data + EVENT_CONF_ADC1_SAVE_RAW_DATA_ALWAYS_ENABLE_BIT + EVENT_CONF_ADC2_SAVE_RAW_DATA_ALWAYS_ENABLE_BIT ;	   //
				break;
	  		case  2: // first event of buffer
				data = data + EVENT_CONF_ADC1_SAVE_RAW_DATA_FIRST_EVENT_ENABLE_BIT + EVENT_CONF_ADC2_SAVE_RAW_DATA_FIRST_EVENT_ENABLE_BIT ;	   //
				break;
	  		case  3: // first event of buffer or if Pileup
				data = data + EVENT_CONF_ADC1_SAVE_RAW_DATA_FIRST_EVENT_ENABLE_BIT + EVENT_CONF_ADC2_SAVE_RAW_DATA_FIRST_EVENT_ENABLE_BIT ;	   //
				data = data + EVENT_CONF_ADC1_SAVE_RAW_DATA_IF_PILEUP_ENABLE_BIT + EVENT_CONF_ADC2_SAVE_RAW_DATA_IF_PILEUP_ENABLE_BIT ;	   //
				break;
	  		case  4: // if Pileup
				data = data + EVENT_CONF_ADC1_SAVE_RAW_DATA_IF_PILEUP_ENABLE_BIT + EVENT_CONF_ADC2_SAVE_RAW_DATA_IF_PILEUP_ENABLE_BIT ;	   //
				break;
		} // end switch (gl_uint_SIS3150LemoOut1ModeConf)







		switch (gl_uint_RawDataTestMode)	// 0 no test data; 1: odd channels; 2: even channels; 3: both channels
		{
	  		case  0: // no test data
				data = data  ;	   //
				break;
	  		case  1: // 1: odd channels
				data = data + EVENT_CONF_ADC1_TEST_SAVE_FIR_DATA_ENABLE_BIT  ;	   //
				break;
	  		case  2: // 2: even channels
				data = data + EVENT_CONF_ADC2_TEST_SAVE_FIR_DATA_ENABLE_BIT  ;	   //
				break;
	  		case  3: // 3: both channels
				data = data + EVENT_CONF_ADC1_TEST_SAVE_FIR_DATA_ENABLE_BIT + EVENT_CONF_ADC2_TEST_SAVE_FIR_DATA_ENABLE_BIT ;	   //
				break;
		} // end switch (gl_uint_SIS3150LemoOut1ModeConf)



		// channel ID = Module Address 31:27
		data = data  + (module_addr & 0xf8000000) ;	   //

		adc12_data = data  ;	   //
		adc34_data = data ;	   //
		adc56_data = data ;	   //
		adc78_data = data ;	   //



		if (gl_uint_ADC_SignalInvertConf[module_conf_index][INDEX_ADC_CHANNEL1] != 0) {
			adc12_data = adc12_data + EVENT_CONF_ADC1_INPUT_INVERT_BIT ;	   //
		}
		if (gl_uint_ADC_SignalInvertConf[module_conf_index][INDEX_ADC_CHANNEL2] != 0) {
			adc12_data = adc12_data + EVENT_CONF_ADC2_INPUT_INVERT_BIT ;	   //
		}

		if (gl_uint_ADC_SignalInvertConf[module_conf_index][INDEX_ADC_CHANNEL3] != 0) {
			adc34_data = adc34_data + EVENT_CONF_ADC1_INPUT_INVERT_BIT ;	   //
		}
		if (gl_uint_ADC_SignalInvertConf[module_conf_index][INDEX_ADC_CHANNEL4] != 0) {
			adc34_data = adc34_data + EVENT_CONF_ADC2_INPUT_INVERT_BIT ;	   //
		}

		if (gl_uint_ADC_SignalInvertConf[module_conf_index][INDEX_ADC_CHANNEL5] != 0) {
			adc56_data = adc56_data + EVENT_CONF_ADC1_INPUT_INVERT_BIT ;	   //
		}
		if (gl_uint_ADC_SignalInvertConf[module_conf_index][INDEX_ADC_CHANNEL6] != 0) {
			adc56_data = adc56_data + EVENT_CONF_ADC2_INPUT_INVERT_BIT ;	   //
		}

		if (gl_uint_ADC_SignalInvertConf[module_conf_index][INDEX_ADC_CHANNEL7] != 0) {
			adc78_data = adc78_data + EVENT_CONF_ADC1_INPUT_INVERT_BIT ;	   //
		}
		if (gl_uint_ADC_SignalInvertConf[module_conf_index][INDEX_ADC_CHANNEL8] != 0) {
			adc78_data = adc78_data + EVENT_CONF_ADC2_INPUT_INVERT_BIT ;	   //
		}




		addr = module_addr + SIS3320_EVENT_CONFIG_ADC12 ;
		if ((error = sub_vme_A32D32_write(addr,adc12_data )) != 0) {
			sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_write")   ;
			gl_uint_system_status = SYSTEM_STATUS_MODULES_NOT_READY ;
			return -1 ;
		}
		addr = module_addr + SIS3320_EVENT_CONFIG_ADC34 ;
		if ((error = sub_vme_A32D32_write(addr,adc34_data )) != 0) {
			sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_write")   ;
			gl_uint_system_status = SYSTEM_STATUS_MODULES_NOT_READY ;
			return -1 ;
		}
		addr = module_addr + SIS3320_EVENT_CONFIG_ADC56 ;
		if ((error = sub_vme_A32D32_write(addr,adc56_data )) != 0) {
			sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_write")   ;
			gl_uint_system_status = SYSTEM_STATUS_MODULES_NOT_READY ;
			return -1 ;
		}
		addr = module_addr + SIS3320_EVENT_CONFIG_ADC78 ;
		if ((error = sub_vme_A32D32_write(addr,adc78_data )) != 0) {
			sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_write")   ;
			gl_uint_system_status = SYSTEM_STATUS_MODULES_NOT_READY ;
			return -1 ;
		}



	// SIS3320_PRETRIGGER_ACTIVEGATE_WINDOW_ALL_ADC
		data = ((gl_uint_MainGatePreTriggerDelay << 16) & 0x03ff0000) +  (gl_uint_MainGateLength & 0x3ff)  ;
		addr = module_addr + SIS3320_PRETRIGGER_ACTIVEGATE_WINDOW_ALL_ADC ;
		if ((error = sub_vme_A32D32_write(addr,data )) != 0) {
			sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_write")   ;
			gl_uint_system_status = SYSTEM_STATUS_MODULES_NOT_READY ;
			return -1 ;
		}



	// SIS3320_ACCUMULATOR_GATE1_CONFIG_ALL_ADC
		data = ((gl_uint_Gate1_Length << 16) & 0x01ff0000) +  (gl_uint_Gate1_StartIndex & 0x3ff)  ;
		addr = module_addr + SIS3320_ACCUMULATOR_GATE1_CONFIG_ALL_ADC ;
		if ((error = sub_vme_A32D32_write(addr,data )) != 0) {
			sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_write")   ;
			gl_uint_system_status = SYSTEM_STATUS_MODULES_NOT_READY ;
			return -1 ;
		}

	// SIS3320_ACCUMULATOR_GATE2_CONFIG_ALL_ADC
		data = ((gl_uint_Gate2_Length << 16) & 0x01ff0000) +  (gl_uint_Gate2_StartIndex & 0x3ff)  ;
		addr = module_addr + SIS3320_ACCUMULATOR_GATE2_CONFIG_ALL_ADC ;
		if ((error = sub_vme_A32D32_write(addr,data )) != 0) {
			sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_write")   ;
			gl_uint_system_status = SYSTEM_STATUS_MODULES_NOT_READY ;
			return -1 ;
		}

	// SIS3320_ACCUMULATOR_GATE3_CONFIG_ALL_ADC
		data = ((gl_uint_Gate3_Length << 16) & 0x01ff0000) +  (gl_uint_Gate3_StartIndex & 0x3ff)  ;
		addr = module_addr + SIS3320_ACCUMULATOR_GATE3_CONFIG_ALL_ADC ;
		if ((error = sub_vme_A32D32_write(addr,data )) != 0) {
			sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_write")   ;
			gl_uint_system_status = SYSTEM_STATUS_MODULES_NOT_READY ;
			return -1 ;
		}

	// SIS3320_ACCUMULATOR_GATE4_CONFIG_ALL_ADC
		data = ((gl_uint_Gate4_Length << 16) & 0x01ff0000) +  (gl_uint_Gate4_StartIndex & 0x3ff)  ;
		addr = module_addr + SIS3320_ACCUMULATOR_GATE4_CONFIG_ALL_ADC ;
		if ((error = sub_vme_A32D32_write(addr,data )) != 0) {
			sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_write")   ;
			gl_uint_system_status = SYSTEM_STATUS_MODULES_NOT_READY ;
			return -1 ;
		}

	// SIS3320_ACCUMULATOR_GATE5_CONFIG_ALL_ADC
		data = ((gl_uint_Gate5_Length << 16) & 0x01ff0000) +  (gl_uint_Gate5_StartIndex & 0x3ff)  ;
		addr = module_addr + SIS3320_ACCUMULATOR_GATE5_CONFIG_ALL_ADC ;
		if ((error = sub_vme_A32D32_write(addr,data )) != 0) {
			sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_write")   ;
			gl_uint_system_status = SYSTEM_STATUS_MODULES_NOT_READY ;
			return -1 ;
		}

	// SIS3320_ACCUMULATOR_GATE6_CONFIG_ALL_ADC
		data = ((gl_uint_Gate6_Length << 16) & 0x01ff0000) +  (gl_uint_Gate6_StartIndex & 0x3ff)  ;
		addr = module_addr + SIS3320_ACCUMULATOR_GATE6_CONFIG_ALL_ADC ;
		if ((error = sub_vme_A32D32_write(addr,data )) != 0) {
			sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_write")   ;
			gl_uint_system_status = SYSTEM_STATUS_MODULES_NOT_READY ;
			return -1 ;
		}

	// SIS3320_ACCUMULATOR_GATE7_CONFIG_ALL_ADC
		data = ((gl_uint_Gate7_Length << 16) & 0x01ff0000) +  (gl_uint_Gate7_StartIndex & 0x3ff)  ;
		addr = module_addr + SIS3320_ACCUMULATOR_GATE7_CONFIG_ALL_ADC ;
		if ((error = sub_vme_A32D32_write(addr,data )) != 0) {
			sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_write")   ;
			gl_uint_system_status = SYSTEM_STATUS_MODULES_NOT_READY ;
			return -1 ;
		}

	// SIS3320_ACCUMULATOR_GATE8_CONFIG_ALL_ADC
		data = ((gl_uint_Gate8_Length << 16) & 0x01ff0000) +  (gl_uint_Gate8_StartIndex & 0x3ff)  ;
		addr = module_addr + SIS3320_ACCUMULATOR_GATE8_CONFIG_ALL_ADC ;
		if ((error = sub_vme_A32D32_write(addr,data )) != 0) {
			sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_write")   ;
			gl_uint_system_status = SYSTEM_STATUS_MODULES_NOT_READY ;
			return -1 ;
		}




	// SIS3320_RAW_DATA_BUFFER_CONFIG_ALL_ADC
		data = ((gl_uint_RawSample_Length << 16) & 0x03ff0000) +  (gl_uint_RawSample_StartIndex & 0x3ff)  ;
		addr = module_addr + SIS3320_RAW_DATA_BUFFER_CONFIG_ALL_ADC ;
		if ((error = sub_vme_A32D32_write(addr,data )) != 0) {
			sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_write")   ;
			gl_uint_system_status = SYSTEM_STATUS_MODULES_NOT_READY ;
			return -1 ;
		}


		// address threshold flag
		data = 0x15c0 ;		// write 0x1c0 x 2 samples
		addr = module_addr + SIS3320_END_ADDRESS_THRESHOLD_ALL_ADC ;
		if ((error = sub_vme_A32D32_write(addr,data )) != 0) {
			sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_write")   ;
			gl_uint_system_status = SYSTEM_STATUS_MODULES_NOT_READY ;
			return -1 ;
		}

		// VME IRQ generation
		data = 0x800 + 0x600 ;		// IRQ 6 enable
		addr = module_addr + SIS3320_IRQ_CONFIG ;
		if ((error = sub_vme_A32D32_write(addr,data )) != 0) {
			sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_write")   ;
			gl_uint_system_status = SYSTEM_STATUS_MODULES_NOT_READY ;
			return -1 ;
		}

		data = 0x2 ;		// Enable IRQ Address Threshold Flag Level sensitive
		addr = module_addr + SIS3320_IRQ_CONTROL ;
		if ((error = sub_vme_A32D32_write(addr,data )) != 0) {
			sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_write")   ;
			gl_uint_system_status = SYSTEM_STATUS_MODULES_NOT_READY ;
			return -1 ;
		}


	// Fast FIR Trigger
		sub_sis3320_fastTriggerOut_setup(module_addr, module_conf_index) ;


	// DACs
		sub_sis3320_Configuration_DACs_setup(module_addr, module_conf_index)  ;



		// only SIS3320-250
		// SPI Interface
		if (gl_uint_SIS3320_250_FlagConf[module_conf_index] == 1) {
			for (i=0;i<8;i++) {
				error = sis3320_250_write_adc_spi(module_addr, i, 0x0f, 0x2 ) ; // set CML
				if (error  != 0) {
					sisVME_ErrorHandling (error, module_addr, "sis3320_250_write_adc_spi");
 					return -1;
				}
			}
		}

  #ifdef test_print
		for (i=0;i<0x10;i++) {
			sis3320_250_read_adc_spi(module_addr, 0, i, &error ) ; //
			sisVME_ErrorHandling (error, i, "sis3320_250_read_adc_spi");

		}
   #endif


 	return 0x0 ;


} // end function  ()


//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------

int sis3320_250_read_adc_spi(unsigned int module_addr, unsigned int adc_channel, unsigned int spi_addr, unsigned int* spi_rd_data)
{
	unsigned int i, error, temp;
	unsigned int return_code;
	unsigned int vme_data, vme_addr ;

	adc_channel = adc_channel & 0x7 ; // 0 to 7 are valid

    if ((adc_channel & 0x6) == 0) { vme_addr = module_addr + SIS3320_NG_ADC_SPI_ADC12 ;} //
    if ((adc_channel & 0x6) == 2) { vme_addr = module_addr + SIS3320_NG_ADC_SPI_ADC34 ;} //
    if ((adc_channel & 0x6) == 4) { vme_addr = module_addr + SIS3320_NG_ADC_SPI_ADC56 ;} //
    if ((adc_channel & 0x6) == 6) { vme_addr = module_addr + SIS3320_NG_ADC_SPI_ADC78 ;} //


	vme_data =  0;
    if ((adc_channel & 0x1) == 1) { vme_data = 0x400000 ;} //  ADC 2 Select bit

	vme_data =  vme_data + 0x200000 + ((spi_addr << 8) & 0x1fff00)  ;

	if ((error = sub_vme_A32D32_write(vme_addr,vme_data )) != 0) {
		sisVME_ErrorHandling (error, vme_addr, "sub_vme_A32D32_write");
		return -1;
	}

// wait 1 us !
	if ((error = sub_vme_A32D32_read(vme_addr,&vme_data )) != 0) {
		sisVME_ErrorHandling (error, vme_addr, "sub_vme_A32D32_read");
		return -1;
	}

    *spi_rd_data =    ((vme_data >> 24) & 0xff ) ;

	return 0x0 ;
} // end function  ()



//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
int sis3320_250_write_adc_spi(unsigned int module_addr, unsigned int adc_channel, unsigned int spi_addr, unsigned int spi_wr_data )
{
	unsigned int i, error, temp;
	unsigned int return_code;
	unsigned int vme_data, vme_addr ;

	adc_channel = adc_channel & 0x7 ; // 0 to 7 are valid

    if ((adc_channel & 0x6) == 0) { vme_addr = module_addr + SIS3320_NG_ADC_SPI_ADC12 ;} //
    if ((adc_channel & 0x6) == 2) { vme_addr = module_addr + SIS3320_NG_ADC_SPI_ADC34 ;} //
    if ((adc_channel & 0x6) == 4) { vme_addr = module_addr + SIS3320_NG_ADC_SPI_ADC56 ;} //
    if ((adc_channel & 0x6) == 6) { vme_addr = module_addr + SIS3320_NG_ADC_SPI_ADC78 ;} //


	vme_data =  0;
    if ((adc_channel & 0x1) == 1) { vme_data = 0x400000 ;} //  ADC 2 Select bit

	vme_data =  vme_data + ((spi_addr << 8) & 0x1fff00)  + (spi_wr_data  & 0xff);

	if ((error = sub_vme_A32D32_write(vme_addr,vme_data )) != 0) {
		sisVME_ErrorHandling (error, vme_addr, "sub_vme_A32D32_write");
		return -1;
	}

// wait 1 us !
	vme_data =  0;
    if ((adc_channel & 0x1) == 1) { vme_data = 0x400000 ;} //  ADC 2 Select bit
	vme_data =    vme_data + 0xff01 ; // update cmd
	if ((error = sub_vme_A32D32_write(vme_addr,vme_data )) != 0) {
		sisVME_ErrorHandling (error, vme_addr, "sub_vme_A32D32_write");
		return -1;
	}

	return 0x0 ;
} // end function  ()
