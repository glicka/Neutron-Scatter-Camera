/***************************************************************************/
/*                                                                         */
/*  Project: Gamma Detector Stockholm                                      */
/*                                                                         */
/*  Filename: sis3150_display_routines.c                                   */
/*                                                                         */
/*  Funktion: configuration                                                */
/*                                                                         */
/*  Autor:                TH                                               */
/*  date:                 07.04.2005                                       */
/*  last modification:    08.06.2005                                       */
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


//extern int  gl_plot_raw_plot_color  ;
//extern int  gl_plot_fpga_plot_color  ;
//extern int  gl_plot_energy_spec_plot_color  ;
//extern int  gl_plot_diag_plot_color  ;


signed int  loc_gl_energy_value_max  ;
signed int  loc_gl_energy_value_min  ;

//--------------------------------------------------------------------------- 
// Local DEFINES (to be put into Include File)                                                              
//--------------------------------------------------------------------------- 


//static double temp;

void gauss_fit (unsigned int gauss_from_x, unsigned int gauss_numpoints, unsigned int* uint_gaussEnergySpectrum_ptr);
double gauss (double x, double a[], int ncoef)	  ;

//static double coefs[5] = {100., 100., 2., 1.0 , 0.1};
//static double xfit[MAX_NOF_ENERGY_SPECTRUM];
//static double yinfit[MAX_NOF_ENERGY_SPECTRUM];
//static double youtfit[MAX_NOF_ENERGY_SPECTRUM];
//static double MSE;
//double gausspos,gaussfwhm,gaussint;


 
//--------------------------------------------------------------------------- 
// Root Menu Call Back
//--------------------------------------------------------------------------- 

unsigned int local_trapez_display_yminmax_freshing_enable ;
void find_energy_max_value_index (unsigned int module_index , unsigned int channel_index , unsigned int* max_value_index) ;

void setdisplayEnergySpectrumZoomPeak (unsigned int peak_value_index_max, unsigned int peak_value_index_min)  ;
int calibrate_spectrum_histograms(unsigned int* uint_calibrateEnergySpectrum_ptr, float float_new_energy_factor) ;

int openPanelDisplayGaussValues(void)  ;


//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 

int DisableZoomCursorsDisplayRaw (void)
{
    double xmin;
    double xmax;
    double ymin;
    double ymax;
   	SetCtrlVal (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_X_POSITION, 0.0);
   	SetCtrlVal (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_Y_POSITION, 0.0);

	SetCtrlAttribute (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_XY_ZOOM_IN_RAW, ATTR_DIMMED, 1);
	SetCtrlAttribute (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_X_ZOOM_IN_RAW, ATTR_DIMMED, 1);
	SetCtrlAttribute (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_Y_ZOOM_IN_RAW, ATTR_DIMMED, 1);
	SetCtrlAttribute (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_GRAPH_RAW, ATTR_NUM_CURSORS, 0);

//	xmin =  (double) gl_unit_defaultGraphRawXmin ;
//	xmax =  (double) gl_unit_defaultGraphRawXmax ;
//	ymin =  (double) gl_unit_defaultGraphRawYmin ;
//	ymax =  (double) gl_unit_defaultGraphRawYmax ;
//	SetAxisScalingMode  (Panels[DIAG_RAW],DIAGPANEL3_GRAPH_RAW, VAL_XAXIS, VAL_MANUAL, xmin, xmax)  ;
//	SetAxisScalingMode  (Panels[DIAG_RAW],DIAGPANEL3_GRAPH_RAW, VAL_LEFT_YAXIS, VAL_MANUAL, ymin, ymax)  ;
	return 0;
}

//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 

int EnableZoomCursorsDisplayRaw (void)
{
    int tempX, tempY;
    double x, y;
    double xmin;
    double xmax;
    double ymin;
    double ymax;

	GetAxisScalingMode  (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_GRAPH_RAW, VAL_XAXIS, VAL_MANUAL, &xmin, &xmax)  ;
	GetAxisScalingMode  (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_GRAPH_RAW, VAL_LEFT_YAXIS, VAL_MANUAL, &ymin, &ymax)  ;
	
	
	tempX = (int) ((xmax - xmin) / 4) ;
	tempY = (int) ((ymax - ymin) / 4) ;

	SetCtrlAttribute (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_GRAPH_RAW, ATTR_NUM_CURSORS, 3);

	// cursor 1
	SetCursorAttribute (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_GRAPH_RAW, 1, ATTR_CURSOR_ENABLED, 1); // enable cursor
	SetCursorAttribute (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_GRAPH_RAW, 1, ATTR_CURSOR_COLOR, VAL_DK_BLUE); 

	SetCursorAttribute (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_GRAPH_RAW, 1, ATTR_CROSS_HAIR_STYLE, VAL_LONG_CROSS); //  
	SetCursorAttribute (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_GRAPH_RAW, 1, ATTR_CURSOR_MODE, VAL_FREE_FORM); //  
	SetCursorAttribute (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_GRAPH_RAW, 1, ATTR_CURSOR_YAXIS, VAL_LEFT_YAXIS); //  
	SetCursorAttribute (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_GRAPH_RAW, 1, ATTR_CURSOR_POINT_STYLE, VAL_EMPTY_CIRCLE); //  

	if (tempX == 0) x = xmin ;
	          else  x = xmin + (double) (tempX )  ;
	if (tempY == 0) y = ymin ;
	          else  y = ymin + (double) (tempY * 3)  ;

   	SetGraphCursor (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_GRAPH_RAW, 1, x, y);
	// cursor 2
	SetCursorAttribute (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_GRAPH_RAW, 2, ATTR_CURSOR_ENABLED, 1); // enable cursor
	SetCursorAttribute (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_GRAPH_RAW, 2, ATTR_CURSOR_COLOR, VAL_DK_BLUE); 

	SetCursorAttribute (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_GRAPH_RAW, 2, ATTR_CROSS_HAIR_STYLE, VAL_LONG_CROSS); //   
	SetCursorAttribute (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_GRAPH_RAW, 2, ATTR_CURSOR_MODE, VAL_FREE_FORM); //  
	SetCursorAttribute (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_GRAPH_RAW, 2, ATTR_CURSOR_YAXIS, VAL_LEFT_YAXIS); //  
	SetCursorAttribute (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_GRAPH_RAW, 2, ATTR_CURSOR_POINT_STYLE, VAL_EMPTY_CIRCLE); //  

	if (tempX == 0) x = xmin ;
	          else  x = xmin + (double) (tempX * 3)  ;
	if (tempY == 0) y = ymin ;
	          else  y = ymin + (double) (tempY)  ;
   	SetGraphCursor (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_GRAPH_RAW, 2, x, y);



	// cursor 3
	SetCursorAttribute (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_GRAPH_RAW, 3, ATTR_CURSOR_ENABLED, 1); // enable cursor
	SetCursorAttribute (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_GRAPH_RAW, 3, ATTR_CURSOR_COLOR, VAL_BLACK); 

	SetCursorAttribute (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_GRAPH_RAW, 3, ATTR_CROSS_HAIR_STYLE, VAL_SHORT_CROSS); //  
	SetCursorAttribute (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_GRAPH_RAW, 3, ATTR_CURSOR_MODE, VAL_SNAP_TO_POINT); //  
	SetCursorAttribute (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_GRAPH_RAW, 3, ATTR_CURSOR_YAXIS, VAL_LEFT_YAXIS); //  
	SetCursorAttribute (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_GRAPH_RAW, 3, ATTR_CURSOR_POINT_STYLE, VAL_DOTTED_EMPTY_CIRCLE); //  

	if (tempX == 0) x = xmin ;
	          else  x = xmin + (double) (tempX * 2)  ;
	if (tempY == 0) y = ymin ;
	          else  y = ymin + (double) (tempY * 2)  ;
   	SetGraphCursor (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_GRAPH_RAW, 3, x, y);


	SetCtrlAttribute (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_XY_ZOOM_IN_RAW, ATTR_DIMMED, 0);
	SetCtrlAttribute (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_X_ZOOM_IN_RAW, ATTR_DIMMED, 0);
	SetCtrlAttribute (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_Y_ZOOM_IN_RAW, ATTR_DIMMED, 0);
	return 0;																					 

}
  


//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 

// setup for offline mode
int setupPanelDisplayOfflineRaw(void) 
{												
    double xmin;
    double xmax;
    double ymin;
    double ymax;
	
	gl_uint_displayRaw_plot_size  = gl_uint_Offline_RawSampleLength ;
	gl_unit_GraphRawXmin = 0x0 ;
	gl_unit_GraphRawXmax = gl_uint_Offline_RawSampleLength-1;
	gl_unit_GraphRawYmin = 0x0 ;

	if (gl_uint_OfflineSIS_Device == 0x3302) {
		gl_unit_GraphRawYmax = 65535 ;
	}
	else {
	 	gl_unit_GraphRawYmax = 4095 ;
	}
	
	xmin =  (double) gl_unit_GraphRawXmin ;
	xmax =  (double) gl_unit_GraphRawXmax ;
	ymin =  (double) gl_unit_GraphRawYmin ;
	ymax =  (double) gl_unit_GraphRawYmax ;
	SetAxisScalingMode  (Panels[PANEL_DISPLAY_RAW],PANEL_RAW_GRAPH_RAW, VAL_XAXIS, VAL_MANUAL, xmin, xmax)  ;
	SetAxisScalingMode  (Panels[PANEL_DISPLAY_RAW],PANEL_RAW_GRAPH_RAW, VAL_LEFT_YAXIS, VAL_MANUAL, ymin, ymax)  ;

	gl_unit_DisplayRawModuleNumber = 1 ;  // module 1
	SetCtrlVal (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_MODULE_NUMBER,gl_unit_DisplayRawModuleNumber);

	gl_uint_DisplayRawAdcShowChoose = 0 ; // all channels
	SetCtrlVal (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_RING_ADC_CHOOSE,gl_uint_DisplayRawAdcShowChoose);


	SetCtrlAttribute (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_GRAPH_RAW, ATTR_CTRL_MODE, VAL_INDICATOR); // only indicator 
	SetCtrlAttribute (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_GRAPH_RAW, ATTR_ENABLE_ZOOM_AND_PAN, 0)  ;   // disable  
	SetCtrlVal (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_CHECKBOX_ZOOM,0);                               // disable   flag
	SetCtrlVal (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_CHECKBOX_CVI_ZOOM,0);                            // disable CVI flag
//	DisableZoomCursorsRaw() ;


   	
	SetCtrlVal (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_T8_LED, OFF);
	SetCtrlVal (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_T7_LED, OFF);
	SetCtrlVal (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_T6_LED, OFF);
	SetCtrlVal (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_T5_LED, OFF);
	SetCtrlVal (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_T4_LED, OFF);
	SetCtrlVal (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_T3_LED, OFF);
	SetCtrlVal (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_T2_LED, OFF);
	SetCtrlVal (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_T1_LED, OFF);
   	
   	
   	DeleteGraphPlot (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_GRAPH_RAW, -1, VAL_IMMEDIATE_DRAW);
	return 0;
}


 	   

//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 

// setup for Running Mode
int setupPanelDisplayRaw(void) 
{												
    double xmin;
    double xmax;
    double ymin;
    double ymax;
	
	gl_uint_displayRaw_plot_size  = gl_uint_RawSample_Length ;
	gl_unit_GraphRawXmin = 0x0 ;
	gl_unit_GraphRawXmax = gl_uint_RawSample_Length-1;
	gl_unit_GraphRawYmin = 0x0 ;

	if (gl_uint_SIS3302_FlagConf[0] == 0)   { 
		gl_unit_GraphRawYmax = 4095 ;
	}
	else {
		gl_unit_GraphRawYmax = 65535 ;
	}	  

	xmin =  (double) gl_unit_GraphRawXmin ;
	xmax =  (double) gl_unit_GraphRawXmax ;
	ymin =  (double) gl_unit_GraphRawYmin ;
	ymax =  (double) gl_unit_GraphRawYmax ;
	SetAxisScalingMode  (Panels[PANEL_DISPLAY_RAW],PANEL_RAW_GRAPH_RAW, VAL_XAXIS, VAL_MANUAL, xmin, xmax)  ;
	SetAxisScalingMode  (Panels[PANEL_DISPLAY_RAW],PANEL_RAW_GRAPH_RAW, VAL_LEFT_YAXIS, VAL_MANUAL, ymin, ymax)  ;

	gl_unit_DisplayRawModuleNumber = 1 ;  // module 1
	SetCtrlVal (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_MODULE_NUMBER,gl_unit_DisplayRawModuleNumber);

	gl_uint_DisplayRawAdcShowChoose = 0 ; // all channels
	SetCtrlVal (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_RING_ADC_CHOOSE,gl_uint_DisplayRawAdcShowChoose);


	SetCtrlAttribute (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_GRAPH_RAW, ATTR_CTRL_MODE, VAL_INDICATOR); // only indicator 
	SetCtrlAttribute (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_GRAPH_RAW, ATTR_ENABLE_ZOOM_AND_PAN, 0)  ;   // disable  
	SetCtrlVal (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_CHECKBOX_ZOOM,0);                               // disable   flag
	SetCtrlVal (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_CHECKBOX_CVI_ZOOM,0);                            // disable CVI flag
	DisableZoomCursorsDisplayRaw() ;


   	
	SetCtrlVal (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_T8_LED, OFF);
	SetCtrlVal (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_T7_LED, OFF);
	SetCtrlVal (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_T6_LED, OFF);
	SetCtrlVal (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_T5_LED, OFF);
	SetCtrlVal (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_T4_LED, OFF);
	SetCtrlVal (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_T3_LED, OFF);
	SetCtrlVal (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_T2_LED, OFF);
	SetCtrlVal (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_T1_LED, OFF);
   	
   	
   	DeleteGraphPlot (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_GRAPH_RAW, -1, VAL_IMMEDIATE_DRAW);
	return 0;
}


//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 

int openPanelDisplayRaw(void) 
{												
	gl_plot_raw_plot_style = VAL_THIN_LINE ;
	gl_plot_raw_line_style = VAL_SOLID ;
	gl_plot_raw_background_color = VAL_WHITE ;
	gl_plot_raw_grid_color = VAL_BLACK ;
	SetCtrlAttribute (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_GRAPH_RAW, ATTR_PLOT_BGCOLOR, gl_plot_raw_background_color); // 
 	SetCtrlAttribute (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_GRAPH_RAW, ATTR_GRID_COLOR, gl_plot_raw_grid_color); // only indicator 

	SetPanelPos(Panels[PANEL_DISPLAY_RAW],DEFINE_PANEL_DISPLAY_RAW_POS_Y,DEFINE_PANEL_DISPLAY_RAW_POS_X)  ;   // y, x
	DisplayPanel (Panels[PANEL_DISPLAY_RAW]);
	return 0;
}
		  
int closePanelDisplayRaw(void) 
{												
	 	SetMenuBarAttribute  (MenuBars[RUNCTRL_MENU_BAR], MENUCTRLRU_WINDOW_RUN_RAW_ACTIV, ATTR_DIMMED, ON);
		gl_uint_RunCheckDisplayRawFlag = 0 ;
		SetCtrlVal (Panels[RUN_CTRL_MENUE], RUN_CTRL_CHECKBOX_DISPL_RAW, 0);  
        HidePanel(Panels[PANEL_DISPLAY_RAW]); //Clear Panel 
	return 0;
}
		  



// Call Backs

//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 

void CVICALLBACK CB_MenuGraphRaw (int menuBar, int menuItem, void *callbackData,
        int panel)
{
    switch (menuItem) {
        case MENUGR_RAW_PANEL_CLOSE : {
			closePanelDisplayRaw() ;
           }  
           break;


        case MENUGR_RAW_PLOT_STYLE_THIN_LINE : {
			gl_plot_raw_plot_style = VAL_THIN_LINE ;
           }  
           break;
        case MENUGR_RAW_PLOT_STYLE_FAT_LINE : {
			gl_plot_raw_plot_style = VAL_FAT_LINE ;
           }  
           break;
        case MENUGR_RAW_PLOT_STYLE_THIN_STEP : {
			gl_plot_raw_plot_style = VAL_THIN_STEP ;
           }  
           break;
        case MENUGR_RAW_PLOT_STYLE_FAT_STEP : {
			gl_plot_raw_plot_style = VAL_FAT_STEP ;
           }  
           break;
        case MENUGR_RAW_PLOT_STYLE_CON_POINTS : {
			gl_plot_raw_plot_style = VAL_CONNECTED_POINTS ;
           }  
           break;

        
        case MENUGR_RAW_LINE_STYLE_SOLID : {
			gl_plot_raw_line_style = VAL_SOLID ;
           }  
           break;
        case MENUGR_RAW_LINE_STYLE_DASH : {
			gl_plot_raw_line_style = VAL_DASH ;
           }  
           break;
        case MENUGR_RAW_LINE_STYLE_DOT : {
			gl_plot_raw_line_style = VAL_DOT ;
           }  
           break;
        case MENUGR_RAW_LINE_STYLE_DASH_DOT : {
			gl_plot_raw_line_style = VAL_DASH_DOT ;
           }  
           break;
        case MENUGR_RAW_LINE_STYLE_DASH_2XDOT : {
			gl_plot_raw_line_style = VAL_DASH_DOT_DOT ;
           }  
           break;


// background color
        case MENUGR_RAW_BACKGR_COLOR_WHITE : {
			gl_plot_raw_background_color = VAL_WHITE ;
           }  
           break;

        case MENUGR_RAW_BACKGR_COLOR_OFFWHITE : {
			gl_plot_raw_background_color = VAL_OFFWHITE ;
           }  
           break;
        case MENUGR_RAW_BACKGR_COLOR_LT_GRAY : {
			gl_plot_raw_background_color = VAL_LT_GRAY ;
           }  
           break;
        case MENUGR_RAW_BACKGR_COLOR_GRAY : {
			gl_plot_raw_background_color = VAL_GRAY ;
           }  
           break;
        case MENUGR_RAW_BACKGR_COLOR_DK_GRAY : {
			gl_plot_raw_background_color = VAL_DK_GRAY ;
           }  
           break;

        case MENUGR_RAW_BACKGR_COLOR_TRANSP : {
			gl_plot_raw_background_color = VAL_TRANSPARENT ;
           }  
           break;

        case MENUGR_RAW_BACKGR_COLOR_BLACK : {
			gl_plot_raw_background_color = VAL_BLACK ;
           }  
           break;


        
// grid color
        case MENUGR_RAW_GRID_COLOR_WHITE : {
			gl_plot_raw_grid_color = VAL_WHITE ;
           }  
           break;

        case MENUGR_RAW_GRID_COLOR_OFFWHITE : {
			gl_plot_raw_grid_color = VAL_OFFWHITE ;
           }  
           break;
        case MENUGR_RAW_GRID_COLOR_LT_GRAY : {
			gl_plot_raw_grid_color = VAL_LT_GRAY ;
           }  
           break;
        case MENUGR_RAW_GRID_COLOR_GRAY : {
			gl_plot_raw_grid_color = VAL_GRAY ;
           }  
           break;
        case MENUGR_RAW_GRID_COLOR_DK_GRAY : {
			gl_plot_raw_grid_color = VAL_DK_GRAY ;
           }  
           break;

        case MENUGR_RAW_GRID_COLOR_TRANSP : {
			gl_plot_raw_grid_color = VAL_TRANSPARENT ;
           }  
           break;

        case MENUGR_RAW_GRID_COLOR_BLACK : {
			gl_plot_raw_grid_color = VAL_BLACK ;
           }  
           break;


     }  // switch

	SetCtrlAttribute (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_GRAPH_RAW, ATTR_PLOT_BGCOLOR, gl_plot_raw_background_color); // 
	SetCtrlAttribute (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_GRAPH_RAW, ATTR_GRID_COLOR, gl_plot_raw_grid_color); // only indicator 
	//displayAdcRawData () ;

return;
}



