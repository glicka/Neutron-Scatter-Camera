/***************************************************************************/
/*                                                                         */
/*  Project: SIS3320/SIS3320-250 Neutron/Gamma                             */
/*                                                                         */
/*  Filename: sis3320_configuration.c                                      */
/*                                                                         */
/*  Funktion: configuration                                                */
/*                                                                         */
/*  Autor:                TH                                               */
/*  date:                 21.11.2006                                       */
/*  last modification:    07.02.2008                                       */
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
/*  © 2008                                                                 */
/*                                                                         */
/***************************************************************************/

//--------------------------------------------------------------------------- 
// Include files                                                              
//--------------------------------------------------------------------------- 

#include <windows.h>
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

#include "sis3150.h" 	 
#include "sis3820_clock.h" 	 
#include "sis3320_NeutronGamma.h" 	 
	  
	  
#include "pc_vme_interface_defines.h"
#include "vme_TS_communication_address_map.h"

#include "sis3150_utils.h"
#include "pc_to_vme_routines.h"

int SetDefaultConfiguration (void)	  ;
int WriteModuleParameterToInputBoxes (void) ;
int CopyModuleAddressesToTable (void)	  ;
int CopyTriggerConfvaluesToTable (void)  ;
int module_led_test (void)	   ;
int copy_clock_CommonParameters_to_inbox (void) ;
//int calculate_energy_trigger_windows_and_parameters (void)  ;
int CopyDacOffsetConfvaluesToTable (void) ;
int copy_DacOffset_inboxvalues_to_confvalues (unsigned int module_index) ;
int copy_DacOffset_confvalues_to_input_inbox (unsigned int module_index) ;
int dacReadAdcLoopOn (void) ;
int copy_sis3320_sample_CommonParameters_to_inbox (void) ;
int copy_trigger_inboxvalues_to_confvalues (unsigned int module_index) ;
int copy_trigger_confvalues_to_input_inbox (unsigned int module_index) ;
int calculateFirTriggerAdcCounts (void) ;

int copy_AdcSignal_Invert_inboxvalues_to_confvalues (unsigned int module_index) ;
int CopyAdcSignal_InvertConfvaluesToTable (void) ;
int copy_AdcSignal_Invert_confvalues_to_input_inbox (unsigned int module_index) ;
int copy_Gain_FactorFlag_inboxvalues_to_confvalues (unsigned int module_index)  ;
int CopyGain_FactorFlagConfvaluesToTable (void)  ;
int copy_Gain_FactorFlag_confvalues_to_input_inbox (unsigned int module_index)   ;


int Configuration_SIS3820Clock (void)   ;


int Send_Communication_Command_to_SIS3150_9300_TS1 (unsigned int module_addr, unsigned int mb_cmd) ; 
int Read_Communication_Reply_from_SIS3150_9300_TS1 (unsigned int module_addr, unsigned int* mb_reply);   
 
int Reset_SIS3320ADC (unsigned int module_addr, unsigned int module_conf_index ) ;
int Configuration_SIS3320ADC (unsigned int module_addr, unsigned int module_conf_index ) ;

int sub_sis3320_Configuration_DACs_setup(unsigned int module_addr, unsigned int module_conf_index) ;
int sis3320_write_dac_offset(unsigned int module_addr, unsigned int *offset_value_array) ;
int sis3320_250_write_dac_offset(unsigned int module_addr, unsigned int *offset_value_array) ;

int sub_sis3320_fastTriggerOut_setup(unsigned int module_addr, unsigned int module_conf_index) ;

 
int sis3320_250_read_adc_spi(unsigned int module_addr, unsigned int adc_channel, unsigned int spi_addr, unsigned int* spi_rd_data)	  ; 
int sis3320_250_write_adc_spi(unsigned int module_addr, unsigned int adc_channel, unsigned int spi_addr, unsigned int spi_wr_data )	   ; 

//--------------------------------------------------------------------------- 
// Root Menu Call Back
//--------------------------------------------------------------------------- 
void CVICALLBACK CB_MenuConf (int menuBar, int menuItem, void *callbackData,
        int panel)
{
	int i_mod, i_adc ;
    switch (menuItem) {
        

        
		case MENU_CONFIGURATION_CONFIGUR : {
            SystemConfiguration ()  ;
            CheckSystemStatus ()  ;
            }
            break;
        
        case MENU_CONFIGURATION_LOAD : {
            LoadConfiguration ()  ;
            }
            break;
        case MENU_CONFIGURATION_SAVE : {
            SaveConfiguration (gl_char_FileNameConf)  ;
            }
            break;
        case MENU_CONFIGURATION_SAVEAS : {
            SaveConfigurationAs ()  ;
            }
            break;
        
        case MENU_CONFIGURATION_MODULES : {
   	        SetPanelPos(Panels[MODULE_PARA_CONF],DEFINE_PANEL_MODULE_CONF_POS_Y,DEFINE_PANEL_MODULE_CONF_POS_X)  ;   // y, x
			DisplayPanel (Panels[MODULE_PARA_CONF]);
            }
            break;
            

        case MENU_CONFIGURATION_DAC_PARAM : {
 			SetCtrlVal (Panels[DAC_PARA_CONF], DAC_CONF_LED_LOOP, OFF);
  

			for(i_mod=0;i_mod<MAX_NO_OF_MODULES;i_mod++) {	
				for(i_adc=0;i_adc<8;i_adc++) {	
	   				SetTableCellAttribute (Panels[DAC_PARA_CONF], DAC_CONF_ADC_VALUE_TABLE,  MakePoint (2+i_mod, 2+i_adc),ATTR_CELL_DIMMED, ON);
				}   
			}   
			gl_uint_DacReadAdcValueLoopFlag = 0 ;
   	        SetPanelPos(Panels[DAC_PARA_CONF],DEFINE_PANEL_DAC_CONF_POS_Y,DEFINE_PANEL_DAC_CONF_POS_X)  ;   // y, x
			DisplayPanel (Panels[DAC_PARA_CONF]);
            }
            break;
            

        case MENU_CONFIGURATION_CLOCK_PARAM : {
   	        SetPanelPos(Panels[CLOCK_PARA_CONF],DEFINE_PANEL_CLOCK_CONF_POS_Y,DEFINE_PANEL_CLOCK_CONF_POS_X)  ;   // y, x
			DisplayPanel (Panels[CLOCK_PARA_CONF]);
            }
            break;


        case MENU_CONFIGURATION_TRIGGER_PARAM : {
   	        SetPanelPos(Panels[TRIG_PARA_CONF],DEFINE_PANEL_TRIGGER_CONF_POS_Y,DEFINE_PANEL_TRIGGER_CONF_POS_X)  ;   // y, x
			DisplayPanel (Panels[TRIG_PARA_CONF]);
            }
            break;

        case MENU_CONFIGURATION_SAMPLE_PARAM : {
   	        SetPanelPos(Panels[SAMPLE_PARA_CONF],DEFINE_PANEL_SAMPLE_CONF_POS_Y,DEFINE_PANEL_SAMPLE_CONF_POS_X)  ;   // y, x
			DisplayPanel (Panels[SAMPLE_PARA_CONF]);
            }
            break;

        
        case MENU_CONFIGURATION_SIGNAL_INVERT : {
   	        SetPanelPos(Panels[SIGNAL_INVERT_CONF],DEFINE_PANEL_SIGNAL_INVERT_CONF_POS_Y,DEFINE_PANEL_SIGNAL_INVERT_CONF_POS_X)  ;   // y, x
			DisplayPanel (Panels[SIGNAL_INVERT_CONF]);
            }
            break;

        case MENU_CONFIGURATION_GAIN_FACTOR : {
   	        SetPanelPos(Panels[GAIN_FACTOR_CONF],DEFINE_PANEL_GAIN_CONF_POS_Y,DEFINE_PANEL_GAI_CONF_POS_X)  ;   // y, x
			DisplayPanel (Panels[GAIN_FACTOR_CONF]);
            }
            break;
        }    // end switch menu item

	return ;
}


 

//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
void CVICALLBACK CB_Menu_ModuleLedTest (int menuBar, int menuItem, void *callbackData,
        int panel)
{
    switch (menuItem) {
        case MENUCONFMO_TESTS_LEDTEST : {
		           module_led_test () ;
           }  
           break;
     }  // switch
return;
}







//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
void CVICALLBACK CB_Menu_ModuleConfiguration (int menuBar, int menuItem, void *callbackData,
        int panel)
{
    switch (menuItem) {
        case MENUCONFMO_PANEL_CLOSE : {
            HidePanel(Panels[MODULE_PARA_CONF]); //Clear Panel 
           }  
           break;
     }  // switch
return;
}


//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
void CVICALLBACK CB_Menu_ClockParameterConfiguration (int menuBar, int menuItem, void *callbackData,
        int panel)
{
    switch (menuItem) {
        case MENUCONFCK_PANEL_CLOSE : {
            HidePanel(Panels[CLOCK_PARA_CONF]); //Clear Panel 
           }  
           break;
     }  // switch
return;
}



//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
void CVICALLBACK CB_Menu_TriggerConfiguration (int menuBar, int menuItem, void *callbackData,
        int panel)
{
    switch (menuItem) {
        case MENUCONFTR_PANEL_CLOSE : {
            HidePanel(Panels[TRIG_PARA_CONF]); //Clear Panel 
           }  
           break;
     }  // switch
return;
}



//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
void CVICALLBACK CB_Menu_CommonParameterConfiguration (int menuBar, int menuItem, void *callbackData,
        int panel)
{
int i, select;
    switch (menuItem) {
        case MENUCONFSA_DEF_TS_LOADER : {
            }
            break;

//#define  MENUCONFSA_HELP                 5
//#define  MENUCONFSA_HELP_SHOW_GATE_DIAGR 6       /* callback function: CB_Menu_CommonParameterConfiguration */

        case MENUCONFSA_HELP_SHOW_GATE_DIAGR : {
   	        SetPanelPos(Panels[SAMPLE_HELP_GATE],DEFINE_PANEL_SAMPLE_CONF_POS_Y,DEFINE_PANEL_SAMPLE_CONF_POS_X)  ;   // y, x
			DisplayPanel (Panels[SAMPLE_HELP_GATE]);
           }  
           break;

           
        case MENUCONFSA_PANEL_CLOSE : {
            HidePanel(Panels[SAMPLE_PARA_CONF]);  /* close Panels */
            HidePanel(Panels[SAMPLE_HELP_GATE]);  /* close Panels */
           }  
           break;
     }  // switch
return;
}

					   
		 	 


//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
/* close Panels */
void CVICALLBACK CB_Menu_DacOffset_Configuration (int menuBar, int menuItem, void *callbackData,
        int panel)
{
	int error=0;
	int i;
	unsigned int data_rd;
    switch (menuItem) {
        case MENUCONFDA_PANEL_CLOSE : {
			gl_uint_DacReadAdcValueLoopFlag = 0 ;
            HidePanel(Panels[DAC_PARA_CONF]); //Clear Panel 
           }  
           break;
        case MENUCONFDA_READ_LOOP_ON : {
			gl_uint_DacReadAdcValueLoopFlag = 1 ;
			dacReadAdcLoopOn ()   ;
           }  
           break;
        case MENUCONFDA_READ_LOOP_OFF : {
			gl_uint_DacReadAdcValueLoopFlag = 0 ;
           }  
           break;
        case MENUCONFDA_CONFIG_ALL_DACS : {

  		   	for (i=0;i<MAX_NO_OF_MODULES;i++) {
				if  (gl_uint_ModEnableConf[i] != 0) {  // enabled
					error=sub_sis3320_Configuration_DACs_setup(gl_uint_ModAddrConf[i], i)  ;
					if (error != 0) { 
						sisVME_ErrorHandling (error, gl_uint_ModAddrConf[i], "sub_sis3320_Configuration_DACs_setup")   ;
						gl_uint_system_status = SYSTEM_STATUS_MODULES_NOT_READY ;
					}

				} // if enabled
			} /* for loop */
           
           }  
           break;
     }  // switch
return;
}







//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 

/* close Panels */
void CVICALLBACK CB_Menu_Signal_Invert_Configuration (int menuBar, int menuItem, void *callbackData,
        int panel)
{
    switch (menuItem) {
        case MENUCONFSI_PANEL_CLOSE : {
            HidePanel(Panels[SIGNAL_INVERT_CONF]); //Clear Panel 
           }  
           break;
     }  // switch
return;
}

/* close Panels */
void CVICALLBACK CB_Menu_Gain_Factor_Configuration (int menuBar, int menuItem, void *callbackData,
        int panel)
{
    switch (menuItem) {
        case MENUCONFGF_PANEL_CLOSE : {
            HidePanel(Panels[GAIN_FACTOR_CONF]); //Clear Panel 
           }  
           break;
     }  // switch
return;
}


//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 

int CVICALLBACK CB_ModuleEnableConf (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int CviErr;
	switch (event)
		{
		case EVENT_COMMIT:
  			switch (control)
			{
				case MOD_CONF_CLOCK_MODULE_ENABLE:
				    GetCtrlVal (Panels[MODULE_PARA_CONF], MOD_CONF_CLOCK_MODULE_ENABLE, &gl_uint_SIS3820EnableConf);
					break;
				case MOD_CONF_MODULE_ENABLE_1:
				    GetCtrlVal (Panels[MODULE_PARA_CONF], MOD_CONF_MODULE_ENABLE_1, &gl_uint_ModEnableConf[0]);
					break;
				case MOD_CONF_MODULE_ENABLE_2:
				    GetCtrlVal (Panels[MODULE_PARA_CONF], MOD_CONF_MODULE_ENABLE_2, &gl_uint_ModEnableConf[1]);
					break;
				case MOD_CONF_MODULE_ENABLE_3:
				    GetCtrlVal (Panels[MODULE_PARA_CONF], MOD_CONF_MODULE_ENABLE_3, &gl_uint_ModEnableConf[2]);
					break;
				case MOD_CONF_MODULE_ENABLE_4:
				    GetCtrlVal (Panels[MODULE_PARA_CONF], MOD_CONF_MODULE_ENABLE_4, &gl_uint_ModEnableConf[3]);
					break;
				case MOD_CONF_MODULE_ENABLE_5:
				    GetCtrlVal (Panels[MODULE_PARA_CONF], MOD_CONF_MODULE_ENABLE_5, &gl_uint_ModEnableConf[4]);
					break;
				case MOD_CONF_MODULE_ENABLE_6:
				    GetCtrlVal (Panels[MODULE_PARA_CONF], MOD_CONF_MODULE_ENABLE_6, &gl_uint_ModEnableConf[5]);
					break;
				case MOD_CONF_MODULE_ENABLE_7:
				    GetCtrlVal (Panels[MODULE_PARA_CONF], MOD_CONF_MODULE_ENABLE_7, &gl_uint_ModEnableConf[6]);
					break;
				case MOD_CONF_MODULE_ENABLE_8:
				    GetCtrlVal (Panels[MODULE_PARA_CONF], MOD_CONF_MODULE_ENABLE_8, &gl_uint_ModEnableConf[7]);
					break;
				case MOD_CONF_MODULE_ENABLE_9:
				    GetCtrlVal (Panels[MODULE_PARA_CONF], MOD_CONF_MODULE_ENABLE_9, &gl_uint_ModEnableConf[8]);
					break;
				case MOD_CONF_MODULE_ENABLE_10:
				    GetCtrlVal (Panels[MODULE_PARA_CONF], MOD_CONF_MODULE_ENABLE_10, &gl_uint_ModEnableConf[9]);
					break;
				case MOD_CONF_MODULE_ENABLE_11:
				    GetCtrlVal (Panels[MODULE_PARA_CONF], MOD_CONF_MODULE_ENABLE_11, &gl_uint_ModEnableConf[10]);
					break;
				case MOD_CONF_MODULE_ENABLE_12:
				    GetCtrlVal (Panels[MODULE_PARA_CONF], MOD_CONF_MODULE_ENABLE_12, &gl_uint_ModEnableConf[11]);
					break;
				case MOD_CONF_MODULE_ENABLE_13:
				    GetCtrlVal (Panels[MODULE_PARA_CONF], MOD_CONF_MODULE_ENABLE_13, &gl_uint_ModEnableConf[12]);
					break;
				case MOD_CONF_MODULE_ENABLE_14:
				    GetCtrlVal (Panels[MODULE_PARA_CONF], MOD_CONF_MODULE_ENABLE_14, &gl_uint_ModEnableConf[13]);
					break;
			} // end switch (control)

            CopyModuleAddressesToTable();
            CheckSystemStatus() ;  
			break;
		}
	return 0;
}

			  

//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int CVICALLBACK CB_ModuleAddrConf (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int error=0;
	unsigned int data_rd;
	int CviErr;
	switch (event)
		{
		case EVENT_COMMIT:
  			switch (control)
			{
				case MOD_CONF_CLOCK_MODULE_ADDR:
				    GetCtrlVal (Panels[MODULE_PARA_CONF], MOD_CONF_CLOCK_MODULE_ADDR, &gl_uint_SIS3820AddrConf);
					break;
				case MOD_CONF_MODULE_ADDR_1:
				    GetCtrlVal (Panels[MODULE_PARA_CONF], MOD_CONF_MODULE_ADDR_1, &gl_uint_ModAddrConf[0]);
					break;
				case MOD_CONF_MODULE_ADDR_2:
				    GetCtrlVal (Panels[MODULE_PARA_CONF], MOD_CONF_MODULE_ADDR_2, &gl_uint_ModAddrConf[1]);
					break;
				case MOD_CONF_MODULE_ADDR_3:
				    GetCtrlVal (Panels[MODULE_PARA_CONF], MOD_CONF_MODULE_ADDR_3, &gl_uint_ModAddrConf[2]);
					break;
				case MOD_CONF_MODULE_ADDR_4:
				    GetCtrlVal (Panels[MODULE_PARA_CONF], MOD_CONF_MODULE_ADDR_4, &gl_uint_ModAddrConf[3]);
					break;
				case MOD_CONF_MODULE_ADDR_5:
				    GetCtrlVal (Panels[MODULE_PARA_CONF], MOD_CONF_MODULE_ADDR_5, &gl_uint_ModAddrConf[4]);
					break;
				case MOD_CONF_MODULE_ADDR_6:
				    GetCtrlVal (Panels[MODULE_PARA_CONF], MOD_CONF_MODULE_ADDR_6, &gl_uint_ModAddrConf[5]);
					break;
				case MOD_CONF_MODULE_ADDR_7:
				    GetCtrlVal (Panels[MODULE_PARA_CONF], MOD_CONF_MODULE_ADDR_7, &gl_uint_ModAddrConf[6]);
					break;
				case MOD_CONF_MODULE_ADDR_8:
				    GetCtrlVal (Panels[MODULE_PARA_CONF], MOD_CONF_MODULE_ADDR_8, &gl_uint_ModAddrConf[7]);
					break;
				case MOD_CONF_MODULE_ADDR_9:
				    GetCtrlVal (Panels[MODULE_PARA_CONF], MOD_CONF_MODULE_ADDR_9, &gl_uint_ModAddrConf[8]);
					break;
				case MOD_CONF_MODULE_ADDR_10:
				    GetCtrlVal (Panels[MODULE_PARA_CONF], MOD_CONF_MODULE_ADDR_10, &gl_uint_ModAddrConf[9]);
					break;
				case MOD_CONF_MODULE_ADDR_11:
				    GetCtrlVal (Panels[MODULE_PARA_CONF], MOD_CONF_MODULE_ADDR_11, &gl_uint_ModAddrConf[10]);
					break;
				case MOD_CONF_MODULE_ADDR_12:
				    GetCtrlVal (Panels[MODULE_PARA_CONF], MOD_CONF_MODULE_ADDR_12, &gl_uint_ModAddrConf[11]);
					break;
				case MOD_CONF_MODULE_ADDR_13:
				    GetCtrlVal (Panels[MODULE_PARA_CONF], MOD_CONF_MODULE_ADDR_13, &gl_uint_ModAddrConf[12]);
					break;
				case MOD_CONF_MODULE_ADDR_14:
				    GetCtrlVal (Panels[MODULE_PARA_CONF], MOD_CONF_MODULE_ADDR_14, &gl_uint_ModAddrConf[13]);
					break;
			} // end switch (control)

            CopyModuleAddressesToTable();
		    CheckSystemStatus() ;  

			break;
		}
	return 0;
}



//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int SaveConfigurationAs (void)
{   
int i, temp, status, select;
char tempFile[MAX_FILENAME_LEN];
int tempErr, dummy, okSema;

unsigned int xaddress ;



   GetProjectDir (gl_char_FilePathConf);
   select = FileSelectPopup (gl_char_FilePathConf, NORMAL_CONFIGURATION_FILE, "", 
											  "Save Configuration File", 
											  VAL_SAVE_BUTTON, 0, 1, 1, 1, 
											  gl_char_FileNameConf);

 //  if (select == VAL_EXISTING_FILE_SELECTED) {
      SetMenuBarAttribute  (MenuBars[MAIN_MENU_BAR], MENU_CONFIGURATION_SAVE, ATTR_DIMMED, OFF);
      SetCtrlVal (Panels[MAIN], PANEL_STRING_CONFFILE_NAME, gl_char_FileNameConf);
      tempErr = SaveConfiguration (gl_char_FileNameConf)  ;

	  if (tempErr != FILE_ACCESS_OK) {
         SetMenuBarAttribute  (MenuBars[MAIN_MENU_BAR], MENU_CONFIGURATION_SAVE, ATTR_DIMMED, ON);
         SetCtrlVal (Panels[MAIN], PANEL_STRING_CONFFILE_NAME, "error writing file ");
	  }
//    }

  return 0;
}



