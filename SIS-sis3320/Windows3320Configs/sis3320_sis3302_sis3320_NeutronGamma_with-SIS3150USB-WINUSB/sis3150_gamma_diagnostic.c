/***************************************************************************/
/*                                                                         */
/*  Filename: sis3150_gamma_diagnostic.c                                   */
/*                                                                         */
/*  Funktion: configuration                                                */
/*                                                                         */
/*  Autor:                TH                                               */
/*  date:                 28.11.2005                                       */
/*  last modification:    01.12.2005                                       */
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


//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 

int CVICALLBACK CB_Diag_Pattern_Reset (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
		 	resetDiagPatternArraysAndScaling()   ;
			break;
		}
	return 0;
}

//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 

int CVICALLBACK CB_PrintPanelDiagnostic (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			PrintPanel (Panels[PANEL_DISPLAY_DIAGNOSTIC], "", 1, VAL_FULL_PANEL, 1);   
			break;
		}
	return 0;
}           


//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 

int CVICALLBACK CB_ClosePanelDisplayDiagnostic (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			closePanelDiagnosticPattern() ;

			break;
		}
	return 0;
}


//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 

int openPanelDiagnosticPattern(unsigned int nofModules)  
{
double xmin;
double xmax;
double ymin;
double ymax;
char text[80] ;	
	SetPanelPos(Panels[PANEL_DISPLAY_DIAGNOSTIC],DEFINE_PANEL_DIAG_PATTERN_POS_Y,DEFINE_PANEL_DIAG_PATTERN_POS_X)  ;   // y, x
	DisplayPanel (Panels[PANEL_DISPLAY_DIAGNOSTIC]);
   	//DeleteGraphPlot (Panels[PANEL_DISPLAY_DIAGNOSTIC], PANEL_DIAG_GRAPH_PATT1, -1, VAL_IMMEDIATE_DRAW);
   	//DeleteGraphPlot (Panels[PANEL_DISPLAY_DIAGNOSTIC], PANEL_DIAG_GRAPH_PATT2, -1, VAL_IMMEDIATE_DRAW);
   	//DeleteGraphPlot (Panels[PANEL_DISPLAY_DIAGNOSTIC], PANEL_DIAG_GRAPH_PATT3, -1, VAL_IMMEDIATE_DRAW);

// Graph Pattern1 of Diagnostic Panel
	xmin =  0.5 ;
	xmax =  (double) ((nofModules * 8) + 0.6 ) ;
	SetAxisScalingMode  (Panels[PANEL_DISPLAY_DIAGNOSTIC],PANEL_DIAG_GRAPH_PATT1, VAL_XAXIS, VAL_MANUAL, xmin, xmax)  ;
	
	xmin =  0.5 ;
	xmax =  (double) ((nofModules * 8) + 0.6 ) ;
	SetAxisScalingMode  (Panels[PANEL_DISPLAY_DIAGNOSTIC],PANEL_DIAG_GRAPH_PATT2, VAL_XAXIS, VAL_MANUAL, xmin, xmax)  ;

	xmin =  1.4 ;
	xmax =  15.6 ;
	SetAxisScalingMode  (Panels[PANEL_DISPLAY_DIAGNOSTIC],PANEL_DIAG_GRAPH_PATT4, VAL_XAXIS, VAL_MANUAL, xmin, xmax)  ;

	return 0;
}
		  
//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 

int closePanelDiagnosticPattern(void) 
{												
 	SetMenuBarAttribute  (MenuBars[RUNCTRL_MENU_BAR], MENUCTRLRU_WINDOW_RUN_DIAG_ACTIV, ATTR_DIMMED, ON);
	gl_uint_RunCheckDisplayDiagnosticFlag     = 0  ;  // off
	SetCtrlVal (Panels[RUN_CTRL_MENUE], RUN_CTRL_CHECKBOX_DISPL_DIAG, gl_uint_RunCheckDisplayDiagnosticFlag);  
	HidePanel(Panels[PANEL_DISPLAY_DIAGNOSTIC]); //Clear Panel 
	return 0;
}



//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 

