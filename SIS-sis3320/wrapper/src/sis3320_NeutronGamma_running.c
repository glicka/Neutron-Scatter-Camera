/***************************************************************************/
/*                                                                         */
/*  Project: Neutron/Gamma Detector                                        */
/*                                                                         */
/*                                                                         */
/*  Filename: sis3320_NeutronGamma_running.c                               */
/*                                                                         */
/*  Funktion: running control                                              */
/*                                                                         */
/*  Autor:                TH                                               */
/*  date:                 08.09.2006                                       */
/*  last modification:    11.02.2008                                       */
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

//#define  th_test_gates 
//
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


#include "sis3820_clock.h" 	 
#include "pc_vme_interface_defines.h"
#include "vme_TS_communication_address_map.h"
#include "sis3150USB.h" 	 
#include "sis3150.h" 	 
#include "sis3320_NeutronGamma.h" 	 
#include "pc_to_vme_routines.h"


//--------------------------------------------------------------------------- 
// Local DEFINES (to be put into Include File)                                                              
//--------------------------------------------------------------------------- 
char file_gl_messages_buffer[128] ;           

int uint_timer ;
int uint_temp1 = 0 ;
int uint_temp2 = 0 ;

// --- Prototyps   (sis3300_greta_running) -----------------------------

char *Create_Entire_Stamp_Filename (char *directory, char *extension)  ;
int SetDefaultDataFileName (void);
int ChangeDataFileName (void) ;
int ChangeSIS3150USB_TS_ReadoutLoaderFileName (void) ;
int RunAquisition (void)	  ;


int RunPC_SingleEventAquisition (void)  ;
int RunPC_SIS3320LLNL_MultiEvent_SingleBuffer_Aquisition (void) ;
int RunPC_SIS3320LLNL_MultiEvent_DoubleBuffer_Aquisition (void) ;
int RunPC_SIS3150USB_DSP_Load_Program (void);


int displayRunEventInformations (void)   ;

int Configuration_SIS3150USB (void) ;  
int Setup_Load_Loaderfile_sis3150usb_tigersharcs (void)  ; 
int Setup_SIS3150USB_TS_readout_parameters (unsigned int max_nof_events, unsigned int channel_event_length) ;   

int sis_AnyErrorHandling (char *err_messages) ;

unsigned int timestamp[8] ;


//--------------------------------------------------------------------------- 
// Root Menu Call Back
//--------------------------------------------------------------------------- 


void CVICALLBACK CB_OpenPanelRunControl (int menuBar, int menuItem, void *callbackData,
        int panel)
{
    switch (menuItem) {
        case MENU_RUN_MENUE_OPENPANEL : {


      		SetMenuBarAttribute  (MenuBars[RUNCTRL_MENU_BAR], MENUCTRLRU_TEST_TRIGGER, ATTR_DIMMED, ON);
//      		SetMenuBarAttribute  (MenuBars[RUNCTRL_MENU_BAR], MENUCTRLRU_TEST_TRIGGER, ATTR_DIMMED, OFF);  //roe 14.12.09
			//gl_uint_RunReadoutMode = 1 ;  // PC Multievent 
		   	SetCtrlVal (Panels[RUN_CTRL_MENUE],RUN_CTRL_READOUT_MODE,gl_uint_RunReadoutMode);

  					switch (gl_uint_RunReadoutMode) {
						case RUNNING_MODE_PC_SINGLE_EVENT:
							gl_uint_RunCheckDisplayRawFlag        = 1  ;  // on
							SetCtrlAttribute (Panels[RUN_CTRL_MENUE], RUN_CTRL_STRING_USBTS_FILE_NAM, ATTR_DIMMED, 1);
			 		  		SetCtrlVal (Panels[RUN_CTRL_MENUE],RUN_CTRL_NOF_EVENT_READ,1);
					  		SetCtrlAttribute (Panels[RUN_CTRL_MENUE], RUN_CTRL_CHECKBOX_DISPL_RAW, ATTR_DIMMED, 0);
					  		SetCtrlAttribute (Panels[RUN_CTRL_MENUE], RUN_CTRL_CHECKBOX_DISPL_ENER_V, ATTR_DIMMED, 0);

						  	break;

						case RUNNING_MODE_PC_MULTI_EVENT_SINGLE_BUFFER:
							gl_uint_RunCheckDisplayRawFlag        = 1  ;  // on
							SetCtrlAttribute (Panels[RUN_CTRL_MENUE], RUN_CTRL_STRING_USBTS_FILE_NAM, ATTR_DIMMED, 1);
			 		  		SetCtrlVal (Panels[RUN_CTRL_MENUE],RUN_CTRL_NOF_EVENT_READ,1);
					  		SetCtrlAttribute (Panels[RUN_CTRL_MENUE], RUN_CTRL_CHECKBOX_DISPL_RAW, ATTR_DIMMED, 0);
					  		SetCtrlAttribute (Panels[RUN_CTRL_MENUE], RUN_CTRL_CHECKBOX_DISPL_ENER_V, ATTR_DIMMED, 0);

						  	break;

						case RUNNING_MODE_PC_MULTI_EVENT_DOUBLE_BUFFER:
							gl_uint_RunCheckDisplayRawFlag        = 1  ;  // on
							SetCtrlAttribute (Panels[RUN_CTRL_MENUE], RUN_CTRL_STRING_USBTS_FILE_NAM, ATTR_DIMMED, 1);
			 		  		SetCtrlVal (Panels[RUN_CTRL_MENUE],RUN_CTRL_NOF_EVENT_READ,1);
					  		SetCtrlAttribute (Panels[RUN_CTRL_MENUE], RUN_CTRL_CHECKBOX_DISPL_RAW, ATTR_DIMMED, 0);
					  		SetCtrlAttribute (Panels[RUN_CTRL_MENUE], RUN_CTRL_CHECKBOX_DISPL_ENER_V, ATTR_DIMMED, 0);

						  	break;

						

						case RUNNING_MODE_SIS3150USB_DSP_LOAD_PROGRAM_TEST:
							gl_uint_RunCheckDisplayRawFlag        = 0  ;  // off
							SetCtrlAttribute (Panels[RUN_CTRL_MENUE], RUN_CTRL_STRING_USBTS_FILE_NAM, ATTR_DIMMED, 0);
			 		  		SetCtrlVal (Panels[RUN_CTRL_MENUE],RUN_CTRL_NOF_EVENT_READ,1);

 							closePanelDisplayRaw()  ;
							gl_uint_RunCheckDisplayRawFlag = 0 ;
							SetCtrlVal (Panels[RUN_CTRL_MENUE], RUN_CTRL_CHECKBOX_DISPL_RAW,gl_uint_RunCheckDisplayRawFlag);  
					  		SetCtrlAttribute (Panels[RUN_CTRL_MENUE], RUN_CTRL_CHECKBOX_DISPL_RAW, ATTR_DIMMED, 1);
							
              				closePanelDisplayEnergyValue(); //Clear Panel 
							gl_uint_RunCheckDisplayEnergyValueFlag = 0 ;
							SetCtrlVal (Panels[RUN_CTRL_MENUE], RUN_CTRL_CHECKBOX_DISPL_ENER_V,gl_uint_RunCheckDisplayEnergyValueFlag);  
					  		SetCtrlAttribute (Panels[RUN_CTRL_MENUE], RUN_CTRL_CHECKBOX_DISPL_ENER_V, ATTR_DIMMED, 1);

						  	break;

					} // end switch (gl_uint_RunReadoutMode)
    		
    		
    		SetCtrlVal (Panels[RUN_CTRL_MENUE], RUN_CTRL_STRING_USBTS_FILE_NAM, gl_char_FileNameLoaderSIS3150USB_TS);

			gl_uint_RunDisableStartClearFlag = 0 ;
			SetCtrlVal (Panels[RUN_CTRL_MENUE], RUN_CTRL_CHECKBOX_START_CLR_DI,gl_uint_RunDisableStartClearFlag);  

	 
	 // Raw panel
			setupPanelDisplayRaw() ;
			SetCtrlVal (Panels[RUN_CTRL_MENUE], RUN_CTRL_CHECKBOX_DISPL_RAW, gl_uint_RunCheckDisplayRawFlag);  
			if(gl_uint_RunCheckDisplayRawFlag == 1) {
			 	SetMenuBarAttribute  (MenuBars[RUNCTRL_MENU_BAR], MENUCTRLRU_WINDOW_RUN_RAW_ACTIV, ATTR_DIMMED, OFF);
				openPanelDisplayRaw() ;

			}
			 else {
			 	SetMenuBarAttribute  (MenuBars[RUNCTRL_MENU_BAR], MENUCTRLRU_WINDOW_RUN_RAW_ACTIV, ATTR_DIMMED, ON);
				closePanelDisplayRaw() ;
			}

	 // Energy Value (MWD) panel
			setupPanelDisplayEnergyValue() ;
			gl_uint_RunCheckDisplayEnergyValueFlag     = 0  ;  // off
			SetCtrlVal (Panels[RUN_CTRL_MENUE], RUN_CTRL_CHECKBOX_DISPL_ENER_V, gl_uint_RunCheckDisplayEnergyValueFlag);  
			if(gl_uint_RunCheckDisplayEnergyValueFlag == 1) {
			 	SetMenuBarAttribute  (MenuBars[RUNCTRL_MENU_BAR], MENUCTRLRU_WINDOW_RUN_FPGA_ACTIV, ATTR_DIMMED, OFF);
				openPanelDisplayEnergyValue() ;
			}
			 else {
			 	SetMenuBarAttribute  (MenuBars[RUNCTRL_MENU_BAR], MENUCTRLRU_WINDOW_RUN_FPGA_ACTIV, ATTR_DIMMED, ON);
				closePanelDisplayEnergyValue() ;
			}

			
			setupPanelDisplayEnergySpectrum() ;
			gl_uint_RunCheckDisplayEnergySpectrumFlag     = 0  ;  // off
			SetCtrlVal (Panels[RUN_CTRL_MENUE], RUN_CTRL_CHECKBOX_DISPL_ENSPEC, gl_uint_RunCheckDisplayEnergySpectrumFlag);  

			if(gl_uint_RunCheckDisplayEnergySpectrumFlag == 1) {
			 	SetMenuBarAttribute  (MenuBars[RUNCTRL_MENU_BAR], MENUCTRLRU_WINDOW_RUN_SPEC_ACTIV, ATTR_DIMMED, OFF);
				openPanelDisplayEnergySpectrum() ;
			}
			 else {
			 	SetMenuBarAttribute  (MenuBars[RUNCTRL_MENU_BAR], MENUCTRLRU_WINDOW_RUN_SPEC_ACTIV, ATTR_DIMMED, ON);
				closePanelDisplayEnergySpectrum() ;
			}


			gl_uint_RunCheckDisplayDiagnosticFlag     = 0  ;  // off
			SetCtrlVal (Panels[RUN_CTRL_MENUE], RUN_CTRL_CHECKBOX_DISPL_DIAG, gl_uint_RunCheckDisplayDiagnosticFlag);  
			if (gl_uint_RunCheckDisplayDiagnosticFlag == 1) { //off
			 	SetMenuBarAttribute  (MenuBars[RUNCTRL_MENU_BAR], MENUCTRLRU_WINDOW_RUN_DIAG_ACTIV, ATTR_DIMMED, OFF);
				openPanelDiagnosticPattern(gl_uint_NoOfModulesRun) ;
			}
			else { // on
			 	SetMenuBarAttribute  (MenuBars[RUNCTRL_MENU_BAR], MENUCTRLRU_WINDOW_RUN_DIAG_ACTIV, ATTR_DIMMED, ON);
				closePanelDiagnosticPattern() ;
			}

			gl_uint_RunCheckWrDataToFileFlag      = 0  ;  // off
			SetCtrlVal (Panels[RUN_CTRL_MENUE], RUN_CTRL_CHECKBOX_WR_DATA,gl_uint_RunCheckWrDataToFileFlag);  
			if(gl_uint_RunCheckWrDataToFileFlag == 0) {
				SetCtrlAttribute (Panels[RUN_CTRL_MENUE], RUN_CTRL_STRING_DATAFILE_NAME, ATTR_DIMMED, 1);
  			}
			else {
				SetCtrlAttribute (Panels[RUN_CTRL_MENUE], RUN_CTRL_STRING_DATAFILE_NAME, ATTR_DIMMED, 0);
  			}
		  	SetCtrlAttribute (Panels[RUN_CTRL_MENUE], RUN_CTRL_CHECKBOX_WR_DATA, ATTR_DIMMED, 0);


				
			gl_uint_RunMaxSecondsCounter = 60 ;
			SetCtrlVal (Panels[RUN_CTRL_MENUE], RUN_CTRL_RUN_EVENT_MAX_SECOND, gl_uint_RunMaxSecondsCounter);
			gl_uint_RunCheckStopTimeFlag      = 0  ;  // off
			SetCtrlVal (Panels[RUN_CTRL_MENUE], RUN_CTRL_CHECKBOX_STOP_TIME, gl_uint_RunCheckStopTimeFlag);  
			if(gl_uint_RunCheckStopTimeFlag == 0) {
				SetCtrlAttribute (Panels[RUN_CTRL_MENUE], RUN_CTRL_RUN_EVENT_MAX_SECOND, ATTR_DIMMED, 1);
		  	 }
		 	else {
				SetCtrlAttribute (Panels[RUN_CTRL_MENUE], RUN_CTRL_RUN_EVENT_MAX_SECOND, ATTR_DIMMED, 0);
		 	 }


			gl_uint_RunMaxEventCounter = 1000 ;
			SetCtrlVal (Panels[RUN_CTRL_MENUE], RUN_CTRL_RUN_EVENT_MAX_NUMBER, gl_uint_RunMaxEventCounter);
			gl_uint_RunCheckStopEventsFlag      = 0  ;  // off
			SetCtrlVal (Panels[RUN_CTRL_MENUE], RUN_CTRL_CHECKBOX_STOP_EVENT, gl_uint_RunCheckStopEventsFlag);  
  			if(gl_uint_RunCheckStopEventsFlag == 0) {
				SetCtrlAttribute (Panels[RUN_CTRL_MENUE], RUN_CTRL_RUN_EVENT_MAX_NUMBER, ATTR_DIMMED, 1);
  			}
			 else {
				SetCtrlAttribute (Panels[RUN_CTRL_MENUE], RUN_CTRL_RUN_EVENT_MAX_NUMBER, ATTR_DIMMED, 0);
  			 }

	        SetPanelPos(Panels[RUN_CTRL_MENUE],DEFINE_PANEL_RUN_CTRL_POS_Y,DEFINE_PANEL_RUN_CTRL_POS_X)  ;   // y, x
			SetCtrlAttribute (Panels[RUN_CTRL_MENUE], RUN_CTRL_STARTBUTTOM, ATTR_VISIBLE, 1);
			SetCtrlAttribute (Panels[RUN_CTRL_MENUE], RUN_CTRL_STOPBUTTOM, ATTR_VISIBLE, 0);

			DisplayPanel (Panels[RUN_CTRL_MENUE]);

 
			SetDefaultDataFileName () ;
			gl_uint_DataEvent_OpenFlag    = 0   ; // Closed
            
            }

			
            break;

        }    // end switch menu item
	return ;
}



