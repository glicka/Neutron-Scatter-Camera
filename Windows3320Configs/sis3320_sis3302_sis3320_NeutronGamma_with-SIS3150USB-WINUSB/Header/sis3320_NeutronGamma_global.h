/***************************************************************************/
/*                                                                         */
/*  Project: Neutron/Gamma Detector                                        */
/*                                                                         */
/*  Filename: sis3320_NeutronGamma_global.h                                */      
/*  Funktion: definition of globals                                        */
/*                                                                         */
/*  Autor:                TH                                               */
/*  date:                 21.09.2006                                       */
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







// --- Programm globale Konstanten ------------------------------------------

#define OFF					 0
#define ON					 1

#define SET_BIT16			 0x10000
#define SET_BIT15			 0x8000
#define SET_BIT14			 0x4000
#define SET_BIT13			 0x2000
#define SET_BIT12			 0x1000
#define SET_BIT11			 0x800
#define SET_BIT10			 0x400
#define SET_BIT9			 0x200
#define SET_BIT8			 0x100
#define SET_BIT7			 0x80
#define SET_BIT6			 0x40
#define SET_BIT5			 0x20
#define SET_BIT4			 0x10
#define SET_BIT3			 0x8
#define SET_BIT2			 0x4
#define SET_BIT1			 0x2
#define SET_BIT0			 0x1


// Panel Open Positions

#define DEFINE_PANEL_MODULE_CONF_POS_Y 			60
#define DEFINE_PANEL_MODULE_CONF_POS_X 			60
				
#define DEFINE_PANEL_DAC_CONF_POS_Y 		60
#define DEFINE_PANEL_DAC_CONF_POS_X 		60

#define DEFINE_PANEL_CLOCK_CONF_POS_Y 		60
#define DEFINE_PANEL_CLOCK_CONF_POS_X 		60

#define DEFINE_PANEL_SAMPLE_CONF_POS_Y 		60
#define DEFINE_PANEL_SAMPLE_CONF_POS_X 		60

#define DEFINE_PANEL_TRIGGER_CONF_POS_Y 		60
#define DEFINE_PANEL_TRIGGER_CONF_POS_X 		60

#define DEFINE_PANEL_SIGNAL_INVERT_CONF_POS_Y 		60
#define DEFINE_PANEL_SIGNAL_INVERT_CONF_POS_X 		60

#define DEFINE_PANEL_GAIN_CONF_POS_Y 		60
#define DEFINE_PANEL_GAI_CONF_POS_X 		60

#define DEFINE_PANEL_ENERGY_FACTOR_CONF_POS_Y 		60
#define DEFINE_PANEL_ENERGY_FACTOR_CONF_POS_X 		60

#define DEFINE_PANEL_DECAY_FACTOR_CONF_POS_Y 		60
#define DEFINE_PANEL_DECAY_FACTOR_CONF_POS_X 		60

#define DEFINE_PANEL_TRIG_RD_MATRIX_CONF_POS_Y 		60
#define DEFINE_PANEL_TRIG_RD_MATRIX_CONF_POS_X 		60


#define DEFINE_PANEL_RUN_CTRL_POS_Y 		45
#define DEFINE_PANEL_RUN_CTRL_POS_X 		10

#define DEFINE_PANEL_OFFLINE_CTRL_POS_Y 		45
#define DEFINE_PANEL_OFFLINE_CTRL_POS_X 		10



#define DEFINE_PANEL_DISPLAY_RAW_POS_Y 			380
#define DEFINE_PANEL_DISPLAY_RAW_POS_X 			10

#define DEFINE_PANEL_DISPLAY_RAW2_POS_Y 			100
#define DEFINE_PANEL_DISPLAY_RAW2_POS_X 			600

#define DEFINE_PANEL_DISPLAY_EVALUES_POS_Y 			340
#define DEFINE_PANEL_DISPLAY_EVALUES_POS_X 			600

#define DEFINE_PANEL_DISPLAY_ENERGY_SPEC_POS_Y		340
#define DEFINE_PANEL_DISPLAY_ENERGY_SPEC_POS_X		10

#define DEFINE_PANEL_DISPLAY_ENERGY_GAUSS_POS_Y		50
#define DEFINE_PANEL_DISPLAY_ENERGY_GAUSS_POS_X		890

#define DEFINE_PANEL_DIAG_PATTERN_POS_Y				45
#define DEFINE_PANEL_DIAG_PATTERN_POS_X				850

		 


#define DEFINE_PANEL_TEST1_MENU_CTRL_POS_Y 		40
#define DEFINE_PANEL_TEST1_MENU_CTRL_POS_X 		10

#define DEFINE_PANEL_TEST1_RAW_POS_Y 			320
#define DEFINE_PANEL_TEST1_RAW_POS_X 			10

#define DEFINE_PANEL_TEST1_HISTO_POS_Y 			320
#define DEFINE_PANEL_TEST1_HISTO_POS_X 			700

#define DEFINE_PANEL_TEST1_FFT_POS_Y 			420
#define DEFINE_PANEL_TEST1_FFT_POS_X 			100

#define DEFINE_PANEL_TEST1_LTERM_POS_Y 			520
#define DEFINE_PANEL_TEST1_LTERM_POS_X 			100




