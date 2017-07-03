# SIS3302toRootTree

** NOTES **
This parser was created and tested on Ubuntu 12.04 with ROOT 5.32. While it
should still work on 5.34+, there is no guarantee! GCC 4.3+ is recommended
for compiling this code. Intended for firmware 15.02, but it should work for
14.02 and 15.01.While the basic functionality, such as pulling out event energy,
channel, timestamp, and waveforms have been tested, the actual meaning
of some things (such as "Energy sample mode" in the header) are unknown and
need to be tested.

** HOW IT WORKS **
The parser loops through the SIS3302 raw data file and puts each event into
a ROOT tree, where each event trait is a separate branch. The file is read one
buffer at a time (30~1000 events, depending on raw trace length). The buffer
is then deconstructed and each event is put into the tree with the Fill() call.

See main.cc for an example binary implementing the parser class.

The SIS3302 data file holds data in 32-bit words. The file structure
is as follows:

<* FILE HEADER *>
	-> 16 words (upper 16bits / lower 16bits, if applicable)
		1. File number
		2. File format
		3. Number of modules
		4. Clock mode
		5. Raw waveform start index / number of raw waveform samples
		6. FIR gap / FIR length
		7. Energy sample mode
		8. Readout mode
		9. Trap waveform start index
		10. Trap number of samples / ?
		11. Energy gate length
		12. Trigger gate length
		13. Pre-trigger delay
		14. ?
		15. ?
		16. ?
<* EVENT BUFFER 0*>
	-> Header, 4 words
		1. Event marker
		2. ?
		3. ?
		4. Number of words in this event buffer
	<* EVENT 0 *>
		-> N Events, depending on raw trace length, wrap, etc (fixed size buffer)
		-> Format: Bits  32			  		 16								0
											| word top 16 | word lower 16 |
		-> | Timestamp3 | Channel 	 |
			 | Timestamp2 | Timestamp1 |
			 If the data wrap is on
			 -> word 1. | 						?						  |
			 -> word 2. | Raw waveform start index |
			 otherwise
			 | Raw waveform sample 1&2 |
			 | Raw waveform sample 3&4 |
			 |           ...           |
			 | Trap waveform sample 1	 |
			 | Trap waveform sample 2	 |
			 |           ...           |
			 |			 Event flags			 |
			 |			 Event marker      |
	<* EVENT 1 *>
		-> ...
<* EVENT BUFFER 1*>
	-> ...
		|			 Event marker      |
<* END OF FILE MARKER *>

The last event in the file has 0xDEADBEEF as its event marker, followed by 0xE0F0E0F0 where the next header buffer would be. A check is done during the buffer header read to determine if the end of file has been reached.
		
** HOW TO USE **
Compile using the Makefile and run the example binary, SIS3302ToROOT, on
a raw data file or create your own binary using the parsing class,
ReadSIS3302. An example script to plot the energy histogram is provided
in the scripts folder for C++. The Makefile is made to be independent of
the ROOT installation location and uses root-config to find it to include
the libraries.