/*---------------------------------------------------------------------------
Get all Configuration parameter, store to variables and save into file     
---------------------------------------------------------------------------*/
int SaveConfiguration (char *path_file)
{
    int i, temp, status, okSema;
    //write actual values to file (name defined in opm_defines as constant
	int imod, iadc;
    
	unsigned int xaddress ;
	FILE *used_file ;
    char line_in[128];
    char line_out[128];

	char charLoaderFile_1[1024];	// Name und Pfad der Loader-Datei
	char path[1024];
	int  select;
	static char *timeString, *dateString;

    
    used_file=fopen(path_file, "w");
//    used_file=fopen(path_file, "w");
    if (used_file==NULL) return -1  ; // FILE_OPEN_ERROR_CONFIGURATION;

	timeString=TimeStr ();	  //get system time pointer
	dateString=DateStr ();	  // get system date pointer

    fprintf(used_file,"%s\n", STRING_CONFIGURATION_FILE);
	CopyString (line_out, 0, STRING_DATE, 0, strlen(STRING_DATE));
	CopyString (line_out, strlen(line_out), dateString, 0, 10);
	CopyString (line_out, strlen(line_out), STRING_TIME, 0, strlen(STRING_TIME));
	CopyString (line_out, strlen(line_out), timeString, 0, 8);
    fprintf(used_file,"%s \n", line_out);
    fprintf(used_file,"%s \n", STRING_BLANK);

// PC Readout Mode 
    fprintf(used_file,"%s\n", STRING_RUN_READOUT_MODE);
   	fprintf(used_file,"%8x \n",gl_uint_RunReadoutMode);
    fprintf(used_file,"%s \n", STRING_BLANK);

// Clock Module
    fprintf(used_file,"%s \n", STRING_CLOCK_MODULE);
	fprintf(used_file,"%8x %8x \n",gl_uint_SIS3820EnableConf, gl_uint_SIS3820AddrConf);
    fprintf(used_file,"%s \n", STRING_BLANK);


// Clock Modes
    fprintf(used_file,"%s \n", STRING_CLOCK_MODE);
	fprintf(used_file,"%8x \n",gl_uint_SIS3820ClockModeConf);
	fprintf(used_file,"%8x \n",gl_uint_SIS3820ClockCtrl4FlagConf);
	fprintf(used_file,"%8x \n",gl_uint_SIS3820ClockCtrl3FlagConf);
	fprintf(used_file,"%8x \n",gl_uint_SIS3820ClockCtrl2FlagConf);
	fprintf(used_file,"%8x \n",gl_uint_SIS3820ClockTriggerMaskConf);

	fprintf(used_file,"%8x \n",gl_uint_SIS3320ClockModeConf);
    fprintf(used_file,"%s \n", STRING_BLANK);


// STRING_SIS3320_MODES
    fprintf(used_file,"%s \n", STRING_SIS3320_MODES);
	fprintf(used_file,"%8x %8x %8x %8x \n",gl_uint_SIS3320_Trigger_Mode_Source_ModeConf, gl_uint_SIS3320_DUMMY_ModeConf, 
	                                       gl_uint_SIS3320External_Lemo_Trigger_FlagConf, gl_uint_SIS3320External_Lemo_TimestampClr_FlagConf);
    fprintf(used_file,"%s \n", STRING_BLANK);




// ADC Modules    
    fprintf(used_file,"%s \n", STRING_ADC_MODULES);
    for (i=0;i<MAX_NO_OF_MODULES;i++) { 
		fprintf(used_file,"%8x %8x \n",gl_uint_ModEnableConf[i], gl_uint_ModAddrConf[i]);
	}
    fprintf(used_file,"%s \n", STRING_BLANK);


    

// SIS3150 USB TS Loader File 
    fprintf(used_file,"%s \n", STRING_SIS3150USB_TS_LOADER_FILE);
    fprintf(used_file,"%s \n", gl_char_FileNameLoaderSIS3150USB_TS);
    fprintf(used_file,"%s \n", STRING_BLANK);


// Sampling and Energy 
    fprintf(used_file,"%s \n", STRING_SAMPLING_PARAMETER);

   	fprintf(used_file,"%8x %8x \n",gl_uint_MainGateLength, gl_uint_MainGatePreTriggerDelay);
   	fprintf(used_file,"%8x %8x \n",gl_uint_Gate1_Length, gl_uint_Gate1_StartIndex);
   	fprintf(used_file,"%8x %8x \n",gl_uint_Gate2_Length, gl_uint_Gate2_StartIndex);
   	fprintf(used_file,"%8x %8x \n",gl_uint_Gate3_Length, gl_uint_Gate3_StartIndex);
   	fprintf(used_file,"%8x %8x \n",gl_uint_Gate4_Length, gl_uint_Gate4_StartIndex);
   	fprintf(used_file,"%8x %8x \n",gl_uint_Gate5_Length, gl_uint_Gate5_StartIndex);
   	fprintf(used_file,"%8x %8x \n",gl_uint_Gate6_Length, gl_uint_Gate6_StartIndex);
   	fprintf(used_file,"%8x %8x \n",gl_uint_Gate7_Length, gl_uint_Gate7_StartIndex);
   	fprintf(used_file,"%8x %8x \n",gl_uint_Gate8_Length, gl_uint_Gate8_StartIndex);
   	fprintf(used_file,"%8x %8x \n",gl_uint_RawSample_Length, gl_uint_RawSample_StartIndex);
   	fprintf(used_file,"%8x %8x \n",gl_uint_RawDataSampleMode, gl_uint_RawDataTestMode);

    fprintf(used_file,"%s \n", STRING_BLANK);


// DAC Offset	
    fprintf(used_file,"%s \n", STRING_DAC_OFFSET_VALUES);
    for (imod=0;imod<MAX_NO_OF_MODULES;imod++) {   
		fprintf(used_file,"%8x %8x %8x %8x %8x %8x %8x %8x \n",	gl_uint_DacOffset_Conf[imod][INDEX_ADC_CHANNEL1],
                                                       			gl_uint_DacOffset_Conf[imod][INDEX_ADC_CHANNEL2],
                                                       			gl_uint_DacOffset_Conf[imod][INDEX_ADC_CHANNEL3],
                                                       			gl_uint_DacOffset_Conf[imod][INDEX_ADC_CHANNEL4],
                                                       			gl_uint_DacOffset_Conf[imod][INDEX_ADC_CHANNEL5],
                                                       			gl_uint_DacOffset_Conf[imod][INDEX_ADC_CHANNEL6],
                                                       			gl_uint_DacOffset_Conf[imod][INDEX_ADC_CHANNEL7],
                                                       			gl_uint_DacOffset_Conf[imod][INDEX_ADC_CHANNEL8] );
	 } 
    fprintf(used_file,"%s \n", STRING_BLANK);



// FIR Trigger values
    fprintf(used_file,"%s \n", STRING_FIR_TRIGGER_VALUES);
    for (imod=0;imod<MAX_NO_OF_MODULES;imod++) {   
    	for (iadc=0;iadc<NO_OF_ADC_CHANNELS;iadc++) {   
			fprintf(used_file,"%8x %8x %8x %8x %8x \n",gl_uint_FirTriggerP_Conf[imod][iadc],
                                                       gl_uint_FirTriggerG_Conf[imod][iadc],
                                                       gl_uint_FirTriggerThreshold_GtLtFlag_Conf[imod][iadc],
                                                       gl_int_FirTriggerThresholdValue_Conf[imod][iadc],
                                                       gl_uint_FirTriggerPulseLength_Conf[imod][iadc] );
	 	} 
	 } 
    fprintf(used_file,"%s \n", STRING_BLANK);
 

// ADC_SIGNAL_INVERT_FLAGS	
    fprintf(used_file,"%s \n", STRING_ADC_SIGNAL_INVERT_FLAGS);
    for (imod=0;imod<MAX_NO_OF_MODULES;imod++) {   
		fprintf(used_file,"%8x %8x %8x %8x %8x %8x %8x %8x \n",	gl_uint_ADC_SignalInvertConf[imod][INDEX_ADC_CHANNEL1],
                                                       			gl_uint_ADC_SignalInvertConf[imod][INDEX_ADC_CHANNEL2],
                                                       			gl_uint_ADC_SignalInvertConf[imod][INDEX_ADC_CHANNEL3],
                                                       			gl_uint_ADC_SignalInvertConf[imod][INDEX_ADC_CHANNEL4],
                                                       			gl_uint_ADC_SignalInvertConf[imod][INDEX_ADC_CHANNEL5],
                                                       			gl_uint_ADC_SignalInvertConf[imod][INDEX_ADC_CHANNEL6],
                                                       			gl_uint_ADC_SignalInvertConf[imod][INDEX_ADC_CHANNEL7],
                                                       			gl_uint_ADC_SignalInvertConf[imod][INDEX_ADC_CHANNEL8] );
	 } 
    fprintf(used_file,"%s \n", STRING_BLANK);


// ADC_GAIN_FACTOR_FLAGS	
    fprintf(used_file,"%s \n", STRING_ADC_GAIN_FACTOR_FLAGS);
    for (imod=0;imod<MAX_NO_OF_MODULES;imod++) {   
		fprintf(used_file,"%8x %8x %8x %8x %8x %8x %8x %8x \n",	gl_uint_ADC_Gain_FactorConf[imod][INDEX_ADC_CHANNEL1],
                                                       			gl_uint_ADC_Gain_FactorConf[imod][INDEX_ADC_CHANNEL2],
                                                       			gl_uint_ADC_Gain_FactorConf[imod][INDEX_ADC_CHANNEL3],
                                                       			gl_uint_ADC_Gain_FactorConf[imod][INDEX_ADC_CHANNEL4],
                                                       			gl_uint_ADC_Gain_FactorConf[imod][INDEX_ADC_CHANNEL5],
                                                       			gl_uint_ADC_Gain_FactorConf[imod][INDEX_ADC_CHANNEL6],
                                                       			gl_uint_ADC_Gain_FactorConf[imod][INDEX_ADC_CHANNEL7],
                                                       			gl_uint_ADC_Gain_FactorConf[imod][INDEX_ADC_CHANNEL8] );
	 } 
    fprintf(used_file,"%s \n", STRING_BLANK);
    fprintf(used_file,"%s \n", STRING_BLANK);

    fprintf(used_file,"%s\n", STRING_BLANK);
    fprintf(used_file,"%s\n", STRING_END_OF_FILE);

    fclose(used_file);

	return 0 ;
}


//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int FirstReadConfiguration (void)
{   
int i, select;
char tempFile[MAX_FILENAME_LEN];
int tempErr ;

   GetProjectDir (gl_char_FilePathConf);
   select = FileSelectPopup (gl_char_FilePathConf, NORMAL_CONFIGURATION_FILE, "", 
											  "Load Configuration File", 
											  VAL_LOAD_BUTTON, 0, 1, 1, 0, 
											  gl_char_FileNameConf);

   if (select == VAL_EXISTING_FILE_SELECTED) {
		SetMenuBarAttribute  (MenuBars[MAIN_MENU_BAR], MENU_CONFIGURATION_SAVE, ATTR_DIMMED, OFF);
		SetCtrlAttribute (Panels[MAIN], PANEL_STRING_CONFFILE_NAME,ATTR_CTRL_VAL,gl_char_FileNameConf);
		SetCtrlAttribute (Panels[MAIN], PANEL_STRING_CONFFILE_NAME,ATTR_TEXT_COLOR,VAL_BLACK);
		tempErr = ReadConfiguration (gl_char_FileNameConf)  ;

	  
		if (tempErr != FILE_ACCESS_OK) {
			SetDefaultConfiguration() ;
			SetMenuBarAttribute  (MenuBars[MAIN_MENU_BAR], MENU_CONFIGURATION_SAVE, ATTR_DIMMED, ON);
			SetCtrlAttribute (Panels[MAIN], PANEL_STRING_CONFFILE_NAME,ATTR_CTRL_VAL,"not valid configuration file (default configuration)");
			SetCtrlAttribute (Panels[MAIN], PANEL_STRING_CONFFILE_NAME,ATTR_TEXT_COLOR,VAL_RED);
		}
    }
    else { // VAL_NO_FILE_SELECTED; file not valid 
		SetDefaultConfiguration() ;
		SetMenuBarAttribute  (MenuBars[MAIN_MENU_BAR], MENU_CONFIGURATION_SAVE, ATTR_DIMMED, ON);
			SetCtrlAttribute (Panels[MAIN], PANEL_STRING_CONFFILE_NAME,ATTR_CTRL_VAL,"no configuration file is used (default configuration)");
			SetCtrlAttribute (Panels[MAIN], PANEL_STRING_CONFFILE_NAME,ATTR_TEXT_COLOR,VAL_RED);
    } 
	// Modules
    WriteModuleParameterToInputBoxes();
    CopyModuleAddressesToTable();


	copy_clock_CommonParameters_to_inbox () ;
	copy_sis3320_sample_CommonParameters_to_inbox()  ;

    CopyDacOffsetConfvaluesToTable () ;
	copy_DacOffset_confvalues_to_input_inbox (INDEX_MODULE1) ;


    CopyTriggerConfvaluesToTable () ;
    copy_trigger_confvalues_to_input_inbox (INDEX_MODULE1)   ;


    CopyAdcSignal_InvertConfvaluesToTable () ;
    copy_AdcSignal_Invert_confvalues_to_input_inbox (INDEX_MODULE1)   ;

    CopyGain_FactorFlagConfvaluesToTable () ;
    copy_Gain_FactorFlag_confvalues_to_input_inbox (INDEX_MODULE1)   ;

    CheckSystemStatus() ;  
  return 0;
}
 

//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int LoadConfiguration (void)
{   
int i, select;
char tempFile[MAX_FILENAME_LEN];
int tempErr ;


   GetProjectDir (gl_char_FilePathConf);
   select = FileSelectPopup (gl_char_FilePathConf, "*.ini", "", 
											  "Load Configuration File", 
											  VAL_LOAD_BUTTON, 0, 1, 1, 0, 
											  gl_char_FileNameConf);

   if (select == VAL_EXISTING_FILE_SELECTED) {
      SetMenuBarAttribute  (MenuBars[MAIN_MENU_BAR], MENU_CONFIGURATION_SAVE, ATTR_DIMMED, OFF);
      SetCtrlVal (Panels[MAIN], PANEL_STRING_CONFFILE_NAME, gl_char_FileNameConf);
      tempErr = ReadConfiguration (gl_char_FileNameConf)  ;

	  if (tempErr != FILE_ACCESS_OK) {
	     SetDefaultConfiguration() ;
         SetMenuBarAttribute  (MenuBars[MAIN_MENU_BAR], MENU_CONFIGURATION_SAVE, ATTR_DIMMED, ON);
         SetCtrlVal (Panels[MAIN], PANEL_STRING_CONFFILE_NAME, "not valid configuration file (default configuration)");
	  }
	// Modules
    WriteModuleParameterToInputBoxes();
    CopyModuleAddressesToTable();

	copy_clock_CommonParameters_to_inbox () ;
	copy_sis3320_sample_CommonParameters_to_inbox()  ;

    CopyDacOffsetConfvaluesToTable () ;
	copy_DacOffset_confvalues_to_input_inbox (INDEX_MODULE1) ;
    
    CopyTriggerConfvaluesToTable () ;
    copy_trigger_confvalues_to_input_inbox (INDEX_MODULE1)   ;

    CopyAdcSignal_InvertConfvaluesToTable () ;
    copy_AdcSignal_Invert_confvalues_to_input_inbox (INDEX_MODULE1)   ;

    CopyGain_FactorFlagConfvaluesToTable () ;
    copy_Gain_FactorFlag_confvalues_to_input_inbox (INDEX_MODULE1)   ;

    CheckSystemStatus() ;  
    }
  return 0;
}
 
 

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
	temp = errno ;
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




//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
/* functions */

int SetDefaultConfiguration (void)
{   
	int imod, iadc;
	unsigned int temp0, temp1 ;
    char messages_buffer[80] ;           

// PC Readout Mode
	gl_uint_RunReadoutMode =  RUN_READOUT_MODE_DEFAULT ;

  // Clock Module
	gl_uint_SIS3820EnableConf     = 0 ;
	gl_uint_SIS3820AddrConf       = CLOCK_MODULE_CONF_DEFAULT_ADDRESS ;
	
  // ADC Modules
	for (imod=0;imod<MAX_NO_OF_MODULES;imod++)  gl_uint_ModEnableConf[imod] = 0 ;
	for (imod=0;imod<MAX_NO_OF_MODULES;imod++) {
		gl_uint_ModAddrConf[imod]   = ADC_MODULE_CONF_DEFAULT_STARTADDRESS + (imod * ADC_MODULE_CONF_DEFAULT_ADDRESSINC) ;
	}

// Common Clock 
	gl_uint_SIS3820ClockModeConf        = CLOCK_SIS3820_CONF_DEFAULT_CLOCK_MODE ;
	gl_uint_SIS3820ClockCtrl4FlagConf   = CLOCK_SIS3820_CONF_DEFAULT_CTRL4_ENABLE_FLAG ;
	gl_uint_SIS3820ClockCtrl3FlagConf   = CLOCK_SIS3820_CONF_DEFAULT_CTRL3_ENABLE_FLAG ;
	gl_uint_SIS3820ClockCtrl2FlagConf   = CLOCK_SIS3820_CONF_DEFAULT_CTRL2_ENABLE_FLAG ;
	gl_uint_SIS3820ClockTriggerMaskConf = CLOCK_SIS3820_CONF_DEFAULT_TRIGGERMASK ;


	gl_uint_SIS3320ClockModeConf  = CLOCK_SIS3320_CONF_DEFAULT_CLOCK_MODE ;
	gl_uint_SIS3320External_Lemo_Trigger_FlagConf  = SIS3320_CONF_DEFAULT_LEMO_TRIGGER_ENABLE_FLAG ;
	gl_uint_SIS3320External_Lemo_TimestampClr_FlagConf  = SIS3320_CONF_DEFAULT_LEMO_TIMSTAMPCLR_ENABLE_FLAG ;


// sis3150USB TS Readout loaderfiel
	sprintf(gl_char_FileNameLoaderSIS3150USB_TS, NORMAL_SIS3150USB_TS_READOUT_LOADER_FILE) ;
  
// Sampling and Energy Parameters


	gl_uint_MainGateLength           = SAMPLE_MAIN_GATE_LENGTH_DEFAULT ;
	gl_uint_MainGatePreTriggerDelay  = SAMPLE_MAIN_GATE_PRETRIGGER_DELAY_DEFAULT ;
	gl_uint_Gate1_Length             = SAMPLE_GATE1_LENGTH_DEFAULT ;
	gl_uint_Gate1_StartIndex         = SAMPLE_GATE1_START_INDEX_DEFAULT ;
	gl_uint_Gate2_Length             = SAMPLE_GATE2_LENGTH_DEFAULT ;
	gl_uint_Gate2_StartIndex         = SAMPLE_GATE2_START_INDEX_DEFAULT ;
	gl_uint_Gate3_Length             = SAMPLE_GATE3_LENGTH_DEFAULT ;
	gl_uint_Gate3_StartIndex         = SAMPLE_GATE3_START_INDEX_DEFAULT ;
	gl_uint_Gate4_Length             = SAMPLE_GATE4_LENGTH_DEFAULT ;
	gl_uint_Gate4_StartIndex         = SAMPLE_GATE4_START_INDEX_DEFAULT ;
	gl_uint_Gate5_Length             = SAMPLE_GATE5_LENGTH_DEFAULT ;
	gl_uint_Gate5_StartIndex         = SAMPLE_GATE5_START_INDEX_DEFAULT ;
	gl_uint_Gate6_Length             = SAMPLE_GATE6_LENGTH_DEFAULT ;
	gl_uint_Gate6_StartIndex         = SAMPLE_GATE6_START_INDEX_DEFAULT ;
	gl_uint_Gate7_Length             = SAMPLE_GATE7_LENGTH_DEFAULT ;
	gl_uint_Gate7_StartIndex         = SAMPLE_GATE7_START_INDEX_DEFAULT ;
	gl_uint_Gate8_Length             = SAMPLE_GATE8_LENGTH_DEFAULT ;
	gl_uint_Gate8_StartIndex         = SAMPLE_GATE8_START_INDEX_DEFAULT ;
	
	gl_uint_RawSample_Length         = SAMPLE_RAW_DATA_LENGTH_DEFAULT ;
	gl_uint_RawSample_StartIndex     = SAMPLE_RAW_DATA_START_INDEX_DEFAULT ;
	gl_uint_RawDataSampleMode        = SAMPLE_RAW_DATA_MODE_DEFAULT ;
	gl_uint_RawDataTestMode          = 0 ;
	

// DAC Offset
	for (imod=0;imod < MAX_NO_OF_MODULES; imod++) {  
		for (iadc=0; iadc < NO_OF_ADC_CHANNELS; iadc++) {
			gl_uint_DacOffset_Conf[imod][iadc] =  DAC_OFFSET_DEFAULT ;
		}
	}


// Trigger 
	for (imod=0;imod < MAX_NO_OF_MODULES; imod++) {  
		for (iadc=0; iadc < NO_OF_ADC_CHANNELS; iadc++) {
			gl_uint_FirTriggerP_Conf[imod][iadc] =  FIR_TRIGGER_PEAKING_DEFAULT ;
			gl_uint_FirTriggerG_Conf[imod][iadc] =  FIR_TRIGGER_GAP_DEFAULT ;
	  		gl_uint_FirTriggerThreshold_GtLtFlag_Conf[imod][iadc] =  FIR_TRIGGER_THRESHOLD_CONF_DISABLE ;
	  		gl_int_FirTriggerThresholdValue_Conf[imod][iadc]      =  FIR_TRIGGER_THRESHOLD_CONF_DEFAULT_VALUE ;
	  		gl_uint_FirTriggerPulseLength_Conf[imod][iadc]        =  FIR_TRIGGER_PULSE_LENGTH_DEFAULT ;
		}
	}
  

// ADC_SIGNAL_INVERT_FLAGS
	for (imod=0;imod < MAX_NO_OF_MODULES; imod++) {  
		for (iadc=0; iadc < NO_OF_ADC_CHANNELS; iadc++) {
			gl_uint_ADC_SignalInvertConf[imod][iadc] =  0 ;
		}
	}

// ADC_GAIN_FACTOR_FLAGS
	for (imod=0;imod < MAX_NO_OF_MODULES; imod++) {  
		for (iadc=0; iadc < NO_OF_ADC_CHANNELS; iadc++) {
			gl_uint_ADC_Gain_FactorConf[imod][iadc] =  0 ;
		}
	}

  	sprintf (messages_buffer, "%s\n", "Set Default Parameters");
   	write_system_messages (messages_buffer, PRINT_DATE_YES)	   ;


  return 0;
}



//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int WriteModuleParameterToInputBoxes (void)
{   
int CviErr;

  // Modules
   SetCtrlAttribute (Panels[MODULE_PARA_CONF], MOD_CONF_CLOCK_MODULE_ENABLE,ATTR_CTRL_VAL, gl_uint_SIS3820EnableConf);
   SetCtrlAttribute (Panels[MODULE_PARA_CONF], MOD_CONF_MODULE_ENABLE_1,ATTR_CTRL_VAL, gl_uint_ModEnableConf[0]);
   SetCtrlAttribute (Panels[MODULE_PARA_CONF], MOD_CONF_MODULE_ENABLE_2,ATTR_CTRL_VAL, gl_uint_ModEnableConf[1]);
   SetCtrlAttribute (Panels[MODULE_PARA_CONF], MOD_CONF_MODULE_ENABLE_3,ATTR_CTRL_VAL, gl_uint_ModEnableConf[2]);
   SetCtrlAttribute (Panels[MODULE_PARA_CONF], MOD_CONF_MODULE_ENABLE_4,ATTR_CTRL_VAL, gl_uint_ModEnableConf[3]);
   SetCtrlAttribute (Panels[MODULE_PARA_CONF], MOD_CONF_MODULE_ENABLE_5,ATTR_CTRL_VAL, gl_uint_ModEnableConf[4]);
   SetCtrlAttribute (Panels[MODULE_PARA_CONF], MOD_CONF_MODULE_ENABLE_6,ATTR_CTRL_VAL, gl_uint_ModEnableConf[5]);
   SetCtrlAttribute (Panels[MODULE_PARA_CONF], MOD_CONF_MODULE_ENABLE_7,ATTR_CTRL_VAL, gl_uint_ModEnableConf[6]);
   SetCtrlAttribute (Panels[MODULE_PARA_CONF], MOD_CONF_MODULE_ENABLE_8,ATTR_CTRL_VAL, gl_uint_ModEnableConf[7]);
   SetCtrlAttribute (Panels[MODULE_PARA_CONF], MOD_CONF_MODULE_ENABLE_9,ATTR_CTRL_VAL, gl_uint_ModEnableConf[8]);
   SetCtrlAttribute (Panels[MODULE_PARA_CONF], MOD_CONF_MODULE_ENABLE_10,ATTR_CTRL_VAL, gl_uint_ModEnableConf[9]);
   SetCtrlAttribute (Panels[MODULE_PARA_CONF], MOD_CONF_MODULE_ENABLE_11,ATTR_CTRL_VAL, gl_uint_ModEnableConf[10]);
   SetCtrlAttribute (Panels[MODULE_PARA_CONF], MOD_CONF_MODULE_ENABLE_12,ATTR_CTRL_VAL, gl_uint_ModEnableConf[11]);
   SetCtrlAttribute (Panels[MODULE_PARA_CONF], MOD_CONF_MODULE_ENABLE_13,ATTR_CTRL_VAL, gl_uint_ModEnableConf[12]);
   SetCtrlAttribute (Panels[MODULE_PARA_CONF], MOD_CONF_MODULE_ENABLE_14,ATTR_CTRL_VAL, gl_uint_ModEnableConf[13]);

   SetCtrlAttribute (Panels[MODULE_PARA_CONF], MOD_CONF_CLOCK_MODULE_ADDR,ATTR_CTRL_VAL, gl_uint_SIS3820AddrConf);
   SetCtrlAttribute (Panels[MODULE_PARA_CONF], MOD_CONF_MODULE_ADDR_1,ATTR_CTRL_VAL, gl_uint_ModAddrConf[0]);
   SetCtrlAttribute (Panels[MODULE_PARA_CONF], MOD_CONF_MODULE_ADDR_2,ATTR_CTRL_VAL, gl_uint_ModAddrConf[1]);
   SetCtrlAttribute (Panels[MODULE_PARA_CONF], MOD_CONF_MODULE_ADDR_3,ATTR_CTRL_VAL, gl_uint_ModAddrConf[2]);
   SetCtrlAttribute (Panels[MODULE_PARA_CONF], MOD_CONF_MODULE_ADDR_4,ATTR_CTRL_VAL, gl_uint_ModAddrConf[3]);
   SetCtrlAttribute (Panels[MODULE_PARA_CONF], MOD_CONF_MODULE_ADDR_5,ATTR_CTRL_VAL, gl_uint_ModAddrConf[4]);
   SetCtrlAttribute (Panels[MODULE_PARA_CONF], MOD_CONF_MODULE_ADDR_6,ATTR_CTRL_VAL, gl_uint_ModAddrConf[5]);
   SetCtrlAttribute (Panels[MODULE_PARA_CONF], MOD_CONF_MODULE_ADDR_7,ATTR_CTRL_VAL, gl_uint_ModAddrConf[6]);
   SetCtrlAttribute (Panels[MODULE_PARA_CONF], MOD_CONF_MODULE_ADDR_8,ATTR_CTRL_VAL, gl_uint_ModAddrConf[7]);
   SetCtrlAttribute (Panels[MODULE_PARA_CONF], MOD_CONF_MODULE_ADDR_9,ATTR_CTRL_VAL, gl_uint_ModAddrConf[8]);
   SetCtrlAttribute (Panels[MODULE_PARA_CONF], MOD_CONF_MODULE_ADDR_10,ATTR_CTRL_VAL, gl_uint_ModAddrConf[9]);
   SetCtrlAttribute (Panels[MODULE_PARA_CONF], MOD_CONF_MODULE_ADDR_11,ATTR_CTRL_VAL, gl_uint_ModAddrConf[10]);
   SetCtrlAttribute (Panels[MODULE_PARA_CONF], MOD_CONF_MODULE_ADDR_12,ATTR_CTRL_VAL, gl_uint_ModAddrConf[11]);
   SetCtrlAttribute (Panels[MODULE_PARA_CONF], MOD_CONF_MODULE_ADDR_13,ATTR_CTRL_VAL, gl_uint_ModAddrConf[12]);
   SetCtrlAttribute (Panels[MODULE_PARA_CONF], MOD_CONF_MODULE_ADDR_14,ATTR_CTRL_VAL, gl_uint_ModAddrConf[13]);
  return 0;
}
    