//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
/* close Panels */
void CVICALLBACK CB_MenuRunControl (int menuBar, int menuItem, void *callbackData,
        int panel)
{
    switch (menuItem) {
        case MENUCTRLRU_PANEL_CLOSE : {
			closePanelDisplayRaw()  ;
			closePanelDisplayEnergyValue()  ;
			closePanelDisplayEnergySpectrum() ;
			SetCtrlAttribute (Panels[RUN_CTRL_MENUE], RUN_CTRL_ONE_M_SECOND_TICK, ATTR_ENABLED, OFF);

            HidePanel(Panels[RUN_CTRL_MENUE]); //Clear Panel 
           }  
           break;
        case MENUCTRLRU_FILE_CHANGE_DATA_FILE : {
			ChangeDataFileName () ;
           }  
           break;
        case MENUCTRLRU_FILE_CHANGE_USBTSFILE : {
			ChangeSIS3150USB_TS_ReadoutLoaderFileName () ;
           }  
           break;

        case MENUCTRLRU_WINDOW_RUN_RAW_ACTIV : {
			SetActivePanel (Panels[PANEL_DISPLAY_RAW]);
           }  
           break;
        case MENUCTRLRU_WINDOW_RUN_FPGA_ACTIV : {
			SetActivePanel (Panels[PANEL_DISPLAY_EVALUES]);
           }  
           break;
        case MENUCTRLRU_WINDOW_RUN_SPEC_ACTIV : {
			SetActivePanel (Panels[PANEL_DISPLAY_ENERGY_SPEC]);
           }  
           break;
        case MENUCTRLRU_WINDOW_RUN_DIAG_ACTIV : {
			SetActivePanel (Panels[PANEL_DISPLAY_DIAGNOSTIC]);
            SetMenuBarAttribute  (MenuBars[RUNCTRL_MENU_BAR], MENUCTRLRU_TEST_TRIGGER, ATTR_DIMMED, OFF);
           }  
           break;
        case MENUCTRLRU_TEST_TRIGGER_LOOP_ON : {
			SetCtrlAttribute (Panels[RUN_CTRL_MENUE], RUN_CTRL_ONE_M_SECOND_TICK, ATTR_ENABLED, ON);
 			SetCtrlVal (Panels[RUN_CTRL_MENUE], RUN_CTRL_LED_LOOP, ON);
           }  
           break;
        case MENUCTRLRU_TEST_TRIGGER_LOOP_OFF : {
			SetCtrlAttribute (Panels[RUN_CTRL_MENUE], RUN_CTRL_ONE_M_SECOND_TICK, ATTR_ENABLED, OFF);
 			SetCtrlVal (Panels[RUN_CTRL_MENUE], RUN_CTRL_LED_LOOP, OFF);
           }  
           break;
     }  // switch

return;
}
		  													 
			  

 		  


//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
 int CVICALLBACK CB_CheckBoxRun (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int check_on, temp ;
	switch (event)
		{
		case EVENT_COMMIT:
  			switch (control)
			{

 			  case RUN_CTRL_CHECK_NOF_EVENT_MANUA:
				GetCtrlVal (Panels[RUN_CTRL_MENUE], RUN_CTRL_CHECK_NOF_EVENT_MANUA,&temp);  
				if (temp == 0) {
				  	SetCtrlAttribute (Panels[RUN_CTRL_MENUE], RUN_CTRL_RUN_EVENT_MAX_NUMBER2, ATTR_DIMMED, 1);
				}
				else {
				  	SetCtrlAttribute (Panels[RUN_CTRL_MENUE], RUN_CTRL_RUN_EVENT_MAX_NUMBER2, ATTR_DIMMED, 0);
				}
				break ;			


		  // disable Clear
			  case RUN_CTRL_CHECKBOX_START_CLR_DI:
				GetCtrlVal (Panels[RUN_CTRL_MENUE], RUN_CTRL_CHECKBOX_START_CLR_DI,&gl_uint_RunDisableStartClearFlag);  
				break ;			
		  // raw
			  case RUN_CTRL_CHECKBOX_DISPL_RAW:
				GetCtrlVal (Panels[RUN_CTRL_MENUE], RUN_CTRL_CHECKBOX_DISPL_RAW,&gl_uint_RunCheckDisplayRawFlag);  
				if (gl_uint_RunCheckDisplayRawFlag == 0) { //off
				 	SetMenuBarAttribute  (MenuBars[RUNCTRL_MENU_BAR], MENUCTRLRU_WINDOW_RUN_RAW_ACTIV, ATTR_DIMMED, ON);
 					closePanelDisplayRaw()  ;
				  }
				  else { // on
					setupPanelDisplayRaw() ;
				 	SetMenuBarAttribute  (MenuBars[RUNCTRL_MENU_BAR], MENUCTRLRU_WINDOW_RUN_RAW_ACTIV, ATTR_DIMMED, OFF);
	 				openPanelDisplayRaw() ;
				  }
				break ;			


		  // Energy Values
			  case RUN_CTRL_CHECKBOX_DISPL_ENER_V:
				GetCtrlVal (Panels[RUN_CTRL_MENUE], RUN_CTRL_CHECKBOX_DISPL_ENER_V,&gl_uint_RunCheckDisplayEnergyValueFlag);  
				if (gl_uint_RunCheckDisplayEnergyValueFlag == 0) { //off
             		//HidePanel(Panels[PANEL_DISPLAY_RAW]); //Clear Panel 
				 	SetMenuBarAttribute  (MenuBars[RUNCTRL_MENU_BAR], MENUCTRLRU_WINDOW_RUN_FPGA_ACTIV, ATTR_DIMMED, ON);
             		closePanelDisplayEnergyValue(); //Clear Panel 
				  }
				  else { // on
				 	SetMenuBarAttribute  (MenuBars[RUNCTRL_MENU_BAR], MENUCTRLRU_WINDOW_RUN_FPGA_ACTIV, ATTR_DIMMED, OFF);
	 				openPanelDisplayEnergyValue() ;
				  }
				break ;			

		//energy Spectrum display				
			  case RUN_CTRL_CHECKBOX_DISPL_ENSPEC:
				GetCtrlVal (Panels[RUN_CTRL_MENUE], RUN_CTRL_CHECKBOX_DISPL_ENSPEC,&gl_uint_RunCheckDisplayEnergySpectrumFlag);  
				if (gl_uint_RunCheckDisplayEnergySpectrumFlag == 0) { //off
				 	SetMenuBarAttribute  (MenuBars[RUNCTRL_MENU_BAR], MENUCTRLRU_WINDOW_RUN_SPEC_ACTIV, ATTR_DIMMED, ON);
					closePanelDisplayEnergySpectrum() ;
				  }
				  else { // on
				 	SetMenuBarAttribute  (MenuBars[RUNCTRL_MENU_BAR], MENUCTRLRU_WINDOW_RUN_SPEC_ACTIV, ATTR_DIMMED, OFF);
					openPanelDisplayEnergySpectrum() ;
				  }
					break ;			


 		// diagnostic	  
			  case RUN_CTRL_CHECKBOX_DISPL_DIAG:
				GetCtrlVal (Panels[RUN_CTRL_MENUE], RUN_CTRL_CHECKBOX_DISPL_DIAG,&gl_uint_RunCheckDisplayDiagnosticFlag);  
				if (gl_uint_RunCheckDisplayDiagnosticFlag == 0) { //off
				 	SetMenuBarAttribute  (MenuBars[RUNCTRL_MENU_BAR], MENUCTRLRU_WINDOW_RUN_DIAG_ACTIV, ATTR_DIMMED, ON);
					closePanelDiagnosticPattern() ;
				}
				else { // on
				 	SetMenuBarAttribute  (MenuBars[RUNCTRL_MENU_BAR], MENUCTRLRU_WINDOW_RUN_DIAG_ACTIV, ATTR_DIMMED, OFF);
					openPanelDiagnosticPattern(gl_uint_NoOfModulesRun) ;
				}
					break ;			

			  case RUN_CTRL_CHECKBOX_WR_DATA:
				GetCtrlVal (Panels[RUN_CTRL_MENUE], RUN_CTRL_CHECKBOX_WR_DATA,&gl_uint_RunCheckWrDataToFileFlag);  
				if(gl_uint_RunCheckWrDataToFileFlag == 0) {
					SetCtrlAttribute (Panels[RUN_CTRL_MENUE], RUN_CTRL_STRING_DATAFILE_NAME, ATTR_DIMMED, 1);
  			  	 }
			 	else {
					SetCtrlAttribute (Panels[RUN_CTRL_MENUE], RUN_CTRL_STRING_DATAFILE_NAME, ATTR_DIMMED, 0);
					SetDefaultDataFileName () ;
  			 	 }
				break ;			
				 
			  
			  case RUN_CTRL_CHECKBOX_STOP_TIME:
				GetCtrlVal (Panels[RUN_CTRL_MENUE], RUN_CTRL_CHECKBOX_STOP_TIME,&gl_uint_RunCheckStopTimeFlag);  
				if(gl_uint_RunCheckStopTimeFlag == 0) {
					SetCtrlAttribute (Panels[RUN_CTRL_MENUE], RUN_CTRL_RUN_EVENT_MAX_SECOND, ATTR_DIMMED, 1);
  			  	 }
			 	else {
					SetCtrlAttribute (Panels[RUN_CTRL_MENUE], RUN_CTRL_RUN_EVENT_MAX_SECOND, ATTR_DIMMED, 0);
  			 	 }
				break ;			

			  case RUN_CTRL_CHECKBOX_STOP_EVENT:
				GetCtrlVal (Panels[RUN_CTRL_MENUE], RUN_CTRL_CHECKBOX_STOP_EVENT,&gl_uint_RunCheckStopEventsFlag);  
  				if(gl_uint_RunCheckStopEventsFlag == 0) {
					SetCtrlAttribute (Panels[RUN_CTRL_MENUE], RUN_CTRL_RUN_EVENT_MAX_NUMBER, ATTR_DIMMED, 1);
  			 	  }
				 else {
					SetCtrlAttribute (Panels[RUN_CTRL_MENUE], RUN_CTRL_RUN_EVENT_MAX_NUMBER, ATTR_DIMMED, 0);
  			 	  }
				break ;			


			} // end switch (control)

			break;
		}
	return 0;
}





//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int CVICALLBACK CB_Run_ReadoutMode (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
  			switch (control)
			{
				case RUN_CTRL_READOUT_MODE:
		 		  	GetCtrlVal (Panels[RUN_CTRL_MENUE],RUN_CTRL_READOUT_MODE,&gl_uint_RunReadoutMode);
  					switch (gl_uint_RunReadoutMode) {
						case RUNNING_MODE_PC_SINGLE_EVENT:
							SetCtrlAttribute (Panels[RUN_CTRL_MENUE], RUN_CTRL_STRING_USBTS_FILE_NAM, ATTR_DIMMED, 1);
			 		  		SetCtrlVal (Panels[RUN_CTRL_MENUE],RUN_CTRL_NOF_EVENT_READ,1);
					  		SetCtrlAttribute (Panels[RUN_CTRL_MENUE], RUN_CTRL_CHECKBOX_DISPL_RAW, ATTR_DIMMED, 0);
					  		SetCtrlAttribute (Panels[RUN_CTRL_MENUE], RUN_CTRL_CHECKBOX_DISPL_ENER_V, ATTR_DIMMED, 0);


						  	break;

						case RUNNING_MODE_PC_MULTI_EVENT_SINGLE_BUFFER:
							SetCtrlAttribute (Panels[RUN_CTRL_MENUE], RUN_CTRL_STRING_USBTS_FILE_NAM, ATTR_DIMMED, 1);
			 		  		SetCtrlVal (Panels[RUN_CTRL_MENUE],RUN_CTRL_NOF_EVENT_READ,1);
					  		SetCtrlAttribute (Panels[RUN_CTRL_MENUE], RUN_CTRL_CHECKBOX_DISPL_RAW, ATTR_DIMMED, 0);
					  		SetCtrlAttribute (Panels[RUN_CTRL_MENUE], RUN_CTRL_CHECKBOX_DISPL_ENER_V, ATTR_DIMMED, 0);

						  	break;

						case RUNNING_MODE_PC_MULTI_EVENT_DOUBLE_BUFFER:
							SetCtrlAttribute (Panels[RUN_CTRL_MENUE], RUN_CTRL_STRING_USBTS_FILE_NAM, ATTR_DIMMED, 1);
			 		  		SetCtrlVal (Panels[RUN_CTRL_MENUE],RUN_CTRL_NOF_EVENT_READ,1);
					  		SetCtrlAttribute (Panels[RUN_CTRL_MENUE], RUN_CTRL_CHECKBOX_DISPL_RAW, ATTR_DIMMED, 0);
					  		SetCtrlAttribute (Panels[RUN_CTRL_MENUE], RUN_CTRL_CHECKBOX_DISPL_ENER_V, ATTR_DIMMED, 0);
              				closePanelDisplayEnergyValue(); //Clear Panel 
							gl_uint_RunCheckDisplayEnergyValueFlag = 0 ;
							SetCtrlVal (Panels[RUN_CTRL_MENUE], RUN_CTRL_CHECKBOX_DISPL_ENER_V,gl_uint_RunCheckDisplayEnergyValueFlag);  
					  		SetCtrlAttribute (Panels[RUN_CTRL_MENUE], RUN_CTRL_CHECKBOX_DISPL_ENER_V, ATTR_DIMMED, 1);

						  	break;


						case RUNNING_MODE_SIS3150USB_DSP_LOAD_PROGRAM_TEST:
							SetCtrlAttribute (Panels[RUN_CTRL_MENUE], RUN_CTRL_STRING_USBTS_FILE_NAM, ATTR_DIMMED, 0);
			 		  		SetCtrlVal (Panels[RUN_CTRL_MENUE],RUN_CTRL_NOF_EVENT_READ,1);

 							closePanelDisplayRaw()  ;
							gl_uint_RunCheckDisplayRawFlag = 0 ;
							SetCtrlVal (Panels[RUN_CTRL_MENUE], RUN_CTRL_CHECKBOX_DISPL_RAW,gl_uint_RunCheckDisplayRawFlag);  
					  		SetCtrlAttribute (Panels[RUN_CTRL_MENUE], RUN_CTRL_CHECKBOX_DISPL_RAW, ATTR_DIMMED, 1);
							
              				closePanelDisplayEnergyValue(); //Clear Panel 
							gl_uint_RunCheckDisplayEnergyValueFlag = 0 ;
							SetCtrlVal (Panels[RUN_CTRL_MENUE], RUN_CTRL_CHECKBOX_DISPL_ENER_V,gl_uint_RunCheckDisplayEnergyValueFlag);  
					  		SetCtrlAttribute (Panels[RUN_CTRL_MENUE], RUN_CTRL_CHECKBOX_DISPL_ENER_V, ATTR_DIMMED, 1);

						  	break;

					} // end switch (gl_uint_RunReadoutMode)


					
					break;
			} // end switch (control)
		  	break;

	}
	return 0;
} // end function  ()







//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int SetDefaultDataFileName (void)
{   
int i, temp, status, select;
char tempFile[MAX_FILENAME_LEN];
int tempErr, dummy, okSema;
char *fileName ;

	GetProjectDir (gl_char_FilePathData);

	fileName   = Create_Entire_Stamp_Filename (gl_char_FilePathData, ".dat")  ;
	CopyString (gl_char_FileNameData, 0, fileName, 0, strlen(fileName));
    SetCtrlVal (Panels[RUN_CTRL_MENUE], RUN_CTRL_STRING_DATAFILE_NAME, gl_char_FileNameData);

//   if (select == VAL_EXISTING_FILE_SELECTED) {
//      SetMenuBarAttribute  (MenuBars[MENU_BAR], MENU_CONFIGURATION_SAVE, ATTR_DIMMED, OFF);
      		SetCtrlVal (Panels[RUN_CTRL_MENUE], RUN_CTRL_STRING_DATAFILE_NAME, gl_char_FileNameData);

//	  if (tempErr != FILE_ACCESS_OK) {
//         SetMenuBarAttribute  (MenuBars[MENU_BAR], MENU_CONFIGURATION_SAVE, ATTR_DIMMED, ON);
//         SetCtrlVal (Panels[MAIN], PANEL_STRING_CONFFILE_NAME, "error writing file ");
//	  }
//    }
  return 0;
}


//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 

/*---------------------------------------------------------------------------
appends to the directory path a timestamp filename
Dmm-dd-yyyyThh-mm-ss-.bod 
---------------------------------------------------------------------------*/