//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 

// Call Backs
int CVICALLBACK CB_ClosePanelDisplayRaw (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
		 	SetMenuBarAttribute  (MenuBars[RUNCTRL_MENU_BAR], MENUCTRLRU_WINDOW_RUN_RAW_ACTIV, ATTR_DIMMED, ON);
			closePanelDisplayRaw() ;
			break;
		}
	return 0;
}


//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 

int CVICALLBACK CB_PrintPanelRaw (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			SetPrintAttribute (ATTR_BITMAP_PRINTING, 1);
			SetPrintAttribute (ATTR_EJECT_AFTER, 1);
			SetPrintAttribute (ATTR_ORIENTATION, VAL_LANDSCAPE); // VAL_PORTRAIT
			PrintPanel (Panels[PANEL_DISPLAY_RAW], "", 0, VAL_VISIBLE_AREA, 1);   
			break;
		}
	return 0;
}           


//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
 
int CVICALLBACK CB_DisplayRawChooseAdcShow (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
 		  GetCtrlVal (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_RING_ADC_CHOOSE,&gl_uint_DisplayRawAdcShowChoose);
		//  displayAdcRawData () ;
		  break;
	}
	return 0;
} // end function CB_ChooseAdcShow ()



 
//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 

int CVICALLBACK CB_DisplayRawModuleNumber (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int CviErr,i;
	switch (event)
	{
		case EVENT_COMMIT:
 			GetCtrlVal (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_MODULE_NUMBER,&gl_unit_DisplayRawModuleNumber);
	}
	return 0;
} // end function 


//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 

