function Data = UnpackSIS3302(filename,MaxOutFileSize,RawSampleLength,EnergySampleLength)

% UNPACKSIS3302
% 
% Unpacks the .dat files created by the SIS CVI program for 3302 boards and
% saves the data in one or more .mat files. Tested with firmwares 1405
% through 1511, including wrap mode.
%
% UNPACKSIS3302(filename,MaxOutFileSize,RawSampleLength,EnergySampleLength)
%
% 'filename' is name of the .dat file to be opened.
% 
% 'MaxOutFileSize' is the maximum size in bytes for each output file
% (remember that 1 Mb = 1048576 b), although note that the .mat files will
% be compressed somewhat. Default is 1 Gb. Note that over 2 Gb may cause
% problems on 32-bit systems, and .mat files may not be saved.
%
% 'RawSampleLength' limits the length of the raw traces returned. Default
% is to return the entire length.
%
% 'EnergySampleLength' limits the length of the energy filter values
% returned. Filter values may be none, full trapezoid, or three regions.
% Default is to return the entire length.
% 
% Output contains the following fields, where N is number of counts:
%   Header (struct) - contains header information about the file
%   DetID (Nx1 uint8) - unique ID number for each channel
%   Time = (Nx1 double) - trigger time in samples (10ns) since start
%   Energy = (Nx1 double) - max value of trapezoidal filter
%   Raw = (NxRawSampleLength uint16) - digitized pulses
%   Filter = (NxEnergySampleLength int32) - trapezoidal filter values
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
fh = OpenSISDataFile(filename);
if fh.Err
    error(fh.ErrorMsg)
end

if nargin < 2
    MaxOutFileSize = 1048576000; % default is 1Gb
end

if nargin < 3
    RawSampleLength = fh.RawSampleLength;
end

if nargin < 4
    EnergySampleLength = fh.EnergySampleLength;
end

% get file size
disp(['Parsing file: ' filename ' (' int2str(finfo.bytes/1048576) 'MB)'])
if finfo.bytes > 2*1048576000 && MaxOutFileSize > 2*1048576000
    disp('Warning! Requested file size requires 64 bit memory;')
    disp('         data may not be saved to .mat file successfully.')
end

% this is number of words per event; should be 4 byte words
datasize = 2 + round(fh.RawSampleLength/2) + fh.EnergySampleLength + 4;
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
empty.Energy = zeros(N,1,'double');
empty.Raw = zeros(N,RawSampleLength,'uint16');
empty.Filter = zeros(N,EnergySampleLength,'int32');
empty.Trig = zeros(N,1,'uint8');

Data = empty;
filectr = 0;
n = 0;

progressbar(0);

while(1)
    
    Dat = GetSingleBufferReadData(fh);
    msg = Dat.Msg;
    
    % check for end of file message
    if strcmp(msg,'EOF')
        disp('End of file reached');
        if ~isempty(Data.Energy)
            if ~filectr
                fname = [filebase,'.mat'];
            else
                filectr = filectr + 1;
                fname = [filebase,'_',num2str(filectr),'.mat'];
            end
            
            Data.DetID = Data.DetID(1:n);
            Data.Time = Data.Time(1:n);
            Data.Energy = Data.Energy(1:n);
            Data.Raw = Data.Raw(1:n,:);
            Data.Filter = Data.Filter(1:n,:);
            Data.Trig = Data.Trig(1:n);
            
            disp(['Writing to file: ',fname]);
            save(fname,'Data');
        end
        break
    end
      
    % check if we went over the size limit requested
    if n + Dat.NumRec > N
        
        filectr = filectr + 1;
        fname = [filebase,'_',num2str(filectr),'.mat'];

        Data.DetID = Data.DetID(1:n);
        Data.Time = Data.Time(1:n);
        Data.Energy = Data.Energy(1:n);
        Data.Raw = Data.Raw(1:n,:);
        Data.Filter = Data.Filter(1:n,:);
        Data.Trig = Data.Trig(1:n); %#ok<STRNU>
 
        disp(['Writing to file: ',fname]);
        save(fname,'Data');
        
        Data = empty;
        n = 0;
        
    end
    
    % verify success message
    if strcmp(msg,'DON')
        
        Data.DetID(n+1:n+Dat.NumRec) = Dat.DetID;
        Data.Time(n+1:n+Dat.NumRec) = Dat.Timestamp;
        Data.Energy(n+1:n+Dat.NumRec) = Dat.Energy;
        Data.Raw(n+1:n+Dat.NumRec,:) = Dat.RawSamples(:,1:RawSampleLength);
        Data.Filter(n+1:n+Dat.NumRec,:) = Dat.FilterData(:,1:EnergySampleLength);
        Data.Trig(n+1:n+Dat.NumRec) = Dat.FastTriggerCounter;
     
        n = n + Dat.NumRec;
        
    else
        error(msg);
    end
    
    progressbar(ftell(fh.fid)/filesize);
    
end

fclose(fh.fid);
progressbar(1);

end