char *Create_Entire_Stamp_Filename (char *directory, char *extension)
{
    static int cviErr, i;
    static char fileName[MAX_PATHNAME_LENGTH];
    static char *timeString, *dateString;
    static char temp1,temp2;
    
    timeString=TimeStr ();    //get system time pointer
    dateString=DateStr ();    // get system date pointer
    CopyString (fileName, 0, directory, 0, strlen(directory));
    CopyString (fileName, strlen(fileName), "\\", 0, 1);
    CopyString (fileName, strlen(fileName), "D", 0, 1);
    CopyString (fileName, strlen(fileName), dateString, 0, 10);
    CopyString (fileName, strlen(fileName), "T", 0, 1);
    CopyString (fileName, strlen(fileName), timeString, 0, 8);
    CopyString (fileName, strlen(fileName), extension, 0, strlen(extension));
    //replace ":" by "-" to get a valid file-name
    for (i=2; i<strlen(fileName);i++)  //do not start at 0 since drive ":" must be kept
    if(fileName[i]==*":") fileName[i]=*"-";

    return fileName;
}





//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int ChangeDataFileName (void)
{   
int i, temp, status, select;
char tempFile[MAX_FILENAME_LEN];
int tempErr, dummy, okSema;
char *fileName ;


   GetProjectDir (gl_char_FilePathData);

	fileName   = Create_Entire_Stamp_Filename (gl_char_FilePathData, ".dat")  ;
//	CopyString (gl_char_FileNameData, 0, fileName, 0, strlen(fileName));

   select = FileSelectPopup (gl_char_FilePathData, fileName, "", 
											  "Define Data File Name", 
											  VAL_OK_BUTTON, 0, 1, 1, 1, 
											  gl_char_FileNameData);

      		SetCtrlVal (Panels[RUN_CTRL_MENUE], RUN_CTRL_STRING_DATAFILE_NAME, gl_char_FileNameData);


   if (select == VAL_EXISTING_FILE_SELECTED) {
//      SetMenuBarAttribute  (MenuBars[MENU_BAR], MENU_CONFIGURATION_SAVE, ATTR_DIMMED, OFF);
      		SetCtrlVal (Panels[RUN_CTRL_MENUE], RUN_CTRL_STRING_DATAFILE_NAME, gl_char_FileNameData);

//	  if (tempErr != FILE_ACCESS_OK) {
//         SetMenuBarAttribute  (MenuBars[MENU_BAR], MENU_CONFIGURATION_SAVE, ATTR_DIMMED, ON);
//         SetCtrlVal (Panels[MAIN], PANEL_STRING_CONFFILE_NAME, "error writing file ");
//	  }
    }
  return 0;
}


//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int ChangeSIS3150USB_TS_ReadoutLoaderFileName (void)
{   
int i, temp, status, select;
char tempFile[MAX_FILENAME_LEN];
int tempErr, dummy, okSema;
char *fileName ;

	GetProjectDir (gl_char_FilePathConf);
	select = FileSelectPopup (gl_char_FilePathConf, NORMAL_SIS3150USB_TS_READOUT_LOADER_FILE, "ldr", 
							  "Select SIS3150USB TigerSharc VME Readout Loader File", 
							  VAL_SELECT_BUTTON, 0, 1, 1, 0, 
							  gl_char_FileNameLoaderSIS3150USB_TS);

	SetCtrlVal (Panels[RUN_CTRL_MENUE], RUN_CTRL_STRING_USBTS_FILE_NAM, gl_char_FileNameLoaderSIS3150USB_TS);

  return 0;
}



//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int OpenEventDataFile (void)
{   

int written ;
unsigned int dataFormat ;	
unsigned int temp ;	
unsigned int gateheaderlength ;	
unsigned int sisdevice ;	


//	SetCtrlVal (Panels[RUN_CTRL_MENUE], RUN_CTRL_STRING_DATAFILE_NAME, gl_char_FileNameData);
	SetCtrlVal (Panels[RUN_CTRL_MENUE], RUN_CTRL_STRING_DATAFILE_NAME, gl_char_FileNameData);



	gl_FILE_DataEvenFilePointer=fopen(gl_char_FileNameData,"wb");

  // File Number
	gl_uint_DataEvent_FileCounter = 0x1 ;
    written=fwrite(&gl_uint_DataEvent_FileCounter,0x4,0x1,gl_FILE_DataEvenFilePointer); // write one  uint word
	gl_uint_DataEvent_LWordCounter = written ;

  // Data Format Mode
	dataFormat = 1 ;	 // 
    written=fwrite(&dataFormat,0x4,0x1,gl_FILE_DataEvenFilePointer); // write one  uint word
	gl_uint_DataEvent_LWordCounter = gl_uint_DataEvent_LWordCounter + written ;

  // Number of modules
    written=fwrite(&gl_uint_NoOfModulesRun,0x4,0x1,gl_FILE_DataEvenFilePointer); // write one  uint word
	gl_uint_DataEvent_LWordCounter = gl_uint_DataEvent_LWordCounter + written ;


  // sampling parameters (clock)
	temp =   (gl_uint_SIS3820ClockModeConf << 16) +  (gl_uint_SIS3320ClockModeConf) ;
    written=fwrite(&temp,0x4,0x1,gl_FILE_DataEvenFilePointer); // write one  uint word
	gl_uint_DataEvent_LWordCounter = gl_uint_DataEvent_LWordCounter + written ;

  // SIS3320_PRETRIGGER_ACTIVEGATE_WINDOW_ALL_ADC
	temp =   ((gl_uint_MainGatePreTriggerDelay << 16) & 0x03ff0000) +  (gl_uint_MainGateLength & 0x3ff) ;
    written=fwrite(&temp,0x4,0x1,gl_FILE_DataEvenFilePointer); // write one  uint word
	gl_uint_DataEvent_LWordCounter = gl_uint_DataEvent_LWordCounter + written ;

  // Raw data gl_uint_RawDataSampleMode
	temp =   gl_uint_RawDataSampleMode ;
    written=fwrite(&temp,0x4,0x1,gl_FILE_DataEvenFilePointer); // write one  uint word
	gl_uint_DataEvent_LWordCounter = gl_uint_DataEvent_LWordCounter + written ;

  // Raw data
	temp =   ((gl_uint_RawSample_Length << 16) & 0x03ff0000) +  (gl_uint_RawSample_StartIndex & 0x3ff)  ; ;
    written=fwrite(&temp,0x4,0x1,gl_FILE_DataEvenFilePointer); // write one  uint word
	gl_uint_DataEvent_LWordCounter = gl_uint_DataEvent_LWordCounter + written ;


  // // SIS3320_ACCUMULATOR_GATE1
	temp =   ((gl_uint_Gate1_Length << 16) & 0x01ff0000) +  (gl_uint_Gate1_StartIndex & 0x3ff)  ;
    written=fwrite(&temp,0x4,0x1,gl_FILE_DataEvenFilePointer); // write one  uint word
	gl_uint_DataEvent_LWordCounter = gl_uint_DataEvent_LWordCounter + written ;


  // // SIS3320_ACCUMULATOR_GATE2
	temp =   ((gl_uint_Gate2_Length << 16) & 0x01ff0000) +  (gl_uint_Gate2_StartIndex & 0x3ff)  ;
    written=fwrite(&temp,0x4,0x1,gl_FILE_DataEvenFilePointer); // write one  uint word
	gl_uint_DataEvent_LWordCounter = gl_uint_DataEvent_LWordCounter + written ;


  // // SIS3320_ACCUMULATOR_GATE3
	temp =   ((gl_uint_Gate3_Length << 16) & 0x01ff0000) +  (gl_uint_Gate3_StartIndex & 0x3ff)  ;
    written=fwrite(&temp,0x4,0x1,gl_FILE_DataEvenFilePointer); // write one  uint word
	gl_uint_DataEvent_LWordCounter = gl_uint_DataEvent_LWordCounter + written ;


  // // SIS3320_ACCUMULATOR_GATE4
	temp =   ((gl_uint_Gate4_Length << 16) & 0x01ff0000) +  (gl_uint_Gate4_StartIndex & 0x3ff)  ;
    written=fwrite(&temp,0x4,0x1,gl_FILE_DataEvenFilePointer); // write one  uint word
	gl_uint_DataEvent_LWordCounter = gl_uint_DataEvent_LWordCounter + written ;


  // // SIS3320_ACCUMULATOR_GATE5
	temp =   ((gl_uint_Gate5_Length << 16) & 0x01ff0000) +  (gl_uint_Gate5_StartIndex & 0x3ff)  ;
    written=fwrite(&temp,0x4,0x1,gl_FILE_DataEvenFilePointer); // write one  uint word
	gl_uint_DataEvent_LWordCounter = gl_uint_DataEvent_LWordCounter + written ;


  // // SIS3320_ACCUMULATOR_GATE6
	temp =   ((gl_uint_Gate6_Length << 16) & 0x01ff0000) +  (gl_uint_Gate6_StartIndex & 0x3ff)  ;
    written=fwrite(&temp,0x4,0x1,gl_FILE_DataEvenFilePointer); // write one  uint word
	gl_uint_DataEvent_LWordCounter = gl_uint_DataEvent_LWordCounter + written ;


  // // SIS3320_ACCUMULATOR_GATE7
	temp =   ((gl_uint_Gate7_Length << 16) & 0x01ff0000) +  (gl_uint_Gate7_StartIndex & 0x3ff)  ;
    written=fwrite(&temp,0x4,0x1,gl_FILE_DataEvenFilePointer); // write one  uint word
	gl_uint_DataEvent_LWordCounter = gl_uint_DataEvent_LWordCounter + written ;


  // // SIS3320_ACCUMULATOR_GATE8
	temp =   ((gl_uint_Gate8_Length << 16) & 0x01ff0000) +  (gl_uint_Gate8_StartIndex & 0x3ff)  ;
    written=fwrite(&temp,0x4,0x1,gl_FILE_DataEvenFilePointer); // write one  uint word
	gl_uint_DataEvent_LWordCounter = gl_uint_DataEvent_LWordCounter + written ;


    
   // reserved 1
	if (gl_uint_SIS3302_FlagConf[0] == 0)   { 
		gateheaderlength	 = 10  ; // Timestamp/Header, Peakhigh, Integrals of Gates, Trailer
		sisdevice       	 = 0x3320  ;  
	}
	else {
   		GetCtrlVal (Panels[SAMPLE_PARA_CONF],SAMPL_CONF_ACCU_DATA_FORMAT, &temp);
		sisdevice       	 = 0x3302  ;  
		if (temp == 0) { // 6-Accumulator mode
			gateheaderlength	 = 10  ; // Timestamp/Header, Peakhigh, Integrals of Gates, Trailer
   		}
		else {
			gateheaderlength	 = 12  ; // Timestamp/Header, Peakhigh, Integrals of Gates, Trailer
   		}
   	}

	//temp =   0  ;  event length
    written=fwrite(&gateheaderlength,0x4,0x1,gl_FILE_DataEvenFilePointer); // write one  uint word
	gl_uint_DataEvent_LWordCounter = gl_uint_DataEvent_LWordCounter + written ;


  
  // sisdevice  
	temp =   sisdevice ;
    written=fwrite(&temp,0x4,0x1,gl_FILE_DataEvenFilePointer); // write one  uint word
	gl_uint_DataEvent_LWordCounter = gl_uint_DataEvent_LWordCounter + written ;

  // reserved 3
	temp =   0 ;
    written=fwrite(&temp,0x4,0x1,gl_FILE_DataEvenFilePointer); // write one  uint word
	gl_uint_DataEvent_LWordCounter = gl_uint_DataEvent_LWordCounter + written ;

  // reserved 4
	temp =   0 ;
    written=fwrite(&temp,0x4,0x1,gl_FILE_DataEvenFilePointer); // write one  uint word
	gl_uint_DataEvent_LWordCounter = gl_uint_DataEvent_LWordCounter + written ;

  // reserved 5
	temp =   0 ;
    written=fwrite(&temp,0x4,0x1,gl_FILE_DataEvenFilePointer); // write one  uint word
	gl_uint_DataEvent_LWordCounter = gl_uint_DataEvent_LWordCounter + written ;

  // reserved 6
	temp =   0 ;
    written=fwrite(&temp,0x4,0x1,gl_FILE_DataEvenFilePointer); // write one  uint word
	gl_uint_DataEvent_LWordCounter = gl_uint_DataEvent_LWordCounter + written ;

	gl_uint_DataEvent_OpenFlag    = 1   ; // Open


 	return 0;

}



//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int WriteBufferHeaderCounterNofChannelToDataFile (unsigned int buffer_no,unsigned int nof_events, unsigned int event_length)
{   
int written ;
int data ;
  //header
	data = FILE_FORMAT_EVENT_HEADER ;    
    written=fwrite(&data,0x4,0x1,gl_FILE_DataEvenFilePointer); // write one  uint word
	gl_uint_DataEvent_LWordCounter = gl_uint_DataEvent_LWordCounter + written ;
  //Buffer No
    written=fwrite(&buffer_no,0x4,0x1,gl_FILE_DataEvenFilePointer); // write one  uint word
	gl_uint_DataEvent_LWordCounter = gl_uint_DataEvent_LWordCounter + written ;
  //nof events
    written=fwrite(&nof_events,0x4,0x1,gl_FILE_DataEvenFilePointer); // write one  uint word
	gl_uint_DataEvent_LWordCounter = gl_uint_DataEvent_LWordCounter + written ;
  //event length
    written=fwrite(&event_length,0x4,0x1,gl_FILE_DataEvenFilePointer); // write one  uint word
	gl_uint_DataEvent_LWordCounter = gl_uint_DataEvent_LWordCounter + written ;

	//gl_uint_DataEvent_RunFile_EventChannelSize =  event_length;
	//gl_uint_DataEvent_RunFile_EventSize = nof_channels * gl_uint_DataEvent_RunFile_EventChannelSize ;
 	
 	return 0;

}




//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int WriteTS_EventsToDataFile (unsigned int* memory_data_array, unsigned int nof_write_length_lwords)
{   
int nof_write_elements ;
int written ;
int data ;
char messages_buffer[256] ;           

// gl_uint_DataEvent_RunFile_EvenSize : length 

		nof_write_elements = nof_write_length_lwords ;
		written=fwrite(memory_data_array,0x4,nof_write_elements,gl_FILE_DataEvenFilePointer); // write 3 uint value
		gl_uint_DataEvent_LWordCounter = gl_uint_DataEvent_LWordCounter + written  ;
		if(nof_write_elements != written) { 
	        SetPanelPos(Panels[MODULE_MESS_SYSTEM],60,400)  ;   // y, x
			DisplayPanel (Panels[MODULE_MESS_SYSTEM]);
    		sprintf (messages_buffer, "Data File Write Error in  WriteEventToDataFile()  \n");
    		write_system_messages (messages_buffer, PRINT_DATE_YES)	   ;
		 }

 	return 0;

}


//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int CloseEventDataFile (void)
{   
int written ;
int data ;

	data = FILE_FORMAT_EOF_TRAILER ;    
    written=fwrite(&data,0x4,0x1,gl_FILE_DataEvenFilePointer); // write one  uint word
	gl_uint_DataEvent_LWordCounter = gl_uint_DataEvent_LWordCounter + written ;
    fclose(gl_FILE_DataEvenFilePointer);
	gl_uint_DataEvent_OpenFlag    = 0   ; // Close
 	return 0;
}






