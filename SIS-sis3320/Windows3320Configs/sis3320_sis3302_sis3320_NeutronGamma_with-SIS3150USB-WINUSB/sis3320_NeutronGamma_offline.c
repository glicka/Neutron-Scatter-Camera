/***************************************************************************/
/*                                                                         */
/*  Project: Neutron/Gamma Detector                                        */
/*                                                                         */
/*  Filename: sis3320_NeutronGamma_offline.c                               */
/*                                                                         */
/*  Funktion: configuration                                                */
/*                                                                         */
/*  Autor:                TH                                               */
/*  date:                 07.09.2006                                       */
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

int local_timer_event_number ;
double OfflineTimerInterval	 ;




int OfflineReadFileAndStart (void) ;
int OfflineReadAndCheckNofEventsFromDataFile(void);
int OfflineReadAndCopyOneEventFromDataFile(unsigned int event_number)  ;


int offline_display_raw_event(void) ;
int offline_display_raw_asyn_event(void);

//int OfflineGetDataFileInfo (void)	 ;
 
//--------------------------------------------------------------------------- 
// Root Menu Call Back
//--------------------------------------------------------------------------- 

void CVICALLBACK CB_OpenPanelOfflineControl (int menuBar, int menuItem, void *callbackData,
        int panel)
{
    switch (menuItem) {
        case MENU_OFFLINE_DIAG_OPENPANEL : {
		 // close other


			closePanelDisplayRaw()  ;
			closePanelDisplayEnergyValue()  ;
			closePanelDisplayEnergySpectrum() ;
            HidePanel(Panels[RUN_CTRL_MENUE]); //Clear Panel 


			gl_uint_Offline_RawSampleLength = 512     ;
			setupPanelDisplayOfflineRaw() ;

		 // Raw panel
			gl_uint_OfflineCheckDisplayRawFlag = 1 ;
			SetCtrlVal (Panels[OFFLINE_CONTROL], OFFLI_CTRL_CHECKBOX_DISPL_RAW,gl_uint_OfflineCheckDisplayRawFlag);  
			if(gl_uint_OfflineCheckDisplayRawFlag == 1) {
				setupPanelDisplayRaw() ;
				openPanelDisplayRaw() ;
			 }
			 else {
            	closePanelDisplayRaw();     //Clear Panel 
			 } 

			// Energy Value Panel
			setupPanelDisplayEnergyValue() ;
			gl_uint_OfflineCheckDisplayEnergyValueFlag = 0 ;
			SetCtrlVal (Panels[OFFLINE_CONTROL], OFFLI_CTRL_CHECKBOX_DISPL_ENER_V,gl_uint_OfflineCheckDisplayEnergyValueFlag);  
			if(gl_uint_OfflineCheckDisplayEnergyValueFlag == 1) {
	 			openPanelDisplayEnergyValue() ;
			 }
			 else {
            	closePanelDisplayEnergyValue(); //Clear Panel 
			 } 

			// Energy Spectrum
			setupPanelDisplayEnergySpectrum() ;
			gl_uint_OfflineCheckDisplayEnergySpectrumFlag = 0 ;
			SetCtrlVal (Panels[OFFLINE_CONTROL], OFFLI_CTRL_CHECKBOX_DISPL_ENSPEC,gl_uint_OfflineCheckDisplayEnergySpectrumFlag);  
			if(gl_uint_OfflineCheckDisplayEnergySpectrumFlag == 1) {
	 			openPanelDisplayEnergySpectrum() ;
			 }
			 else {
           		closePanelDisplayEnergySpectrum(); //Clear Panel 
			 } 
  
			gl_uint_Offline_RunLoopFlag  = 0 ;
			SetCtrlAttribute (Panels[OFFLINE_CONTROL], OFFLI_CTRL_READ_FILE, ATTR_VISIBLE, 1);
			SetCtrlAttribute (Panels[OFFLINE_CONTROL], OFFLI_CTRL_STOP_LOOP, ATTR_VISIBLE, 0);

			gl_uint_OfflineCheckSingleStepFlag  = 1 ;
			SetCtrlVal (Panels[OFFLINE_CONTROL], OFFLI_CTRL_CHECKBOX_SGL_STEP_EN,gl_uint_OfflineCheckSingleStepFlag);  

			gl_uint_OfflineCheckStopIfPileupFlag  = 0 ;
			SetCtrlVal (Panels[OFFLINE_CONTROL], OFFLI_CTRL_CHECKBOX_STOP_IF_PILE, gl_uint_OfflineCheckStopIfPileupFlag);  
			
			
			if (gl_uint_system_status == SYSTEM_STATUS_MODULES_RUNNING) gl_uint_system_status = SYSTEM_STATUS_MODULES_READY ;
			if (gl_uint_system_status == SYSTEM_STATUS_MODULES_CONFIGURED) gl_uint_system_status = SYSTEM_STATUS_MODULES_READY ;
            CheckSystemStatus () ;

	        SetPanelPos(Panels[OFFLINE_CONTROL],DEFINE_PANEL_OFFLINE_CTRL_POS_Y,DEFINE_PANEL_OFFLINE_CTRL_POS_X)  ;   // y, x
			DisplayPanel (Panels[OFFLINE_CONTROL]);
            }
            break;

        }    // end switch menu item
	return ;
}

	  
//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
/* close Panels */
void CVICALLBACK CB_MenuOfflineControl (int menuBar, int menuItem, void *callbackData,
        int panel)
{
    switch (menuItem) {
        case MENUCTRLOF_PANEL_CLOSE : {
//			SetCtrlAttribute (Panels[OFFLINE_CONTROL], OFFLI_CTRL_OFFLINE_TICK, ATTR_ENABLED, OFF);
			closePanelDisplayRaw()  ;
			closePanelDisplayEnergyValue()  ;
			closePanelDisplayEnergySpectrum() ;
            HidePanel(Panels[OFFLINE_CONTROL]); //Clear Panel 
           }  
           break;
        case MENUCTRLOF_FILE_DEFINE_FILENAME : {
			OfflineReadFileAndStart () ;
           }  
           break;
     }  // switch
return;
}



