int WriteParseBuffer (unsigned int* memory_data_array, unsigned int nof_write_length_lwords,struct SISdata **data, unsigned int *len)
{
    long long timestamp;
    int energy;
//    int maxEnergy;
//    int firstEnergy;
	int peakHigh;
	int argHigh;
    unsigned short *raw_data_ptr ;
    unsigned int Cl = 6 + floor(gl_uint_RawSampleLength/2 + 0.5) + gl_uint_DataEvent_RunFile_NOF_Energy;
    unsigned int NumRec = nof_write_length_lwords/Cl;
    //qint64 * qTS = new qint64[NumRec];
    //SISdata *unpackeddata = new SISdata[NumRec];
    int oldlen = *len;
    *len += NumRec;
	printf("entering malloc\n");
    if (oldlen == 0) {
        *data = malloc(NumRec*sizeof(struct SISdata));
    }
    else {
        *data = realloc(*data,(*len)*sizeof(struct SISdata));
    }
    //printf("%d events\n",NumRec);
	printf("leaving malloc\n");
    unsigned int cntr = 0;

//    printf( "gl_uint_RawSampleLength = %d\n", gl_uint_RawSampleLength );
    for(unsigned int i = 0; i <NumRec; i++){
        unsigned int ADCID = memory_data_array[cntr] & 65535;
        unsigned int Mod = ADCID >> 11;//
        unsigned int ID = (((Mod-1) << 3) + (ADCID & 7) ) -56 ;

        timestamp = ((long long)(memory_data_array[cntr] & 0xffff0000) << 16) + (long long)memory_data_array[cntr+1];


        cntr = cntr + 2;
		if (cntr == 0){
		peakHigh = (memory_data_array[cntr] & 0xffff0000) << 11;
		argHigh = (memory_data_array[cntr] & 0xffff0000) << 20
		}
        if (gl_uint_RawSampleLength != 0)
        {
            raw_data_ptr = (unsigned short*) &(memory_data_array[cntr]);	//Changed to "&" - RWB
//            for (int k=0;k<gl_uint_RawSampleLength;k++){
//                //data[i].rawdata[k] = raw_data_ptr[k];
//            }
         }

        cntr = cntr + gl_uint_RawSampleLength/2 + gl_uint_DataEvent_RunFile_NOF_Energy;
//        maxEnergy = memory_data_array[cntr++];
//        firstEnergy = memory_data_array[cntr++];
        int trigger = (memory_data_array[cntr] >> 24 ) & 7;	//RWB
        int nneighborm1 = (memory_data_array[cntr] >> 28) & 1;
        int nneighborp1 = (memory_data_array[cntr]>> 29) & 1;
        int pileup = (memory_data_array[cntr] >> 30) & 1 ;
        //unsigned int trailer = memory_data_array[cntr+1]; this reads the trailer which should be 3735928559 in decimal
//        energy = maxEnergy - firstEnergy;
        energy = maxEnergy;					//RWB
        cntr += 2;
        //printf("energy: %u adcid: %u \n",energy,ID);
        int n = i +oldlen;
        (*data)[n].adcid = ID;
//        (*data)[n].energy = energy;
        (*data)[n].timestamp = timestamp;
        (*data)[n].trigger = trigger;				//RWB
        (*data)[n].neighborminus = nneighborm1;
        (*data)[n].neighborplus = nneighborp1;
        (*data)[n].pileup = pileup;
        // Raw Data  - RWB
        int k;
        for( k=0; k < gl_uint_RawSampleLength; k++ )
        {
          (*data)[n].rawdata[k] = raw_data_ptr[k];
        }
    }
    return 0;
}

