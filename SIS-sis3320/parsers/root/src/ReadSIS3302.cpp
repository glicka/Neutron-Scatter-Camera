#include "ReadSIS3302.hpp"

ReadSIS3302::ReadSIS3302(string inName, string outName):
		inName(inName), outName(outName), rootFile(nullptr), eventTree(nullptr),
		rawLen(0), trapLen(0), wrap(false), rawStart(0), nTotalEvents(0),
		marker(0), bufLen(0), eventLen(0), buf(nullptr), done(false) {
	ClearEvent();
}

ReadSIS3302::~ReadSIS3302() {
	if (rootFile != nullptr) {
		rootFile->Close();
	}
	if (datFile.good()) {
		datFile.close();
	}
	delete[] buf;
}

/* Open the input data file and read the header */
void ReadSIS3302::OpenDATFile() {
	// Try opening the input file - throw an exception if we're unable
	datFile.open(inName.c_str(), ios::binary);
	if (!datFile.good()) {
		throw runtime_error("OpenDATFile(): Unable to open input DAT file.");
	}
	// Allocate for the input buffer: 0xFFFFFF @ 32 bits  = 134 MB
	buf = new uint32_t[0xFFFFFF];
	cout << "Input DAT file opened." << endl;
	ReadFileHeader();
	return;
}

void ReadSIS3302::OpenROOTFile() {
	// ROOT doesn't throw good/any exceptions on TFile failure so we have to
	// check manually. AccessPathName returns true if it cannot access the file
	// nice one ROOT
	rootFile = new TFile(outName.c_str(), "RECREATE");
	if (gSystem->AccessPathName(outName.c_str())) {
		throw runtime_error("OpenROOTFile(): Unable to access path after TFile creation.");
	}
	eventTree = new TTree("SISEvents", "SISEvents");
	eventTree->Branch("channel", &channel);
	// Specify 64 bit unsigned integer to ROOT with /l
	eventTree->Branch("timestamp", &timestamp, "timestamp/l");
	eventTree->Branch("raw", &raw);
	eventTree->Branch("energy", &energy);
	cout << "Output ROOT file opened." << endl;
	return;
}

void ReadSIS3302::ReadFileHeader() {
	// File header is 16 words
	ReadBuffer(16);
	// Number of samples in the raw trace
	rawLen = (int)(buf[4] & 0xFFFF);
	// Start index (only useful for wrap? and maybe not even)
	rawStart = (int)(buf[4] >> 16);
	// Number of samples in the energy (trapezoidal) trace, usually 510
	trapLen = (int)(buf[9] >> 16);

	// Channel+Timestamp, Raw Trace, Trap Trace, and Event Flags
	eventLen = 2 + rawLen/2 + trapLen + 4;

	// Check for raw data wrap - determine the length of the first event
	CheckRawWrap();
	return;
}

/* Checks for the raw trace wrap by looking for the event trailer at
	 the end of the first event. It should be 2 words later if the wrap is on */
void ReadSIS3302::CheckRawWrap() {
	cout << "Checking for raw trace wrap...";
	// Read the first event assuming no wrap and 2 extra
	ReadBufferHeader();
	ReadBuffer(eventLen + 2);
	// Wrap is off
	if (buf[eventLen-1] == SIS_TRAILER) {
		cout << "not detected." << endl;
	} else if (buf[eventLen + 1] == SIS_TRAILER) {
		cout << "wrap detected." << endl;
		wrap = true;
		eventLen += 2;
	} else {
		throw runtime_error("CheckRawWrap(): SIS_TRAILER not found.");
	}
	// Go back to the end of the file header
	datFile.seekg(64, datFile.beg);
	return;
}

void ReadSIS3302::ReadBuffer(int nWords) {
	if (!datFile.good()) {
		throw runtime_error("ReadBuffer(): DAT file not good during buffer read.");
	}
	datFile.read((char*)buf, 4*nWords);
	return;
}