//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int CopyModuleAddressesToTable (void)
{
	
   int CviErr;
   int i, j ;
   int no_of_enabled_modules ;
   int error ;
   unsigned int data_rd;


	
	no_of_enabled_modules = 0 ;
	gl_uint_system_status =  SYSTEM_STATUS_MODULES_READY ;

	// Clock Modules
	SetTableCellAttribute (Panels[MAIN], PANEL_MODULE_TABLE_2,  MakePoint (1, 2),ATTR_CELL_DIMMED, OFF);
	SetTableCellAttribute (Panels[MAIN], PANEL_MODULE_TABLE_2,  MakePoint (1, 3),ATTR_CELL_DIMMED, OFF);
	SetTableCellAttribute (Panels[MAIN], PANEL_MODULE_TABLE_2,  MakePoint (1, 4),ATTR_CELL_DIMMED, OFF);
	SetTableCellAttribute (Panels[MAIN], PANEL_MODULE_TABLE_2,  MakePoint (1, 1),ATTR_TEXT_BGCOLOR, VAL_WHITE);
	SetTableCellAttribute (Panels[MAIN], PANEL_MODULE_TABLE_2,  MakePoint (1, 2),ATTR_TEXT_BGCOLOR, VAL_WHITE);
	SetTableCellAttribute (Panels[MAIN], PANEL_MODULE_TABLE_2,  MakePoint (1, 3),ATTR_TEXT_BGCOLOR, VAL_WHITE);
	SetTableCellAttribute (Panels[MAIN], PANEL_MODULE_TABLE_2,  MakePoint (1, 4),ATTR_TEXT_BGCOLOR, VAL_WHITE);

	SetTableCellAttribute (Panels[MAIN], PANEL_MODULE_TABLE_2,  MakePoint (1, 1),ATTR_CTRL_VAL,gl_uint_SIS3820EnableConf);
	SetTableCellAttribute (Panels[MAIN], PANEL_MODULE_TABLE_2,  MakePoint (1, 2),ATTR_CTRL_VAL,gl_uint_SIS3820AddrConf);
	// check if disabled/enabled
	if  (gl_uint_SIS3820EnableConf == 0) {  // disabled
		SetTableCellAttribute (Panels[MAIN], PANEL_MODULE_TABLE_2,  MakePoint (1, 3),ATTR_CTRL_VAL,0x0);
        SetTableCellAttribute (Panels[MAIN], PANEL_MODULE_TABLE_2,  MakePoint (1, 4),ATTR_CTRL_VAL,0x0);
        SetTableCellAttribute (Panels[MAIN], PANEL_MODULE_TABLE_2,  MakePoint (1, 2),ATTR_CELL_DIMMED, ON);
        SetTableCellAttribute (Panels[MAIN], PANEL_MODULE_TABLE_2,  MakePoint (1, 3),ATTR_CELL_DIMMED, ON);
        SetTableCellAttribute (Panels[MAIN], PANEL_MODULE_TABLE_2,  MakePoint (1, 4),ATTR_CELL_DIMMED, ON);
	}
	else {   // enabled
        error = sub_vme_A32D32_read(gl_uint_SIS3820AddrConf + SIS3820CLOCK_MODID, &data_rd) ;
        if (error != 0x0) { // vme error
			SetTableCellAttribute (Panels[MAIN], PANEL_MODULE_TABLE_2,  MakePoint (1, 3),ATTR_CTRL_VAL,0xEEEE);
			SetTableCellAttribute (Panels[MAIN], PANEL_MODULE_TABLE_2,  MakePoint (1, 4),ATTR_CTRL_VAL,0xEEEE);
			SetTableCellAttribute (Panels[MAIN], PANEL_MODULE_TABLE_2,  MakePoint (1, 1),ATTR_TEXT_BGCOLOR, VAL_RED);
			SetTableCellAttribute (Panels[MAIN], PANEL_MODULE_TABLE_2,  MakePoint (1, 2),ATTR_TEXT_BGCOLOR, VAL_RED);
			SetTableCellAttribute (Panels[MAIN], PANEL_MODULE_TABLE_2,  MakePoint (1, 3),ATTR_TEXT_BGCOLOR, VAL_RED);
			SetTableCellAttribute (Panels[MAIN], PANEL_MODULE_TABLE_2,  MakePoint (1, 4),ATTR_TEXT_BGCOLOR, VAL_RED);
			gl_uint_system_status =  SYSTEM_STATUS_MODULES_NOT_READY ; 
		}
		else { // VME OK	    
			SetTableCellAttribute (Panels[MAIN], PANEL_MODULE_TABLE_2,  MakePoint (1, 3),ATTR_CTRL_VAL,(data_rd >> 16) & 0xffff);
			SetTableCellAttribute (Panels[MAIN], PANEL_MODULE_TABLE_2,  MakePoint (1, 4),ATTR_CTRL_VAL,(data_rd ) & 0xffff);
			gl_uint_SIS3820_Version = data_rd ;
			if( ((data_rd  & 0xffffff00) != 0x3820E000) && (((data_rd  & 0xffffff00) != 0x3820E200)) ) { // check Mod ID and Major Version	
				SetTableCellAttribute (Panels[MAIN], PANEL_MODULE_TABLE_2,  MakePoint (1, 3),ATTR_TEXT_BGCOLOR, VAL_RED);
				SetTableCellAttribute (Panels[MAIN], PANEL_MODULE_TABLE_2,  MakePoint (1, 4),ATTR_TEXT_BGCOLOR, VAL_RED);
				gl_uint_system_status =  SYSTEM_STATUS_MODULES_NOT_READY ; 
			}	

		   if ((gl_uint_SIS3820_Version & 0xffffff00) == 0x3820E000)   { 
	  			SetCtrlAttribute (Panels[CLOCK_PARA_CONF],CLOCK_CONF_SIS3820_MODE_CLK, ATTR_VISIBLE, 1);
	  			SetCtrlAttribute (Panels[CLOCK_PARA_CONF],CLOCK_CONF_SIS3820_MODE_CLK_E2, ATTR_VISIBLE, 0);
		   }
		   else {
	  			SetCtrlAttribute (Panels[CLOCK_PARA_CONF],CLOCK_CONF_SIS3820_MODE_CLK, ATTR_VISIBLE, 0);
	  			SetCtrlAttribute (Panels[CLOCK_PARA_CONF],CLOCK_CONF_SIS3820_MODE_CLK_E2, ATTR_VISIBLE, 1);
		   }
						
		}	
	
	}

  
   for (i=0;i<MAX_NO_OF_MODULES;i++) {


     SetTableCellAttribute (Panels[MAIN], PANEL_MODULE1_TABLE,  MakePoint (1+i, 2),ATTR_CELL_DIMMED, OFF);
     SetTableCellAttribute (Panels[MAIN], PANEL_MODULE1_TABLE,  MakePoint (1+i, 3),ATTR_CELL_DIMMED, OFF);
     SetTableCellAttribute (Panels[MAIN], PANEL_MODULE1_TABLE,  MakePoint (1+i, 4),ATTR_CELL_DIMMED, OFF);
     SetTableCellAttribute (Panels[MAIN], PANEL_MODULE1_TABLE,  MakePoint (i+1, 1),ATTR_TEXT_BGCOLOR, VAL_WHITE);
     SetTableCellAttribute (Panels[MAIN], PANEL_MODULE1_TABLE,  MakePoint (i+1, 2),ATTR_TEXT_BGCOLOR, VAL_WHITE);
     SetTableCellAttribute (Panels[MAIN], PANEL_MODULE1_TABLE,  MakePoint (i+1, 3),ATTR_TEXT_BGCOLOR, VAL_WHITE);
     SetTableCellAttribute (Panels[MAIN], PANEL_MODULE1_TABLE,  MakePoint (i+1, 4),ATTR_TEXT_BGCOLOR, VAL_WHITE);

     SetTableCellAttribute (Panels[MAIN], PANEL_MODULE1_TABLE,  MakePoint (1+i, 1),ATTR_CTRL_VAL,gl_uint_ModEnableConf[i]);
     SetTableCellAttribute (Panels[MAIN], PANEL_MODULE1_TABLE,  MakePoint (1+i, 2),ATTR_CTRL_VAL,gl_uint_ModAddrConf[i]);



	 // check if disabled/enabled
     if  (gl_uint_ModEnableConf[i] == 0) {  // disabled
		gl_uint_SIS3320_250_FlagConf[i] = 0 ;

//		gl_uint_module_status = MODULE_STATUS_NOT_VALID ; 
        SetTableCellAttribute (Panels[MAIN], PANEL_MODULE1_TABLE,  MakePoint (1+i, 3),ATTR_CTRL_VAL,0x0);
        SetTableCellAttribute (Panels[MAIN], PANEL_MODULE1_TABLE,  MakePoint (1+i, 4),ATTR_CTRL_VAL,0x0);
        SetTableCellAttribute (Panels[MAIN], PANEL_MODULE1_TABLE,  MakePoint (1+i, 2),ATTR_CELL_DIMMED, ON);
        SetTableCellAttribute (Panels[MAIN], PANEL_MODULE1_TABLE,  MakePoint (1+i, 3),ATTR_CELL_DIMMED, ON);
        SetTableCellAttribute (Panels[MAIN], PANEL_MODULE1_TABLE,  MakePoint (1+i, 4),ATTR_CELL_DIMMED, ON);
      
      }
      else {   // enabled
        error = sub_vme_A32D32_read(gl_uint_ModAddrConf[i] + SIS3320_MODID , &data_rd) ;
        if (error != 0x0) { // vme error
           SetTableCellAttribute (Panels[MAIN], PANEL_MODULE1_TABLE,  MakePoint (1+i, 3),ATTR_CTRL_VAL,0xEEEE);
           SetTableCellAttribute (Panels[MAIN], PANEL_MODULE1_TABLE,  MakePoint (1+i, 4),ATTR_CTRL_VAL,0xEEEE);
           SetTableCellAttribute (Panels[MAIN], PANEL_MODULE1_TABLE,  MakePoint (i+1, 1),ATTR_TEXT_BGCOLOR, VAL_RED);
           SetTableCellAttribute (Panels[MAIN], PANEL_MODULE1_TABLE,  MakePoint (i+1, 2),ATTR_TEXT_BGCOLOR, VAL_RED);
           SetTableCellAttribute (Panels[MAIN], PANEL_MODULE1_TABLE,  MakePoint (i+1, 3),ATTR_TEXT_BGCOLOR, VAL_RED);
           SetTableCellAttribute (Panels[MAIN], PANEL_MODULE1_TABLE,  MakePoint (i+1, 4),ATTR_TEXT_BGCOLOR, VAL_RED);
		   gl_uint_system_status =  SYSTEM_STATUS_MODULES_NOT_READY ; 
	     }
         else  {  // vme OK
			SetTableCellAttribute (Panels[MAIN], PANEL_MODULE1_TABLE,  MakePoint (1+i, 3),ATTR_CTRL_VAL,(data_rd ) );
			//SetTableCellAttribute (Panels[MAIN], PANEL_MODULE1_TABLE,  MakePoint (1+i, 3),ATTR_CTRL_VAL,(data_rd >> 16) & 0xffff);
			SetTableCellAttribute (Panels[MAIN], PANEL_MODULE1_TABLE,  MakePoint (1+i, 4),ATTR_CTRL_VAL,(data_rd ) & 0xffff);
			
		   if ( ((data_rd >> 16) & 0xffff) == 0x3302) {
				gl_uint_SIS3302_FlagConf[i] = 1; 
       			SetTableCellVal (Panels[MAIN], PANEL_MODULE1_TABLE,  MakePoint (1+i, 5),"SIS3302");
				gl_uint_SIS3320_250_FlagConf[i] = 0 ;
		   }
		   else {
				gl_uint_SIS3302_FlagConf[i] = 0; 
		   		if ( ((data_rd >> 16) & 0xffff) == 0x3320) {
			  		if (((data_rd ) & 0xffff) < 0x2000) {
						gl_uint_SIS3320_250_FlagConf[i] = 0 ;
           				SetTableCellVal (Panels[MAIN], PANEL_MODULE1_TABLE,  MakePoint (1+i, 5),"SIS3320");
		   			}
		   			else {
						gl_uint_SIS3320_250_FlagConf[i] = 1 ;
           				SetTableCellVal (Panels[MAIN], PANEL_MODULE1_TABLE,  MakePoint (1+i, 5),"SIS3320-250");
		   			}
		   		}
		   		else {
           			SetTableCellVal (Panels[MAIN], PANEL_MODULE1_TABLE,  MakePoint (1+i, 5)," ");
		   		}
		   	}

           
           no_of_enabled_modules++;
         }  // VME OK
      } // disabled/enabled
   } /* for loop */
   /* if no module is disabled then */
   if (no_of_enabled_modules == 0)   { gl_uint_system_status =  SYSTEM_STATUS_MODULES_NOT_READY ;}

   // if the first module a sis3302 then set CVI parameters to the SIS3302 16-bit ADC 	
   if (gl_uint_SIS3302_FlagConf[0] == 0)   { 
		// different clock setup
		SetCtrlVal (Panels[CLOCK_PARA_CONF], CLOCK_CONF_CURSORMSG_CLOCK,"SIS3320 ADC Modules");  
	  	SetCtrlAttribute (Panels[CLOCK_PARA_CONF],CLOCK_CONF_SIS3320_MODE_CLK, ATTR_VISIBLE, 1);
	  	SetCtrlAttribute (Panels[CLOCK_PARA_CONF],CLOCK_CONF_SIS3302_MODE_CLK, ATTR_VISIBLE, 0);
		// different Trigger
	  	SetCtrlAttribute (Panels[TRIG_PARA_CONF],TRIG_CONF_FIR_TRIGGER_P_1, ATTR_MAX_VALUE, 16);
	  	SetCtrlAttribute (Panels[TRIG_PARA_CONF],TRIG_CONF_FIR_TRIGGER_P_2, ATTR_MAX_VALUE, 16);
	  	SetCtrlAttribute (Panels[TRIG_PARA_CONF],TRIG_CONF_FIR_TRIGGER_P_3, ATTR_MAX_VALUE, 16);
	  	SetCtrlAttribute (Panels[TRIG_PARA_CONF],TRIG_CONF_FIR_TRIGGER_P_4, ATTR_MAX_VALUE, 16);
	  	SetCtrlAttribute (Panels[TRIG_PARA_CONF],TRIG_CONF_FIR_TRIGGER_P_5, ATTR_MAX_VALUE, 16);
	  	SetCtrlAttribute (Panels[TRIG_PARA_CONF],TRIG_CONF_FIR_TRIGGER_P_6, ATTR_MAX_VALUE, 16);
	  	SetCtrlAttribute (Panels[TRIG_PARA_CONF],TRIG_CONF_FIR_TRIGGER_P_7, ATTR_MAX_VALUE, 16);
	  	SetCtrlAttribute (Panels[TRIG_PARA_CONF],TRIG_CONF_FIR_TRIGGER_P_8, ATTR_MAX_VALUE, 16);
	  	
	  	SetCtrlAttribute (Panels[TRIG_PARA_CONF],TRIG_CONF_FIR_TRIGGER_G_1, ATTR_MAX_VALUE, 16);
	  	SetCtrlAttribute (Panels[TRIG_PARA_CONF],TRIG_CONF_FIR_TRIGGER_G_2, ATTR_MAX_VALUE, 16);
	  	SetCtrlAttribute (Panels[TRIG_PARA_CONF],TRIG_CONF_FIR_TRIGGER_G_3, ATTR_MAX_VALUE, 16);
	  	SetCtrlAttribute (Panels[TRIG_PARA_CONF],TRIG_CONF_FIR_TRIGGER_G_4, ATTR_MAX_VALUE, 16);
	  	SetCtrlAttribute (Panels[TRIG_PARA_CONF],TRIG_CONF_FIR_TRIGGER_G_5, ATTR_MAX_VALUE, 16);
	  	SetCtrlAttribute (Panels[TRIG_PARA_CONF],TRIG_CONF_FIR_TRIGGER_G_6, ATTR_MAX_VALUE, 16);
	  	SetCtrlAttribute (Panels[TRIG_PARA_CONF],TRIG_CONF_FIR_TRIGGER_G_7, ATTR_MAX_VALUE, 16);
	  	SetCtrlAttribute (Panels[TRIG_PARA_CONF],TRIG_CONF_FIR_TRIGGER_G_8, ATTR_MAX_VALUE, 16);

		// Accumulator 5 to 8 Gate Length
	  	SetCtrlAttribute (Panels[SAMPLE_PARA_CONF],SAMPL_CONF_GATE5_LENGTH, ATTR_MAX_VALUE, 15);
	  	SetCtrlAttribute (Panels[SAMPLE_PARA_CONF],SAMPL_CONF_GATE6_LENGTH, ATTR_MAX_VALUE, 15);
	  	SetCtrlAttribute (Panels[SAMPLE_PARA_CONF],SAMPL_CONF_GATE7_LENGTH, ATTR_MAX_VALUE, 15);
	  	SetCtrlAttribute (Panels[SAMPLE_PARA_CONF],SAMPL_CONF_GATE8_LENGTH, ATTR_MAX_VALUE, 15);

		// Accumulator Data Format (6 or 8 Accumulators)
	  	SetCtrlAttribute (Panels[SAMPLE_PARA_CONF],SAMPL_CONF_ACCU_DATA_FORMAT, ATTR_VISIBLE, 0);
	  	SetCtrlVal (Panels[SAMPLE_PARA_CONF],SAMPL_CONF_ACCU_DATA_FORMAT, 0);
 

   }
   else {
		// different clock setup
		SetCtrlVal (Panels[CLOCK_PARA_CONF], CLOCK_CONF_CURSORMSG_CLOCK,"SIS3302 ADC Modules");  
	  	SetCtrlAttribute (Panels[CLOCK_PARA_CONF],CLOCK_CONF_SIS3320_MODE_CLK, ATTR_VISIBLE, 0);
	  	SetCtrlAttribute (Panels[CLOCK_PARA_CONF],CLOCK_CONF_SIS3302_MODE_CLK, ATTR_VISIBLE, 1);

		// different Trigger
	  	SetCtrlAttribute (Panels[TRIG_PARA_CONF],TRIG_CONF_FIR_TRIGGER_P_1, ATTR_MAX_VALUE, 64);
	  	SetCtrlAttribute (Panels[TRIG_PARA_CONF],TRIG_CONF_FIR_TRIGGER_P_2, ATTR_MAX_VALUE, 64);
	  	SetCtrlAttribute (Panels[TRIG_PARA_CONF],TRIG_CONF_FIR_TRIGGER_P_3, ATTR_MAX_VALUE, 64);
	  	SetCtrlAttribute (Panels[TRIG_PARA_CONF],TRIG_CONF_FIR_TRIGGER_P_4, ATTR_MAX_VALUE, 64);
	  	SetCtrlAttribute (Panels[TRIG_PARA_CONF],TRIG_CONF_FIR_TRIGGER_P_5, ATTR_MAX_VALUE, 64);
	  	SetCtrlAttribute (Panels[TRIG_PARA_CONF],TRIG_CONF_FIR_TRIGGER_P_6, ATTR_MAX_VALUE, 64);
	  	SetCtrlAttribute (Panels[TRIG_PARA_CONF],TRIG_CONF_FIR_TRIGGER_P_7, ATTR_MAX_VALUE, 64);
	  	SetCtrlAttribute (Panels[TRIG_PARA_CONF],TRIG_CONF_FIR_TRIGGER_P_8, ATTR_MAX_VALUE, 64);
	  	
	  	SetCtrlAttribute (Panels[TRIG_PARA_CONF],TRIG_CONF_FIR_TRIGGER_G_1, ATTR_MAX_VALUE, 64);
	  	SetCtrlAttribute (Panels[TRIG_PARA_CONF],TRIG_CONF_FIR_TRIGGER_G_2, ATTR_MAX_VALUE, 64);
	  	SetCtrlAttribute (Panels[TRIG_PARA_CONF],TRIG_CONF_FIR_TRIGGER_G_3, ATTR_MAX_VALUE, 64);
	  	SetCtrlAttribute (Panels[TRIG_PARA_CONF],TRIG_CONF_FIR_TRIGGER_G_4, ATTR_MAX_VALUE, 64);
	  	SetCtrlAttribute (Panels[TRIG_PARA_CONF],TRIG_CONF_FIR_TRIGGER_G_5, ATTR_MAX_VALUE, 64);
	  	SetCtrlAttribute (Panels[TRIG_PARA_CONF],TRIG_CONF_FIR_TRIGGER_G_6, ATTR_MAX_VALUE, 64);
	  	SetCtrlAttribute (Panels[TRIG_PARA_CONF],TRIG_CONF_FIR_TRIGGER_G_7, ATTR_MAX_VALUE, 64);
	  	SetCtrlAttribute (Panels[TRIG_PARA_CONF],TRIG_CONF_FIR_TRIGGER_G_8, ATTR_MAX_VALUE, 64);

		// Accumulator 5 to 8 Gate Length
	  	SetCtrlAttribute (Panels[SAMPLE_PARA_CONF],SAMPL_CONF_GATE5_LENGTH, ATTR_MAX_VALUE, 511);
	  	SetCtrlAttribute (Panels[SAMPLE_PARA_CONF],SAMPL_CONF_GATE6_LENGTH, ATTR_MAX_VALUE, 511);
	  	SetCtrlAttribute (Panels[SAMPLE_PARA_CONF],SAMPL_CONF_GATE7_LENGTH, ATTR_MAX_VALUE, 511);
	  	SetCtrlAttribute (Panels[SAMPLE_PARA_CONF],SAMPL_CONF_GATE8_LENGTH, ATTR_MAX_VALUE, 511);

		// Accumulator Data Format (6 or 8 Accumulators)
	  	SetCtrlAttribute (Panels[SAMPLE_PARA_CONF],SAMPL_CONF_ACCU_DATA_FORMAT, ATTR_VISIBLE, 1);
	  	SetCtrlVal (Panels[SAMPLE_PARA_CONF],SAMPL_CONF_ACCU_DATA_FORMAT, 0);
   
   
   } 
  
   
   return 0;
} // end function  ()


