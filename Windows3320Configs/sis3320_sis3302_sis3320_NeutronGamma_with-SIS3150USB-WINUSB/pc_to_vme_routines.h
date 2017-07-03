/*********************************************************************************/
/*                                                                               */
/*  Project: SIS VME Master Library                                              */
/*                                                                               */
/*  Filename: pc_to_vme_routines.h                                               */
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


int sub_vme_A32D32_read (unsigned int vme_adr, unsigned int* vme_data) ;
int sub_vme_A32D32_write (unsigned int vme_adr, unsigned int vme_data) ;


#ifdef raus
int sub_load_vme_sis3150_tigersharcs (unsigned int vme_adr, char* loaderfile_path)  ;
int sub_load_vme_sis3150_tigersharcs_without_Reset (unsigned int vme_adr, char* loaderfile_path)  ;
int sub_vme_sis3150_tigersharcs_Reset (unsigned int vme_adr)	;
#endif

int sub_vme_A32BLT32_read (unsigned int vme_adr, unsigned int* dma_buffer, unsigned int request_nof_words, unsigned int* got_nof_words)  ;
int sub_vme_A32MBLT64_read (unsigned int vme_adr, unsigned int* dma_buffer, unsigned int request_nof_words, unsigned int* got_nof_words)  ;

int sub_vme_A32BLT32FIFO_read (unsigned int vme_adr, unsigned int* dma_buffer, unsigned int request_nof_words, unsigned int* got_nof_words)  ;
int sub_vme_A32MBLT64FIFO_read (unsigned int vme_adr, unsigned int* dma_buffer, unsigned int request_nof_words, unsigned int* got_nof_words)  ;


int sub_vme_A32BLT32FIFO_write (unsigned int vme_adr, unsigned int* dma_buffer, unsigned int request_nof_words, unsigned int* written_nof_words)  ;
int sub_vme_A32MBLT64FIFO_write (unsigned int vme_adr, unsigned int* dma_buffer, unsigned int request_nof_words, unsigned int* written_nof_words)  ;

int sub_vme_A32DMA_D32FIFO_write (unsigned int vme_adr, unsigned int* dma_buffer, unsigned int request_nof_words, unsigned int* put_nof_words)	  ;

