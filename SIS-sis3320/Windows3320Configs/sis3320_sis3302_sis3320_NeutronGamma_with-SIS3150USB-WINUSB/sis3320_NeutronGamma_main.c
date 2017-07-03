/***************************************************************************/
/*                                                                         */
/*  Project: SIS3320/SIS3320-250 Neutron/Gamma                             */
/*                                                                         */
/*  Filename: sis3320_NeutronGamma_main.c                                  */
/*                                                                         */
/*  Funktion:                                                              */
/*                                                                         */
/*  Autor:                TH                                               */
/*  date:                 01.10.2006                                       */
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


// --- CVI - Header ---------------------------------------------------------
#include <windows.h>
#include <formatio.h>
#include <cvirte.h>
#include <userint.h>
#include <stdio.h>
#include <ansi_c.h>
#include <utility.h>         
#include "sis3320_NeutronGamma_uir.h"
#include "sis3320_NeutronGamma_global.h" 	// Globale Defines fuers Programm


#include "pc_vme_interface_defines.h"

// -- Optical Interface

#ifdef PCI_VME_INTERFACE
// PCI VME interface

//#include "sis3150.h"
#include "sis3150_utils.h"

struct SIS1100_Device_Struct  sis1100_device1 ;
struct SIS1100_Device_Struct  gl_sis1100_device ;

#endif


// -- USB Interface

#ifdef USB_VME_INTERFACE

#include "sis3150usb.h"

HANDLE  gl_USBDevice = NULL;
HANDLE  gl_hXDev = NULL;

struct SIS3150USB_Device_Struct	gl_sis3150_device_information_struct[MAX_USB_DEV_NUMBER];

UCHAR    gl_cDName[128] ;    //DriverNames

int     ixDebug;
unsigned int gl_nof_usbdevices   ;
unsigned int gl_usb_index   ;

#endif

// --- Programm globale Variablen -------------------------------------------
// 

char gl_char_FilePathConf[MAX_PATHNAME_LENGTH];
char gl_char_FileNameConf[MAX_FILENAME_LENGTH];	 


char gl_char_FilePathData[MAX_PATHNAME_LENGTH];
char gl_char_FileNameData[MAX_FILENAME_LENGTH];	 
char gl_char_FileNameLoaderSIS3150USB_TS[MAX_FILENAME_LENGTH];	 


// configuration globals 
unsigned int gl_uint_system_status ;   

// SIS3320 Modules
unsigned int gl_uint_SIS3320_BroadcastAddrConf	;
unsigned int gl_uint_ModEnableConf[MAX_NO_OF_MODULES]   ;
unsigned int gl_uint_ModAddrConf[MAX_NO_OF_MODULES]		;
unsigned int gl_uint_SIS3320_250_FlagConf[MAX_NO_OF_MODULES]		;
unsigned int gl_uint_SIS3302_FlagConf[MAX_NO_OF_MODULES]		;


// Clock Module
unsigned int gl_uint_SIS3820EnableConf   ;
unsigned int gl_uint_SIS3820AddrConf	;
unsigned int gl_uint_SIS3820_Version	;


// Common Clock 
unsigned int gl_uint_SIS3820ClockModeConf	;

unsigned int gl_uint_SIS3820ClockCtrl4FlagConf	;
unsigned int gl_uint_SIS3820ClockCtrl3FlagConf	;
unsigned int gl_uint_SIS3820ClockCtrl2FlagConf	;
unsigned int gl_uint_SIS3820ClockTriggerMaskConf	;

unsigned int  gl_uint_SIS3320ClockModeConf     ;

// Common SIS3320 
unsigned int  gl_uint_SIS3320_Trigger_Mode_Source_ModeConf     ;
unsigned int  gl_uint_SIS3320_DUMMY_ModeConf     ;

unsigned int  gl_uint_SIS3320External_Lemo_Trigger_FlagConf     ;
unsigned int  gl_uint_SIS3320External_Lemo_TimestampClr_FlagConf     ;

// NeutronGamma  Common Sample Parameters
unsigned int  gl_uint_MainGateLength     ;
unsigned int  gl_uint_MainGatePreTriggerDelay     ;

unsigned int  gl_uint_Gate1_Length     ;
unsigned int  gl_uint_Gate1_StartIndex     ;
unsigned int  gl_uint_Gate2_Length     ;
unsigned int  gl_uint_Gate2_StartIndex     ;
unsigned int  gl_uint_Gate3_Length     ;
unsigned int  gl_uint_Gate3_StartIndex     ;
unsigned int  gl_uint_Gate4_Length     ;
unsigned int  gl_uint_Gate4_StartIndex     ;

unsigned int  gl_uint_Gate5_Length     ;
unsigned int  gl_uint_Gate5_StartIndex     ;
unsigned int  gl_uint_Gate6_Length     ;
unsigned int  gl_uint_Gate6_StartIndex     ;
unsigned int  gl_uint_Gate7_Length     ;
unsigned int  gl_uint_Gate7_StartIndex     ;
unsigned int  gl_uint_Gate8_Length     ;
unsigned int  gl_uint_Gate8_StartIndex     ;

