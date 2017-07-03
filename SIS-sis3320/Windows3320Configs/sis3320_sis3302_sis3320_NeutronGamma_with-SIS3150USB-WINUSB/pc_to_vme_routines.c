/*********************************************************************************/
/*                                                                               */
/*  Project: SIS VME Master Library                                              */
/*                                                                               */
/*  Filename: pc_to_vme_routines.c                                               */
/*                                                                               */
/*  Funktion:                                                                    */
/*                                                                               */
/*  Autor:                TH                                                     */
/*  date:                 21.02.2005                                             */
/*  last modification:    09.07.2010                                             */
/*                                                                               */
/*  05.02.2010: add sub_vme_A32BLT32FIFO_read, sub_vme_A32MBLT64FIFO_read        */
/*  23.04.2010: add sub_vme_A32BLT32_write, sub_vme_A32MBLT64_write		         */
/*  23.04.2010: add sub_vme_A32BLT32FIFO_write, sub_vme_A32MBLT64FIFO_write      */
/*  07.07.2010: add sub_vme_A32DMAFIFO_write                                     */
/*                                                                               */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*  SIS  Struck Innovative Systeme GmbH                                          */
/*                                                                               */
/*  Harksheider Str. 102A                                                        */
/*  22399 Hamburg                                                                */
/*                                                                               */
/*  Tel. +49 (0)40 60 87 305 0                                                   */
/*  Fax  +49 (0)40 60 87 305 20                                                  */
/*                                                                               */
/*  http://www.struck.de                                                         */
/*                                                                               */
/*  © 2010                                                                       */
/*                                                                               */
/*********************************************************************************/


//
//--------------------------------------------------------------------------- 
// Include files                                                              
//--------------------------------------------------------------------------- 

#include <windows.h>
//#include <formatio.h>
//#include <cvirte.h>     
//#include <userint.h>
#include <stdio.h> 
#include <math.h> 
//#include <utility.h> 
//#include <ansi_c.h>
#include <stdio.h>

	  
#include "pc_vme_interface_defines.h"



//int sub_vme_A32D32_read (unsigned int vme_adr, unsigned int* vme_data) ;
//int sub_vme_A32D32_write (unsigned int vme_adr, unsigned int vme_data) ;
//int sub_load_vme_sis3150_tigersharcs (unsigned int vme_adr, char* loaderfile_path)  ;










/********************************************************************************************************/
/********************************************************************************************************/
/********************************************************************************************************/
/********************************************************************************************************/

// non priv
//   vme_am_mode = 0x8 ;  // MBLT64 
//   vme_am_mode = 0xB ;  // BLT32
//   vme_am_mode = 0x9 ;  // D32

// supervisor
//   vme_am_mode = 0xC ;  // MBLT64 
//   vme_am_mode = 0xF ;  // BLT32
//   vme_am_mode = 0xD ;  // D32

int sub_vme_A32BLT32_read (unsigned int vme_adr, unsigned int* dma_buffer, unsigned int request_nof_words, unsigned int* got_nof_words)
{
   int error  ;

#ifdef PCI_VME_INTERFACE  // Optical
	error = sis1100w_Vme_Dma_Read(&gl_sis1100_device, vme_adr, 0xf,4,0, dma_buffer, request_nof_words, got_nof_words) ;
#endif   


   
#ifndef PCI_VME_INTERFACE   // USB_VME_INTERFACE 
	error = sis3150Usb_Vme_Dma_Read(gl_USBDevice, vme_adr, 0xf, 4, 0,dma_buffer, request_nof_words, got_nof_words);   
#endif   
   
   return error ;
} // end function  ()



int sub_vme_A32MBLT64_read (unsigned int vme_adr, unsigned int* dma_buffer, unsigned int request_nof_words, unsigned int* got_nof_words)
{
   int error  ;

#ifdef PCI_VME_INTERFACE  // Optical
	error = sis1100w_Vme_Dma_Read(&gl_sis1100_device, vme_adr, 0x8,4,0, dma_buffer, request_nof_words, got_nof_words) ;
#endif   


   
#ifndef PCI_VME_INTERFACE   // USB_VME_INTERFACE 
	error = sis3150Usb_Vme_Dma_Read(gl_USBDevice, vme_adr, 0x8, 8, 0,dma_buffer, request_nof_words & 0xfffffffe, got_nof_words);   
#endif   
   
   return error ;
} // end function  ()






	 