//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int module_led_test (void)
{
	
   int CviErr;
   int i ;
   int no_of_enabled_modules ;
   int error ;
   unsigned int data_rd;
   int idelay, times, temp = 0 ;

   for (times=0;times<10;times++) {
	if  (gl_uint_SIS3820EnableConf != 0) {  // disabled
	 	error = sub_vme_A32D32_write (gl_uint_SIS3820AddrConf + SIS3150_CONTROL_STATUS, CTRL_USER_LED_ON) ;
        if (error != 0x0) { // vme error
           SetTableCellAttribute (Panels[MAIN], PANEL_MODULE_TABLE_2,  MakePoint (i+1, 1),ATTR_TEXT_BGCOLOR, VAL_RED);
           SetTableCellAttribute (Panels[MAIN], PANEL_MODULE_TABLE_2,  MakePoint (i+1, 2),ATTR_TEXT_BGCOLOR, VAL_RED);
           SetTableCellAttribute (Panels[MAIN], PANEL_MODULE_TABLE_2,  MakePoint (i+1, 3),ATTR_TEXT_BGCOLOR, VAL_RED);
           SetTableCellAttribute (Panels[MAIN], PANEL_MODULE_TABLE_2,  MakePoint (i+1, 4),ATTR_TEXT_BGCOLOR, VAL_RED);
	     }
	 }

    for (i=0;i<MAX_NO_OF_MODULES;i++) {
     if  (gl_uint_ModEnableConf[i] != 0) {  // enabled
		error = sub_vme_A32D32_write (gl_uint_ModAddrConf[i] + SIS3150_CONTROL_STATUS, CTRL_USER_LED_ON) ;
        if (error != 0x0) { // vme error
           SetTableCellAttribute (Panels[MAIN], PANEL_MODULE1_TABLE,  MakePoint (i+1, 1),ATTR_TEXT_BGCOLOR, VAL_RED);
           SetTableCellAttribute (Panels[MAIN], PANEL_MODULE1_TABLE,  MakePoint (i+1, 2),ATTR_TEXT_BGCOLOR, VAL_RED);
           SetTableCellAttribute (Panels[MAIN], PANEL_MODULE1_TABLE,  MakePoint (i+1, 3),ATTR_TEXT_BGCOLOR, VAL_RED);
           SetTableCellAttribute (Panels[MAIN], PANEL_MODULE1_TABLE,  MakePoint (i+1, 4),ATTR_TEXT_BGCOLOR, VAL_RED);
           SetTableCellAttribute (Panels[MAIN], PANEL_MODULE1_TABLE,  MakePoint (i+1, 5),ATTR_TEXT_BGCOLOR, VAL_RED);
           SetTableCellAttribute (Panels[MAIN], PANEL_MODULE1_TABLE,  MakePoint (i+1, 6),ATTR_TEXT_BGCOLOR, VAL_RED);
	     }
    for (idelay=0;idelay<0x100000;idelay++) temp++ ;
      } // disabled/enabled

     } /* for loop */

   i=0;
   for (idelay=0;idelay<0x100000;idelay++) i++ ;
   //delay

	if  (gl_uint_SIS3820EnableConf != 0) {  // disabled
	 	error = sub_vme_A32D32_write (gl_uint_SIS3820AddrConf + SIS3150_CONTROL_STATUS, CTRL_USER_LED_OFF) ;
        if (error != 0x0) { // vme error
           SetTableCellAttribute (Panels[MAIN], PANEL_MODULE_TABLE_2,  MakePoint (i+1, 1),ATTR_TEXT_BGCOLOR, VAL_RED);
           SetTableCellAttribute (Panels[MAIN], PANEL_MODULE_TABLE_2,  MakePoint (i+1, 2),ATTR_TEXT_BGCOLOR, VAL_RED);
           SetTableCellAttribute (Panels[MAIN], PANEL_MODULE_TABLE_2,  MakePoint (i+1, 3),ATTR_TEXT_BGCOLOR, VAL_RED);
           SetTableCellAttribute (Panels[MAIN], PANEL_MODULE_TABLE_2,  MakePoint (i+1, 4),ATTR_TEXT_BGCOLOR, VAL_RED);
	     }
	 }

   for (i=0;i<MAX_NO_OF_MODULES;i++) {
     if  (gl_uint_ModEnableConf[i] != 0) {  // enabled
		error = sub_vme_A32D32_write (gl_uint_ModAddrConf[i] + SIS3150_CONTROL_STATUS, CTRL_USER_LED_OFF) ;
        if (error != 0x0) { // vme error
           SetTableCellAttribute (Panels[MAIN], PANEL_MODULE1_TABLE,  MakePoint (i+1, 1),ATTR_TEXT_BGCOLOR, VAL_RED);
           SetTableCellAttribute (Panels[MAIN], PANEL_MODULE1_TABLE,  MakePoint (i+1, 2),ATTR_TEXT_BGCOLOR, VAL_RED);
           SetTableCellAttribute (Panels[MAIN], PANEL_MODULE1_TABLE,  MakePoint (i+1, 3),ATTR_TEXT_BGCOLOR, VAL_RED);
           SetTableCellAttribute (Panels[MAIN], PANEL_MODULE1_TABLE,  MakePoint (i+1, 4),ATTR_TEXT_BGCOLOR, VAL_RED);
           SetTableCellAttribute (Panels[MAIN], PANEL_MODULE1_TABLE,  MakePoint (i+1, 5),ATTR_TEXT_BGCOLOR, VAL_RED);
           SetTableCellAttribute (Panels[MAIN], PANEL_MODULE1_TABLE,  MakePoint (i+1, 6),ATTR_TEXT_BGCOLOR, VAL_RED);
	     }
   for (idelay=0;idelay<0x100000;idelay++) temp++ ; ;

      } // disabled/enabled

   } /* for loop */

   } // times
   
   /* if no module is disabled then */
//   if (no_of_enabled_modules == 0)   gl_uint_module_status = MODULE_STATUS_NOT_VALID ;
   
   return 0;
} // end function  ()


//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int CheckSystemStatus (void)
{
   int cvi_err ;
// Modules not ready 
   if (gl_uint_system_status == SYSTEM_STATUS_MODULES_NOT_READY) {
  	 SetCtrlAttribute (Panels[MAIN], PANEL_SYSTEM_LED, ATTR_ON_COLOR, VAL_RED);
     MenuBars[MAIN_MENU_BAR] = LoadMenuBar (Panels[MAIN], "sis3320_NeutronGamma_uir.uir", MENU) ;

	 MenuBars[CONFMODULE_MENU_BAR] = LoadMenuBar (Panels[MODULE_PARA_CONF], "sis3320_NeutronGamma_uir.uir", MENUCONFMO) ;
	 MenuBars[CONFDAC_MENU_BAR] = LoadMenuBar (Panels[DAC_PARA_CONF], "sis3320_NeutronGamma_uir.uir", MENUCONFDA) ;
   	 MenuBars[CONFCLOCK_MENU_BAR] = LoadMenuBar (Panels[CLOCK_PARA_CONF], "sis3320_NeutronGamma_uir.uir", MENUCONFCK) ;
   	 MenuBars[CONFTRIG_MENU_BAR]   = LoadMenuBar (Panels[TRIG_PARA_CONF], "sis3320_NeutronGamma_uir.uir", MENUCONFTR) ;
   	 MenuBars[CONFSAMPLE_MENU_BAR] = LoadMenuBar (Panels[SAMPLE_PARA_CONF], "sis3320_NeutronGamma_uir.uir", MENUCONFSA) ;

   	 MenuBars[CONF_SIGNAL_INVERT_MENU_BAR] = LoadMenuBar (Panels[SIGNAL_INVERT_CONF], "sis3320_NeutronGamma_uir.uir", MENUCONFSI) ; // ADC Signal Invert
   	 MenuBars[CONF_GAIN_FACTOR_MENU_BAR] = LoadMenuBar (Panels[GAIN_FACTOR_CONF], "sis3320_NeutronGamma_uir.uir", MENUCONFGF) ; // ADC Gain Factor
   	 
   	 

	 MenuBars[RUNCTRL_MENU_BAR] = LoadMenuBar (Panels[RUN_CTRL_MENUE], "sis3320_NeutronGamma_uir.uir", MENUCTRLRU) ;
	 MenuBars[DISPLAY_GRAPH_RAW_MENU_BAR] = LoadMenuBar (Panels[PANEL_DISPLAY_RAW], "sis3320_NeutronGamma_uir.uir", MENUGR_RAW) ;
	 MenuBars[DISPLAY_GRAPH_ENERGY_VAL_MENU_BAR] = LoadMenuBar (Panels[PANEL_DISPLAY_EVALUES], "sis3320_NeutronGamma_uir.uir", MENUGR_ENE) ;
	 MenuBars[DISPLAY_GRAPH_ENERGY_SPEC_MENU_BAR] = LoadMenuBar (Panels[PANEL_DISPLAY_ENERGY_SPEC], "sis3320_NeutronGamma_uir.uir", MENUGR_SPE) ;

     SetMenuBarAttribute  (MenuBars[MAIN_MENU_BAR], MENU_CONFIGURATION, ATTR_DIMMED, OFF);
     return 0 ;
   }


// Modules ready but not configrued 
   if (gl_uint_system_status == SYSTEM_STATUS_MODULES_READY) {
  	 SetCtrlAttribute (Panels[MAIN], PANEL_SYSTEM_LED, ATTR_ON_COLOR, VAL_YELLOW);
     MenuBars[MAIN_MENU_BAR] = LoadMenuBar (Panels[MAIN], "sis3320_NeutronGamma_uir.uir", MENU) ;

	 MenuBars[CONFMODULE_MENU_BAR] = LoadMenuBar (Panels[MODULE_PARA_CONF], "sis3320_NeutronGamma_uir.uir", MENUCONFMO) ;
	 MenuBars[CONFDAC_MENU_BAR] = LoadMenuBar (Panels[DAC_PARA_CONF], "sis3320_NeutronGamma_uir.uir", MENUCONFDA) ;
   	 MenuBars[CONFCLOCK_MENU_BAR] = LoadMenuBar (Panels[CLOCK_PARA_CONF], "sis3320_NeutronGamma_uir.uir", MENUCONFCK) ;
   	 MenuBars[CONFTRIG_MENU_BAR]   = LoadMenuBar (Panels[TRIG_PARA_CONF], "sis3320_NeutronGamma_uir.uir", MENUCONFTR) ;
   	 MenuBars[CONFSAMPLE_MENU_BAR] = LoadMenuBar (Panels[SAMPLE_PARA_CONF], "sis3320_NeutronGamma_uir.uir", MENUCONFSA) ;

	 MenuBars[RUNCTRL_MENU_BAR] = LoadMenuBar (Panels[RUN_CTRL_MENUE], "sis3320_NeutronGamma_uir.uir", MENUCTRLRU) ;
	 MenuBars[DISPLAY_GRAPH_RAW_MENU_BAR] = LoadMenuBar (Panels[PANEL_DISPLAY_RAW], "sis3320_NeutronGamma_uir.uir", MENUGR_RAW) ;
	 MenuBars[DISPLAY_GRAPH_ENERGY_VAL_MENU_BAR] = LoadMenuBar (Panels[PANEL_DISPLAY_EVALUES], "sis3320_NeutronGamma_uir.uir", MENUGR_ENE) ;
	 MenuBars[DISPLAY_GRAPH_ENERGY_SPEC_MENU_BAR] = LoadMenuBar (Panels[PANEL_DISPLAY_ENERGY_SPEC], "sis3320_NeutronGamma_uir.uir", MENUGR_SPE) ;

     return 0 ;
   }


// Modules configrued 
   if (gl_uint_system_status == SYSTEM_STATUS_MODULES_CONFIGURED) {
  	 SetCtrlAttribute (Panels[MAIN], PANEL_SYSTEM_LED, ATTR_ON_COLOR, VAL_GREEN);

     MenuBars[MAIN_MENU_BAR] = LoadMenuBar (Panels[MAIN], "sis3320_NeutronGamma_uir.uir", MENU) ;

	 MenuBars[CONFMODULE_MENU_BAR] = LoadMenuBar (Panels[MODULE_PARA_CONF], "sis3320_NeutronGamma_uir.uir", MENUCONFMO) ;
	 MenuBars[CONFDAC_MENU_BAR] = LoadMenuBar (Panels[DAC_PARA_CONF], "sis3320_NeutronGamma_uir.uir", MENUCONFDA) ;
   	 MenuBars[CONFCLOCK_MENU_BAR] = LoadMenuBar (Panels[CLOCK_PARA_CONF], "sis3320_NeutronGamma_uir.uir", MENUCONFCK) ;
   	 MenuBars[CONFTRIG_MENU_BAR]   = LoadMenuBar (Panels[TRIG_PARA_CONF], "sis3320_NeutronGamma_uir.uir", MENUCONFTR) ;
   	 MenuBars[CONFSAMPLE_MENU_BAR] = LoadMenuBar (Panels[SAMPLE_PARA_CONF], "sis3320_NeutronGamma_uir.uir", MENUCONFSA) ;


     SetMenuBarAttribute  (MenuBars[MAIN_MENU_BAR], MENU_CONFIGURATION, ATTR_DIMMED, OFF);
     return 0 ;
   }

    // Modules running 
   if (gl_uint_system_status == SYSTEM_STATUS_MODULES_RUNNING) {
  	 SetCtrlAttribute (Panels[MAIN], PANEL_SYSTEM_LED, ATTR_ON_COLOR, VAL_BLUE);

     return 0 ;
   }

   return 0;
} // end function  ()


// Lemo Out

/* --------------------------------------------------------------------------
   CB-Funktion 
-------------------------------------------------------------------------- */
int CVICALLBACK CB_SIS3320_TriggerMode_Souce_Conf (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
  			switch (control)
			{
				case CLOCK_CONF_SIS3320_TRIGGER_MODE:
		 		  	GetCtrlVal (Panels[CLOCK_PARA_CONF],CLOCK_CONF_SIS3320_TRIGGER_MODE,&gl_uint_SIS3320_Trigger_Mode_Source_ModeConf);
					break;
			} // end switch (control)
		  break;
	}
	return 0;
} // end function  ()



   
//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 

int CVICALLBACK CB_SIS3320_ExternalConfFlags (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int check_on ;
	switch (event)
		{
		case EVENT_COMMIT:
  			switch (control)
			{
			  case CLOCK_CONF_CHECKBOX_FLAG_TRIGGER:
				GetCtrlVal (Panels[CLOCK_PARA_CONF], CLOCK_CONF_CHECKBOX_FLAG_TRIGGER,&gl_uint_SIS3320External_Lemo_Trigger_FlagConf);  
				break;
			  case CLOCK_CONF_CHECKBOX_FLAG_TIMSTAM:
				GetCtrlVal (Panels[CLOCK_PARA_CONF], CLOCK_CONF_CHECKBOX_FLAG_TIMSTAM,&gl_uint_SIS3320External_Lemo_TimestampClr_FlagConf);  
				break;

			} // end switch (control)
			break;
		}

	return 0;
}





//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
// Clock

/* --------------------------------------------------------------------------
   CB-Funktion 
-------------------------------------------------------------------------- */
int CVICALLBACK CB_ClockModeConf (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
  			switch (control)
			{
				case CLOCK_CONF_SIS3820_MODE_CLK:
		 		  	GetCtrlVal (Panels[CLOCK_PARA_CONF],CLOCK_CONF_SIS3820_MODE_CLK,&gl_uint_SIS3820ClockModeConf);
					break;
				case CLOCK_CONF_SIS3820_MODE_CLK_E2:
		 		  	GetCtrlVal (Panels[CLOCK_PARA_CONF],CLOCK_CONF_SIS3820_MODE_CLK_E2,&gl_uint_SIS3820ClockModeConf);
					break;
				case CLOCK_CONF_SIS3320_MODE_CLK:
		 		  	GetCtrlVal (Panels[CLOCK_PARA_CONF],CLOCK_CONF_SIS3320_MODE_CLK,&gl_uint_SIS3320ClockModeConf);
					break;
				case CLOCK_CONF_SIS3302_MODE_CLK:
		 		  	GetCtrlVal (Panels[CLOCK_PARA_CONF],CLOCK_CONF_SIS3302_MODE_CLK,&gl_uint_SIS3320ClockModeConf);
					break;
			} // end switch (control)
		  break;
	}
	return 0;
} // end function  ()




//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 

int CVICALLBACK CB_ClockConfFlags (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int check_on ;
	switch (event)
		{
		case EVENT_COMMIT:
  			switch (control)
			{
			  case CLOCK_CONF_CHECKBOX_FLAG_CTRL4:
				GetCtrlVal (Panels[CLOCK_PARA_CONF], CLOCK_CONF_CHECKBOX_FLAG_CTRL4,&gl_uint_SIS3820ClockCtrl4FlagConf);  
				break;
			  case CLOCK_CONF_CHECKBOX_FLAG_CTRL3:
				GetCtrlVal (Panels[CLOCK_PARA_CONF], CLOCK_CONF_CHECKBOX_FLAG_CTRL3,&gl_uint_SIS3820ClockCtrl3FlagConf);  
				break;
			  case CLOCK_CONF_CHECKBOX_FLAG_CTRL2:
				GetCtrlVal (Panels[CLOCK_PARA_CONF], CLOCK_CONF_CHECKBOX_FLAG_CTRL2,&gl_uint_SIS3820ClockCtrl2FlagConf);  
				break;


			  case CLOCK_CONF_CHECKBOX_FLAG_G_AND:
				GetCtrlVal (Panels[CLOCK_PARA_CONF], CLOCK_CONF_CHECKBOX_FLAG_G_AND,&check_on);  
				if(check_on == 0) {
					gl_uint_SIS3820ClockTriggerMaskConf = gl_uint_SIS3820ClockTriggerMaskConf & ~SET_BIT16 ;
				}
				else {
					gl_uint_SIS3820ClockTriggerMaskConf = gl_uint_SIS3820ClockTriggerMaskConf | SET_BIT16 ;
				}
				break;


			  
			  case CLOCK_CONF_CHECKBOX_FLAG_G1_1:
				GetCtrlVal (Panels[CLOCK_PARA_CONF], CLOCK_CONF_CHECKBOX_FLAG_G1_1,&check_on);  
				if(check_on == 0) {
					gl_uint_SIS3820ClockTriggerMaskConf = gl_uint_SIS3820ClockTriggerMaskConf & ~SET_BIT0 ;
				}
				else {
					gl_uint_SIS3820ClockTriggerMaskConf = gl_uint_SIS3820ClockTriggerMaskConf | SET_BIT0 ;
				}
				break;

			  case CLOCK_CONF_CHECKBOX_FLAG_G1_2:
				GetCtrlVal (Panels[CLOCK_PARA_CONF], CLOCK_CONF_CHECKBOX_FLAG_G1_2,&check_on);  
				if(check_on == 0) {
					gl_uint_SIS3820ClockTriggerMaskConf = gl_uint_SIS3820ClockTriggerMaskConf & ~SET_BIT1 ;
				}
				else {
					gl_uint_SIS3820ClockTriggerMaskConf = gl_uint_SIS3820ClockTriggerMaskConf | SET_BIT1 ;
				}
				break;
			  case CLOCK_CONF_CHECKBOX_FLAG_G1_3:
				GetCtrlVal (Panels[CLOCK_PARA_CONF], CLOCK_CONF_CHECKBOX_FLAG_G1_3,&check_on);  
				if(check_on == 0) {
					gl_uint_SIS3820ClockTriggerMaskConf = gl_uint_SIS3820ClockTriggerMaskConf & ~SET_BIT2 ;
				}
				else {
					gl_uint_SIS3820ClockTriggerMaskConf = gl_uint_SIS3820ClockTriggerMaskConf | SET_BIT2 ;
				}
				break;
			  case CLOCK_CONF_CHECKBOX_FLAG_G1_4:
				GetCtrlVal (Panels[CLOCK_PARA_CONF], CLOCK_CONF_CHECKBOX_FLAG_G1_4,&check_on);  
				if(check_on == 0) {
					gl_uint_SIS3820ClockTriggerMaskConf = gl_uint_SIS3820ClockTriggerMaskConf & ~SET_BIT3 ;
				}
				else {
					gl_uint_SIS3820ClockTriggerMaskConf = gl_uint_SIS3820ClockTriggerMaskConf | SET_BIT3 ;
				}
				break;
			  case CLOCK_CONF_CHECKBOX_FLAG_G1_5:
				GetCtrlVal (Panels[CLOCK_PARA_CONF], CLOCK_CONF_CHECKBOX_FLAG_G1_5,&check_on);  
				if(check_on == 0) {
					gl_uint_SIS3820ClockTriggerMaskConf = gl_uint_SIS3820ClockTriggerMaskConf & ~SET_BIT4 ;
				}
				else {
					gl_uint_SIS3820ClockTriggerMaskConf = gl_uint_SIS3820ClockTriggerMaskConf | SET_BIT4 ;
				}
				break;
			  case CLOCK_CONF_CHECKBOX_FLAG_G1_6:
				GetCtrlVal (Panels[CLOCK_PARA_CONF], CLOCK_CONF_CHECKBOX_FLAG_G1_6,&check_on);  
				if(check_on == 0) {
					gl_uint_SIS3820ClockTriggerMaskConf = gl_uint_SIS3820ClockTriggerMaskConf & ~SET_BIT5 ;
				}
				else {
					gl_uint_SIS3820ClockTriggerMaskConf = gl_uint_SIS3820ClockTriggerMaskConf | SET_BIT5 ;
				}
				break;
			  case CLOCK_CONF_CHECKBOX_FLAG_G1_7:
				GetCtrlVal (Panels[CLOCK_PARA_CONF], CLOCK_CONF_CHECKBOX_FLAG_G1_7,&check_on);  
				if(check_on == 0) {
					gl_uint_SIS3820ClockTriggerMaskConf = gl_uint_SIS3820ClockTriggerMaskConf & ~SET_BIT6 ;
				}
				else {
					gl_uint_SIS3820ClockTriggerMaskConf = gl_uint_SIS3820ClockTriggerMaskConf | SET_BIT6 ;
				}
				break;
			  case CLOCK_CONF_CHECKBOX_FLAG_G1_8:
				GetCtrlVal (Panels[CLOCK_PARA_CONF], CLOCK_CONF_CHECKBOX_FLAG_G1_8,&check_on);  
				if(check_on == 0) {
					gl_uint_SIS3820ClockTriggerMaskConf = gl_uint_SIS3820ClockTriggerMaskConf & ~SET_BIT7 ;
				}
				else {
					gl_uint_SIS3820ClockTriggerMaskConf = gl_uint_SIS3820ClockTriggerMaskConf | SET_BIT7 ;
				}
				break;

			  case CLOCK_CONF_CHECKBOX_FLAG_G2_1:
				GetCtrlVal (Panels[CLOCK_PARA_CONF], CLOCK_CONF_CHECKBOX_FLAG_G2_1,&check_on);  
				if(check_on == 0) {
					gl_uint_SIS3820ClockTriggerMaskConf = gl_uint_SIS3820ClockTriggerMaskConf & ~SET_BIT8 ;
				}
				else {
					gl_uint_SIS3820ClockTriggerMaskConf = gl_uint_SIS3820ClockTriggerMaskConf | SET_BIT8 ;
				}
				break;

			  case CLOCK_CONF_CHECKBOX_FLAG_G2_2:
				GetCtrlVal (Panels[CLOCK_PARA_CONF], CLOCK_CONF_CHECKBOX_FLAG_G2_2,&check_on);  
				if(check_on == 0) {
					gl_uint_SIS3820ClockTriggerMaskConf = gl_uint_SIS3820ClockTriggerMaskConf & ~SET_BIT9 ;
				}
				else {
					gl_uint_SIS3820ClockTriggerMaskConf = gl_uint_SIS3820ClockTriggerMaskConf | SET_BIT9 ;
				}
				break;
			  case CLOCK_CONF_CHECKBOX_FLAG_G2_3:
				GetCtrlVal (Panels[CLOCK_PARA_CONF], CLOCK_CONF_CHECKBOX_FLAG_G2_3,&check_on);  
				if(check_on == 0) {
					gl_uint_SIS3820ClockTriggerMaskConf = gl_uint_SIS3820ClockTriggerMaskConf & ~SET_BIT10 ;
				}
				else {
					gl_uint_SIS3820ClockTriggerMaskConf = gl_uint_SIS3820ClockTriggerMaskConf | SET_BIT10 ;
				}
				break;
			  case CLOCK_CONF_CHECKBOX_FLAG_G2_4:
				GetCtrlVal (Panels[CLOCK_PARA_CONF], CLOCK_CONF_CHECKBOX_FLAG_G2_4,&check_on);  
				if(check_on == 0) {
					gl_uint_SIS3820ClockTriggerMaskConf = gl_uint_SIS3820ClockTriggerMaskConf & ~SET_BIT11 ;
				}
				else {
					gl_uint_SIS3820ClockTriggerMaskConf = gl_uint_SIS3820ClockTriggerMaskConf | SET_BIT11 ;
				}
				break;
			  case CLOCK_CONF_CHECKBOX_FLAG_G2_5:
				GetCtrlVal (Panels[CLOCK_PARA_CONF], CLOCK_CONF_CHECKBOX_FLAG_G2_5,&check_on);  
				if(check_on == 0) {
					gl_uint_SIS3820ClockTriggerMaskConf = gl_uint_SIS3820ClockTriggerMaskConf & ~SET_BIT12 ;
				}
				else {
					gl_uint_SIS3820ClockTriggerMaskConf = gl_uint_SIS3820ClockTriggerMaskConf | SET_BIT12 ;
				}
				break;
			  case CLOCK_CONF_CHECKBOX_FLAG_G2_6:
				GetCtrlVal (Panels[CLOCK_PARA_CONF], CLOCK_CONF_CHECKBOX_FLAG_G2_6,&check_on);  
				if(check_on == 0) {
					gl_uint_SIS3820ClockTriggerMaskConf = gl_uint_SIS3820ClockTriggerMaskConf & ~SET_BIT13 ;
				}
				else {
					gl_uint_SIS3820ClockTriggerMaskConf = gl_uint_SIS3820ClockTriggerMaskConf | SET_BIT13 ;
				}
				break;
			  case CLOCK_CONF_CHECKBOX_FLAG_G2_7:
				GetCtrlVal (Panels[CLOCK_PARA_CONF], CLOCK_CONF_CHECKBOX_FLAG_G2_7,&check_on);  
				if(check_on == 0) {
					gl_uint_SIS3820ClockTriggerMaskConf = gl_uint_SIS3820ClockTriggerMaskConf & ~SET_BIT14 ;
				}
				else {
					gl_uint_SIS3820ClockTriggerMaskConf = gl_uint_SIS3820ClockTriggerMaskConf | SET_BIT14 ;
				}
				break;
			  case CLOCK_CONF_CHECKBOX_FLAG_G2_8:
				GetCtrlVal (Panels[CLOCK_PARA_CONF], CLOCK_CONF_CHECKBOX_FLAG_G2_8,&check_on);  
				if(check_on == 0) {
					gl_uint_SIS3820ClockTriggerMaskConf = gl_uint_SIS3820ClockTriggerMaskConf & ~SET_BIT15 ;
				}
				else {
					gl_uint_SIS3820ClockTriggerMaskConf = gl_uint_SIS3820ClockTriggerMaskConf | SET_BIT15 ;
				}
				break;

			} // end switch (control)
			copy_clock_CommonParameters_to_inbox() ;
			break;
		}


	return 0;
}