function d = OpenSISDataFile(filename)

    d.Err = 0;
    d.fid = fopen(filename,'r');

    if d.fid == -1
        d.Err = 1;
        d.ErrorMsg = 'SIS3302 .dat file could not be opened';
        return
    end

    FileHeader = fread(d.fid,16,'uint32=>uint32');

    d.FileNumber = double(FileHeader(1)); % always 1
    d.FileDataFormat = double(FileHeader(2)); % always reads x1406...
    d.NumberOf3302Modules = double(FileHeader(3));
    d.SIS3820ClockMode = double(bitshift(FileHeader(4),-16));
    d.SIS3302ClockMode = double(bitand(FileHeader(4),2^16-1));
    d.RawSampleStartIndex = double(bitshift(FileHeader(5),-16));
    d.RawSampleLength = double(bitand(FileHeader(5),2^16-1));
    d.DecimationMode = double(bitshift(FileHeader(6),-28));
    d.EnergyGap = double(bitand(bitshift(FileHeader(6),-12),2^12-1));
    d.EnergyPeaking = double(bitand(FileHeader(6),2^12-1));
    d.EnergySampleMode = double(FileHeader(7));
    d.ReadoutMode = double(FileHeader(8));
    d.EnergySampleStartIndex2 = double(bitshift(FileHeader(9),-16));
    d.EnergySampleStartIndex1 = double(bitand(FileHeader(9),2^16-1));
    d.EnergySampleLength = double(bitshift(FileHeader(10),-16));
    d.EnergySampleStartIndex3 = double(bitand(FileHeader(10),2^16-1));
    d.EnergyGateLength = double(FileHeader(11));
    d.TriggerGateLength = double(FileHeader(12));
    d.PreTriggerDelay = double(FileHeader(13));
    d.Reserved_1 = double(FileHeader(14));
    d.Reserved_2 = double(FileHeader(15));
    d.Reserved_3 = double(FileHeader(16));
    
    if d.Reserved_3 == 10 % xA
        disp('Warning: This appears to be a 3320 data file, not 3302.')
    end
    
end


function Dat = GetSingleBufferReadData(fh)

cl = 2 + round(fh.RawSampleLength/2) + fh.EnergySampleLength + 4;
eh = GetEventBufferHeader(fh);

if eh.EventHeader == 235867663; % xE0F0E0F
    Dat.Msg = 'EOF';
    return
end

if eh.EventHeader ~= 2881137594; % xABBAABBA
    Dat.Msg = 'Event Header Mismatch';
    return
end

NumRec = eh.BufferChannelDataLength/cl;

if mod(NumRec,1) ~= 0 % should be integer number of records
    NumRec = eh.BufferChannelDataLength/(cl + 2); % if not, try wrap mode
    if mod(NumRec,1) ~= 0
        Dat.Msg = 'Event Header Data Length Error';
        return
    else
        WrapMode = true;
    end
else
    WrapMode = false;
end

Dat.NumRec = NumRec;
Dat.DetID = zeros(NumRec,1,'uint8');
Dat.Timestamp = zeros(NumRec,1,'double');
Dat.Energy = zeros(NumRec,1,'double');
Dat.RawSamples = zeros(NumRec,fh.RawSampleLength,'uint16');
Dat.FilterData = zeros(NumRec,fh.EnergySampleLength,'int32');
Dat.FastTriggerCounter = zeros(NumRec,1,'uint8');

for i = 1:NumRec
    
    CD = GetNextBufferChannelData(fh,WrapMode);
    
    Dat.DetID(i) = CD.Header + CD.ADCID;
    Dat.Timestamp(i) = CD.Timestamp;
    Dat.Energy(i) = CD.EnergyMaxValue - CD.FirstEnergyValue;
    Dat.RawSamples(i,:) = CD.RawSamples;
    Dat.FilterData(i,:) = CD.EnergyData;
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
    EHDR.Reserved = d(3);
    EHDR.BufferChannelDataLength = d(4);

end


function CD = GetNextBufferChannelData(f,WrapFlag)
    
    CD.words = 0;
    
    d = fread(f.fid,2,'uint32=>uint32');
    CD.words = CD.words + 2;
    ts3 = double(bitshift(d(1),-16));
    CD.ADCID = uint8(bitand(d(1),2^8-1)); % channel #
    CD.Header = uint8(bitshift(bitand(d(1),2^16-1),-8)); % module #
    CD.Timestamp = double(d(2)) + ts3*2^32;
    
    if f.RawSampleLength > 0
        if nargin > 1 && WrapFlag % wrap mode
            CD.WrapDataLength = fread(f.fid,1,'uint32=>uint32');
            CD.WrapStartIndex = fread(f.fid,1,'uint32=>uint32');
            CD.words = CD.words + 2;
            WrapBuffer = fread(f.fid,CD.WrapDataLength,'uint16=>uint16');
            CD.RawSamples = [WrapBuffer(CD.WrapStartIndex+1:end);
                             WrapBuffer(1:CD.WrapStartIndex)];
            CD.words = CD.words + CD.WrapDataLength;
        else % no wrap mode
            CD.RawSamples = fread(f.fid,f.RawSampleLength,'uint16=>uint16');
            if mod(f.RawSampleLength,2) ~= 0
                fread(f.fid,1,'uint16=>uint16'); % realign to 32-bit words
            end
            CD.words = CD.words + round(f.RawSampleLength/2);
        end
    else
        CD.RawSamples = -1;
    end
    
    if f.EnergySampleLength > 0
        CD.EnergyData = fread(f.fid,f.EnergySampleLength,'int32=>int32');
        CD.words = CD.words + f.EnergySampleLength;
    else
        CD.EnergyData = -1;
    end
    
    CD.EnergyMaxValue = fread(f.fid,1,'int32=>double');    
    CD.FirstEnergyValue = fread(f.fid,1,'int32=>double');    
    CD.words = CD.words + 2;
    
    d = fread(f.fid,1,'uint32=>uint32');
    CD.FastTriggerCounter = uint8(bitand(bitshift(d,-24),15)); % changed 2013/5/2; should be 4 bits?
    CD.RetriggerFlag = logical(bitand(bitshift(d,-30),1));
    CD.PileupFlag = logical(bitand(bitshift(d,-31),1));
    CD.Trailer = fread(f.fid,1,'uint32=>uint32');
    CD.words = CD.words + 2;
    
end