#define SYSTEM_STATUS_NULL        		 	0
#define SYSTEM_STATUS_MODULES_NOT_READY 	1		 // red
#define SYSTEM_STATUS_MODULES_READY			2		 // yellow
#define SYSTEM_STATUS_MODULES_CONFIGURED	3		 // green
#define SYSTEM_STATUS_MODULES_RUNNING		4		 // blue



//#define MAX_NO_OF_MODULES    	16
#define MAX_NO_OF_MODULES    	14
#define MAX_NO_OF_CHANNELS    	(MAX_NO_OF_MODULES * 8)


#define INDEX_MODULE1 			0
#define INDEX_MODULE2 			1
#define INDEX_MODULE3 			2
#define INDEX_MODULE4 			3
#define INDEX_MODULE5 			4
#define INDEX_MODULE6 			5
#define INDEX_MODULE7 			6
#define INDEX_MODULE8 			7
#define INDEX_MODULE9 			8
#define INDEX_MODULE10 			9
#define INDEX_MODULE11 			10
#define INDEX_MODULE12 			11
#define INDEX_MODULE13 			12
#define INDEX_MODULE14 			13


#define NO_OF_ADC_CHANNELS    	8

#define INDEX_ADC_CHANNEL1 		0
#define INDEX_ADC_CHANNEL2 		1
#define INDEX_ADC_CHANNEL3 		2
#define INDEX_ADC_CHANNEL4 		3
#define INDEX_ADC_CHANNEL5 		4
#define INDEX_ADC_CHANNEL6 		5
#define INDEX_ADC_CHANNEL7 		6
#define INDEX_ADC_CHANNEL8 		7




#define ENERGY_SPECTRUM_DISPLAY_FLOAT_FACTOR  	1.0   
#define ENERGY_SPECTRUM_DISPLAY_FACTOR  		1   
#define MAX_NOF_ENERGY_SPECTRUM  				(0x1000*ENERGY_SPECTRUM_DISPLAY_FACTOR)   // 12 bit

#define ENERGY_PEAK_ZOOM_VALUE	(50*ENERGY_SPECTRUM_DISPLAY_FACTOR) 



#define MAX_PATHNAME_LENGTH 	1024
#define MAX_FILENAME_LENGTH 	1024  //including Pathname


#define NORMAL_SIS3150USB_TS_READOUT_LOADER_FILE  	"vme_readout.ldr"   
//#define NORMAL_TS_LOADER_FILE  						"gamma_adc_prog.ldr"   
//#define NORMAL_ADC_TS_LOADER_FILE  					"gamma_adc_prog.ldr"   

#define NORMAL_CONFIGURATION_FILE  					"sis3320_NeutronGamma_gui_config.ini"  



#define STRING_CONFIGURATION_FILE					"SIS3320 NeutronGamma CONFIGURATION File"   
#define STRING_DATE  								"Date: "   
#define STRING_TIME  								"   Time: "   

#define STRING_ADC_MODULES  						"ADC_MODULES" 
#define STRING_CLOCK_MODULE  						"CLOCK_MODULE"   

#define STRING_CLOCK_MODE  							"CLOCK_MODE"   
#define STRING_SIS3320_MODES  						"SIS3320_MODES"   


#define STRING_SIS3150USB_TS_LOADER_FILE  			"SIS3150USB_TS_Readout_Loader_File" 
#define STRING_SAMPLING_PARAMETER  					"SAMPLING_PARAMETER" 


#define STRING_ADC_SIGNAL_INVERT_FLAGS 				"ADC_SIGNAL_INVERT_FLAGS" 
#define STRING_ADC_GAIN_FACTOR_FLAGS 				"ADC_GAIN_FACTOR_FLAGS" 
#define STRING_DAC_OFFSET_VALUES  					"DAC_OFFSET_VALUES" 
#define STRING_FIR_TRIGGER_VALUES  					"FIR_TRIGGER_VALUES" 
#define STRING_ENERGY_FACTOR_VALUES 				"ENERGY_FACTOR_VALUES" 
#define STRING_DECAY_TAU_VALUES						"DECAY_TAU_VALUES" 
#define STRING_ENERGY_PULSE_INVERT_FLAGS			"ENERGY_PULSE_INVERT_FLAGS" 
#define STRING_SIS3150USB_TRIGGER_READOUT_MATRIX	"SIS3150USB_TRIGGER_READOUT_MATRIX" 
#define STRING_RUN_READOUT_MODE						"RUN_READOUT_MODE" 


#define STRING_BLANK				" "   
#define STRING_END_OF_FILE			"END_OF_FILE"   

#define FILE_ACCESS_OK  			0   
#define FILE_ACCESS_NOT_OK  		-1   

#define STATUS_YES  	  			0   
#define STATUS_NO			  		-1   

#define PRINT_DATE_YES 	  			0   
#define PRINT_DATE_NO 	  			-1   


// default configuration values
#define CLOCK_MODULE_CONF_DEFAULT_ADDRESS   		0x38000000 

#define ADC_MODULE_CONF_DEFAULT_BROADCAST_ADDRESS  	0x30000000 
#define ADC_MODULE_CONF_DEFAULT_STARTADDRESS   		0x40000000 
#define ADC_MODULE_CONF_DEFAULT_ADDRESSINC   		0x10000000 