//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 

int copy_clock_CommonParameters_to_inbox (void)
{   
	SetCtrlAttribute (Panels[CLOCK_PARA_CONF], CLOCK_CONF_SIS3820_MODE_CLK, ATTR_CTRL_VAL, gl_uint_SIS3820ClockModeConf);

	SetCtrlAttribute (Panels[CLOCK_PARA_CONF], CLOCK_CONF_CHECKBOX_FLAG_CTRL4, ATTR_CTRL_VAL,gl_uint_SIS3820ClockCtrl4FlagConf);  
	SetCtrlAttribute (Panels[CLOCK_PARA_CONF], CLOCK_CONF_CHECKBOX_FLAG_CTRL3, ATTR_CTRL_VAL,gl_uint_SIS3820ClockCtrl3FlagConf);  
	SetCtrlAttribute (Panels[CLOCK_PARA_CONF], CLOCK_CONF_CHECKBOX_FLAG_CTRL2, ATTR_CTRL_VAL,gl_uint_SIS3820ClockCtrl2FlagConf);  

	SetCtrlAttribute (Panels[CLOCK_PARA_CONF], CLOCK_CONF_CHECKBOX_FLAG_G_AND, ATTR_CTRL_VAL,(gl_uint_SIS3820ClockTriggerMaskConf>>16) & 1 );  

	SetCtrlAttribute (Panels[CLOCK_PARA_CONF], CLOCK_CONF_CHECKBOX_FLAG_G1_1, ATTR_CTRL_VAL,(gl_uint_SIS3820ClockTriggerMaskConf>>0) & 1 );  
	SetCtrlAttribute (Panels[CLOCK_PARA_CONF], CLOCK_CONF_CHECKBOX_FLAG_G1_2, ATTR_CTRL_VAL,(gl_uint_SIS3820ClockTriggerMaskConf>>1) & 1 );  
	SetCtrlAttribute (Panels[CLOCK_PARA_CONF], CLOCK_CONF_CHECKBOX_FLAG_G1_3, ATTR_CTRL_VAL,(gl_uint_SIS3820ClockTriggerMaskConf>>2) & 1 );  
	SetCtrlAttribute (Panels[CLOCK_PARA_CONF], CLOCK_CONF_CHECKBOX_FLAG_G1_4, ATTR_CTRL_VAL,(gl_uint_SIS3820ClockTriggerMaskConf>>3) & 1 );  
	SetCtrlAttribute (Panels[CLOCK_PARA_CONF], CLOCK_CONF_CHECKBOX_FLAG_G1_5, ATTR_CTRL_VAL,(gl_uint_SIS3820ClockTriggerMaskConf>>4) & 1 );  
	SetCtrlAttribute (Panels[CLOCK_PARA_CONF], CLOCK_CONF_CHECKBOX_FLAG_G1_6, ATTR_CTRL_VAL,(gl_uint_SIS3820ClockTriggerMaskConf>>5) & 1 );  
	SetCtrlAttribute (Panels[CLOCK_PARA_CONF], CLOCK_CONF_CHECKBOX_FLAG_G1_7, ATTR_CTRL_VAL,(gl_uint_SIS3820ClockTriggerMaskConf>>6) & 1 );  
	SetCtrlAttribute (Panels[CLOCK_PARA_CONF], CLOCK_CONF_CHECKBOX_FLAG_G1_8, ATTR_CTRL_VAL,(gl_uint_SIS3820ClockTriggerMaskConf>>7) & 1 );  
	SetCtrlAttribute (Panels[CLOCK_PARA_CONF], CLOCK_CONF_CHECKBOX_FLAG_G2_1, ATTR_CTRL_VAL,(gl_uint_SIS3820ClockTriggerMaskConf>>8) & 1 );  
	SetCtrlAttribute (Panels[CLOCK_PARA_CONF], CLOCK_CONF_CHECKBOX_FLAG_G2_2, ATTR_CTRL_VAL,(gl_uint_SIS3820ClockTriggerMaskConf>>9) & 1 );  
	SetCtrlAttribute (Panels[CLOCK_PARA_CONF], CLOCK_CONF_CHECKBOX_FLAG_G2_3, ATTR_CTRL_VAL,(gl_uint_SIS3820ClockTriggerMaskConf>>10) & 1 );  
	SetCtrlAttribute (Panels[CLOCK_PARA_CONF], CLOCK_CONF_CHECKBOX_FLAG_G2_4, ATTR_CTRL_VAL,(gl_uint_SIS3820ClockTriggerMaskConf>>11) & 1 );  
	SetCtrlAttribute (Panels[CLOCK_PARA_CONF], CLOCK_CONF_CHECKBOX_FLAG_G2_5, ATTR_CTRL_VAL,(gl_uint_SIS3820ClockTriggerMaskConf>>12) & 1 );  
	SetCtrlAttribute (Panels[CLOCK_PARA_CONF], CLOCK_CONF_CHECKBOX_FLAG_G2_6, ATTR_CTRL_VAL,(gl_uint_SIS3820ClockTriggerMaskConf>>13) & 1 );  
	SetCtrlAttribute (Panels[CLOCK_PARA_CONF], CLOCK_CONF_CHECKBOX_FLAG_G2_7, ATTR_CTRL_VAL,(gl_uint_SIS3820ClockTriggerMaskConf>>14) & 1 );  
	SetCtrlAttribute (Panels[CLOCK_PARA_CONF], CLOCK_CONF_CHECKBOX_FLAG_G2_8, ATTR_CTRL_VAL,(gl_uint_SIS3820ClockTriggerMaskConf>>15) & 1 );  
   
	if ((gl_uint_SIS3820ClockTriggerMaskConf & 0x10000) == 0) { // only group 1
		  	SetCtrlAttribute (Panels[CLOCK_PARA_CONF], CLOCK_CONF_CHECKBOX_FLAG_G2_1, ATTR_DIMMED, 1);
		  	SetCtrlAttribute (Panels[CLOCK_PARA_CONF], CLOCK_CONF_CHECKBOX_FLAG_G2_2, ATTR_DIMMED, 1);
		  	SetCtrlAttribute (Panels[CLOCK_PARA_CONF], CLOCK_CONF_CHECKBOX_FLAG_G2_3, ATTR_DIMMED, 1);
		  	SetCtrlAttribute (Panels[CLOCK_PARA_CONF], CLOCK_CONF_CHECKBOX_FLAG_G2_4, ATTR_DIMMED, 1);
		  	SetCtrlAttribute (Panels[CLOCK_PARA_CONF], CLOCK_CONF_CHECKBOX_FLAG_G2_5, ATTR_DIMMED, 1);
		  	SetCtrlAttribute (Panels[CLOCK_PARA_CONF], CLOCK_CONF_CHECKBOX_FLAG_G2_6, ATTR_DIMMED, 1);
		  	SetCtrlAttribute (Panels[CLOCK_PARA_CONF], CLOCK_CONF_CHECKBOX_FLAG_G2_7, ATTR_DIMMED, 1);
		  	SetCtrlAttribute (Panels[CLOCK_PARA_CONF], CLOCK_CONF_CHECKBOX_FLAG_G2_8, ATTR_DIMMED, 1);
	}
	else {
		  	SetCtrlAttribute (Panels[CLOCK_PARA_CONF], CLOCK_CONF_CHECKBOX_FLAG_G2_1, ATTR_DIMMED, 0);
		  	SetCtrlAttribute (Panels[CLOCK_PARA_CONF], CLOCK_CONF_CHECKBOX_FLAG_G2_2, ATTR_DIMMED, 0);
		  	SetCtrlAttribute (Panels[CLOCK_PARA_CONF], CLOCK_CONF_CHECKBOX_FLAG_G2_3, ATTR_DIMMED, 0);
		  	SetCtrlAttribute (Panels[CLOCK_PARA_CONF], CLOCK_CONF_CHECKBOX_FLAG_G2_4, ATTR_DIMMED, 0);
		  	SetCtrlAttribute (Panels[CLOCK_PARA_CONF], CLOCK_CONF_CHECKBOX_FLAG_G2_5, ATTR_DIMMED, 0);
		  	SetCtrlAttribute (Panels[CLOCK_PARA_CONF], CLOCK_CONF_CHECKBOX_FLAG_G2_6, ATTR_DIMMED, 0);
		  	SetCtrlAttribute (Panels[CLOCK_PARA_CONF], CLOCK_CONF_CHECKBOX_FLAG_G2_7, ATTR_DIMMED, 0);
		  	SetCtrlAttribute (Panels[CLOCK_PARA_CONF], CLOCK_CONF_CHECKBOX_FLAG_G2_8, ATTR_DIMMED, 0);
	}
   
   
	SetCtrlAttribute (Panels[CLOCK_PARA_CONF], CLOCK_CONF_SIS3320_MODE_CLK, ATTR_CTRL_VAL, gl_uint_SIS3320ClockModeConf);

  	SetCtrlVal (Panels[CLOCK_PARA_CONF],CLOCK_CONF_SIS3320_TRIGGER_MODE, gl_uint_SIS3320_Trigger_Mode_Source_ModeConf);
  	//SetCtrlVal (Panels[CLOCK_PARA_CONF],CLOCK_CONF_SIS3320_TRIGGER_MODE, gl_uint_SIS3320_DUMMY_ModeConf);

 	SetCtrlAttribute (Panels[CLOCK_PARA_CONF], CLOCK_CONF_CHECKBOX_FLAG_TRIGGER, ATTR_CTRL_VAL,gl_uint_SIS3320External_Lemo_Trigger_FlagConf);  
 	SetCtrlAttribute (Panels[CLOCK_PARA_CONF], CLOCK_CONF_CHECKBOX_FLAG_TIMSTAM, ATTR_CTRL_VAL,gl_uint_SIS3320External_Lemo_TimestampClr_FlagConf);  
			
 

  
  return 0;
}


//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
/* --------------------------------------------------------------------------
   CB-Funktion 
-------------------------------------------------------------------------- */
int CVICALLBACK CB_SampleModeConf (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
  			switch (control)
			{

				
				case SAMPL_CONF_MAIN_GATE_LENGTH:
		 		  	GetCtrlVal (Panels[SAMPLE_PARA_CONF],SAMPL_CONF_MAIN_GATE_LENGTH,&gl_uint_MainGateLength);
					break;
				case SAMPL_CONF_MAIN_GATE_PRETRIGGER:
		 		  	GetCtrlVal (Panels[SAMPLE_PARA_CONF],SAMPL_CONF_MAIN_GATE_PRETRIGGER,&gl_uint_MainGatePreTriggerDelay);
					break;
				
	 
				case SAMPL_CONF_GATE1_LENGTH:
		 		  	GetCtrlVal (Panels[SAMPLE_PARA_CONF],SAMPL_CONF_GATE1_LENGTH,&gl_uint_Gate1_Length);
					break;
				case SAMPL_CONF_GATE1_START_INDEX:
		 		  	GetCtrlVal (Panels[SAMPLE_PARA_CONF],SAMPL_CONF_GATE1_START_INDEX,&gl_uint_Gate1_StartIndex);
					break;
	 
				case SAMPL_CONF_GATE2_LENGTH:
		 		  	GetCtrlVal (Panels[SAMPLE_PARA_CONF],SAMPL_CONF_GATE2_LENGTH,&gl_uint_Gate2_Length);
					break;
				case SAMPL_CONF_GATE2_START_INDEX:
		 		  	GetCtrlVal (Panels[SAMPLE_PARA_CONF],SAMPL_CONF_GATE2_START_INDEX,&gl_uint_Gate2_StartIndex);
					break;
	 
				case SAMPL_CONF_GATE3_LENGTH:
		 		  	GetCtrlVal (Panels[SAMPLE_PARA_CONF],SAMPL_CONF_GATE3_LENGTH,&gl_uint_Gate3_Length);
					break;
				case SAMPL_CONF_GATE3_START_INDEX:
		 		  	GetCtrlVal (Panels[SAMPLE_PARA_CONF],SAMPL_CONF_GATE3_START_INDEX,&gl_uint_Gate3_StartIndex);
					break;
	 
				case SAMPL_CONF_GATE4_LENGTH:
		 		  	GetCtrlVal (Panels[SAMPLE_PARA_CONF],SAMPL_CONF_GATE4_LENGTH,&gl_uint_Gate4_Length);
					break;
				case SAMPL_CONF_GATE4_START_INDEX:
		 		  	GetCtrlVal (Panels[SAMPLE_PARA_CONF],SAMPL_CONF_GATE4_START_INDEX,&gl_uint_Gate4_StartIndex);
					break;
	 
				case SAMPL_CONF_GATE5_LENGTH:
		 		  	GetCtrlVal (Panels[SAMPLE_PARA_CONF],SAMPL_CONF_GATE5_LENGTH,&gl_uint_Gate5_Length);
					break;
				case SAMPL_CONF_GATE5_START_INDEX:
		 		  	GetCtrlVal (Panels[SAMPLE_PARA_CONF],SAMPL_CONF_GATE5_START_INDEX,&gl_uint_Gate5_StartIndex);
					break;
	 
				case SAMPL_CONF_GATE6_LENGTH:
		 		  	GetCtrlVal (Panels[SAMPLE_PARA_CONF],SAMPL_CONF_GATE6_LENGTH,&gl_uint_Gate6_Length);
					break;
				case SAMPL_CONF_GATE6_START_INDEX:
		 		  	GetCtrlVal (Panels[SAMPLE_PARA_CONF],SAMPL_CONF_GATE6_START_INDEX,&gl_uint_Gate6_StartIndex);
					break;
	 
				case SAMPL_CONF_GATE7_LENGTH:
		 		  	GetCtrlVal (Panels[SAMPLE_PARA_CONF],SAMPL_CONF_GATE7_LENGTH,&gl_uint_Gate7_Length);
					break;
				case SAMPL_CONF_GATE7_START_INDEX:
		 		  	GetCtrlVal (Panels[SAMPLE_PARA_CONF],SAMPL_CONF_GATE7_START_INDEX,&gl_uint_Gate7_StartIndex);
					break;
	 
				case SAMPL_CONF_GATE8_LENGTH:
		 		  	GetCtrlVal (Panels[SAMPLE_PARA_CONF],SAMPL_CONF_GATE8_LENGTH,&gl_uint_Gate8_Length);
					break;
				case SAMPL_CONF_GATE8_START_INDEX:
		 		  	GetCtrlVal (Panels[SAMPLE_PARA_CONF],SAMPL_CONF_GATE8_START_INDEX,&gl_uint_Gate8_StartIndex);
					break;
	 
	 

				case SAMPL_CONF_SAMPLE_RAW_LENGTH:
		 		  	GetCtrlVal (Panels[SAMPLE_PARA_CONF],SAMPL_CONF_SAMPLE_RAW_LENGTH,&gl_uint_RawSample_Length);
					gl_uint_RawSample_Length = gl_uint_RawSample_Length & 0x7fc ;
		 		  	SetCtrlVal (Panels[SAMPLE_PARA_CONF],SAMPL_CONF_SAMPLE_RAW_LENGTH, gl_uint_RawSample_Length);
		//			setupPanelDisplayRaw() ;
					break;
				case SAMPL_CONF_SAMPLE_RAW_STARTINDEX:
		 		  	GetCtrlVal (Panels[SAMPLE_PARA_CONF],SAMPL_CONF_SAMPLE_RAW_STARTINDEX,&gl_uint_RawSample_StartIndex);
					break;

				case SAMPL_CONF_RAW_DATA_SAMPLE_MODE:  
		 		  	GetCtrlVal (Panels[SAMPLE_PARA_CONF],SAMPL_CONF_RAW_DATA_SAMPLE_MODE,&gl_uint_RawDataSampleMode);
					break;
				case SAMPL_CONF_RAW_DATA_TEST_FIR:  
		 		  	GetCtrlVal (Panels[SAMPLE_PARA_CONF],SAMPL_CONF_RAW_DATA_TEST_FIR,&gl_uint_RawDataTestMode);
					break;

		
			
			} // end switch (control)
		//	calculate_energy_trigger_windows_and_parameters() ;
		  	break;
	}
	return 0;
} // end function  ()


//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int copy_sis3320_sample_CommonParameters_to_inbox (void)
{
	
   int CviErr;
   int i ;
   int no_of_enabled_modules ;
   int error ;
   unsigned int temp_value;

	SetCtrlVal (Panels[SAMPLE_PARA_CONF],SAMPL_CONF_MAIN_GATE_LENGTH, gl_uint_MainGateLength);
	SetCtrlVal (Panels[SAMPLE_PARA_CONF],SAMPL_CONF_MAIN_GATE_PRETRIGGER, gl_uint_MainGatePreTriggerDelay);

	SetCtrlVal (Panels[SAMPLE_PARA_CONF],SAMPL_CONF_GATE1_LENGTH, gl_uint_Gate1_Length);
	SetCtrlVal (Panels[SAMPLE_PARA_CONF],SAMPL_CONF_GATE1_START_INDEX, gl_uint_Gate1_StartIndex);
	SetCtrlVal (Panels[SAMPLE_PARA_CONF],SAMPL_CONF_GATE1_LENGTH, gl_uint_Gate1_Length);
	SetCtrlVal (Panels[SAMPLE_PARA_CONF],SAMPL_CONF_GATE1_START_INDEX, gl_uint_Gate1_StartIndex);
	SetCtrlVal (Panels[SAMPLE_PARA_CONF],SAMPL_CONF_GATE2_LENGTH, gl_uint_Gate2_Length);
	SetCtrlVal (Panels[SAMPLE_PARA_CONF],SAMPL_CONF_GATE2_START_INDEX, gl_uint_Gate2_StartIndex);
	SetCtrlVal (Panels[SAMPLE_PARA_CONF],SAMPL_CONF_GATE3_LENGTH, gl_uint_Gate3_Length);
	SetCtrlVal (Panels[SAMPLE_PARA_CONF],SAMPL_CONF_GATE3_START_INDEX, gl_uint_Gate3_StartIndex);
	SetCtrlVal (Panels[SAMPLE_PARA_CONF],SAMPL_CONF_GATE4_LENGTH, gl_uint_Gate4_Length);
	SetCtrlVal (Panels[SAMPLE_PARA_CONF],SAMPL_CONF_GATE4_START_INDEX, gl_uint_Gate4_StartIndex);
	SetCtrlVal (Panels[SAMPLE_PARA_CONF],SAMPL_CONF_GATE5_LENGTH, gl_uint_Gate5_Length);
	SetCtrlVal (Panels[SAMPLE_PARA_CONF],SAMPL_CONF_GATE5_START_INDEX, gl_uint_Gate5_StartIndex);
	SetCtrlVal (Panels[SAMPLE_PARA_CONF],SAMPL_CONF_GATE6_LENGTH, gl_uint_Gate6_Length);
	SetCtrlVal (Panels[SAMPLE_PARA_CONF],SAMPL_CONF_GATE6_START_INDEX, gl_uint_Gate6_StartIndex);
	SetCtrlVal (Panels[SAMPLE_PARA_CONF],SAMPL_CONF_GATE7_LENGTH, gl_uint_Gate7_Length);
	SetCtrlVal (Panels[SAMPLE_PARA_CONF],SAMPL_CONF_GATE7_START_INDEX, gl_uint_Gate7_StartIndex);
	SetCtrlVal (Panels[SAMPLE_PARA_CONF],SAMPL_CONF_GATE8_LENGTH, gl_uint_Gate8_Length);
	SetCtrlVal (Panels[SAMPLE_PARA_CONF],SAMPL_CONF_GATE8_START_INDEX, gl_uint_Gate8_StartIndex);

	SetCtrlVal (Panels[SAMPLE_PARA_CONF],SAMPL_CONF_SAMPLE_RAW_LENGTH, gl_uint_RawSample_Length);
	//	setupPanelDisplayRaw() ;
	SetCtrlVal (Panels[SAMPLE_PARA_CONF],SAMPL_CONF_SAMPLE_RAW_STARTINDEX, gl_uint_RawSample_StartIndex);
	SetCtrlVal (Panels[SAMPLE_PARA_CONF],SAMPL_CONF_RAW_DATA_SAMPLE_MODE, gl_uint_RawDataSampleMode);
	SetCtrlVal (Panels[SAMPLE_PARA_CONF],SAMPL_CONF_RAW_DATA_TEST_FIR, gl_uint_RawDataTestMode);

   return 0;
} // end function  ()




//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
// DAC Offset					
int CVICALLBACK CB_DacOffsetConf (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int error=0;
	unsigned int data_rd;
	int CviErr;
	switch (event)
		{
		case EVENT_COMMIT:
  			switch (control)
			{
				case DAC_CONF_DAC_OFFSET_ADC1:
				    CviErr = GetCtrlVal (Panels[DAC_PARA_CONF], DAC_CONF_DAC_OFFSET_ADC1, &gl_uint_DacOffset_Inbox[0]);
					break;
				case DAC_CONF_DAC_OFFSET_ADC2:
				    CviErr = GetCtrlVal (Panels[DAC_PARA_CONF], DAC_CONF_DAC_OFFSET_ADC2, &gl_uint_DacOffset_Inbox[1]);
					break;
				case DAC_CONF_DAC_OFFSET_ADC3:
				    CviErr = GetCtrlVal (Panels[DAC_PARA_CONF], DAC_CONF_DAC_OFFSET_ADC3, &gl_uint_DacOffset_Inbox[2]);
					break;
				case DAC_CONF_DAC_OFFSET_ADC4:
				    CviErr = GetCtrlVal (Panels[DAC_PARA_CONF], DAC_CONF_DAC_OFFSET_ADC4, &gl_uint_DacOffset_Inbox[3]);
					break;
				case DAC_CONF_DAC_OFFSET_ADC5:
				    CviErr = GetCtrlVal (Panels[DAC_PARA_CONF], DAC_CONF_DAC_OFFSET_ADC5, &gl_uint_DacOffset_Inbox[4]);
					break;
				case DAC_CONF_DAC_OFFSET_ADC6:
				    CviErr = GetCtrlVal (Panels[DAC_PARA_CONF], DAC_CONF_DAC_OFFSET_ADC6, &gl_uint_DacOffset_Inbox[5]);
					break;
				case DAC_CONF_DAC_OFFSET_ADC7:
				    CviErr = GetCtrlVal (Panels[DAC_PARA_CONF], DAC_CONF_DAC_OFFSET_ADC7, &gl_uint_DacOffset_Inbox[6]);
					break;
				case DAC_CONF_DAC_OFFSET_ADC8:
				    CviErr = GetCtrlVal (Panels[DAC_PARA_CONF], DAC_CONF_DAC_OFFSET_ADC8, &gl_uint_DacOffset_Inbox[7]);
					break;

			} // end switch (control)

			break;
		}
	return 0;
}
			     
				
							
//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 

void CVICALLBACK CB_PutDacOffsetToTable (int menuBar, int menuItem, void *callbackData,
        int panel)
{
    switch (menuItem) {
        case MENUCONFDA_PUT_MODULE1 : {
            copy_DacOffset_inboxvalues_to_confvalues (INDEX_MODULE1)   ;
           }  
           break;
        case MENUCONFDA_PUT_MODULE2 : {
            copy_DacOffset_inboxvalues_to_confvalues (INDEX_MODULE2)   ;
           }  
           break;
        case MENUCONFDA_PUT_MODULE3 : {
            copy_DacOffset_inboxvalues_to_confvalues (INDEX_MODULE3)   ;
           }  
           break;
        case MENUCONFDA_PUT_MODULE4 : {
            copy_DacOffset_inboxvalues_to_confvalues (INDEX_MODULE4)   ;
           }  
           break;
        case MENUCONFDA_PUT_MODULE5 : {
            copy_DacOffset_inboxvalues_to_confvalues (INDEX_MODULE5)   ;
           }  
           break;
        case MENUCONFDA_PUT_MODULE6 : {
            copy_DacOffset_inboxvalues_to_confvalues (INDEX_MODULE6)   ;
           }  
           break;
        case MENUCONFDA_PUT_MODULE7 : {
            copy_DacOffset_inboxvalues_to_confvalues (INDEX_MODULE7)   ;
           }  
           break;
        case MENUCONFDA_PUT_MODULE8 : {
            copy_DacOffset_inboxvalues_to_confvalues (INDEX_MODULE8)   ;
           }  
           break;
        case MENUCONFDA_PUT_MODULE9 : {
            copy_DacOffset_inboxvalues_to_confvalues (INDEX_MODULE9)   ;
           }  
           break;
        case MENUCONFDA_PUT_MODULE10 : {
            copy_DacOffset_inboxvalues_to_confvalues (INDEX_MODULE10)   ;
           }  
           break;
        case MENUCONFDA_PUT_MODULE11 : {
            copy_DacOffset_inboxvalues_to_confvalues (INDEX_MODULE11)   ;
           }  
           break;
        case MENUCONFDA_PUT_MODULE12 : {
            copy_DacOffset_inboxvalues_to_confvalues (INDEX_MODULE12)   ;
           }  
           break;
        case MENUCONFDA_PUT_MODULE13 : {
            copy_DacOffset_inboxvalues_to_confvalues (INDEX_MODULE13)   ;
           }  
           break;
        case MENUCONFDA_PUT_MODULE14 : {
            copy_DacOffset_inboxvalues_to_confvalues (INDEX_MODULE14)   ;
           }  
           break;
     }  // switch

    CopyDacOffsetConfvaluesToTable () ;
//    CheckSystemStatus() ;  


return;
}