unsigned int  gl_uint_RawSample_Length     ;
unsigned int  gl_uint_RawSample_StartIndex     ;

unsigned int  gl_uint_RawDataSampleMode     ;
unsigned int  gl_uint_RawDataTestMode     ;

// DAC Offset
unsigned int  gl_uint_DacOffset_Conf[MAX_NO_OF_MODULES] [NO_OF_ADC_CHANNELS]     ;
unsigned int  gl_uint_DacOffset_Inbox[NO_OF_ADC_CHANNELS]     ;
unsigned int  gl_uint_DacReadAdcValueLoopFlag     ;

// FIR Trigger Parameters
unsigned int  gl_uint_FirTriggerP_Inbox[NO_OF_ADC_CHANNELS]     ;
unsigned int  gl_uint_FirTriggerG_Inbox[NO_OF_ADC_CHANNELS]     ;

unsigned int  gl_uint_FirTriggerP_Conf[MAX_NO_OF_MODULES] [NO_OF_ADC_CHANNELS]     ;
unsigned int  gl_uint_FirTriggerG_Conf[MAX_NO_OF_MODULES] [NO_OF_ADC_CHANNELS]     ;

int  gl_int_FirTriggerThresholdValue_Inbox[NO_OF_ADC_CHANNELS]     ;
int  gl_int_FirTriggerThresholdValue_Conf[MAX_NO_OF_MODULES] [NO_OF_ADC_CHANNELS]     ;

unsigned int  gl_uint_FirTriggerThreshold_GtLtFlag_Inbox[NO_OF_ADC_CHANNELS]     ;
unsigned int  gl_uint_FirTriggerThreshold_GtLtFlag_Conf[MAX_NO_OF_MODULES] [NO_OF_ADC_CHANNELS]     ;

unsigned int  gl_uint_FirTriggerPulseLength_Inbox[NO_OF_ADC_CHANNELS]     ;
unsigned int  gl_uint_FirTriggerPulseLength_Conf[MAX_NO_OF_MODULES] [NO_OF_ADC_CHANNELS]     ;

// ADC Signal Invert Flag
unsigned int  gl_uint_ADC_SignalInvertInbox[MAX_NO_OF_MODULES]     ;
unsigned int  gl_uint_ADC_SignalInvertConf[MAX_NO_OF_MODULES][NO_OF_ADC_CHANNELS]     ;

// ADC Gain Factor
unsigned int  gl_uint_ADC_Gain_FactorInbox[MAX_NO_OF_MODULES]     ;
unsigned int  gl_uint_ADC_Gain_FactorConf[MAX_NO_OF_MODULES][NO_OF_ADC_CHANNELS]     ;


//run
unsigned int  gl_uint_RunStopStatusFlag     ;
unsigned int  gl_uint_RunReadoutMode     ;

unsigned int  gl_uint_RunDisableStartClearFlag     ;
unsigned int  gl_uint_RunCheckDisplayRawFlag     ;
unsigned int  gl_uint_RunCheckDisplayEnergyValueFlag     ;
unsigned int  gl_uint_RunCheckDisplayEnergySpectrumFlag     ;
unsigned int  gl_uint_RunCheckDisplayDiagnosticFlag     ;
unsigned int  gl_uint_RunCheckWrDataToFileFlag     ;

unsigned int  gl_uint_RunCheckDisplayDiagnosticFlag     ;
unsigned int  gl_uint_RunCheckEnableEnergyFlag   ;

unsigned int  gl_uint_RunCheckStopTimeFlag     ;
unsigned int  gl_uint_RunCheckStopEventsFlag     ;

unsigned int  gl_uint_RunMaxSecondsCounter        ;
unsigned int  gl_uint_RunMaxEventCounter        ;
unsigned int  gl_uint_RunEventCounter        ;
unsigned int  gl_uint_RunEventOldCounter     ;
unsigned int  gl_unit_RunOneSecondCounter    ;


// run globals
unsigned int gl_uint_ModConfIndexRun[MAX_NO_OF_MODULES]  ;
unsigned int gl_uint_ModAddrRun[MAX_NO_OF_MODULES]  ;
unsigned int gl_uint_NoOfModulesRun ;

// Display raw
unsigned int gl_unit_DisplayRawModuleNumber    ;
unsigned int gl_uint_DisplayRawAdcShowChoose ;

unsigned short *gl_ushort_displayRawADC1_ptr    ;
unsigned short *gl_ushort_displayRawADC2_ptr    ;
unsigned short *gl_ushort_displayRawADC3_ptr    ;
unsigned short *gl_ushort_displayRawADC4_ptr    ;
unsigned short *gl_ushort_displayRawADC5_ptr    ;
unsigned short *gl_ushort_displayRawADC6_ptr    ;
unsigned short *gl_ushort_displayRawADC7_ptr    ;
unsigned short *gl_ushort_displayRawADC8_ptr    ;


