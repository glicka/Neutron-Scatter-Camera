/***************************************************************************/
/*                                                                         */
/*  Filename: pc_TS_communication_address_map.h                            */
/*                                                                         */
/*  Funktion: SIS3150_9300 Gamma                                           */
/*                                                                         */
/*  Autor:                TH                                               */
/*  date:                 28.07.2005                                       */
/*  last modification:    03.02.2005                                       */
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





/* Communication Commands and Replies */
#define VME_TO_TS_CMD1			0x1111

#define MB_CLEAR				0x0000

#define MB_TS_STARTED_REPLY		0xAAAA0001 



#define CMD__OPMS_ANALYSER_VME_INIT		0x5555aaaa
#define MB_OPMS_ANALYSER_START_CMD		0x1100

#define MB_OPMS_ANALYSER_INIT_OK		0x8100
#define MB_OPMS_ANALYSER_START_OK		0x0
#define MB_OPMS_ANALYSER_INIT_OK		0x8100


/* *********************  Gloabal Simulation definition  ****************************/
/* TS1: 0x4000 to 0xffff */


#define TS_COMMUNICATION_VARIABLE 		0x4000		


//#define TS_COMMUNICATION_VARIABLE 		0x4000		/* USB TS-BUS offset 0x02004000; VME Slave offset 0x02010000	*/
#define	TS_SOFTWARE_VERSION				0x4001		/* Software Version 	*/


#define TS_ALIVE_COUNTER				0x4002		/* USB TS-BUS offset 0x02004002; VME Slave offset 0x02010008	*/
#define TS_ERROR_COUNTER				0x4003		/* 	*/







#define TS_PARAMETER_uint_RawPreSampleLength		0x4100		/* 	*/
#define TS_PARAMETER_uint_RawSampleLength			0x4101		/* 	*/
#define TS_PARAMETER_uint_EnergySampleMode			0x4102		/* 	*/

#define TS_PARAMETER_uint_FirEnergyGap				0x4110		/* 	*/
#define TS_PARAMETER_uint_FirEnergyLength			0x4111		/* 	*/
#define TS_PARAMETER_uint_FirDecimationMode			0x4112		/* 	*/


#define TS_PARAMETER_uint_TriggerWindowActiveLength	0x4120		/* 	*/



#define TS_PARAMETER_float_EnergyFactorConf			0x4180		/* Array of 8 used / reserved for 16	*/
#define TS_PARAMETER_float_ExpDecayTimeConf			0x4190		/* Array of 8 used / reserved for 16	*/ 







#ifdef raus
  // Common Sample and Energy Parameters
unsigned int  gl_uint_FirEnergyGap     ;
unsigned int  gl_uint_FirEnergyLength     ;
unsigned int  gl_uint_FirDecimationMode     ;

unsigned int  gl_uint_RawPreSampleLength     ;
unsigned int  gl_uint_RawSampleLength     ;
unsigned int  gl_uint_EnergySampleMode     ;
unsigned int  gl_uint_TriggerWindowActiveLength     ;


// Energy Factor
float  gl_float_EnergyFactorConf[MAX_NO_OF_MODULES][ NO_OF_ADC_CHANNELS]    ;

// Decay Factor
float  gl_float_ExpDecayTimeConf[MAX_NO_OF_MODULES][ NO_OF_ADC_CHANNELS]    ;

#endif
/* increment with each Superframe */
#define	SUPERFRAME_COUNTER_A					0x02010000			/* TS 0x4000	*/ 	


#define	DOUBLE_BUFFER_CONTROL_A					0x02010044			/* TS 0x4011	*/ 	 		
#define	TS2_FFT_CONTROL_A						0x02010048			/* TS 0x4012	*/ 	 		









/**********************  Director Top Simulation defination CMC1 ***************** */
/* TS1: 0x84000 to 0x8ffff */

#define	BUF_DIRTOP_DIR2DEU_ADDR_OUT_A			0x02210000			/* 1024 ;  TS 0x84000	*/ 	
#define	BUF_DIRTOP_DIR2DEU_DISCERTE_OUT_A		0x02214000			/* 2048 ;  TS 0x85000   */ 	