int CVICALLBACK CB_CheckDisplayRaw (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int test ;
	int check_on ;
	switch (event)
		{
		case EVENT_COMMIT:
  			switch (control)
			{
			  case PANEL_RAW_CHECKBOX_ZOOM:
				GetCtrlVal (Panels[PANEL_DISPLAY_RAW],PANEL_RAW_CHECKBOX_ZOOM,&check_on);  //Show in panel Configuration
				if (check_on == 0) { //off
				    SetCtrlAttribute (Panels[PANEL_DISPLAY_RAW],PANEL_RAW_GRAPH_RAW, ATTR_CTRL_MODE, VAL_INDICATOR); // only indicator 
				    SetCtrlAttribute (Panels[PANEL_DISPLAY_RAW],PANEL_RAW_GRAPH_RAW, ATTR_ENABLE_ZOOM_AND_PAN, 0);   // disable  
					SetCtrlVal (Panels[PANEL_DISPLAY_RAW],PANEL_RAW_CHECKBOX_CVI_ZOOM,0);                            // disable CVI flag
					DisableZoomCursorsDisplayRaw() ;
				  }
				  else { // on
				    SetCtrlAttribute (Panels[PANEL_DISPLAY_RAW],PANEL_RAW_GRAPH_RAW, ATTR_CTRL_MODE, VAL_HOT);     // and hot 
					EnableZoomCursorsDisplayRaw() ;
				  }
				break ;			

			  case PANEL_RAW_CHECKBOX_CVI_ZOOM:
				GetCtrlVal (Panels[PANEL_DISPLAY_RAW],PANEL_RAW_CHECKBOX_CVI_ZOOM,&check_on);  //Show in panel Configuration
				if (check_on == 0) { //off
				    SetCtrlAttribute (Panels[PANEL_DISPLAY_RAW],PANEL_RAW_GRAPH_RAW, ATTR_ENABLE_ZOOM_AND_PAN, 0);  // disable  
				  }
				  else { // on
				    SetCtrlAttribute (Panels[PANEL_DISPLAY_RAW],PANEL_RAW_GRAPH_RAW, ATTR_ENABLE_ZOOM_AND_PAN, 1);  // enable  
				    SetCtrlAttribute (Panels[PANEL_DISPLAY_RAW],PANEL_RAW_GRAPH_RAW, ATTR_CTRL_MODE, VAL_HOT);     // and hot 
					SetCtrlVal (Panels[PANEL_DISPLAY_RAW],PANEL_RAW_CHECKBOX_ZOOM,1);  //and enable general zoom
					EnableZoomCursorsDisplayRaw() ;
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

int CVICALLBACK CB_MoveCursor_DisplayRaw (int panel, int control, int event,
                              void *callbackData, int eventData1,  int eventData2)
{
    double x;
    double x1, x2;
    double y;
    double xmin;
    double xmax;
    double ymin;
    double ymax;

    switch (event) {
        case EVENT_COMMIT:
        	GetGraphCursor (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_GRAPH_RAW, 3, &x, &y);
        	SetCtrlVal (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_X_POSITION, x);
        	SetCtrlVal (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_Y_POSITION, y);

        	GetGraphCursor (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_GRAPH_RAW, 1, &x1, &y);
        	GetGraphCursor (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_GRAPH_RAW, 2, &x2, &y);

            break;

        case EVENT_RIGHT_CLICK:
			xmin =  (double) gl_unit_GraphRawXmin ;
			xmax =  (double) gl_unit_GraphRawXmax ;
			ymin =  (double) gl_unit_GraphRawYmin ;
			ymax =  (double) gl_unit_GraphRawYmax ;
			SetAxisScalingMode  (Panels[PANEL_DISPLAY_RAW],PANEL_RAW_GRAPH_RAW, VAL_XAXIS, VAL_MANUAL, xmin, xmax)  ;
			SetAxisScalingMode  (Panels[PANEL_DISPLAY_RAW],PANEL_RAW_GRAPH_RAW, VAL_LEFT_YAXIS, VAL_MANUAL, ymin, ymax)  ;
            break;
        }
    return 0;
}



//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
	  
int CVICALLBACK CB_DisplayRawZoomIn (int panel, int control, int event, void *callbackData,
                        int eventData1, int eventData2)
{
    double x1;
    double x2;
    double y1;
    double y2;
    double temp;
	int i ;
    
    if (event == EVENT_COMMIT)
    {
        
        /* Get the current position of both cursors.  Notive that the        */
        /* position is relative to the Graph's coordinate system (your plots)*/
        GetGraphCursor (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_GRAPH_RAW, 1, &x1, &y1);
        GetGraphCursor (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_GRAPH_RAW, 2, &x2, &y2);
        
        /* Get positive range values, and rescale the Graph */
        if (x1 > x2)
            {
            temp = x1;
            x1 = x2;
            x2 = temp;
            }
        if (y1 > y2)
            {
            temp = y1;
            y1 = y2;
            y2 = temp;
            }

		switch (control)
		{
		  case PANEL_RAW_XY_ZOOM_IN_RAW:
			SetAxisScalingMode  (Panels[PANEL_DISPLAY_RAW],PANEL_RAW_GRAPH_RAW, VAL_XAXIS, VAL_MANUAL, x1, x2)  ;
			SetAxisScalingMode  (Panels[PANEL_DISPLAY_RAW],PANEL_RAW_GRAPH_RAW, VAL_LEFT_YAXIS, VAL_MANUAL, y1, y2)  ;
			break;																						  
		  case PANEL_RAW_X_ZOOM_IN_RAW:
			SetAxisScalingMode  (Panels[PANEL_DISPLAY_RAW],PANEL_RAW_GRAPH_RAW, VAL_XAXIS, VAL_MANUAL, x1, x2)  ;
			break;
		  case PANEL_RAW_Y_ZOOM_IN_RAW:
			SetAxisScalingMode  (Panels[PANEL_DISPLAY_RAW],PANEL_RAW_GRAPH_RAW, VAL_LEFT_YAXIS, VAL_MANUAL, y1, y2)  ;
			break;
		} // end switch (control)

    }
    return 0;
}
	  
	  
	
//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 

int CVICALLBACK CB_DisplayExpand_Raw (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
    double xmin;
    double xmax;
    double ymin;
    double ymax;


	switch (event)
		{
		case EVENT_COMMIT:
			xmin =  (double) gl_unit_GraphRawXmin ;
			xmax =  (double) gl_unit_GraphRawXmax ;
			ymin =  (double) gl_unit_GraphRawYmin ;
			ymax =  (double) gl_unit_GraphRawYmax ;
  			switch (control)
			{
			  case PANEL_RAW_XY_EXPAND_RAW:
				SetAxisScalingMode  (Panels[PANEL_DISPLAY_RAW],PANEL_RAW_GRAPH_RAW, VAL_XAXIS, VAL_MANUAL, xmin, xmax)  ;
				SetAxisScalingMode  (Panels[PANEL_DISPLAY_RAW],PANEL_RAW_GRAPH_RAW, VAL_LEFT_YAXIS, VAL_MANUAL, ymin, ymax)  ;
				break;																						  
			  case PANEL_RAW_X_EXPAND_RAW:
				SetAxisScalingMode  (Panels[PANEL_DISPLAY_RAW],PANEL_RAW_GRAPH_RAW, VAL_XAXIS, VAL_MANUAL, xmin, xmax)  ;
				break;
			  case PANEL_RAW_Y_EXPAND_RAW:
				SetAxisScalingMode  (Panels[PANEL_DISPLAY_RAW],PANEL_RAW_GRAPH_RAW, VAL_LEFT_YAXIS, VAL_MANUAL, ymin, ymax)  ;
				break;
			} // end switch (control)

			break;
		}
	return 0;
}

//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
  
int displayEventDataInformation(unsigned int* buffer_ptr)
{
	unsigned int  temp;
  	SetCtrlVal (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_HEADER_ID,(buffer_ptr[0] & 0xffff));
  	SetCtrlVal (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_TIMESTAMP_UPPER,((buffer_ptr[0] >>16) & 0xffff) );
	SetCtrlVal (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_TIMESTAMP_LOWER,buffer_ptr[1]);

// SIS3302 modification
  	SetCtrlVal (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_PEAKHIGH_INDEX,((buffer_ptr[2] >> 16) & 0xffff) );
  	SetCtrlVal (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_PEAKHIGH_VALUE,(buffer_ptr[2] & 0xffff));

  	SetCtrlVal (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_PILEUP_INFO,((buffer_ptr[3] >> 24) & 0xff) );
  	SetCtrlVal (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_ACCU_GATE1,(buffer_ptr[3] & 0xffffff)); // 24 bit
  	SetCtrlVal (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_ACCU_GATE2,(buffer_ptr[4] & 0xfffffff));// 28 bit
  	SetCtrlVal (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_ACCU_GATE3,(buffer_ptr[5] & 0xfffffff));// 28 bit
  	SetCtrlVal (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_ACCU_GATE4,(buffer_ptr[6] & 0xfffffff));// 28 bit
   
   if (gl_uint_SIS3302_FlagConf[0] == 0)   { 
	// SIS3320
  		SetCtrlVal (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_ACCU_GATE5,(buffer_ptr[7] & 0xffff));
  		SetCtrlVal (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_ACCU_GATE6,((buffer_ptr[8] >>16) & 0xffff) );
  		SetCtrlVal (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_ACCU_GATE7,(buffer_ptr[8] & 0xffff));
  		SetCtrlVal (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_ACCU_GATE8,((buffer_ptr[8] >>16) & 0xffff) );
  		SetCtrlVal (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_TRAILER,(buffer_ptr[9] & 0xffffffff));
   }
   else {
   		GetCtrlVal (Panels[SAMPLE_PARA_CONF],SAMPL_CONF_ACCU_DATA_FORMAT, &temp);
		if (temp == 0) { // 6-Accumulator mode
		// SIS3302 6 x Accumulator
  			SetCtrlVal (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_ACCU_GATE5,(buffer_ptr[7] & 0xfffffff));
  			SetCtrlVal (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_ACCU_GATE6,(buffer_ptr[8] & 0xfffffff) );
  			SetCtrlVal (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_ACCU_GATE7,0);
  			SetCtrlVal (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_ACCU_GATE8,0 );
  			SetCtrlVal (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_TRAILER,(buffer_ptr[9] & 0xffffffff));
   		}
		else {
		// SIS3302 8 x Accumulator
  			SetCtrlVal (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_ACCU_GATE5,(buffer_ptr[7] & 0xfffffff));
  			SetCtrlVal (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_ACCU_GATE6,(buffer_ptr[8] & 0xfffffff) );
  			SetCtrlVal (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_ACCU_GATE7,(buffer_ptr[9] & 0xfffffff));
  			SetCtrlVal (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_ACCU_GATE8,(buffer_ptr[10] & 0xfffffff) );
  			SetCtrlVal (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_TRAILER,(buffer_ptr[11] & 0xffffffff));
   		}
   }

	return 0;
}

//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 

int displayEventAdcRawData(unsigned int plot_size, unsigned int* buffer_ptr, int plot_color)
{
	PlotY (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_GRAPH_RAW, (unsigned short*) buffer_ptr, 
	       plot_size,  VAL_UNSIGNED_SHORT_INTEGER, gl_plot_raw_plot_style, VAL_NO_POINT, gl_plot_raw_line_style, 1, plot_color);
	return 0;
}



//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 

int deleteRawGraph(void)
{
       	DeleteGraphPlot (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_GRAPH_RAW, -1, VAL_IMMEDIATE_DRAW);
	return 0;
}




//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 

int displayAdcRawData()
{
   int  event_i, module_i, channel_i   ;
   int  index   ;
	unsigned int plot_size;

		plot_size =   gl_uint_displayRaw_plot_size ;
       	DeleteGraphPlot (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_GRAPH_RAW, -1, VAL_IMMEDIATE_DRAW);

	

	 if (plot_size > 0) {
      	if ((gl_uint_DisplayRawAdcShowChoose == 0) || (gl_uint_DisplayRawAdcShowChoose == 1)) {	
  			PlotY (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_GRAPH_RAW, gl_ushort_displayRawADC1_ptr, 
  			       plot_size, 
			       VAL_UNSIGNED_SHORT_INTEGER, gl_plot_raw_plot_style, VAL_NO_POINT, gl_plot_raw_line_style, 1, VAL_RED);
		}

      	if ((gl_uint_DisplayRawAdcShowChoose == 0) || (gl_uint_DisplayRawAdcShowChoose == 2)) {	
  			PlotY (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_GRAPH_RAW, gl_ushort_displayRawADC2_ptr, 
  			       plot_size, 
			       VAL_UNSIGNED_SHORT_INTEGER, gl_plot_raw_plot_style, VAL_NO_POINT, gl_plot_raw_line_style, 1, VAL_BLUE);
		}

      	if ((gl_uint_DisplayRawAdcShowChoose == 0) || (gl_uint_DisplayRawAdcShowChoose == 3)) {	
  			PlotY (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_GRAPH_RAW, gl_ushort_displayRawADC3_ptr, 
  			       plot_size, 
			       VAL_UNSIGNED_SHORT_INTEGER, gl_plot_raw_plot_style, VAL_NO_POINT, gl_plot_raw_line_style, 1, VAL_GREEN);
		}
      	
      	if ((gl_uint_DisplayRawAdcShowChoose == 0) || (gl_uint_DisplayRawAdcShowChoose == 4)) {	
  			PlotY (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_GRAPH_RAW, gl_ushort_displayRawADC4_ptr, 
  			       plot_size, 
			       VAL_UNSIGNED_SHORT_INTEGER, gl_plot_raw_plot_style, VAL_NO_POINT, gl_plot_raw_line_style, 1, VAL_CYAN);
		}


      	if ((gl_uint_DisplayRawAdcShowChoose == 0) || (gl_uint_DisplayRawAdcShowChoose == 5)) {	
  			PlotY (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_GRAPH_RAW, gl_ushort_displayRawADC5_ptr, 
  			       plot_size, 
			       VAL_UNSIGNED_SHORT_INTEGER, gl_plot_raw_plot_style, VAL_NO_POINT, gl_plot_raw_line_style, 1, VAL_DK_RED);
		}

      	if ((gl_uint_DisplayRawAdcShowChoose == 0) || (gl_uint_DisplayRawAdcShowChoose == 6)) {	
  			PlotY (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_GRAPH_RAW, gl_ushort_displayRawADC6_ptr, 
  			       plot_size, 
			       VAL_UNSIGNED_SHORT_INTEGER, gl_plot_raw_plot_style, VAL_NO_POINT, gl_plot_raw_line_style, 1, VAL_DK_BLUE);
		}

      	if ((gl_uint_DisplayRawAdcShowChoose == 0) || (gl_uint_DisplayRawAdcShowChoose == 7)) {	
  			PlotY (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_GRAPH_RAW, gl_ushort_displayRawADC7_ptr, 
  			       plot_size, 
			       VAL_UNSIGNED_SHORT_INTEGER, gl_plot_raw_plot_style, VAL_NO_POINT, gl_plot_raw_line_style, 1, VAL_DK_GREEN);
		}
      	
      	if ((gl_uint_DisplayRawAdcShowChoose == 0) || (gl_uint_DisplayRawAdcShowChoose == 8)) {	
  			PlotY (Panels[PANEL_DISPLAY_RAW], PANEL_RAW_GRAPH_RAW, gl_ushort_displayRawADC8_ptr, 
  			       plot_size, 
			       VAL_UNSIGNED_SHORT_INTEGER, gl_plot_raw_plot_style, VAL_NO_POINT, gl_plot_raw_line_style, 1, VAL_DK_CYAN);
		}

	  }

	return 0;
}




/*******************************************************************************/
/*                                                                             */
/*                                                                             */
/*      Energy Values                                                          */
/*                                                                             */
/*                                                                             */
/*******************************************************************************/

int DisableZoomCursorsDisplayEnergyValue (void)
{
    double xmin;
    double xmax;
    double ymin;
    double ymax;

   	//SetCtrlVal (Panels[PANEL_DISPLAY_EVALUES], PANEL_EVAL_X_POSITION, 0);
   	//SetCtrlVal (Panels[PANEL_DISPLAY_EVALUES], PANEL_EVAL_Y_POSITION, 0);
	SetCtrlAttribute (Panels[PANEL_DISPLAY_EVALUES], PANEL_EVAL_XY_ZOOM_IN, ATTR_DIMMED, 1);
	SetCtrlAttribute (Panels[PANEL_DISPLAY_EVALUES], PANEL_EVAL_X_ZOOM_IN, ATTR_DIMMED, 1);
	SetCtrlAttribute (Panels[PANEL_DISPLAY_EVALUES], PANEL_EVAL_Y_ZOOM_IN, ATTR_DIMMED, 1);
	SetCtrlAttribute (Panels[PANEL_DISPLAY_EVALUES], PANEL_EVAL_GRAPH_EVAL1, ATTR_NUM_CURSORS, 0);

//	xmin =  (double) gl_unit_defaultGraphRawXmin ;
//	xmax =  (double) gl_unit_defaultGraphRawXmax ;
//	ymin =  (double) gl_unit_defaultGraphRawYmin ;
//	ymax =  (double) gl_unit_defaultGraphRawYmax ;
//	SetAxisScalingMode  (Panels[DIAG_RAW],DIAGPANEL3_GRAPH_RAW, VAL_XAXIS, VAL_MANUAL, xmin, xmax)  ;
//	SetAxisScalingMode  (Panels[DIAG_RAW],DIAGPANEL3_GRAPH_RAW, VAL_LEFT_YAXIS, VAL_MANUAL, ymin, ymax)  ;
	return 0;
}



//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 

int EnableZoomCursorsDisplayEnergyValue (void)
{
    int tempX, tempY;
    double x, y;
    double xmin;
    double xmax;
    double ymin;
    double ymax;

	GetAxisScalingMode  (Panels[PANEL_DISPLAY_EVALUES], PANEL_EVAL_GRAPH_EVAL1, VAL_XAXIS, VAL_MANUAL, &xmin, &xmax)  ;
	GetAxisScalingMode  (Panels[PANEL_DISPLAY_EVALUES], PANEL_EVAL_GRAPH_EVAL1, VAL_LEFT_YAXIS, VAL_MANUAL, &ymin, &ymax)  ;
	
	
	tempX = (int) ((xmax - xmin) / 4) ;
	tempY = (int) ((ymax - ymin) / 4) ;

	SetCtrlAttribute (Panels[PANEL_DISPLAY_EVALUES], PANEL_EVAL_GRAPH_EVAL1, ATTR_NUM_CURSORS, 3);

	// cursor 1
	SetCursorAttribute (Panels[PANEL_DISPLAY_EVALUES], PANEL_EVAL_GRAPH_EVAL1, 1, ATTR_CURSOR_ENABLED, 1); // enable cursor
	SetCursorAttribute (Panels[PANEL_DISPLAY_EVALUES], PANEL_EVAL_GRAPH_EVAL1, 1, ATTR_CURSOR_COLOR, VAL_DK_BLUE); 

	SetCursorAttribute (Panels[PANEL_DISPLAY_EVALUES], PANEL_EVAL_GRAPH_EVAL1, 1, ATTR_CROSS_HAIR_STYLE, VAL_LONG_CROSS); //  
	SetCursorAttribute (Panels[PANEL_DISPLAY_EVALUES], PANEL_EVAL_GRAPH_EVAL1, 1, ATTR_CURSOR_MODE, VAL_FREE_FORM); //  
	SetCursorAttribute (Panels[PANEL_DISPLAY_EVALUES], PANEL_EVAL_GRAPH_EVAL1, 1, ATTR_CURSOR_YAXIS, VAL_LEFT_YAXIS); //  
	SetCursorAttribute (Panels[PANEL_DISPLAY_EVALUES], PANEL_EVAL_GRAPH_EVAL1, 1, ATTR_CURSOR_POINT_STYLE, VAL_EMPTY_CIRCLE); //  

	if (tempX == 0) x = xmin ;
	          else  x = xmin + (double) (tempX )  ;
	if (tempY == 0) y = ymin ;
	          else  y = ymin + (double) (tempY * 3)  ;

   	SetGraphCursor (Panels[PANEL_DISPLAY_EVALUES], PANEL_EVAL_GRAPH_EVAL1, 1, x, y);


	
	// cursor 2
	SetCursorAttribute (Panels[PANEL_DISPLAY_EVALUES], PANEL_EVAL_GRAPH_EVAL1, 2, ATTR_CURSOR_ENABLED, 1); // enable cursor
	SetCursorAttribute (Panels[PANEL_DISPLAY_EVALUES], PANEL_EVAL_GRAPH_EVAL1, 2, ATTR_CURSOR_COLOR, VAL_DK_BLUE); 

	SetCursorAttribute (Panels[PANEL_DISPLAY_EVALUES], PANEL_EVAL_GRAPH_EVAL1, 2, ATTR_CROSS_HAIR_STYLE, VAL_LONG_CROSS); //   
	SetCursorAttribute (Panels[PANEL_DISPLAY_EVALUES], PANEL_EVAL_GRAPH_EVAL1, 2, ATTR_CURSOR_MODE, VAL_FREE_FORM); //  
	SetCursorAttribute (Panels[PANEL_DISPLAY_EVALUES], PANEL_EVAL_GRAPH_EVAL1, 2, ATTR_CURSOR_YAXIS, VAL_LEFT_YAXIS); //  
	SetCursorAttribute (Panels[PANEL_DISPLAY_EVALUES], PANEL_EVAL_GRAPH_EVAL1, 2, ATTR_CURSOR_POINT_STYLE, VAL_EMPTY_CIRCLE); //  

	if (tempX == 0) x = xmin ;
	          else  x = xmin + (double) (tempX * 3)  ;
	if (tempY == 0) y = ymin ;
	          else  y = ymin + (double) (tempY)  ;
   	SetGraphCursor (Panels[PANEL_DISPLAY_EVALUES], PANEL_EVAL_GRAPH_EVAL1, 2, x, y);



	// cursor 3
	SetCursorAttribute (Panels[PANEL_DISPLAY_EVALUES], PANEL_EVAL_GRAPH_EVAL1, 3, ATTR_CURSOR_ENABLED, 1); // enable cursor
	SetCursorAttribute (Panels[PANEL_DISPLAY_EVALUES], PANEL_EVAL_GRAPH_EVAL1, 3, ATTR_CURSOR_COLOR, VAL_BLACK); 

	SetCursorAttribute (Panels[PANEL_DISPLAY_EVALUES], PANEL_EVAL_GRAPH_EVAL1, 3, ATTR_CROSS_HAIR_STYLE, VAL_SHORT_CROSS); //  
	SetCursorAttribute (Panels[PANEL_DISPLAY_EVALUES], PANEL_EVAL_GRAPH_EVAL1, 3, ATTR_CURSOR_MODE, VAL_SNAP_TO_POINT); //  
	SetCursorAttribute (Panels[PANEL_DISPLAY_EVALUES], PANEL_EVAL_GRAPH_EVAL1, 3, ATTR_CURSOR_YAXIS, VAL_LEFT_YAXIS); //  
	SetCursorAttribute (Panels[PANEL_DISPLAY_EVALUES], PANEL_EVAL_GRAPH_EVAL1, 3, ATTR_CURSOR_POINT_STYLE, VAL_DOTTED_EMPTY_CIRCLE); //  

	if (tempX == 0) x = xmin ;
	          else  x = xmin + (double) (tempX * 2)  ;
	if (tempY == 0) y = ymin ;
	          else  y = ymin + (double) (tempY * 2)  ;
   	SetGraphCursor (Panels[PANEL_DISPLAY_EVALUES], PANEL_EVAL_GRAPH_EVAL1, 3, x, y);


	SetCtrlAttribute (Panels[PANEL_DISPLAY_EVALUES], PANEL_EVAL_XY_ZOOM_IN, ATTR_DIMMED, 0);
	SetCtrlAttribute (Panels[PANEL_DISPLAY_EVALUES], PANEL_EVAL_X_ZOOM_IN, ATTR_DIMMED, 0);
	SetCtrlAttribute (Panels[PANEL_DISPLAY_EVALUES], PANEL_EVAL_Y_ZOOM_IN, ATTR_DIMMED, 0);
	return 0;																				 

}
  

//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 

int setupPanelDisplayEnergyValue(void) 
{												
    double xmin;
    double xmax;
    double ymin;
    double ymax;
	unsigned int temp_index ;
	
	gl_uint_displayEnergyValue_plot_size  = gl_uint_RawSample_Length ;
	gl_unit_GraphEnergyValueXmin = 0x0 ;
	gl_unit_GraphEnergyValueXmax = gl_uint_RawSample_Length - 1;
//	gl_unit_GraphRawYmin = 0x0 ;
//	gl_unit_GraphRawYmax = 16383 ;
	  
	xmin =  (double) gl_unit_GraphEnergyValueXmin ;
	xmax =  (double) gl_unit_GraphEnergyValueXmax ;
//	ymin =  (double) gl_unit_GraphRawYmin ;
//	ymax =  (double) gl_unit_GraphRawYmax ;
	SetAxisScalingMode  (Panels[PANEL_DISPLAY_EVALUES],PANEL_EVAL_GRAPH_EVAL1, VAL_XAXIS, VAL_MANUAL, xmin, xmax)  ;
//	SetAxisScalingMode  (Panels[PANEL_DISPLAY_EVALUES],PANEL_EVAL_GRAPH_EVAL1, VAL_LEFT_YAXIS, VAL_MANUAL, ymin, ymax)  ;

	gl_unit_DisplayEnergyValueModuleNumber = 1 ;  // module 1
	SetCtrlVal (Panels[PANEL_DISPLAY_EVALUES], PANEL_EVAL_MODULE_NUMBER,gl_unit_DisplayEnergyValueModuleNumber);

	gl_uint_DisplayEnergyValueAdcShowChoose = 0 ; // all channels
	SetCtrlVal (Panels[PANEL_DISPLAY_EVALUES], PANEL_EVAL_RING_ADC_CHOOSE,gl_uint_DisplayEnergyValueAdcShowChoose);

	temp_index =  gl_uint_ModConfIndexRun[gl_unit_DisplayEnergyValueModuleNumber-1] ;


	SetCtrlAttribute (Panels[PANEL_DISPLAY_EVALUES], PANEL_EVAL_GRAPH_EVAL1, ATTR_CTRL_MODE, VAL_INDICATOR); // only indicator 
	SetCtrlAttribute (Panels[PANEL_DISPLAY_EVALUES], PANEL_EVAL_GRAPH_EVAL1, ATTR_ENABLE_ZOOM_AND_PAN, 0)  ;   // disable  
	SetCtrlVal (Panels[PANEL_DISPLAY_EVALUES], PANEL_EVAL_CHECKBOX_ZOOM,0);                               // disable   flag
	SetCtrlVal (Panels[PANEL_DISPLAY_EVALUES], PANEL_EVAL_CHECKBOX_CVI_ZOOM,0);                            // disable CVI flag
	DisableZoomCursorsDisplayEnergyValue() ;

	gl_int_displayEnergyValueADC1_ptr = (int *) &gl_dma_rd_buffer ; 
	gl_int_displayEnergyValueADC2_ptr = (int *) &gl_dma_rd_buffer ; 
	gl_int_displayEnergyValueADC3_ptr = (int *) &gl_dma_rd_buffer ; 
	gl_int_displayEnergyValueADC4_ptr = (int *) &gl_dma_rd_buffer ; 
	gl_int_displayEnergyValueADC5_ptr = (int *) &gl_dma_rd_buffer ; 
	gl_int_displayEnergyValueADC6_ptr = (int *) &gl_dma_rd_buffer ; 
	gl_int_displayEnergyValueADC7_ptr = (int *) &gl_dma_rd_buffer ; 
	gl_int_displayEnergyValueADC8_ptr = (int *) &gl_dma_rd_buffer ; 


   	DeleteGraphPlot (Panels[PANEL_DISPLAY_EVALUES], PANEL_EVAL_GRAPH_EVAL1, -1, VAL_IMMEDIATE_DRAW);

	loc_gl_energy_value_max = -50000000  ;
	loc_gl_energy_value_min =  50000000 ;

	return 0;
}

//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 

int openPanelDisplayEnergyValue(void) 
{												
	gl_plot_fpga_plot_style = VAL_THIN_LINE ;
	gl_plot_fpga_line_style = VAL_SOLID ;
	gl_plot_fpga_background_color = VAL_WHITE ;
	gl_plot_fpga_grid_color = VAL_BLACK ;
	SetCtrlAttribute (Panels[PANEL_DISPLAY_EVALUES], PANEL_EVAL_GRAPH_EVAL1, ATTR_PLOT_BGCOLOR, gl_plot_fpga_background_color); // 
	SetCtrlAttribute (Panels[PANEL_DISPLAY_EVALUES], PANEL_EVAL_GRAPH_EVAL1, ATTR_GRID_COLOR, gl_plot_fpga_grid_color); // only indicator 

	
	SetPanelPos(Panels[PANEL_DISPLAY_EVALUES],DEFINE_PANEL_DISPLAY_EVALUES_POS_Y,DEFINE_PANEL_DISPLAY_EVALUES_POS_X)  ;   // y, x
	local_trapez_display_yminmax_freshing_enable = 1 ;
	DisplayPanel (Panels[PANEL_DISPLAY_EVALUES]);
	return 0;
}

//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
		  
int closePanelDisplayEnergyValue(void) 
{												
	 	SetMenuBarAttribute  (MenuBars[RUNCTRL_MENU_BAR], MENUCTRLRU_WINDOW_RUN_FPGA_ACTIV, ATTR_DIMMED, ON);
		gl_uint_RunCheckDisplayEnergyValueFlag = 0 ;
		SetCtrlVal (Panels[RUN_CTRL_MENUE], RUN_CTRL_CHECKBOX_DISPL_ENER_V, 0);  
        HidePanel(Panels[PANEL_DISPLAY_EVALUES]); //Clear Panel 
	return 0;
}



//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 

void CVICALLBACK CB_MenuGraphEnergyValue (int menuBar, int menuItem, void *callbackData,
        int panel)
{
    switch (menuItem) {
        case MENUGR_ENE_PANEL_CLOSE : {
			closePanelDisplayEnergyValue() ;
           }  
           break;

        case MENUGR_ENE_PLOT_STYLE_THIN_LINE : {
			gl_plot_fpga_plot_style = VAL_THIN_LINE ;
           }  
           break;
        case MENUGR_ENE_PLOT_STYLE_FAT_LINE : {
			gl_plot_fpga_plot_style = VAL_FAT_LINE ;
           }  
           break;
        case MENUGR_ENE_PLOT_STYLE_THIN_STEP : {
			gl_plot_fpga_plot_style = VAL_THIN_STEP ;
           }  
           break;
        case MENUGR_ENE_PLOT_STYLE_FAT_STEP : {
			gl_plot_fpga_plot_style = VAL_FAT_STEP ;
           }  
           break;
        case MENUGR_ENE_PLOT_STYLE_CON_POINTS : {
			gl_plot_fpga_plot_style = VAL_CONNECTED_POINTS ;
           }  
           break;

        
        case MENUGR_ENE_LINE_STYLE_SOLID : {
			gl_plot_fpga_line_style = VAL_SOLID ;
           }  
           break;
        case MENUGR_ENE_LINE_STYLE_DASH : {
			gl_plot_fpga_line_style = VAL_DASH ;
           }  
           break;
        case MENUGR_ENE_LINE_STYLE_DOT : {
			gl_plot_fpga_line_style = VAL_DOT ;
           }  
           break;
        case MENUGR_ENE_LINE_STYLE_DASH_DOT : {
			gl_plot_fpga_line_style = VAL_DASH_DOT ;
           }  
           break;
        case MENUGR_ENE_LINE_STYLE_DASH_2XDOT : {
			gl_plot_fpga_line_style = VAL_DASH_DOT_DOT ;
           }  
           break;


// background color
        case MENUGR_ENE_BACKGR_COLOR_WHITE : {
			gl_plot_fpga_background_color = VAL_WHITE ;
           }  
           break;

        case MENUGR_ENE_BACKGR_COLOR_OFFWHITE : {
			gl_plot_fpga_background_color = VAL_OFFWHITE ;
           }  
           break;
        case MENUGR_ENE_BACKGR_COLOR_LT_GRAY : {
			gl_plot_fpga_background_color = VAL_LT_GRAY ;
           }  
           break;
        case MENUGR_ENE_BACKGR_COLOR_GRAY : {
			gl_plot_fpga_background_color = VAL_GRAY ;
           }  
           break;
        case MENUGR_ENE_BACKGR_COLOR_DK_GRAY : {
			gl_plot_fpga_background_color = VAL_DK_GRAY ;
           }  
           break;

        case MENUGR_ENE_BACKGR_COLOR_TRANSP : {
			gl_plot_fpga_background_color = VAL_TRANSPARENT ;
           }  
           break;

        case MENUGR_ENE_BACKGR_COLOR_BLACK : {
			gl_plot_fpga_background_color = VAL_BLACK ;
           }  
           break;


        
// grid color
        case MENUGR_ENE_GRID_COLOR_WHITE : {
			gl_plot_fpga_grid_color = VAL_WHITE ;
           }  
           break;

        case MENUGR_ENE_GRID_COLOR_OFFWHITE : {
			gl_plot_fpga_grid_color = VAL_OFFWHITE ;
           }  
           break;
        case MENUGR_ENE_GRID_COLOR_LT_GRAY : {
			gl_plot_fpga_grid_color = VAL_LT_GRAY ;
           }  
           break;
        case MENUGR_ENE_GRID_COLOR_GRAY : {
			gl_plot_fpga_grid_color = VAL_GRAY ;
           }  
           break;
        case MENUGR_ENE_GRID_COLOR_DK_GRAY : {
			gl_plot_fpga_grid_color = VAL_DK_GRAY ;
           }  
           break;

        case MENUGR_ENE_GRID_COLOR_TRANSP : {
			gl_plot_fpga_grid_color = VAL_TRANSPARENT ;
           }  
           break;

        case MENUGR_ENE_GRID_COLOR_BLACK : {
			gl_plot_fpga_grid_color = VAL_BLACK ;
           }  
           break;
 
     }  // switch

	SetCtrlAttribute (Panels[PANEL_DISPLAY_EVALUES], PANEL_EVAL_GRAPH_EVAL1, ATTR_PLOT_BGCOLOR, gl_plot_fpga_background_color); // 
	SetCtrlAttribute (Panels[PANEL_DISPLAY_EVALUES], PANEL_EVAL_GRAPH_EVAL1, ATTR_GRID_COLOR, gl_plot_fpga_grid_color); // only indicator 

	//DisplayEnergyValue () ;

return;
}

	 
	 


//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 

int CVICALLBACK CB_ClosePanelDisplayEnergyValue (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			closePanelDisplayEnergyValue() ;
			break;
		}
	return 0;
}




//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int CVICALLBACK CB_DisplayEnergyValueChooseAdcShow (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	unsigned int temp_index ;
	switch (event)
	{
		case EVENT_COMMIT:
 		  GetCtrlVal (Panels[PANEL_DISPLAY_EVALUES], PANEL_EVAL_RING_ADC_CHOOSE,&gl_uint_DisplayEnergyValueAdcShowChoose);
		  if (gl_uint_DisplayEnergyValueAdcShowChoose == 0) {
			temp_index =  gl_uint_ModConfIndexRun[gl_unit_DisplayEnergyValueModuleNumber-1] ;
		  }
		  else {
			temp_index =  gl_uint_ModConfIndexRun[gl_unit_DisplayEnergyValueModuleNumber-1] ;
		  }
		  
		//  DisplayEnergyValue () ;
		  break;
	}
	return 0;
} // end function CB_ChooseAdcShow ()


 

//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int CVICALLBACK CB_DisplayEnergyValueModuleNumber (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int CviErr,i;
	unsigned int temp_index ;
	switch (event)
	{
		case EVENT_COMMIT:
 			GetCtrlVal (Panels[PANEL_DISPLAY_EVALUES], PANEL_EVAL_MODULE_NUMBER,&gl_unit_DisplayEnergyValueModuleNumber);
			if (gl_uint_Offline_RunLoopFlag == 1) {
				offline_display_EnergyValues () ;
			}
			else {
				temp_index =  gl_uint_ModConfIndexRun[gl_unit_DisplayEnergyValueModuleNumber-1] ;
				DisplayEnergyValue () ;
			}
		  break;
	}
	return 0;
} // end function 




//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int CVICALLBACK CB_CheckDisplayEnergyValue (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int test ;
	int check_on ;
	switch (event)
		{
		case EVENT_COMMIT:
  			switch (control)
			{
			  case PANEL_EVAL_CHECKBOX_ZOOM:
				GetCtrlVal (Panels[PANEL_DISPLAY_EVALUES],PANEL_EVAL_CHECKBOX_ZOOM,&check_on);  //Show in panel Configuration
				if (check_on == 0) { //off
				    SetCtrlAttribute (Panels[PANEL_DISPLAY_EVALUES],PANEL_EVAL_GRAPH_EVAL1, ATTR_CTRL_MODE, VAL_INDICATOR); // only indicator 
				    SetCtrlAttribute (Panels[PANEL_DISPLAY_EVALUES],PANEL_EVAL_GRAPH_EVAL1, ATTR_ENABLE_ZOOM_AND_PAN, 0);   // disable  
					SetCtrlVal (Panels[PANEL_DISPLAY_EVALUES],PANEL_EVAL_CHECKBOX_CVI_ZOOM,0);                            // disable CVI flag
					DisableZoomCursorsDisplayEnergyValue() ;
				  }
				  else { // on
				    SetCtrlAttribute (Panels[PANEL_DISPLAY_EVALUES],PANEL_EVAL_GRAPH_EVAL1, ATTR_CTRL_MODE, VAL_HOT);     // and hot 
					EnableZoomCursorsDisplayEnergyValue() ;
				  }
				break ;			

			  case PANEL_EVAL_CHECKBOX_CVI_ZOOM:
				GetCtrlVal (Panels[PANEL_DISPLAY_EVALUES],PANEL_EVAL_CHECKBOX_CVI_ZOOM,&check_on);  //Show in panel Configuration
				if (check_on == 0) { //off
				    SetCtrlAttribute (Panels[PANEL_DISPLAY_EVALUES],PANEL_EVAL_GRAPH_EVAL1, ATTR_ENABLE_ZOOM_AND_PAN, 0);  // disable  
				  }
				  else { // on
				    SetCtrlAttribute (Panels[PANEL_DISPLAY_EVALUES],PANEL_EVAL_GRAPH_EVAL1, ATTR_ENABLE_ZOOM_AND_PAN, 1);  // enable  
				    SetCtrlAttribute (Panels[PANEL_DISPLAY_EVALUES],PANEL_EVAL_GRAPH_EVAL1, ATTR_CTRL_MODE, VAL_HOT);     // and hot 
					SetCtrlVal (Panels[PANEL_DISPLAY_EVALUES],PANEL_EVAL_CHECKBOX_ZOOM,1);  //and enable general zoom
					EnableZoomCursorsDisplayEnergyValue() ;
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
int CVICALLBACK CB_MoveCursor_DisplayEnergyValue (int panel, int control, int event,
                              void *callbackData, int eventData1,  int eventData2)
{
    double x;
    double x1, x2;
    double y;
    double xmin;
    double xmax;
    double ymin;
    double ymax;

    switch (event) {
        case EVENT_COMMIT:
        	GetGraphCursor (Panels[PANEL_DISPLAY_EVALUES], PANEL_EVAL_GRAPH_EVAL1, 3, &x, &y);
        	SetCtrlVal (Panels[PANEL_DISPLAY_EVALUES], PANEL_EVAL_X_POSITION, x);
        	SetCtrlVal (Panels[PANEL_DISPLAY_EVALUES], PANEL_EVAL_Y_POSITION, y);

        	GetGraphCursor (Panels[PANEL_DISPLAY_EVALUES], PANEL_EVAL_GRAPH_EVAL1, 1, &x1, &y);
        	GetGraphCursor (Panels[PANEL_DISPLAY_EVALUES], PANEL_EVAL_GRAPH_EVAL1, 2, &x2, &y);

            break;

        case EVENT_RIGHT_CLICK:
			xmin =  (double) gl_unit_GraphEnergyValueXmin ;
			xmax =  (double) gl_unit_GraphEnergyValueXmax ;
 			ymin =  (double) gl_unit_GraphEnergyValueYmin ;
 			ymax =  (double) gl_unit_GraphEnergyValueYmax ;
			SetAxisScalingMode  (Panels[PANEL_DISPLAY_EVALUES],PANEL_EVAL_GRAPH_EVAL1, VAL_XAXIS, VAL_MANUAL, xmin, xmax)  ;
 			SetAxisScalingMode  (Panels[PANEL_DISPLAY_EVALUES],PANEL_EVAL_GRAPH_EVAL1, VAL_LEFT_YAXIS, VAL_AUTOSCALE, ymin, ymax)  ;
            break;
        }
    return 0;
}


//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int CVICALLBACK CB_DisplayEnergyValueZoomIn (int panel, int control, int event, void *callbackData,
                        int eventData1, int eventData2)
{
    double x1;
    double x2;
    double y1;
    double y2;
    double temp;
	int i ;
    
    if (event == EVENT_COMMIT)
        {
        
        /* Get the current position of both cursors.  Notive that the        */
        /* position is relative to the Graph's coordinate system (your plots)*/
        GetGraphCursor (Panels[PANEL_DISPLAY_EVALUES], PANEL_EVAL_GRAPH_EVAL1, 1, &x1, &y1);
        GetGraphCursor (Panels[PANEL_DISPLAY_EVALUES], PANEL_EVAL_GRAPH_EVAL1, 2, &x2, &y2);
        
        /* Get positive range values, and rescale the Graph */
        if (x1 > x2)
            {
            temp = x1;
            x1 = x2;
            x2 = temp;
            }
        if (y1 > y2)
            {
            temp = y1;
            y1 = y2;
            y2 = temp;
            }

		switch (control)
		{
		  case PANEL_EVAL_XY_ZOOM_IN:
			SetAxisScalingMode  (Panels[PANEL_DISPLAY_EVALUES],PANEL_EVAL_GRAPH_EVAL1, VAL_XAXIS, VAL_MANUAL, x1, x2)  ;
			SetAxisScalingMode  (Panels[PANEL_DISPLAY_EVALUES],PANEL_EVAL_GRAPH_EVAL1, VAL_LEFT_YAXIS, VAL_MANUAL, y1, y2)  ;
			break;																						  
		  case PANEL_EVAL_X_ZOOM_IN:
			SetAxisScalingMode  (Panels[PANEL_DISPLAY_EVALUES],PANEL_EVAL_GRAPH_EVAL1, VAL_XAXIS, VAL_MANUAL, x1, x2)  ;
			break;
		  case PANEL_EVAL_Y_ZOOM_IN:
			SetAxisScalingMode  (Panels[PANEL_DISPLAY_EVALUES],PANEL_EVAL_GRAPH_EVAL1, VAL_LEFT_YAXIS, VAL_MANUAL, y1, y2)  ;
			break;
		} // end switch (control)

        }
    return 0;
}
	  
	  
	  

//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int CVICALLBACK CB_Expand_DisplayEnergyValue (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
    double xmin;
    double xmax;
    double ymin;
    double ymax;


	switch (event)
		{
		case EVENT_COMMIT:
			local_trapez_display_yminmax_freshing_enable = 1 ;

			xmin =  (double) gl_unit_GraphEnergyValueXmin ;
			xmax =  (double) gl_unit_GraphEnergyValueXmax ;
 			ymin =  (double) gl_unit_GraphEnergyValueYmin ;
 			ymax =  (double) gl_unit_GraphEnergyValueYmax ;
  			switch (control)
			{
			  case PANEL_EVAL_XY_EXPAND:
				SetAxisScalingMode  (Panels[PANEL_DISPLAY_EVALUES],PANEL_EVAL_GRAPH_EVAL1, VAL_XAXIS, VAL_MANUAL, xmin, xmax)  ;
				SetAxisScalingMode  (Panels[PANEL_DISPLAY_EVALUES],PANEL_EVAL_GRAPH_EVAL1, VAL_LEFT_YAXIS, VAL_AUTOSCALE, ymin, ymax)  ;
				break;																						  
			  case PANEL_EVAL_X_EXPAND:
				SetAxisScalingMode  (Panels[PANEL_DISPLAY_EVALUES],PANEL_EVAL_GRAPH_EVAL1, VAL_XAXIS, VAL_MANUAL, xmin, xmax)  ;
				break;
			  case PANEL_EVAL_Y_EXPAND:
				SetAxisScalingMode  (Panels[PANEL_DISPLAY_EVALUES],PANEL_EVAL_GRAPH_EVAL1, VAL_LEFT_YAXIS, VAL_AUTOSCALE, ymin, ymax)  ;
				break;
			} // end switch (control)


			
			break;
		}
	loc_gl_energy_value_max = -50000000  ;
	loc_gl_energy_value_min =  50000000 ;

			
			local_trapez_display_yminmax_freshing_enable = 1 ;
	return 0;
}

			  
    	 
 
//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int CVICALLBACK CB_SetTrapezDisplayYScale (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int CviErr;
	int ymin_value, ymax_value;	
	switch (event)
	{
		case EVENT_COMMIT:
			
			GetCtrlVal (Panels[PANEL_DISPLAY_EVALUES], PANEL_EVAL_TRAPEZ_YMIN_SCALE, &ymin_value);
			GetCtrlVal (Panels[PANEL_DISPLAY_EVALUES], PANEL_EVAL_TRAPEZ_YMAX_SCALE, &ymax_value);
			if (ymin_value >= ymax_value)  {
				ymax_value = ymin_value + 500 ;
				SetCtrlVal (Panels[PANEL_DISPLAY_EVALUES], PANEL_EVAL_TRAPEZ_YMIN_SCALE, ymin_value);
				SetCtrlVal (Panels[PANEL_DISPLAY_EVALUES], PANEL_EVAL_TRAPEZ_YMAX_SCALE, ymax_value);
			}
			
			SetAxisScalingMode  (Panels[PANEL_DISPLAY_EVALUES],PANEL_EVAL_GRAPH_EVAL1, VAL_LEFT_YAXIS, VAL_MANUAL, ymin_value, ymax_value)  ;

			break;
	}
	local_trapez_display_yminmax_freshing_enable = 0 ;
	return 0;
} // end function  ()

  
//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int displayEventAdcTestFirData(unsigned int plot_size, unsigned int* buffer_ptr, int plot_color)
{
   	int  i   ;
	unsigned short *gl_unshort_display_ptr    ;
	signed short *gl_short_display_ptr    ;
    signed short dummy16 ;
    unsigned int uint_dummy32 ;
    signed int dummy32[0x10000] ;

	gl_short_display_ptr = (unsigned short*) &buffer_ptr[0] ; 
	gl_unshort_display_ptr = (unsigned short*) &buffer_ptr[0] ; 
	for (i=0;i<plot_size;i++) {
		//dummy16 =  *(gl_short_display_ptr+i) +0x8000 ;
		//dummy32[i] = (signed int)  dummy16 * 2 ;
		dummy16 =  *(gl_short_display_ptr+i)   ;
		uint_dummy32 = (unsigned int)  *(gl_unshort_display_ptr+i)   ;
		dummy32[i] =   uint_dummy32   ;
	}
	PlotY (Panels[PANEL_DISPLAY_EVALUES], PANEL_EVAL_GRAPH_EVAL1, dummy32, plot_size, 
			       VAL_INTEGER, gl_plot_fpga_plot_style, VAL_NO_POINT, gl_plot_fpga_line_style, 1, plot_color);
	return 0;
}




//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int deleteTestFirGraph(void)
{
       	DeleteGraphPlot (Panels[PANEL_DISPLAY_EVALUES], PANEL_EVAL_GRAPH_EVAL1, -1, VAL_IMMEDIATE_DRAW);
	return 0;
}
  
  
#define test_energy_value_max_min				
 	 
int DisplayEnergyValue(void)
{
   int  i   ;
   int  event_i, module_i, channel_i   ;
   int  index   ;
	unsigned int plot_size;
    int ymax, ymin;
    double double_ymax, double_ymin;
    signed short dummy[0x10000] ;
    
		plot_size =   2 * (gl_uint_displayEnergyValue_plot_size  - 2);
       	DeleteGraphPlot (Panels[PANEL_DISPLAY_EVALUES], PANEL_EVAL_GRAPH_EVAL1, -1, VAL_IMMEDIATE_DRAW);
 for (i=0;i<plot_size;i++) {
	dummy[i] =  *(gl_short_displayRawADC1_ptr+i) +0x8000 ;
 }
      	if ((gl_uint_DisplayEnergyValueAdcShowChoose == 0) || (gl_uint_DisplayEnergyValueAdcShowChoose == 1)) {	
  			PlotY (Panels[PANEL_DISPLAY_EVALUES], PANEL_EVAL_GRAPH_EVAL1, dummy, 
  			       plot_size, 
			       //VAL_INTEGER, gl_plot_fpga_plot_style, VAL_NO_POINT, gl_plot_fpga_line_style, 1, VAL_RED);
			       VAL_SHORT_INTEGER, gl_plot_fpga_plot_style, VAL_NO_POINT, gl_plot_fpga_line_style, 1, VAL_RED);

      //	if ((gl_uint_DisplayEnergyValueAdcShowChoose == 0) || (gl_uint_DisplayEnergyValueAdcShowChoose == 1)) {	
  	//		PlotY (Panels[PANEL_DISPLAY_EVALUES], PANEL_EVAL_GRAPH_EVAL1, gl_int_displayEnergyValueADC1_ptr, 
  	//		       plot_size, 
	//		       VAL_INTEGER, gl_plot_fpga_plot_style, VAL_NO_POINT, gl_plot_fpga_line_style, 1, VAL_RED);

#ifdef test_energy_value_max_min				
		  	for (i=0;i<plot_size;i++) {
		    	if ( *(gl_int_displayEnergyValueADC1_ptr+i) > loc_gl_energy_value_max ) {
					loc_gl_energy_value_max  = *(gl_int_displayEnergyValueADC1_ptr+i) ;
		    	}
				
		    	if ( *(gl_int_displayEnergyValueADC1_ptr+i) < loc_gl_energy_value_min ) {
					loc_gl_energy_value_min  = *(gl_int_displayEnergyValueADC1_ptr+i) ;
		    	}
		  	 }
 			SetCtrlVal (Panels[PANEL_DISPLAY_EVALUES], PANEL_EVAL_TRAPEZ_ENERGY_MAX, loc_gl_energy_value_max);
			SetCtrlVal (Panels[PANEL_DISPLAY_EVALUES], PANEL_EVAL_TRAPEZ_ENERGY_MIN, loc_gl_energy_value_min);
#endif
		}
	return 0;
}



/*******************************************************************************/
/*                                                                             */
/*                                                                             */
/*      Energy Spectrum                                                        */
/*                                                                             */
/*                                                                             */
/*******************************************************************************/

int DisableZoomCursorsDisplayEnergySpectrum (void)
{
    double xmin;
    double xmax;
    double ymin;
    double ymax;

   	SetCtrlVal (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_X_POSITION, 0.0);
   	SetCtrlVal (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_Y_POSITION, 0.0);
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_XY_ZOOM_IN, ATTR_DIMMED, 1);
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_X_ZOOM_IN, ATTR_DIMMED, 1);
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_Y_ZOOM_IN, ATTR_DIMMED, 1);
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_0, ATTR_NUM_CURSORS, 0);
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_1, ATTR_NUM_CURSORS, 0);
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_2, ATTR_NUM_CURSORS, 0);
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_3, ATTR_NUM_CURSORS, 0);
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_4, ATTR_NUM_CURSORS, 0);
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_5, ATTR_NUM_CURSORS, 0);
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_6, ATTR_NUM_CURSORS, 0);
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_7, ATTR_NUM_CURSORS, 0);
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_8, ATTR_NUM_CURSORS, 0);

	return 0;
}

								   