// Common Clock 
#define CLOCK_SIS3820_CONF_DEFAULT_CLOCK_MODE   		0x000000 
#define CLOCK_SIS3820_CONF_DEFAULT_CTRL4_ENABLE_FLAG   	0 
#define CLOCK_SIS3820_CONF_DEFAULT_CTRL3_ENABLE_FLAG   	0 
#define CLOCK_SIS3820_CONF_DEFAULT_CTRL2_ENABLE_FLAG   	0 
#define CLOCK_SIS3820_CONF_DEFAULT_TRIGGERMASK   		0x7F 



#define CLOCK_SIS3320_CONF_DEFAULT_CLOCK_MODE   					4 //  

// SIS3320 Modes
#define SIS3320_CONF_DEFAULT_TRIGGER_MODE_SOURCE   					0 //  
#define SIS3320_CONF_DEFAULT_DUMMY_MODE		   						0 //  
#define SIS3320_CONF_DEFAULT_LEMO_TRIGGER_ENABLE_FLAG   			0 
#define SIS3320_CONF_DEFAULT_LEMO_TIMSTAMPCLR_ENABLE_FLAG   		0 


// Sampling Parameters
#define SAMPLE_MAIN_GATE_LENGTH_DEFAULT  	 		1024 
#define SAMPLE_MAIN_GATE_PRETRIGGER_DELAY_DEFAULT  	128 

#define SAMPLE_GATE1_LENGTH_DEFAULT  	 			1 
#define SAMPLE_GATE1_START_INDEX_DEFAULT  	 		1

#define SAMPLE_GATE2_LENGTH_DEFAULT  	 			1 
#define SAMPLE_GATE2_START_INDEX_DEFAULT  	 		1

#define SAMPLE_GATE3_LENGTH_DEFAULT  	 			1 
#define SAMPLE_GATE3_START_INDEX_DEFAULT  	 		1

#define SAMPLE_GATE4_LENGTH_DEFAULT  	 			1 
#define SAMPLE_GATE4_START_INDEX_DEFAULT  	 		1

#define SAMPLE_GATE5_LENGTH_DEFAULT  	 			1 
#define SAMPLE_GATE5_START_INDEX_DEFAULT  	 		1

#define SAMPLE_GATE6_LENGTH_DEFAULT  	 			1 
#define SAMPLE_GATE6_START_INDEX_DEFAULT  	 		1

#define SAMPLE_GATE7_LENGTH_DEFAULT  	 			1 
#define SAMPLE_GATE7_START_INDEX_DEFAULT  	 		1

#define SAMPLE_GATE8_LENGTH_DEFAULT  	 			1 
#define SAMPLE_GATE8_START_INDEX_DEFAULT  	 		1

#define SAMPLE_RAW_DATA_LENGTH_DEFAULT  	 		1 
#define SAMPLE_RAW_DATA_START_INDEX_DEFAULT  	 	1024
#define SAMPLE_RAW_DATA_MODE_DEFAULT  	 			1


// DAC Offset
#define DAC_OFFSET_DEFAULT  			 	38144 

		 

// Trigger 
#define FIR_TRIGGER_PEAKING_DEFAULT     	10 
#define FIR_TRIGGER_GAP_DEFAULT    			30 
#define FIR_TRIGGER_PULSE_LENGTH_DEFAULT  	20 

#define FIR_TRIGGER_THRESHOLD_CONF_DEFAULT_VALUE   	-1000 
#define FIR_TRIGGER_THRESHOLD_CONF_DISABLE      	0x0 
#define FIR_TRIGGER_THRESHOLD_CONF_GT_OUT_ENABLE	0x1 
#define FIR_TRIGGER_THRESHOLD_CONF_GT_OUT_DISABLE	0x2 
#define FIR_TRIGGER_THRESHOLD_CONF_GT_ZERO_OUT_ENABLE	0x3 
#define FIR_TRIGGER_THRESHOLD_CONF_GT_ZERO_OUT_DISABLE	0x4 


// Energy Factor (default) 
#define ENERGY_FACTOR_DEFAULT  				1.52

// Energy Factor (default) 
//#define DECAY_FACTOR_DEFAULT  				5.00
#define DECAY_TAU_FACTOR_DEFAULT  				0
#define PULSE_INVERT_FLAG_DEFAULT  				0

#define RUN_READOUT_MODE_DEFAULT  				1



#define ADC_SIGNAL_NOT_INVERT      		0x0 
#define FIR_ENERGY_PULSE_NOT_INVERT      	0x0 



#define AQC_STOP_STATUS		  		0   
#define AQC_RUN_STATUS		  		1   



// Running Modes

#define RUNNING_MODE_PC_SINGLE_EVENT		  					0   
#define RUNNING_MODE_PC_MULTI_EVENT_SINGLE_BUFFER				1   
#define RUNNING_MODE_PC_MULTI_EVENT_DOUBLE_BUFFER				2   
#define RUNNING_MODE_SIS3150USB_DSP_LOAD_PROGRAM_TEST			3   
//#define RUNNING_MODE_PC_SIS3150USB_DSP_MULTI_EVENT				2   
//#define RUNNING_MODE_PC_MULTI_EVENT_ASYN_MODE					3   
//#define RUNNING_MODE_PC_SIS3150USB_DSP_MULTI_EVENT_ASYN_MODE	4   