/**********************  Director Top Simulation defination CMC2 ***************** */
/* TS1: 0x104000 to 0x10ffff */


#define	BUF_DIRTOP_DIR2DEU_ADDR_OUT_B			((0x104000*4)+0x2000000)			/* 1024 ;  VME 0xS2410000	*/ 	
#define	BUF_DIRTOP_DIR2DEU_DISCERTE_OUT_B		((0x105000*4)+0x2000000)			/* 2048 ;  VME 0xS2414000	*/ 	
#define	BUF_DIRTOP_DIR2DEU_HIGHSPEED_OUT_B		((0x105800*4)+0x2000000)			/* 2048 ;  VME 0xS2416000	*/ 	
/* word 0 ; word 1 .. */


#define	BUF_DIRTOP_DIR2DEU_AUDIO_0_OUT_B		((0x106000*4)+0x2000000)			/* 1024 ;  VME 0xS2418000	*/ 	





/**********************  DEU Top Simulation defination CMC1 ***************** */

/* TS1: 0xA000 to 0xffff */

#define	BUF_DEUTOP_DEU2DIR_IDENT_IN_A			((0xA000*4)+0x2000000)	/* 1024 ;  VME 0xS2028000	*/ 	
#define	BUF_DEUTOP_DEU2DIR_DISCRETE_IN_A		((0xA400*4)+0x2000000)	/* 1024 ;  VME 0xS2029000	*/ 	

/* 8 words for each Frame ; 8 x 1024 */
#define	BUF_DEUTOP_DEU2DIR_HIGHSPEED_IN_A		((0xA800*4)+0x2000000)	/* VME 0xS202A000	*/ 	


#define	BUF_DEUTOP_DEU2DIR_IDENT_IN_B			((0xD000*4)+0x2000000)	/* 1024 ;  VME 0xS2034000	*/ 	
#define	BUF_DEUTOP_DEU2DIR_DISCRETE_IN_B		((0xD400*4)+0x2000000)	/* 1024 ;  VME 0xS2036000	*/ 	
																	
/* 8 words for each Frame ; 8 x 1024 */
#define	BUF_DEUTOP_DEU2DIR_HIGHSPEED_IN_B		((0xD800*4)+0x2000000)	/* VME 0xS2036000	*/ 	



/* TS1: 0x84000 to 0x8ffff */
/* hier werden die  von VME NICHT "staendig" gebrauchten Daten verwaltet */
#define	BUF1_DEUTOP_DIR2DEU_ADDR_IN_A			((0x84000*4)+0x2000000)				/* 1024 ;  VME 0xS2210000	*/ 	

#define	BUF1_DEUTOP_DIR2DEU_AUDIO_0_IN_A		((0x84400*4)+0x2000000)				/* 1024 ;  VME 0xS2211000	*/ 	
#define	BUF1_DEUTOP_DIR2DEU_AUDIO_1_IN_A		((0x84800*4)+0x2000000)				/* 1024 ;  VME 0xS2212000	*/ 	
#define	BUF1_DEUTOP_DIR2DEU_AUDIO_2_IN_A		((0x84C00*4)+0x2000000)				/* 1024 ;  VME 0xS2213000	*/ 	
#define	BUF1_DEUTOP_DIR2DEU_AUDIO_3_IN_A		((0x85000*4)+0x2000000)				/* 1024 ;  VME 0xS2214000	*/ 	
#define	BUF1_DEUTOP_DIR2DEU_AUDIO_4_IN_A		((0x85400*4)+0x2000000)				/* 1024 ;  VME 0xS2215000	*/ 	
#define	BUF1_DEUTOP_DIR2DEU_AUDIO_5_IN_A		((0x85800*4)+0x2000000)				/* 1024 ;  VME 0xS2216000	*/ 	
#define	BUF1_DEUTOP_DIR2DEU_AUDIO_6_IN_A		((0x85C00*4)+0x2000000)				/* 1024 ;  VME 0xS2217000	*/ 	
#define	BUF1_DEUTOP_DIR2DEU_AUDIO_7_IN_A		((0x86000*4)+0x2000000)				/* 1024 ;  VME 0xS2218000	*/ 	
#define	BUF1_DEUTOP_DIR2DEU_AUDIO_8_IN_A		((0x86400*4)+0x2000000)				/* 1024 ;  VME 0xS2219000	*/ 	
#define	BUF1_DEUTOP_DIR2DEU_AUDIO_9_IN_A		((0x86800*4)+0x2000000)				/* 1024 ;  VME 0xS221A000	*/ 	