//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 

void CVICALLBACK CB_GetDacOffsetToTable (int menuBar, int menuItem, void *callbackData,
        int panel)
{
    switch (menuItem) {
        case MENUCONFDA_GET_MODULE1 : {
            copy_DacOffset_confvalues_to_input_inbox (INDEX_MODULE1)   ;
           }  
           break;
        case MENUCONFDA_GET_MODULE2 : {
            copy_DacOffset_confvalues_to_input_inbox (INDEX_MODULE2)   ;
           }  
           break;
        case MENUCONFDA_GET_MODULE3 : {
            copy_DacOffset_confvalues_to_input_inbox (INDEX_MODULE3)   ;
           }  
           break;
        case MENUCONFDA_GET_MODULE4 : {
            copy_DacOffset_confvalues_to_input_inbox (INDEX_MODULE4)   ;
           }  
           break;
        case MENUCONFDA_GET_MODULE5 : {
            copy_DacOffset_confvalues_to_input_inbox (INDEX_MODULE5)   ;
           }  
           break;
        case MENUCONFDA_GET_MODULE6 : {
            copy_DacOffset_confvalues_to_input_inbox (INDEX_MODULE6)   ;
           }  
           break;
        case MENUCONFDA_GET_MODULE7 : {
            copy_DacOffset_confvalues_to_input_inbox (INDEX_MODULE7)   ;
           }  
           break;
        case MENUCONFDA_GET_MODULE8 : {
            copy_DacOffset_confvalues_to_input_inbox (INDEX_MODULE8)   ;
           }  
           break;
        case MENUCONFDA_GET_MODULE9 : {
            copy_DacOffset_confvalues_to_input_inbox (INDEX_MODULE9)   ;
           }  
           break;
        case MENUCONFDA_GET_MODULE10 : {
            copy_DacOffset_confvalues_to_input_inbox (INDEX_MODULE10)   ;
           }  
           break;
        case MENUCONFDA_GET_MODULE11 : {
            copy_DacOffset_confvalues_to_input_inbox (INDEX_MODULE11)   ;
           }  
           break;
        case MENUCONFDA_GET_MODULE12 : {
            copy_DacOffset_confvalues_to_input_inbox (INDEX_MODULE12)   ;
           }  
           break;
        case MENUCONFDA_GET_MODULE13 : {
            copy_DacOffset_confvalues_to_input_inbox (INDEX_MODULE13)   ;
           }  
           break;
        case MENUCONFDA_GET_MODULE14 : {
            copy_DacOffset_confvalues_to_input_inbox (INDEX_MODULE14)   ;
           }  
           break;
     }  // switch




return;
}

//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int copy_DacOffset_inboxvalues_to_confvalues (unsigned int module_index)
{
   int i ;
   if (module_index >= MAX_NO_OF_MODULES) return -1 ;
  
   for (i=0; i < NO_OF_ADC_CHANNELS; i++)  {
	  gl_uint_DacOffset_Conf[module_index][i] =  gl_uint_DacOffset_Inbox[i] ;
   }
   return 0;
} // end function  ()



  


//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 

int CopyDacOffsetConfvaluesToTable (void)
{
   int i ;
   unsigned int temp ;
   int imod, iadc;


   for (imod=0;imod < MAX_NO_OF_MODULES; imod++) {  
      for (iadc=0; iadc < NO_OF_ADC_CHANNELS; iadc++) {
	     temp = gl_uint_DacOffset_Conf[imod][iadc]  ;
         SetTableCellVal (Panels[DAC_PARA_CONF], DAC_CONF_DAC_OFFSET_TABLE, MakePoint (1 + (imod), 9 - ( iadc)),temp);
	  }
   }
   return 0;
} // end function  ()


							 

 
//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
  
int copy_DacOffset_confvalues_to_input_inbox (unsigned int module_index)
{
//   int CviErr;
   int i ;
   if (module_index >= MAX_NO_OF_MODULES) return -1 ;

   for (i=0; i < NO_OF_ADC_CHANNELS; i++)  {
	  gl_uint_DacOffset_Inbox[i] =  gl_uint_DacOffset_Conf[module_index][i] ;
   }
   
   SetCtrlVal (Panels[DAC_PARA_CONF], DAC_CONF_DAC_OFFSET_ADC1,  gl_uint_DacOffset_Conf[module_index][INDEX_ADC_CHANNEL1]);  
   SetCtrlVal (Panels[DAC_PARA_CONF], DAC_CONF_DAC_OFFSET_ADC2,  gl_uint_DacOffset_Conf[module_index][INDEX_ADC_CHANNEL2]);  
   SetCtrlVal (Panels[DAC_PARA_CONF], DAC_CONF_DAC_OFFSET_ADC3,  gl_uint_DacOffset_Conf[module_index][INDEX_ADC_CHANNEL3]);  
   SetCtrlVal (Panels[DAC_PARA_CONF], DAC_CONF_DAC_OFFSET_ADC4,  gl_uint_DacOffset_Conf[module_index][INDEX_ADC_CHANNEL4]);  
   SetCtrlVal (Panels[DAC_PARA_CONF], DAC_CONF_DAC_OFFSET_ADC5,  gl_uint_DacOffset_Conf[module_index][INDEX_ADC_CHANNEL5]);  
   SetCtrlVal (Panels[DAC_PARA_CONF], DAC_CONF_DAC_OFFSET_ADC6,  gl_uint_DacOffset_Conf[module_index][INDEX_ADC_CHANNEL6]);  
   SetCtrlVal (Panels[DAC_PARA_CONF], DAC_CONF_DAC_OFFSET_ADC7,  gl_uint_DacOffset_Conf[module_index][INDEX_ADC_CHANNEL7]);  
   SetCtrlVal (Panels[DAC_PARA_CONF], DAC_CONF_DAC_OFFSET_ADC8,  gl_uint_DacOffset_Conf[module_index][INDEX_ADC_CHANNEL8]);  

   return 0;
} // end function  ()
  

//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int dacReadAdcLoopOn (void)
{
   int error;
   int i, i_adc, i_mod ;
   int max_average_loop, i_average ;
   unsigned int addr, data ;
   unsigned int adc_data[8] ;
   unsigned int adc_temp[8] ;

// 1. reset all modules and define 
	for (i=0;i<MAX_NO_OF_MODULES;i++) {
		if  (gl_uint_ModEnableConf[i] != 0) {  // enabled
			addr = gl_uint_ModAddrConf[i] + SIS3320_KEY_RESET ; 
			if ((error = sub_vme_A32D32_write(addr,0x0 )) != 0) { 
				sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_write")   ;
				gl_uint_system_status = SYSTEM_STATUS_MODULES_NOT_READY ;
				gl_uint_DacReadAdcValueLoopFlag = 0 ;
				return -1 ;
			}
		} // if enabled
	} /* for loop */


// 2. set Clock to internal 100 MHz 
	data = SIS3320_ACQ_SET_CLOCK_TO_100MHZ ;	   // 
	for (i=0;i<MAX_NO_OF_MODULES;i++) {
		if  (gl_uint_ModEnableConf[i] != 0) {  // enabled
			addr = gl_uint_ModAddrConf[i] + SIS3320_ACQUISTION_CONTROL ; 
			if ((error = sub_vme_A32D32_write(addr,data )) != 0) { 
				sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_write")   ;
				gl_uint_system_status = SYSTEM_STATUS_MODULES_NOT_READY ;
				gl_uint_DacReadAdcValueLoopFlag = 0 ;
				return -1 ;
			}

			for(i_adc=0;i_adc<8;i_adc++) {	
	   			SetTableCellAttribute (Panels[DAC_PARA_CONF], DAC_CONF_ADC_VALUE_TABLE,  MakePoint (1+i, 2+i_adc),ATTR_CELL_DIMMED, OFF);
			}   
		} // if enabled
	} /* for loop */
   


 	SetCtrlVal (Panels[DAC_PARA_CONF], DAC_CONF_LED_LOOP, ON);
	do {   


	// readout Loop
		max_average_loop = 10 ;
		for (i=0;i<MAX_NO_OF_MODULES;i++) {
			if  (gl_uint_ModEnableConf[i] != 0) {  // enabled


		// adc 1/2
				adc_temp[0] = 0 ;
				adc_temp[1] = 0 ;
				addr = gl_uint_ModAddrConf[i] + SIS3320_ACTUAL_SAMPLE_VALUE_ADC12 ; 
				for (i_average=0; i_average<max_average_loop;i_average++) {
					sub_vme_A32D32_read(addr,&data );
					adc_temp[0] = adc_temp[0] + ((data & 0xffff0000) >> 16) ;
					adc_temp[1] = adc_temp[1] +  (data & 0xffff) ;
				}
				adc_data[0] =  adc_temp[0] /  max_average_loop ;
				adc_data[1] =  adc_temp[1] /  max_average_loop ;
         		SetTableCellVal (Panels[DAC_PARA_CONF], DAC_CONF_ADC_VALUE_TABLE, MakePoint (1 + (i), 9),adc_data[0]);
         		SetTableCellVal (Panels[DAC_PARA_CONF], DAC_CONF_ADC_VALUE_TABLE, MakePoint (1 + (i), 8),adc_data[1]);

		// adc 3/4
				adc_temp[2] = 0 ;
				adc_temp[3] = 0 ;
				addr = gl_uint_ModAddrConf[i] + + SIS3320_ACTUAL_SAMPLE_VALUE_ADC34 ; 
				for (i_average=0; i_average<max_average_loop;i_average++) {
					sub_vme_A32D32_read(addr,&data );
					adc_temp[2] = adc_temp[2] + ((data & 0xffff0000) >> 16) ;
					adc_temp[3] = adc_temp[3] +  (data & 0xffff) ;
				}
				adc_data[2] =  adc_temp[2] /  max_average_loop ;
				adc_data[3] =  adc_temp[3] /  max_average_loop ;
         		SetTableCellVal (Panels[DAC_PARA_CONF], DAC_CONF_ADC_VALUE_TABLE, MakePoint (1 + (i), 7),adc_data[2]);
         		SetTableCellVal (Panels[DAC_PARA_CONF], DAC_CONF_ADC_VALUE_TABLE, MakePoint (1 + (i), 6),adc_data[3]);


		// adc 5/6
				adc_temp[4] = 0 ;
				adc_temp[5] = 0 ;
				addr = gl_uint_ModAddrConf[i] + SIS3320_ACTUAL_SAMPLE_VALUE_ADC56 ; 
				for (i_average=0; i_average<max_average_loop;i_average++) {
					sub_vme_A32D32_read(addr,&data );
					adc_temp[4] = adc_temp[4] + ((data & 0xffff0000) >> 16) ;
					adc_temp[5] = adc_temp[5] +  (data & 0xffff) ;
				}
				adc_data[4] =  adc_temp[4] /  max_average_loop ;
				adc_data[5] =  adc_temp[5] /  max_average_loop ;
         		SetTableCellVal (Panels[DAC_PARA_CONF], DAC_CONF_ADC_VALUE_TABLE, MakePoint (1 + (i), 5),adc_data[4]);
         		SetTableCellVal (Panels[DAC_PARA_CONF], DAC_CONF_ADC_VALUE_TABLE, MakePoint (1 + (i), 4),adc_data[5]);

		// adc 7/8
				adc_temp[6] = 0 ;
				adc_temp[7] = 0 ;
				addr = gl_uint_ModAddrConf[i] + SIS3320_ACTUAL_SAMPLE_VALUE_ADC78 ; 
				for (i_average=0; i_average<max_average_loop;i_average++) {
					sub_vme_A32D32_read(addr,&data );
					adc_temp[6] = adc_temp[6] + ((data & 0xffff0000) >> 16) ;
					adc_temp[7] = adc_temp[7] +  (data & 0xffff) ;
				}
				adc_data[6] =  adc_temp[6] /  max_average_loop ;
				adc_data[7] =  adc_temp[7] /  max_average_loop ;
         		SetTableCellVal (Panels[DAC_PARA_CONF], DAC_CONF_ADC_VALUE_TABLE, MakePoint (1 + (i), 3),adc_data[6]);
         		SetTableCellVal (Panels[DAC_PARA_CONF], DAC_CONF_ADC_VALUE_TABLE, MakePoint (1 + (i), 2),adc_data[7]);

				
			
			} // if enabled

		} /* for loop */
	

	// write DAC
		for (i=0;i<MAX_NO_OF_MODULES;i++) {
			if  (gl_uint_ModEnableConf[i] != 0) {  // enabled
		

				for (i_adc=0;i_adc<8;i_adc++) {
					adc_temp[i_adc]	= gl_uint_DacOffset_Conf[i][i_adc] ;
				}
				error=sis3320_write_dac_offset(gl_uint_ModAddrConf[i], adc_temp)  ;
				if (error != 0) { 
					sisVME_ErrorHandling (error, gl_uint_ModAddrConf[i], "sis3320_write_dac_offset")   ;
					gl_uint_system_status = SYSTEM_STATUS_MODULES_NOT_READY ;
					return -1 ;
				}



			} // if enabled
		} /* for loop */

   		
    	ProcessSystemEvents ();  
	} while (gl_uint_DacReadAdcValueLoopFlag != 0) ;	

 	
 	SetCtrlVal (Panels[DAC_PARA_CONF], DAC_CONF_LED_LOOP, OFF);
  
	for(i_mod=0;i_mod<MAX_NO_OF_MODULES;i_mod++) {	
		for(i_adc=0;i_adc<8;i_adc++) {	
	   		SetTableCellAttribute (Panels[DAC_PARA_CONF], DAC_CONF_ADC_VALUE_TABLE,  MakePoint (1+i_mod, 2+i_adc),ATTR_CELL_DIMMED, ON);
		}   
	}   
   
   return 0;
} // end function  ()

/********************************************************************************************************/
//
//  FIR Trigger Parameters	  Panel
// 
/********************************************************************************************************/
/********************************************************************************************************/


//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 

int CVICALLBACK CB_ADC_FirTriggerP (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
  			switch (control)
			{
				case TRIG_CONF_FIR_TRIGGER_P_1:
				    GetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_FIR_TRIGGER_P_1, &gl_uint_FirTriggerP_Inbox[0]);
					break;
				case TRIG_CONF_FIR_TRIGGER_P_2:
				    GetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_FIR_TRIGGER_P_2, &gl_uint_FirTriggerP_Inbox[1]);
					break;
				case TRIG_CONF_FIR_TRIGGER_P_3:
				    GetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_FIR_TRIGGER_P_3, &gl_uint_FirTriggerP_Inbox[2]);
					break;
				case TRIG_CONF_FIR_TRIGGER_P_4:
				    GetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_FIR_TRIGGER_P_4, &gl_uint_FirTriggerP_Inbox[3]);
					break;
				case TRIG_CONF_FIR_TRIGGER_P_5:
				    GetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_FIR_TRIGGER_P_5, &gl_uint_FirTriggerP_Inbox[4]);
					break;
				case TRIG_CONF_FIR_TRIGGER_P_6:
				    GetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_FIR_TRIGGER_P_6, &gl_uint_FirTriggerP_Inbox[5]);
					break;
				case TRIG_CONF_FIR_TRIGGER_P_7:
				    GetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_FIR_TRIGGER_P_7, &gl_uint_FirTriggerP_Inbox[6]);
					break;
				case TRIG_CONF_FIR_TRIGGER_P_8:
				    GetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_FIR_TRIGGER_P_8, &gl_uint_FirTriggerP_Inbox[7]);
					break;
			} // end switch (control)

			calculateFirTriggerAdcCounts ()  ; 

			break;
		}
	return 0;
}

//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 

int CVICALLBACK CB_ADC_FirTriggerG (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
  			switch (control)
			{
				case TRIG_CONF_FIR_TRIGGER_G_1:
				    GetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_FIR_TRIGGER_G_1, &gl_uint_FirTriggerG_Inbox[0]);
					break;
				case TRIG_CONF_FIR_TRIGGER_G_2:
				    GetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_FIR_TRIGGER_G_2, &gl_uint_FirTriggerG_Inbox[1]);
					break;
				case TRIG_CONF_FIR_TRIGGER_G_3:
				    GetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_FIR_TRIGGER_G_3, &gl_uint_FirTriggerG_Inbox[2]);
					break;
				case TRIG_CONF_FIR_TRIGGER_G_4:
				    GetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_FIR_TRIGGER_G_4, &gl_uint_FirTriggerG_Inbox[3]);
					break;
				case TRIG_CONF_FIR_TRIGGER_G_5:
				    GetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_FIR_TRIGGER_G_5, &gl_uint_FirTriggerG_Inbox[4]);
					break;
				case TRIG_CONF_FIR_TRIGGER_G_6:
				    GetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_FIR_TRIGGER_G_6, &gl_uint_FirTriggerG_Inbox[5]);
					break;
				case TRIG_CONF_FIR_TRIGGER_G_7:
				    GetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_FIR_TRIGGER_G_7, &gl_uint_FirTriggerG_Inbox[6]);
					break;
				case TRIG_CONF_FIR_TRIGGER_G_8:
				    GetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_FIR_TRIGGER_G_8, &gl_uint_FirTriggerG_Inbox[7]);
					break;
			} // end switch (control)


			break;
		}
	return 0;
}



//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 

int CVICALLBACK CB_ADC_FirTriggerThreshold (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
  			switch (control)
			{
				case TRIG_CONF_FIR_TRIGGER_THRES_1:
				    GetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_FIR_TRIGGER_THRES_1, &gl_int_FirTriggerThresholdValue_Inbox[0]);
					break;
				case TRIG_CONF_FIR_TRIGGER_THRES_2:
				    GetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_FIR_TRIGGER_THRES_2, &gl_int_FirTriggerThresholdValue_Inbox[1]);
					break;
				case TRIG_CONF_FIR_TRIGGER_THRES_3:
				    GetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_FIR_TRIGGER_THRES_3, &gl_int_FirTriggerThresholdValue_Inbox[2]);
					break;
				case TRIG_CONF_FIR_TRIGGER_THRES_4:
				    GetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_FIR_TRIGGER_THRES_4, &gl_int_FirTriggerThresholdValue_Inbox[3]);
					break;
				case TRIG_CONF_FIR_TRIGGER_THRES_5:
				    GetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_FIR_TRIGGER_THRES_5, &gl_int_FirTriggerThresholdValue_Inbox[4]);
					break;
				case TRIG_CONF_FIR_TRIGGER_THRES_6:
				    GetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_FIR_TRIGGER_THRES_6, &gl_int_FirTriggerThresholdValue_Inbox[5]);
					break;
				case TRIG_CONF_FIR_TRIGGER_THRES_7:
				    GetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_FIR_TRIGGER_THRES_7, &gl_int_FirTriggerThresholdValue_Inbox[6]);
					break;
				case TRIG_CONF_FIR_TRIGGER_THRES_8:
				    GetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_FIR_TRIGGER_THRES_8, &gl_int_FirTriggerThresholdValue_Inbox[7]);
					break;
			} // end switch (control)


			calculateFirTriggerAdcCounts ()  ; 

		

			break;
		}
	return 0;
}

//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 

int calculateFirTriggerAdcCounts (void)
{   
    unsigned int shift_factor[8];
	int temp;
    unsigned int i;
//	float  eventRate,  eventRateAverage, fileMByteSize ;

   // SIS3320  12-bit ADC	
   if (gl_uint_SIS3302_FlagConf[0] == 0)   { 

		if(gl_uint_FirTriggerP_Inbox[0] != 0) {
			temp = (gl_int_FirTriggerThresholdValue_Inbox[0] / ((int) gl_uint_FirTriggerP_Inbox[0])) ;
		}
		else {
			temp = 0 ;
		}
	    SetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_ADC_COUNTS_1, temp);

		if(gl_uint_FirTriggerP_Inbox[1] != 0) {
			temp = (gl_int_FirTriggerThresholdValue_Inbox[1] / ((int) gl_uint_FirTriggerP_Inbox[1])) ;
		}
		else {
			temp = 0 ;
		}
	    SetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_ADC_COUNTS_2, temp);
		
		if(gl_uint_FirTriggerP_Inbox[2] != 0) {
			temp = (gl_int_FirTriggerThresholdValue_Inbox[2] / ((int) gl_uint_FirTriggerP_Inbox[2])) ;
		}
		else {
			temp = 0 ;
		}
	    SetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_ADC_COUNTS_3, temp);

		if(gl_uint_FirTriggerP_Inbox[3] != 0) {
			temp = (gl_int_FirTriggerThresholdValue_Inbox[3] / ((int) gl_uint_FirTriggerP_Inbox[3])) ;
		}
		else {
			temp = 0 ;
		}
	    SetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_ADC_COUNTS_4, temp);



		if(gl_uint_FirTriggerP_Inbox[4] != 0) {
			temp = (gl_int_FirTriggerThresholdValue_Inbox[4] / ((int) gl_uint_FirTriggerP_Inbox[4])) ;
		}
		else {
			temp = 0 ;
		}
	    SetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_ADC_COUNTS_5, temp);

		if(gl_uint_FirTriggerP_Inbox[5] != 0) {
			temp = (gl_int_FirTriggerThresholdValue_Inbox[5] / ((int) gl_uint_FirTriggerP_Inbox[5])) ;
		}
		else {
			temp = 0 ;
		}
	    SetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_ADC_COUNTS_6, temp);

		if(gl_uint_FirTriggerP_Inbox[6] != 0) {
			temp = (gl_int_FirTriggerThresholdValue_Inbox[6] / ((int) gl_uint_FirTriggerP_Inbox[6])) ;
		}
		else {
			temp = 0 ;
		}
	    SetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_ADC_COUNTS_7, temp);

		if(gl_uint_FirTriggerP_Inbox[7] != 0) {
			temp = (gl_int_FirTriggerThresholdValue_Inbox[7] / ((int) gl_uint_FirTriggerP_Inbox[7])) ;
		}
		else {
			temp = 0 ;
		}
	    SetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_ADC_COUNTS_8, temp);
	    //SetCtrlAttribute (Panels[TRIG_PARA_CONF], TRIG_CONF_ADC_COUNTS_8, ATTR_FRAME_COLOR, VAL_RED);

   }
   else {  // SIS3302  16-bit ADC	 
		for (i=0;i<8;i++){
		    if (gl_uint_FirTriggerP_Inbox[i] <= 16 ) {
				shift_factor[i] = 16 ;		   // P = 1 to 16
			}
		    else {
			    if (gl_uint_FirTriggerP_Inbox[i] <= 32 ) {
					shift_factor[i] = 32 ;	   // P = 17 to 32
				}
		    	else {
					shift_factor[i] = 64 ;	   // P = 33 to 64
		    	}
		    }
		}

		if(gl_uint_FirTriggerP_Inbox[0] != 0) {
			temp = ( (shift_factor[0] * gl_int_FirTriggerThresholdValue_Inbox[0]) / ((int) gl_uint_FirTriggerP_Inbox[0])) ;
			 // * 16 because is shifted by in FPGA
		}
		else {
			temp = 0 ;
		}
	    SetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_ADC_COUNTS_1, temp);

		if(gl_uint_FirTriggerP_Inbox[1] != 0) {
			temp = ( (shift_factor[1] * gl_int_FirTriggerThresholdValue_Inbox[1]) / ((int) gl_uint_FirTriggerP_Inbox[1])) ;
			 // * 16 because is shifted by in FPGA
		}
		else {
			temp = 0 ;
		}
	    SetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_ADC_COUNTS_2, temp);
		
		if(gl_uint_FirTriggerP_Inbox[2] != 0) {
			temp = ( (shift_factor[2] * gl_int_FirTriggerThresholdValue_Inbox[2]) / ((int) gl_uint_FirTriggerP_Inbox[2])) ;
			 // * 16 because is shifted by in FPGA
		}
		else {
			temp = 0 ;
		}
	    SetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_ADC_COUNTS_3, temp);

		if(gl_uint_FirTriggerP_Inbox[3] != 0) {
			temp = ( (shift_factor[3] * gl_int_FirTriggerThresholdValue_Inbox[3]) / ((int) gl_uint_FirTriggerP_Inbox[3])) ;
			 // * 16 because is shifted by in FPGA
		}
		else {
			temp = 0 ;
		}
	    SetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_ADC_COUNTS_4, temp);



		if(gl_uint_FirTriggerP_Inbox[4] != 0) {
			temp = ( (shift_factor[4] * gl_int_FirTriggerThresholdValue_Inbox[4]) / ((int) gl_uint_FirTriggerP_Inbox[4])) ;
			 // * 16 because is shifted by in FPGA
		}
		else {
			temp = 0 ;
		}
	    SetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_ADC_COUNTS_5, temp);

		if(gl_uint_FirTriggerP_Inbox[5] != 0) {
			temp = ( (shift_factor[5] * gl_int_FirTriggerThresholdValue_Inbox[5]) / ((int) gl_uint_FirTriggerP_Inbox[5])) ;
			 // * 16 because is shifted by in FPGA
		}
		else {
			temp = 0 ;
		}
	    SetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_ADC_COUNTS_6, temp);

		if(gl_uint_FirTriggerP_Inbox[6] != 0) {
			temp = ( (shift_factor[6] * gl_int_FirTriggerThresholdValue_Inbox[6]) / ((int) gl_uint_FirTriggerP_Inbox[6])) ;
			 // * 16 because is shifted by in FPGA
		}
		else {
			temp = 0 ;
		}
	    SetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_ADC_COUNTS_7, temp);

		if(gl_uint_FirTriggerP_Inbox[7] != 0) {
			temp = ( (shift_factor[7] * gl_int_FirTriggerThresholdValue_Inbox[7]) / ((int) gl_uint_FirTriggerP_Inbox[7])) ;
			temp = temp * 16 ; // because is shifted by in FPGA
		}
		else {
			temp = 0 ;
		}
	    SetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_ADC_COUNTS_8, temp);
   }
   
 


  return 0;
}