//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int CVICALLBACK CB_RunStartAcq (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int CviErr, i,j;
	int error;
	int status;
	switch (event)
		{
		case EVENT_COMMIT:

 			SystemConfiguration() ;

			// open data file
		  	SetCtrlAttribute (Panels[RUN_CTRL_MENUE], RUN_CTRL_CHECKBOX_WR_DATA, ATTR_DIMMED, 1);
		  	if (gl_uint_RunCheckWrDataToFileFlag == 1)  {  // on
   	 			OpenEventDataFile()  ;    
	   	   	}

			gl_uint_system_status = SYSTEM_STATUS_MODULES_RUNNING ;
            CheckSystemStatus () ;


			SetCtrlAttribute (Panels[RUN_CTRL_MENUE], RUN_CTRL_STARTBUTTOM, ATTR_VISIBLE, 0);
			SetCtrlAttribute (Panels[RUN_CTRL_MENUE], RUN_CTRL_STOPBUTTOM, ATTR_VISIBLE, 1);
			gl_uint_RunStopStatusFlag = 1 ;

//            DisableTaskSwitching();
//             SetPanelAttribute (Panels[RUN_CTRL_MENUE], ATTR_WINDOW_ZOOM, VAL_MAXIMIZE);

		
			// start one second timer
			gl_uint_RunEventOldCounter  = 0 ;
			gl_unit_RunOneSecondCounter = 0 ;
   			gl_uint_RunEventCounter = 0 ;
		//	gl_uint_DataEvent_LWordCounter = 0 ;
			SetCtrlVal (Panels[RUN_CTRL_MENUE], RUN_CTRL_RUN_EVENT_RATE, 0.0);
			SetCtrlVal (Panels[RUN_CTRL_MENUE], RUN_CTRL_RUN_EVENT_RATE_A, 0.0);
			SetCtrlVal (Panels[RUN_CTRL_MENUE], RUN_CTRL_RUN_EVENT_SECOND, 0);
			SetCtrlVal (Panels[RUN_CTRL_MENUE], RUN_CTRL_RUN_EVENT_MBYTE, 0.0);
			SetCtrlVal (Panels[RUN_CTRL_MENUE], RUN_CTRL_RUN_EVENT_NUMBER, gl_uint_RunEventCounter);
			// later
			//SetCtrlAttribute (Panels[RUN_CTRL_MENUE], RUN_CTRL_ONE_SECOND_TICK, ATTR_ENABLED, ON);

   			gl_uint_DataFileRunEventCounter = 0 ;


			if (gl_uint_RunDisableStartClearFlag == 0) {
				clear_all_spectrum_histograms() ;	 // Clear Energy Spectren
				resetDiagPatternArraysAndScaling() ; // Clear Diagonstic Pattern 
			}

			// Clear Timestamp
			if (gl_uint_SIS3820EnableConf == 1)  {
				if ((error = sub_vme_A32D32_write(gl_uint_SIS3820AddrConf + SIS3820CLOCK_KEY_CLR_TIMESTAMP,0x0 )) != 0) { 
					sisVME_ErrorHandling (error, gl_uint_SIS3820AddrConf + SIS3820CLOCK_KEY_CLR_TIMESTAMP, "sub_vme_A32D32_write"); 
 		//			return -1;
				}
			}
			SetCtrlAttribute (Panels[RUN_CTRL_MENUE], RUN_CTRL_ONE_SECOND_TICK, ATTR_ENABLED, ON);
			switch (gl_uint_SIS3320_Trigger_Mode_Source_ModeConf)				
			{
	  			case  0: // asynch Trigger Mode
 		     		SetMenuBarAttribute  (MenuBars[RUNCTRL_MENU_BAR], MENUCTRLRU_TEST_TRIGGER, ATTR_DIMMED, ON);
					break;
	  			case  1: // synch Trigger Mode / external Lemo IN3 Trigger 
      				SetMenuBarAttribute  (MenuBars[RUNCTRL_MENU_BAR], MENUCTRLRU_TEST_TRIGGER, ATTR_DIMMED, OFF);
					break;
			} // end switch  		

			
  			switch (gl_uint_RunReadoutMode) {

				case RUNNING_MODE_PC_SINGLE_EVENT:
					RunPC_SingleEventAquisition() ;    
					break ;			

				case RUNNING_MODE_PC_MULTI_EVENT_SINGLE_BUFFER:
					RunPC_SIS3320LLNL_MultiEvent_SingleBuffer_Aquisition() ;
					break ;			

				case RUNNING_MODE_PC_MULTI_EVENT_DOUBLE_BUFFER:
					RunPC_SIS3320LLNL_MultiEvent_DoubleBuffer_Aquisition() ;    
					break ;			
				
				case RUNNING_MODE_SIS3150USB_DSP_LOAD_PROGRAM_TEST:
					RunPC_SIS3150USB_DSP_Load_Program() ;    
					break ;			

			
			} // end of switch

	do {
       	ProcessSystemEvents ();    /* danach mus status  abgefragt werden */
   	}while (    (gl_uint_RunStopStatusFlag == AQC_RUN_STATUS)  
            && ((gl_uint_RunEventCounter < gl_uint_RunMaxEventCounter ) || (gl_uint_RunCheckStopEventsFlag == 0) )
            && ((gl_unit_RunOneSecondCounter < gl_uint_RunMaxSecondsCounter ) || (gl_uint_RunCheckStopTimeFlag == 0) ) ) ; 


		   
		  // disable second timer
			SetCtrlAttribute (Panels[RUN_CTRL_MENUE], RUN_CTRL_ONE_SECOND_TICK, ATTR_ENABLED, OFF);
		  	SetCtrlAttribute (Panels[RUN_CTRL_MENUE], RUN_CTRL_CHECKBOX_WR_DATA, ATTR_DIMMED, 0);
			SetCtrlAttribute (Panels[RUN_CTRL_MENUE], RUN_CTRL_ONE_M_SECOND_TICK, ATTR_ENABLED, OFF);
		  // cloese data file
		    if (gl_uint_RunCheckWrDataToFileFlag == 1)  {  // on
   	 		  CloseEventDataFile()  ;    
	   	     }


		  // display Event Informaton
			displayRunEventInformations();

		  // disable stop buttom / enable start button (neccessary if stoped with MaxEventNumber 
			SetCtrlAttribute (Panels[RUN_CTRL_MENUE], RUN_CTRL_STARTBUTTOM, ATTR_VISIBLE, 1);
			SetCtrlAttribute (Panels[RUN_CTRL_MENUE], RUN_CTRL_STOPBUTTOM, ATTR_VISIBLE, 0);
			gl_uint_RunStopStatusFlag = 0 ;

			gl_uint_system_status = SYSTEM_STATUS_MODULES_CONFIGURED ;
            CheckSystemStatus () ;
			break;
		}
//            EnableTaskSwitching();
//            SetPanelAttribute (Panels[RUN_CTRL_MENUE], ATTR_WINDOW_ZOOM, VAL_NO_ZOOM);
 	return 0;
}




//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int CVICALLBACK CB_RunStopAcq (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int CviErr, i;
	int status;

	switch (event)
		{
		case EVENT_COMMIT:
//	if ((MenuBars[MAIN_MENU_BAR] = LoadMenuBar (Panels[MAIN], "sis3300_greta_uir.uir", MENU)) < 0) return -1;
// 	LoadMenuBar (Panels[MAIN], "sis3300_greta_uir.uir", MENU);
			SetCtrlAttribute (Panels[RUN_CTRL_MENUE], RUN_CTRL_STARTBUTTOM, ATTR_VISIBLE, 1);
			SetCtrlAttribute (Panels[RUN_CTRL_MENUE], RUN_CTRL_STOPBUTTOM, ATTR_VISIBLE, 0);
			gl_uint_RunStopStatusFlag = 0 ;
	 // wait for stop !!!
			gl_uint_system_status = SYSTEM_STATUS_MODULES_CONFIGURED ;  // prepared for stoping !!
      //      CheckSystemStatus () ;
			SetCtrlAttribute (Panels[RUN_CTRL_MENUE], RUN_CTRL_ONE_M_SECOND_TICK, ATTR_ENABLED, OFF);
 			SetCtrlVal (Panels[RUN_CTRL_MENUE], RUN_CTRL_LED_LOOP, OFF);
			SetCtrlAttribute (Panels[RUN_CTRL_MENUE], RUN_CTRL_ONE_SECOND_TICK, ATTR_ENABLED, OFF);
      		SetMenuBarAttribute  (MenuBars[RUNCTRL_MENU_BAR], MENUCTRLRU_TEST_TRIGGER, ATTR_DIMMED, ON);

			
			break;
		}
	return 0;
}
		  

/****************************************************************************************/
/*                                                                                      */
/*                                                                                      */
/*     functions                                                                        */
/*                                                                                      */
/****************************************************************************************/

//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
//Just for test of first module in chain

