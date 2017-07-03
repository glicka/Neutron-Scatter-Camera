#include "parserthread.h"
#include "loadCalibration.h"

#include <cstdio>
#include <iostream>
#include <sstream>
#include <cmath>

//#include "TFile.h"
//#include "TTree.h"

#include "H5Cpp.h"

#ifndef H5_NO_NAMESPACE
     using namespace H5;
#endif

parserthread::parserthread(QObject *parent) :
    QThread(parent)
{
}


void parserthread::parse(){
    start(HighPriority);

}

void parserthread::run(){


    char messages_buffer[256] ;
    int nof_read;
    int rd3302 = this->rd3302;
    unsigned int gl_dma_rd_buffer[0x10000] ; //This needs to be large enough to hold the largest raw data block
    unsigned int  i, ievent  ;
    unsigned int  reserved    ;
    unsigned int  reserved1,reserved2,reserved3;
    unsigned int uint_offline_file_event_header ;
    unsigned int uint_offline_file_event_number ;
    unsigned int uint_offline_file_channel_size ;
    unsigned int channel_event_length, raw_data_length, energy_data_length, events_in_buffer ;
    unsigned int ptr_index ;
    unsigned short *raw_data_ptr ;
    const unsigned int TRIGGERBIT = pow(2, 24);
    const unsigned int PILEBIT = pow(2,30);
    const unsigned int RETRIGBIT = pow(2,31);
    //unsigned  int szip_options_mask;
    //unsigned  int szip_pixels_per_block;

    //LOAD CALIBRATION TABLE
    double mAry[NUM_ROWS*NUM_COLS];
    double bAry[NUM_ROWS*NUM_COLS];
    if( this->calMode ) { loadData1D( mAry, bAry, calFileName.toStdString() ); }

    FILE * gl_FILE_OfflineDataEvenFilePointer;

    // open data file
            gl_FILE_OfflineDataEvenFilePointer=fopen(filename.toLatin1(),"rb");// filename to be opened

            if(gl_FILE_OfflineDataEvenFilePointer == NULL) {
            sprintf (messages_buffer, "Data File Open Error \n");
                    //return -1 ;
             }
            fseek(gl_FILE_OfflineDataEvenFilePointer,0,SEEK_END);
            unsigned long long filesize = ftell(gl_FILE_OfflineDataEvenFilePointer);
            fseek(gl_FILE_OfflineDataEvenFilePointer,0,SEEK_SET);

    // ************
    // FILE HEADER
    // ************

    unsigned int gl_uint_OfflineFileNumber;
    unsigned int gl_uint_OfflineDataFormat;
    unsigned int gl_uint_OfflineNofModules;
    unsigned int gl_uint_OfflineSamplingParamters;
    unsigned int gl_uint_OfflineRawDataParameters;
    unsigned int gl_uint_OfflineEnergyParameters;
    unsigned int gl_uint_OfflineEnergyModeLength;
    unsigned int gl_uint_OfflineReadoutMode;
    unsigned int gl_uint_OfflineReadoutModeRawDataBufferControlWrapMode;
    unsigned int gl_uint_OfflineEnergyModeLengthAddr3;
    unsigned int gl_uint_OfflineEnergyGateLength;
    unsigned int gl_uint_OfflineTriggerGateLength;
    unsigned int gl_uint_OfflinePreTriggerDelay;


    // read 16 32-bit words
    nof_read=fread(&gl_uint_OfflineFileNumber,0x4,0x1,gl_FILE_OfflineDataEvenFilePointer);
    nof_read=nof_read+fread(&gl_uint_OfflineDataFormat,0x4,0x1,gl_FILE_OfflineDataEvenFilePointer);// 1 for 3320, 0x1406 for 3302
    nof_read=nof_read+fread(&gl_uint_OfflineNofModules,0x4,0x1,gl_FILE_OfflineDataEvenFilePointer);
    nof_read=nof_read+fread(&gl_uint_OfflineSamplingParamters,0x4,0x1,gl_FILE_OfflineDataEvenFilePointer);
    //unsigned int temp;
    //nof_read=fread(&temp,16,1,gl_FILE_OfflineDataEvenFilePointer);

    nof_read=nof_read+fread(&gl_uint_OfflineRawDataParameters,0x4,0x1,gl_FILE_OfflineDataEvenFilePointer);//need

    nof_read=nof_read+fread(&gl_uint_OfflineEnergyParameters,0x4,0x1,gl_FILE_OfflineDataEvenFilePointer);
    nof_read=nof_read+fread(&gl_uint_OfflineEnergyModeLength,0x4,0x1,gl_FILE_OfflineDataEvenFilePointer);
    nof_read=nof_read+fread(&gl_uint_OfflineReadoutMode,0x4,0x1,gl_FILE_OfflineDataEvenFilePointer);
    nof_read=nof_read+fread(&gl_uint_OfflineReadoutModeRawDataBufferControlWrapMode,0x4,0x1,gl_FILE_OfflineDataEvenFilePointer);// 1 for 1511 wrap mode, 0 otherwise
    //nof_read=nof_read+fread(&temp,16,1,gl_FILE_OfflineDataEvenFilePointer);

    nof_read=nof_read+fread(&gl_uint_OfflineEnergyModeLengthAddr3,0x4,0x1,gl_FILE_OfflineDataEvenFilePointer);//need

    nof_read=nof_read+fread(&gl_uint_OfflineEnergyGateLength,0x4,0x1,gl_FILE_OfflineDataEvenFilePointer);
    nof_read=nof_read+fread(&gl_uint_OfflineTriggerGateLength,0x4,0x1,gl_FILE_OfflineDataEvenFilePointer);

    nof_read=nof_read+fread(&gl_uint_OfflinePreTriggerDelay,0x4,0x1,gl_FILE_OfflineDataEvenFilePointer);
    nof_read=nof_read+fread(&reserved1,0x4,0x1,gl_FILE_OfflineDataEvenFilePointer);
    nof_read=nof_read+fread(&reserved2,0x4,0x1,gl_FILE_OfflineDataEvenFilePointer);
    nof_read=nof_read+fread(&reserved3,0x4,0x1,gl_FILE_OfflineDataEvenFilePointer);
    //nof_read=nof_read+fread(&temp,24,1,gl_FILE_OfflineDataEvenFilePointer);


    if(nof_read!=16) {
            fclose(gl_FILE_OfflineDataEvenFilePointer);//
            return;
    }

    unsigned int rdl2 = 0;
    if (gl_uint_OfflineDataFormat ==1){
        //rd3302 = 0;
    }
    if (rd3302 > 0){
        raw_data_length      =   (gl_uint_OfflineRawDataParameters & 0xfffe);
        rdl2 = (gl_uint_OfflineRawDataParameters >>16 & 0xfffe);//this corresponds to the wrap pretrigger delay but isn't needed
    }
    else
    {
        raw_data_length      =   1;//(gl_uint_OfflineRawDataParameters & 0xfffe); this appears to mean nothing for 3320 data
    }
    energy_data_length   =   (gl_uint_OfflineEnergyModeLengthAddr3 >> 16) & 0x0fff  ;
    channel_event_length =   2   // Timestamp
                           + (raw_data_length / 2)    //  16-bit values but need lword length
                                               + energy_data_length
                           + 4 ; // max. , min. Energy, Flags, Trailor

    std::stringstream sstm;
    sstm << raw_data_length;
    //std::cout << sstm << std::endl;

    //Check for consistency in run mode
    if( (this->noRawMode==false) && (raw_data_length == 0) )
    {
        std::cerr << "Warning: No raw data detected in file. Try running with the 'Events Only' option checked" << std::endl;
        std::exit(0);
    }

    unsigned int nevents = 0;
    filename.chop(4);
    filename.append(".h5");
    //int lastind = filename.lastIndexOf("/");
    //filename.remove(0,lastind+1);
    //this->ui->statusBar->showMessage(tr( filename.toAscii()));

    int bad = 0;
    int wrapdata;
    int j = 0;

    // initializing HDF5 stuff *****************************************************************************
    const H5std_string FILE_NAME(filename.toStdString());
    //unsigned  int szip_options_mask=H5_SZIP_NN_OPTION_MASK;
    //unsigned  int szip_pixels_per_block=32;
    const int CHUNKSIZE = 256;
    //unsigned int eventsperbuffer = 1;
    // Raw Data dataspace
    const H5std_string DATASET_NAME( "RawData" );
    const int RANK = 2;

    if(this->noRawMode){ raw_data_length = 1; }

    hsize_t rawdims[2] = {1,raw_data_length};
    hsize_t rawtdims[2];
    rawtdims[0] = rawdims[0];
    rawtdims[1] = rawdims[1];
    hsize_t rawmaxdims[2] = {H5S_UNLIMITED, H5S_UNLIMITED};
    //rawdims[0] = eventsperbuffer;
    DataSpace rawdataspace(RANK, rawdims, rawmaxdims);

    DSetCreatPropList rawcreateparameters;
    hsize_t rchunkdims[2] = {CHUNKSIZE * 2, raw_data_length};
    //rchunkdims[0] = 10;//10
    //rchunkdims[1] = rawdims[1];
    rawcreateparameters.setChunk(RANK, rchunkdims);
    int fill_val = 0;
    rawcreateparameters.setFillValue(PredType::NATIVE_INT,&fill_val);
    rawcreateparameters.setShuffle();
    rawcreateparameters.setDeflate(1);
    //rawcreateparameters.setSzip(szip_options_mask,szip_pixels_per_block);

    // Energy, timestamp, channel
    const H5std_string DATASET2_NAME( "EventData" );
    const H5std_string MEMBER1( "timestamp" );
    const H5std_string MEMBER2( "ADC_value" );
    const H5std_string MEMBER3( "detector" );
    const H5std_string MEMBER4( "trigger" );
    const H5std_string MEMBER5( "pileup" );
    const H5std_string MEMBER6( "retrigger" );
    const H5std_string MEMBER7("rid");
    struct edt_t {
        unsigned long long timestamp;
        float ADC;
        unsigned short detector;
        unsigned short trigger;
        unsigned short pileup;
        unsigned short retrigger;
        unsigned int rid;

    };
    edt_t hdf5event[1];
    edt_t hdf5filler;
    hsize_t eventdims[] = {1};
    hsize_t eventtdims[] = {1};
    hsize_t echunkdims[] = {CHUNKSIZE};
    hsize_t eventmaxdims[] = {H5S_UNLIMITED};
    DataSpace eventdataspace(1, eventdims, eventmaxdims);
    CompType eventtype(sizeof(edt_t));
    eventtype.insertMember(MEMBER1,HOFFSET(edt_t, timestamp),PredType::NATIVE_ULLONG);
    eventtype.insertMember(MEMBER2,HOFFSET(edt_t, ADC),PredType::NATIVE_FLOAT);
    eventtype.insertMember(MEMBER3,HOFFSET(edt_t, detector),PredType::NATIVE_USHORT);
    eventtype.insertMember(MEMBER4,HOFFSET(edt_t, trigger),PredType::NATIVE_USHORT);
    eventtype.insertMember(MEMBER5,HOFFSET(edt_t, pileup),PredType::NATIVE_USHORT);
    eventtype.insertMember(MEMBER6,HOFFSET(edt_t, retrigger),PredType::NATIVE_USHORT);
    eventtype.insertMember(MEMBER7,HOFFSET(edt_t, rid), PredType::NATIVE_UINT);

    DSetCreatPropList eventcreateparameters;
    eventcreateparameters.setChunk(1, echunkdims);

    hdf5filler.timestamp = 0;
    hdf5filler.ADC = 0;
    hdf5filler.detector = 0;
    hdf5filler.trigger = 0;
    hdf5filler.pileup = 0;
    hdf5filler.retrigger = 0;
    hdf5filler.rid = 0;
    eventcreateparameters.setFillValue(eventtype,&hdf5filler);

    //eventcreateparameters.setSzip(szip_options_mask,1);
    eventcreateparameters.setShuffle();
    eventcreateparameters.setDeflate(1);
    H5File file( FILE_NAME, H5F_ACC_TRUNC );

    DataSet rawdataset = file.createDataSet( DATASET_NAME, PredType::NATIVE_INT, rawdataspace, rawcreateparameters);
    DataSet eventdataset = file.createDataSet(DATASET2_NAME,eventtype,eventdataspace,eventcreateparameters);

    // ***************************************************************************************************

    // Initializing ROOT stuff****************************************************************************
    /*
    TFile* fRootFout = new TFile("test.root","RECREATE","My SIS data") ;
    TTree* fRootTree = new TTree ("tree","My SIS events") ;
    struct event_t{
            Long64_t timestamp;
            ULong64_t adc_val;
            ULong64_t det_id;
            UShort_t raw[30000];

    };

    event_t event;

    fRootTree->Branch("events",&event,"timestamp/L:adc_val/l:det_id:raw[30000]/s") ;

    // ***************************************************************************************************
    */
            if (rd3302){}
            else{
                nof_read=fread(&reserved1,0x4,1,gl_FILE_OfflineDataEvenFilePointer);
            }


                 //nof_event_buffer_loops = 0 ;
            do {  // loop over events

                    // ************
                    // EVENT HEADER
                    // ************
                    // read event header ....


                    nof_read=fread(&uint_offline_file_event_header,0x4,1,gl_FILE_OfflineDataEvenFilePointer);
                    nof_read=nof_read+fread(&uint_offline_file_event_number,0x4,1,gl_FILE_OfflineDataEvenFilePointer);
                    nof_read=nof_read+fread(&reserved,0x4,1,gl_FILE_OfflineDataEvenFilePointer);
                    nof_read=nof_read+fread(&uint_offline_file_channel_size,0x4,1,gl_FILE_OfflineDataEvenFilePointer);

                    //fprintf(used_txt_file,"\n\n");
                    if(nof_read!=4 | uint_offline_file_event_header == 235867663) {
                            // Write out ROOT tree
                            /*
                            fRootFout->cd();
                            fRootTree->Print();
                            fRootTree->Write();
                            fRootFout->Close();
                            */
                            fclose(gl_FILE_OfflineDataEvenFilePointer);
                            emit finished();
                            /*
                            mutex.lock();
                            if (!restart)
                                condition.wait(&mutex);
                            restart = false;
                            mutex.unlock();
                            break;
                            */
                            return;
                    }

                    events_in_buffer  =    uint_offline_file_channel_size /   channel_event_length ;
                    unsigned int buffer_size = reserved;//uint_offline_file_channel_size;
                    //fprintf(used_txt_file,"info: events in buffer = %d   \n",events_in_buffer);
                    if(rd3302 > 0){
                        //int wrapdata = gl_uint_OfflineReadoutModeRawDataBufferControlWrapMode;
                        if (rd3302 == 2){
                            wrapdata = 1;
                        }else{
                            wrapdata = 0;
                        }
                        unsigned short *hdf5rawdata = new unsigned short[raw_data_length];
                        for (ievent=0;ievent<events_in_buffer;ievent++)  {
                                // read event
                                nof_read=fread(gl_dma_rd_buffer,0x4,channel_event_length+wrapdata*2,gl_FILE_OfflineDataEvenFilePointer);
                                // timestamp

                                if(wrapdata){
                                    //unsigned int rawdlength = gl_dma_rd_buffer[2] & 0xffff;
                                    unsigned int rawstartindex = gl_dma_rd_buffer[3] & 0xffff;
                                    j = rawstartindex;
                                    ptr_index=4;
                                }else{
                                    ptr_index=2;
                                }
                                // raw data
                                if ( (raw_data_length != 0)  && (!this->noRawMode) )
                                {
                                        raw_data_ptr = (unsigned short*) &(gl_dma_rd_buffer[ptr_index]);
                                        for (i=0;i<raw_data_length;i++){


                                            if(wrapdata){
                                                hdf5rawdata[i] = raw_data_ptr[j];
                                                //event.raw[i] = raw_data_ptr[j]; // ROOT raw data
                                                j++;
                                                if(j >= raw_data_length){j=0;}
                                            }else{
                                                hdf5rawdata[i] = raw_data_ptr[i];
                                                //event.raw[i] = raw_data_ptr[i]; //ROOT raw data
                                            }

                                        }
                                        rawdataset.extend(rawtdims);
                                        DataSpace rawdataspace_temp = rawdataset.getSpace ();
                                        hsize_t     offset[2];
                                        offset[0] = nevents;
                                        offset[1] = 0;
                                        rawdataspace_temp.selectHyperslab( H5S_SELECT_SET, rawdims, offset );
                                        rawdataset.write( hdf5rawdata, PredType::NATIVE_USHORT, rawdataspace, rawdataspace_temp);

                                        //fprintf(used_txt_file,"\n");
                                        ptr_index=ptr_index+(raw_data_length/2);
                                }

                                //energy data
                                if (energy_data_length != 0) {
                                        /*
                                        for (i=0;i<energy_data_length;i++){
                                                if ((i&0x7) == 0) {
                                                }
                                        }
                                        */
                                        ptr_index=ptr_index+energy_data_length;
                                }
                                hsize_t eventoffset[1];
                                eventoffset[0] = nevents;

                                eventdataset.extend(eventtdims);
                                DataSpace eventdataspace_temp = eventdataset.getSpace();
                                eventdataspace_temp.selectHyperslab(H5S_SELECT_SET,eventdims, eventoffset);
                                hdf5event[0].timestamp = ((qint64)(gl_dma_rd_buffer[0] & 0xffff0000) << 16) + (qint64)gl_dma_rd_buffer[1];

                                // convert the channel number from the raw 14 bit number to an ADC channel number with channel 0 corresponding to adc 1 on a board set to 40.
                                unsigned int ADCID = gl_dma_rd_buffer[0] & 65535;
                                unsigned int Mod = ADCID >> 11;//12
                                unsigned int Ch = (ADCID & 7); // 0 to 7
                                //unsigned int ID = ((Mod-1) << 3);
                                unsigned int ID = ((Mod-1) << 3);    //ORIGINAL
                                ID = ID + Ch - 56;

                                hdf5event[0].detector = ID;//(gl_dma_rd_buffer[0]&0xffff);
                                //MAYBE TRY NOT SUBTRACTING MIN VALUE!!!!!!!!!
                                //hdf5event[0].ADC =  gl_dma_rd_buffer[ptr_index] - gl_dma_rd_buffer[ptr_index+1];        //Original
                                //hdf5event[0].ADC =  gl_dma_rd_buffer[ptr_index]; //UNCALIBRATED
                                if( this->calMode )
                                {
                                    hdf5event[0].ADC = bAry[ID] + gl_dma_rd_buffer[ptr_index] * mAry[ID];
                                }
                                else{ hdf5event[0].ADC = gl_dma_rd_buffer[ptr_index]; }
                                //NEW: Get the trigger, pileup, and retrigger flags
                                unsigned int bitline = gl_dma_rd_buffer[ptr_index+2];
                                hdf5event[0].trigger = (bitline/TRIGGERBIT) & 7;
                                hdf5event[0].pileup = (bitline/PILEBIT) & 1;
                                hdf5event[0].retrigger = (bitline/RETRIGBIT) & 1;
                                hdf5event[0].rid = nevents;
                                //unsigned int checksum = gl_dma_rd_buffer[ptr_index+3];

                                eventdataset.write(hdf5event,eventtype,eventdataspace,eventdataspace_temp);

                                //eventn++;
                                eventtdims[0]++;
                                rawtdims[0]++;
                                nevents ++;

                                // Fill ROOT tree
                                //event.timestamp = ((qint64)(gl_dma_rd_buffer[0] & 0xffff0000) << 16) + (qint64)gl_dma_rd_buffer[1];
                                //event.adc_val = gl_dma_rd_buffer[ptr_index] - gl_dma_rd_buffer[ptr_index+1];
                                //event.det = ID;
                                //fRootTree->Fill();

                                emit completion((double)(ftell(gl_FILE_OfflineDataEvenFilePointer)/(double)filesize)) ;
                        }

                        delete [] hdf5rawdata;




                    }
                    else{

                        while(buffer_size > 0)  {
                                // read event
                                nof_read=fread(gl_dma_rd_buffer,0x4,10,gl_FILE_OfflineDataEvenFilePointer);
                                // convert the channel number from the raw 14 bit number to an ADC channel number with channel 0 corresponding to adc 1 on a board set to 40.
                                hsize_t eventoffset[1];
                                eventoffset[0] = nevents;

                                eventdataset.extend(eventtdims);
                                DataSpace eventdataspace_temp = eventdataset.getSpace();
                                eventdataspace_temp.selectHyperslab(H5S_SELECT_SET,eventdims, eventoffset);
                                hdf5event[0].timestamp = ((qint64)(gl_dma_rd_buffer[0] & 0xffff0000) << 16) + (qint64)gl_dma_rd_buffer[1];

                                // convert the channel number from the raw 14 bit number to an ADC channel number with channel 0 corresponding to adc 1 on a board set to 40.
                                unsigned int ADCID = gl_dma_rd_buffer[0] & 65535;
                                unsigned int Mod = ADCID >> 11;//12
                                unsigned int Ch = (ADCID & 7); // 0 to 7
                                unsigned int ID = ((Mod-1) << 3);
                                ID = ID + Ch;

                                hdf5event[0].detector = ID;//(gl_dma_rd_buffer[0]&0xffff);
                                hdf5event[0].ADC =  0;//gl_dma_rd_buffer[ptr_index] - gl_dma_rd_buffer[ptr_index+1];
                                //unsigned int checksum = gl_dma_rd_buffer[ptr_index+3];
                                eventdataset.write(hdf5event,eventtype,eventdataspace,eventdataspace_temp);

                                int raw_data_length2 = (gl_dma_rd_buffer[9]) & 0xffff;
                                unsigned int trailer = (gl_dma_rd_buffer[9]>> 16) & 0xffff;
                                ptr_index = 0;
                                //int sample[1000];
                                unsigned short *hdf5rawdata = new unsigned short[raw_data_length2];

                                if (raw_data_length2 != 0 && trailer == 56026) {
                                        nof_read=fread(gl_dma_rd_buffer,0x4,raw_data_length2/2,gl_FILE_OfflineDataEvenFilePointer);
                                        raw_data_ptr = (unsigned short*) &(gl_dma_rd_buffer[ptr_index]);
                                        for (i=0;i<raw_data_length2;i++){
                                                if ((i&0x7) == 0) {
                                                        //fprintf(used_txt_file,"\n i = %4d    ",i);
                                                }
                                                if (i < 1000){
                                                  //  sample[i] = raw_data_ptr[i];
                                                }
                                                else{
                                                    bad = 1;
                                                }
                                                //event.raw[i] = raw_data_ptr[i];
                                                hdf5rawdata[i] = raw_data_ptr[i]; // Fill HDF5 raw data array

                                                //fprintf(used_txt_file," %4x ",raw_data_ptr[i]);
                                        }
                                        if (rawtdims[1] < raw_data_length2){
                                            rawtdims[1] = raw_data_length2;
                                        }
                                        rawdataset.extend(rawtdims);
                                        DataSpace rawdataspace_temp = rawdataset.getSpace ();
                                        rawdims[1] = raw_data_length2;
                                        DataSpace rawdataspace_temp2(RANK,rawdims);
                                        hsize_t     offset[2];
                                        offset[0] = nevents;
                                        offset[1] = 0;
                                        rawdataspace_temp.selectHyperslab( H5S_SELECT_SET, rawdims, offset );
                                        rawdataset.write( hdf5rawdata, PredType::NATIVE_USHORT, rawdataspace_temp2, rawdataspace_temp);

                                        //fprintf(used_txt_file,"\n");
                                        //ptr_index=ptr_index+(raw_data_length/2);
                                }
                                else{
                                    bad = 1;
                                }


                                //this->ui->progressBar->setValue((int)((double)ftell(gl_FILE_OfflineDataEvenFilePointer)/(double)filesize*100.0));
                                emit completion((double)(ftell(gl_FILE_OfflineDataEvenFilePointer)/(double)filesize)) ;


                                delete [] hdf5rawdata;

                                eventtdims[0]++;
                                rawtdims[0]++;
                                nevents ++;
                                //buffer_size = buffer_size - 10 - raw_data_length/2;
                                buffer_size--;
                        }
                    }

            } while (1) ; //

//}

}