//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 

int CVICALLBACK CB_TriggerCondition (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
  			switch (control)
			{
				case TRIG_CONF_RING_MODE_TRIGGER_1:
				    GetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_RING_MODE_TRIGGER_1, &gl_uint_FirTriggerThreshold_GtLtFlag_Inbox[0]);
					break;
				case TRIG_CONF_RING_MODE_TRIGGER_2:
				    GetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_RING_MODE_TRIGGER_2, &gl_uint_FirTriggerThreshold_GtLtFlag_Inbox[1]);
					break;
				case TRIG_CONF_RING_MODE_TRIGGER_3:
				    GetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_RING_MODE_TRIGGER_3, &gl_uint_FirTriggerThreshold_GtLtFlag_Inbox[2]);
					break;
				case TRIG_CONF_RING_MODE_TRIGGER_4:
				    GetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_RING_MODE_TRIGGER_4, &gl_uint_FirTriggerThreshold_GtLtFlag_Inbox[3]);
					break;
				case TRIG_CONF_RING_MODE_TRIGGER_5:
				    GetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_RING_MODE_TRIGGER_5, &gl_uint_FirTriggerThreshold_GtLtFlag_Inbox[4]);
					break;
				case TRIG_CONF_RING_MODE_TRIGGER_6:
				    GetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_RING_MODE_TRIGGER_6, &gl_uint_FirTriggerThreshold_GtLtFlag_Inbox[5]);
					break;
				case TRIG_CONF_RING_MODE_TRIGGER_7:
				    GetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_RING_MODE_TRIGGER_7, &gl_uint_FirTriggerThreshold_GtLtFlag_Inbox[6]);
					break;
				case TRIG_CONF_RING_MODE_TRIGGER_8:
				    GetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_RING_MODE_TRIGGER_8, &gl_uint_FirTriggerThreshold_GtLtFlag_Inbox[7]);
					break;
			} // end switch (control)
		  break;
	}
	return 0;
} // end function  ()






	   
//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 

int CVICALLBACK CB_ADC_FirTriggerPulsLength (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
  			switch (control)
			{
				case TRIG_CONF_FIR_TRIGGER_PLENGTH_1:
				    GetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_FIR_TRIGGER_PLENGTH_1, &gl_uint_FirTriggerPulseLength_Inbox[0]);
					break;
				case TRIG_CONF_FIR_TRIGGER_PLENGTH_2:
				    GetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_FIR_TRIGGER_PLENGTH_2, &gl_uint_FirTriggerPulseLength_Inbox[1]);
					break;
				case TRIG_CONF_FIR_TRIGGER_PLENGTH_3:
				    GetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_FIR_TRIGGER_PLENGTH_3, &gl_uint_FirTriggerPulseLength_Inbox[2]);
					break;
				case TRIG_CONF_FIR_TRIGGER_PLENGTH_4:
				    GetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_FIR_TRIGGER_PLENGTH_4, &gl_uint_FirTriggerPulseLength_Inbox[3]);
					break;
				case TRIG_CONF_FIR_TRIGGER_PLENGTH_5:
				    GetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_FIR_TRIGGER_PLENGTH_5, &gl_uint_FirTriggerPulseLength_Inbox[4]);
					break;
				case TRIG_CONF_FIR_TRIGGER_PLENGTH_6:
				    GetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_FIR_TRIGGER_PLENGTH_6, &gl_uint_FirTriggerPulseLength_Inbox[5]);
					break;
				case TRIG_CONF_FIR_TRIGGER_PLENGTH_7:
				    GetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_FIR_TRIGGER_PLENGTH_7, &gl_uint_FirTriggerPulseLength_Inbox[6]);
					break;
				case TRIG_CONF_FIR_TRIGGER_PLENGTH_8:
				    GetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_FIR_TRIGGER_PLENGTH_8, &gl_uint_FirTriggerPulseLength_Inbox[7]);
					break;
			} // end switch (control)


			break;
		}
	return 0;
}












//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 

void CVICALLBACK CB_PutTrigValueToTable (int menuBar, int menuItem, void *callbackData,
        int panel)
{
    switch (menuItem) {
        case MENUCONFTR_PUT_MODULE1 : {
            copy_trigger_inboxvalues_to_confvalues (INDEX_MODULE1)   ;
           }  
           break;
        case MENUCONFTR_PUT_MODULE2 : {
            copy_trigger_inboxvalues_to_confvalues (INDEX_MODULE2)   ;
           }  
           break;
        case MENUCONFTR_PUT_MODULE3 : {
            copy_trigger_inboxvalues_to_confvalues (INDEX_MODULE3)   ;
           }  
           break;
        case MENUCONFTR_PUT_MODULE4 : {
            copy_trigger_inboxvalues_to_confvalues (INDEX_MODULE4)   ;
           }  
           break;
        case MENUCONFTR_PUT_MODULE5 : {
            copy_trigger_inboxvalues_to_confvalues (INDEX_MODULE5)   ;
           }  
           break;
        case MENUCONFTR_PUT_MODULE6 : {
            copy_trigger_inboxvalues_to_confvalues (INDEX_MODULE6)   ;
           }  
           break;
        case MENUCONFTR_PUT_MODULE7 : {
            copy_trigger_inboxvalues_to_confvalues (INDEX_MODULE7)   ;
           }  
           break;
        case MENUCONFTR_PUT_MODULE8 : {
            copy_trigger_inboxvalues_to_confvalues (INDEX_MODULE8)   ;
           }  
           break;
        case MENUCONFTR_PUT_MODULE9 : {
            copy_trigger_inboxvalues_to_confvalues (INDEX_MODULE9)   ;
           }  
           break;
        case MENUCONFTR_PUT_MODULE10 : {
            copy_trigger_inboxvalues_to_confvalues (INDEX_MODULE10)   ;
           }  
           break;
        case MENUCONFTR_PUT_MODULE11 : {
            copy_trigger_inboxvalues_to_confvalues (INDEX_MODULE11)   ;
           }  
           break;
        case MENUCONFTR_PUT_MODULE12 : {
            copy_trigger_inboxvalues_to_confvalues (INDEX_MODULE12)   ;
           }  
           break;
        case MENUCONFTR_PUT_MODULE13 : {
            copy_trigger_inboxvalues_to_confvalues (INDEX_MODULE13)   ;
           }  
           break;
        case MENUCONFTR_PUT_MODULE14 : {
            copy_trigger_inboxvalues_to_confvalues (INDEX_MODULE14)   ;
           }  
           break;
     }  // switch

	CopyTriggerConfvaluesToTable () ;
//    CheckSystemStatus() ;  

return;
}



//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 

/* functions for Trigger Confirmation */

int copy_trigger_inboxvalues_to_confvalues (unsigned int module_index)
{
   int i ;

   if (module_index >= MAX_NO_OF_MODULES) return -1 ;
  
   for (i=0; i < NO_OF_ADC_CHANNELS; i++)  {

	  gl_uint_FirTriggerP_Conf[module_index][i] =  gl_uint_FirTriggerP_Inbox[i] ;
	  gl_uint_FirTriggerG_Conf[module_index][i] =  gl_uint_FirTriggerG_Inbox[i] ;
	  
	  gl_uint_FirTriggerThreshold_GtLtFlag_Conf[module_index][i] =  gl_uint_FirTriggerThreshold_GtLtFlag_Inbox[i] ;
	  gl_int_FirTriggerThresholdValue_Conf[module_index][i]      =  gl_int_FirTriggerThresholdValue_Inbox[i] ;
	  gl_uint_FirTriggerPulseLength_Conf[module_index][i]        =  gl_uint_FirTriggerPulseLength_Inbox[i] ;
   }
   return 0;
} // end function  ()



//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
void CVICALLBACK CB_GetTrigValueToTable (int menuBar, int menuItem, void *callbackData,
        int panel)
{
    switch (menuItem) {
        case MENUCONFTR_GET_MODULE1 : {
            copy_trigger_confvalues_to_input_inbox (INDEX_MODULE1)   ;
           }  
           break;
        case MENUCONFTR_GET_MODULE2 : {
            copy_trigger_confvalues_to_input_inbox (INDEX_MODULE2)   ;
           }  
           break;
        case MENUCONFTR_GET_MODULE3 : {
            copy_trigger_confvalues_to_input_inbox (INDEX_MODULE3)   ;
           }  
           break;
        case MENUCONFTR_GET_MODULE4 : {
            copy_trigger_confvalues_to_input_inbox (INDEX_MODULE4)   ;
           }  
           break;
        case MENUCONFTR_GET_MODULE5 : {
            copy_trigger_confvalues_to_input_inbox (INDEX_MODULE5)   ;
           }  
           break;
        case MENUCONFTR_GET_MODULE6 : {
            copy_trigger_confvalues_to_input_inbox (INDEX_MODULE6)   ;
           }  
           break;
        case MENUCONFTR_GET_MODULE7 : {
            copy_trigger_confvalues_to_input_inbox (INDEX_MODULE7)   ;
           }  
           break;
        case MENUCONFTR_GET_MODULE8 : {
            copy_trigger_confvalues_to_input_inbox (INDEX_MODULE8)   ;
           }  
           break;
        case MENUCONFTR_GET_MODULE9 : {
            copy_trigger_confvalues_to_input_inbox (INDEX_MODULE9)   ;
           }  
           break;
        case MENUCONFTR_GET_MODULE10 : {
            copy_trigger_confvalues_to_input_inbox (INDEX_MODULE10)   ;
           }  
           break;
        case MENUCONFTR_GET_MODULE11 : {
            copy_trigger_confvalues_to_input_inbox (INDEX_MODULE11)   ;
           }  
           break;
        case MENUCONFTR_GET_MODULE12 : {
            copy_trigger_confvalues_to_input_inbox (INDEX_MODULE12)   ;
           }  
           break;
        case MENUCONFTR_GET_MODULE13 : {
            copy_trigger_confvalues_to_input_inbox (INDEX_MODULE13)   ;
           }  
           break;
        case MENUCONFTR_GET_MODULE14 : {
            copy_trigger_confvalues_to_input_inbox (INDEX_MODULE14)   ;
           }  
           break;
     }  // switch




return;
}

 
//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
	  
int CopyTriggerConfvaluesToTable (void)
{
   int i ;
   unsigned int temp ;
   int imod, iadc;

	
   for (imod=0;imod < MAX_NO_OF_MODULES; imod++) {  
      for (iadc=0; iadc < NO_OF_ADC_CHANNELS; iadc++) {
	     temp = gl_uint_FirTriggerP_Conf[imod][iadc]  ;
         SetTableCellAttribute (Panels[TRIG_PARA_CONF], TRIG_CONF_TRIG_TABLE_PG, MakePoint (1 + (2*imod), 10 - ( iadc)),ATTR_CTRL_VAL,temp);
	     temp = gl_uint_FirTriggerG_Conf[imod][iadc]  ;
         SetTableCellAttribute (Panels[TRIG_PARA_CONF], TRIG_CONF_TRIG_TABLE_PG, MakePoint (2 + (2*imod), 10 - ( iadc)),ATTR_CTRL_VAL,temp);

	     
	     temp = gl_int_FirTriggerThresholdValue_Conf[imod][iadc]  ;
         SetTableCellAttribute (Panels[TRIG_PARA_CONF], TRIG_CONF_TRIG_TABLE, MakePoint (2 + (2*imod), 9 - ( iadc)),ATTR_CTRL_VAL,temp);

	     temp = gl_uint_FirTriggerThreshold_GtLtFlag_Conf[imod][iadc]  ;
		 if (temp == FIR_TRIGGER_THRESHOLD_CONF_DISABLE)
            SetTableCellAttribute (Panels[TRIG_PARA_CONF], TRIG_CONF_TRIG_TABLE, MakePoint (1 + (2*imod), 9 - ( iadc)),ATTR_CTRL_VAL,"disable");
		 if (temp == FIR_TRIGGER_THRESHOLD_CONF_GT_OUT_ENABLE)
            SetTableCellAttribute (Panels[TRIG_PARA_CONF], TRIG_CONF_TRIG_TABLE, MakePoint (1 + (2*imod), 9 - ( iadc)),ATTR_CTRL_VAL,"GT");
		 if (temp == FIR_TRIGGER_THRESHOLD_CONF_GT_OUT_DISABLE)
            SetTableCellAttribute (Panels[TRIG_PARA_CONF], TRIG_CONF_TRIG_TABLE, MakePoint (1 + (2*imod), 9 - ( iadc)),ATTR_CTRL_VAL,"GT");
		 if (temp == FIR_TRIGGER_THRESHOLD_CONF_GT_ZERO_OUT_ENABLE)
            SetTableCellAttribute (Panels[TRIG_PARA_CONF], TRIG_CONF_TRIG_TABLE, MakePoint (1 + (2*imod), 9 - ( iadc)),ATTR_CTRL_VAL,"GT/ZERO");
		 if (temp == FIR_TRIGGER_THRESHOLD_CONF_GT_ZERO_OUT_DISABLE)
            SetTableCellAttribute (Panels[TRIG_PARA_CONF], TRIG_CONF_TRIG_TABLE, MakePoint (1 + (2*imod), 9 - ( iadc)),ATTR_CTRL_VAL,"GT/ZERO");




  		 if (temp == FIR_TRIGGER_THRESHOLD_CONF_GT_OUT_ENABLE)  {
            SetTableCellAttribute (Panels[TRIG_PARA_CONF], TRIG_CONF_TRIG_OUT, MakePoint (1 + (imod), 9 - ( iadc)),ATTR_CTRL_VAL,"enable");
 	     	SetTableCellAttribute (Panels[TRIG_PARA_CONF], TRIG_CONF_TRIG_OUT, MakePoint(1+(imod),9-(iadc)),ATTR_TEXT_COLOR,VAL_BLACK);
		 }
		  else  {
            SetTableCellAttribute (Panels[TRIG_PARA_CONF], TRIG_CONF_TRIG_OUT, MakePoint (1 + (imod), 9 - ( iadc)),ATTR_CTRL_VAL,"disable");
	     	SetTableCellAttribute (Panels[TRIG_PARA_CONF], TRIG_CONF_TRIG_OUT, MakePoint(1+(imod),9-(iadc)),ATTR_TEXT_COLOR,VAL_RED);
		 }

	     temp = gl_uint_FirTriggerPulseLength_Conf[imod][iadc]  ;
         SetTableCellAttribute (Panels[TRIG_PARA_CONF], TRIG_CONF_TRIG_TABLE_PLENGTH, MakePoint (1 + (imod), 9 - ( iadc)),ATTR_CTRL_VAL,temp);

	  }
   }


   if (gl_uint_system_status == SYSTEM_STATUS_MODULES_NOT_READY)   return 0; 
   gl_uint_system_status =  SYSTEM_STATUS_MODULES_READY ;      

   return 0;
} // end function  ()


  
  


//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int copy_trigger_confvalues_to_input_inbox (unsigned int module_index)
{
//   int CviErr;
   int i ;

   if (module_index >= MAX_NO_OF_MODULES) return -1 ;

  
   for (i=0; i < NO_OF_ADC_CHANNELS; i++)  {
	  gl_uint_FirTriggerP_Inbox[i]  =  gl_uint_FirTriggerP_Conf[module_index][i] ;
	  gl_uint_FirTriggerG_Inbox[i]  =  gl_uint_FirTriggerG_Conf[module_index][i] ;

	  gl_uint_FirTriggerThreshold_GtLtFlag_Inbox[i]  =  gl_uint_FirTriggerThreshold_GtLtFlag_Conf[module_index][i] ;
	  gl_int_FirTriggerThresholdValue_Inbox[i]       =  gl_int_FirTriggerThresholdValue_Conf[module_index][i] ;
	  gl_uint_FirTriggerPulseLength_Inbox[i]         =  gl_uint_FirTriggerPulseLength_Conf[module_index][i] ;
   }
  

   		 
   
// Peaking Time   
   SetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_FIR_TRIGGER_P_1, gl_uint_FirTriggerP_Conf[module_index][INDEX_ADC_CHANNEL1]);
   SetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_FIR_TRIGGER_P_2, gl_uint_FirTriggerP_Conf[module_index][INDEX_ADC_CHANNEL2]);
   SetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_FIR_TRIGGER_P_3, gl_uint_FirTriggerP_Conf[module_index][INDEX_ADC_CHANNEL3]);
   SetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_FIR_TRIGGER_P_4, gl_uint_FirTriggerP_Conf[module_index][INDEX_ADC_CHANNEL4]);
   SetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_FIR_TRIGGER_P_5, gl_uint_FirTriggerP_Conf[module_index][INDEX_ADC_CHANNEL5]);
   SetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_FIR_TRIGGER_P_6, gl_uint_FirTriggerP_Conf[module_index][INDEX_ADC_CHANNEL6]);
   SetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_FIR_TRIGGER_P_7, gl_uint_FirTriggerP_Conf[module_index][INDEX_ADC_CHANNEL7]);
   SetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_FIR_TRIGGER_P_8, gl_uint_FirTriggerP_Conf[module_index][INDEX_ADC_CHANNEL8]);


// Gap (P+G)   
   SetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_FIR_TRIGGER_G_1, gl_uint_FirTriggerG_Conf[module_index][INDEX_ADC_CHANNEL1]);
   SetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_FIR_TRIGGER_G_2, gl_uint_FirTriggerG_Conf[module_index][INDEX_ADC_CHANNEL2]);
   SetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_FIR_TRIGGER_G_3, gl_uint_FirTriggerG_Conf[module_index][INDEX_ADC_CHANNEL3]);
   SetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_FIR_TRIGGER_G_4, gl_uint_FirTriggerG_Conf[module_index][INDEX_ADC_CHANNEL4]);
   SetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_FIR_TRIGGER_G_5, gl_uint_FirTriggerG_Conf[module_index][INDEX_ADC_CHANNEL5]);
   SetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_FIR_TRIGGER_G_6, gl_uint_FirTriggerG_Conf[module_index][INDEX_ADC_CHANNEL6]);
   SetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_FIR_TRIGGER_G_7, gl_uint_FirTriggerG_Conf[module_index][INDEX_ADC_CHANNEL7]);
   SetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_FIR_TRIGGER_G_8, gl_uint_FirTriggerG_Conf[module_index][INDEX_ADC_CHANNEL8]);

  
// Threshold and Condition   
   SetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_RING_MODE_TRIGGER_1, gl_uint_FirTriggerThreshold_GtLtFlag_Conf[module_index][INDEX_ADC_CHANNEL1]);
   SetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_FIR_TRIGGER_THRES_1,  gl_int_FirTriggerThresholdValue_Conf[module_index][INDEX_ADC_CHANNEL1]);  

   SetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_RING_MODE_TRIGGER_2, gl_uint_FirTriggerThreshold_GtLtFlag_Conf[module_index][INDEX_ADC_CHANNEL2]);
   SetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_FIR_TRIGGER_THRES_2,  gl_int_FirTriggerThresholdValue_Conf[module_index][INDEX_ADC_CHANNEL2]);  

   SetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_RING_MODE_TRIGGER_3, gl_uint_FirTriggerThreshold_GtLtFlag_Conf[module_index][INDEX_ADC_CHANNEL3]);
   SetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_FIR_TRIGGER_THRES_3,  gl_int_FirTriggerThresholdValue_Conf[module_index][INDEX_ADC_CHANNEL3]);  

   SetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_RING_MODE_TRIGGER_4, gl_uint_FirTriggerThreshold_GtLtFlag_Conf[module_index][INDEX_ADC_CHANNEL4]);
   SetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_FIR_TRIGGER_THRES_4,  gl_int_FirTriggerThresholdValue_Conf[module_index][INDEX_ADC_CHANNEL4]);  

   SetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_RING_MODE_TRIGGER_5, gl_uint_FirTriggerThreshold_GtLtFlag_Conf[module_index][INDEX_ADC_CHANNEL5]);
   SetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_FIR_TRIGGER_THRES_5,  gl_int_FirTriggerThresholdValue_Conf[module_index][INDEX_ADC_CHANNEL5]);  

   SetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_RING_MODE_TRIGGER_6, gl_uint_FirTriggerThreshold_GtLtFlag_Conf[module_index][INDEX_ADC_CHANNEL6]);
   SetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_FIR_TRIGGER_THRES_6,  gl_int_FirTriggerThresholdValue_Conf[module_index][INDEX_ADC_CHANNEL6]);  

   SetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_RING_MODE_TRIGGER_7, gl_uint_FirTriggerThreshold_GtLtFlag_Conf[module_index][INDEX_ADC_CHANNEL7]);
   SetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_FIR_TRIGGER_THRES_7,  gl_int_FirTriggerThresholdValue_Conf[module_index][INDEX_ADC_CHANNEL7]);  

   SetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_RING_MODE_TRIGGER_8, gl_uint_FirTriggerThreshold_GtLtFlag_Conf[module_index][INDEX_ADC_CHANNEL8]);
   SetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_FIR_TRIGGER_THRES_8,  gl_int_FirTriggerThresholdValue_Conf[module_index][INDEX_ADC_CHANNEL8]);  


// Pulse Length   
   SetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_FIR_TRIGGER_PLENGTH_1, gl_uint_FirTriggerPulseLength_Conf[module_index][INDEX_ADC_CHANNEL1]);
   SetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_FIR_TRIGGER_PLENGTH_2, gl_uint_FirTriggerPulseLength_Conf[module_index][INDEX_ADC_CHANNEL2]);
   SetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_FIR_TRIGGER_PLENGTH_3, gl_uint_FirTriggerPulseLength_Conf[module_index][INDEX_ADC_CHANNEL3]);
   SetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_FIR_TRIGGER_PLENGTH_4, gl_uint_FirTriggerPulseLength_Conf[module_index][INDEX_ADC_CHANNEL4]);
   SetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_FIR_TRIGGER_PLENGTH_5, gl_uint_FirTriggerPulseLength_Conf[module_index][INDEX_ADC_CHANNEL5]);
   SetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_FIR_TRIGGER_PLENGTH_6, gl_uint_FirTriggerPulseLength_Conf[module_index][INDEX_ADC_CHANNEL6]);
   SetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_FIR_TRIGGER_PLENGTH_7, gl_uint_FirTriggerPulseLength_Conf[module_index][INDEX_ADC_CHANNEL7]);
   SetCtrlVal (Panels[TRIG_PARA_CONF], TRIG_CONF_FIR_TRIGGER_PLENGTH_8, gl_uint_FirTriggerPulseLength_Conf[module_index][INDEX_ADC_CHANNEL8]);
         
	calculateFirTriggerAdcCounts ()  ; 
         
   return 0;
} // end function  ()
  