int RunPC_SingleEventAquisition (void)
{
	unsigned int  first_event_length_lwords  ;
	unsigned int  event_length_lwords, max_events, address_threshold_value ;
	int i,j,k, temp2 ;
	int module_index, event_index, channel_index ;
	int error ;
	unsigned int poll_counter ;
	unsigned int addr, data, data_rd ;
	unsigned int plot_size ;
	unsigned int  dma_request_no_of_words, dma_got_no_of_words ;
	unsigned int  event_length ;
	unsigned int  module_buffer_offset ;
	unsigned int  uint_timestamp_upper, uint_timestamp_lower ;
	unsigned int  sum1, sum2 ;

	unsigned int  uint_energy ;
	int sign_diff ;
	int sign_max,sign_min  ;	//    
	float float_factor;

	unsigned int  find_from_index1 ;
	unsigned int  find_from_index2 ;
	unsigned int  find_average ;
	
 	int *int_filesaveModuleEvent_ptr    ;
 	int *int_displayEnergyValueADC_ptr    ;

	unsigned int  uint_trigger_flags;
	unsigned int  local_CountofTriggerEventBased;
	unsigned int  local_PileupFlag;

	unsigned int  energy_mode ;
	unsigned int  nof_energy_values ;
	unsigned int  energy_max_index ;
    	 
//	signed int  sign_integral ;
 	unsigned int  gate1_sum, gate2_sum, gate3_sum, gate4_sum;
 	unsigned int  gate5_sum, gate6_sum, gate7_sum, gate8_sum;
 	signed int  gate_difference ;

	//unsigned int  gl_uint_Gate1_Length     ;
	float float_Gate1_sum, float_Gate2_sum, float_Gate3_sum;
	float float_N1, float_N2, float_N3;
	float float_scaled_Gate2_sum, float_scaled_Gate3_sum;

	unsigned int  temp;
	int check_on ;
	unsigned int  raw_buffer_length_index;


// SIS3302 modification
	if (gl_uint_SIS3302_FlagConf[0] == 0)   { 
		event_length_lwords	 = 10  ; // Timestamp/Header, Peakhigh, Integrals of Gates, Trailer
	}
	else {
   		GetCtrlVal (Panels[SAMPLE_PARA_CONF],SAMPL_CONF_ACCU_DATA_FORMAT, &temp);
		if (temp == 0) { // 6-Accumulator mode
			event_length_lwords	 = 10  ; // Timestamp/Header, Peakhigh, Integrals of Gates, Trailer
   		}
		else {
			event_length_lwords	 = 12  ; // Timestamp/Header, Peakhigh, Integrals of Gates, Trailer
   		}
   	}
	raw_buffer_length_index = event_length_lwords - 1 ;
	
	if (gl_uint_RawDataSampleMode == 1) { // always raw data 
		first_event_length_lwords	 = event_length_lwords + (gl_uint_RawSample_Length>>1) ;
		event_length_lwords	         = event_length_lwords + (gl_uint_RawSample_Length>>1) ;
 	}
	if (gl_uint_RawDataSampleMode == 2) { // only first event 
		first_event_length_lwords	 = event_length_lwords + (gl_uint_RawSample_Length>>1) ;
		event_length_lwords	 = event_length_lwords   ;
 	}

	// calculation of max events to use only one 8MByte Sample Buffer (only one page)
 	max_events = 0x200000 / (event_length_lwords) ;  // 8MByte (2MLwors) / Event_length
 	max_events = 1 ;  // 8MByte (2MLwors) / Event_length


    address_threshold_value = (max_events * event_length_lwords) ; // valid if halfful !!
  	SetCtrlVal (Panels[RUN_CTRL_MENUE],RUN_CTRL_NOF_EVENT_READ,max_events);

	// address threshold flag
	data = address_threshold_value ;		//  
	for (module_index=0;module_index<gl_uint_NoOfModulesRun;module_index++) {
	//for (module_index=0;module_index<1;module_index++) {
		addr = gl_uint_ModAddrRun[module_index] + SIS3320_END_ADDRESS_THRESHOLD_ALL_ADC ; 
		if ((error = sub_vme_A32D32_write(addr,data )) != 0) { 
			sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_write")   ;
			gl_uint_system_status = SYSTEM_STATUS_MODULES_NOT_READY ;
			return -1 ;
		}
	}


// Readout Loop  */
	do {
		addr = gl_uint_ModAddrRun[0] + SIS3320_KEY_DISARM_AND_ARM_BANK1 ; 
		if ((error = sub_vme_A32D32_write(addr,0x0 )) != 0) { 
			sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_write")   ;
			gl_uint_system_status = SYSTEM_STATUS_MODULES_NOT_READY ;
			return -1 ;
		}


		// wait for address threshold flag
		poll_counter = 0 ;
		addr = gl_uint_ModAddrRun[0] + SIS3320_ACQUISTION_CONTROL ; 
		do {
			if ((error = sub_vme_A32D32_read(addr,&data_rd )) != 0) { 
				sisVME_ErrorHandling (error, gl_uint_ModAddrRun[0], "sub_vme_A32D32_read"); 
				return -1;
			}
			poll_counter++;
			if (poll_counter == 100) {
    			ProcessSystemEvents ();
				poll_counter = 0 ;
    		}
		} while (((data_rd & 0x80000) != 0x80000) && (gl_uint_RunStopStatusFlag == AQC_RUN_STATUS))  ;


		addr = gl_uint_ModAddrRun[0] + SIS3320_KEY_DISARM ; 
		if ((error = sub_vme_A32D32_write(addr,0x0 )) != 0) { 
			sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_write")   ;
			gl_uint_system_status = SYSTEM_STATUS_MODULES_NOT_READY ;
			return -1 ;
		}


		addr = gl_uint_ModAddrRun[0] + SIS3320_ACTUAL_SAMPLE_ADDRESS_ADC1 ; 
		if ((error = sub_vme_A32D32_read(addr,&gl_uint_end_sample_address[0] )) != 0) { 
			sisVME_ErrorHandling (error, gl_uint_ModAddrRun[0], "sub_vme_A32D32_read"); 
			return -1;
		}

		addr = gl_uint_ModAddrRun[0] + SIS3320_ACTUAL_SAMPLE_ADDRESS_ADC2 ; 
		if ((error = sub_vme_A32D32_read(addr,&gl_uint_end_sample_address[1] )) != 0) { 
			sisVME_ErrorHandling (error, gl_uint_ModAddrRun[0], "sub_vme_A32D32_read"); 
			return -1;
		}

		addr = gl_uint_ModAddrRun[0] + SIS3320_ACTUAL_SAMPLE_ADDRESS_ADC3 ; 
		if ((error = sub_vme_A32D32_read(addr,&gl_uint_end_sample_address[2] )) != 0) { 
			sisVME_ErrorHandling (error, gl_uint_ModAddrRun[0], "sub_vme_A32D32_read"); 
			return -1;
		}

		addr = gl_uint_ModAddrRun[0] + SIS3320_ACTUAL_SAMPLE_ADDRESS_ADC4 ; 
		if ((error = sub_vme_A32D32_read(addr,&gl_uint_end_sample_address[3] )) != 0) { 
			sisVME_ErrorHandling (error, gl_uint_ModAddrRun[0], "sub_vme_A32D32_read"); 
			return -1;
		}

		addr = gl_uint_ModAddrRun[0] + SIS3320_ACTUAL_SAMPLE_ADDRESS_ADC5 ; 
		if ((error = sub_vme_A32D32_read(addr,&gl_uint_end_sample_address[4] )) != 0) { 
			sisVME_ErrorHandling (error, gl_uint_ModAddrRun[0], "sub_vme_A32D32_read"); 
			return -1;
		}

		addr = gl_uint_ModAddrRun[0] + SIS3320_ACTUAL_SAMPLE_ADDRESS_ADC6 ; 
		if ((error = sub_vme_A32D32_read(addr,&gl_uint_end_sample_address[5] )) != 0) { 
			sisVME_ErrorHandling (error, gl_uint_ModAddrRun[0], "sub_vme_A32D32_read"); 
			return -1;
		}

		addr = gl_uint_ModAddrRun[0] + SIS3320_ACTUAL_SAMPLE_ADDRESS_ADC7 ; 
		if ((error = sub_vme_A32D32_read(addr,&gl_uint_end_sample_address[6] )) != 0) { 
			sisVME_ErrorHandling (error, gl_uint_ModAddrRun[0], "sub_vme_A32D32_read"); 
			return -1;
		}

		addr = gl_uint_ModAddrRun[0] + SIS3320_ACTUAL_SAMPLE_ADDRESS_ADC8 ; 
		if ((error = sub_vme_A32D32_read(addr,&gl_uint_end_sample_address[7] )) != 0) { 
			sisVME_ErrorHandling (error, gl_uint_ModAddrRun[0], "sub_vme_A32D32_read"); 
			return -1;
		}

// readout	   	
// ADC 1
		if (gl_uint_end_sample_address[0] != 0) {
	   		addr = gl_uint_ModAddrRun[0] + SIS3320_ADC1_OFFSET  ;
	  		error = sub_vme_A32MBLT64_read(addr, &gl_dma_rd_adc1_buffer[0],  (gl_uint_end_sample_address[0] & 0x3ffffc)>>1, &dma_got_no_of_words) ;
			if (error != 0x0) { // vme error
				sisVME_ErrorHandling (error, addr, "sub_vme_A32MBLT64_read")   ;
			}
		}

// ADC 2
		if (gl_uint_end_sample_address[1] != 0) {
	   		addr = gl_uint_ModAddrRun[0] + SIS3320_ADC2_OFFSET  ;
	  		error = sub_vme_A32MBLT64_read(addr, &gl_dma_rd_adc2_buffer[0],  (gl_uint_end_sample_address[1] & 0x3ffffc)>>1, &dma_got_no_of_words) ;
			if (error != 0x0) { // vme error
				sisVME_ErrorHandling (error, addr, "sub_vme_A32MBLT64_read")   ;
			}
		}

// ADC 3
		if (gl_uint_end_sample_address[2] != 0) {
	   		addr = gl_uint_ModAddrRun[0] + SIS3320_ADC3_OFFSET  ;
	  		error = sub_vme_A32MBLT64_read(addr, &gl_dma_rd_adc3_buffer[0],  (gl_uint_end_sample_address[2] & 0x3ffffc)>>1, &dma_got_no_of_words) ;
			if (error != 0x0) { // vme error
				sisVME_ErrorHandling (error, addr, "sub_vme_A32MBLT64_read")   ;
			}
		}

// ADC 4
		if (gl_uint_end_sample_address[3] != 0) {
	   		addr = gl_uint_ModAddrRun[0] + SIS3320_ADC4_OFFSET  ;
	  		error = sub_vme_A32MBLT64_read(addr, &gl_dma_rd_adc4_buffer[0],  (gl_uint_end_sample_address[3] & 0x3ffffc)>>1, &dma_got_no_of_words) ;
			if (error != 0x0) { // vme error
				sisVME_ErrorHandling (error, addr, "sub_vme_A32MBLT64_read")   ;
			}
		}

// ADC 5
		if (gl_uint_end_sample_address[4] != 0) {
	   		addr = gl_uint_ModAddrRun[0] + SIS3320_ADC5_OFFSET  ;
	  		error = sub_vme_A32MBLT64_read(addr, &gl_dma_rd_adc5_buffer[0],  (gl_uint_end_sample_address[4] & 0x3ffffc)>>1, &dma_got_no_of_words) ;
			if (error != 0x0) { // vme error
				sisVME_ErrorHandling (error, addr, "sub_vme_A32MBLT64_read")   ;
			}
		}

// ADC 6
		if (gl_uint_end_sample_address[5] != 0) {
	   		addr = gl_uint_ModAddrRun[0] + SIS3320_ADC6_OFFSET  ;
	  		error = sub_vme_A32MBLT64_read(addr, &gl_dma_rd_adc6_buffer[0],  (gl_uint_end_sample_address[5] & 0x3ffffc)>>1, &dma_got_no_of_words) ;
			if (error != 0x0) { // vme error
				sisVME_ErrorHandling (error, addr, "sub_vme_A32MBLT64_read")   ;
			}
		}

// ADC 7
		if (gl_uint_end_sample_address[6] != 0) {
	   		addr = gl_uint_ModAddrRun[0] + SIS3320_ADC7_OFFSET  ;
	  		error = sub_vme_A32MBLT64_read(addr, &gl_dma_rd_adc7_buffer[0],  (gl_uint_end_sample_address[6] & 0x3ffffc)>>1, &dma_got_no_of_words) ;
			if (error != 0x0) { // vme error
				sisVME_ErrorHandling (error, addr, "sub_vme_A32MBLT64_read")   ;
			}
		}

// ADC 8
		if (gl_uint_end_sample_address[7] != 0) {
	   		addr = gl_uint_ModAddrRun[0] + SIS3320_ADC8_OFFSET  ;
	  		error = sub_vme_A32MBLT64_read(addr, &gl_dma_rd_adc8_buffer[0],  (gl_uint_end_sample_address[7] & 0x3ffffc)>>1, &dma_got_no_of_words) ;
			if (error != 0x0) { // vme error
				sisVME_ErrorHandling (error, addr, "sub_vme_A32MBLT64_read")   ;
			}
		}

// display of the EventDataInformations
		if (gl_uint_end_sample_address[0] != 0) {
      		if ((gl_uint_DisplayRawAdcShowChoose == 0) || (gl_uint_DisplayRawAdcShowChoose == 1)) {	
				displayEventDataInformation(gl_dma_rd_adc1_buffer)  ;
			}
		}
		if (gl_uint_end_sample_address[1] != 0) {
      		if ((gl_uint_DisplayRawAdcShowChoose == 0) || (gl_uint_DisplayRawAdcShowChoose == 2)) {	
				displayEventDataInformation(gl_dma_rd_adc2_buffer)  ;
			}
		}
		if (gl_uint_end_sample_address[2] != 0) {
      		if ((gl_uint_DisplayRawAdcShowChoose == 0) || (gl_uint_DisplayRawAdcShowChoose == 3)) {	
				displayEventDataInformation(gl_dma_rd_adc3_buffer)  ;
			}
		}
		if (gl_uint_end_sample_address[3] != 0) {
      		if ((gl_uint_DisplayRawAdcShowChoose == 0) || (gl_uint_DisplayRawAdcShowChoose == 4)) {	
				displayEventDataInformation(gl_dma_rd_adc4_buffer)  ;
			}
		}
		if (gl_uint_end_sample_address[4] != 0) {
      		if ((gl_uint_DisplayRawAdcShowChoose == 0) || (gl_uint_DisplayRawAdcShowChoose == 5)) {	
				displayEventDataInformation(gl_dma_rd_adc5_buffer)  ;
			}
		}
		if (gl_uint_end_sample_address[5] != 0) {
      		if ((gl_uint_DisplayRawAdcShowChoose == 0) || (gl_uint_DisplayRawAdcShowChoose == 6)) {	
				displayEventDataInformation(gl_dma_rd_adc6_buffer)  ;
			}
		}
		if (gl_uint_end_sample_address[6] != 0) {
      		if ((gl_uint_DisplayRawAdcShowChoose == 0) || (gl_uint_DisplayRawAdcShowChoose == 7)) {	
				displayEventDataInformation(gl_dma_rd_adc7_buffer)  ;
			}
		}
		if (gl_uint_end_sample_address[7] != 0) {
      		if ((gl_uint_DisplayRawAdcShowChoose == 0) || (gl_uint_DisplayRawAdcShowChoose == 8)) {	
				displayEventDataInformation(gl_dma_rd_adc8_buffer)  ;
			}
		}

// display raw data

// 		  	SetCtrlVal (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_TRAILER,(buffer_ptr[9] & 0xffffffff));

		GetCtrlVal (Panels[PANEL_DISPLAY_RAW],PANEL_RAW_CHECKBOX_DELETE_DISAB,&check_on);  //Show in panel Configuration

 		if (check_on == 0) { deleteRawGraph(); } 

		if (gl_uint_RunCheckDisplayRawFlag == 1)  {   ; // on

		
		
			if ((gl_uint_end_sample_address[0] != 0) && ( (gl_dma_rd_adc1_buffer[raw_buffer_length_index] & 0xffff0000) == 0xdada0000) ) {
      			if ((gl_uint_DisplayRawAdcShowChoose == 0) || (gl_uint_DisplayRawAdcShowChoose == 1)) {	
					displayEventAdcRawData((gl_dma_rd_adc1_buffer[raw_buffer_length_index] & 0xffff), &gl_dma_rd_adc1_buffer[raw_buffer_length_index+1], VAL_RED)	;
				}						   
			}

			if ((gl_uint_end_sample_address[1] != 0) && ( (gl_dma_rd_adc2_buffer[raw_buffer_length_index] & 0xffff0000) == 0xdada0000) ) {
      			if ((gl_uint_DisplayRawAdcShowChoose == 0) || (gl_uint_DisplayRawAdcShowChoose == 2)) {	
					displayEventAdcRawData((gl_dma_rd_adc2_buffer[raw_buffer_length_index] & 0xffff), &gl_dma_rd_adc2_buffer[raw_buffer_length_index+1], VAL_BLUE)	;
				}						   
			}

			if ((gl_uint_end_sample_address[2] != 0) && ( (gl_dma_rd_adc3_buffer[raw_buffer_length_index] & 0xffff0000) == 0xdada0000) ) {
      			if ((gl_uint_DisplayRawAdcShowChoose == 0) || (gl_uint_DisplayRawAdcShowChoose == 3)) {	
					displayEventAdcRawData((gl_dma_rd_adc3_buffer[raw_buffer_length_index] & 0xffff), &gl_dma_rd_adc3_buffer[raw_buffer_length_index+1], VAL_GREEN)	;
				}						   
			}

			if ((gl_uint_end_sample_address[3] != 0) && ( (gl_dma_rd_adc4_buffer[raw_buffer_length_index] & 0xffff0000) == 0xdada0000) ) {
      			if ((gl_uint_DisplayRawAdcShowChoose == 0) || (gl_uint_DisplayRawAdcShowChoose == 4)) {	
					displayEventAdcRawData((gl_dma_rd_adc4_buffer[raw_buffer_length_index] & 0xffff), &gl_dma_rd_adc4_buffer[raw_buffer_length_index+1], VAL_CYAN)	;
				}						   
			}


			if ((gl_uint_end_sample_address[4] != 0) && ( (gl_dma_rd_adc5_buffer[raw_buffer_length_index] & 0xffff0000) == 0xdada0000) ) {
      			if ((gl_uint_DisplayRawAdcShowChoose == 0) || (gl_uint_DisplayRawAdcShowChoose == 5)) {	
					displayEventAdcRawData((gl_dma_rd_adc5_buffer[raw_buffer_length_index] & 0xffff), &gl_dma_rd_adc5_buffer[raw_buffer_length_index+1], VAL_DK_RED)	;
				}						   
			}

			if ((gl_uint_end_sample_address[5] != 0) && ( (gl_dma_rd_adc6_buffer[raw_buffer_length_index] & 0xffff0000) == 0xdada0000) ) {
      			if ((gl_uint_DisplayRawAdcShowChoose == 0) || (gl_uint_DisplayRawAdcShowChoose == 6)) {	
					displayEventAdcRawData((gl_dma_rd_adc6_buffer[raw_buffer_length_index] & 0xffff), &gl_dma_rd_adc6_buffer[raw_buffer_length_index+1], VAL_DK_BLUE)	;
				}						   
			}

			if ((gl_uint_end_sample_address[6] != 0) && ( (gl_dma_rd_adc7_buffer[raw_buffer_length_index] & 0xffff0000) == 0xdada0000) ) {
      			if ((gl_uint_DisplayRawAdcShowChoose == 0) || (gl_uint_DisplayRawAdcShowChoose == 7)) {	
					displayEventAdcRawData((gl_dma_rd_adc7_buffer[raw_buffer_length_index] & 0xffff), &gl_dma_rd_adc7_buffer[raw_buffer_length_index+1], VAL_DK_GREEN)	;
				}						   
			}

			if ((gl_uint_end_sample_address[7] != 0) && ( (gl_dma_rd_adc8_buffer[raw_buffer_length_index] & 0xffff0000) == 0xdada0000) ) {
      			if ((gl_uint_DisplayRawAdcShowChoose == 0) || (gl_uint_DisplayRawAdcShowChoose == 8)) {	
					displayEventAdcRawData((gl_dma_rd_adc8_buffer[raw_buffer_length_index] & 0xffff), &gl_dma_rd_adc8_buffer[raw_buffer_length_index+1], VAL_DK_CYAN)	;
				}						   
			}

		}


 		deleteTestFirGraph() ;
		if (gl_uint_RunCheckDisplayEnergyValueFlag == 1)  {   ; // on
		
			if ((gl_uint_end_sample_address[0] != 0) && ( (gl_dma_rd_adc1_buffer[raw_buffer_length_index] & 0xffff0000) == 0xdada0000) ) {
      			if ((gl_uint_DisplayEnergyValueAdcShowChoose == 0) || (gl_uint_DisplayEnergyValueAdcShowChoose == 1)) {	
					displayEventAdcTestFirData((gl_dma_rd_adc1_buffer[raw_buffer_length_index] & 0xffff), &gl_dma_rd_adc1_buffer[raw_buffer_length_index+1], VAL_RED)	;
				}						   
			}

			if ((gl_uint_end_sample_address[1] != 0) && ( (gl_dma_rd_adc2_buffer[raw_buffer_length_index] & 0xffff0000) == 0xdada0000) ) {
      			if ((gl_uint_DisplayEnergyValueAdcShowChoose == 0) || (gl_uint_DisplayEnergyValueAdcShowChoose == 2)) {	
					displayEventAdcTestFirData((gl_dma_rd_adc2_buffer[raw_buffer_length_index] & 0xffff), &gl_dma_rd_adc2_buffer[raw_buffer_length_index+1], VAL_BLUE)	;
				}						   
			}

			if ((gl_uint_end_sample_address[2] != 0) && ( (gl_dma_rd_adc3_buffer[raw_buffer_length_index] & 0xffff0000) == 0xdada0000) ) {
      			if ((gl_uint_DisplayEnergyValueAdcShowChoose == 0) || (gl_uint_DisplayEnergyValueAdcShowChoose == 3)) {	
					displayEventAdcTestFirData((gl_dma_rd_adc3_buffer[raw_buffer_length_index] & 0xffff), &gl_dma_rd_adc3_buffer[raw_buffer_length_index+1], VAL_GREEN)	;
				}						   
			}

			if ((gl_uint_end_sample_address[3] != 0) && ( (gl_dma_rd_adc4_buffer[raw_buffer_length_index] & 0xffff0000) == 0xdada0000) ) {
      			if ((gl_uint_DisplayEnergyValueAdcShowChoose == 0) || (gl_uint_DisplayEnergyValueAdcShowChoose == 4)) {	
					displayEventAdcTestFirData((gl_dma_rd_adc4_buffer[raw_buffer_length_index] & 0xffff), &gl_dma_rd_adc4_buffer[raw_buffer_length_index+1], VAL_CYAN)	;
				}						   
			}


			if ((gl_uint_end_sample_address[4] != 0) && ( (gl_dma_rd_adc5_buffer[raw_buffer_length_index] & 0xffff0000) == 0xdada0000) ) {
      			if ((gl_uint_DisplayEnergyValueAdcShowChoose == 0) || (gl_uint_DisplayEnergyValueAdcShowChoose == 5)) {	
					displayEventAdcTestFirData((gl_dma_rd_adc5_buffer[raw_buffer_length_index] & 0xffff), &gl_dma_rd_adc5_buffer[raw_buffer_length_index+1], VAL_DK_RED)	;
				}						   
			}

			if ((gl_uint_end_sample_address[5] != 0) && ( (gl_dma_rd_adc6_buffer[raw_buffer_length_index] & 0xffff0000) == 0xdada0000) ) {
      			if ((gl_uint_DisplayEnergyValueAdcShowChoose == 0) || (gl_uint_DisplayEnergyValueAdcShowChoose == 6)) {	
					displayEventAdcTestFirData((gl_dma_rd_adc6_buffer[raw_buffer_length_index] & 0xffff), &gl_dma_rd_adc6_buffer[raw_buffer_length_index+1], VAL_DK_BLUE)	;
				}						   
			}

			if ((gl_uint_end_sample_address[6] != 0) && ( (gl_dma_rd_adc7_buffer[raw_buffer_length_index] & 0xffff0000) == 0xdada0000) ) {
      			if ((gl_uint_DisplayEnergyValueAdcShowChoose == 0) || (gl_uint_DisplayEnergyValueAdcShowChoose == 7)) {	
					displayEventAdcTestFirData((gl_dma_rd_adc7_buffer[raw_buffer_length_index] & 0xffff), &gl_dma_rd_adc7_buffer[raw_buffer_length_index+1], VAL_DK_GREEN)	;
				}						   
			}

			if ((gl_uint_end_sample_address[7] != 0) && ( (gl_dma_rd_adc8_buffer[raw_buffer_length_index] & 0xffff0000) == 0xdada0000) ) {
      			if ((gl_uint_DisplayEnergyValueAdcShowChoose == 0) || (gl_uint_DisplayEnergyValueAdcShowChoose == 8)) {	
					displayEventAdcTestFirData((gl_dma_rd_adc8_buffer[raw_buffer_length_index] & 0xffff), &gl_dma_rd_adc8_buffer[raw_buffer_length_index+1], VAL_DK_CYAN)	;
				}						   
			}

		}

	gl_uint_RunEventCounter++ ;

	if (gl_uint_end_sample_address[0] != 0 ) {
  	// adc1
	 	float_N1 = (float)  (gl_uint_Gate1_Length + 1);
	 	float_N2 = (float)  (gl_uint_Gate2_Length + 1);
	 	float_N3 = (float)  (gl_uint_Gate3_Length + 1);

		float_Gate1_sum =  (float) (gl_dma_rd_adc1_buffer[3] & 0xfffff) ;
		float_Gate2_sum =  (float) (gl_dma_rd_adc1_buffer[4] & 0xfffff) ;
		float_Gate3_sum =  (float) (gl_dma_rd_adc1_buffer[5] & 0xfffff) ;

		float_scaled_Gate2_sum = float_Gate2_sum - ((float_Gate1_sum *  float_N2) /  float_N1);
	                   
		uint_energy =   (unsigned int) float_scaled_Gate2_sum;
	
		if ((uint_energy <= (MAX_NOF_ENERGY_SPECTRUM-1)) && (uint_energy > 30) ) {
				gl_uint_EnergySpectrumArray[0][0][uint_energy]++ ;	    
		}
		float_scaled_Gate3_sum = float_Gate3_sum - ((float_Gate1_sum *  float_N3) /  float_N1);
	 	//float_scaled_Gate3_sum = ( (float_Gate3_sum / float_N3) - (float_Gate1_sum /  float_N1) );
	                   
		uint_energy =   (unsigned int) ((float_scaled_Gate3_sum / float_scaled_Gate2_sum) * 10000.0);
	
		if ((uint_energy <= (MAX_NOF_ENERGY_SPECTRUM-1)) && (uint_energy > 30) ) {
				gl_uint_EnergySpectrum2Array[0][0][uint_energy]++ ;	    
		}
	}
 	
	
	
	if (gl_uint_RunCheckDisplayEnergySpectrumFlag == 1) {   ; // on
		DisplayEnergySpectrum();
	}
	                   
   		ProcessSystemEvents ();  
	}while (    (gl_uint_RunStopStatusFlag == AQC_RUN_STATUS) 
            && ((gl_uint_RunEventCounter < gl_uint_RunMaxEventCounter ) || (gl_uint_RunCheckStopEventsFlag == 0) )
            && ((gl_unit_RunOneSecondCounter < gl_uint_RunMaxSecondsCounter ) || (gl_uint_RunCheckStopTimeFlag == 0) ) ) ; 


   return 0;
} // end function  ()