//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int EnableZoomCursorsDisplayEnergySpectrum (void)
{
    int tempX, tempY;
    double x, y;
    double xmin;
    double xmax;
    double ymin;
    double ymax;

	GetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_0, VAL_XAXIS, VAL_MANUAL, &xmin, &xmax)  ;
	GetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_0, VAL_LEFT_YAXIS, VAL_MANUAL, &ymin, &ymax)  ;
	
	
	tempX = (int) ((xmax - xmin) / 4) ;
	tempY = (int) ((ymax - ymin) / 4) ;

	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_0, ATTR_NUM_CURSORS, 3);

	// cursor 1
	SetCursorAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_0, 1, ATTR_CURSOR_ENABLED, 1); // enable cursor
	SetCursorAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_0, 1, ATTR_CURSOR_COLOR, VAL_DK_BLUE); 

	SetCursorAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_0, 1, ATTR_CROSS_HAIR_STYLE, VAL_LONG_CROSS); //  
	SetCursorAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_0, 1, ATTR_CURSOR_MODE, VAL_FREE_FORM); //  
	SetCursorAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_0, 1, ATTR_CURSOR_YAXIS, VAL_LEFT_YAXIS); //  
	SetCursorAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_0, 1, ATTR_CURSOR_POINT_STYLE, VAL_EMPTY_CIRCLE); //  

	if (tempX == 0) x = xmin ;
	          else  x = xmin + (double) (tempX )  ;
	if (tempY == 0) y = ymin ;
	          else  y = ymin + (double) (tempY * 3)  ;

   	SetGraphCursor (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_0, 1, x, y);


	
	// cursor 2
	SetCursorAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_0, 2, ATTR_CURSOR_ENABLED, 1); // enable cursor
	SetCursorAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_0, 2, ATTR_CURSOR_COLOR, VAL_DK_BLUE); 

	SetCursorAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_0, 2, ATTR_CROSS_HAIR_STYLE, VAL_LONG_CROSS); //   
	SetCursorAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_0, 2, ATTR_CURSOR_MODE, VAL_FREE_FORM); //  
	SetCursorAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_0, 2, ATTR_CURSOR_YAXIS, VAL_LEFT_YAXIS); //  
	SetCursorAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_0, 2, ATTR_CURSOR_POINT_STYLE, VAL_EMPTY_CIRCLE); //  

	if (tempX == 0) x = xmin ;
	          else  x = xmin + (double) (tempX * 3)  ;
	if (tempY == 0) y = ymin ;
	          else  y = ymin + (double) (tempY)  ;
   	SetGraphCursor (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_0, 2, x, y);



	// cursor 3
	SetCursorAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_0, 3, ATTR_CURSOR_ENABLED, 1); // enable cursor
	SetCursorAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_0, 3, ATTR_CURSOR_COLOR, VAL_BLACK); 

	SetCursorAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_0, 3, ATTR_CROSS_HAIR_STYLE, VAL_SHORT_CROSS); //  
	SetCursorAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_0, 3, ATTR_CURSOR_MODE, VAL_SNAP_TO_POINT); //  
	SetCursorAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_0, 3, ATTR_CURSOR_YAXIS, VAL_LEFT_YAXIS); //  
	SetCursorAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_0, 3, ATTR_CURSOR_POINT_STYLE, VAL_DOTTED_EMPTY_CIRCLE); //  

	if (tempX == 0) x = xmin ;
	          else  x = xmin + (double) (tempX * 2)  ;
	if (tempY == 0) y = ymin ;
	          else  y = ymin + (double) (tempY * 2)  ;
   	SetGraphCursor (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_0, 3, x, y);


	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_XY_ZOOM_IN, ATTR_DIMMED, 0);
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_X_ZOOM_IN, ATTR_DIMMED, 0);
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_Y_ZOOM_IN, ATTR_DIMMED, 0);
	return 0;																				 

}
  



