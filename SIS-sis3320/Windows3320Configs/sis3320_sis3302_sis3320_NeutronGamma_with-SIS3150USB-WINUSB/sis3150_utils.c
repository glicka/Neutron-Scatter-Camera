/***************************************************************************/
/*                                                                         */
/*  Filename: sis3150_utils.c                                              */
/*                                                                         */
/*  Funktion:                                                              */
/*                                                                         */
/*  Autor:                TH                                               */
/*  date:                 01.06.2003                                       */
/*  last modification:    29.04.2005                                       */
/*  24.03.2005: CMC1 and CMC2 Reset removed                                */
/*  29.04.2005: add load_without Reset and Reset                           */
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
/* Headers								     */
/*===========================================================================*/

#include "pc_vme_interface_defines.h"

#ifdef PCI_VME_INTERFACE  // Optical


#include <windows.h>
#include <formatio.h>
#include <cvirte.h>
#include <userint.h>
#include <stdio.h>
#include <ansi_c.h>
#include <utility.h>         


//#include "vme_interface_defines.h"
#include "sis3320_NeutronGamma_global.h" 	// Globale Defines fuers Programm
#include "sis3150.h" 			//  


#define MAX_LOADER_FILE_LENGTH        0x0100000 

 
/*===========================================================================*/
/* Prototypes					  			     */
/*===========================================================================*/

#include "sis3150_utils.h"


/*===========================================================================*/
/* Load DSP     					  		     */
/*===========================================================================*/



/*===========================================================================*/
int vme_sis3150_tigersharcs_Reset(u_int32_t sis3150_base_addr)
{
	int error=0;
    unsigned int addr;
    addr =   sis3150_base_addr + SIS3150_KEY_TS_RESET   ;
    if ((error = sis1100w_Vme_Single_Write(&gl_sis1100_device, addr ,0x9,4,0x0 ) ) != 0) { 
        return -1;
	}
 return 0 ;
}

/*===========================================================================*/


int load_tigersharcs(u_int32_t sis3150_base_addr,  char* loaderfile_path)
{
	int error=0;
	error = vme_sis3150_tigersharcs_Reset(sis3150_base_addr) ;
    if (error != 0) { return -1; }
	error = load_vme_sis3150_tigersharcs_without_Reset(sis3150_base_addr,  loaderfile_path) ;
    if (error != 0) { return -1; }
 return 0 ;
}
/*===========================================================================*/