// data file
#define FILE_FORMAT_EVENT_HEADER        	0xDEADBEEF  
#define FILE_FORMAT_EOF_TRAILER        		0x0E0F0E0F  




#define NO_OF_PANEL			 		60	  // Anzahl der Fenster im UIR-File

#define	MAIN				 		0	  // Haupt-Fenster


#define MODULE_MESS_SYSTEM	 		1
#define MODULE_MESS_ERROR	 		2

#define MODULE_PARA_CONF	 		3
#define DAC_PARA_CONF	 			4
#define CLOCK_PARA_CONF		 		5

 
#define TRIG_PARA_CONF	 			6
#define SAMPLE_PARA_CONF	 		7
#define ENERGY_FACTOR_CONF	 		8
#define DECAY_FACTOR_CONF	 		9
#define TRIGGER_READOUT_MATRIX_CONF	10

#define RUN_CTRL_MENUE       		11	  // 
#define OFFLINE_CONTROL       		12	  // 


	  
#define SIGNAL_INVERT_CONF	 		13
#define GAIN_FACTOR_CONF	 		14

#define SAMPLE_HELP_GATE	 		15

	  
	  
#define PANEL_DISPLAY_RAW      		21	  // 
#define PANEL_DISPLAY_EVALUES  		22	  // 
#define PANEL_DISPLAY_ENERGY_SPEC  	23	  // 
#define PANEL_DISPLAY_GAUSS_VALUE  	24	  // 

#define PANEL_DISPLAY_DIAGNOSTIC  	25	  // 
  

  
#define TEST1_MENUE       		34	  // Fenster fuer die Funktionskarten
#define TEST1_RAW       		35	  // Fenster fuer die Funktionskarten
#define TEST1_HISTO       		36	  // Fenster fuer die Funktionskarten
#define TEST1_FFT       		37	  // Fenster fuer die Funktionskarten
#define TEST1_LTERM       		38	  // Fenster fuer die Funktionskarten


#define TEST2_MENUE       		14	  // Fenster fuer die Funktionskarten





#define MESSAGE_PANEL	 	 	26	  // Nachrichten-Fenster

// Menubars
#define NO_OF_MENUBARS	     20	  // Anzahl der Fenster im UIR-File

#define MAIN_MENU_BAR              		0
#define CONFMODULE_MENU_BAR		   		1
#define CONFDAC_MENU_BAR		   		2

#define CONFCLOCK_MENU_BAR		   		3

#define CONFSAMPLE_MENU_BAR		   		4
#define CONFTRIG_MENU_BAR		   		5
#define CONF_ENERGYFACTOR_MENU_BAR		6
#define CONF_DECAYFACTOR_MENU_BAR		7
#define CONF_TRIG_READ_MATRIX_MENU_BAR	8


#define RUNCTRL_MENU_BAR		   		11
#define OFFLINECTRL_MENU_BAR	   		12

#define DISPLAY_GRAPH_RAW_MENU_BAR		13
#define DISPLAY_GRAPH_ENERGY_VAL_MENU_BAR		14
#define DISPLAY_GRAPH_ENERGY_SPEC_MENU_BAR		15



#define CONF_SIGNAL_INVERT_MENU_BAR		   16
#define CONF_GAIN_FACTOR_MENU_BAR		   17

  

// --- Programm globale Variablen -------------------------------------------


extern int Panels[NO_OF_PANEL];		// Feld fuer die einzelnen PanelHandles
extern int MenuBars[NO_OF_MENUBARS];		// Feld fuer die einzelnen PanelHandles




extern char gl_char_FilePathConf[MAX_PATHNAME_LENGTH];
extern char gl_char_FileNameConf[MAX_FILENAME_LENGTH];	 

extern char gl_char_FilePathData[MAX_PATHNAME_LENGTH];
extern char gl_char_FileNameData[MAX_FILENAME_LENGTH];	 
extern char gl_char_FileNameLoaderSIS3150USB_TS[MAX_FILENAME_LENGTH];	 



// configuration globals 
extern unsigned int gl_uint_system_status ;   

// SIS3320 Modules
extern unsigned int gl_uint_SIS3320_BroadcastAddrConf	;
extern unsigned int gl_uint_ModEnableConf[MAX_NO_OF_MODULES]   ;
extern unsigned int gl_uint_ModAddrConf[MAX_NO_OF_MODULES]		;
extern unsigned int gl_uint_SIS3320_250_FlagConf[MAX_NO_OF_MODULES]		;
extern unsigned int gl_uint_SIS3302_FlagConf[MAX_NO_OF_MODULES]		;



// Clock Module
extern unsigned int gl_uint_SIS3820EnableConf   ;
extern unsigned int gl_uint_SIS3820AddrConf	;
extern unsigned int gl_uint_SIS3820_Version 	;


// Common Sample and Energy Parameters
extern unsigned int gl_uint_SIS3820ClockModeConf	;