//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int setupPanelDisplayEnergySpectrum(void) 
{												
    double xmin;
    double xmax;
    double ymin;
    double ymax;
	
	gl_uint_displayEnergySpectrum_plot_size  = MAX_NOF_ENERGY_SPECTRUM ;
	gl_unit_GraphEnergySpectrumXmin = 0x0 ;
	gl_unit_GraphEnergySpectrumXmax = MAX_NOF_ENERGY_SPECTRUM-1;
 	gl_unit_GraphEnergySpectrumYmin = 0x0 ;
 	gl_unit_GraphEnergySpectrumYmax = 100 ;
	  
	xmin =  (double) gl_unit_GraphEnergySpectrumXmin ;
	xmax =  (double) gl_unit_GraphEnergySpectrumXmax ;
 	ymin =  (double) gl_unit_GraphEnergySpectrumYmin ;
 	ymax =  (double) gl_unit_GraphEnergySpectrumYmax ;

	
	SetCtrlVal (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_ENERGY_XMIN_SCALE, (unsigned int)(xmin/ENERGY_SPECTRUM_DISPLAY_FLOAT_FACTOR) );
	SetCtrlVal (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_ENERGY_XMAX_SCALE, (unsigned int)(xmax/ENERGY_SPECTRUM_DISPLAY_FLOAT_FACTOR) ) ;

	
	SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_0, VAL_XAXIS, VAL_MANUAL, xmin, xmax)  ;
	SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_0, VAL_LEFT_YAXIS, VAL_AUTOSCALE, ymin, ymax)  ;
//	SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_0, VAL_LEFT_YAXIS, VAL_MANUAL, ymin, ymax)  ;

	SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_1, VAL_XAXIS, VAL_MANUAL, xmin, xmax)  ;
	SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_1, VAL_LEFT_YAXIS, VAL_AUTOSCALE, ymin, ymax)  ;
	SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_2, VAL_XAXIS, VAL_MANUAL, xmin, xmax)  ;
	SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_2, VAL_LEFT_YAXIS, VAL_AUTOSCALE, ymin, ymax)  ;
	SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_3, VAL_XAXIS, VAL_MANUAL, xmin, xmax)  ;
	SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_3, VAL_LEFT_YAXIS, VAL_AUTOSCALE, ymin, ymax)  ;
	SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_4, VAL_XAXIS, VAL_MANUAL, xmin, xmax)  ;
	SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_4, VAL_LEFT_YAXIS, VAL_AUTOSCALE, ymin, ymax)  ;
	SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_5, VAL_XAXIS, VAL_MANUAL, xmin, xmax)  ;
	SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_5, VAL_LEFT_YAXIS, VAL_AUTOSCALE, ymin, ymax)  ;
	SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_6, VAL_XAXIS, VAL_MANUAL, xmin, xmax)  ;
	SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_6, VAL_LEFT_YAXIS, VAL_AUTOSCALE, ymin, ymax)  ;
	SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_7, VAL_XAXIS, VAL_MANUAL, xmin, xmax)  ;
	SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_7, VAL_LEFT_YAXIS, VAL_AUTOSCALE, ymin, ymax)  ;
	SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_8, VAL_XAXIS, VAL_MANUAL, xmin, xmax)  ;
	SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_8, VAL_LEFT_YAXIS, VAL_AUTOSCALE, ymin, ymax)  ;




	gl_unit_DisplayEnergySpectrumModuleNumber = 1 ;  // module 1
	SetCtrlVal (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_MODULE_NUMBER,gl_unit_DisplayEnergySpectrumModuleNumber);

	gl_uint_DisplayEnergySpectrumAdcShowChoose = 1 ; // adc channel 1
	SetCtrlVal (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_RING_ADC_CHOOSE,gl_uint_DisplayEnergySpectrumAdcShowChoose);


	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_0, ATTR_CTRL_MODE, VAL_INDICATOR); // only indicator 
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_0, ATTR_ENABLE_ZOOM_AND_PAN, 0)  ;   // disable  
	SetCtrlVal (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_CHECKBOX_ZOOM,0);                               // disable   flag
	//SetCtrlVal (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_CHECKBOX_CVI_ZOOM,0);                            // disable CVI flag
//	DisableZoomCursorsEnergyValue() ;
														  
	
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_0, ATTR_VISIBLE, 1);
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_1, ATTR_VISIBLE, 0);
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_2, ATTR_VISIBLE, 0);
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_3, ATTR_VISIBLE, 0);
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_4, ATTR_VISIBLE, 0);
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_5, ATTR_VISIBLE, 0);
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_6, ATTR_VISIBLE, 0);
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_7, ATTR_VISIBLE, 0);
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_8, ATTR_VISIBLE, 0);

   	DeleteGraphPlot (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_0, -1, VAL_IMMEDIATE_DRAW);
   	DeleteGraphPlot (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_1, -1, VAL_IMMEDIATE_DRAW);
   	DeleteGraphPlot (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_2, -1, VAL_IMMEDIATE_DRAW);
   	DeleteGraphPlot (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_3, -1, VAL_IMMEDIATE_DRAW);
   	DeleteGraphPlot (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_4, -1, VAL_IMMEDIATE_DRAW);
   	DeleteGraphPlot (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_5, -1, VAL_IMMEDIATE_DRAW);
   	DeleteGraphPlot (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_6, -1, VAL_IMMEDIATE_DRAW);
   	DeleteGraphPlot (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_7, -1, VAL_IMMEDIATE_DRAW);
   	DeleteGraphPlot (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_8, -1, VAL_IMMEDIATE_DRAW);


	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_0, ATTR_XAXIS_GAIN, 1.0/ENERGY_SPECTRUM_DISPLAY_FLOAT_FACTOR);
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_1, ATTR_XAXIS_GAIN, 1.0/ENERGY_SPECTRUM_DISPLAY_FLOAT_FACTOR);
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_2, ATTR_XAXIS_GAIN, 1.0/ENERGY_SPECTRUM_DISPLAY_FLOAT_FACTOR);
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_3, ATTR_XAXIS_GAIN, 1.0/ENERGY_SPECTRUM_DISPLAY_FLOAT_FACTOR);
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_4, ATTR_XAXIS_GAIN, 1.0/ENERGY_SPECTRUM_DISPLAY_FLOAT_FACTOR);
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_5, ATTR_XAXIS_GAIN, 1.0/ENERGY_SPECTRUM_DISPLAY_FLOAT_FACTOR);
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_6, ATTR_XAXIS_GAIN, 1.0/ENERGY_SPECTRUM_DISPLAY_FLOAT_FACTOR);
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_7, ATTR_XAXIS_GAIN, 1.0/ENERGY_SPECTRUM_DISPLAY_FLOAT_FACTOR);
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_8, ATTR_XAXIS_GAIN, 1.0/ENERGY_SPECTRUM_DISPLAY_FLOAT_FACTOR);
	
	
	
	return 0;
}

//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int openPanelDisplayEnergySpectrum(void) 
{												
	gl_plot_energy_spec_plot_color = VAL_RED ;
	gl_plot_energy_spec_plot_style = VAL_THIN_LINE ;
	gl_plot_energy_spec_line_style = VAL_SOLID ;
	gl_plot_energy_spec_background_color = VAL_WHITE ;
	gl_plot_energy_spec_grid_color = VAL_BLACK ;
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_0, ATTR_PLOT_BGCOLOR, gl_plot_energy_spec_background_color); // 
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_1, ATTR_PLOT_BGCOLOR, gl_plot_energy_spec_background_color); // 
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_2, ATTR_PLOT_BGCOLOR, gl_plot_energy_spec_background_color); // 
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_3, ATTR_PLOT_BGCOLOR, gl_plot_energy_spec_background_color); // 
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_4, ATTR_PLOT_BGCOLOR, gl_plot_energy_spec_background_color); // 
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_5, ATTR_PLOT_BGCOLOR, gl_plot_energy_spec_background_color); // 
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_6, ATTR_PLOT_BGCOLOR, gl_plot_energy_spec_background_color); // 
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_7, ATTR_PLOT_BGCOLOR, gl_plot_energy_spec_background_color); // 
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_8, ATTR_PLOT_BGCOLOR, gl_plot_energy_spec_background_color); // 

	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_0, ATTR_GRID_COLOR, gl_plot_energy_spec_grid_color); // only indicator 
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_1, ATTR_GRID_COLOR, gl_plot_energy_spec_grid_color); // only indicator 
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_2, ATTR_GRID_COLOR, gl_plot_energy_spec_grid_color); // only indicator 
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_3, ATTR_GRID_COLOR, gl_plot_energy_spec_grid_color); // only indicator 
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_4, ATTR_GRID_COLOR, gl_plot_energy_spec_grid_color); // only indicator 
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_5, ATTR_GRID_COLOR, gl_plot_energy_spec_grid_color); // only indicator 
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_6, ATTR_GRID_COLOR, gl_plot_energy_spec_grid_color); // only indicator 
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_7, ATTR_GRID_COLOR, gl_plot_energy_spec_grid_color); // only indicator 
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_8, ATTR_GRID_COLOR, gl_plot_energy_spec_grid_color); // only indicator 


	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_0, ATTR_YMAP_MODE, 0); // non log
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_1, ATTR_YMAP_MODE, 0); // non log
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_2, ATTR_YMAP_MODE, 0); // non log
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_3, ATTR_YMAP_MODE, 0); // non log
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_4, ATTR_YMAP_MODE, 0); // non log
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_5, ATTR_YMAP_MODE, 0); // non log
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_6, ATTR_YMAP_MODE, 0); // non log
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_7, ATTR_YMAP_MODE, 0); // non log
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_8, ATTR_YMAP_MODE, 0); // non log


	SetCtrlVal (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_CHECKBOX_LOG,0);                            // 
    SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_0, ATTR_CTRL_MODE, VAL_INDICATOR); // only indicator 
    SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_0, ATTR_ENABLE_ZOOM_AND_PAN, 0);   // disable  
	SetCtrlVal (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_CHECKBOX_ZOOM,0);                            // disable CVI flag
	DisableZoomCursorsDisplayEnergySpectrum() ;
	SetPanelPos(Panels[PANEL_DISPLAY_ENERGY_SPEC],DEFINE_PANEL_DISPLAY_ENERGY_SPEC_POS_Y,DEFINE_PANEL_DISPLAY_ENERGY_SPEC_POS_X)  ;   // y, x
	DisplayPanel (Panels[PANEL_DISPLAY_ENERGY_SPEC]);
	return 0;
}
		  

//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int openPanelDisplayGaussValues(void) 
{												

	SetPanelPos(Panels[PANEL_DISPLAY_GAUSS_VALUE],DEFINE_PANEL_DISPLAY_ENERGY_GAUSS_POS_Y,DEFINE_PANEL_DISPLAY_ENERGY_GAUSS_POS_X)  ;   // y, x
	DisplayPanel (Panels[PANEL_DISPLAY_GAUSS_VALUE]);
	return 0;
}






