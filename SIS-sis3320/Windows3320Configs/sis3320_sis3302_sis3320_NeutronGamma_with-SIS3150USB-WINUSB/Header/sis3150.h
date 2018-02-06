/***************************************************************************/
/*                                                                         */
/*  Filename: sis3150.h                                                    */
/*                                                                         */
/*  Funktion: headerfile for SIS3150                                       */
/*                                                                         */
/*  Autor:                TH                                               */
/*  date:                 20.01.2004                                       */
/*  last modification:    21.01.2004                                       */
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
/*  © 2004                                                                 */
/*                                                                         */
/***************************************************************************/


/* bits */
#define LEMO2_CMC2_VETO_BIT     			0x8000000 	  	 
#define LEMO2_CMC1_VETO_BIT     			0x4000000 	  	 
#define LEMO2_TS1_FLAG2_BIT     			0x40000 	  	 
#define LEMO2_TS1_FLAG1_BIT     			0x20000 	  	 

#define LEMO1_CMC2_TRIGGER_BIT     			0x200 	  	 
#define LEMO1_CMC1_TRIGGER_BIT     			0x100 	  	 
#define LEMO1_TS1_FLAG2_BIT     			0x4  	  	 
#define LEMO1_TS1_FLAG1_BIT     			0x2 	  	 

/* general registers */
#define SIS3150_CONTROL_STATUS     			0x0	  	/* read/write; D32 */
#define SIS3150_MODID           			0x4		/* read only;  D32 */
#define SIS3150_IRQ_CONFIG  				0x8 	/* read/write; D32 */
#define SIS3150_IRQ_CONTROL     			0xC 	/* read/write; D32 */
#define SIS3150_LEMO_OUT_SELECT_REG			0x10	 

/* key addresses */
#define SIS3150_KEY_RESET  					0x0400 
#define SIS3150_KEY_CMC_RESET 				0x0404 
#define SIS3150_KEY_CMC1_RESET 				0x0408 
#define SIS3150_KEY_CMC2_RESET 				0x040C 
#define SIS3150_KEY_TS_RESET  				0x0410 

/* CMC Offset Addresses  */
#define SIS3150_CMC1_BASE          			0x01000000 
#define SIS3150_CMC2_BASE          			0x01800000 

/* TS Offset Addresses  */
#define SIS3150_TS1_BASE          			0x02000000 
#define SIS3150_TS2_BASE        			0x03000000 

/* SDRAM Offset Addresses  */
#define SIS3150_SDRAM_BASE          		0x04000000 




/* DSP TigerSharc internal Memory Spaces */
#define TS_MEMORY_BLOCK0       				0x0 
#define TS_MEMORY_BLOCK1       				0x80000*4 
#define TS_MEMORY_BLOCK2       				0x100000*4 



/* DSP TigerSharc internal Registers */
#define TS_REG_ILATL   						0x018034A*4 
#define TS_REG_ILATH 	  					0x018034B*4   /* !! */

#define TS_REG_IMASKL   					0x018034C*4 
#define TS_REG_IMASKH   					0x018034D*4 
#define TS_REG_PMASKL   					0x018034E*4 
#define TS_REG_PMASKH   					0x018034F*4 

#define TS_REG_ILATCLL   					0x018035E*4 
#define TS_REG_ILATCLH   					0x018035F*4   /* !! */
/* #define TS_REG_ILATCLH   				0x018034F*4   */

#define TS_REG_SQCTL	   					0x0180358*4   /* !! */
#define TS_REG_SQCTLST   					0x0180359*4   /* !! */
#define TS_REG_SQCTLCL   					0x018035A*4   /* !! */


#define TS_REG_SYSCON   					0x0180480*4 
#define TS_REG_SDRCON   					0x0180484*4 
#define TS_REG_VIRP     					0x0180730*4 

#define TS_REG_DMA_DC8     					0x0180440*4    
#define TS_REG_DMA_DC9	   					0x0180444*4    
#define TS_REG_DMA_DC10	   					0x0180448*4    
#define TS_REG_DMA_DC11	   					0x018044C*4    

#define TS_REG_LCTL0     					0x01804E0*4    
#define TS_REG_LCTL1     					0x01804E4*4    
#define TS_REG_LCTL2     					0x01804E8*4    
#define TS_REG_LCTL3     					0x01804EC*4    




/* bits */
#define CTRL_USER_LED_OFF  					0x10000	   /* default after Reset */
#define CTRL_USER_LED_ON     				0x1