signed short *gl_short_displayRawADC1_ptr    ;
signed short *gl_short_displayRawADC2_ptr    ;
signed short *gl_short_displayRawADC3_ptr    ;
signed short *gl_short_displayRawADC4_ptr    ;
signed short *gl_short_displayRawADC5_ptr    ;
signed short *gl_short_displayRawADC6_ptr    ;
signed short *gl_short_displayRawADC7_ptr    ;
signed short *gl_short_displayRawADC8_ptr    ;


unsigned int gl_uint_displayRaw_plot_size    ;
unsigned int gl_unit_GraphRawXmin ;
unsigned int gl_unit_GraphRawXmax ;
unsigned int gl_unit_GraphRawYmin ;
unsigned int gl_unit_GraphRawYmax ;

unsigned int gl_uint_DisplayRawADC_Header_ID[8]  ;
unsigned int gl_uint_DisplayRawADC_TIMESTAMP_UPPER  ;
unsigned int gl_uint_DisplayRawADC_TIMESTAMP_LOWER  ;
unsigned int gl_uint_DisplayRawADC_FlagInfo[8]  ;


// Display Energy Values
unsigned int gl_unit_DisplayEnergyValueModuleNumber    ;
unsigned int gl_uint_DisplayEnergyValueAdcShowChoose ;

unsigned int gl_uint_displayEnergyValue_plot_size    ;
int *gl_int_displayEnergyValueADC1_ptr    ;
int *gl_int_displayEnergyValueADC2_ptr    ;
int *gl_int_displayEnergyValueADC3_ptr    ;
int *gl_int_displayEnergyValueADC4_ptr    ;
int *gl_int_displayEnergyValueADC5_ptr    ;
int *gl_int_displayEnergyValueADC6_ptr    ;
int *gl_int_displayEnergyValueADC7_ptr    ;
int *gl_int_displayEnergyValueADC8_ptr    ;

unsigned int gl_unit_GraphEnergyValueXmin ;
unsigned int gl_unit_GraphEnergyValueXmax ;
unsigned int gl_unit_GraphEnergyValueYmin ;
unsigned int gl_unit_GraphEnergyValueYmax ;


// Display Energy Spectrum
unsigned int gl_unit_DisplayEnergySpectrumModuleNumber    ;
unsigned int gl_uint_DisplayEnergySpectrumAdcShowChoose ;

unsigned int gl_uint_displayEnergySpectrum_plot_size    ;
unsigned int gl_unit_GraphEnergySpectrumXmin ;
unsigned int gl_unit_GraphEnergySpectrumXmax ;
unsigned int gl_unit_GraphEnergySpectrumYmin ;
unsigned int gl_unit_GraphEnergySpectrumYmax ;

unsigned int  gl_uint_EnergySpectrumArray[MAX_NO_OF_MODULES][NO_OF_ADC_CHANNELS][MAX_NOF_ENERGY_SPECTRUM]  ;
unsigned int  gl_uint_EnergySpectrum2Array[MAX_NO_OF_MODULES][NO_OF_ADC_CHANNELS][MAX_NOF_ENERGY_SPECTRUM]  ;
unsigned int  gl_uint_EnergySpectrum3Array[MAX_NO_OF_MODULES][NO_OF_ADC_CHANNELS][MAX_NOF_ENERGY_SPECTRUM]  ;

double gl_double_EnergySpectrumGaussXdraw[MAX_NOF_ENERGY_SPECTRUM];

double gl_double_gausspos;
double gl_double_gaussfwhm;
double gl_double_gaussint;
double gl_double_MSE;

double gl_double_coefs[5] = {100., 100., 2., 1.0 , 0.1};
double gl_double_xfit[MAX_NOF_ENERGY_SPECTRUM];
double gl_double_yinfit[MAX_NOF_ENERGY_SPECTRUM];
double gl_double_youtfit[MAX_NOF_ENERGY_SPECTRUM];

// Display Diagnostic

unsigned int  gl_uint_CountOfTriggersChannelBasedArray[MAX_NO_OF_CHANNELS]  ;
unsigned int  gl_uint_CountOfTriggersEventBasedArray[MAX_NO_OF_CHANNELS]  ;
unsigned int  gl_uint_CountOfPileupsTriggerCountBasedArray[16]  ;

// Display Plot Style

int  gl_plot_raw_plot_style  ;
int  gl_plot_fpga_plot_style  ;
int  gl_plot_energy_spec_plot_style  ;
int  gl_plot_diag_plot_style  ;

int  gl_plot_raw_line_style  ;
int  gl_plot_fpga_line_style  ;
int  gl_plot_energy_spec_line_style  ;
int  gl_plot_diag_line_style  ;

int  gl_plot_raw_background_color  ;
int  gl_plot_fpga_background_color  ;
int  gl_plot_energy_spec_background_color  ;
int  gl_plot_diag_background_color  ;