//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int closePanelDisplayEnergySpectrum(void) 
{												
	 	SetMenuBarAttribute  (MenuBars[RUNCTRL_MENU_BAR], MENUCTRLRU_WINDOW_RUN_SPEC_ACTIV, ATTR_DIMMED, ON);
		gl_uint_RunCheckDisplayEnergySpectrumFlag = 0 ;
		SetCtrlVal (Panels[RUN_CTRL_MENUE], RUN_CTRL_CHECKBOX_DISPL_ENSPEC, 0);  
        HidePanel(Panels[PANEL_DISPLAY_ENERGY_SPEC]); //Clear Panel 
        HidePanel(Panels[PANEL_DISPLAY_GAUSS_VALUE]); //Clear Panel 
	return 0;
}

		  
		  
		  
//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
void CVICALLBACK CB_MenuGraphEnergySpec (int menuBar, int menuItem, void *callbackData,
        int panel)
{
    switch (menuItem) {
        case MENUGR_SPE_PANEL_CLOSE : {
			closePanelDisplayEnergySpectrum() ;
           }  
           break;


        case MENUGR_SPE_PLOT_STYLE_THIN_LINE : {
			gl_plot_energy_spec_plot_style = VAL_THIN_LINE ;
           }  
           break;
        case MENUGR_SPE_PLOT_STYLE_FAT_LINE : {
			gl_plot_energy_spec_plot_style = VAL_FAT_LINE ;
           }  
           break;
        case MENUGR_SPE_PLOT_STYLE_THIN_STEP : {
			gl_plot_energy_spec_plot_style = VAL_THIN_STEP ;
           }  
           break;
        case MENUGR_SPE_PLOT_STYLE_FAT_STEP : {
			gl_plot_energy_spec_plot_style = VAL_FAT_STEP ;
           }  
           break;
        case MENUGR_SPE_PLOT_STYLE_CON_POINTS : {
			gl_plot_energy_spec_plot_style = VAL_CONNECTED_POINTS ;
           }  
           break;
        case MENUGR_SPE_PLOT_STYLE_VERTIC_BAR : {
			gl_plot_energy_spec_plot_style = VAL_VERTICAL_BAR ;
           }  
           break;
        case MENUGR_SPE_PLOT_STYLE_BVERTI_BAR : {
			gl_plot_energy_spec_plot_style = VAL_BASE_ZERO_VERTICAL_BAR ;
           }  
           break;
//         
        case MENUGR_SPE_LINE_STYLE_SOLID : {
			gl_plot_energy_spec_line_style = VAL_SOLID ;
           }  
           break;
        case MENUGR_SPE_LINE_STYLE_DASH : {
			gl_plot_energy_spec_line_style = VAL_DASH ;
           }  
           break;
        case MENUGR_SPE_LINE_STYLE_DOT : {
			gl_plot_energy_spec_line_style = VAL_DOT ;
           }  
           break;
        case MENUGR_SPE_LINE_STYLE_DASH_DOT : {
			gl_plot_energy_spec_line_style = VAL_DASH_DOT ;
           }  
           break;
        case MENUGR_SPE_LINE_STYLE_DASH_2XDOT : {
			gl_plot_energy_spec_line_style = VAL_DASH_DOT_DOT ;
           }  
           break;


// background color
        case MENUGR_SPE_BACKGR_COLOR_WHITE : {
			gl_plot_energy_spec_background_color = VAL_WHITE ;
           }  
           break;

        case MENUGR_SPE_BACKGR_COLOR_OFFWHITE : {
			gl_plot_energy_spec_background_color = VAL_OFFWHITE ;
           }  
           break;
        case MENUGR_SPE_BACKGR_COLOR_LT_GRAY : {
			gl_plot_energy_spec_background_color = VAL_LT_GRAY ;
           }  
           break;
        case MENUGR_SPE_BACKGR_COLOR_GRAY : {
			gl_plot_energy_spec_background_color = VAL_GRAY ;
           }  
           break;
        case MENUGR_SPE_BACKGR_COLOR_DK_GRAY : {
			gl_plot_energy_spec_background_color = VAL_DK_GRAY ;
           }  
           break;

        case MENUGR_SPE_BACKGR_COLOR_TRANSP : {
			gl_plot_energy_spec_background_color = VAL_TRANSPARENT ;
           }  
           break;

        case MENUGR_SPE_BACKGR_COLOR_BLACK : {
			gl_plot_energy_spec_background_color = VAL_BLACK ;
           }  
           break;

// grid color
        case MENUGR_SPE_GRID_COLOR_WHITE : {
			gl_plot_energy_spec_grid_color = VAL_WHITE ;
           }  
           break;

        case MENUGR_SPE_GRID_COLOR_OFFWHITE : {
			gl_plot_energy_spec_grid_color = VAL_OFFWHITE ;
           }  
           break;
        case MENUGR_SPE_GRID_COLOR_LT_GRAY : {
			gl_plot_energy_spec_grid_color = VAL_LT_GRAY ;
           }  
           break;
        case MENUGR_SPE_GRID_COLOR_GRAY : {
			gl_plot_energy_spec_grid_color = VAL_GRAY ;
           }  
           break;
        case MENUGR_SPE_GRID_COLOR_DK_GRAY : {
			gl_plot_energy_spec_grid_color = VAL_DK_GRAY ;
           }  
           break;

        case MENUGR_SPE_GRID_COLOR_TRANSP : {
			gl_plot_energy_spec_grid_color = VAL_TRANSPARENT ;
           }  
           break;

        case MENUGR_SPE_GRID_COLOR_BLACK : {
			gl_plot_energy_spec_grid_color = VAL_BLACK ;
           }  
           break;

 // plot color
        case MENUGR_SPE_PLOT_COLOR_RED : {
			gl_plot_energy_spec_plot_color = VAL_RED ;
           }  
           break;
        case MENUGR_SPE_PLOT_COLOR_DK_RED : {
			gl_plot_energy_spec_plot_color = VAL_DK_RED ;
           }  
           break;

        case MENUGR_SPE_PLOT_COLOR_GREEN : {
			gl_plot_energy_spec_plot_color = VAL_GREEN ;
           }  
           break;


        case MENUGR_SPE_PLOT_COLOR_YELLOW : {
			gl_plot_energy_spec_plot_color = VAL_YELLOW ;
           }  
           break;
        case MENUGR_SPE_PLOT_COLOR_BLACK : {
			gl_plot_energy_spec_plot_color = VAL_BLACK ;
           }  
           break;
        case MENUGR_SPE_PLOT_COLOR_WHITE : {
			gl_plot_energy_spec_plot_color = VAL_WHITE ;
           }  
           break;

     
     }  // switch

	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_0, ATTR_PLOT_BGCOLOR, gl_plot_energy_spec_background_color); // 
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_1, ATTR_PLOT_BGCOLOR, gl_plot_energy_spec_background_color); // 
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_2, ATTR_PLOT_BGCOLOR, gl_plot_energy_spec_background_color); // 
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_3, ATTR_PLOT_BGCOLOR, gl_plot_energy_spec_background_color); // 
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_4, ATTR_PLOT_BGCOLOR, gl_plot_energy_spec_background_color); // 
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_5, ATTR_PLOT_BGCOLOR, gl_plot_energy_spec_background_color); // 
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_6, ATTR_PLOT_BGCOLOR, gl_plot_energy_spec_background_color); // 
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_7, ATTR_PLOT_BGCOLOR, gl_plot_energy_spec_background_color); // 
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_8, ATTR_PLOT_BGCOLOR, gl_plot_energy_spec_background_color); // 

	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_0, ATTR_GRID_COLOR, gl_plot_energy_spec_grid_color); // only indicator 
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_1, ATTR_GRID_COLOR, gl_plot_energy_spec_grid_color); // only indicator 
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_2, ATTR_GRID_COLOR, gl_plot_energy_spec_grid_color); // only indicator 
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_3, ATTR_GRID_COLOR, gl_plot_energy_spec_grid_color); // only indicator 
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_4, ATTR_GRID_COLOR, gl_plot_energy_spec_grid_color); // only indicator 
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_5, ATTR_GRID_COLOR, gl_plot_energy_spec_grid_color); // only indicator 
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_6, ATTR_GRID_COLOR, gl_plot_energy_spec_grid_color); // only indicator 
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_7, ATTR_GRID_COLOR, gl_plot_energy_spec_grid_color); // only indicator 
	SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_8, ATTR_GRID_COLOR, gl_plot_energy_spec_grid_color); // only indicator 

	DisplayEnergySpectrum() ;


return;
}
	 

		  

//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int CVICALLBACK CB_ClosePanelDisplayEnergySpectrum (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{												
 	SetMenuBarAttribute  (MenuBars[RUNCTRL_MENU_BAR], MENUCTRLRU_WINDOW_RUN_DIAG_ACTIV, ATTR_DIMMED, ON);
	closePanelDisplayEnergySpectrum() ;
	return 0;
}
		  


//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int CVICALLBACK CB_DisplayEnergySpectrumChooseAdcShow (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
 		  GetCtrlVal (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_RING_ADC_CHOOSE,&gl_uint_DisplayEnergySpectrumAdcShowChoose);
		  if(gl_uint_DisplayEnergySpectrumAdcShowChoose == 0) {
			SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_0, ATTR_VISIBLE, 0);
			SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_1, ATTR_VISIBLE, 1);
			SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_2, ATTR_VISIBLE, 1);
			SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_3, ATTR_VISIBLE, 1);
			SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_4, ATTR_VISIBLE, 1);
			SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_5, ATTR_VISIBLE, 1);
			SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_6, ATTR_VISIBLE, 1);
			SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_7, ATTR_VISIBLE, 1);
			SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_8, ATTR_VISIBLE, 1);


			//SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_1, ATTR_LABEL_TEXT, "hallo");

		  }
		  else {
			SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_0, ATTR_VISIBLE, 1);
			SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_1, ATTR_VISIBLE, 0);
			SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_2, ATTR_VISIBLE, 0);
			SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_3, ATTR_VISIBLE, 0);
			SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_4, ATTR_VISIBLE, 0);
			SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_5, ATTR_VISIBLE, 0);
			SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_6, ATTR_VISIBLE, 0);
			SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_7, ATTR_VISIBLE, 0);
			SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_8, ATTR_VISIBLE, 0);
	        HidePanel(Panels[PANEL_DISPLAY_GAUSS_VALUE]); //Clear Panel 
		  }
		  
		  DisplayEnergySpectrum() ;

		  break;
	}
	return 0;
} // end function CB_ChooseAdcShow ()



 

//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int CVICALLBACK CB_DisplayEnergySpectrumModuleNumber (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int CviErr,i;
	switch (event)
	{
		case EVENT_COMMIT:
 			GetCtrlVal (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_MODULE_NUMBER,&gl_unit_DisplayEnergySpectrumModuleNumber);
			DisplayEnergySpectrum() ;
		  break;
	}
	return 0;
} // end function 


 

//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int CVICALLBACK CB_CheckDisplayEnergySpectrum (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int test ;
	int check_on ;
	switch (event)
		{
		case EVENT_COMMIT:
  			switch (control)
			{
			  case PANEL_ESPE_CHECKBOX_LOG:
				GetCtrlVal (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_CHECKBOX_LOG,&check_on);  // 
				if (check_on == 0) { //off
					SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_0, ATTR_YMAP_MODE, 0); // non log
					SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_1, ATTR_YMAP_MODE, 0); // non log
					SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_2, ATTR_YMAP_MODE, 0); // non log
					SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_3, ATTR_YMAP_MODE, 0); // non log
					SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_4, ATTR_YMAP_MODE, 0); // non log
					SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_5, ATTR_YMAP_MODE, 0); // non log
					SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_6, ATTR_YMAP_MODE, 0); // non log
					SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_7, ATTR_YMAP_MODE, 0); // non log
					SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_8, ATTR_YMAP_MODE, 0); // non log
					SetCtrlVal (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_CHECKBOX_LOG,0);                            // 
				  }
				  else { // on
					SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_0, ATTR_YMAP_MODE, 1); //  log
					SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_1, ATTR_YMAP_MODE, 1); //  log
					SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_2, ATTR_YMAP_MODE, 1); //  log
					SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_3, ATTR_YMAP_MODE, 1); //  log
					SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_4, ATTR_YMAP_MODE, 1); //  log
					SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_5, ATTR_YMAP_MODE, 1); //  log
					SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_6, ATTR_YMAP_MODE, 1); //  log
					SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_7, ATTR_YMAP_MODE, 1); //  log
					SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_8, ATTR_YMAP_MODE, 1); //  log
					SetCtrlVal (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_CHECKBOX_LOG,1);                            // 
				  }
				break ;			


			  case PANEL_ESPE_CHECKBOX_ZOOM:
				GetCtrlVal (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_CHECKBOX_ZOOM,&check_on);  //Show in panel Configuration
				if (check_on == 0) { //off
				    SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_0, ATTR_CTRL_MODE, VAL_INDICATOR); // only indicator 
				    SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_0, ATTR_ENABLE_ZOOM_AND_PAN, 0);   // disable  
					DisableZoomCursorsDisplayEnergySpectrum() ;
				  }
				  else { // on
				    SetCtrlAttribute (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_0, ATTR_CTRL_MODE, VAL_HOT);     // and hot 
					EnableZoomCursorsDisplayEnergySpectrum() ;
				  }
				break ;			
			} // end switch (control)

			break;
		}
	  DisplayEnergySpectrum() ;

	return 0;
}




//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int CVICALLBACK CB_MoveCursor_DisplayEnergySpectrum (int panel, int control, int event,
                              void *callbackData, int eventData1,  int eventData2)
{
    double x;
    double x1, x2;
    double y;
    double xmin;
    double xmax;
    double ymin;
    double ymax;

    switch (event) {
        case EVENT_COMMIT:
        	GetGraphCursor (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_0, 3, &x, &y);
			x = (x / ENERGY_SPECTRUM_DISPLAY_FLOAT_FACTOR) ;
        	
        	SetCtrlVal (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_X_POSITION, x);
        	SetCtrlVal (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_Y_POSITION, y);

        	GetGraphCursor (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_0, 1, &x1, &y);
        	GetGraphCursor (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_0, 2, &x2, &y);

            break;

        case EVENT_RIGHT_CLICK:
			xmin =  (double) gl_unit_GraphEnergySpectrumXmin ;
			xmax =  (double) gl_unit_GraphEnergySpectrumXmax ;
 			ymin =  (double) gl_unit_GraphEnergySpectrumYmin ;
 			ymax =  (double) gl_unit_GraphEnergySpectrumYmax ;
			SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_0, VAL_XAXIS, VAL_MANUAL, xmin, xmax)  ;
 			SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_0, VAL_LEFT_YAXIS, VAL_AUTOSCALE, ymin, ymax)  ;

			SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_1, VAL_XAXIS, VAL_MANUAL, xmin, xmax)  ;
 			SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_1, VAL_LEFT_YAXIS, VAL_AUTOSCALE, ymin, ymax)  ;
			SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_2, VAL_XAXIS, VAL_MANUAL, xmin, xmax)  ;
 			SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_2, VAL_LEFT_YAXIS, VAL_AUTOSCALE, ymin, ymax)  ;
			SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_3, VAL_XAXIS, VAL_MANUAL, xmin, xmax)  ;
 			SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_3, VAL_LEFT_YAXIS, VAL_AUTOSCALE, ymin, ymax)  ;
			SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_4, VAL_XAXIS, VAL_MANUAL, xmin, xmax)  ;
 			SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_4, VAL_LEFT_YAXIS, VAL_AUTOSCALE, ymin, ymax)  ;
			SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_5, VAL_XAXIS, VAL_MANUAL, xmin, xmax)  ;
 			SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_5, VAL_LEFT_YAXIS, VAL_AUTOSCALE, ymin, ymax)  ;
			SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_6, VAL_XAXIS, VAL_MANUAL, xmin, xmax)  ;
 			SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_6, VAL_LEFT_YAXIS, VAL_AUTOSCALE, ymin, ymax)  ;
			SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_7, VAL_XAXIS, VAL_MANUAL, xmin, xmax)  ;
 			SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_7, VAL_LEFT_YAXIS, VAL_AUTOSCALE, ymin, ymax)  ;
			SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_8, VAL_XAXIS, VAL_MANUAL, xmin, xmax)  ;
 			SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_8, VAL_LEFT_YAXIS, VAL_AUTOSCALE, ymin, ymax)  ;


			SetCtrlVal (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_ENERGY_XMIN_SCALE, (unsigned int)(xmin/ENERGY_SPECTRUM_DISPLAY_FLOAT_FACTOR) );
			SetCtrlVal (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_ENERGY_XMAX_SCALE, (unsigned int)(xmax/ENERGY_SPECTRUM_DISPLAY_FLOAT_FACTOR) );

		  DisplayEnergySpectrum() ;
            
            break;
        }
    return 0;
}

 
//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int CVICALLBACK CB_DisplayEnergySpectrumZoomIn (int panel, int control, int event, void *callbackData,
                        int eventData1, int eventData2)
{
    double x1;
    double x2;
    double y1;
    double y2;
    double temp;
	int i ;
    
    if (event == EVENT_COMMIT) {
        
        /* Get the current position of both cursors.  Notive that the        */
        /* position is relative to the Graph's coordinate system (your plots)*/
        GetGraphCursor (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_0, 1, &x1, &y1);
        GetGraphCursor (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_0, 2, &x2, &y2);
        
        /* Get positive range values, and rescale the Graph */
        if (x1 > x2)
            {
            temp = x1;
            x1 = x2;
            x2 = temp;
            }
        if (y1 > y2)
            {
            temp = y1;
            y1 = y2;
            y2 = temp;
            }

		
		switch (control)
		{
		  case PANEL_ESPE_XY_ZOOM_IN:
			SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_0, VAL_XAXIS, VAL_MANUAL, x1, x2)  ;
			SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_0, VAL_LEFT_YAXIS, VAL_MANUAL, y1, y2)  ;

			SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_1, VAL_XAXIS, VAL_MANUAL, x1, x2)  ;
			SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_1, VAL_LEFT_YAXIS, VAL_MANUAL, y1, y2)  ;
			SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_2, VAL_XAXIS, VAL_MANUAL, x1, x2)  ;
			SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_2, VAL_LEFT_YAXIS, VAL_MANUAL, y1, y2)  ;
			SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_3, VAL_XAXIS, VAL_MANUAL, x1, x2)  ;
			SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_3, VAL_LEFT_YAXIS, VAL_MANUAL, y1, y2)  ;
			SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_4, VAL_XAXIS, VAL_MANUAL, x1, x2)  ;
			SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_4, VAL_LEFT_YAXIS, VAL_MANUAL, y1, y2)  ;
			SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_5, VAL_XAXIS, VAL_MANUAL, x1, x2)  ;
			SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_5, VAL_LEFT_YAXIS, VAL_MANUAL, y1, y2)  ;
			SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_6, VAL_XAXIS, VAL_MANUAL, x1, x2)  ;
			SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_6, VAL_LEFT_YAXIS, VAL_MANUAL, y1, y2)  ;
			SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_7, VAL_XAXIS, VAL_MANUAL, x1, x2)  ;
			SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_7, VAL_LEFT_YAXIS, VAL_MANUAL, y1, y2)  ;
			SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_8, VAL_XAXIS, VAL_MANUAL, x1, x2)  ;
			SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_8, VAL_LEFT_YAXIS, VAL_MANUAL, y1, y2)  ;

			SetCtrlVal (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_ENERGY_XMIN_SCALE, (unsigned int)(x1 / ENERGY_SPECTRUM_DISPLAY_FLOAT_FACTOR));
			SetCtrlVal (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_ENERGY_XMAX_SCALE, (unsigned int)(x2 / ENERGY_SPECTRUM_DISPLAY_FLOAT_FACTOR));
			break;																						  
		  case PANEL_ESPE_X_ZOOM_IN:
			SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_0, VAL_XAXIS, VAL_MANUAL, x1, x2)  ;
			SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_1, VAL_XAXIS, VAL_MANUAL, x1, x2)  ;
			SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_2, VAL_XAXIS, VAL_MANUAL, x1, x2)  ;
			SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_3, VAL_XAXIS, VAL_MANUAL, x1, x2)  ;
			SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_4, VAL_XAXIS, VAL_MANUAL, x1, x2)  ;
			SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_5, VAL_XAXIS, VAL_MANUAL, x1, x2)  ;
			SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_6, VAL_XAXIS, VAL_MANUAL, x1, x2)  ;
			SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_7, VAL_XAXIS, VAL_MANUAL, x1, x2)  ;
			SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_8, VAL_XAXIS, VAL_MANUAL, x1, x2)  ;
			SetCtrlVal (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_ENERGY_XMIN_SCALE, (unsigned int)(x1 / ENERGY_SPECTRUM_DISPLAY_FLOAT_FACTOR));
			SetCtrlVal (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_ENERGY_XMAX_SCALE, (unsigned int)(x2 / ENERGY_SPECTRUM_DISPLAY_FLOAT_FACTOR));
			break;
		  case PANEL_ESPE_Y_ZOOM_IN:
			SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_0, VAL_LEFT_YAXIS, VAL_MANUAL, y1, y2)  ;
			SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_1, VAL_LEFT_YAXIS, VAL_MANUAL, y1, y2)  ;
			SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_2, VAL_LEFT_YAXIS, VAL_MANUAL, y1, y2)  ;
			SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_3, VAL_LEFT_YAXIS, VAL_MANUAL, y1, y2)  ;
			SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_4, VAL_LEFT_YAXIS, VAL_MANUAL, y1, y2)  ;
			SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_5, VAL_LEFT_YAXIS, VAL_MANUAL, y1, y2)  ;
			SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_6, VAL_LEFT_YAXIS, VAL_MANUAL, y1, y2)  ;
			SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_7, VAL_LEFT_YAXIS, VAL_MANUAL, y1, y2)  ;
			SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_8, VAL_LEFT_YAXIS, VAL_MANUAL, y1, y2)  ;
			break;
		} // end switch (control)

 		  DisplayEnergySpectrum() ;

				
        }
    return 0;
}
	  
	  
	