//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int RunPC_SIS3320LLNL_MultiEvent_SingleBuffer_Aquisition (void)
{

	unsigned int  first_event_length_lwords  ;
	unsigned int  event_length_lwords, max_events, address_threshold_value ;
	unsigned int  actual_sample_address_reg_offset[8] ;
	unsigned int  adc_buffer_reg_offset[8] ;
	int module_index, channel_index ;
	int event_index, nof_events, event_index_offset  ;
	int buffer_switch_counter  ;

	char messages_buffer[80] ;           
	

	int i,j,k ;
	int error ;
	unsigned int poll_counter ;
	unsigned int addr, data, data_rd ;
	unsigned int plot_size ;
	unsigned int  dma_request_no_of_words, dma_got_no_of_words ;
	unsigned int  module_buffer_offset ;
	unsigned int  uint_timestamp_upper, uint_timestamp_lower ;
	unsigned int  sum1, sum2 ;

	unsigned int  uint_energy ;
	int sign_diff ;
	int sign_max,sign_min  ;	//    
	float float_factor;


	unsigned int  uint_trigger_flags;
	unsigned int  local_CountofTriggerEventBased;
	unsigned int  local_PileupFlag;

	unsigned int  energy_mode ;
	unsigned int  nof_energy_values ;
	unsigned int  energy_max_index ;
    	 
//	signed int  sign_integral ;
 	unsigned int  gate1_sum, gate2_sum, gate3_sum, gate4_sum;
 	unsigned int  gate5_sum, gate6_sum, gate7_sum, gate8_sum;
 	signed int  gate_difference ;

	float float_Gate1_sum, float_Gate2_sum, float_Gate3_sum;
	float float_N1, float_N2, float_N3;
	float float_scaled_Gate2_sum, float_scaled_Gate3_sum;

	unsigned int  temp, temp2;
	unsigned int  raw_buffer_length_index;


	// loop setups

 	float_N1 = (float)  (gl_uint_Gate1_Length + 1);
 	float_N2 = (float)  (gl_uint_Gate2_Length + 1);
 	float_N3 = (float)  (gl_uint_Gate3_Length + 1);

	actual_sample_address_reg_offset[0] = SIS3320_ACTUAL_SAMPLE_ADDRESS_ADC1  ;
	actual_sample_address_reg_offset[1] = SIS3320_ACTUAL_SAMPLE_ADDRESS_ADC2  ;
	actual_sample_address_reg_offset[2] = SIS3320_ACTUAL_SAMPLE_ADDRESS_ADC3  ;
	actual_sample_address_reg_offset[3] = SIS3320_ACTUAL_SAMPLE_ADDRESS_ADC4  ;
	actual_sample_address_reg_offset[4] = SIS3320_ACTUAL_SAMPLE_ADDRESS_ADC5  ;
	actual_sample_address_reg_offset[5] = SIS3320_ACTUAL_SAMPLE_ADDRESS_ADC6  ;
	actual_sample_address_reg_offset[6] = SIS3320_ACTUAL_SAMPLE_ADDRESS_ADC7  ;
	actual_sample_address_reg_offset[7] = SIS3320_ACTUAL_SAMPLE_ADDRESS_ADC8  ;
	
	adc_buffer_reg_offset[0] = SIS3320_ADC1_OFFSET  ;
	adc_buffer_reg_offset[1] = SIS3320_ADC2_OFFSET  ;
	adc_buffer_reg_offset[2] = SIS3320_ADC3_OFFSET  ;
	adc_buffer_reg_offset[3] = SIS3320_ADC4_OFFSET  ;
	adc_buffer_reg_offset[4] = SIS3320_ADC5_OFFSET  ;
	adc_buffer_reg_offset[5] = SIS3320_ADC6_OFFSET  ;
	adc_buffer_reg_offset[6] = SIS3320_ADC7_OFFSET  ;
	adc_buffer_reg_offset[7] = SIS3320_ADC8_OFFSET  ;


	//gl_uint_RawDataSampleMode;
	// 0: no raw data; 
	// 1: always; 
	// 2: first event of buffer; 
	// 3: first event of buffer or if Pileup; 
	// 4: if Pileup			

	if (gl_uint_RawDataSampleMode > 2) { // raw data if Pileup
 		DisplayPanel (Panels[MODULE_MESS_SYSTEM]);
		sprintf (messages_buffer, "\n\n\nyou have to use an other -Raw Data Sample Mode- \n");
   		write_system_messages (messages_buffer, PRINT_DATE_YES)	   ;
   		ProcessSystemEvents ();  
	    return 0 ;
 	}
	
	//event_length_lwords	 = 10  ; // Timestamp/Header, Peakhigh, Integrals of Gates, Trailer
	// SIS3302 modification
	if (gl_uint_SIS3302_FlagConf[0] == 0)   { 
		event_length_lwords	 = 10  ; // Timestamp/Header, Peakhigh, Integrals of Gates, Trailer
	}
	else {
   		GetCtrlVal (Panels[SAMPLE_PARA_CONF],SAMPL_CONF_ACCU_DATA_FORMAT, &temp);
		if (temp == 0) { // 6-Accumulator mode
			event_length_lwords	 = 10  ; // Timestamp/Header, Peakhigh, Integrals of Gates, Trailer
   		}
		else {
			event_length_lwords	 = 12  ; // Timestamp/Header, Peakhigh, Integrals of Gates, Trailer
   		}
   	}

	raw_buffer_length_index = event_length_lwords - 1 ;
	
	
	if (gl_uint_RawDataSampleMode == 1) { // always raw data 
		first_event_length_lwords	 = event_length_lwords + (gl_uint_RawSample_Length>>1) ;
		event_length_lwords	         = event_length_lwords + (gl_uint_RawSample_Length>>1) ;
 	}
	if (gl_uint_RawDataSampleMode == 2) { // only first event 
		first_event_length_lwords	 = event_length_lwords + (gl_uint_RawSample_Length>>1) ;
		event_length_lwords	 = event_length_lwords   ;
 	}

	// calculation of max events to use only one 8MByte Sample Buffer (only one page)
 	max_events = 0x200000 / (event_length_lwords) ;  // 8MByte (2MLwors) / Event_length
 	max_events = 0x1 ;  // 8MByte (2MLwors) / Event_length

    address_threshold_value = (max_events * event_length_lwords) ; // valid if halfful !!
  	SetCtrlVal (Panels[RUN_CTRL_MENUE],RUN_CTRL_NOF_EVENT_READ,max_events/2);

	// address threshold flag
	data = address_threshold_value ;		// 
	
	for (module_index=0;module_index<gl_uint_NoOfModulesRun;module_index++) {
	//for (module_index=0;module_index<1;module_index++) {
		addr = gl_uint_ModAddrRun[module_index] + SIS3320_END_ADDRESS_THRESHOLD_ALL_ADC ; 
		if ((error = sub_vme_A32D32_write(addr,data )) != 0) { 
			sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_write")   ;
			gl_uint_system_status = SYSTEM_STATUS_MODULES_NOT_READY ;
			return -1 ;
		}
	}

	buffer_switch_counter = 0 ;	
// Readout Loop  */
	do {

		addr = gl_uint_SIS3320_BroadcastAddrConf + SIS3320_KEY_DISARM_AND_ARM_BANK1 ; 
		if ((error = sub_vme_A32D32_write(addr,0x0 )) != 0) { 
			sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_write")   ;
			gl_uint_system_status = SYSTEM_STATUS_MODULES_NOT_READY ;
			return -1 ;
		}


// poll now on ADDRESS Threshold valid		

#ifdef PCI_VME_INTERFACE  // Optical

		// wait for address threshold flag (IRQ 6) . Poll on an internal Flag in the SIS3150USB module
		poll_counter = 0 ;
		addr = 0x104 ; // SIS3100 VME Interrupt status register 
		do {
			if ((error = sis1100w_sis3100_Control_Read(&gl_sis1100_device, addr, &data_rd )) != 0) { 
				sisVME_ErrorHandling (error, addr, "sis1100w_sis3100_Control_Read"); 
				return -1;
			}
			poll_counter++;
			if (poll_counter == 100) {
    			ProcessSystemEvents ();
				poll_counter = 0 ;
    		}
		} while (((data_rd & 0xFE000000) == 0x00000) && (gl_uint_RunStopStatusFlag == AQC_RUN_STATUS))  ;   // loop until IRQ



#endif


#ifdef USB_VME_INTERFACE

   #define  POLL_ON_VME_IRQ // or of all ADDRESS Threshold Flags
   #ifdef POLL_ON_VME_IRQ
		// wait for address threshold flag (IRQ 6) . Poll on an internal Flag in the SIS3150USB module
		poll_counter = 0 ;
		addr = SIS3150USB_VME_INTERRUPT_STATUS ;  
		do {
			if ((error = sis3150Usb_Register_Single_Read(gl_USBDevice, addr, &data_rd )) != 0) { 
				sisVME_ErrorHandling (error, addr, "sis3150Usb_Register_Single_Read"); 
				return -1;
			}
			poll_counter++;
			if (poll_counter == 100) {
    			ProcessSystemEvents ();
				poll_counter = 0 ;
    		}
		} while (((data_rd & 0xFE) == 0x00000) && (gl_uint_RunStopStatusFlag == AQC_RUN_STATUS))  ;   // loop until IRQ
   #endif


    //#define  poll_on_first_module
	#ifdef poll_on_first_module	
		// wait for address threshold flag
		poll_counter = 0 ;
		addr = gl_uint_ModAddrRun[0] + SIS3320_ACQUISTION_CONTROL ; 
		do {
			if ((error = sub_vme_A32D32_read(addr,&data_rd )) != 0) { 
				sisVME_ErrorHandling (error, gl_uint_ModAddrRun[0], "sub_vme_A32D32_read"); 
				return -1;
			}
			poll_counter++;
			if (poll_counter == 100) {
    			ProcessSystemEvents ();
				poll_counter = 0 ;
    		}
		} while (((data_rd & 0x80000) != 0x80000) && (gl_uint_RunStopStatusFlag == AQC_RUN_STATUS))  ;

	#endif



#endif

		addr = gl_uint_SIS3320_BroadcastAddrConf + SIS3320_KEY_DISARM ; 
		if ((error = sub_vme_A32D32_write(addr,0x0 )) != 0) { 
			sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_write")   ;
			gl_uint_system_status = SYSTEM_STATUS_MODULES_NOT_READY ;
			return -1 ;
		}


		// loop over modules
		for (module_index=0;module_index<gl_uint_NoOfModulesRun;module_index++) {
		//for (module_index=0;module_index<1;module_index++) {

			for (channel_index=0;channel_index<8;channel_index++) {
			//for (channel_index=0;channel_index<1;channel_index++) {

				// read stop sample address
				addr = gl_uint_ModAddrRun[module_index] + actual_sample_address_reg_offset[channel_index] ; 
				if ((error = sub_vme_A32D32_read(addr,&gl_uint_end_sample_address[channel_index] )) != 0) { 
					sisVME_ErrorHandling (error, gl_uint_ModAddrRun[module_index], "sub_vme_A32D32_read"); 
					return -1;
				}

				// readout	   	
				if (gl_uint_end_sample_address[channel_index] != 0) {
	   				addr = gl_uint_ModAddrRun[module_index] + adc_buffer_reg_offset[channel_index]  ;
	  				error = sub_vme_A32MBLT64_read(addr, &gl_dma_rd_buffer[0],  (gl_uint_end_sample_address[channel_index] & 0x3ffffC)>>1, &dma_got_no_of_words) ;
					if (error != 0x0) { // vme error
						sisVME_ErrorHandling (error, addr, "sub_vme_A32MBLT64_read")   ;
					}
				}
						   
				// display information and raw data	   	
				if (gl_uint_end_sample_address[channel_index] != 0) {
					if (gl_uint_RunCheckDisplayRawFlag == 1)  {   ; // on
						displayEventDataInformation(gl_dma_rd_buffer)  ;

						if ((gl_uint_RawDataSampleMode == 1) || (gl_uint_RawDataSampleMode == 2) ) { // only if  always raw data or first
					 		deleteRawGraph() ;
							displayEventAdcRawData((gl_dma_rd_buffer[raw_buffer_length_index] & 0xffff), &gl_dma_rd_buffer[raw_buffer_length_index+1], VAL_RED)	;
						}
					}

				}

				//Histogramming
				if (gl_uint_end_sample_address[channel_index] == 0) {
					nof_events =	0 ;
				}
				else {
					nof_events =	(gl_uint_end_sample_address[channel_index]  >> 1) / event_length_lwords ;
					for (event_index=0;event_index<nof_events;event_index++) {
						
						if ((gl_uint_RawDataSampleMode == 0) || (gl_uint_RawDataSampleMode == 1) ) { // never or always raw data  
							event_index_offset =  event_index * event_length_lwords ;
						}
						else {  // 2 only first event
						   if (event_index == 0) {
								event_index_offset =  0 ;
						   }
						   else { 
								event_index_offset =  first_event_length_lwords + ((event_index -1)* event_length_lwords ) ;
						   }
						}
						float_Gate1_sum =  (float) (gl_dma_rd_buffer[event_index_offset+3] & 0xffffff) ;
						float_Gate2_sum =  (float) (gl_dma_rd_buffer[event_index_offset+4] & 0xfffffff) ;
						float_Gate3_sum =  (float) (gl_dma_rd_buffer[event_index_offset+5] & 0xfffffff) ;
						float_scaled_Gate2_sum = float_Gate2_sum - ((float_Gate1_sum *  float_N2) /  float_N1);
	                   
						uint_energy =   (unsigned int) float_scaled_Gate2_sum;
	
						if ((uint_energy <= (MAX_NOF_ENERGY_SPECTRUM-1)) && (uint_energy > 30) ) {
							gl_uint_EnergySpectrumArray[module_index][channel_index][uint_energy]++ ;	    
						}
					
						float_scaled_Gate3_sum = float_Gate3_sum - ((float_Gate1_sum *  float_N3) /  float_N1);
						uint_energy =   (unsigned int) ((float_scaled_Gate3_sum * 10000.0) / float_scaled_Gate2_sum) ;
	
						if ((uint_energy <= (MAX_NOF_ENERGY_SPECTRUM-1)) && (uint_energy > 30) ) {
							gl_uint_EnergySpectrum2Array[module_index][channel_index][uint_energy]++ ;	    
						}
					
					}
				
				}
				gl_uint_RunEventCounter = gl_uint_RunEventCounter +  nof_events ;
 
 	
	
				if (gl_uint_RunCheckDisplayEnergySpectrumFlag == 1) {   ; // on
					DisplayEnergySpectrum();
				}


				if (gl_uint_end_sample_address[channel_index] != 0) {
					if (gl_uint_DataEvent_OpenFlag == 1) {   ; // Open
						WriteBufferHeaderCounterNofChannelToDataFile (buffer_switch_counter, nof_events, event_length_lwords) ;
						WriteTS_EventsToDataFile (gl_dma_rd_buffer, dma_got_no_of_words)  ;
        			}
        		}
				
			}   // channel_index
 		}   //   module_index

		buffer_switch_counter++ ;	

   		ProcessSystemEvents ();  
//	}while (    (gl_uint_RunStopStatusFlag == AQC_RUN_STATUS)   ) ;
	}while (    (gl_uint_RunStopStatusFlag == AQC_RUN_STATUS) 
            && ((gl_uint_RunEventCounter < gl_uint_RunMaxEventCounter ) || (gl_uint_RunCheckStopEventsFlag == 0) )
            && ((gl_unit_RunOneSecondCounter < gl_uint_RunMaxSecondsCounter ) || (gl_uint_RunCheckStopTimeFlag == 0) ) ) ; 


   return 0;
} // end function  ()