/********************************************************************************************************/

int sub_vme_A32BLT32FIFO_read (unsigned int vme_adr, unsigned int* dma_buffer, unsigned int request_nof_words, unsigned int* got_nof_words)
{
   int error  ;

#ifdef PCI_VME_INTERFACE  // Optical
	error = sis1100w_Vme_Dma_Read(&gl_sis1100_device, vme_adr, 0xf,4,1, dma_buffer, request_nof_words, got_nof_words) ;
#endif   


   
#ifndef PCI_VME_INTERFACE   // USB_VME_INTERFACE 
	error = sis3150Usb_Vme_Dma_Read(gl_USBDevice, vme_adr, 0xf, 4, 1,dma_buffer, request_nof_words, got_nof_words);   
#endif   
   
   return error ;
} // end function  ()



int sub_vme_A32MBLT64FIFO_read (unsigned int vme_adr, unsigned int* dma_buffer, unsigned int request_nof_words, unsigned int* got_nof_words)
{
   int error  ;

#ifdef PCI_VME_INTERFACE  // Optical
	error = sis1100w_Vme_Dma_Read(&gl_sis1100_device, vme_adr, 0x8,4,1, dma_buffer, request_nof_words, got_nof_words) ;
#endif   


   
#ifndef PCI_VME_INTERFACE   // USB_VME_INTERFACE 
	error = sis3150Usb_Vme_Dma_Read(gl_USBDevice, vme_adr, 0x8, 8, 1,dma_buffer, request_nof_words & 0xfffffffe, got_nof_words);   
#endif   
   
   return error ;
} // end function  ()








/********************************************************************************************************/


int sub_vme_A32D32_read (unsigned int vme_adr, unsigned int* vme_data)
{
   int error  ;

#ifdef PCI_VME_INTERFACE  // Optical
	error = sis1100w_Vme_Single_Read(&gl_sis1100_device, vme_adr ,0x9,4,vme_data )  ;
#endif   


#ifndef PCI_VME_INTERFACE   // USB_VME_INTERFACE 
	error = vme_A32D32_read(gl_USBDevice, vme_adr, vme_data)  ;
#endif   

   return error ;
} // end function  ()


/********************************************************************************************************/


int sub_vme_A32D32_write (unsigned int vme_adr, unsigned int vme_data)
{
   int error  ;

#ifdef PCI_VME_INTERFACE  // Optical
	error = sis1100w_Vme_Single_Write(&gl_sis1100_device, vme_adr ,0x9,4,vme_data )  ;
#endif   


#ifndef PCI_VME_INTERFACE   // USB_VME_INTERFACE 
	error = vme_A32D32_write(gl_USBDevice, vme_adr, vme_data)  ;
#endif   

   return error ;
} // end function  ()







/********************************************************************************************************/
/********************************************************************************************************/
int sub_vme_A32BLT32_write (unsigned int vme_adr, unsigned int* dma_buffer, unsigned int request_nof_words, unsigned int* written_nof_words)
{
   int error  ;

#ifdef PCI_VME_INTERFACE  // Optical
	error = sis1100w_Vme_Dma_Write(&gl_sis1100_device, vme_adr, 0xf,4,0, dma_buffer, request_nof_words, written_nof_words) ;
#endif   


   
#ifndef PCI_VME_INTERFACE   // USB_VME_INTERFACE 
	error = sis3150Usb_Vme_Dma_Write(gl_USBDevice, vme_adr, 0xf, 4, 0,dma_buffer, request_nof_words, written_nof_words);   
#endif   
   
   return error ;
} // end function  ()
/********************************************************************************************************/


int sub_vme_A32MBLT64_write (unsigned int vme_adr, unsigned int* dma_buffer, unsigned int request_nof_words, unsigned int* written_nof_words)
{
   int error  ;

#ifdef PCI_VME_INTERFACE  // Optical
	error = sis1100w_Vme_Dma_Write(&gl_sis1100_device, vme_adr, 0x8,4,0, dma_buffer, request_nof_words, written_nof_words) ;
#endif   


   
#ifndef PCI_VME_INTERFACE   // USB_VME_INTERFACE 
	error = sis3150Usb_Vme_Dma_Write(gl_USBDevice, vme_adr, 0x8, 8, 0,dma_buffer, request_nof_words & 0xfffffffe, written_nof_words);   
#endif   
   
   return error ;
} // end function  ()