//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int CVICALLBACK CB_Expand_DisplayEnergySpectrum (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
    double xmin;
    double xmax;
    double ymin;
    double ymax;


	switch (event)
		{
		case EVENT_COMMIT:
			xmin =  (double) gl_unit_GraphEnergySpectrumXmin ;
			xmax =  (double) gl_unit_GraphEnergySpectrumXmax ;
 			ymin =  (double) gl_unit_GraphEnergySpectrumYmin ;
 			ymax =  (double) gl_unit_GraphEnergySpectrumYmax ;
  			switch (control)
			{
			  case PANEL_ESPE_XY_EXPAND:
				SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_0, VAL_XAXIS, VAL_MANUAL, xmin, xmax)  ;
				SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_0, VAL_LEFT_YAXIS, VAL_AUTOSCALE, ymin, ymax)  ;

				SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_1, VAL_XAXIS, VAL_MANUAL, xmin, xmax)  ;
				SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_1, VAL_LEFT_YAXIS, VAL_AUTOSCALE, ymin, ymax)  ;
				SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_2, VAL_XAXIS, VAL_MANUAL, xmin, xmax)  ;
				SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_2, VAL_LEFT_YAXIS, VAL_AUTOSCALE, ymin, ymax)  ;
				SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_3, VAL_XAXIS, VAL_MANUAL, xmin, xmax)  ;
				SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_3, VAL_LEFT_YAXIS, VAL_AUTOSCALE, ymin, ymax)  ;
				SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_4, VAL_XAXIS, VAL_MANUAL, xmin, xmax)  ;
				SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_4, VAL_LEFT_YAXIS, VAL_AUTOSCALE, ymin, ymax)  ;
				SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_5, VAL_XAXIS, VAL_MANUAL, xmin, xmax)  ;
				SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_5, VAL_LEFT_YAXIS, VAL_AUTOSCALE, ymin, ymax)  ;
				SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_6, VAL_XAXIS, VAL_MANUAL, xmin, xmax)  ;
				SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_6, VAL_LEFT_YAXIS, VAL_AUTOSCALE, ymin, ymax)  ;
				SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_7, VAL_XAXIS, VAL_MANUAL, xmin, xmax)  ;
				SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_7, VAL_LEFT_YAXIS, VAL_AUTOSCALE, ymin, ymax)  ;
				SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_8, VAL_XAXIS, VAL_MANUAL, xmin, xmax)  ;
				SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_8, VAL_LEFT_YAXIS, VAL_AUTOSCALE, ymin, ymax)  ;

				SetCtrlVal (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_ENERGY_XMIN_SCALE, (unsigned int)(xmin / ENERGY_SPECTRUM_DISPLAY_FLOAT_FACTOR));
				SetCtrlVal (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_ENERGY_XMAX_SCALE, (unsigned int)(xmax / ENERGY_SPECTRUM_DISPLAY_FLOAT_FACTOR));
				break;																						  
			  case PANEL_ESPE_X_EXPAND:
				SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_0, VAL_XAXIS, VAL_MANUAL, xmin, xmax)  ;
				SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_1, VAL_XAXIS, VAL_MANUAL, xmin, xmax)  ;
				SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_2, VAL_XAXIS, VAL_MANUAL, xmin, xmax)  ;
				SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_3, VAL_XAXIS, VAL_MANUAL, xmin, xmax)  ;
				SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_4, VAL_XAXIS, VAL_MANUAL, xmin, xmax)  ;
				SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_5, VAL_XAXIS, VAL_MANUAL, xmin, xmax)  ;
				SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_6, VAL_XAXIS, VAL_MANUAL, xmin, xmax)  ;
				SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_7, VAL_XAXIS, VAL_MANUAL, xmin, xmax)  ;
				SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_8, VAL_XAXIS, VAL_MANUAL, xmin, xmax)  ;
				SetCtrlVal (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_ENERGY_XMIN_SCALE, (unsigned int)(xmin / ENERGY_SPECTRUM_DISPLAY_FLOAT_FACTOR));
				SetCtrlVal (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_ENERGY_XMAX_SCALE, (unsigned int)(xmax / ENERGY_SPECTRUM_DISPLAY_FLOAT_FACTOR));
				break;
			  case PANEL_ESPE_Y_EXPAND:
				SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_0, VAL_LEFT_YAXIS, VAL_AUTOSCALE, ymin, ymax)  ;
				SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_1, VAL_LEFT_YAXIS, VAL_AUTOSCALE, ymin, ymax)  ;
				SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_2, VAL_LEFT_YAXIS, VAL_AUTOSCALE, ymin, ymax)  ;
				SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_3, VAL_LEFT_YAXIS, VAL_AUTOSCALE, ymin, ymax)  ;
				SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_4, VAL_LEFT_YAXIS, VAL_AUTOSCALE, ymin, ymax)  ;
				SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_5, VAL_LEFT_YAXIS, VAL_AUTOSCALE, ymin, ymax)  ;
				SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_6, VAL_LEFT_YAXIS, VAL_AUTOSCALE, ymin, ymax)  ;
				SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_7, VAL_LEFT_YAXIS, VAL_AUTOSCALE, ymin, ymax)  ;
				SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_8, VAL_LEFT_YAXIS, VAL_AUTOSCALE, ymin, ymax)  ;
				break;
			} // end switch (control)


			
			//break;
		  DisplayEnergySpectrum() ;
		}
	return 0;
}


//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int CVICALLBACK CB_DisplayEnergySpectrumZoomPeak (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
    double xmin;
    double xmax;
    double temp;
	unsigned int max_value_index ;
	unsigned int max_value_index_min ;
	unsigned int max_value_index_max ;
	unsigned int i ;
	switch (event)
		{
		case EVENT_COMMIT:
			switch (control)
			{
		 	 case PANEL_ESPE_MAX_PEAK_ZOOM_IN:

				
				if (gl_uint_DisplayEnergySpectrumAdcShowChoose == 0) {
					find_energy_max_value_index (gl_unit_DisplayEnergySpectrumModuleNumber-1 , 0 /*channel_index */ , &max_value_index)  ;
					max_value_index_max = max_value_index ;
					max_value_index_min = max_value_index ;
					for (i=1;i<8;i++) { 
						find_energy_max_value_index (gl_unit_DisplayEnergySpectrumModuleNumber-1 , i /*channel_index */ , &max_value_index)  ;
						if (max_value_index != 0) {
							if (max_value_index > max_value_index_max) {max_value_index_max = max_value_index ; }
							if (max_value_index < max_value_index_min) {max_value_index_min = max_value_index ; }
						}
					}

					
					setdisplayEnergySpectrumZoomPeak (max_value_index_max, max_value_index_min) ;
				}
				else {
					find_energy_max_value_index (gl_unit_DisplayEnergySpectrumModuleNumber-1 , gl_uint_DisplayEnergySpectrumAdcShowChoose-1 /*channel_index */ , &max_value_index)  ;
					setdisplayEnergySpectrumZoomPeak (max_value_index, max_value_index)	   ;

	 			}
				break;
			} // end switch (control)
			break;
		}
	return 0;
}



//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
void setdisplayEnergySpectrumZoomPeak (unsigned int peak_value_index_max, unsigned int peak_value_index_min)
{
    double xmin;
    double xmax;
    double temp;
	unsigned int max_value_index ;
	unsigned int max_value_index_min ;
	unsigned int max_value_index_max ;
	unsigned int i ;


	max_value_index_max = peak_value_index_max ;
	max_value_index_min = peak_value_index_min ;
		
	if (max_value_index_min > ENERGY_PEAK_ZOOM_VALUE) { 
		xmin = max_value_index_min - ENERGY_PEAK_ZOOM_VALUE ;
	} 
	else {
		xmin = 0 ;
	} 
	if (max_value_index_max < (MAX_NOF_ENERGY_SPECTRUM - ENERGY_PEAK_ZOOM_VALUE) ) { 
		xmax = max_value_index_max + ENERGY_PEAK_ZOOM_VALUE ;
	} 
	else {
		xmax = MAX_NOF_ENERGY_SPECTRUM ;
	} 

	/* Get positive range values, and rescale the Graph */
	if (xmin > xmax) {
   		temp = xmin;
   		xmin = xmax;
   		xmax = temp;
   	}
	if (xmin > xmax) {
   		temp = xmin;
  		xmin = xmax;
		xmax = temp;
	}

				
	SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_0, VAL_XAXIS, VAL_MANUAL, xmin, xmax)  ;
	SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_1, VAL_XAXIS, VAL_MANUAL, xmin, xmax)  ;
	SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_2, VAL_XAXIS, VAL_MANUAL, xmin, xmax)  ;
	SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_3, VAL_XAXIS, VAL_MANUAL, xmin, xmax)  ;
	SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_4, VAL_XAXIS, VAL_MANUAL, xmin, xmax)  ;
	SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_5, VAL_XAXIS, VAL_MANUAL, xmin, xmax)  ;
	SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_6, VAL_XAXIS, VAL_MANUAL, xmin, xmax)  ;
	SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_7, VAL_XAXIS, VAL_MANUAL, xmin, xmax)  ;
	SetAxisScalingMode  (Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_8, VAL_XAXIS, VAL_MANUAL, xmin, xmax)  ;
 	DisplayEnergySpectrum() ;

	SetCtrlVal (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_ENERGY_XMIN_SCALE, (unsigned int)(xmin/ENERGY_SPECTRUM_DISPLAY_FLOAT_FACTOR));
	SetCtrlVal (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_ENERGY_XMAX_SCALE, (unsigned int)(xmax/ENERGY_SPECTRUM_DISPLAY_FLOAT_FACTOR));
	return ;
}


//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int CVICALLBACK CB_SetEnergySpectrumXScale (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int CviErr;
	unsigned int xmin_value, xmax_value;	
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_ENERGY_XMIN_SCALE, &xmin_value);
			GetCtrlVal (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_ENERGY_XMAX_SCALE, &xmax_value);


			
			if (xmin_value >= xmax_value)  {
				xmax_value = xmin_value + 200 ;
				SetCtrlVal (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_ENERGY_XMIN_SCALE, xmin_value);
				SetCtrlVal (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_ENERGY_XMAX_SCALE, xmax_value);
			}

			xmin_value = xmin_value * ENERGY_SPECTRUM_DISPLAY_FLOAT_FACTOR ;
			xmax_value = xmax_value * ENERGY_SPECTRUM_DISPLAY_FLOAT_FACTOR ;
			
			
			SetAxisScalingMode(Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_0, VAL_XAXIS, VAL_MANUAL,xmin_value,xmax_value)  ;
			SetAxisScalingMode(Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_1, VAL_XAXIS, VAL_MANUAL,xmin_value,xmax_value)  ;
			SetAxisScalingMode(Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_2, VAL_XAXIS, VAL_MANUAL,xmin_value,xmax_value)  ;
			SetAxisScalingMode(Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_3, VAL_XAXIS, VAL_MANUAL,xmin_value,xmax_value)  ;
			SetAxisScalingMode(Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_4, VAL_XAXIS, VAL_MANUAL,xmin_value,xmax_value)  ;
			SetAxisScalingMode(Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_5, VAL_XAXIS, VAL_MANUAL,xmin_value,xmax_value)  ;
			SetAxisScalingMode(Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_6, VAL_XAXIS, VAL_MANUAL,xmin_value,xmax_value)  ;
			SetAxisScalingMode(Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_7, VAL_XAXIS, VAL_MANUAL,xmin_value,xmax_value)  ;
			SetAxisScalingMode(Panels[PANEL_DISPLAY_ENERGY_SPEC],PANEL_ESPE_GRAPH_ENERGY_SPEC_8, VAL_XAXIS, VAL_MANUAL,xmin_value,xmax_value)  ;

			break;
	}
		  DisplayEnergySpectrum() ;
	return 0;
} // end function  ()
			  
    	 
 
  


  
 	 
