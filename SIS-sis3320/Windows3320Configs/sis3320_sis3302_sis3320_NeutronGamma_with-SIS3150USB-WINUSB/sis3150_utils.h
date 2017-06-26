/***************************************************************************/
/*                                                                         */
/*  Filename: sis3150_utils.h                                              */
/*                                                                         */
/*  Funktion:                                                              */
/*                                                                         */
/*  Autor:                TH                                               */
/*  date:                 01.06.2003                                       */
/*  last modification:    29.04.2005                                       */
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


/*===========================================================================*/
/* Prototypes					  			     */
/*===========================================================================*/


int load_vme_sis3150_tigersharcs_without_Reset(u_int32_t sis3150_base_addr,  char* loaderfile_path)   ;
int vme_sis3150_tigersharcs_Reset(u_int32_t sis3150_base_addr) ;

int load_tigersharcs(u_int32_t sis3150_base_addr,  char* loaderfile_path) ;