/********************************************************************************************************/

int sub_vme_A32BLT32FIFO_write (unsigned int vme_adr, unsigned int* dma_buffer, unsigned int request_nof_words, unsigned int* written_nof_words)
{
   int error  ;

#ifdef PCI_VME_INTERFACE  // Optical
	error = sis1100w_Vme_Dma_Write(&gl_sis1100_device, vme_adr, 0xf,4,1, dma_buffer, request_nof_words, written_nof_words) ;
#endif   


   
#ifndef PCI_VME_INTERFACE   // USB_VME_INTERFACE 
	error = sis3150Usb_Vme_Dma_Write(gl_USBDevice, vme_adr, 0xf, 4, 1,dma_buffer, request_nof_words, written_nof_words);   
#endif   
   
   return error ;
} // end function  ()
/********************************************************************************************************/


int sub_vme_A32MBLT64FIFO_write (unsigned int vme_adr, unsigned int* dma_buffer, unsigned int request_nof_words, unsigned int* written_nof_words)
{
   int error  ;

#ifdef PCI_VME_INTERFACE  // Optical
	error = sis1100w_Vme_Dma_Write(&gl_sis1100_device, vme_adr, 0x8,4,1, dma_buffer, request_nof_words, written_nof_words) ;
#endif   


   
#ifndef PCI_VME_INTERFACE   // USB_VME_INTERFACE 
	error = sis3150Usb_Vme_Dma_Write(gl_USBDevice, vme_adr, 0x8, 8, 1, dma_buffer, request_nof_words & 0xfffffffe, written_nof_words);   
#endif   
   
   return error ;
} // end function  ()
/********************************************************************************************************/



int sub_vme_A32DMA_D32FIFO_write (unsigned int vme_adr, unsigned int* dma_buffer, unsigned int request_nof_words, unsigned int* put_nof_words)
{
   int error  ;

#ifdef PCI_VME_INTERFACE  // Optical
	error = sis1100w_Vme_Dma_Write(&gl_sis1100_device, vme_adr, 0x9,4,1, dma_buffer, request_nof_words, put_nof_words) ;
#endif   


   
#ifndef PCI_VME_INTERFACE   // USB_VME_INTERFACE 
	error = sis3150Usb_Vme_Dma_Write(gl_USBDevice, vme_adr, 0x9, 4, 1,dma_buffer, request_nof_words, put_nof_words);   
#endif   
   
   return error ;
} // end function  ()


/********************************************************************************************************/









#ifdef not_used

int sub_load_vme_sis3150_tigersharcs (unsigned int vme_adr, char* loaderfile_path)
{
   int error  ;

#ifdef PCI_VME_INTERFACE  // Optical
	error = load_tigersharcs(vme_adr,  loaderfile_path)   ;     
#endif   


#ifndef PCI_VME_INTERFACE   // USB_VME_INTERFACE 
	error = usb_load_vme_sis3150_tigersharcs(gl_USBDevice, vme_adr,  loaderfile_path)  ;
#endif   

   return error ;
} // end function  ()



/********************************************************************************************************************/



int sub_vme_sis3150_tigersharcs_Reset (unsigned int vme_adr)
{
   int error  ;

#ifdef PCI_VME_INTERFACE  // Optical
	error = vme_sis3150_tigersharcs_Reset(vme_adr)   ;     
#endif   


#ifndef PCI_VME_INTERFACE   // USB_VME_INTERFACE 
	error = usb_vme_sis3150_tigersharcs_Reset(gl_USBDevice, vme_adr)  ;
#endif   

   return error ;
} // end function  ()

/********************************************************************************************************************/



int sub_load_vme_sis3150_tigersharcs_without_Reset (unsigned int vme_adr, char* loaderfile_path)
{
   int error  ;

#ifdef PCI_VME_INTERFACE  // Optical
	error = load_vme_sis3150_tigersharcs_without_Reset(vme_adr,  loaderfile_path)   ;     
#endif   


#ifndef PCI_VME_INTERFACE   // USB_VME_INTERFACE 
	error = usb_load_vme_sis3150_tigersharcs_without_Reset(gl_USBDevice, vme_adr,  loaderfile_path)  ;
#endif   

   return error ;
} // end function  ()

/********************************************************************************************************************/



#endif

/********************************************************************************************************/
/********************************************************************************************************/
/********************************************************************************************************/
/********************************************************************************************************/
/********************************************************************************************************/



