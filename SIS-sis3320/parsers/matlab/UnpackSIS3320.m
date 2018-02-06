function Data = UnpackSIS3320(filename,MaxOutFileSize,RawSampleLength)

% UNPACKSIS3320
% 
% Unpacks the .dat files created by the SIS CVI program for 3320 boards and
% saves the data in one or more .mat files.
%
% UNPACKSIS3320(filename,MaxOutFileSize,RawSampleLength)
%
% 'filename' is name of the .dat file to be opened. This field is required.
% 
% 'MaxOutFileSize' is the maximum size in bytes for each output file
% (remember that 1 Mb = 1048576 b), although note that the .mat files will
% be compressed somewhat. Default is 1 Gb. Note that over 2 Gb may cause
% problems on 32-bit systems, and .mat files may not be saved.
%
% 'RawSampleLength' limits the length of the raw traces returned. Default
% is to return the entire length.
% 
% Output 'Data' contains the following fields, where N is number of counts:
%   Header (struct) - contains header information about the file
%   DetID (Nx1 uint8) - unique ID number for each channel
%   Time = (Nx1 double) - trigger time in samples (10ns) since start
%   PeakHigh = (Nx1 uint16) - max value of waveform
%   PeakIndex = (Nx1 uint16) - index of max value
%   Raw = (NxRawSampleLength uint16) - digitized pulses
%   Accum = (Nx8 uint32) - accumulator values
%   Trig = (Nx1 uint8) - number of fast triggers during this readout
%
% To save space, all values are saved in their original formats; they will
% need to be converted to doubles to do more exotic operations on them. All
% data is still in units of sampling time (10ns).
%
% The DetID field is the decimal conversion of the hex module and channel
% number, and is guaranteed to be unique and monotonically increasing, but
% not necessarily sequential, depending on the module address scheme used.
% For example, a module with address 0x40000000 will have channels from
% 0x40 to 0x47, giving DetIDs of 64 through 71.
%
% Original code written by Dan Chivers
% Last updated 2013 May 2 by Tim Aucott

if nargin < 1
    [filename,pathname] = uigetfile( ...
       {'*.dat', 'DAT Files (*.dat)';
        '*.*',  'All Files (*.*)'}, ...
        'Pick a DAT File');
    if isempty(filename)
        return
    end
    cd(pathname)
end

% make sure file exists
finfo = dir(filename);
if isempty(finfo)
    % see if user forgot to add .dat extension
    finfo = dir([filename '.dat']);
    if isempty(finfo)
        error(['File ' filename ' not found.']);
    else
        filebase = filename;
        filename = [filename '.dat'];
    end
else
    F = strfind(filename,'.dat');
    filebase = filename(1:F(1)-1);
end

% open file and pull all the header information
fh = OpenSIS3320(filename);
if fh.Err
    error(fh.ErrorMsg)
end

if nargin < 2
    MaxOutFileSize = 1048576000; % default is 1Gb
end

if nargin < 3
    RawSampleLength = fh.RawSampleLength;
end

% get file size
disp(['Parsing file: ' filename ' (' int2str(finfo.bytes/1048576) 'MB)'])
if finfo.bytes > 2*1048576000 && MaxOutFileSize > 2*1048576000
    disp('Warning: Requested file size requires 64 bit memory;')
    disp('         data may not be saved to .mat file successfully.')
end

% this is number of words per event; should be 4 byte words
datasize = 10 + round(fh.RawSampleLength/2);
N = floor(finfo.bytes*1.1 / (datasize*4));
if 704 + N*26 > MaxOutFileSize
    N = floor((MaxOutFileSize - 704) / 26);
end

tmp = ftell(fh.fid);
fseek(fh.fid,0,'eof');
filesize = ftell(fh.fid);
fseek(fh.fid,tmp,'bof');

empty.Header = fh;
empty.DetID = zeros(N,1,'uint8');
empty.Time = zeros(N,1,'double');
empty.PeakHigh = zeros(N,1,'uint16');
empty.PeakIndex = zeros(N,1,'uint16');
empty.Raw = zeros(N,RawSampleLength,'uint16');
empty.Accum = zeros(N,8,'uint32');
empty.Trig = zeros(N,1,'uint8');

Data = empty;
filectr = 0;
n = 0;

progressbar(0);