//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int RunPC_SIS3320LLNL_MultiEvent_DoubleBuffer_Aquisition (void)
{

	unsigned int  first_event_length_lwords  ;
	unsigned int  event_length_lwords, max_events, address_threshold_value ;
	unsigned int  previous_bank_sample_address_reg_offset[8] ;
	unsigned int  adc_buffer_reg_offset[8] ;
	int module_index, channel_index ;
	int event_index, nof_events, event_index_offset  ;
	int bank1_armed_flag  ;
	unsigned int buffer_switch_counter  ;


	char messages_buffer[80] ;           

//	int i,j,k ;
	int error, temp, temp2 ;
	unsigned int poll_counter ;
	unsigned int addr, data, data_rd ;
	unsigned int plot_size ;
	unsigned int  dma_request_no_of_words, dma_got_no_of_words ;
	unsigned int  module_buffer_offset ;
	unsigned int  uint_timestamp_upper, uint_timestamp_lower ;
	unsigned int  sum1, sum2 ;

	unsigned int  uint_energy ;
	int sign_diff ;
	int sign_max,sign_min  ;	//    
	float float_factor;


	unsigned int  uint_trigger_flags;
	unsigned int  local_CountofTriggerEventBased;
	unsigned int  local_PileupFlag;

	unsigned int  energy_mode ;
	unsigned int  nof_energy_values ;
	unsigned int  energy_max_index ;
    	 
//	signed int  sign_integral ;
 	unsigned int  gate1_sum, gate2_sum, gate3_sum, gate4_sum;
 	unsigned int  gate5_sum, gate6_sum, gate7_sum, gate8_sum;
 	signed int  gate_difference ;

	float float_Gate1_sum, float_Gate2_sum, float_Gate3_sum;
	float float_N1, float_N2, float_N3;
	float float_scaled_Gate2_sum, float_scaled_Gate3_sum;
 	unsigned int  raw_buffer_length_index;

// loop setups

 	float_N1 = (float)  (gl_uint_Gate1_Length + 1);
 	float_N2 = (float)  (gl_uint_Gate2_Length + 1);
 	float_N3 = (float)  (gl_uint_Gate3_Length + 1);

	previous_bank_sample_address_reg_offset[0] = SIS3320_PREVIOUS_BANK_SAMPLE_ADDRESS_ADC1  ;
	previous_bank_sample_address_reg_offset[1] = SIS3320_PREVIOUS_BANK_SAMPLE_ADDRESS_ADC2  ;
	previous_bank_sample_address_reg_offset[2] = SIS3320_PREVIOUS_BANK_SAMPLE_ADDRESS_ADC3  ;
	previous_bank_sample_address_reg_offset[3] = SIS3320_PREVIOUS_BANK_SAMPLE_ADDRESS_ADC4  ;
	previous_bank_sample_address_reg_offset[4] = SIS3320_PREVIOUS_BANK_SAMPLE_ADDRESS_ADC5  ;
	previous_bank_sample_address_reg_offset[5] = SIS3320_PREVIOUS_BANK_SAMPLE_ADDRESS_ADC6  ;
	previous_bank_sample_address_reg_offset[6] = SIS3320_PREVIOUS_BANK_SAMPLE_ADDRESS_ADC7  ;
	previous_bank_sample_address_reg_offset[7] = SIS3320_PREVIOUS_BANK_SAMPLE_ADDRESS_ADC8  ;
	
	adc_buffer_reg_offset[0] = SIS3320_ADC1_OFFSET  ;
	adc_buffer_reg_offset[1] = SIS3320_ADC2_OFFSET  ;
	adc_buffer_reg_offset[2] = SIS3320_ADC3_OFFSET  ;
	adc_buffer_reg_offset[3] = SIS3320_ADC4_OFFSET  ;
	adc_buffer_reg_offset[4] = SIS3320_ADC5_OFFSET  ;
	adc_buffer_reg_offset[5] = SIS3320_ADC6_OFFSET  ;
	adc_buffer_reg_offset[6] = SIS3320_ADC7_OFFSET  ;
	adc_buffer_reg_offset[7] = SIS3320_ADC8_OFFSET  ;


	//gl_uint_RawDataSampleMode;
	// 0: no raw data; 
	// 1: always; 
	// 2: first event of buffer; 
	// 3: first event of buffer or if Pileup; 
	// 4: if Pileup			

	if (gl_uint_RawDataSampleMode > 2) { // raw data if Pileup
 		DisplayPanel (Panels[MODULE_MESS_SYSTEM]);
		sprintf (messages_buffer, "\n\n\nyou have to use an other -Raw Data Sample Mode- \n");
   		write_system_messages (messages_buffer, PRINT_DATE_YES)	   ;
   		ProcessSystemEvents ();  
	    return 0 ;
 	}

	//event_length_lwords	 = 10  ; // Timestamp/Header, Peakhigh, Integrals of Gates, Trailer
	// SIS3302 modification
	if (gl_uint_SIS3302_FlagConf[0] == 0)   { 
		event_length_lwords	 = 10  ; // Timestamp/Header, Peakhigh, Integrals of Gates, Trailer
	}
	else {
   		GetCtrlVal (Panels[SAMPLE_PARA_CONF],SAMPL_CONF_ACCU_DATA_FORMAT, &temp);
		if (temp == 0) { // 6-Accumulator mode
			event_length_lwords	 = 10  ; // Timestamp/Header, Peakhigh, Integrals of Gates, Trailer
   		}
		else {
			event_length_lwords	 = 12  ; // Timestamp/Header, Peakhigh, Integrals of Gates, Trailer
   		}
   	}
	raw_buffer_length_index = event_length_lwords - 1;
	
	
	if (gl_uint_RawDataSampleMode == 1) { // always raw data 
		first_event_length_lwords	 = event_length_lwords + (gl_uint_RawSample_Length>>1) ;
		event_length_lwords	         = event_length_lwords + (gl_uint_RawSample_Length>>1) ;
 	}
	if (gl_uint_RawDataSampleMode == 2) { // only first event 
		first_event_length_lwords	 = event_length_lwords + (gl_uint_RawSample_Length>>1) ;
		event_length_lwords	 = event_length_lwords   ;
 	}

	// calculation of max events to use only one 8MByte Sample Buffer (only one page)
 	max_events = 0x200000 / (event_length_lwords) ;  // 8MByte (2MLwors) / Event_length

	GetCtrlVal (Panels[RUN_CTRL_MENUE],RUN_CTRL_CHECK_NOF_EVENT_MANUA,&temp);		//roe14.12.09
	if (temp == 1) {																//
  		GetCtrlVal (Panels[RUN_CTRL_MENUE],RUN_CTRL_RUN_EVENT_MAX_NUMBER2, &temp2); //
	  	if ( max_events > temp2) {													//
		 	max_events = temp2 * 2;  // 											//
	  	}																			//
	}																				//
																					//
    address_threshold_value = (max_events * event_length_lwords) ; // valid if halfful !!
  	SetCtrlVal (Panels[RUN_CTRL_MENUE],RUN_CTRL_NOF_EVENT_READ,max_events/2);
	
	// address threshold flag
	data = address_threshold_value ;		//  
	for (module_index=0;module_index<gl_uint_NoOfModulesRun;module_index++) {
	//for (module_index=0;module_index<1;module_index++) {
		addr = gl_uint_ModAddrRun[module_index] + SIS3320_END_ADDRESS_THRESHOLD_ALL_ADC ; 
		if ((error = sub_vme_A32D32_write(addr,data )) != 0) { 
			sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_write")   ;
			gl_uint_system_status = SYSTEM_STATUS_MODULES_NOT_READY ;
			return -1 ;
		}
	}

		
// Start Readout Loop  */
	addr = gl_uint_SIS3320_BroadcastAddrConf + SIS3320_KEY_DISARM_AND_ARM_BANK1 ; 
	if ((error = sub_vme_A32D32_write(addr,0x0 )) != 0) { 
		sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_write")   ;
		gl_uint_system_status = SYSTEM_STATUS_MODULES_NOT_READY ;
		return -1 ;
	}
	bank1_armed_flag = 1; // start condition
	buffer_switch_counter = 0 ;	
	do {

// poll now on ADDRESS Threshold valid		

#ifdef PCI_VME_INTERFACE  // Optical

		// wait for address threshold flag (IRQ 6) . Poll on an internal Flag in the SIS3150USB module
		poll_counter = 0 ;
		addr = 0x104 ; // SIS3100 VME Interrupt status register 
		do {
			if ((error = sis1100w_sis3100_Control_Read(&gl_sis1100_device, addr, &data_rd )) != 0) { 
				sisVME_ErrorHandling (error, addr, "sis1100w_sis3100_Control_Read"); 
				return -1;
			}
			poll_counter++;
			if (poll_counter == 100) {
    			ProcessSystemEvents ();
				poll_counter = 0 ;
    		}
		} while (((data_rd & 0xFE000000) == 0x00000) && (gl_uint_RunStopStatusFlag == AQC_RUN_STATUS))  ;   // loop until IRQ
#endif


#ifdef USB_VME_INTERFACE

   #define  POLL_ON_VME_IRQ // or of all ADDRESS Threshold Flags
   #ifdef POLL_ON_VME_IRQ
		// wait for address threshold flag (IRQ 6) . Poll on an internal Flag in the SIS3150USB module
		poll_counter = 0 ;
		addr = SIS3150USB_VME_INTERRUPT_STATUS ;  
		do {
			if ((error = sis3150Usb_Register_Single_Read(gl_USBDevice, addr, &data_rd )) != 0) { 
				sisVME_ErrorHandling (error, addr, "sis3150Usb_Register_Single_Read"); 
				return -1;
			}
			poll_counter++;
			if (poll_counter == 100) {
    			ProcessSystemEvents ();
				poll_counter = 0 ;
    		}
		} while (((data_rd & 0xFE) == 0x00000) && (gl_uint_RunStopStatusFlag == AQC_RUN_STATUS))  ;   // loop until IRQ
   #endif


    //#define  poll_on_first_module
	#ifdef poll_on_first_module	
		// wait for address threshold flag
		poll_counter = 0 ;
		addr = gl_uint_ModAddrRun[0] + SIS3320_ACQUISTION_CONTROL ; 
		do {
			if ((error = sub_vme_A32D32_read(addr,&data_rd )) != 0) { 
				sisVME_ErrorHandling (error, gl_uint_ModAddrRun[0], "sub_vme_A32D32_read"); 
				return -1;
			}
			poll_counter++;
			if (poll_counter == 100) {
    			ProcessSystemEvents ();
				poll_counter = 0 ;
    		}
		} while (((data_rd & 0x80000) != 0x80000) && (gl_uint_RunStopStatusFlag == AQC_RUN_STATUS))  ;

	#endif
#endif


		if (bank1_armed_flag == 1) {		
			addr = gl_uint_SIS3320_BroadcastAddrConf + SIS3320_KEY_DISARM_AND_ARM_BANK2 ; 
			bank1_armed_flag = 0; // bank 2 is armed
		}
		else {
			addr = gl_uint_SIS3320_BroadcastAddrConf + SIS3320_KEY_DISARM_AND_ARM_BANK1 ; 
			bank1_armed_flag = 1; // bank 2 is armed
		}

		
		if ((error = sub_vme_A32D32_write(addr,0x0 )) != 0) { 
			sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_write")   ;
			gl_uint_system_status = SYSTEM_STATUS_MODULES_NOT_READY ;
			return -1 ;
		}
		

		// loop over modules
		for (module_index=0;module_index<gl_uint_NoOfModulesRun;module_index++) {
		//for (module_index=0;module_index<1;module_index++) {
			// set Buffer page 
			data = 0x0 ; //Bank2 is armed and Bank1 (page 0) has to be readout
			if (bank1_armed_flag == 1) { // Bank1 is armed and Bank2 (page 4) has to be readout		
				data = 0x4 ;
			}
			addr = gl_uint_ModAddrRun[module_index] + SIS3320_ADC_MEMORY_PAGE_REGISTER ; 
			if ((error = sub_vme_A32D32_write(addr,data )) != 0) { 
				sisVME_ErrorHandling (error, gl_uint_ModAddrRun[module_index], "sub_vme_A32D32_write"); 
				return -1;
			}

			for (channel_index=0;channel_index<8;channel_index++) {
			//for (channel_index=0;channel_index<1;channel_index++) {

				// read stop sample address
				addr = gl_uint_ModAddrRun[module_index] + previous_bank_sample_address_reg_offset[channel_index] ; 
				if ((error = sub_vme_A32D32_read(addr,&gl_uint_end_sample_address[channel_index] )) != 0) { 
					sisVME_ErrorHandling (error, gl_uint_ModAddrRun[module_index], "sub_vme_A32D32_read"); 
					return -1;
				}

			   	// check buffer address
			   	gl_uint_end_sample_address[channel_index] = gl_uint_end_sample_address[channel_index] & 0xffffff ; // mask bank2 address bit (bit 24)
				if (gl_uint_end_sample_address[channel_index] > 0x3fffff) {   // more than 1 page memory buffer is used
					    gl_uint_end_sample_address[channel_index] = 2 * ((max_events-1) * event_length_lwords) ; // max 8Mbyte (inside one page)
				}

				// readout	   	
				temp =  (gl_uint_end_sample_address[channel_index] & 0x3ffffc)>>1 ;
				temp =  gl_uint_end_sample_address[channel_index]  ;
				if (gl_uint_end_sample_address[channel_index] != 0) {
	   				addr = gl_uint_ModAddrRun[module_index] + adc_buffer_reg_offset[channel_index]  ;
	  				error = sub_vme_A32MBLT64_read(addr, &gl_dma_rd_buffer[0],  (gl_uint_end_sample_address[channel_index] & 0x3ffffc)>>1, &dma_got_no_of_words) ;
					if (error != 0x0) { // vme error
						sisVME_ErrorHandling (error, addr, "sub_vme_A32MBLT64_read")   ;
					}
				}
						   
				// display information and raw data	   	
				if (gl_uint_end_sample_address[channel_index] != 0) {
					if (gl_uint_RunCheckDisplayRawFlag == 1)  {   ; // on
						displayEventDataInformation(gl_dma_rd_buffer)  ;

						if ((gl_uint_RawDataSampleMode == 1) || (gl_uint_RawDataSampleMode == 2) ) { // only if  always raw data or first
					 		deleteRawGraph() ;
							displayEventAdcRawData((gl_dma_rd_buffer[raw_buffer_length_index] & 0xffff), &gl_dma_rd_buffer[raw_buffer_length_index+1], VAL_RED)	;
						}
					}
				}


				//Histogramming
				if (gl_uint_end_sample_address[channel_index] == 0) {
					nof_events =	0 ;
				}
				else {
					nof_events =	(gl_uint_end_sample_address[channel_index]  >> 1) / event_length_lwords ;
					for (event_index=0;event_index<nof_events;event_index++) {

						if ((gl_uint_RawDataSampleMode == 0) || (gl_uint_RawDataSampleMode == 1) ) { // never or always raw data  
							event_index_offset =  event_index * event_length_lwords ;
						}
						else {  // 2 only first event
						   if (event_index == 0) {
								event_index_offset =  0 ;
						   }
						   else { 
								event_index_offset =  first_event_length_lwords + ((event_index -1)* event_length_lwords ) ;
						   }
						}

						float_Gate1_sum =  (float) (gl_dma_rd_buffer[event_index_offset+3] & 0xfffffff) ;
						float_Gate2_sum =  (float) (gl_dma_rd_buffer[event_index_offset+4] & 0xffffffff) ;
						float_Gate3_sum =  (float) (gl_dma_rd_buffer[event_index_offset+5] & 0xffffffff) ;
						float_scaled_Gate2_sum = float_Gate2_sum - ((float_Gate1_sum *  float_N2) /  float_N1);
	                   
						uint_energy =   (unsigned int) float_scaled_Gate2_sum;
	
						if ((uint_energy <= (MAX_NOF_ENERGY_SPECTRUM-1)) && (uint_energy > 30) ) {
							gl_uint_EnergySpectrumArray[module_index][channel_index][uint_energy]++ ;	    
						}
					
						float_scaled_Gate3_sum = float_Gate3_sum - ((float_Gate1_sum *  float_N3) /  float_N1);
						uint_energy =   (unsigned int) ((float_scaled_Gate3_sum * 10000.0) / float_scaled_Gate2_sum) ;
	
						if ((uint_energy <= (MAX_NOF_ENERGY_SPECTRUM-1)) && (uint_energy > 30) ) {
							gl_uint_EnergySpectrum2Array[module_index][channel_index][uint_energy]++ ;	    
						}

						//Peakhigh - base
						//uint_energy =   (unsigned int) ((gl_dma_rd_buffer[event_index_offset+2] & 0xffff) - (float_Gate1_sum /  float_N1)) ;;
						uint_energy =   (unsigned int) ((gl_dma_rd_buffer[event_index_offset+2] & 0xffff) ) ;;
	
						if ((uint_energy <= (MAX_NOF_ENERGY_SPECTRUM-1)) && (uint_energy > 30) ) {
							gl_uint_EnergySpectrum3Array[module_index][channel_index][uint_energy]++ ;	    
						}
					
					
					
					}
				
				}
				
				gl_uint_RunEventCounter = gl_uint_RunEventCounter +  nof_events ;
 
 	
	

				if (gl_uint_end_sample_address[channel_index] != 0) {
					if (gl_uint_DataEvent_OpenFlag == 1) {   ; // Open
						WriteBufferHeaderCounterNofChannelToDataFile (buffer_switch_counter, nof_events, event_length_lwords) ;
						WriteTS_EventsToDataFile (gl_dma_rd_buffer, dma_got_no_of_words)  ;
        			}
        		}
				
			}   // channel_index
   			ProcessSystemEvents ();

 		}   //   module_index
		if (gl_uint_RunCheckDisplayEnergySpectrumFlag == 1) {   ; // on
			DisplayEnergySpectrum();
		}

		buffer_switch_counter++ ;	


   		ProcessSystemEvents ();  
//	}while (    (gl_uint_RunStopStatusFlag == AQC_RUN_STATUS)   ) ;
	}while (    (gl_uint_RunStopStatusFlag == AQC_RUN_STATUS) 
            && ((gl_uint_RunEventCounter < gl_uint_RunMaxEventCounter ) || (gl_uint_RunCheckStopEventsFlag == 0) )
            && ((gl_unit_RunOneSecondCounter < gl_uint_RunMaxSecondsCounter ) || (gl_uint_RunCheckStopTimeFlag == 0) ) ) ; 



	addr =gl_uint_SIS3320_BroadcastAddrConf + SIS3320_KEY_DISARM ; 
	if ((error = sub_vme_A32D32_write(addr,0x0 )) != 0) { 
		sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_write")   ;
		gl_uint_system_status = SYSTEM_STATUS_MODULES_NOT_READY ;
		return -1 ;
	}

   return 0;
} // end function  ()