#define	BUF1_DEUTOP_DIR2DEU_ADDR_IN_B			((0x87000*4)+0x2000000)				/* 1024 ;  VME 0xS221C000	*/ 	

#define	BUF1_DEUTOP_DIR2DEU_AUDIO_0_IN_B		((0x87400*4)+0x2000000)				/* 1024 ;  VME 0xS221D000	*/ 	
#define	BUF1_DEUTOP_DIR2DEU_AUDIO_1_IN_B		((0x87800*4)+0x2000000)				/* 1024 ;  VME 0xS221E000	*/ 	
#define	BUF1_DEUTOP_DIR2DEU_AUDIO_2_IN_B		((0x87C00*4)+0x2000000)				/* 1024 ;  VME 0xS221F000	*/ 	
#define	BUF1_DEUTOP_DIR2DEU_AUDIO_3_IN_B		((0x88000*4)+0x2000000)				/* 1024 ;  VME 0xS2220000	*/ 	
#define	BUF1_DEUTOP_DIR2DEU_AUDIO_4_IN_B		((0x88400*4)+0x2000000)				/* 1024 ;  VME 0xS2221000	*/ 	
#define	BUF1_DEUTOP_DIR2DEU_AUDIO_5_IN_B		((0x88800*4)+0x2000000)				/* 1024 ;  VME 0xS2222000	*/ 	
#define	BUF1_DEUTOP_DIR2DEU_AUDIO_6_IN_B		((0x88C00*4)+0x2000000)				/* 1024 ;  VME 0xS2223000	*/ 	
#define	BUF1_DEUTOP_DIR2DEU_AUDIO_7_IN_B		((0x89000*4)+0x2000000)				/* 1024 ;  VME 0xS2224000	*/ 	
#define	BUF1_DEUTOP_DIR2DEU_AUDIO_8_IN_B		((0x89400*4)+0x2000000)				/* 1024 ;  VME 0xS2225000	*/ 	
#define	BUF1_DEUTOP_DIR2DEU_AUDIO_9_IN_B		((0x89800*4)+0x2000000)				/* 1024 ;  VME 0xS2226000	*/ 	

#define	BUFFER2_OFFSET_DEUTOP		((0x6000*4))			/* VME 0x18000	*/ 	





/* TS1: 0x104000 to 0x10ffff */
/* hier werden die "staendig" vom VME zuschreibenden/zulesenden Daten verwaltet */
#define	BUF1_DEUTOP_DIR2DEU_DISCERTE_IN_A		((0x104000*4)+0x2000000)			/* 1024 (2048x16bit) ;  VME 0xS2410000	*/ 	
#define	BUF1_DEUTOP_DIR2DEU_HIGHSPEED_IN_A		((0x104400*4)+0x2000000)			/* 1024 (2048x16bit) ;  VME 0xS2411000	*/ 	

#define	BUF1_DEUTOP_DIR2DEU_DISCERTE_IN_B		((0x104800*4)+0x2000000)			/* 1024 (2048x16bit) ;  VME 0xS2412000	*/ 	
#define	BUF1_DEUTOP_DIR2DEU_HIGHSPEED_IN_B		((0x104C00*4)+0x2000000)			/* 1024 (2048x16bit) ;  VME 0xS2413000	*/ 	