while(1)
    
    Dat = GetSingleBuffer3320(fh);
    msg = Dat.Msg;
    
    % check for end of file message
    if strcmp(msg,'EOF')
        disp('End of file reached');
        if ~isempty(Data.Time)
            if ~filectr
                fname = [filebase,'.mat'];
            else
                filectr = filectr + 1;
                fname = [filebase,'_',num2str(filectr),'.mat'];
            end
            
            Data.DetID = Data.DetID(1:n);
            Data.Time = Data.Time(1:n);
            Data.PeakHigh = Data.PeakHigh(1:n);
            Data.PeakIndex = Data.PeakIndex(1:n);
            Data.Raw = Data.Raw(1:n,:);
            Data.Accum = Data.Accum(1:n,:);
            Data.Trig = Data.Trig(1:n);
            
            disp(['Writing to file: ',fname]);
            save(fname,'Data');
        end
        break
    end
    
    % verify success message
    if ~strcmp(msg,'DON')
        error(msg)
    end
      
    % check if we went over the size limit requested
    if n + Dat.NumRec > N
        
        filectr = filectr + 1;
        fname = [filebase,'_',num2str(filectr),'.mat'];

        Data.DetID = Data.DetID(1:n);
        Data.Time = Data.Time(1:n);
        Data.PeakHigh = Data.PeakHigh(1:n);
        Data.PeakIndex = Data.PeakIndex(1:n);
        Data.Raw = Data.Raw(1:n,:);
        Data.Accum = Data.Accum(1:n,:);
        Data.Trig = Data.Trig(1:n); %#ok<STRNU>
 
        disp(['Writing to file: ',fname]);
        save(fname,'Data');
        
        Data = empty;
        n = 0;
        
    end
        
    Data.DetID(n+1:n+Dat.NumRec) = Dat.DetID;
    Data.Time(n+1:n+Dat.NumRec) = Dat.Timestamp;
    Data.PeakHigh(n+1:n+Dat.NumRec) = Dat.PeakHigh;
    Data.PeakIndex(n+1:n+Dat.NumRec) = Dat.PeakIndex;
    Data.Raw(n+1:n+Dat.NumRec,:) = Dat.RawSamples(:,1:RawSampleLength);
    Data.Accum(n+1:n+Dat.NumRec,:) = Dat.Accum;
    Data.Trig(n+1:n+Dat.NumRec) = Dat.FastTriggerCounter;

    n = n + Dat.NumRec;
    
    progressbar(ftell(fh.fid)/filesize);
    
end

fclose(fh.fid);
progressbar(1);

end


function d = OpenSIS3320(filename)

    d.Err = 0;
    d.fid = fopen(filename,'r');

    if d.fid == -1
        d.Err = 1;
        d.ErrorMsg = 'SIS 3320 .dat file could not be opened';
        return
    end

    FileHeader = fread(d.fid,32,'uint32=>uint32');

    d.FileNumber = double(FileHeader(1)); % always 1
    d.FileDataFormat = double(FileHeader(2)); % always x1
    d.NumberOf3320Modules = double(FileHeader(3));
    d.SIS3820ClockMode = double(bitshift(FileHeader(4),-16));
    d.SIS3320ClockMode = double(bitand(FileHeader(4),2^16-1));
    d.PreTriggerDelay = double(bitshift(FileHeader(5),-16));
    d.GateLength = double(bitand(FileHeader(5),2^16-1));
    d.SampleMode = double(FileHeader(6));
    d.RawSampleLength = double(bitshift(FileHeader(7),-16));
    d.RawSampleStartIndex = double(bitand(FileHeader(7),2^16-1));
    d.Acc1GateLength = double(bitshift(FileHeader(8),-16));
    d.Acc1StartIndex = double(bitand(FileHeader(8),2^16-1));
    d.Acc2GateLength = double(bitshift(FileHeader(9),-16));
    d.Acc2StartIndex = double(bitand(FileHeader(9),2^16-1));
    d.Acc3GateLength = double(bitshift(FileHeader(10),-16));
    d.Acc3StartIndex = double(bitand(FileHeader(10),2^16-1));
    d.Acc4GateLength = double(bitshift(FileHeader(11),-16));
    d.Acc4StartIndex = double(bitand(FileHeader(11),2^16-1));
    d.Acc5GateLength = double(bitshift(FileHeader(12),-16));
    d.Acc5StartIndex = double(bitand(FileHeader(12),2^16-1));
    d.Acc6GateLength = double(bitshift(FileHeader(13),-16));
    d.Acc6StartIndex = double(bitand(FileHeader(13),2^16-1));
    d.Acc7GateLength = double(bitshift(FileHeader(14),-16));
    d.Acc7StartIndex = double(bitand(FileHeader(14),2^16-1));
    d.Acc8GateLength = double(bitshift(FileHeader(15),-16));
    d.Acc8StartIndex = double(bitand(FileHeader(15),2^16-1));
    d.Trailer = double(FileHeader(16)); % always xa
    d.ModuleType = double(FileHeader(17)); % always x3320
    d.Reserved3 = double(FileHeader(18));
    d.Reserved4 = double(FileHeader(19));
    d.Reserved5 = double(FileHeader(20));
    d.Reserved6 = double(FileHeader(21));
    d.Reserved7 = double(FileHeader(22));
    d.Reserved8 = double(FileHeader(23));
    d.Reserved9 = double(FileHeader(24));
    
    if d.FileDataFormat == 5126 % x1406
        disp('Warning: This appears to be a 3302 data file, not 3320.')
    end
    