//--------------------------------------------------------------------------- 
//  only if USB INterface                                                           
//--------------------------------------------------------------------------- 
int RunPC_SIS3150USB_DSP_Load_Program (void)
{
//   int  event_i, module_i  ;
   int i, j, k ;
   int error ;
 	unsigned int temp_index ;
    	 


#ifdef USB_VME_INTERFACE

 
// SIS3150USB Configuration
	error = Configuration_SIS3150USB () ;   
	if (error != 0) { sisVME_ErrorHandling (error, 0, "Configuration_SIS3150USB"); return -1 ;}

// Load Program into SIS3150-9300 TigerSharcs  (Reset, Clear Commmunication Varibale and load Loaderfile)
	error = Setup_Load_Loaderfile_sis3150usb_tigersharcs () ;   
	if (error != 0) { sisVME_ErrorHandling (error, 0, "Setup_Load_Loaderfile_sis3150usb_tigersharcs"); return -1 ;}


	do {

       	ProcessSystemEvents ();
	//}while (    (gl_uint_RunStopStatusFlag == AQC_RUN_STATUS)   ) ;
	}while (    (gl_uint_RunStopStatusFlag == AQC_RUN_STATUS) 
            && ((gl_uint_RunEventCounter < gl_uint_RunMaxEventCounter ) || (gl_uint_RunCheckStopEventsFlag == 0) )
            && ((gl_unit_RunOneSecondCounter < gl_uint_RunMaxSecondsCounter ) || (gl_uint_RunCheckStopTimeFlag == 0) ) ) ; 

	usb_sis3150_tigersharcs_Reset(gl_USBDevice) ;

#endif
   return 0;
} // end function  ()






///--------------------------------------------------------------------------- 
//   only if USB INterface                                                         
//--------------------------------------------------------------------------- 

int Configuration_SIS3150USB (void)   
{
 	unsigned int error;
	unsigned int data, addr;
#ifdef USB_VME_INTERFACE
	//  set bit 3 in control register --> USB has control over LEMO outputs 	
	addr = SIS3150USB_CONTROL_STATUS  ;
	error = sis3150Usb_Register_Single_Write(gl_USBDevice, addr, 0x8) ;
	if (error != 0) { sisVME_ErrorHandling (error, addr, "sis3150Usb_Register_Single_Write"); return -1 ;}

	//  TS1 Flag ored to Lemo out1 	, TS2 Flag ored to Lemo out2
	addr = SIS3150USB_LEMO_OUT_SELECT_REG  ;
	error = sis3150Usb_Register_Single_Write(gl_USBDevice, addr, 0x40002) ; 
	if (error != 0) { sisVME_ErrorHandling (error, addr, "sis3150Usb_Register_Single_Write"); return -1 ;}

#endif
	return 0x0 ;
} // end function  ()


/*************************************************************************************************/

/* --------------------------------------------------------------------------
   - Reset TigerSharcs
   - Clear Communication Variable
   - Load TigerSharc Loaderfile into TSs
-------------------------------------------------------------------------- */

//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int Setup_Load_Loaderfile_sis3150usb_tigersharcs (void)   
{
 	unsigned int i;
 	unsigned int error;
	unsigned int data, addr;
#ifdef USB_VME_INTERFACE


	//sprintf(gl_char_FileNameLoaderSIS3150USB_TS, "main.ldr") ;
	//usb_load_tigersharcs(gl_USBDevice,  gl_char_FileNameLoaderSIS3150USB_TS)   ;

	// Reset TSharcs
	usb_sis3150_tigersharcs_Reset(gl_USBDevice) ;

	// clear communication parameters
	data = MB_CLEAR   ; // 
	addr = SIS3150USB_TS1_BASE +  SIS3150USB_TS_MEMORY_BLOCK0 + (TS_COMMUNICATION_VARIABLE)  ;
	if ((error = sis3150Usb_TsBus_Single_Write(gl_USBDevice,addr,data )) != 0) { 
		sisVME_ErrorHandling (error, addr, "sis3150Usb_TsBus_Single_Write"); 
		return -1;
	}
	addr = SIS3150USB_TS2_BASE +  SIS3150USB_TS_MEMORY_BLOCK0 + (TS_COMMUNICATION_VARIABLE)  ;
	if ((error = sis3150Usb_TsBus_Single_Write(gl_USBDevice,addr,data )) != 0) { 
		sisVME_ErrorHandling (error, addr, "sis3150Usb_TsBus_Single_Write"); 
		return -1;
	}

	// Load TSharcs program
	usb_load_tigersharcs_without_Reset(gl_USBDevice, gl_char_FileNameLoaderSIS3150USB_TS) ;

#endif
	return 0x0 ;
} // end function  ()




//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int Setup_SIS3150USB_TS_readout_parameters (unsigned int max_nof_events, unsigned int channel_event_length)   
{
 	unsigned int i;
 	unsigned int error;
	unsigned int data, addr;
	unsigned int data31_0, data63_32;
	unsigned int help_data31_0, help_data63_32;
	unsigned int module_index, channel_index;
	unsigned int i_mod, i_ch;
	unsigned int conf_mod_byte[8];
	unsigned int run_mod_byte[8];
	   

	return 0x0 ;
} // end function  ()


//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 

int CVICALLBACK CB_Run10mSecondTick (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int error ;
	unsigned int addr;
	switch (event)
		{
		case EVENT_TIMER_TICK:
			addr = gl_uint_ModAddrRun[0] + SIS3320_KEY_TRIGGER ;  // spater broadcast addresse
			if ((error = sub_vme_A32D32_write(addr,0 )) != 0) { 
				sisVME_ErrorHandling (error, addr, "sub_vme_A32D32_write")   ;
			}

			break;
		}
	return 0;
}


//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int CVICALLBACK CB_RunSecondTick (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	float  eventRate,  eventRateAverage, fileMByteSize ;
	switch (event)
		{
		case EVENT_TIMER_TICK:
			gl_unit_RunOneSecondCounter ++   ;
			displayRunEventInformations();

   			gl_uint_RunEventOldCounter = gl_uint_RunEventCounter ;

			break;
		}
	return 0;
}


//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int displayRunEventInformations (void)
{   
	unsigned int temp;
	float  eventRate,  eventRateAverage, fileMByteSize ;

		temp = gl_uint_RunEventCounter ;
		eventRate = (float) (temp) - (float)(gl_uint_RunEventOldCounter)	   ;
		gl_uint_RunEventOldCounter = temp ;
		if (gl_unit_RunOneSecondCounter == 0) {
		 	eventRateAverage = eventRate ;
		  }
		 else {
			eventRateAverage = (float) (gl_uint_RunEventCounter) / (float)( gl_unit_RunOneSecondCounter )   ;
		  }
//		fileMByteSize =   ((((float) (100))  * 4.0) /  1048576.0 ) ;  // 1MByte
		fileMByteSize =   ((((float) (gl_uint_DataEvent_LWordCounter))  * 4.0) /  1048576.0 ) ;  // 1MByte
//	//	fileMByteSize =   (((float) (gl_uint_DataEvent_LWordCounter))  / 250000.0 ) ;  // * 4 / 1000

		SetCtrlVal (Panels[RUN_CTRL_MENUE], RUN_CTRL_RUN_EVENT_NUMBER, gl_uint_RunEventCounter);
		SetCtrlVal (Panels[RUN_CTRL_MENUE], RUN_CTRL_RUN_EVENT_RATE, eventRate);
		SetCtrlVal (Panels[RUN_CTRL_MENUE], RUN_CTRL_RUN_EVENT_RATE_A, eventRateAverage);
		SetCtrlVal (Panels[RUN_CTRL_MENUE], RUN_CTRL_RUN_EVENT_SECOND, gl_unit_RunOneSecondCounter);
		SetCtrlVal (Panels[RUN_CTRL_MENUE], RUN_CTRL_RUN_EVENT_MBYTE, fileMByteSize);
  return 0;
}



//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int CVICALLBACK CB_RunEventMaxNumber (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{

	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal (Panels[RUN_CTRL_MENUE], RUN_CTRL_RUN_EVENT_MAX_NUMBER, &gl_uint_RunMaxEventCounter);
			break;
		}
	return 0;
}


//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int CVICALLBACK CB_RunEventMaxSeconds (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal (Panels[RUN_CTRL_MENUE], RUN_CTRL_RUN_EVENT_MAX_SECOND, &gl_uint_RunMaxSecondsCounter);

			break;
		}
	return 0;
}

 

//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int CVICALLBACK CB_Timer (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	return 0;
}


//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int CVICALLBACK CB_WriteFile (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
unsigned int blt_data[0x10000];
unsigned int read_data[0x10000];
int i ;
int written ;
FILE *diskfile;

	return 0;
}