int  gl_plot_raw_grid_color  ;
int  gl_plot_fpga_grid_color  ;
int  gl_plot_energy_spec_grid_color  ;
int  gl_plot_diag_grid_color  ;

int  gl_plot_raw_plot_color  ;
int  gl_plot_fpga_plot_color  ;
int  gl_plot_energy_spec_plot_color  ;
int  gl_plot_diag_plot_color  ;


// data event file save
FILE *gl_FILE_DataEvenFilePointer           ;
unsigned int  gl_uint_DataEvent_OpenFlag	;
unsigned int  gl_uint_DataEvent_FileCounter ;
unsigned int  gl_uint_DataFileRunEventCounter ;

unsigned int  gl_uint_DataEvent_RunFile_NOF_Energy ;
unsigned int  gl_uint_DataEvent_RunFile_EventSize ;
unsigned int  gl_uint_DataEvent_RunFile_EventChannelSize ;

unsigned int  gl_uint_DataEvent_LWordCounter ;
unsigned int  gl_uint_DataEvent_Nof1kLwords   ;

// data event file offline
FILE *gl_FILE_OfflineDataEvenFilePointer           ;
unsigned int  gl_uint_OfflineDataEvent_OpenFlag	;
unsigned int  gl_uint_OfflineDataEvent_FileCounter ;
unsigned int  gl_uint_OfflineDataEvent_LWordCounter ;
unsigned int  gl_uint_OfflineDataEvent_Nof1kLwords   ;

unsigned int  gl_uint_OfflineFileNumber   ;
unsigned int  gl_uint_OfflineDataFormat    ; 
unsigned int  gl_uint_OfflineNofModules   ;

unsigned int  gl_uint_OfflineSamplingParamters   ;

unsigned int  gl_uint_OfflineMainGateParameters    ;
unsigned int  gl_uint_OfflineRawSampleModeParameters   ;
unsigned int  gl_uint_OfflineRawDataParameters   ;
unsigned int  gl_uint_OfflineGate1Parameters   ;
unsigned int  gl_uint_OfflineGate2Parameters   ;
unsigned int  gl_uint_OfflineGate3Parameters   ;
unsigned int  gl_uint_OfflineGate4Parameters   ;
unsigned int  gl_uint_OfflineGate5Parameters   ;
unsigned int  gl_uint_OfflineGate6Parameters   ;
unsigned int  gl_uint_OfflineGate7Parameters   ;
unsigned int  gl_uint_OfflineGate8Parameters   ;
unsigned int  gl_uint_OfflineGateEventLength   ;
unsigned int  gl_uint_OfflineSIS_Device   ;
 

unsigned int  gl_uint_OfflineEnergyParameters    ;
unsigned int  gl_uint_OfflineEnergyModeLength    ;
unsigned int  gl_uint_OfflineReadoutMode  ;
unsigned int  gl_uint_OfflineReadoutModeAddr2Addr1  ;
unsigned int  gl_uint_OfflineEnergyModeLengthAddr3  ;

unsigned int  gl_uint_OfflineSizeOfEvent  ;
unsigned int  gl_uint_OfflineSizeOfChannelEvent    ; 
unsigned int  gl_uint_OfflineNofEvents    ; 

//unsigned int  gl_uint_OfflineCheckDisplayDiagnosticFlag     ;
//unsigned int  gl_uint_OfflineCheckDisplayEnergyFlag     ;
unsigned int  gl_uint_OfflineCheckDisplayRawFlag     ;
unsigned int  gl_uint_OfflineCheckDisplayEnergyValueFlag     ;
unsigned int  gl_uint_OfflineCheckDisplayEnergySpectrumFlag     ;

// offline
unsigned int  gl_uint_Offline_RawSampleLength     ;
unsigned int  gl_uint_Offline_EnergyLength     ;
unsigned int  gl_uint_Offline_RunLoopFlag ;     ;
unsigned int  gl_uint_Offline_PauseLoopFlag ;     ;
unsigned int  gl_uint_OfflineCheckSingleStepFlag ;     ;
unsigned int  gl_uint_OfflineCheckStopIfPileupFlag ;     ;

//unsigned int gl_dma_rd_buffer[0x100000] ; // 4MByte 
unsigned int gl_dma_rd_buffer[0x1000000] ; // 64MByte 
unsigned int gl_dma_rd_adc1_buffer[0x200000] ; // 8MByte 
unsigned int gl_dma_rd_adc2_buffer[0x200000] ; // 8MByte 
unsigned int gl_dma_rd_adc3_buffer[0x200000] ; // 8MByte 
unsigned int gl_dma_rd_adc4_buffer[0x200000] ; // 8MByte 
unsigned int gl_dma_rd_adc5_buffer[0x200000] ; // 8MByte 
unsigned int gl_dma_rd_adc6_buffer[0x200000] ; // 8MByte 
unsigned int gl_dma_rd_adc7_buffer[0x200000] ; // 8MByte 
unsigned int gl_dma_rd_adc8_buffer[0x200000] ; // 8MByte 