end


function Dat = GetSingleBuffer3320(fh)

cl = 10 + round(fh.RawSampleLength/2);
eh = GetEventBufferHeader(fh);

if eh.EventHeader == 235867663; % xE0F0E0F
    Dat.Msg = 'EOF';
    return
end

if eh.EventHeader == 2881137594; % xABBAABBA
    NumRec = eh.BufferChannelDataLength/cl;
elseif eh.EventHeader == 3735928559; % xDEADBEEF
    NumRec = eh.NumberOfEvents;
else
    Dat.Msg = 'Event Header Mismatch';
    return
end

Dat.NumRec = NumRec;
Dat.DetID = zeros(NumRec,1,'uint8');
Dat.Timestamp = zeros(NumRec,1,'double');
Dat.PeakHigh = zeros(NumRec,1,'uint32');
Dat.PeakIndex = zeros(NumRec,1,'uint32');
Dat.RawSamples = zeros(NumRec,fh.RawSampleLength,'uint16');
Dat.Accum = zeros(NumRec,8,'uint32');
Dat.FastTriggerCounter = zeros(NumRec,1,'uint8');

for i = 1:NumRec
    
    CD = GetNextBufferChannel3320(fh);
    
    Dat.DetID(i) = CD.Header + CD.ADCID;
    Dat.Timestamp(i) = CD.Timestamp;
    Dat.PeakHigh(i) = CD.PeakHigh;
    Dat.PeakIndex(i) = CD.PeakIndex;
    Dat.RawSamples(i,:) = CD.RawSamples;
    Dat.Accum(i,:) = CD.Accum;
    Dat.FastTriggerCounter(i) = CD.FastTriggerCounter;

end

Dat.Msg = 'DON';

end


function EHDR = GetEventBufferHeader(filehdr)

    d = fread(filehdr.fid,4,'uint32=>double');
    
    if isempty(d(1))
        EHDR.EventHeader = -1;
        return
    elseif d(1)==235867663 % xE0F0E0F
        EHDR.EventHeader = d(1);
        return
    end

    if length(d) == 1
        EHDR = -1;
        return
    end

    EHDR.EventHeader = d(1);
    EHDR.BufferNumber = d(2);
    
    if d(1)== 3735928559; % xDEADBEEF
        EHDR.NumberOfEvents = d(3);
        EHDR.EventDataLength = fread(filehdr.fid,1,'uint32=>double');
        EHDR.Reserved = d(4);
    else
        EHDR.Reserved = d(3);
        EHDR.BufferChannelDataLength = d(4);
    end

end


function CD = GetNextBufferChannel3320(f)
    
    CD.words = 0;
    
    d = fread(f.fid,2,'uint32=>uint32');
    CD.words = CD.words + 2;
    ts3 = double(bitshift(d(1),-16));
    CD.ADCID = uint8(bitand(d(1),2^8-1)); % channel #
    CD.Header = uint8(bitshift(bitand(d(1),2^16-1),-8)); % module #
    CD.Timestamp = double(d(2)) + ts3*2^32;
    
    CD.PeakHigh = fread(f.fid,1,'uint16=>uint16');    
    CD.PeakIndex = fread(f.fid,1,'uint16=>uint16');    
    CD.words = CD.words + 1;
    
    d = fread(f.fid,1,'uint32=>uint32');
    CD.FastTriggerCounter = uint8(bitand(bitshift(d(1),-24),15)); % changed 2013/5/2; should be 4 bits?
    CD.RetriggerFlag = logical(bitand(bitshift(d(1),-30),1));
    CD.PileupFlag = logical(bitand(bitshift(d(1),-31),1));
    CD.Accum(1) = bitand(d,2^21-1);
    CD.Accum(2:4) = fread(f.fid,3,'uint32=>uint32');
    CD.Accum(5:8) = fread(f.fid,4,'uint16=>uint32');
    CD.words = CD.words + 6;
    
    CD.Trailer = fread(f.fid,1,'uint32=>uint32');
    CD.words = CD.words + 1;
    
    if f.RawSampleLength > 0
        CD.RawSamples = fread(f.fid,f.RawSampleLength,'uint16=>uint16');
        if mod(f.RawSampleLength,2) ~= 0
            fread(f.fid,1,'uint16=>uint16'); % realign to 32-bit words
        end
        CD.words = CD.words + round(f.RawSampleLength/2);
    else
        CD.RawSamples = -1;
    end
    
end