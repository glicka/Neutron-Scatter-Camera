#ifndef READSIS3302_HH
#define READSIS3302_HH

// C++ includes
#include <iostream>
#include <fstream>
#include <stdint.h>
#include <stdexcept>

// ROOT includes
#include <TFile.h>
#include <TTree.h>
#include <TSystem.h>

using namespace std;

// Marker definitions
#define SIS_BUFFER	0xABBAABBA // 1st word in the buffer header
#define SIS_TRAILER 0xDEADBEEF // Last word of the event packet
#define SIS_EOF    	0xE0F0E0F  // Instead of SIS_BUFFER after the last event

/* Parser class. Instantiate with the input/output file names, then run
	 the parsing function. */
class ReadSIS3302	{
  public:
    ReadSIS3302(string inName, string outName);
    ~ReadSIS3302();

		// Call this to run the parser
    void Parse();
  
	protected:
    // Basic file stuff
    string   inName;
    string   outName;
    ifstream datFile;

    // ROOT file stuff
    TFile   *rootFile;
    TTree   *eventTree;

    // File header stuff
    int      rawLen;
    int      trapLen;
		bool		 wrap;
		int 		 rawStart;
    
    // Event data stuff
    int      		nTotalEvents;
		int			 		channel;
		uint64_t 		timestamp;
		vector<int>	raw;
		int			 		energy;

    // Useful things
    uint32_t 		marker;
    uint32_t 		bufLen;
    uint32_t 		eventLen;
		uint32_t 	 *buf;
    bool     		done;

		// Parsing functions
		void				OpenDATFile();
		void				OpenROOTFile();
		void 				ReadFileHeader();
		void				CheckRawWrap();
		void				ReadBuffer(int nWords);
		void				ReadBufferHeader();
		void				UnpackBuffer();
		void		 		ClearEvent();
};

#endif