int load_vme_sis3150_tigersharcs_without_Reset(u_int32_t sis3150_base_addr,  char* loaderfile_path)
{
	int error=0;
    int retcode=1;
    int count=0,loadcount=0;
    int offset;
    int currentaddress ;
//    char line_in[1024];
    FILE *loaderfile;
    unsigned int tempword[0x10000];
    unsigned int read_tempword[0x10000]; // 
    u_int32_t data ;
    u_int32_t addr ;

	int i;
    unsigned int  loader_header_word;
    unsigned int  loader_format_length;
    unsigned int  loader_format_addr;
    unsigned int  ts_ilatl, ts_ilath;
    unsigned int  ts_imaskl, ts_imaskh;
    unsigned int  ts_pmaskl, ts_pmaskh;
    unsigned int  timer;
    unsigned int  clear_virp_error;


// SYSCON setup
//	data = 0x279e7 ;  default after reset

    data = 0x0 ;
    data = data + 0x27         ; // Bank 0 : slow (5), pipe = 0 (4:3), 3 wait cycles (2:1) , idle (0)
    data = data + (0x27 << 6)  ; // Bank 1 : slow (5), pipe = 0 (4:3), 3 wait cycles (2:1) , idle (0)
    data = data + (0x27 << 12) ; // HOST   : slow (5), pipe = 0 (4:3), 3 wait cycles (2:1) , idle (0)

    data = data + (0x1  << 19) ; // BUS Width MEM:    64 bit
    data = data + (0x1  << 20) ; // BUS Width Multi:  64 bit
//    data = data + (0x0  << 21) ; // BUS Width HOST:   32 bit erstmal
    data = data + (0x1  << 21) ; // BUS Width HOST:   64 bit 

	
	addr = sis3150_base_addr + SIS3150_TS1_BASE +  TS_REG_SYSCON  ;
	if ((error = sis1100w_Vme_Single_Write(&gl_sis1100_device, addr ,0x9,4,data )) != 0) { 
		sisVME_ErrorHandling (error, addr, "sis1100w_Vme_Single_Write"); 
 		return -1;
	}

	addr = sis3150_base_addr + SIS3150_TS2_BASE +  TS_REG_SYSCON  ;
	if ((error = sis1100w_Vme_Single_Write(&gl_sis1100_device, addr,0x9,4,data )) != 0) { 
		sisVME_ErrorHandling (error, addr, "sis1100w_Vme_Single_Write"); 
 		return -1;
	}

#ifdef debug
	sis1100w_Vme_Single_Read(&gl_sis1100_device,(sis3150_base_addr+SIS3150_TS2_BASE+TS_REG_ILATL),0x9,4,&ts_ilatl ) ;
	sis1100w_Vme_Single_Read(&gl_sis1100_device,(sis3150_base_addr+SIS3150_TS2_BASE+TS_REG_ILATH),0x9,4,&ts_ilath ) ;
	sis1100w_Vme_Single_Read(&gl_sis1100_device,(sis3150_base_addr+SIS3150_TS2_BASE+TS_REG_IMASKL),0x9,4,&ts_imaskl ) ;
	sis1100w_Vme_Single_Read(&gl_sis1100_device,(sis3150_base_addr+SIS3150_TS2_BASE+TS_REG_IMASKH),0x9,4,&ts_imaskh ) ;
	sis1100w_Vme_Single_Read(&gl_sis1100_device,(sis3150_base_addr+SIS3150_TS2_BASE+TS_REG_PMASKL),0x9,4,&ts_pmaskl ) ;
	sis1100w_Vme_Single_Read(&gl_sis1100_device,(sis3150_base_addr+SIS3150_TS2_BASE+TS_REG_PMASKH),0x9,4,&ts_pmaskh ) ;
	printf("\n"); 
	printf("\n"); 
	printf("after reset: ILATH/ILATL      = 0x%08x    0x%08x\n", ts_ilath,ts_ilatl ); 
	printf("after reset: IMASKH/IMASKL    = 0x%08x    0x%08x\n", ts_imaskh,ts_imaskl ); 
	printf("after reset: PMASKH/PMASKL    = 0x%08x    0x%08x\n", ts_pmaskh,ts_pmaskl ); 
#endif
  
// SDRCON SDRAM configuration 
//	data = 0 ;  default after reset ; SDRAM is disabled

    data = 0x0 ;
    data = data + 0x1         ; // SDRAM Enable
    data = data + (0x1 << 1)  ; // CAS Latency = 2 Cycles 
    data = data + (0x0 << 3)  ; // no pipe
    data = data + (0x1 << 4)  ; // page boundary = 512
    data = data + (0x0 << 6)  ; // reserved

    data = data + (0x1 << 7)  ; // Refresh rate every 900 cycles; 900 x 16 ns = 14,4 us (must min 15,6)
    data = data + (0x0 << 9)  ; // Row precharge (Trp min =20ns)  2 cycles x 16 ns = 32 ns
    data = data + (0x1 << 11) ; // Row active time (Tras min = 45ns)  3 cycles x 16ns 48ns
    data = data + (0x1 << 14) ; // INIT Sequence

	
	addr = sis3150_base_addr + SIS3150_TS1_BASE +  TS_REG_SDRCON  ;
	if ((error = sis1100w_Vme_Single_Write(&gl_sis1100_device, addr ,0x9,4,data )) != 0) { 
		sisVME_ErrorHandling (error, addr, "sis1100w_Vme_Single_Write"); 
 		return -1;
	}

	addr = sis3150_base_addr + SIS3150_TS2_BASE +  TS_REG_SDRCON  ;
	if ((error = sis1100w_Vme_Single_Write(&gl_sis1100_device, addr,0x9,4,data )) != 0) { 
		sisVME_ErrorHandling (error, addr, "sis1100w_Vme_Single_Write"); 
 		return -1;
	}
  
  
#ifdef debug
	sis1100w_Vme_Single_Read(&gl_sis1100_device,(sis3150_base_addr+SIS3150_TS2_BASE+TS_REG_ILATL),0x9,4,&ts_ilatl ) ;
	sis1100w_Vme_Single_Read(&gl_sis1100_device,(sis3150_base_addr+SIS3150_TS2_BASE+TS_REG_ILATH),0x9,4,&ts_ilath ) ;
	sis1100w_Vme_Single_Read(&gl_sis1100_device,(sis3150_base_addr+SIS3150_TS2_BASE+TS_REG_IMASKL),0x9,4,&ts_imaskl ) ;
	sis1100w_Vme_Single_Read(&gl_sis1100_device,(sis3150_base_addr+SIS3150_TS2_BASE+TS_REG_IMASKH),0x9,4,&ts_imaskh ) ;
	sis1100w_Vme_Single_Read(&gl_sis1100_device,(sis3150_base_addr+SIS3150_TS2_BASE+TS_REG_PMASKL),0x9,4,&ts_pmaskl ) ;
	sis1100w_Vme_Single_Read(&gl_sis1100_device,(sis3150_base_addr+SIS3150_TS2_BASE+TS_REG_PMASKH),0x9,4,&ts_pmaskh ) ;
	printf("\n"); 
	printf("after read SDRCON: ILATH/ILATL      = 0x%08x    0x%08x\n", ts_ilath,ts_ilatl ); 
	printf("after read SDRCON: IMASKH/IMASKL    = 0x%08x    0x%08x\n", ts_imaskh,ts_imaskl ); 
	printf("after read SDRCON: PMASKH/PMASKL    = 0x%08x    0x%08x\n", ts_pmaskh,ts_pmaskl ); 
#endif  

  
  
  /* check  both TigerSharcs SYSCON and ID register */
    addr =   sis3150_base_addr + SIS3150_TS1_BASE +  TS_REG_SYSCON  ;
    if ((error = sis1100w_Vme_Single_Read(&gl_sis1100_device, addr ,0x9,4,&data )) != 0) { 
	    sisVME_ErrorHandling (error, addr, "sis1100w_Vme_Single_Read"); 
        return -1;
	}

  /* check  both TigerSharcs SYSCON and ID register */
    addr =   sis3150_base_addr + SIS3150_TS2_BASE +  TS_REG_SYSCON  ;
    if ((error = sis1100w_Vme_Single_Read(&gl_sis1100_device, addr ,0x9,4,&data )) != 0) { 
	    sisVME_ErrorHandling (error, addr, "sis1100w_Vme_Single_Read"); 
        return -1;
	}

#ifdef debug
	sis1100w_Vme_Single_Read(&gl_sis1100_device,(sis3150_base_addr+SIS3150_TS2_BASE+TS_REG_ILATL),0x9,4,&ts_ilatl ) ;
	sis1100w_Vme_Single_Read(&gl_sis1100_device,(sis3150_base_addr+SIS3150_TS2_BASE+TS_REG_ILATH),0x9,4,&ts_ilath ) ;
	sis1100w_Vme_Single_Read(&gl_sis1100_device,(sis3150_base_addr+SIS3150_TS2_BASE+TS_REG_IMASKL),0x9,4,&ts_imaskl ) ;
	sis1100w_Vme_Single_Read(&gl_sis1100_device,(sis3150_base_addr+SIS3150_TS2_BASE+TS_REG_IMASKH),0x9,4,&ts_imaskh ) ;
	sis1100w_Vme_Single_Read(&gl_sis1100_device,(sis3150_base_addr+SIS3150_TS2_BASE+TS_REG_PMASKL),0x9,4,&ts_pmaskl ) ;
	sis1100w_Vme_Single_Read(&gl_sis1100_device,(sis3150_base_addr+SIS3150_TS2_BASE+TS_REG_PMASKH),0x9,4,&ts_pmaskh ) ;
	printf("\n"); 
	printf("after read SYSCON: ILATH/ILATL      = 0x%08x    0x%08x\n", ts_ilath,ts_ilatl ); 
	printf("after read SYSCON: IMASKH/IMASKL    = 0x%08x    0x%08x\n", ts_imaskh,ts_imaskl ); 
	printf("after read SYSCON: PMASKH/PMASKL    = 0x%08x    0x%08x\n", ts_pmaskh,ts_pmaskl ); 
#endif


	/* disable all Link Input DMA channels ; from TS_REG_DMA_DC8 to TS_REG_DMA_DC11 */ 
    data = 0x0 ;
	for (i=0;i<16;i++) {
		addr = sis3150_base_addr + SIS3150_TS1_BASE +  TS_REG_DMA_DC8 + (4*i) ;
		if ((error = sis1100w_Vme_Single_Write(&gl_sis1100_device, addr,0x9,4,data )) != 0) { 
			sisVME_ErrorHandling (error, addr, "sis1100w_Vme_Single_Write"); 
 			return -1;
		}
	}
	/* disable all Link Input DMA channels ; from TS_REG_DMA_DC8 to TS_REG_DMA_DC11 */ 
    data = 0x0 ;
	for (i=0;i<16;i++) {
		addr = sis3150_base_addr + SIS3150_TS2_BASE +  TS_REG_DMA_DC8 + (4*i) ;
		if ((error = sis1100w_Vme_Single_Write(&gl_sis1100_device, addr,0x9,4,data )) != 0) { 
			sisVME_ErrorHandling (error, addr, "sis1100w_Vme_Single_Write"); 
 			return -1;
		}
	}

#ifdef debug
	sis1100w_Vme_Single_Read(&gl_sis1100_device,(sis3150_base_addr+SIS3150_TS2_BASE+TS_REG_ILATL),0x9,4,&ts_ilatl ) ;
	sis1100w_Vme_Single_Read(&gl_sis1100_device,(sis3150_base_addr+SIS3150_TS2_BASE+TS_REG_ILATH),0x9,4,&ts_ilath ) ;
	sis1100w_Vme_Single_Read(&gl_sis1100_device,(sis3150_base_addr+SIS3150_TS2_BASE+TS_REG_IMASKL),0x9,4,&ts_imaskl ) ;
	sis1100w_Vme_Single_Read(&gl_sis1100_device,(sis3150_base_addr+SIS3150_TS2_BASE+TS_REG_IMASKH),0x9,4,&ts_imaskh ) ;
	sis1100w_Vme_Single_Read(&gl_sis1100_device,(sis3150_base_addr+SIS3150_TS2_BASE+TS_REG_PMASKL),0x9,4,&ts_pmaskl ) ;
	sis1100w_Vme_Single_Read(&gl_sis1100_device,(sis3150_base_addr+SIS3150_TS2_BASE+TS_REG_PMASKH),0x9,4,&ts_pmaskh ) ;
	printf("\n"); 
	printf("after disable DMA: ILATH/ILATL      = 0x%08x    0x%08x\n", ts_ilath,ts_ilatl ); 
	printf("after disable DMA: IMASKH/IMASKL    = 0x%08x    0x%08x\n", ts_imaskh,ts_imaskl ); 
	printf("after disable DMA: PMASKH/PMASKL    = 0x%08x    0x%08x\n", ts_pmaskh,ts_pmaskl ); 
#endif


	/* disable all Link Receive and Transmit  */ 
    data = 0x0 ;
	for (i=0;i<4;i++) {
		addr = sis3150_base_addr + SIS3150_TS1_BASE +  TS_REG_LCTL0 + (4*i) ;
		if ((error = sis1100w_Vme_Single_Write(&gl_sis1100_device, addr,0x9,4,data )) != 0) { 
			sisVME_ErrorHandling (error, addr, "sis1100w_Vme_Single_Write"); 
 			return -1;
		}
	}
    data = 0x0 ;
	for (i=0;i<4;i++) {
		addr = sis3150_base_addr + SIS3150_TS2_BASE +  TS_REG_LCTL0 + (4*i) ;
		if ((error = sis1100w_Vme_Single_Write(&gl_sis1100_device, addr,0x9,4,data )) != 0) { 
			sisVME_ErrorHandling (error, addr, "sis1100w_Vme_Single_Write"); 
 			return -1;
		}
	}



    //usw
    loaderfile=fopen(loaderfile_path,"r");
    retcode = 1 ;
    if ((int)loaderfile>0) {
   //    printf("loader file %s opened\n",loaderfile_path);
       while (retcode>0) {
   //       tempword[count]= strtoul(line_in,NULL,32); 
	      retcode=fscanf(loaderfile,"0x%8x\n",&tempword[count]); 
          if (count<MAX_LOADER_FILE_LENGTH) {
             count++;
          }
          else {
	  	   printf("load file size too big\n");
             return -1;
	      }
       }
     // printf("load file length: %d\n",count);
     }
    else {
       printf("loader file %s not found\n",loaderfile_path);
      return -1;
     }
    fclose(loaderfile);


   // printf("loading SHARC DSP\n");

//    currentaddress=SHARCRAM;
 //	   printf("currentaddress = 0x%08x\n", currentaddress ); 



    loadcount=0 ;
    while (loadcount<(count-1)) {  
      loader_header_word = (tempword[loadcount] & 0xc0000000) ;
      switch (loader_header_word) {

	     case 0x0: {       // final init
			if ((tempword[loadcount] & 0x38000000) == 0x0) { // 
			  addr = sis3150_base_addr + SIS3150_TS1_BASE +  TS_MEMORY_BLOCK0  ;
			} 
			else {
			  addr = sis3150_base_addr + SIS3150_TS2_BASE +  TS_MEMORY_BLOCK0  ;
			} 
			loader_format_length = 0x100 ; // 256 word 			 
			loadcount++;
			if ((count-loadcount) < 0x100 ) {
   		    	write_system_messages ("loader File error in FINAL_INIT ((count-loadcount) < 0x100 ))", PRINT_DATE_NO)	   ;
				return -1;
			} 
			for (i=0;i<0x100;i++) {
				data = tempword[loadcount] ;
				if ((error = sis1100w_Vme_Single_Write(&gl_sis1100_device, addr + 4*i,0x9,4,data )) != 0) { 
	                sisVME_ErrorHandling (error, addr, "sis1100w_Vme_Single_Write"); 
				return -1;
				}
				loadcount++;
			}
          }
         break;  // case final init  

	     case 0x40000000: {       // write data to memory
			if ((tempword[loadcount] & 0x38000000) == 0x0) { // 
			  addr = sis3150_base_addr + SIS3150_TS1_BASE +  TS_MEMORY_BLOCK0  ;
			} 
			else {
			  addr = sis3150_base_addr + SIS3150_TS2_BASE +  TS_MEMORY_BLOCK0  ;
			} 
			loader_format_length = (tempword[loadcount] & 0xffff) ;			 
			loadcount++;
			loader_format_addr = (tempword[loadcount] * 4) ;			 
			loadcount++;
	
			if ((count-loadcount) < loader_format_length ) {
   		    	write_system_messages ("loader File error in FINAL_INIT ((count-loadcount) < loader_format_length ))", PRINT_DATE_NO)	   ;
				return -1;
			} 

			for (i=0;i<loader_format_length;i++) {
				data = tempword[loadcount] ;
				if ((error = sis1100w_Vme_Single_Write(&gl_sis1100_device, addr + loader_format_addr + 4*i,0x9,4,data )) != 0) { 
	                sisVME_ErrorHandling (error, addr, "sis1100w_Vme_Single_Write"); 
				return -1;
				}
				loadcount++;
			}

		  }
          break;   // case write data to memory


	    case 0x80000000: {       // clear memory
			if ((tempword[loadcount] & 0x38000000) == 0x0) { // 
			  addr = sis3150_base_addr + SIS3150_TS1_BASE +  TS_MEMORY_BLOCK0  ;
			} 
			else {
			  addr = sis3150_base_addr + SIS3150_TS2_BASE +  TS_MEMORY_BLOCK0  ;
			} 
			loader_format_length = (tempword[loadcount] & 0xffff) ;			 
			loadcount++;
			loader_format_addr = (tempword[loadcount] * 4) 		;	 
			loadcount++;
	
			for (i=0;i<loader_format_length;i++) {
				data = 0x0 ;
				if ((error = sis1100w_Vme_Single_Write(&gl_sis1100_device, addr + loader_format_addr + 4*i,0x9,4,data )) != 0) { 
	                sisVME_ErrorHandling (error, addr, "sis1100w_Vme_Single_Write"); 
				return -1;
				}
			}
		  }
          break;


	     case 0xC0000000: {       // not defined
   		    	write_system_messages ("loader File error in:  not defined ))", PRINT_DATE_NO)	   ;
           return -1 ;
           }
		   break;
        }    // end switch(loader_header_word)
		
 	} //while

#ifdef debug

	sis1100w_Vme_Single_Read(&gl_sis1100_device,(sis3150_base_addr+SIS3150_TS2_BASE+TS_REG_ILATL),0x9,4,&ts_ilatl ) ;
	sis1100w_Vme_Single_Read(&gl_sis1100_device,(sis3150_base_addr+SIS3150_TS2_BASE+TS_REG_ILATH),0x9,4,&ts_ilath ) ;
	sis1100w_Vme_Single_Read(&gl_sis1100_device,(sis3150_base_addr+SIS3150_TS2_BASE+TS_REG_IMASKL),0x9,4,&ts_imaskl ) ;
	sis1100w_Vme_Single_Read(&gl_sis1100_device,(sis3150_base_addr+SIS3150_TS2_BASE+TS_REG_IMASKH),0x9,4,&ts_imaskh ) ;
	sis1100w_Vme_Single_Read(&gl_sis1100_device,(sis3150_base_addr+SIS3150_TS2_BASE+TS_REG_PMASKL),0x9,4,&ts_pmaskl ) ;
	sis1100w_Vme_Single_Read(&gl_sis1100_device,(sis3150_base_addr+SIS3150_TS2_BASE+TS_REG_PMASKH),0x9,4,&ts_pmaskh ) ;

	printf("\n"); 
	printf("after write program: ILATH/ILATL      = 0x%08x    0x%08x\n", ts_ilath,ts_ilatl ); 
	printf("after write program: IMASKH/IMASKL    = 0x%08x    0x%08x\n", ts_imaskh,ts_imaskl ); 
	printf("after write program: PMASKH/PMASKL    = 0x%08x    0x%08x\n", ts_pmaskh,ts_pmaskl ); 
#endif



// write VIRP Service routine to TS at address 0x10fff0
// VIRP service routine
//     0     01820088    41     xr0 = 0x00000201;;                  // set NMOD and BTB enable (1/24/00) bits in sequencer control register
//     1     321a0088    42     SQCTLST = xr0;;                     // mnemonic changed to SQCTLST (12/19/00)
//     2     400008b3    43     rds;;                               // reduce interrupt to subroutine level
//     3     000008b0    44     jump 0x0 (ABS) (NP);;               // jump to last patch

// 	data = 0x01820088 ;
 	data = 0x88008201  ;
	addr = sis3150_base_addr + SIS3150_TS1_BASE +  (4 * 0x10fff0) ;
	if ((error = sis1100w_Vme_Single_Write(&gl_sis1100_device, addr,0x9,4,data )) != 0) { 
		sisVME_ErrorHandling (error, addr, "sis1100w_Vme_Single_Write");  return -1;
	}
	addr = sis3150_base_addr + SIS3150_TS2_BASE +  (4 * 0x10fff0) ;
	if ((error = sis1100w_Vme_Single_Write(&gl_sis1100_device, addr,0x9,4,data )) != 0) { 
		sisVME_ErrorHandling (error, addr, "sis1100w_Vme_Single_Write");  return -1;
	}

// 	data = 0x321a0088 ;
 	data = 0x88001a32       ;
	addr = sis3150_base_addr + SIS3150_TS1_BASE +  (4 * 0x10fff1) ;
	if ((error = sis1100w_Vme_Single_Write(&gl_sis1100_device, addr,0x9,4,data )) != 0) { 
		sisVME_ErrorHandling (error, addr, "sis1100w_Vme_Single_Write");  return -1;
	}
	addr = sis3150_base_addr + SIS3150_TS2_BASE +  (4 * 0x10fff1) ;
	if ((error = sis1100w_Vme_Single_Write(&gl_sis1100_device, addr,0x9,4,data )) != 0) { 
		sisVME_ErrorHandling (error, addr, "sis1100w_Vme_Single_Write");  return -1;
	}

// 	data = 0x400008b3 ;
 	data = 0xb3080040     ;
	addr = sis3150_base_addr + SIS3150_TS1_BASE +  (4 * 0x10fff2) ;
	if ((error = sis1100w_Vme_Single_Write(&gl_sis1100_device, addr,0x9,4,data )) != 0) { 
		sisVME_ErrorHandling (error, addr, "sis1100w_Vme_Single_Write");  return -1;
	}
	addr = sis3150_base_addr + SIS3150_TS2_BASE +  (4 * 0x10fff2) ;
	if ((error = sis1100w_Vme_Single_Write(&gl_sis1100_device, addr,0x9,4,data )) != 0) { 
		sisVME_ErrorHandling (error, addr, "sis1100w_Vme_Single_Write");  return -1;
	}

// 	data = 0x000008b0 ;
 	data = 0xb0080000 ;
	addr = sis3150_base_addr + SIS3150_TS1_BASE +  (4 * 0x10fff3) ;
	if ((error = sis1100w_Vme_Single_Write(&gl_sis1100_device, addr,0x9,4,data )) != 0) { 
		sisVME_ErrorHandling (error, addr, "sis1100w_Vme_Single_Write");  return -1;
	}
	addr = sis3150_base_addr + SIS3150_TS2_BASE +  (4 * 0x10fff3) ;
	if ((error = sis1100w_Vme_Single_Write(&gl_sis1100_device, addr,0x9,4,data )) != 0) { 
		sisVME_ErrorHandling (error, addr, "sis1100w_Vme_Single_Write");  return -1;
	}




#ifdef debug
	sis1100w_Vme_Single_Read(&gl_sis1100_device,(sis3150_base_addr+SIS3150_TS2_BASE+TS_REG_ILATL),0x9,4,&ts_ilatl ) ;
	sis1100w_Vme_Single_Read(&gl_sis1100_device,(sis3150_base_addr+SIS3150_TS2_BASE+TS_REG_ILATH),0x9,4,&ts_ilath ) ;
	sis1100w_Vme_Single_Read(&gl_sis1100_device,(sis3150_base_addr+SIS3150_TS2_BASE+TS_REG_IMASKL),0x9,4,&ts_imaskl ) ;
	sis1100w_Vme_Single_Read(&gl_sis1100_device,(sis3150_base_addr+SIS3150_TS2_BASE+TS_REG_IMASKH),0x9,4,&ts_imaskh ) ;
	sis1100w_Vme_Single_Read(&gl_sis1100_device,(sis3150_base_addr+SIS3150_TS2_BASE+TS_REG_PMASKL),0x9,4,&ts_pmaskl ) ;
	sis1100w_Vme_Single_Read(&gl_sis1100_device,(sis3150_base_addr+SIS3150_TS2_BASE+TS_REG_PMASKH),0x9,4,&ts_pmaskh ) ;
	printf("\n"); 
	printf("befor starting: ILATH/ILATL     = 0x%08x    0x%08x\n", ts_ilath,ts_ilatl ); 
	printf("befor starting: IMASKH/IMASKL   = 0x%08x    0x%08x\n", ts_imaskh,ts_imaskl ); 
	printf("befor starting: PMASKH/PMASKL   = 0x%08x    0x%08x\n", ts_pmaskh,ts_pmaskl ); 
#endif


// start Tigerscharc
	data = 0x10fff0 ;

	addr = sis3150_base_addr + SIS3150_TS2_BASE +  TS_REG_VIRP ;
	if ((error = sis1100w_Vme_Single_Write(&gl_sis1100_device, addr,0x9,4,data )) != 0) { 
		sisVME_ErrorHandling (error, addr, "sis1100w_Vme_Single_Write");  return -1;
	}

	addr = sis3150_base_addr + SIS3150_TS1_BASE +  TS_REG_VIRP ;
	if ((error = sis1100w_Vme_Single_Write(&gl_sis1100_device, addr,0x9,4,data )) != 0) { 
		sisVME_ErrorHandling (error, addr, "sis1100w_Vme_Single_Write");  return -1;
	}




#ifdef debug
	sis1100w_Vme_Single_Read(&gl_sis1100_device,(sis3150_base_addr+SIS3150_TS2_BASE+TS_REG_ILATL),0x9,4,&ts_ilatl ) ;
	sis1100w_Vme_Single_Read(&gl_sis1100_device,(sis3150_base_addr+SIS3150_TS2_BASE+TS_REG_ILATH),0x9,4,&ts_ilath ) ;
	sis1100w_Vme_Single_Read(&gl_sis1100_device,(sis3150_base_addr+SIS3150_TS2_BASE+TS_REG_IMASKL),0x9,4,&ts_imaskl ) ;
	sis1100w_Vme_Single_Read(&gl_sis1100_device,(sis3150_base_addr+SIS3150_TS2_BASE+TS_REG_IMASKH),0x9,4,&ts_imaskh ) ;
	sis1100w_Vme_Single_Read(&gl_sis1100_device,(sis3150_base_addr+SIS3150_TS2_BASE+TS_REG_PMASKL),0x9,4,&ts_pmaskl ) ;
	sis1100w_Vme_Single_Read(&gl_sis1100_device,(sis3150_base_addr+SIS3150_TS2_BASE+TS_REG_PMASKH),0x9,4,&ts_pmaskh ) ;

	printf("\n"); 
	printf("after starting: ILATH/ILATL     = 0x%08x    0x%08x\n", ts_ilath,ts_ilatl ); 
	printf("after starting: IMASKH/IMASKL   = 0x%08x    0x%08x\n", ts_imaskh,ts_imaskl ); 
	printf("after starting: PMASKH/PMASKL   = 0x%08x    0x%08x\n", ts_pmaskh,ts_pmaskl ); 
#endif



 return 0 ;
}



#endif   






