unsigned int  gl_uint_end_sample_address[NO_OF_ADC_CHANNELS]  ;



// --- Panel Handle ---------------------------------------------------------
int Panels[NO_OF_PANEL];		// Feld fuer die einzelnen PanelHandles
int MenuBars[NO_OF_MENUBARS];		// Feld fuer die einzelnen PanelHandles

int intShowPanel;							// Zeigt an welches Panel nach
    									// dem Message-Panel angezeigt
											// werden soll


/* --------------------------------------------------------------------------
   Main program start
-------------------------------------------------------------------------- */
int main (int argc, char *argv[])
{									 

	int CviErr;
	int error=0;
	int mode_wr, mode_rd;
	int stat;
	unsigned int addr_wr, addr_rd, data_rd;

	int sis_ret ;
	HANDLE hProcess;
	HANDLE hDevice ;
	unsigned int found_no_sis1100 ;
	unsigned int  use_sis1100_no ;
	unsigned int  sis1100_no  ;
	unsigned int  sis1100_PciBus ;
	unsigned int  sis1100_PciSlot ;
	unsigned int  data ;
	int return_code ;
    int i ;
    char messages_buffer[1024] ;           
	int i2, temp ;
 
	if (InitCVIRTE (0, argv, 0) == 0)  return -1;  	// Nicht genug Speicher

	// Das Haupt-Panel laden
	if ((Panels[MAIN] = LoadPanel (0, "sis3320_NeutronGamma_uir.uir", PANEL)) < 0) return -1;

			  
	
	if ((Panels[MODULE_PARA_CONF] = LoadPanel (Panels[MAIN], "sis3320_NeutronGamma_uir.uir", MOD_CONF)) < 0) return -1;
	if ((Panels[DAC_PARA_CONF] = LoadPanel (Panels[MAIN], "sis3320_NeutronGamma_uir.uir", DAC_CONF)) < 0) return -1;
	if ((Panels[CLOCK_PARA_CONF] = LoadPanel (Panels[MAIN], "sis3320_NeutronGamma_uir.uir", CLOCK_CONF)) < 0) return -1;

												
	if ((Panels[TRIG_PARA_CONF] = LoadPanel (Panels[MAIN], "sis3320_NeutronGamma_uir.uir", TRIG_CONF)) < 0) return -1;
	if ((Panels[SAMPLE_PARA_CONF] = LoadPanel (Panels[MAIN], "sis3320_NeutronGamma_uir.uir", SAMPL_CONF)) < 0) return -1;

	if ((Panels[SIGNAL_INVERT_CONF] = LoadPanel (Panels[MAIN], "sis3320_NeutronGamma_uir.uir", SIGNA_CONF)) < 0) return -1;
	if ((Panels[GAIN_FACTOR_CONF] = LoadPanel (Panels[MAIN], "sis3320_NeutronGamma_uir.uir", GAIN_CONF)) < 0) return -1;

	if ((Panels[SAMPLE_HELP_GATE] = LoadPanel (Panels[MAIN], "sis3320_NeutronGamma_uir.uir", HELP_GATE)) < 0) return -1;


	if ((Panels[MODULE_MESS_SYSTEM] = LoadPanel (Panels[MAIN], "sis3320_NeutronGamma_uir.uir", MESS_SYS)) < 0) return -1;
	if ((Panels[MODULE_MESS_ERROR]  = LoadPanel (Panels[MAIN], "sis3320_NeutronGamma_uir.uir", MESS_ERR)) < 0) return -1;

				 
	if ((Panels[RUN_CTRL_MENUE] = LoadPanel (Panels[MAIN], "sis3320_NeutronGamma_uir.uir", RUN_CTRL)) < 0) return -1;
	if ((Panels[OFFLINE_CONTROL] = LoadPanel (Panels[MAIN], "sis3320_NeutronGamma_uir.uir", OFFLI_CTRL)) < 0) return -1;

	
	
	if ((Panels[PANEL_DISPLAY_RAW] = LoadPanel (Panels[MAIN], "sis3320_NeutronGamma_uir.uir", PANEL_RAW)) < 0) return -1;
	if ((Panels[PANEL_DISPLAY_EVALUES] = LoadPanel (Panels[MAIN], "sis3320_NeutronGamma_uir.uir", PANEL_EVAL)) < 0) return -1;
	if ((Panels[PANEL_DISPLAY_ENERGY_SPEC] = LoadPanel (Panels[MAIN], "sis3320_NeutronGamma_uir.uir", PANEL_ESPE)) < 0) return -1;

	if ((Panels[PANEL_DISPLAY_GAUSS_VALUE] = LoadPanel (Panels[MAIN], "sis3320_NeutronGamma_uir.uir", PANEL_GAUS)) < 0) return -1;
	
	
	if ((Panels[PANEL_DISPLAY_DIAGNOSTIC] = LoadPanel (Panels[MAIN], "sis3320_NeutronGamma_uir.uir", PANEL_DIAG)) < 0) return -1;
 																					 
// load MenuBars

	if ((MenuBars[MAIN_MENU_BAR] = LoadMenuBar (Panels[MAIN], "sis3320_NeutronGamma_uir.uir", MENU)) < 0) return -1;

	if ((MenuBars[OFFLINECTRL_MENU_BAR] = LoadMenuBar (Panels[OFFLINE_CONTROL], "sis3320_NeutronGamma_uir.uir", MENUCTRLOF)) < 0) return -1;


// -- PCI VME Interface Setup

/************************************
*        init sis1100
************************************/

#ifdef PCI_VME_INTERFACE


	sis_ret = sis1100w_Find_No_Of_sis1100(&found_no_sis1100) ;

//    if (found_no_sis1100 == 0)  exit(-1) ;

    sprintf (messages_buffer, "number of SIS1100 modules = %d \n",found_no_sis1100);
    write_system_messages (messages_buffer, PRINT_DATE_YES)	   ;

	for (i=1;i<=found_no_sis1100;i++) {
	  sis_ret = sis1100w_Get_PciSlot_Information(i, &sis1100_PciBus, &sis1100_PciSlot) ;
	}
	sprintf (messages_buffer, "used SIS1100 is in PCI Slot %d  \n",found_no_sis1100);
    write_system_messages (messages_buffer, PRINT_DATE_NO)	   ;

	use_sis1100_no = found_no_sis1100 ; // use last one which was founded
  //   use_sis1100_no = 1 ; 
	sis_ret =  sis1100w_Get_Handle_And_Open(use_sis1100_no, &sis1100_device1) ;
    if (sis_ret!=0) exit(-1);
	sis_ret = sis1100w_Init(&sis1100_device1, 1 /* enable_logfile */) ;
    if ( sis_ret !=0) {
    	write_system_messages ("FAILED to open SIS1100\n", PRINT_DATE_NO)	   ;
 		//  exit(-1);
 	 }
 	 else {
    	write_system_messages ("open and init SIS1100  OK\n", PRINT_DATE_NO)	   ;
  	 }

    sis_ret = sis1100w_Init_sis3100(&sis1100_device1, 1 /* enable_logfile */) ; 
    if ( sis_ret !=0) {
    	write_system_messages ("FAILED to init SIS3100\n\n", PRINT_DATE_NO)	   ;
 		//  exit(-1);
 	 }
 	 else {
    	write_system_messages ("init SIS3100  OK\n\n", PRINT_DATE_NO)	   ;
  	 }
    gl_sis1100_device =   sis1100_device1 ;	   // global SIS1100 device handle 



#endif

/************************************
*       end of  init sis1100
************************************/




// -- USB VME Interface Setup

/************************************
*        init sis3150USB
************************************/

#ifdef USB_VME_INTERFACE

	FindAll_SIS3150USB_Devices(gl_sis3150_device_information_struct, &gl_nof_usbdevices, MAX_USB_DEV_NUMBER)  ;

	if (gl_nof_usbdevices == 0) {
	    sprintf (messages_buffer, "No SIS3150USB Device found\n");
	    write_system_messages (messages_buffer, PRINT_DATE_YES)	   ;
		//exit(-1) ;
		gl_usb_index = 0 ;
	  	gl_USBDevice = NULL ;
	}
	else {
	    sprintf (messages_buffer, "number of SIS3150USB devices = %d \n\n",gl_nof_usbdevices);
	    write_system_messages (messages_buffer, PRINT_DATE_YES)	   ;


		
	    //sprintf (messages_buffer, "Device    Vendor   Product   Ser.No. \n");  // USB_CYPRESS driver
	    sprintf (messages_buffer, "Vendor   Product   Ser.No. \n");
	    write_system_messages (messages_buffer, PRINT_DATE_NO)	   ;
		for (i=0;i<gl_nof_usbdevices;i++) { 
		  	sprintf (messages_buffer, "%s   0x%04x   0x%04x    0x%04x ",	  // USB_CYPRESS driver 
		#ifdef USB_WIN_DRIVER
	  									gl_sis3150_device_information_struct[i].cDName,
		#else
	  									(UCHAR*)  &gl_sis3150_device_information_struct[i].cDName,
		#endif
	  	                                (USHORT)  gl_sis3150_device_information_struct[i].idVendor,
	  	                                (USHORT)  gl_sis3150_device_information_struct[i].idProduct,
	  	                                (USHORT)  gl_sis3150_device_information_struct[i].idSerNo    );
	    	write_system_messages (messages_buffer, PRINT_DATE_NO)	   ;
		}
		
	   // use first device
		gl_usb_index = 1 ;

		#ifdef USB_WIN_DRIVER
	 	sprintf (gl_cDName, "%s", gl_sis3150_device_information_struct[gl_usb_index-1].cDName);
		#else
	 	sprintf (gl_cDName, "%s", (UCHAR*)&gl_sis3150_device_information_struct[gl_usb_index-1].cDName);
		#endif
 
 		sprintf (messages_buffer, "\n\nuse USB Devices %s\n", gl_cDName);
	    write_system_messages (messages_buffer, PRINT_DATE_NO)	   ;
		return_code = Sis3150usb_OpenDriver_And_Download_FX2_Setup (gl_cDName, &gl_USBDevice );

 		if(return_code != 0) {
	  		gl_USBDevice = NULL ;
		  	sprintf (messages_buffer, "%s\n", "ERROR Loading BIX File");
	    	write_system_messages (messages_buffer, PRINT_DATE_NO)	   ;
		}

	}


#endif

#ifdef USB_VME_INTERFACE
	#ifdef USB_WIN_DRIVER
			SetPanelAttribute  (Panels[MAIN], ATTR_TITLE, "Demo Application SIS3302 / SIS3320 / SIS3320-250 ADC  Neutron/Gamma  - 4. June 2011 - SIS3150USB-WinUSB driver");
		#else
			SetPanelAttribute  (Panels[MAIN], ATTR_TITLE, "Demo Application SIS3302 / SIS3320 / SIS3320-250 ADC  Neutron/Gamma  - 4. June 2011 - SIS3150USB-Cypress driver");
	#endif

   #else
			SetPanelAttribute  (Panels[MAIN], ATTR_TITLE, "Demo Application SIS3302 / SIS3320 / SIS3320-250 ADC  Neutron/Gamma  - 4. June 2011 - SIS311x driver");
#endif



    SetCtrlVal (Panels[MAIN], PANEL_SYSTEM_LED, ON);
	SetCtrlAttribute (Panels[MAIN], PANEL_SYSTEM_LED, ATTR_ON_COLOR, VAL_RED);


	gl_uint_system_status = SYSTEM_STATUS_MODULES_NOT_READY  ;
	CheckSystemStatus() ;  

	FirstReadConfiguration();

	// Das Panel anzeigen
	SetPanelPos(Panels[MAIN],30,10)  ;
	DisplayPanel (Panels[MAIN]);
	// Die Prozessprioritaet setzen


	hProcess = GetCurrentProcess();
//	stat = SetPriorityClass(hProcess, NORMAL_PRIORITY_CLASS);
//	stat = SetPriorityClass(hProcess, NORMAL_PRIORITY_CLASS);
	// IDLE_PRIORITY_CLASS
	// NORMAL_PRIORITY_CLASS
	// HIGH_PRIORITY_CLASS
	// REALTIME_PRIORITY_CLASS  
	
	// Das CVI-Userinterface starten
	RunUserInterface ();

	return 0;
} // end function main ()



