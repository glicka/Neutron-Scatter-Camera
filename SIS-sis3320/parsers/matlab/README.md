#MATLAB SIS Parsers
---

Here are parsers for the SIS 3302 (100MHz), 3320 (250MHz) and 3350 (500MHz) modules. The Matlab scripts are self contained except for the ProgressBar function which gives a visual progress bar while parsing. They write the raw data waveforms and associated event information to the matlab storage format (*.mat) files in chunks depending on the memory usage (in `bytes`) you pass to these functions. In Matlab you can find the max memory availible by typing `memory` into the command line.