void ReadSIS3302::ReadBufferHeader() {
	ReadBuffer(4);
	if (buf[0] == SIS_EOF) {
		done = true;
		return;
	} else if (buf[0] != SIS_BUFFER) {
		throw runtime_error("ReadBufferHeader(): Buffer marker not equal to 0xABBAABBA");
	}

	// Set the number of words in this buffer
	bufLen = buf[3];
	return;
}

void ReadSIS3302::UnpackBuffer() {
	int nEvents = bufLen/eventLen;
	
	int offset = 0;
	// Loop over the events in the buffer
	for (int i=0;i < nEvents;i++) {
		// Get a pointer to the start of this event packet in the buffer
		offset = i*eventLen;
		ClearEvent();

		// Channel - first 16 bits of the first word in event packet
		channel = (int)(((buf[offset + 0] & 0xFFFF) % 8) + 1);
		// Timestamp - 48 bits, top 16 from first word and all of the second
		timestamp = buf[offset + 0] >> 16;
		timestamp += buf[offset + 1];
		// Raw waveform - each sample is 16 bits so each words holds 2 samples
		vector<int> wrapTrace;
		// If wrap is on, the trace is split into two, with the end first and the
		// beginning second. The word before the raw samples tells where the true
		// beginning of the waveform is
		if (wrap) { rawStart = buf[offset + 3]; }
		for (int k=0;k < rawLen;k += 2) {
			if (wrap && (k < rawStart)) {
				wrapTrace.push_back((int)(buf[offset + 4 + k/2] >> 16));
				wrapTrace.push_back((int)((buf[offset + 4 + k/2] & 0xFFFF0000) >> 16));
			} else if (wrap) {
				raw.push_back((int)(buf[offset + 4 + k/2] >> 16));
				raw.push_back((int)((buf[offset + 4 + k/2] & 0xFFFF0000) >> 16));
			} else { // No wrap
				raw.push_back((int)(buf[offset + 2 + k/2] >> 16));
				raw.push_back((int)((buf[offset + 2 + k/2] & 0xFFFF0000) >> 16));
			}
		}
		// Append the wrap trace
		if (wrap) {
			raw.insert(raw.end(), wrapTrace.begin(), wrapTrace.end());
		}
		// Trapezoidal waveform - usually 510 words, 32 bits each sample
		for (int k=0;k < trapLen;k++) {
			// Just a placeholder, this loop gets optimized out if it does nothing
		}
		// Energy max - energy first, two consecutive words after the trap trace
		int eStart = offset + 2 + rawLen/2 + trapLen + (wrap ? 2 : 0);
		energy = (int)buf[eStart];
		// Confirm the event trailer is correct
		if (buf[offset + (eventLen-1)] != SIS_TRAILER) {
			throw runtime_error("UnpackBuffer(): SIS_TRAILER not found at end of event.");
		}
		// Add the event to the ROOT tree
		eventTree->Fill();
		nTotalEvents++;
		if (nTotalEvents % 1000 == 0) {
			cout << "Parsing event " << nTotalEvents << endl;
			//cout << "Channel: " << channel << endl;
			//cout << "Timestamp: " << timestamp << endl;
			//cout << "Raw0: " << raw.at(0) << endl;
			//cout << "Energy: " << energy << endl;
		}
	}
	return;
}

void ReadSIS3302::ClearEvent() {
	channel = 0;
	timestamp = 0;
	raw.clear();
	energy = 0;
	return;
}

void ReadSIS3302::Parse() {
	// Let's do this
	OpenDATFile();
	OpenROOTFile();
	while (true) {
		ReadBufferHeader();
		if (done) {
			break;
		}
		ReadBuffer(bufLen);
		UnpackBuffer();
	}
	cout << "Finished parsing. " << nTotalEvents << " events read into " <<
		outName << "." << endl;
	return;
}