int resetDiagPatternArraysAndScaling(void) 
{
int i,j  ;
double ymin;
double ymax;


// Graph Pattern1 of Diagnostic Panel

	for (i=0; i<MAX_NO_OF_CHANNELS; i++) {
		gl_uint_CountOfTriggersChannelBasedArray[i] = 0 ;
	}
	ymin =  0.0 ;
	ymax =  100.0 ;
	SetAxisScalingMode  (Panels[PANEL_DISPLAY_DIAGNOSTIC],PANEL_DIAG_GRAPH_PATT1, VAL_LEFT_YAXIS, VAL_AUTOSCALE, ymin, ymax)  ;


// Graph Pattern2 of Diagnostic Panel

	for (i=0; i<MAX_NO_OF_CHANNELS; i++) {
		gl_uint_CountOfTriggersEventBasedArray[i] = 0 ;
	}
	ymin =  0.0 ;
	ymax =  100.0 ;
	SetAxisScalingMode  (Panels[PANEL_DISPLAY_DIAGNOSTIC],PANEL_DIAG_GRAPH_PATT2, VAL_LEFT_YAXIS, VAL_AUTOSCALE, ymin, ymax)  ;

// Graph Pattern4 of Diagnostic Panel
	for (i=0; i<16; i++) {
		gl_uint_CountOfPileupsTriggerCountBasedArray[i] = 0 ;
	}
	ymin =  0.0 ;
	ymax =  100.0 ;
	SetAxisScalingMode  (Panels[PANEL_DISPLAY_DIAGNOSTIC],PANEL_DIAG_GRAPH_PATT4, VAL_LEFT_YAXIS, VAL_AUTOSCALE, ymin, ymax)  ;

	return 0;
}


//--------------------------------------------------------------------------- 
//                                                             
//--------------------------------------------------------------------------- 

int displayDiagPattern (unsigned int nofModules) 
{
int i,j ;
unsigned int x[MAX_NO_OF_CHANNELS] ;
ColorMapEntry colors[8];
int minArrayI, maxArrayI;
double minArrayV, maxArrayV;
//unsigned int  gl_uint_CountOfTrigger2DPattern3[MAX_NO_OF_MODULES][NO_OF_ADC_CHANNELS]  ;
double   magnitude[MAX_NO_OF_MODULES][NO_OF_ADC_CHANNELS] ;
double *help ;


	for (i=0; i<MAX_NO_OF_CHANNELS; i++) {  x[i] = i+1  ; }
     	//DeleteGraphPlot (Panels[PANEL_DISPLAY_DIAGNOSTIC], PANEL_DIAG_GRAPH_PATT1, -1, VAL_IMMEDIATE_DRAW);
     	//DeleteGraphPlot (Panels[PANEL_DISPLAY_DIAGNOSTIC], PANEL_DIAG_GRAPH_PATT2, -1, VAL_IMMEDIATE_DRAW);
     	//DeleteGraphPlot (Panels[DIAG_PATTERN], DIAGPANEL1_GRAPH_PATT3, -1, VAL_IMMEDIATE_DRAW);

  		PlotXY (Panels[PANEL_DISPLAY_DIAGNOSTIC], PANEL_DIAG_GRAPH_PATT1,x, gl_uint_CountOfTriggersChannelBasedArray,  
  			       nofModules * 8, 
			       VAL_UNSIGNED_INTEGER, VAL_UNSIGNED_INTEGER, VAL_VERTICAL_BAR, VAL_NO_POINT, VAL_SOLID, 1, VAL_RED);
	

  		PlotXY (Panels[PANEL_DISPLAY_DIAGNOSTIC], PANEL_DIAG_GRAPH_PATT2,x, gl_uint_CountOfTriggersEventBasedArray,  
  			       nofModules * 8, 
			       VAL_UNSIGNED_INTEGER, VAL_UNSIGNED_INTEGER, VAL_BASE_ZERO_VERTICAL_BAR, VAL_NO_POINT, VAL_SOLID, 1, VAL_RED);
	


// 		PlotY (Panels[PANEL_DISPLAY_DIAGNOSTIC], PANEL_DIAG_GRAPH_PATT2, 
// 		 					gl_uint_CountOfTriggersEventBasedArray, (nofModules * 8), 
// 				    	   VAL_UNSIGNED_INTEGER, VAL_BASE_ZERO_VERTICAL_BAR, VAL_NO_POINT, VAL_SOLID, 1, VAL_RED);

  		PlotXY (Panels[PANEL_DISPLAY_DIAGNOSTIC], PANEL_DIAG_GRAPH_PATT4,x, gl_uint_CountOfPileupsTriggerCountBasedArray,  
  			       16, 
			       VAL_UNSIGNED_INTEGER, VAL_UNSIGNED_INTEGER, VAL_BASE_ZERO_VERTICAL_BAR, VAL_NO_POINT, VAL_SOLID, 1, VAL_RED);
        

	return 0 ;
}