#define	BUF1_DEUTOP_DIR2DEU_AUDIO_FFT_A			((0x105000*4)+0x2000000)			/* 512 reserviert ;     VME 0xS2414000	*/ 	
#define	BUF1_DEUTOP_DIR2DEU_AUDIO_FFT_B			((0x105200*4)+0x2000000)			/* 512 reserviert ;     VME 0xS2414800	*/ 	



/* offset von 0x6000 fuer Buffer2 */
/*#define	BUF2_DEUTOP_DIR2DEU_DISCERTE_IN_A		0x10A000				 1024 (2048x16bit) ;  VME 0xS2428000	*/ 	
/*#define	BUF2_DEUTOP_DIR2DEU_HIGHSPEED_IN_A		0x10A400				 1024 (2048x16bit) ;  VME 0xS2429000	*/ 	

/*#define	BUF2_DEUTOP_DIR2DEU_DISCERTE_IN_B		0x10A800				 1024 (2048x16bit) ;  VME 0xS242A000	*/ 	
/*#define	BUF2_DEUTOP_DIR2DEU_HIGHSPEED_IN_B		0x10AC00				 1024 (2048x16bit) ;  VME 0xS242B000	*/ 	

/*#define	BUF2_DEUTOP_DIR2DEU_AUDIO_FFT_A			0x10B000				 512 reserviert ;     VME 0xS242C000	*/ 	
/*#define	BUF2_DEUTOP_DIR2DEU_AUDIO_FFT_B			0x10B200				 512 reserviert ;     VME 0xS242C800	*/ 	



/* write buffers */




#define	BUF1_DEUTOP_DEU2DIR_IDENT_OUT_A			((0x106000*4)+0x2000000)	/* 1024 ;  VME 0xS2418000	*/ 	
#define	BUF1_DEUTOP_DEU2DIR_IDENT_OUT_B			((0x106400*4)+0x2000000)	/* 1024 ;  VME 0xS2419000	*/ 	

#define	BUF1_DEUTOP_DEU2DIR_DISCRETE_OUT_A		((0x106800*4)+0x2000000)	/* 1024 ;  VME 0xS241A000	*/ 	
#define	BUF1_DEUTOP_DEU2DIR_HIGHSPEED_OUT_A		((0x106C00*4)+0x2000000)	/* to 0x107bff	; 4096 (8 x 1024 x16bit)VME 0xS241C000	*/ 	

#define	BUF1_DEUTOP_DEU2DIR_DISCRETE_OUT_B		((0x107C00*4)+0x2000000)	/* 1024 ;  VME 0xS241F000	*/ 	
#define	BUF1_DEUTOP_DEU2DIR_HIGHSPEED_OUT_B		((0x108000*4)+0x2000000)	/*  to 0x108fff	; 4096 (8 x 1024 x16bit)VME 0xS2420000	*/ 	


/* offset von 0x6000 fuer Buffer2 */
/*#define	BUF2_DEUTOP_DEU2DIR_IDENT_OUT_A			0x10C000				 1024 ;  VME 0xS2230000	*/ 	
/*#define	BUF2_DEUTOP_DEU2DIR_IDENT_OUT_B			0x10C400				 1024 ;  VME 0xS2230000	*/ 	

/*#define	BUF2_DEUTOP_DEU2DIR_DISCRETE_OUT_A		0x10C800				 1024 ;  VME 0xS2232000	*/ 	
/*#define	BUF2_DEUTOP_DEU2DIR_HIGHSPEED_OUT_A		0x10CC00	 to 0x10Dfff	; 5120 (10 x 1024 x16bit)VME 0xS2234000	*/ 	

/*#define	BUF2_DEUTOP_DEU2DIR_DISCRETE_OUT_B		0x10E000				 1024 ;  VME 0xS2232000	*/ 	
/*#define	BUF2_DEUTOP_DEU2DIR_HIGHSPEED_OUT_B		0x10E400	 to 0x10f7ff	; 5120 (10 x 1024 x16bit)VME 0xS2234000	*/ 	