//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int DisplayEnergySpectrum(void)
{
	int  module_index, channel_index   ;
	unsigned int *uint_displayEnergySpectrum_ptr    ;
	unsigned int plot_size;
	unsigned int loc_uint_DisplayEnergySpectrumHistogramShowChoose;

	GetCtrlVal (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_RING_HISTO_CHOOSE,&loc_uint_DisplayEnergySpectrumHistogramShowChoose);

	plot_size =   gl_uint_displayEnergySpectrum_plot_size ;
    //DeleteGraphPlot (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_0, -1, VAL_IMMEDIATE_DRAW) ;
   	DeleteGraphPlot (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_0, -1, VAL_IMMEDIATE_DRAW);
   	DeleteGraphPlot (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_1, -1, VAL_IMMEDIATE_DRAW);
   	DeleteGraphPlot (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_2, -1, VAL_IMMEDIATE_DRAW);
   	DeleteGraphPlot (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_3, -1, VAL_IMMEDIATE_DRAW);
   	DeleteGraphPlot (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_4, -1, VAL_IMMEDIATE_DRAW);
   	DeleteGraphPlot (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_5, -1, VAL_IMMEDIATE_DRAW);
   	DeleteGraphPlot (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_6, -1, VAL_IMMEDIATE_DRAW);
   	DeleteGraphPlot (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_7, -1, VAL_IMMEDIATE_DRAW);
   	DeleteGraphPlot (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_8, -1, VAL_IMMEDIATE_DRAW);

	module_index  =   0  ;
	if (gl_unit_DisplayEnergySpectrumModuleNumber <= MAX_NO_OF_MODULES) { 
		module_index  =   gl_unit_DisplayEnergySpectrumModuleNumber - 1  ;
	}

        
   	if (gl_uint_DisplayEnergySpectrumAdcShowChoose == 0)  { // all channels	
		channel_index =   0 ; // ADC 1
		uint_displayEnergySpectrum_ptr = &gl_uint_EnergySpectrumArray[module_index][channel_index][0]  ; //default
   		switch (loc_uint_DisplayEnergySpectrumHistogramShowChoose) {
		  case 0:
			uint_displayEnergySpectrum_ptr = &gl_uint_EnergySpectrumArray[module_index][channel_index][0]  ;
			break;																						  
		  case 1:
			uint_displayEnergySpectrum_ptr = &gl_uint_EnergySpectrum2Array[module_index][channel_index][0]  ;
			break;
		  case 2:
			uint_displayEnergySpectrum_ptr = &gl_uint_EnergySpectrum3Array[module_index][channel_index][0]  ;
			break;
		} // end switch (loc_uint_DisplayEnergySpectrumHistogramShowChoose)
		
		PlotY (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_1, uint_displayEnergySpectrum_ptr, plot_size, 
				    	   VAL_UNSIGNED_INTEGER, gl_plot_energy_spec_plot_style, VAL_NO_POINT, gl_plot_energy_spec_line_style, 1, gl_plot_energy_spec_plot_color);

		channel_index =   1 ; // ADC 2 
		uint_displayEnergySpectrum_ptr = &gl_uint_EnergySpectrumArray[module_index][channel_index][0]  ;
  		switch (loc_uint_DisplayEnergySpectrumHistogramShowChoose) {
		  case 0:
			uint_displayEnergySpectrum_ptr = &gl_uint_EnergySpectrumArray[module_index][channel_index][0]  ;
			break;																						  
		  case 1:
			uint_displayEnergySpectrum_ptr = &gl_uint_EnergySpectrum2Array[module_index][channel_index][0]  ;
			break;
		  case 2:
			uint_displayEnergySpectrum_ptr = &gl_uint_EnergySpectrum3Array[module_index][channel_index][0]  ;
			break;
		} // end switch (loc_uint_DisplayEnergySpectrumHistogramShowChoose)
		PlotY (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_2, uint_displayEnergySpectrum_ptr, plot_size, 
				    	   VAL_UNSIGNED_INTEGER, gl_plot_energy_spec_plot_style, VAL_NO_POINT, gl_plot_energy_spec_line_style, 1, gl_plot_energy_spec_plot_color);

		channel_index =   2 ; // ADC 3 
		uint_displayEnergySpectrum_ptr = &gl_uint_EnergySpectrumArray[module_index][channel_index][0]  ;
  		switch (loc_uint_DisplayEnergySpectrumHistogramShowChoose) {
		  case 0:
			uint_displayEnergySpectrum_ptr = &gl_uint_EnergySpectrumArray[module_index][channel_index][0]  ;
			break;																						  
		  case 1:
			uint_displayEnergySpectrum_ptr = &gl_uint_EnergySpectrum2Array[module_index][channel_index][0]  ;
			break;
		  case 2:
			uint_displayEnergySpectrum_ptr = &gl_uint_EnergySpectrum3Array[module_index][channel_index][0]  ;
			break;
		} // end switch (loc_uint_DisplayEnergySpectrumHistogramShowChoose)
		PlotY (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_3, uint_displayEnergySpectrum_ptr, plot_size, 
				    	   VAL_UNSIGNED_INTEGER, gl_plot_energy_spec_plot_style, VAL_NO_POINT, gl_plot_energy_spec_line_style, 1, gl_plot_energy_spec_plot_color);

		channel_index =   3 ; // ADC 4 
		uint_displayEnergySpectrum_ptr = &gl_uint_EnergySpectrumArray[module_index][channel_index][0]  ;
  		switch (loc_uint_DisplayEnergySpectrumHistogramShowChoose) {
		  case 0:
			uint_displayEnergySpectrum_ptr = &gl_uint_EnergySpectrumArray[module_index][channel_index][0]  ;
			break;																						  
		  case 1:
			uint_displayEnergySpectrum_ptr = &gl_uint_EnergySpectrum2Array[module_index][channel_index][0]  ;
			break;
		  case 2:
			uint_displayEnergySpectrum_ptr = &gl_uint_EnergySpectrum3Array[module_index][channel_index][0]  ;
			break;
		} // end switch (loc_uint_DisplayEnergySpectrumHistogramShowChoose)
		PlotY (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_4, uint_displayEnergySpectrum_ptr, plot_size, 
				    	   VAL_UNSIGNED_INTEGER, gl_plot_energy_spec_plot_style, VAL_NO_POINT, gl_plot_energy_spec_line_style, 1, gl_plot_energy_spec_plot_color);


		channel_index =   4 ; // ADC 5
		uint_displayEnergySpectrum_ptr = &gl_uint_EnergySpectrumArray[module_index][channel_index][0]  ;
  		switch (loc_uint_DisplayEnergySpectrumHistogramShowChoose) {
		  case 0:
			uint_displayEnergySpectrum_ptr = &gl_uint_EnergySpectrumArray[module_index][channel_index][0]  ;
			break;																						  
		  case 1:
			uint_displayEnergySpectrum_ptr = &gl_uint_EnergySpectrum2Array[module_index][channel_index][0]  ;
			break;
		  case 2:
			uint_displayEnergySpectrum_ptr = &gl_uint_EnergySpectrum3Array[module_index][channel_index][0]  ;
			break;
		} // end switch (loc_uint_DisplayEnergySpectrumHistogramShowChoose)
		PlotY (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_5, uint_displayEnergySpectrum_ptr, plot_size, 
				    	   VAL_UNSIGNED_INTEGER, gl_plot_energy_spec_plot_style, VAL_NO_POINT, gl_plot_energy_spec_line_style, 1, gl_plot_energy_spec_plot_color);

		channel_index =   5 ; // ADC 6 
		uint_displayEnergySpectrum_ptr = &gl_uint_EnergySpectrumArray[module_index][channel_index][0]  ;
  		switch (loc_uint_DisplayEnergySpectrumHistogramShowChoose) {
		  case 0:
			uint_displayEnergySpectrum_ptr = &gl_uint_EnergySpectrumArray[module_index][channel_index][0]  ;
			break;																						  
		  case 1:
			uint_displayEnergySpectrum_ptr = &gl_uint_EnergySpectrum2Array[module_index][channel_index][0]  ;
			break;
		  case 2:
			uint_displayEnergySpectrum_ptr = &gl_uint_EnergySpectrum3Array[module_index][channel_index][0]  ;
			break;
		} // end switch (loc_uint_DisplayEnergySpectrumHistogramShowChoose)
		PlotY (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_6, uint_displayEnergySpectrum_ptr, plot_size, 
				    	   VAL_UNSIGNED_INTEGER, gl_plot_energy_spec_plot_style, VAL_NO_POINT, gl_plot_energy_spec_line_style, 1, gl_plot_energy_spec_plot_color);

		channel_index =   6 ; // ADC 7 
		uint_displayEnergySpectrum_ptr = &gl_uint_EnergySpectrumArray[module_index][channel_index][0]  ;
  		switch (loc_uint_DisplayEnergySpectrumHistogramShowChoose) {
		  case 0:
			uint_displayEnergySpectrum_ptr = &gl_uint_EnergySpectrumArray[module_index][channel_index][0]  ;
			break;																						  
		  case 1:
			uint_displayEnergySpectrum_ptr = &gl_uint_EnergySpectrum2Array[module_index][channel_index][0]  ;
			break;
		  case 2:
			uint_displayEnergySpectrum_ptr = &gl_uint_EnergySpectrum3Array[module_index][channel_index][0]  ;
			break;
		} // end switch (loc_uint_DisplayEnergySpectrumHistogramShowChoose)
		PlotY (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_7, uint_displayEnergySpectrum_ptr, plot_size, 
				    	   VAL_UNSIGNED_INTEGER, gl_plot_energy_spec_plot_style, VAL_NO_POINT, gl_plot_energy_spec_line_style, 1, gl_plot_energy_spec_plot_color);

		channel_index =   7 ; // ADC 8 
		uint_displayEnergySpectrum_ptr = &gl_uint_EnergySpectrumArray[module_index][channel_index][0]  ;
  		switch (loc_uint_DisplayEnergySpectrumHistogramShowChoose) {
		  case 0:
			uint_displayEnergySpectrum_ptr = &gl_uint_EnergySpectrumArray[module_index][channel_index][0]  ;
			break;																						  
		  case 1:
			uint_displayEnergySpectrum_ptr = &gl_uint_EnergySpectrum2Array[module_index][channel_index][0]  ;
			break;
		  case 2:
			uint_displayEnergySpectrum_ptr = &gl_uint_EnergySpectrum3Array[module_index][channel_index][0]  ;
			break;
		} // end switch (loc_uint_DisplayEnergySpectrumHistogramShowChoose)
		PlotY (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_8, uint_displayEnergySpectrum_ptr, plot_size, 
				    	   VAL_UNSIGNED_INTEGER, gl_plot_energy_spec_plot_style, VAL_NO_POINT, gl_plot_energy_spec_line_style, 1, gl_plot_energy_spec_plot_color);
	}
	 else {
		channel_index =   gl_uint_DisplayEnergySpectrumAdcShowChoose - 1 ;
		uint_displayEnergySpectrum_ptr = &gl_uint_EnergySpectrumArray[module_index][channel_index][0]  ;
  		switch (loc_uint_DisplayEnergySpectrumHistogramShowChoose) {
		  case 0:
			uint_displayEnergySpectrum_ptr = &gl_uint_EnergySpectrumArray[module_index][channel_index][0]  ;
			break;																						  
		  case 1:
			uint_displayEnergySpectrum_ptr = &gl_uint_EnergySpectrum2Array[module_index][channel_index][0]  ;
			break;
		  case 2:
			uint_displayEnergySpectrum_ptr = &gl_uint_EnergySpectrum3Array[module_index][channel_index][0]  ;
			break;
		} // end switch (loc_uint_DisplayEnergySpectrumHistogramShowChoose)
		PlotY (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_0, 
		 					uint_displayEnergySpectrum_ptr, plot_size, 
				    	   VAL_UNSIGNED_INTEGER, gl_plot_energy_spec_plot_style, VAL_NO_POINT, gl_plot_energy_spec_line_style, 1, gl_plot_energy_spec_plot_color);
	}

	return 0;
}





//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int CVICALLBACK CB_ClearSpectrumHistograms (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int  module_index, channel_index   ;
	switch (event)
		{
		case EVENT_COMMIT:
			clear_all_spectrum_histograms() ;
			break;
		}

	return 0;
}


//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
void find_energy_max_value_index (unsigned int module_index , unsigned int channel_index , unsigned int* max_value_index)
{
	unsigned int i ;
	unsigned int max_index = 0 ;
	unsigned int max_value = 0 ;

	for (i=0;i<MAX_NOF_ENERGY_SPECTRUM;i++) {
		if (gl_uint_EnergySpectrumArray[module_index][channel_index][i] > max_value ) { 
			max_value = gl_uint_EnergySpectrumArray[module_index][channel_index][i] ;
			max_index = i ;
		}
	}
	*max_value_index =  max_index ;
}   

//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
int CVICALLBACK CB_EnergySpectrumGaussFit (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
int  module_index, channel_index, i   ;
unsigned int *uint_displayEnergySpectrum_ptr    ;
int gauss_from_x, gauss_to_x, gauss_numpoints  ;	   

	switch (event)
		{
		case EVENT_COMMIT:


			GetCtrlVal (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_ENERGY_XMIN_SCALE, &gauss_from_x);
			GetCtrlVal (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_ENERGY_XMAX_SCALE, &gauss_to_x);

			gauss_from_x = gauss_from_x * ENERGY_SPECTRUM_DISPLAY_FACTOR  ; 	
			gauss_to_x = gauss_to_x * ENERGY_SPECTRUM_DISPLAY_FACTOR  ; 	

			gauss_numpoints =   gauss_to_x -  gauss_from_x ;
			if (gauss_numpoints<=2*ENERGY_SPECTRUM_DISPLAY_FACTOR) {
	  		// error messages
	  			break ;
	 		}

			if (gauss_numpoints>MAX_NOF_ENERGY_SPECTRUM) { // to large
	  		// error messages
	  			break ;
	 		}

			
			module_index  =   0  ;
			if (gl_unit_DisplayEnergySpectrumModuleNumber <= MAX_NO_OF_MODULES) { 
				module_index  =   gl_unit_DisplayEnergySpectrumModuleNumber - 1  ;
			}


			if (gl_uint_DisplayEnergySpectrumAdcShowChoose == 0) { // all
				openPanelDisplayGaussValues() ; 
				for (i=0;i<NO_OF_ADC_CHANNELS;i++) {
					channel_index =   i ;
					uint_displayEnergySpectrum_ptr = &gl_uint_EnergySpectrumArray[module_index][channel_index][0]  ;
					gauss_fit (gauss_from_x, gauss_numpoints, uint_displayEnergySpectrum_ptr) ;
					// outputs:  gl_double_gausspos, gl_double_gaussfwhm, gl_double_gaussint,  gl_double_MSE
					switch (i) {
						case 0:
 							SetCtrlVal (Panels[PANEL_DISPLAY_GAUSS_VALUE], PANEL_GAUS_PEAKPOS_1, gl_double_gausspos); 
 							SetCtrlVal (Panels[PANEL_DISPLAY_GAUSS_VALUE], PANEL_GAUS_PEAKWIDTH_1, gl_double_gaussfwhm); 
							break;
						case 1:
 							SetCtrlVal (Panels[PANEL_DISPLAY_GAUSS_VALUE], PANEL_GAUS_PEAKPOS_2, gl_double_gausspos); 
 							SetCtrlVal (Panels[PANEL_DISPLAY_GAUSS_VALUE], PANEL_GAUS_PEAKWIDTH_2, gl_double_gaussfwhm); 
							break;
						case 2:
 							SetCtrlVal (Panels[PANEL_DISPLAY_GAUSS_VALUE], PANEL_GAUS_PEAKPOS_3, gl_double_gausspos); 
 							SetCtrlVal (Panels[PANEL_DISPLAY_GAUSS_VALUE], PANEL_GAUS_PEAKWIDTH_3, gl_double_gaussfwhm); 
							break;
						case 3:
 							SetCtrlVal (Panels[PANEL_DISPLAY_GAUSS_VALUE], PANEL_GAUS_PEAKPOS_4, gl_double_gausspos); 
 							SetCtrlVal (Panels[PANEL_DISPLAY_GAUSS_VALUE], PANEL_GAUS_PEAKWIDTH_4, gl_double_gaussfwhm); 
							break;
						case 4:
 							SetCtrlVal (Panels[PANEL_DISPLAY_GAUSS_VALUE], PANEL_GAUS_PEAKPOS_5, gl_double_gausspos); 
 							SetCtrlVal (Panels[PANEL_DISPLAY_GAUSS_VALUE], PANEL_GAUS_PEAKWIDTH_5, gl_double_gaussfwhm); 
							break;
						case 5:
 							SetCtrlVal (Panels[PANEL_DISPLAY_GAUSS_VALUE], PANEL_GAUS_PEAKPOS_6, gl_double_gausspos); 
 							SetCtrlVal (Panels[PANEL_DISPLAY_GAUSS_VALUE], PANEL_GAUS_PEAKWIDTH_6, gl_double_gaussfwhm); 
							break;
						case 6:
 							SetCtrlVal (Panels[PANEL_DISPLAY_GAUSS_VALUE], PANEL_GAUS_PEAKPOS_7, gl_double_gausspos); 
 							SetCtrlVal (Panels[PANEL_DISPLAY_GAUSS_VALUE], PANEL_GAUS_PEAKWIDTH_7, gl_double_gaussfwhm); 
							break;
						case 7:
 							SetCtrlVal (Panels[PANEL_DISPLAY_GAUSS_VALUE], PANEL_GAUS_PEAKPOS_8, gl_double_gausspos); 
 							SetCtrlVal (Panels[PANEL_DISPLAY_GAUSS_VALUE], PANEL_GAUS_PEAKWIDTH_8, gl_double_gaussfwhm); 
							break;

					}
				
				}

			
			}
			else {
				channel_index =   gl_uint_DisplayEnergySpectrumAdcShowChoose - 1 ;
				uint_displayEnergySpectrum_ptr = &gl_uint_EnergySpectrumArray[module_index][channel_index][0]  ;
				gauss_fit (gauss_from_x, gauss_numpoints, uint_displayEnergySpectrum_ptr) ;
				// outputs:  gl_double_gausspos, gl_double_gaussfwhm, gl_double_gaussint,  gl_double_MSE
		
 				SetCtrlVal (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_PEAKPOS, gl_double_gausspos); 
 				SetCtrlVal (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_PEAKWIDTH, gl_double_gaussfwhm); 
 				SetCtrlVal (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_PEAKINT, gl_double_gaussint); 
 				SetCtrlVal (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_PEAKMSE, gl_double_MSE); 
		
				PlotXY (Panels[PANEL_DISPLAY_ENERGY_SPEC], PANEL_ESPE_GRAPH_ENERGY_SPEC_0, gl_double_EnergySpectrumGaussXdraw, gl_double_youtfit, gauss_numpoints,
					VAL_DOUBLE, VAL_DOUBLE, VAL_FAT_LINE, VAL_NO_POINT, VAL_SOLID, 1, VAL_BLUE);

			}

			break;
		}

	return 0;
}
		 



//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
// outputs:  gl_double_gausspos, gl_double_gaussfwhm, gl_double_gaussint,  gl_double_MSE
void gauss_fit (unsigned int gauss_from_x, unsigned int gauss_numpoints, unsigned int* uint_gaussEnergySpectrum_ptr)
{
int imax ;
static double ymax;
int i ;
		
		imax=0  ;
		ymax=0.0;
		for (i=0;i<gauss_numpoints;i++){
			gl_double_xfit[i]=i;
			gl_double_EnergySpectrumGaussXdraw[i]=i+gauss_from_x;
			gl_double_yinfit[i]=uint_gaussEnergySpectrum_ptr[i+gauss_from_x];
			if(gl_double_yinfit[i]>ymax){
				ymax=gl_double_yinfit[i];
				imax=i;
			}
		 }
	
		gl_double_coefs[0]=ymax; // Peak maximum
		gl_double_coefs[1]=imax; // Peak position
		gl_double_coefs[2]=(gauss_numpoints)/10.; // (max-min)/10. Peak width
		gl_double_coefs[3]=gl_double_yinfit[0];   //offset in background
		gl_double_coefs[4]=(gl_double_yinfit[gauss_numpoints-1]-gl_double_yinfit[0])/gauss_numpoints;
		NonLinearFit (gl_double_xfit, gl_double_yinfit, gl_double_youtfit, gauss_numpoints, gauss, gl_double_coefs, 5, &gl_double_MSE);
        			
		gl_double_gausspos  = (gl_double_coefs[1]+gauss_from_x)   / ENERGY_SPECTRUM_DISPLAY_FLOAT_FACTOR;
		gl_double_gaussfwhm = (2.354 *  gl_double_coefs[2]) / ENERGY_SPECTRUM_DISPLAY_FLOAT_FACTOR;	  // 2 x SQRT(2 x ln(2))=2.355
		gl_double_gaussint  = (2.5066 * gl_double_coefs[0] * gl_double_coefs[2]) ;                    // SQRT(2Pi) =2.5066 (x SIG x MAX = AREA)

   return ;
}   



//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 
double gauss (double x, double a[], int ncoef)
{
   double value;
   
   value = a[0]*exp(-0.5*pow((x-a[1])/a[2],2))+a[3]+a[4]*x;
   return (value);
}   