//--------------------------------------------------------------------------- 
// Root Menu Call Back
//--------------------------------------------------------------------------- 

void CVICALLBACK CB_MenuFile (int menuBar, int menuItem, void *callbackData,
        int panel)
{
    switch (menuItem) {
        /* Take action depending on which item was selected */
        case MENU_FILE_QUIT :
            if (ConfirmPopup ("Program End", "Sure to quit Application?"))  {  
             //SaveConfiguration (gl_char_FileNameConf)  ;
             // SaveConfigurationAs ()  ;
				QuitUserInterface (0);
                return;}
            break;


        }    // end switch menu item
           
return;

}


 
/* Messages Windows */

//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
void CVICALLBACK CB_MenuMessages (int menuBar, int menuItem, void *callbackData,
        int panel)
{
    switch (menuItem) {
        /* Take action depending on which item was selected */

        case MENU_VIEW_MESSAGES_SYSTEM : {
	        SetPanelPos(Panels[MODULE_MESS_SYSTEM],60,400)  ;   // y, x
 			DisplayPanel (Panels[MODULE_MESS_SYSTEM]);
            }
            break;
        case MENU_VIEW_MESSAGES_ERROR : {
	        SetPanelPos(Panels[MODULE_MESS_ERROR],360,400)  ;   
 			DisplayPanel (Panels[MODULE_MESS_ERROR]);
            }
            break;
        }    // end switch menu item
              
return;

}