extern unsigned int gl_uint_SIS3820ClockCtrl4FlagConf	;
extern unsigned int gl_uint_SIS3820ClockCtrl3FlagConf	;
extern unsigned int gl_uint_SIS3820ClockCtrl2FlagConf	;
extern unsigned int gl_uint_SIS3820ClockTriggerMaskConf	;

extern unsigned int  gl_uint_SIS3320ClockModeConf     ;

// Common SIS3150 
extern unsigned int  gl_uint_SIS3320_Trigger_Mode_Source_ModeConf     ;
extern unsigned int  gl_uint_SIS3320_DUMMY_ModeConf     ;
extern unsigned int  gl_uint_SIS3320External_Lemo_Trigger_FlagConf     ;
extern unsigned int  gl_uint_SIS3320External_Lemo_TimestampClr_FlagConf     ;



// NeutronGamma  Common Sample Parameters

extern unsigned int  gl_uint_MainGateLength     ;
extern unsigned int  gl_uint_MainGatePreTriggerDelay     ;

extern unsigned int  gl_uint_Gate1_Length     ;
extern unsigned int  gl_uint_Gate1_StartIndex     ;
extern unsigned int  gl_uint_Gate2_Length     ;
extern unsigned int  gl_uint_Gate2_StartIndex     ;
extern unsigned int  gl_uint_Gate3_Length     ;
extern unsigned int  gl_uint_Gate3_StartIndex     ;
extern unsigned int  gl_uint_Gate4_Length     ;
extern unsigned int  gl_uint_Gate4_StartIndex     ;

extern unsigned int  gl_uint_Gate5_Length     ;
extern unsigned int  gl_uint_Gate5_StartIndex     ;
extern unsigned int  gl_uint_Gate6_Length     ;
extern unsigned int  gl_uint_Gate6_StartIndex     ;
extern unsigned int  gl_uint_Gate7_Length     ;
extern unsigned int  gl_uint_Gate7_StartIndex     ;
extern unsigned int  gl_uint_Gate8_Length     ;
extern unsigned int  gl_uint_Gate8_StartIndex     ;

extern unsigned int  gl_uint_RawSample_Length     ;
extern unsigned int  gl_uint_RawSample_StartIndex     ;

extern unsigned int  gl_uint_RawDataSampleMode     ;
extern unsigned int  gl_uint_RawDataTestMode     ;

// DAC Offset
extern unsigned int  gl_uint_DacOffset_Conf[MAX_NO_OF_MODULES] [NO_OF_ADC_CHANNELS]     ;
extern unsigned int  gl_uint_DacOffset_Inbox[NO_OF_ADC_CHANNELS]     ;
extern unsigned int  gl_uint_DacReadAdcValueLoopFlag     ;


// FIR Trigger Parameters
extern unsigned int  gl_uint_FirTriggerP_Inbox[NO_OF_ADC_CHANNELS]     ;
extern unsigned int  gl_uint_FirTriggerG_Inbox[NO_OF_ADC_CHANNELS]     ;

extern unsigned int  gl_uint_FirTriggerP_Conf[MAX_NO_OF_MODULES] [NO_OF_ADC_CHANNELS]     ;
extern unsigned int  gl_uint_FirTriggerG_Conf[MAX_NO_OF_MODULES] [NO_OF_ADC_CHANNELS]     ;

extern int  gl_int_FirTriggerThresholdValue_Inbox[NO_OF_ADC_CHANNELS]     ;
extern int  gl_int_FirTriggerThresholdValue_Conf[MAX_NO_OF_MODULES] [NO_OF_ADC_CHANNELS]     ;

extern unsigned int  gl_uint_FirTriggerThreshold_GtLtFlag_Inbox[NO_OF_ADC_CHANNELS]     ;
extern unsigned int  gl_uint_FirTriggerThreshold_GtLtFlag_Conf[MAX_NO_OF_MODULES] [NO_OF_ADC_CHANNELS]     ;

extern unsigned int  gl_uint_FirTriggerPulseLength_Inbox[NO_OF_ADC_CHANNELS]     ;
extern unsigned int  gl_uint_FirTriggerPulseLength_Conf[MAX_NO_OF_MODULES] [NO_OF_ADC_CHANNELS]     ;


// ADC Signal Invert Flag
extern unsigned int  gl_uint_ADC_SignalInvertInbox[MAX_NO_OF_MODULES]     ;
extern unsigned int  gl_uint_ADC_SignalInvertConf[MAX_NO_OF_MODULES][NO_OF_ADC_CHANNELS]     ;

// ADC Gain Factor
extern unsigned int  gl_uint_ADC_Gain_FactorInbox[MAX_NO_OF_MODULES]     ;
extern unsigned int  gl_uint_ADC_Gain_FactorConf[MAX_NO_OF_MODULES][NO_OF_ADC_CHANNELS]     ;





//run
extern unsigned int  gl_uint_RunStopStatusFlag     ;
extern unsigned int  gl_uint_RunReadoutMode     ;

extern unsigned int  gl_uint_RunDisableStartClearFlag     ;
extern unsigned int  gl_uint_RunCheckDisplayRawFlag     ;
extern unsigned int  gl_uint_RunCheckDisplayEnergyValueFlag     ;
extern unsigned int  gl_uint_RunCheckDisplayEnergySpectrumFlag     ;
extern unsigned int  gl_uint_RunCheckDisplayDiagnosticFlag     ;
extern unsigned int  gl_uint_RunCheckWrDataToFileFlag     ;