//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
/************************************************************************************************************/
//
//   ADC Input Signal Invert Panel
// 
/************************************************************************************************************/

 
int CVICALLBACK CB_ADC_InvertFlags (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:									  
  			switch (control)
			{
			  case SIGNA_CONF_CHECK_INVERTPULS_ADC1:
				GetCtrlVal (Panels[SIGNAL_INVERT_CONF], SIGNA_CONF_CHECK_INVERTPULS_ADC1,&gl_uint_ADC_SignalInvertInbox[INDEX_ADC_CHANNEL1]);  
				break;
			  case SIGNA_CONF_CHECK_INVERTPULS_ADC2:
				GetCtrlVal (Panels[SIGNAL_INVERT_CONF], SIGNA_CONF_CHECK_INVERTPULS_ADC2,&gl_uint_ADC_SignalInvertInbox[INDEX_ADC_CHANNEL2]);  
				break;
			  case SIGNA_CONF_CHECK_INVERTPULS_ADC3:
				GetCtrlVal (Panels[SIGNAL_INVERT_CONF], SIGNA_CONF_CHECK_INVERTPULS_ADC3,&gl_uint_ADC_SignalInvertInbox[INDEX_ADC_CHANNEL3]);  
				break;
			  case SIGNA_CONF_CHECK_INVERTPULS_ADC4:
				GetCtrlVal (Panels[SIGNAL_INVERT_CONF], SIGNA_CONF_CHECK_INVERTPULS_ADC4,&gl_uint_ADC_SignalInvertInbox[INDEX_ADC_CHANNEL4]);  
				break;
			  case SIGNA_CONF_CHECK_INVERTPULS_ADC5:
				GetCtrlVal (Panels[SIGNAL_INVERT_CONF], SIGNA_CONF_CHECK_INVERTPULS_ADC5,&gl_uint_ADC_SignalInvertInbox[INDEX_ADC_CHANNEL5]);  
				break;
			  case SIGNA_CONF_CHECK_INVERTPULS_ADC6:
				GetCtrlVal (Panels[SIGNAL_INVERT_CONF], SIGNA_CONF_CHECK_INVERTPULS_ADC6,&gl_uint_ADC_SignalInvertInbox[INDEX_ADC_CHANNEL6]);  
				break;
			  case SIGNA_CONF_CHECK_INVERTPULS_ADC7:
				GetCtrlVal (Panels[SIGNAL_INVERT_CONF], SIGNA_CONF_CHECK_INVERTPULS_ADC7,&gl_uint_ADC_SignalInvertInbox[INDEX_ADC_CHANNEL7]);  
				break;
			  case SIGNA_CONF_CHECK_INVERTPULS_ADC8:
				GetCtrlVal (Panels[SIGNAL_INVERT_CONF], SIGNA_CONF_CHECK_INVERTPULS_ADC8,&gl_uint_ADC_SignalInvertInbox[INDEX_ADC_CHANNEL8]);  
				break;
			} // end switch (control)

			break;
		}
	return 0;
}

				  
				  

//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
void CVICALLBACK CB_PutADCSignal_InvertFlagToTable (int menuBar, int menuItem, void *callbackData,
        int panel)
{
    switch (menuItem) {
        case MENUCONFSI_PUT_MODULE1 : {
            copy_AdcSignal_Invert_inboxvalues_to_confvalues (INDEX_MODULE1)   ;
           }  
           break;
        case MENUCONFSI_PUT_MODULE2 : {
            copy_AdcSignal_Invert_inboxvalues_to_confvalues (INDEX_MODULE2)   ;
           }  
           break;
        case MENUCONFSI_PUT_MODULE3 : {
            copy_AdcSignal_Invert_inboxvalues_to_confvalues (INDEX_MODULE3)   ;
           }  
           break;
        case MENUCONFSI_PUT_MODULE4 : {
            copy_AdcSignal_Invert_inboxvalues_to_confvalues (INDEX_MODULE4)   ;
           }  
           break;
        case MENUCONFSI_PUT_MODULE5 : {
            copy_AdcSignal_Invert_inboxvalues_to_confvalues (INDEX_MODULE5)   ;
           }  
           break;
        case MENUCONFSI_PUT_MODULE6 : {
            copy_AdcSignal_Invert_inboxvalues_to_confvalues (INDEX_MODULE6)   ;
           }  
           break;
        case MENUCONFSI_PUT_MODULE7 : {
            copy_AdcSignal_Invert_inboxvalues_to_confvalues (INDEX_MODULE7)   ;
           }  
           break;
        case MENUCONFSI_PUT_MODULE8 : {
            copy_AdcSignal_Invert_inboxvalues_to_confvalues (INDEX_MODULE8)   ;
           }  
           break;
        case MENUCONFSI_PUT_MODULE9 : {
            copy_AdcSignal_Invert_inboxvalues_to_confvalues (INDEX_MODULE9)   ;
           }  
           break;
        case MENUCONFSI_PUT_MODULE10 : {
            copy_AdcSignal_Invert_inboxvalues_to_confvalues (INDEX_MODULE10)   ;
           }  
           break;
        case MENUCONFSI_PUT_MODULE11 : {
            copy_AdcSignal_Invert_inboxvalues_to_confvalues (INDEX_MODULE11)   ;
           }  
           break;
        case MENUCONFSI_PUT_MODULE12 : {
            copy_AdcSignal_Invert_inboxvalues_to_confvalues (INDEX_MODULE12)   ;
           }  
           break;
        case MENUCONFSI_PUT_MODULE13 : {
            copy_AdcSignal_Invert_inboxvalues_to_confvalues (INDEX_MODULE13)   ;
           }  
           break;
        case MENUCONFSI_PUT_MODULE14 : {
            copy_AdcSignal_Invert_inboxvalues_to_confvalues (INDEX_MODULE14)   ;
           }  
           break;
     }  // switch

    CopyAdcSignal_InvertConfvaluesToTable () ;
//    CheckSystemStatus() ;  


return;
}


				   
//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 

void CVICALLBACK CB_GetADCSignal_InvertFlagToTable (int menuBar, int menuItem, void *callbackData,
        int panel)
{
    switch (menuItem) {
        case MENUCONFSI_GET_MODULE1 : {
            copy_AdcSignal_Invert_confvalues_to_input_inbox (INDEX_MODULE1)   ;
           }  
           break;
        case MENUCONFSI_GET_MODULE2 : {
            copy_AdcSignal_Invert_confvalues_to_input_inbox (INDEX_MODULE2)   ;
           }  
           break;
        case MENUCONFSI_GET_MODULE3 : {
            copy_AdcSignal_Invert_confvalues_to_input_inbox (INDEX_MODULE3)   ;
           }  
           break;
        case MENUCONFSI_GET_MODULE4 : {
            copy_AdcSignal_Invert_confvalues_to_input_inbox (INDEX_MODULE4)   ;
           }  
           break;
        case MENUCONFSI_GET_MODULE5 : {
            copy_AdcSignal_Invert_confvalues_to_input_inbox (INDEX_MODULE5)   ;
           }  
           break;
        case MENUCONFSI_GET_MODULE6 : {
            copy_AdcSignal_Invert_confvalues_to_input_inbox (INDEX_MODULE6)   ;
           }  
           break;
        case MENUCONFSI_GET_MODULE7 : {
            copy_AdcSignal_Invert_confvalues_to_input_inbox (INDEX_MODULE7)   ;
           }  
           break;
        case MENUCONFSI_GET_MODULE8 : {
			copy_AdcSignal_Invert_confvalues_to_input_inbox (INDEX_MODULE8)   ;
           }  
           break;
        case MENUCONFSI_GET_MODULE9 : {
			copy_AdcSignal_Invert_confvalues_to_input_inbox (INDEX_MODULE9)   ;
           }  
           break;
        case MENUCONFSI_GET_MODULE10 : {
			copy_AdcSignal_Invert_confvalues_to_input_inbox (INDEX_MODULE10)   ;
           }  
           break;
        case MENUCONFSI_GET_MODULE11 : {
			copy_AdcSignal_Invert_confvalues_to_input_inbox (INDEX_MODULE11)   ;
           }  
           break;
        case MENUCONFSI_GET_MODULE12 : {
			copy_AdcSignal_Invert_confvalues_to_input_inbox (INDEX_MODULE12)   ;
           }  
           break;
        case MENUCONFSI_GET_MODULE13 : {
			copy_AdcSignal_Invert_confvalues_to_input_inbox (INDEX_MODULE13)   ;
           }  
           break;
        case MENUCONFSI_GET_MODULE14 : {
			copy_AdcSignal_Invert_confvalues_to_input_inbox (INDEX_MODULE14)   ;
           }  
           break;
     }  // switch

 


return;
}


//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
/* functions for AdcSignal_Invert Flags  */

int copy_AdcSignal_Invert_inboxvalues_to_confvalues (unsigned int module_index)
{
   int i ;

   if (module_index >= MAX_NO_OF_MODULES) return -1 ;
  
   for (i=0; i < NO_OF_ADC_CHANNELS; i++)  {
	  gl_uint_ADC_SignalInvertConf[module_index][i] =  gl_uint_ADC_SignalInvertInbox[i] ;
   }
   return 0;
} // end function  ()

  


//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int CopyAdcSignal_InvertConfvaluesToTable (void)
{
   int i ;
   int imod, iadc;

	for (imod=0;imod < MAX_NO_OF_MODULES; imod++) {  
		for (iadc=0; iadc < NO_OF_ADC_CHANNELS; iadc++) {
		 	if (gl_uint_ADC_SignalInvertConf[imod][iadc] == 0)  {
		     	SetTableCellAttribute (Panels[SIGNAL_INVERT_CONF], SIGNA_CONF_INVERT_TABLE, MakePoint(1+(imod),9-(iadc)),ATTR_CTRL_VAL,"not invert");
		     	SetTableCellAttribute (Panels[SIGNAL_INVERT_CONF], SIGNA_CONF_INVERT_TABLE, MakePoint(1+(imod),9-(iadc)),ATTR_TEXT_COLOR,VAL_BLACK);
			}
			else {
		     	SetTableCellAttribute (Panels[SIGNAL_INVERT_CONF], SIGNA_CONF_INVERT_TABLE, MakePoint(1+(imod),9-(iadc)),ATTR_CTRL_VAL,"invert");
		     	SetTableCellAttribute (Panels[SIGNAL_INVERT_CONF], SIGNA_CONF_INVERT_TABLE, MakePoint(1+(imod),9-(iadc)),ATTR_TEXT_COLOR,VAL_RED);
			}
		}
	}
	return 0;
} // end function  ()





  
  
//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int copy_AdcSignal_Invert_confvalues_to_input_inbox (unsigned int module_index)
{
   int i ;
   if (module_index >= MAX_NO_OF_MODULES) return -1 ;

	for (i=0; i < NO_OF_ADC_CHANNELS; i++)  {
		gl_uint_ADC_SignalInvertInbox[i] =  gl_uint_ADC_SignalInvertConf[module_index][i] ;
	}
	SetCtrlVal (Panels[SIGNAL_INVERT_CONF], SIGNA_CONF_CHECK_INVERTPULS_ADC1,gl_uint_ADC_SignalInvertInbox[INDEX_ADC_CHANNEL1]);  
	SetCtrlVal (Panels[SIGNAL_INVERT_CONF], SIGNA_CONF_CHECK_INVERTPULS_ADC2,gl_uint_ADC_SignalInvertInbox[INDEX_ADC_CHANNEL2]);  
	SetCtrlVal (Panels[SIGNAL_INVERT_CONF], SIGNA_CONF_CHECK_INVERTPULS_ADC3,gl_uint_ADC_SignalInvertInbox[INDEX_ADC_CHANNEL3]);  
	SetCtrlVal (Panels[SIGNAL_INVERT_CONF], SIGNA_CONF_CHECK_INVERTPULS_ADC4,gl_uint_ADC_SignalInvertInbox[INDEX_ADC_CHANNEL4]);  
	SetCtrlVal (Panels[SIGNAL_INVERT_CONF], SIGNA_CONF_CHECK_INVERTPULS_ADC5,gl_uint_ADC_SignalInvertInbox[INDEX_ADC_CHANNEL5]);  
	SetCtrlVal (Panels[SIGNAL_INVERT_CONF], SIGNA_CONF_CHECK_INVERTPULS_ADC6,gl_uint_ADC_SignalInvertInbox[INDEX_ADC_CHANNEL6]);  
	SetCtrlVal (Panels[SIGNAL_INVERT_CONF], SIGNA_CONF_CHECK_INVERTPULS_ADC7,gl_uint_ADC_SignalInvertInbox[INDEX_ADC_CHANNEL7]);  
	SetCtrlVal (Panels[SIGNAL_INVERT_CONF], SIGNA_CONF_CHECK_INVERTPULS_ADC8,gl_uint_ADC_SignalInvertInbox[INDEX_ADC_CHANNEL8]);  
         
   
   return 0;
} // end function  ()
  
/************************************************************************************************************/
//
//   ADC Gain Factor Panel
// 
/************************************************************************************************************/


//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
 
int CVICALLBACK CB_Gain_Flags (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:									  
  			switch (control)
			{
			  case GAIN_CONF_CHECK_HALFSCALE_ADC1:
				GetCtrlVal (Panels[GAIN_FACTOR_CONF], GAIN_CONF_CHECK_HALFSCALE_ADC1,&gl_uint_ADC_Gain_FactorInbox[INDEX_ADC_CHANNEL1]);  
				break;
			  case GAIN_CONF_CHECK_HALFSCALE_ADC2:
				GetCtrlVal (Panels[GAIN_FACTOR_CONF], GAIN_CONF_CHECK_HALFSCALE_ADC2,&gl_uint_ADC_Gain_FactorInbox[INDEX_ADC_CHANNEL2]);  
				break;
			  case GAIN_CONF_CHECK_HALFSCALE_ADC3:
				GetCtrlVal (Panels[GAIN_FACTOR_CONF], GAIN_CONF_CHECK_HALFSCALE_ADC3,&gl_uint_ADC_Gain_FactorInbox[INDEX_ADC_CHANNEL3]);  
				break;
			  case GAIN_CONF_CHECK_HALFSCALE_ADC4:
				GetCtrlVal (Panels[GAIN_FACTOR_CONF], GAIN_CONF_CHECK_HALFSCALE_ADC4,&gl_uint_ADC_Gain_FactorInbox[INDEX_ADC_CHANNEL4]);  
				break;
			  case GAIN_CONF_CHECK_HALFSCALE_ADC5:
				GetCtrlVal (Panels[GAIN_FACTOR_CONF], GAIN_CONF_CHECK_HALFSCALE_ADC5,&gl_uint_ADC_Gain_FactorInbox[INDEX_ADC_CHANNEL5]);  
				break;
			  case GAIN_CONF_CHECK_HALFSCALE_ADC6:
				GetCtrlVal (Panels[GAIN_FACTOR_CONF], GAIN_CONF_CHECK_HALFSCALE_ADC6,&gl_uint_ADC_Gain_FactorInbox[INDEX_ADC_CHANNEL6]);  
				break;
			  case GAIN_CONF_CHECK_HALFSCALE_ADC7:
				GetCtrlVal (Panels[GAIN_FACTOR_CONF], GAIN_CONF_CHECK_HALFSCALE_ADC7,&gl_uint_ADC_Gain_FactorInbox[INDEX_ADC_CHANNEL7]);  
				break;
			  case GAIN_CONF_CHECK_HALFSCALE_ADC8:
				GetCtrlVal (Panels[GAIN_FACTOR_CONF], GAIN_CONF_CHECK_HALFSCALE_ADC8,&gl_uint_ADC_Gain_FactorInbox[INDEX_ADC_CHANNEL8]);  
				break;
			} // end switch (control)

			break;
		}
	return 0;
}

			

 
//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
void CVICALLBACK CB_PutGain_FactorFlagToTable (int menuBar, int menuItem, void *callbackData,
        int panel)
{
    switch (menuItem) {
        case MENUCONFGF_PUT_MODULE1 : {
            copy_Gain_FactorFlag_inboxvalues_to_confvalues (INDEX_MODULE1)   ;
           }  
           break;
        case MENUCONFGF_PUT_MODULE2 : {
            copy_Gain_FactorFlag_inboxvalues_to_confvalues (INDEX_MODULE2)   ;
           }  
           break;
        case MENUCONFGF_PUT_MODULE3 : {
            copy_Gain_FactorFlag_inboxvalues_to_confvalues (INDEX_MODULE3)   ;
           }  
           break;
        case MENUCONFGF_PUT_MODULE4 : {
            copy_Gain_FactorFlag_inboxvalues_to_confvalues (INDEX_MODULE4)   ;
           }  
           break;
        case MENUCONFGF_PUT_MODULE5 : {
            copy_Gain_FactorFlag_inboxvalues_to_confvalues (INDEX_MODULE5)   ;
           }  
           break;
        case MENUCONFGF_PUT_MODULE6 : {
            copy_Gain_FactorFlag_inboxvalues_to_confvalues (INDEX_MODULE6)   ;
           }  
           break;
        case MENUCONFGF_PUT_MODULE7 : {
            copy_Gain_FactorFlag_inboxvalues_to_confvalues (INDEX_MODULE7)   ;
           }  
           break;
        case MENUCONFGF_PUT_MODULE8 : {
            copy_Gain_FactorFlag_inboxvalues_to_confvalues (INDEX_MODULE8)   ;
           }  
           break;
        case MENUCONFGF_PUT_MODULE9 : {
            copy_Gain_FactorFlag_inboxvalues_to_confvalues (INDEX_MODULE9)   ;
           }  
           break;
        case MENUCONFGF_PUT_MODULE10 : {
            copy_Gain_FactorFlag_inboxvalues_to_confvalues (INDEX_MODULE10)   ;
           }  
           break;
        case MENUCONFGF_PUT_MODULE11 : {
            copy_Gain_FactorFlag_inboxvalues_to_confvalues (INDEX_MODULE11)   ;
           }  
           break;
        case MENUCONFGF_PUT_MODULE12 : {
            copy_Gain_FactorFlag_inboxvalues_to_confvalues (INDEX_MODULE12)   ;
           }  
           break;
        case MENUCONFGF_PUT_MODULE13 : {
            copy_Gain_FactorFlag_inboxvalues_to_confvalues (INDEX_MODULE13)   ;
           }  
           break;
        case MENUCONFGF_PUT_MODULE14 : {
            copy_Gain_FactorFlag_inboxvalues_to_confvalues (INDEX_MODULE14)   ;
           }  
           break;
     }  // switch

    CopyGain_FactorFlagConfvaluesToTable () ;
//    CheckSystemStatus() ;  


return;
}



//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
void CVICALLBACK CB_GetGain_FactorFlagToTable (int menuBar, int menuItem, void *callbackData,
        int panel)
{
    switch (menuItem) {
        case MENUCONFGF_GET_MODULE1 : {
            copy_Gain_FactorFlag_confvalues_to_input_inbox (INDEX_MODULE1)   ;
           }  
           break;
        case MENUCONFGF_GET_MODULE2 : {
            copy_Gain_FactorFlag_confvalues_to_input_inbox (INDEX_MODULE2)   ;
           }  
           break;
        case MENUCONFGF_GET_MODULE3 : {
            copy_Gain_FactorFlag_confvalues_to_input_inbox (INDEX_MODULE3)   ;
           }  
           break;
        case MENUCONFGF_GET_MODULE4 : {
            copy_Gain_FactorFlag_confvalues_to_input_inbox (INDEX_MODULE4)   ;
           }  
           break;
        case MENUCONFGF_GET_MODULE5 : {
            copy_Gain_FactorFlag_confvalues_to_input_inbox (INDEX_MODULE5)   ;
           }  
           break;
        case MENUCONFGF_GET_MODULE6 : {
            copy_Gain_FactorFlag_confvalues_to_input_inbox (INDEX_MODULE6)   ;
           }  
           break;
        case MENUCONFGF_GET_MODULE7 : {
            copy_Gain_FactorFlag_confvalues_to_input_inbox (INDEX_MODULE7)   ;
           }  
           break;
        case MENUCONFGF_GET_MODULE8 : {
			copy_Gain_FactorFlag_confvalues_to_input_inbox (INDEX_MODULE8)   ;
           }  
           break;
        case MENUCONFGF_GET_MODULE9 : {
			copy_Gain_FactorFlag_confvalues_to_input_inbox (INDEX_MODULE9)   ;
           }  
           break;
        case MENUCONFGF_GET_MODULE10 : {
			copy_Gain_FactorFlag_confvalues_to_input_inbox (INDEX_MODULE10)   ;
           }  
           break;
        case MENUCONFGF_GET_MODULE11 : {
			copy_Gain_FactorFlag_confvalues_to_input_inbox (INDEX_MODULE11)   ;
           }  
           break;
        case MENUCONFGF_GET_MODULE12 : {
			copy_Gain_FactorFlag_confvalues_to_input_inbox (INDEX_MODULE12)   ;
           }  
           break;
        case MENUCONFGF_GET_MODULE13 : {
			copy_Gain_FactorFlag_confvalues_to_input_inbox (INDEX_MODULE13)   ;
           }  
           break;
        case MENUCONFGF_GET_MODULE14 : {
			copy_Gain_FactorFlag_confvalues_to_input_inbox (INDEX_MODULE14)   ;
           }  
           break;
     }  // switch

return;
}

   

//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
/* functions for   */
			  
int copy_Gain_FactorFlag_inboxvalues_to_confvalues (unsigned int module_index)
{
   int i ;

   if (module_index >= MAX_NO_OF_MODULES) return -1 ;
  
   for (i=0; i < NO_OF_ADC_CHANNELS; i++)  {
	  gl_uint_ADC_Gain_FactorConf[module_index][i] =  gl_uint_ADC_Gain_FactorInbox[i] ;
   }
   return 0;
} // end function  ()

  


//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int CopyGain_FactorFlagConfvaluesToTable (void)
{
   int i ;
   int imod, iadc;

	for (imod=0;imod < MAX_NO_OF_MODULES; imod++) {  
		for (iadc=0; iadc < NO_OF_ADC_CHANNELS; iadc++) {
		 	if (gl_uint_ADC_Gain_FactorConf[imod][iadc] == 0)  {
		     	SetTableCellAttribute (Panels[GAIN_FACTOR_CONF], GAIN_CONF_GAIN_TABLE, MakePoint(1+(imod),9-(iadc)),ATTR_CTRL_VAL,"full scale");
		     	SetTableCellAttribute (Panels[GAIN_FACTOR_CONF], GAIN_CONF_GAIN_TABLE, MakePoint(1+(imod),9-(iadc)),ATTR_TEXT_COLOR,VAL_BLACK);
			}
			else {
		     	SetTableCellAttribute (Panels[GAIN_FACTOR_CONF], GAIN_CONF_GAIN_TABLE, MakePoint(1+(imod),9-(iadc)),ATTR_CTRL_VAL,"halffull scale");
		     	SetTableCellAttribute (Panels[GAIN_FACTOR_CONF], GAIN_CONF_GAIN_TABLE, MakePoint(1+(imod),9-(iadc)),ATTR_TEXT_COLOR,VAL_RED);
			}											 
		}
	}
	return 0;
} // end function  ()


  
//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
  
int copy_Gain_FactorFlag_confvalues_to_input_inbox (unsigned int module_index)
{
   int i ;
   if (module_index >= MAX_NO_OF_MODULES) return -1 ;

	for (i=0; i < NO_OF_ADC_CHANNELS; i++)  {
		gl_uint_ADC_Gain_FactorInbox[i] =  gl_uint_ADC_Gain_FactorConf[module_index][i] ;
	}
	SetCtrlVal (Panels[GAIN_FACTOR_CONF], GAIN_CONF_CHECK_HALFSCALE_ADC1,gl_uint_ADC_Gain_FactorInbox[INDEX_ADC_CHANNEL1]);  
	SetCtrlVal (Panels[GAIN_FACTOR_CONF], GAIN_CONF_CHECK_HALFSCALE_ADC2,gl_uint_ADC_Gain_FactorInbox[INDEX_ADC_CHANNEL2]);  
	SetCtrlVal (Panels[GAIN_FACTOR_CONF], GAIN_CONF_CHECK_HALFSCALE_ADC3,gl_uint_ADC_Gain_FactorInbox[INDEX_ADC_CHANNEL3]);  
	SetCtrlVal (Panels[GAIN_FACTOR_CONF], GAIN_CONF_CHECK_HALFSCALE_ADC4,gl_uint_ADC_Gain_FactorInbox[INDEX_ADC_CHANNEL4]);  
	SetCtrlVal (Panels[GAIN_FACTOR_CONF], GAIN_CONF_CHECK_HALFSCALE_ADC5,gl_uint_ADC_Gain_FactorInbox[INDEX_ADC_CHANNEL5]);  
	SetCtrlVal (Panels[GAIN_FACTOR_CONF], GAIN_CONF_CHECK_HALFSCALE_ADC6,gl_uint_ADC_Gain_FactorInbox[INDEX_ADC_CHANNEL6]);  
	SetCtrlVal (Panels[GAIN_FACTOR_CONF], GAIN_CONF_CHECK_HALFSCALE_ADC7,gl_uint_ADC_Gain_FactorInbox[INDEX_ADC_CHANNEL7]);  
	SetCtrlVal (Panels[GAIN_FACTOR_CONF], GAIN_CONF_CHECK_HALFSCALE_ADC8,gl_uint_ADC_Gain_FactorInbox[INDEX_ADC_CHANNEL8]);  
         
   
   return 0;
} // end function  ()
  
//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
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
//                                                             
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



//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
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


		   





//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
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

/************************************************************************************************/


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

 	  	GetCtrlVal (Panels[SAMPLE_PARA_CONF],SAMPL_CONF_ACCU_DATA_FORMAT, &temp);
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



