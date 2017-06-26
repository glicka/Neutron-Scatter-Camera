/***************************************************************************/
/*                                                                         */
/*  Project: SIS                                                           */
/*                                                                         */
/*  Filename: pc_vme_interface_defines.h                                   */
/*                                                                         */
/*  Funktion:                                                 */
/*                                                                         */
/*  Autor:                TH                                               */
/*  date:                 21.02.2005                                       */
/*  last modification:    14.07.2010                                       */
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
/*  © 2010                                                                 */
/*                                                                         */
/***************************************************************************/


// PC interface
//#define NO_INTERFACE				// dummy VME cycles
//#define PCI_VME_INTERFACE			// sis1100/3100 optical interface
#define USB_VME_INTERFACE			// sis3150USB USB2.0 interface
#define USB_WIN_DRIVER				// USB-WIN driver 1.0.0.0 (2009) else USB-Cypress
#define USB_WIN_DRIVER_1.1.0.2		// USB-WIN driver (2009) else USB-Cypress



#ifdef NO_INTERFACE
	#define _DEBUG
	#define PLX_9054
	#define PCI_CODE
	#define LITTLE_ENDIAN
	#include "..\temp\PlxApi.h"
	#include "..\temp\Reg9054.h"		// Header sis1100w.dll
	#include "..\temp\sis1100w.h"		// Header sis1100w.dll
	#include "..\temp\sis3100_vme_calls.h"
#endif


#ifdef PCI_VME_INTERFACE

	#define _DEBUG
	#define PLX_9054
	#define PCI_CODE
	#define LITTLE_ENDIAN

	#include "PlxApi.h"
	#include "Reg9054.h"

	#include "sis1100w.h"		// Header sis1100w.dll
	#include "sis3100_vme_calls.h"


#endif

  extern struct SIS1100_Device_Struct  gl_sis1100_device ;




#ifdef USB_VME_INTERFACE

	#include "sis3150_usb_wrapper.h" // Header  
	#include "sis3150usb_vme_calls.h"  
	#include "sis3150usb_utils.h"  



extern HANDLE  gl_USBDevice ;


#endif