extern unsigned int  gl_uint_RunCheckDisplayDiagnosticFlag     ;
extern unsigned int  gl_uint_RunCheckEnableEnergyFlag   ;

extern unsigned int  gl_uint_RunCheckStopTimeFlag     ;
extern unsigned int  gl_uint_RunCheckStopEventsFlag     ;

extern unsigned int  gl_uint_RunMaxSecondsCounter        ;
extern unsigned int  gl_uint_RunMaxEventCounter        ;
extern unsigned int  gl_uint_RunEventCounter        ;
extern unsigned int  gl_uint_RunEventOldCounter     ;
extern unsigned int  gl_unit_RunOneSecondCounter    ;


// run globals
extern unsigned int gl_uint_ModConfIndexRun[MAX_NO_OF_MODULES]  ;
extern unsigned int gl_uint_ModAddrRun[MAX_NO_OF_MODULES]  ;
extern unsigned int gl_uint_NoOfModulesRun ;


// Display raw
extern unsigned int gl_unit_DisplayRawModuleNumber    ;
extern unsigned int gl_uint_DisplayRawAdcShowChoose ;

extern unsigned short *gl_ushort_displayRawADC1_ptr    ;
extern unsigned short *gl_ushort_displayRawADC2_ptr    ;
extern unsigned short *gl_ushort_displayRawADC3_ptr    ;
extern unsigned short *gl_ushort_displayRawADC4_ptr    ;
extern unsigned short *gl_ushort_displayRawADC5_ptr    ;
extern unsigned short *gl_ushort_displayRawADC6_ptr    ;
extern unsigned short *gl_ushort_displayRawADC7_ptr    ;
extern unsigned short *gl_ushort_displayRawADC8_ptr    ;

extern signed short *gl_short_displayRawADC1_ptr    ;
extern signed short *gl_short_displayRawADC2_ptr    ;
extern signed short *gl_short_displayRawADC3_ptr    ;
extern signed short *gl_short_displayRawADC4_ptr    ;
extern signed short *gl_short_displayRawADC5_ptr    ;
extern signed short *gl_short_displayRawADC6_ptr    ;
extern signed short *gl_short_displayRawADC7_ptr    ;
extern signed short *gl_short_displayRawADC8_ptr    ;

extern unsigned int gl_uint_displayRaw_plot_size    ;
extern unsigned int gl_unit_GraphRawXmin ;
extern unsigned int gl_unit_GraphRawXmax ;
extern unsigned int gl_unit_GraphRawYmin ;
extern unsigned int gl_unit_GraphRawYmax ;

extern unsigned int gl_uint_DisplayRawADC_Header_ID[8]  ;
extern unsigned int gl_uint_DisplayRawADC_TIMESTAMP_UPPER  ;
extern unsigned int gl_uint_DisplayRawADC_TIMESTAMP_LOWER  ;
extern unsigned int gl_uint_DisplayRawADC_FlagInfo[8]  ;



// Display Energy Values
extern unsigned int gl_unit_DisplayEnergyValueModuleNumber    ;
extern unsigned int gl_uint_DisplayEnergyValueAdcShowChoose ;

extern unsigned int gl_uint_displayEnergyValue_plot_size    ;
extern int *gl_int_displayEnergyValueADC1_ptr    ;
extern int *gl_int_displayEnergyValueADC2_ptr    ;
extern int *gl_int_displayEnergyValueADC3_ptr    ;
extern int *gl_int_displayEnergyValueADC4_ptr    ;
extern int *gl_int_displayEnergyValueADC5_ptr    ;
extern int *gl_int_displayEnergyValueADC6_ptr    ;
extern int *gl_int_displayEnergyValueADC7_ptr    ;
extern int *gl_int_displayEnergyValueADC8_ptr    ;

extern unsigned int gl_unit_GraphEnergyValueXmin ;
extern unsigned int gl_unit_GraphEnergyValueXmax ;
extern unsigned int gl_unit_GraphEnergyValueYmin ;
extern unsigned int gl_unit_GraphEnergyValueYmax ;


// Display Energy Spectrum
extern unsigned int gl_unit_DisplayEnergySpectrumModuleNumber    ;
extern unsigned int gl_uint_DisplayEnergySpectrumAdcShowChoose ;

extern unsigned int gl_uint_displayEnergySpectrum_plot_size    ;
extern unsigned int gl_unit_GraphEnergySpectrumXmin ;
extern unsigned int gl_unit_GraphEnergySpectrumXmax ;
extern unsigned int gl_unit_GraphEnergySpectrumYmin ;
extern unsigned int gl_unit_GraphEnergySpectrumYmax ;

extern unsigned int  gl_uint_EnergySpectrumArray[MAX_NO_OF_MODULES][NO_OF_ADC_CHANNELS][MAX_NOF_ENERGY_SPECTRUM]  ;
extern unsigned int  gl_uint_EnergySpectrum2Array[MAX_NO_OF_MODULES][NO_OF_ADC_CHANNELS][MAX_NOF_ENERGY_SPECTRUM]  ;
extern unsigned int  gl_uint_EnergySpectrum3Array[MAX_NO_OF_MODULES][NO_OF_ADC_CHANNELS][MAX_NOF_ENERGY_SPECTRUM]  ;