/* close Panels */
//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
void CVICALLBACK CB_Menu_MessagesSystem (int menuBar, int menuItem, void *callbackData,
        int panel)
{
  int i2, temp ;
    switch (menuItem) {
        case MENUMESSYS_CLOSE : {
            HidePanel(Panels[MODULE_MESS_SYSTEM]); //Clear Panel 
           }  
           break;
        case MENUMESSYS_CLEAR : {
			ResetTextBox (Panels[MODULE_MESS_SYSTEM], MESS_SYS_TEXTBOX, "");
           }  
           break;
        case MENUMESSYS_TEST1 : {

           
           }  
           break;

     }  // switch
return;
}


//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
/* close Panels */
void CVICALLBACK CB_Menu_MessagesError (int menuBar, int menuItem, void *callbackData,
        int panel)
{
    switch (menuItem) {
        case MENUMESERR_CLOSE : {
            HidePanel(Panels[MODULE_MESS_ERROR]); //Clear Panel 
           }  
           break;
        case MENUMESERR_CLEAR : {
			ResetTextBox (Panels[MODULE_MESS_ERROR], MESS_ERR_TEXTBOX, "");
           }  
           break;
     }  // switch
return;
}

//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
/* --------------------------------------------------------------------------
   CB-Funktion  
-------------------------------------------------------------------------- */