//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int CVICALLBACK CB_OfflineCheckBoxRun (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int check_on ;
	switch (event)
		{
		case EVENT_COMMIT:
  			switch (control)
			{

			  
			  case OFFLI_CTRL_CHECKBOX_SGL_STEP_EN:
				GetCtrlVal (Panels[OFFLINE_CONTROL], OFFLI_CTRL_CHECKBOX_SGL_STEP_EN,&gl_uint_OfflineCheckSingleStepFlag);  
				if(gl_uint_OfflineCheckSingleStepFlag == 0) {
					gl_uint_Offline_PauseLoopFlag  = 0 ;
				}
				break ;			

			  case OFFLI_CTRL_CHECKBOX_STOP_IF_PILE:
				GetCtrlVal (Panels[OFFLINE_CONTROL], OFFLI_CTRL_CHECKBOX_STOP_IF_PILE,&gl_uint_OfflineCheckStopIfPileupFlag);  
				break ;			
			  
		  
			  
			  case OFFLI_CTRL_CHECKBOX_DISPL_RAW:
				GetCtrlVal (Panels[OFFLINE_CONTROL], OFFLI_CTRL_CHECKBOX_DISPL_RAW,&gl_uint_OfflineCheckDisplayRawFlag);  
				if(gl_uint_OfflineCheckDisplayRawFlag == 1) {
					setupPanelDisplayRaw() ;
					openPanelDisplayRaw() ;
				 }
				 else {
            		closePanelDisplayRaw();     //Clear Panel 
				 } 
				break ;			

			  case OFFLI_CTRL_CHECKBOX_DISPL_ENER_V:
				GetCtrlVal (Panels[OFFLINE_CONTROL], OFFLI_CTRL_CHECKBOX_DISPL_ENER_V,&gl_uint_OfflineCheckDisplayEnergyValueFlag);  
				if(gl_uint_OfflineCheckDisplayEnergyValueFlag == 1) {
	 				openPanelDisplayEnergyValue() ;
				 }
				 else {
             		closePanelDisplayEnergyValue(); //Clear Panel 
				 } 
				break ;			

			  case OFFLI_CTRL_CHECKBOX_DISPL_ENSPEC:
				GetCtrlVal (Panels[OFFLINE_CONTROL], OFFLI_CTRL_CHECKBOX_DISPL_ENSPEC,&gl_uint_OfflineCheckDisplayEnergySpectrumFlag);  
				if(gl_uint_OfflineCheckDisplayEnergySpectrumFlag == 1) {
	 				openPanelDisplayEnergySpectrum() ;
				 }
				 else {
             		closePanelDisplayEnergySpectrum(); //Clear Panel 
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
int OfflineReadFileAndStart (void)
{   

unsigned int i_event;
unsigned int uint_OfflineSizeOfDataFormat_Lwords;
unsigned int uint_OfflineSizeOfRawData_Lwords;
 
int size_of_1k_read, size_of_1_read;
int nof_1k_reads, nof_1_reads;
int nof_read, sub_nof_read;
int i, temp, status, select;
char tempFile[MAX_FILENAME_LEN];
int tempErr, dummy, okSema;
char *fileName ;
    double xmin;
    double xmax;
    double ymin;
    double ymax;

unsigned int uint_offline_event_number ;
unsigned int uint_offline_file_event_header ;
unsigned int uint_offline_file_buffer_number ;
unsigned int uint_offline_file_event_number ;
unsigned int uint_offline_file_nof_number ;
unsigned int uint_offline_file_nof_channels ;
unsigned int uint_offline_file_channel_size ;

unsigned int uint_adc_trigger_synch_mode  ;

unsigned int uint_energy_sample_addr1  ;
unsigned int uint_energy_sample_addr2  ;
unsigned int uint_energy_sample_addr3  ;
unsigned int uint_energy_sample_length  ;
unsigned int raw_buffer_length_index  ;



	uint_OfflineSizeOfDataFormat_Lwords  = 10 ;

	GetProjectDir (gl_char_FilePathData);

	select = FileSelectPopup (gl_char_FilePathData, "*.dat", "", 
											  "Define Data File Name", 
											  VAL_OK_BUTTON, 0, 1, 1, 1, 
											  gl_char_FileNameData);

	SetCtrlVal (Panels[OFFLINE_CONTROL], OFFLI_CTRL_STRING_DATAFILE_NAME, gl_char_FileNameData);



	if (select == VAL_EXISTING_FILE_SELECTED) {
		SetCtrlVal (Panels[OFFLINE_CONTROL], OFFLI_CTRL_STRING_DATAFILE_NAME, gl_char_FileNameData);
	 // hier dimm fuctions
	 }
	 else {
		SetCtrlVal (Panels[OFFLINE_CONTROL], OFFLI_CTRL_STRING_DATAFILE_NAME, "no EXISTING_FILE_SELECTED !!");

		SetCtrlVal (Panels[OFFLINE_CONTROL], OFFLI_CTRL_FILE_NOF_MODULES, 0);
		SetCtrlVal (Panels[OFFLINE_CONTROL], OFFLI_CTRL_FILE_READOUT_MODE, 0);

		return -1 ;
	 }


	status = OfflineReadAndCheckNofEventsFromDataFile()  ;
	if (status == 0) {

		SetCtrlVal (Panels[OFFLINE_CONTROL], OFFLI_CTRL_FILE_NUMBER, gl_uint_OfflineFileNumber);
		SetCtrlVal (Panels[OFFLINE_CONTROL], OFFLI_CTRL_FILE_DATA_FORMAT, gl_uint_OfflineDataFormat);
		SetCtrlVal (Panels[OFFLINE_CONTROL], OFFLI_CTRL_FILE_NOF_MODULES, gl_uint_OfflineNofModules);

		SetCtrlVal (Panels[OFFLINE_CONTROL], OFFLI_CTRL_SIS3820_MODE_CLK, ((gl_uint_OfflineSamplingParamters & 0xf0000)>>16) ) ;
		SetCtrlVal (Panels[OFFLINE_CONTROL], OFFLI_CTRL_SIS9300_MODE_CLK,  (gl_uint_OfflineSamplingParamters & 0xf));

		SetCtrlVal (Panels[OFFLINE_CONTROL], OFFLI_CTRL_RAW_DATA_SAMPLE_MODE, gl_uint_OfflineRawSampleModeParameters);


		SetCtrlVal (Panels[OFFLINE_CONTROL], OFFLI_CTRL_MAIN_GATE_LENGTH, ((gl_uint_OfflineMainGateParameters & 0xfff0000)>>16) ) ;
		SetCtrlVal (Panels[OFFLINE_CONTROL], OFFLI_CTRL_MAIN_GATE_PRETRIGGER,  (gl_uint_OfflineMainGateParameters & 0xfff));

		SetCtrlVal (Panels[OFFLINE_CONTROL], OFFLI_CTRL_SAMPLE_RAW_LENGTH, ((gl_uint_OfflineRawDataParameters & 0xfff0000)>>16) ) ;
		SetCtrlVal (Panels[OFFLINE_CONTROL], OFFLI_CTRL_SAMPLE_RAW_STARTINDEX,  (gl_uint_OfflineRawDataParameters & 0xfff));

		SetCtrlVal (Panels[OFFLINE_CONTROL], OFFLI_CTRL_GATE1_LENGTH, ((gl_uint_OfflineGate1Parameters & 0xfff0000)>>16) ) ;
		SetCtrlVal (Panels[OFFLINE_CONTROL], OFFLI_CTRL_GATE1_START_INDEX,  (gl_uint_OfflineGate1Parameters & 0xfff));

		SetCtrlVal (Panels[OFFLINE_CONTROL], OFFLI_CTRL_GATE2_LENGTH, ((gl_uint_OfflineGate2Parameters & 0xfff0000)>>16) ) ;
		SetCtrlVal (Panels[OFFLINE_CONTROL], OFFLI_CTRL_GATE2_START_INDEX,  (gl_uint_OfflineGate2Parameters & 0xfff));

		SetCtrlVal (Panels[OFFLINE_CONTROL], OFFLI_CTRL_GATE3_LENGTH, ((gl_uint_OfflineGate3Parameters & 0xfff0000)>>16) ) ;
		SetCtrlVal (Panels[OFFLINE_CONTROL], OFFLI_CTRL_GATE3_START_INDEX,  (gl_uint_OfflineGate3Parameters & 0xfff));

		SetCtrlVal (Panels[OFFLINE_CONTROL], OFFLI_CTRL_GATE4_LENGTH, ((gl_uint_OfflineGate4Parameters & 0xfff0000)>>16) ) ;
		SetCtrlVal (Panels[OFFLINE_CONTROL], OFFLI_CTRL_GATE4_START_INDEX,  (gl_uint_OfflineGate4Parameters & 0xfff));

		SetCtrlVal (Panels[OFFLINE_CONTROL], OFFLI_CTRL_GATE5_LENGTH, ((gl_uint_OfflineGate5Parameters & 0xfff0000)>>16) ) ;
		SetCtrlVal (Panels[OFFLINE_CONTROL], OFFLI_CTRL_GATE5_START_INDEX,  (gl_uint_OfflineGate5Parameters & 0xfff));

		SetCtrlVal (Panels[OFFLINE_CONTROL], OFFLI_CTRL_GATE6_LENGTH, ((gl_uint_OfflineGate6Parameters & 0xfff0000)>>16) ) ;
		SetCtrlVal (Panels[OFFLINE_CONTROL], OFFLI_CTRL_GATE6_START_INDEX,  (gl_uint_OfflineGate6Parameters & 0xfff));

		SetCtrlVal (Panels[OFFLINE_CONTROL], OFFLI_CTRL_GATE7_LENGTH, ((gl_uint_OfflineGate7Parameters & 0xfff0000)>>16) ) ;
		SetCtrlVal (Panels[OFFLINE_CONTROL], OFFLI_CTRL_GATE7_START_INDEX,  (gl_uint_OfflineGate7Parameters & 0xfff));

		SetCtrlVal (Panels[OFFLINE_CONTROL], OFFLI_CTRL_GATE8_LENGTH, ((gl_uint_OfflineGate8Parameters & 0xfff0000)>>16) ) ;
		SetCtrlVal (Panels[OFFLINE_CONTROL], OFFLI_CTRL_GATE8_START_INDEX,  (gl_uint_OfflineGate8Parameters & 0xfff));

		SetCtrlVal (Panels[OFFLINE_CONTROL], OFFLI_CTRL_SIS_DEVICE,  (gl_uint_OfflineSIS_Device ));
		SetCtrlVal (Panels[OFFLINE_CONTROL], OFFLI_CTRL_GATE_EVENT_LEN,  (gl_uint_OfflineGateEventLength ));

    	raw_buffer_length_index =   gl_uint_OfflineGateEventLength - 1 ;
		setupPanelDisplayOfflineRaw() ;


		gl_uint_Offline_PauseLoopFlag  = 0 ;
		gl_uint_Offline_RunLoopFlag  = 1 ;
		SetCtrlAttribute (Panels[OFFLINE_CONTROL], OFFLI_CTRL_READ_FILE, ATTR_VISIBLE, 0);
		SetCtrlAttribute (Panels[OFFLINE_CONTROL], OFFLI_CTRL_STOP_LOOP, ATTR_VISIBLE, 1);

		uint_offline_event_number = 0 ;
		gl_uint_OfflineCheckSingleStepFlag  = 1 ;
		SetCtrlVal (Panels[OFFLINE_CONTROL], OFFLI_CTRL_CHECKBOX_SGL_STEP_EN,gl_uint_OfflineCheckSingleStepFlag);  


		do {  // loop over events

				// read event header ....
		 		nof_read=fread(&uint_offline_file_event_header,0x4,1,gl_FILE_OfflineDataEvenFilePointer);
		 		nof_read=nof_read+fread(&uint_offline_file_buffer_number,0x4,1,gl_FILE_OfflineDataEvenFilePointer);
		 		nof_read=nof_read+fread(&uint_offline_file_nof_channels,0x4,1,gl_FILE_OfflineDataEvenFilePointer);
		 		nof_read=nof_read+fread(&uint_offline_file_channel_size,0x4,1,gl_FILE_OfflineDataEvenFilePointer);
				if(nof_read!=4) break ;
 
				SetCtrlVal (Panels[OFFLINE_CONTROL], OFFLI_CTRL_FILE_EVENT_HEADER, uint_offline_file_event_header);
				SetCtrlVal (Panels[OFFLINE_CONTROL], OFFLI_CTRL_FILE_BUFFER_NUMBER, uint_offline_file_buffer_number);
				SetCtrlVal (Panels[OFFLINE_CONTROL], OFFLI_CTRL_FILE_EVENT_NOF_CHA, uint_offline_file_nof_channels);
				SetCtrlVal (Panels[OFFLINE_CONTROL], OFFLI_CTRL_FILE_CHANNEL_SIZE, uint_offline_file_channel_size);

		 		gl_uint_OfflineSizeOfEvent =  uint_offline_file_nof_channels * uint_offline_file_channel_size ;
		 		gl_uint_OfflineSizeOfChannelEvent =  uint_offline_file_channel_size;

				uint_OfflineSizeOfRawData_Lwords  =  uint_offline_file_channel_size -  uint_OfflineSizeOfDataFormat_Lwords ;

				for (i_event=0;i_event<uint_offline_file_nof_channels;i_event++) {
				 	nof_read=fread(gl_dma_rd_buffer,0x4,uint_offline_file_channel_size,gl_FILE_OfflineDataEvenFilePointer);
					displayEventDataInformation(gl_dma_rd_buffer)  ;

					
					if (gl_uint_OfflineCheckDisplayRawFlag == 1) {   ; // on
						if ((gl_dma_rd_buffer[9] & 0xffff) != 0 ) {
							deleteRawGraph() ;
							displayEventAdcRawData((gl_dma_rd_buffer[raw_buffer_length_index] & 0xffff), &gl_dma_rd_buffer[raw_buffer_length_index+1], VAL_RED)	;
						}
					}

					uint_offline_event_number++;
					SetCtrlVal (Panels[OFFLINE_CONTROL], OFFLI_CTRL_EVENT_NUMBER, uint_offline_event_number);
    				if ((uint_offline_event_number & 0x1f) == 0) {ProcessSystemEvents (); } 

				   // Pileup check
					if (gl_uint_OfflineCheckStopIfPileupFlag == 1) {
						if ((gl_dma_rd_buffer[3] & 0xff000000) != 0x01000000) {
							gl_uint_OfflineCheckSingleStepFlag  = 1 ;
							SetCtrlVal (Panels[OFFLINE_CONTROL], OFFLI_CTRL_CHECKBOX_SGL_STEP_EN,gl_uint_OfflineCheckSingleStepFlag);  
						}
					}

					if(gl_uint_OfflineCheckSingleStepFlag == 1) {
						gl_uint_Offline_PauseLoopFlag  = 1 ;
						do {
    						ProcessSystemEvents ();  
						} while ((gl_uint_Offline_PauseLoopFlag  == 1) && (gl_uint_Offline_RunLoopFlag  == 1))  ;
					}
					if (gl_uint_Offline_RunLoopFlag == 0) {break;}
				}


			if(gl_uint_OfflineCheckSingleStepFlag == 1) {
				gl_uint_Offline_PauseLoopFlag  = 1 ;
				do {
    				ProcessSystemEvents ();  
				} while ((gl_uint_Offline_PauseLoopFlag  == 1) && (gl_uint_Offline_RunLoopFlag  == 1))  ;
				
			}
    				ProcessSystemEvents ();  
		
		} while (gl_uint_Offline_RunLoopFlag  == 1) ; // erstmal 

		gl_uint_Offline_PauseLoopFlag  = 0 ;
		gl_uint_Offline_RunLoopFlag  = 0 ;
		SetCtrlAttribute (Panels[OFFLINE_CONTROL], OFFLI_CTRL_READ_FILE, ATTR_VISIBLE, 1);
		SetCtrlAttribute (Panels[OFFLINE_CONTROL], OFFLI_CTRL_STOP_LOOP, ATTR_VISIBLE, 0);
	   	fclose(gl_FILE_OfflineDataEvenFilePointer);


	 }		
	 else {
		SetCtrlVal (Panels[OFFLINE_CONTROL], OFFLI_CTRL_STRING_DATAFILE_NAME, "error on reading File");



		return -1 ;
	 }

  return 0;
}



//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int OfflineReadAndCheckNofEventsFromDataFile(void)
{   
char messages_buffer[256] ;           
int nof_read;
int fileStartOfEventByteOffset	   ;
int fileEventArrayLengthByteOffset ;
int fileByteOffset ;

unsigned int  file_event_header  ;
unsigned int  file_event_number  ;
unsigned int  reserved    ;
int event_i  ;

// check file parameter
	gl_FILE_OfflineDataEvenFilePointer=fopen(gl_char_FileNameData,"rb");
	if(gl_FILE_OfflineDataEvenFilePointer == NULL) {
        SetPanelPos(Panels[MODULE_MESS_SYSTEM],60,400)  ;   // y, x
		DisplayPanel (Panels[MODULE_MESS_SYSTEM]);
    	sprintf (messages_buffer, "Data File Open Error \n");
    	write_system_messages (messages_buffer, PRINT_DATE_YES)	   ;
		return -1 ;
	 }

 
	nof_read=fread(&gl_uint_OfflineFileNumber,0x4,0x1,gl_FILE_OfflineDataEvenFilePointer);
	nof_read=nof_read+fread(&gl_uint_OfflineDataFormat,0x4,0x1,gl_FILE_OfflineDataEvenFilePointer);
	nof_read=nof_read+fread(&gl_uint_OfflineNofModules,0x4,0x1,gl_FILE_OfflineDataEvenFilePointer);
	nof_read=nof_read+fread(&gl_uint_OfflineSamplingParamters,0x4,0x1,gl_FILE_OfflineDataEvenFilePointer);

	nof_read=nof_read+fread(&gl_uint_OfflineMainGateParameters,0x4,0x1,gl_FILE_OfflineDataEvenFilePointer);
	nof_read=nof_read+fread(&gl_uint_OfflineRawSampleModeParameters,0x4,0x1,gl_FILE_OfflineDataEvenFilePointer);
	nof_read=nof_read+fread(&gl_uint_OfflineRawDataParameters,0x4,0x1,gl_FILE_OfflineDataEvenFilePointer);

	nof_read=nof_read+fread(&gl_uint_OfflineGate1Parameters,0x4,0x1,gl_FILE_OfflineDataEvenFilePointer);
	nof_read=nof_read+fread(&gl_uint_OfflineGate2Parameters,0x4,0x1,gl_FILE_OfflineDataEvenFilePointer);
	nof_read=nof_read+fread(&gl_uint_OfflineGate3Parameters,0x4,0x1,gl_FILE_OfflineDataEvenFilePointer);
	nof_read=nof_read+fread(&gl_uint_OfflineGate4Parameters,0x4,0x1,gl_FILE_OfflineDataEvenFilePointer);
	nof_read=nof_read+fread(&gl_uint_OfflineGate5Parameters,0x4,0x1,gl_FILE_OfflineDataEvenFilePointer);
	nof_read=nof_read+fread(&gl_uint_OfflineGate6Parameters,0x4,0x1,gl_FILE_OfflineDataEvenFilePointer);
	nof_read=nof_read+fread(&gl_uint_OfflineGate7Parameters,0x4,0x1,gl_FILE_OfflineDataEvenFilePointer);
	nof_read=nof_read+fread(&gl_uint_OfflineGate8Parameters,0x4,0x1,gl_FILE_OfflineDataEvenFilePointer);


	nof_read=nof_read+fread(&gl_uint_OfflineGateEventLength,0x4,0x1,gl_FILE_OfflineDataEvenFilePointer);
	nof_read=nof_read+fread(&gl_uint_OfflineSIS_Device,0x4,0x1,gl_FILE_OfflineDataEvenFilePointer);
	nof_read=nof_read+fread(&reserved,0x4,0x1,gl_FILE_OfflineDataEvenFilePointer);
	nof_read=nof_read+fread(&reserved,0x4,0x1,gl_FILE_OfflineDataEvenFilePointer);
	nof_read=nof_read+fread(&reserved,0x4,0x1,gl_FILE_OfflineDataEvenFilePointer);
	nof_read=nof_read+fread(&reserved,0x4,0x1,gl_FILE_OfflineDataEvenFilePointer);
 
	if(nof_read!=21) return -1 ;

	return 0;
}


//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int CVICALLBACK CB_OfflineReadFileAndStart (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			OfflineReadFileAndStart () ; 
			gl_uint_Offline_RunLoopFlag  = 1 ;
			break;
		}
	return 0;
}

//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int CVICALLBACK CB_Stop_Loop (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			gl_uint_Offline_RunLoopFlag  = 0 ;

			break;
		}
	return 0;
}

//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int CVICALLBACK CB_Sgl_Step_Next (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			gl_uint_Offline_PauseLoopFlag  = 0 ;

			break;
		}
	return 0;
}
//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int offline_display_raw_event(void)
{   

   return 0;
}



//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int offline_display_EnergyValues(void)
{   
   return 0;
}




//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int offline_display_EnergySpectrum(void)
{   
   return 0;
}

    		