extern double gl_double_EnergySpectrumGaussXdraw[MAX_NOF_ENERGY_SPECTRUM];
extern double gl_double_gausspos;
extern double gl_double_gaussfwhm;
extern double gl_double_gaussint;
extern double gl_double_MSE;

extern double gl_double_coefs[5] ;
extern double gl_double_xfit[MAX_NOF_ENERGY_SPECTRUM];
extern double gl_double_yinfit[MAX_NOF_ENERGY_SPECTRUM];
extern double gl_double_youtfit[MAX_NOF_ENERGY_SPECTRUM];


// Display Diagnostic

extern unsigned int  gl_uint_CountOfTriggersChannelBasedArray[MAX_NO_OF_CHANNELS]  ;
extern unsigned int  gl_uint_CountOfTriggersEventBasedArray[MAX_NO_OF_CHANNELS]  ;
extern unsigned int  gl_uint_CountOfPileupsTriggerCountBasedArray[16]  ;

// Display Plot Style

extern int  gl_plot_raw_plot_style  ;
extern int  gl_plot_fpga_plot_style  ;
extern int  gl_plot_energy_spec_plot_style  ;
extern int  gl_plot_diag_plot_style  ;

extern int  gl_plot_raw_line_style  ;
extern int  gl_plot_fpga_line_style  ;
extern int  gl_plot_energy_spec_line_style  ;
extern int  gl_plot_diag_line_style  ;

extern int  gl_plot_raw_background_color  ;
extern int  gl_plot_fpga_background_color  ;
extern int  gl_plot_energy_spec_background_color  ;
extern int  gl_plot_diag_background_color  ;

extern int  gl_plot_raw_grid_color  ;
extern int  gl_plot_fpga_grid_color  ;
extern int  gl_plot_energy_spec_grid_color  ;
extern int  gl_plot_diag_grid_color  ;

extern int  gl_plot_raw_plot_color  ;
extern int  gl_plot_fpga_plot_color  ;
extern int  gl_plot_energy_spec_plot_color  ;
extern int  gl_plot_diag_plot_color  ;


// data event file
extern FILE *gl_FILE_DataEvenFilePointer           ;
extern unsigned int  gl_uint_DataEvent_OpenFlag	;
extern unsigned int  gl_uint_DataEvent_FileCounter ;
extern unsigned int  gl_uint_DataFileRunEventCounter ;

extern unsigned int  gl_uint_DataEvent_RunFile_NOF_Energy ;
extern unsigned int  gl_uint_DataEvent_RunFile_EventSize ;
extern unsigned int  gl_uint_DataEvent_RunFile_EventChannelSize ;

extern unsigned int  gl_uint_DataEvent_LWordCounter ;
extern unsigned int  gl_uint_DataEvent_Nof1kLwords   ;
				   

// offline
extern FILE *gl_FILE_OfflineDataEvenFilePointer           ;
extern unsigned int  gl_uint_OfflineDataEvent_OpenFlag	;
extern unsigned int  gl_uint_OfflineDataEvent_FileCounter ;
extern unsigned int  gl_uint_OfflineDataEvent_LWordCounter ;
extern unsigned int  gl_uint_OfflineDataEvent_Nof1kLwords   ;
				   
extern unsigned int  gl_uint_OfflineFileNumber   ;
extern unsigned int  gl_uint_OfflineDataFormat    ; 
extern unsigned int  gl_uint_OfflineNofModules   ;

extern unsigned int  gl_uint_OfflineSamplingParamters   ;

extern unsigned int  gl_uint_OfflineMainGateParameters    ;
extern unsigned int  gl_uint_OfflineRawSampleModeParameters   ;
extern unsigned int  gl_uint_OfflineRawDataParameters   ;
extern unsigned int  gl_uint_OfflineGate1Parameters   ;
extern unsigned int  gl_uint_OfflineGate2Parameters   ;
extern unsigned int  gl_uint_OfflineGate3Parameters   ;
extern unsigned int  gl_uint_OfflineGate4Parameters   ;
extern unsigned int  gl_uint_OfflineGate5Parameters   ;
extern unsigned int  gl_uint_OfflineGate6Parameters   ;
extern unsigned int  gl_uint_OfflineGate7Parameters   ;
extern unsigned int  gl_uint_OfflineGate8Parameters   ;
extern unsigned int  gl_uint_OfflineGateEventLength   ;
extern unsigned int  gl_uint_OfflineSIS_Device   ;


extern unsigned int  gl_uint_OfflineEnergyParameters    ;
extern unsigned int  gl_uint_OfflineEnergyModeLength    ;
extern unsigned int  gl_uint_OfflineReadoutMode  ;

extern unsigned int  gl_uint_OfflineReadoutModeAddr2Addr1  ;
extern unsigned int  gl_uint_OfflineEnergyModeLengthAddr3  ;

extern unsigned int  gl_uint_OfflineSizeOfEvent  ;
extern unsigned int  gl_uint_OfflineSizeOfChannelEvent    ; 
extern unsigned int  gl_uint_OfflineNofEvents    ; 