int CVICALLBACK CB_SystemStatusLed (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
    char buffer[2048];
	switch (event)
		{
		case EVENT_COMMIT:
			break;

		case EVENT_RIGHT_CLICK:

			CopyString (buffer, 0,              "grey:   SIS1100/3100 interface not initialized \n", 0,
			                             strlen("grey:   SIS1100/3100 interface not initialized \n"));
			CopyString (buffer, strlen(buffer), "red:    SIS3300 Module status/definition not OK \n", 0,
			                             strlen("red:    SIS3300 Module status/definition not OK \n"));
			CopyString (buffer, strlen(buffer), "yellow: not valid configuration \n", 0,
			                             strlen("yellow: not valid configuration \n"));
			CopyString (buffer, strlen(buffer), "green:  valid configuration / ready for running \n", 0,
			                             strlen("green:  valid configuration / ready for running \n"));
			CopyString (buffer, strlen(buffer), "blue:   running \n", 0,
			                             strlen("blue:   running \n"));

			MessagePopup ("meaning  ",buffer) ;
    		break;
		}
	return 0;
}



/* --------------------------------------------------------------------------
   VME Error Handling
-------------------------------------------------------------------------- */


int sisVME_ErrorHandling (unsigned int prot_error, unsigned int vme_addr, char *err_messages)
{

	int CviErr;
//	char error_msg[MAX_PATHNAME_LEN];
	char buffer[128];


	DisplayPanel (Panels[MODULE_MESS_ERROR]);

	if(err_messages) {
	  sprintf (buffer, "%s    ", err_messages);
      SetCtrlVal (Panels[MODULE_MESS_ERROR], MESS_ERR_TEXTBOX, buffer);   
	 }
	sprintf (buffer, "prot_error=%8x at address=%8x  \n", prot_error,vme_addr );
    SetCtrlVal (Panels[MODULE_MESS_ERROR], MESS_ERR_TEXTBOX, buffer);   
	

return 0;
} // end function sisVME_ErrorHandling ()



/* --------------------------------------------------------------------------
   VME Error Handling
-------------------------------------------------------------------------- */

int sis_AnyErrorHandling (char *err_messages)
{
	
	int CviErr;
//	char error_msg[MAX_PATHNAME_LEN];
	char buffer[128];


	DisplayPanel (Panels[MODULE_MESS_ERROR]);

	if(err_messages) {
	  sprintf (buffer, "%s    ", err_messages);
      SetCtrlVal (Panels[MODULE_MESS_ERROR], MESS_ERR_TEXTBOX, buffer);   
	 }
	

return 0;
} // end function sisVME_ErrorHandling ()



/* --------------------------------------------------------------------------
   Messages System Handling
-------------------------------------------------------------------------- */

int write_system_messages (char *system_messages, int write_datetime)
{
	int CviErr;
	char buffer[128];
	static char *timeString, *dateString;

	if (write_datetime == PRINT_DATE_YES)  {
	   sprintf (buffer,"\n");
       SetCtrlVal (Panels[MODULE_MESS_SYSTEM], MESS_SYS_TEXTBOX, buffer);   
	   timeString=TimeStr ();	  //get system time pointer
	   dateString=DateStr ();	  // get system date pointer
	   CopyString (buffer, 0, STRING_DATE, 0, strlen(STRING_DATE));
	   CopyString (buffer, strlen(buffer), dateString, 0, 10);
	   CopyString (buffer, strlen(buffer), STRING_TIME, 0, strlen(STRING_TIME));
	   CopyString (buffer, strlen(buffer), timeString, 0, 8);
       SetCtrlVal (Panels[MODULE_MESS_SYSTEM], MESS_SYS_TEXTBOX, buffer);   
	   sprintf (buffer,"\n");
       SetCtrlVal (Panels[MODULE_MESS_SYSTEM], MESS_SYS_TEXTBOX, buffer);   

    }

	sprintf (buffer,"-- %s", system_messages);
	SetCtrlVal (Panels[MODULE_MESS_SYSTEM], MESS_SYS_TEXTBOX, buffer);   

//	if(err_messages) {
//	  sprintf (buffer, "%s    ", err_messages);
//      SetCtrlVal (Panels[MODULE_MESS_ERROR], MESS_ERR_TEXTBOX, buffer);   
//	 }
//	sprintf (buffer, "prot_error=%8x at address=%8x  \n", prot_error,vme_addr );
//    SetCtrlVal (Panels[MODULE_MESS_ERROR], MESS_ERR_TEXTBOX, buffer);   
	

return 0;
} // end function sisVME_ErrorHandling ()