//extern unsigned int  gl_uint_OfflineCheckDisplayDiagnosticFlag     ;
//extern unsigned int  gl_uint_OfflineCheckDisplayEnergyFlag     ;
extern unsigned int  gl_uint_OfflineCheckDisplayRawFlag     ;
extern unsigned int  gl_uint_OfflineCheckDisplayEnergyValueFlag     ;
extern unsigned int  gl_uint_OfflineCheckDisplayEnergySpectrumFlag     ;



// offline
extern unsigned int  gl_uint_Offline_RawSampleLength     ;
extern unsigned int  gl_uint_Offline_EnergyLength     ;
extern unsigned int  gl_uint_Offline_RunLoopFlag ;     ;
extern unsigned int  gl_uint_Offline_PauseLoopFlag ;     ;
extern unsigned int  gl_uint_OfflineCheckSingleStepFlag ;     ;
extern unsigned int  gl_uint_OfflineCheckStopIfPileupFlag ;     ;

//extern unsigned int gl_dma_rd_buffer[0x100000] ; // 4MByte
extern unsigned int gl_dma_rd_buffer[0x1000000] ; // 64MByte  ; 16MLwords

extern unsigned int gl_dma_rd_adc1_buffer[0x200000] ; // 8MByte 
extern unsigned int gl_dma_rd_adc2_buffer[0x200000] ; // 8MByte 
extern unsigned int gl_dma_rd_adc3_buffer[0x200000] ; // 8MByte 
extern unsigned int gl_dma_rd_adc4_buffer[0x200000] ; // 8MByte 
extern unsigned int gl_dma_rd_adc5_buffer[0x200000] ; // 8MByte 
extern unsigned int gl_dma_rd_adc6_buffer[0x200000] ; // 8MByte 
extern unsigned int gl_dma_rd_adc7_buffer[0x200000] ; // 8MByte 
extern unsigned int gl_dma_rd_adc8_buffer[0x200000] ; // 8MByte 


extern unsigned int  gl_uint_end_sample_address[NO_OF_ADC_CHANNELS]  ;





// --- Prototyps     -----------------------------


int FirstReadConfiguration (void)  ;
int LoadConfiguration (void) ;
int ReadConfiguration (char *path_file) ;
int SaveConfigurationAs (void)	  ;
int SaveConfiguration (char *path_file) ;

int distribute_module_addresses (void)  ;

int CheckSystemStatus (void)  ;

int SystemConfiguration (void)  ;
int DefineRunEnergyFactor (void)  ;



int setupPanelDisplayOfflineRaw(void) ;
int setupPanelDisplayRaw(void) ;
int openPanelDisplayRaw(void) ;
int displayAdcRawData(void) ;
int closePanelDisplayRaw(void)  ;

int displayAdcRawADC_HeaderID(void)  ;
int displayAdcRawTimestamp(void)  ;
int displayAdcRawFlagInfo(void);

int displayEventDataInformation(unsigned int* buffer_ptr)   ;
int displayEventAdcRawData(unsigned int plot_size, unsigned int* buffer_ptr, int plot_color)	;
int deleteRawGraph(void) ;

int displayEventAdcTestFirData(unsigned int plot_size, unsigned int* buffer_ptr, int plot_color)  ;
int deleteTestFirGraph(void) ;


int setupPanelDisplayEnergyValue(void); 
int openPanelDisplayEnergyValue(void)  ;
int closePanelDisplayEnergyValue(void) ;
int DisplayEnergyValue(void)	  ;



int setupPanelDisplayEnergySpectrum(void); 
int openPanelDisplayEnergySpectrum(void)	  ;
int closePanelDisplayEnergySpectrum(void) ;
int DisplayEnergySpectrum(void)	  ;

int openPanelDiagnosticPattern(unsigned int nofModules)	  ;
int closePanelDiagnosticPattern(void) ;
int displayDiagPattern (unsigned int nofModules) ;
int resetDiagPatternArraysAndScaling(void) ; 




int CopyDecayConfvaluesToTable (void) ;								; 
int CopyEnergyFactorConfvaluesToTable (void) ;



int clear_spectrum_histogram(unsigned int module_index, unsigned int channel_index) ;
int clear_all_spectrum_histograms(void) ;



int openPanelTest1Raw(void) ;
int openPanelTest1FFT(void)  ;
int openPanelTest1Histo(void); 
int openPanelTest1LongTerm(void); 


int displayRawData (void) ;
int clear_AdcHistograph (void)  ;
int displayAdcHistograph (void) ;
int displayAdcFFTgraph (void) ;

int ConfigurationSetupAdc (void) ;


int Send_Communication_Command_to_SIS3150_9300_TS1 (unsigned int module_addr, unsigned int mb_cmd) ; 
int Read_Communication_Reply_from_SIS3150_9300_TS1 (unsigned int module_addr, unsigned int* mb_reply);   


// --- Prototypen -----------------------------------------------------------
int sisVME_ErrorHandling (unsigned int prot_error, unsigned int vme_addr, char *err_messages)  ;
int write_system_messages (char *system_messages,  int write_datetime)   ;

int offline_display_raw_event(void)   ;
int offline_display_EnergyValues(void) ;
int offline_display_EnergySpectrum(void) ;
