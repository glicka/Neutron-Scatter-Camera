function sname = UnpackSIS3350(filename,singleADCflag,maxmemory)
%function sname = UnpackSIS3350(filename,singleADCflag,maxmemory)
%
%Unpacks the .dat files from SIS 3350 ADCs
%
%filename:      name of the *.dat file from the 3350 data.
%singleADCflag: true means the 2nd, 3rd, 4th ADCs will be thrown out.
%               use this if you only have one detector EventData.channel plugged in.
%maxmemory:     maximum data size, in bytes. should be less than
%               Matlab's available memory (which is usually set to something 
%               much less than your computer's RAM...)
%               The output data will be split into files based on this data
%               size; however the mat files are compressed by about 7x.
%
% Brian Plimley, Sep 22, 2011

% 'l', 'b', or NaN for unspecified.
endianness = NaN;

%open file, get length
if isnan(endianness)
    fid = fopen(filename,'r');
else
    fid = fopen(filename,'r',endianness);
end

%error check
if fid == -1
    error(['Error opening ',filename]);
end

fseek(fid,0,'eof');
fend = ftell(fid);  %location of end of file

fseek(fid,0,'bof'); %but start at beginning of file


%Data format:
% (CRLF = carriage return + line feed)
% (double quotes are not characters in the file)
%
% "New ADC-Buffer ", CRLF
% "ADC #", CRLF where # is 0,1,2,3
% "header", 
%   then header data is listed in ASCII as 32-bit hex values: "0x00430b76", etc.
%   then CRLF
% then more data is listed in ASCII as 16-bit hex values: "0x0f74" CRLF, etc.

%% Parsing.

%set start parameters
cur_ADC = NaN;
bad_file_flag = false;
EventData.signal_length = nan;    %to be discovered on first event
EventData.signal_element_byte_length = nan;
%format output filenames
file_prefix = [filename(1:strfind(filename,'.dat')-1),'_'];
file_suffix = '.mat';
zerostr = '000';

%index of buffer number (not actually important)
n_buffer = 0;
%output file number
n_file = 1;
%event number
n_event = 0;

%dead characters per line of EventData.signal values
skip_char = 5;  %hard coded = 5: %space, CR, LF, '0x'

progressbar(0);

while true
    %get one line
    cur = fgetl(fid);
    
    %parse
    if isnumeric(cur) && cur==-1
        %end of file; we're done
        break
    elseif length(cur)>13 && strcmp(cur(1:14),'New ADC-Buffer')
        %new ADC buffer
        n_buffer = n_buffer + 1;    %...just for the record
    elseif length(cur)>4 && strcmp(cur(1:4),'ADC ')
        %new ADC
        cur_ADC = str2double(cur(5:end));
    elseif length(cur)>6 && strcmp(cur(1:7),'header ')
        %do i care about this event?
        if ~singleADCflag || cur_ADC==0
            %yes, I care
            
            %new event
            n_event = n_event + 1;
            
            %now parse header line
            header_string = cur(7:end);     %include space b/c of next line
            f_0x = strfind(header_string,' 0x');
            f_0x(end+1) = length(header_string)+1;
            for i=1:length(f_0x)-1
                header_value(i) = hex2dec(header_string(f_0x(i)+3:f_0x(i+1)-1));
            end
        end
        
        %now grab EventData.signal data following header.
        %do we know how much data there will be?
        if isnan(EventData.signal_length)
            %no, let's find out.
            curpos = ftell(fid);    %keep track of where we left off here.
            lastpos = curpos;
            curtemp = fgetl(fid);   %look at next line..
            n_line_count = 0;
            while ~strcmp(curtemp(1:6),'header')
                n_line_count = n_line_count + 1;
                linelen = ftell(fid) - lastpos; %line length in bytes
                lastpos = ftell(fid);
                curtemp = fgetl(fid);
            end
            EventData.signal_length = n_line_count;
            EventData.signal_element_byte_length = linelen - skip_char; 
            
            %allocate variables
            %check how much is remaining in the file
            %... don't care how much is remaining in the file
%             estimated_data_length = ...
%                 ceil(min(fend-ftell(fid),maxmemory)./(EventData.signal_length*linelen+length(cur));
            %number of events per output file
            nof_events_per_output_file = ...
                ceil(maxmemory / (8*(EventData.signal_length+3)));
            %  three misc variables (EventData.channel, EventData.timestamp, EventData.event_info) plus EventData.signal
            %  all are doubles, which take 8 bytes per value
            
%             allocate_length = min(estimated_data_length, nof_events_per_output_file);
            allocate_length = nof_events_per_output_file;
            
            EventData.channel = zeros(1,allocate_length);
            EventData.timestamp = zeros(1,allocate_length);
            EventData.event_info = zeros(1,allocate_length);
            EventData.signal = zeros(allocate_length,EventData.signal_length);
            
            %back to where we were
            fseek(fid,curpos,'bof');
        end
        
        %check if variables are 'full' and need to be saved to file
        if n_event > length(EventData.channel)
            %generate filename
            savename = [pwd '/' file_prefix,zerostr(1:end-floor(log10(n_file))),num2str(n_file),file_suffix];
            disp(['Saving file ',savename,' . . .'])
            %save
            save(savename,'EventData')
            %update counters
            n_file = n_file + 1;
            n_event = 1;
            
            %allocate variables again
            EventData.channel = zeros(1,allocate_length);
            EventData.timestamp = zeros(1,allocate_length);
            EventData.event_info = zeros(1,allocate_length);
            EventData.signal = zeros(allocate_length,EventData.signal_length);
        end
            
        
        %check for bad file
        event_length = mod(header_value(3),2^16)*2^24 + header_value(4);
        if EventData.signal_length < event_length
            bad_file_flag = true;
            break
        end
        
        if ~singleADCflag || cur_ADC==0     %if we care
            %write header to variables
            EventData.channel(n_event) = cur_ADC;
            EventData.timestamp(n_event) = header_value(1)*2^24 + header_value(2);
            EventData.event_info(n_event) = floor(header_value(3)./2^16);
            
            %skip two characters for 0x
            fseek(fid,2,'cof');
            %read hex info
            sig_char = fread(fid,EventData.signal_length*EventData.signal_element_byte_length,...
                [num2str(EventData.signal_element_byte_length),'*char=>char'],skip_char);
            %put each hex value on one line. must read in the transpose.
            sig_char = reshape(sig_char,EventData.signal_element_byte_length,EventData.signal_length)';
            %convert to decimal
            EventData.signal(n_event,:) = hex2dec(sig_char)';
            
            %tidy up file position: 
            % fread already skipped skip_char characters, which is too many.
            % but we do need to skip space, CR, LF
            fseek(fid,3-skip_char,'cof');
        else
            %don't care, just skip over it
            fseek(fid,EventData.signal_length*(EventData.signal_element_byte_length + skip_char),'cof');
        end
        
        progressbar(ftell(fid)/fend);
    end
    
end

%save file
%generate filename
% if n_file==1
%     %no need to add zeros; also, drop the underscore from the filename
%     savename = [pwd '/' file_prefix(1:end-1),file_suffix];
% else
%     %add zeros
%     savename = [pwd '/' file_prefix,zerostr(1:end-floor(log10(n_file))),num2str(n_file),file_suffix];
% end
savename = 'savedhere'
disp(['Saving file ',savename,' . . .'])
%cut off allocated but unused data
EventData.channel = EventData.channel(1:n_event);
EventData.timestamp = EventData.timestamp(1:n_event);
EventData.event_info = EventData.event_info(1:n_event);
EventData.signal = EventData.signal(1:n_event,:);
%save
save(savename,'EventData')
            
progressbar(1)

if bad_file_flag
    warning('Event length doesn''t match, file terminated early.')
    EventData.channel = EventData.channel(1:n_eventd-1);
    EventData.timestamp = EventData.timestamp(1:n_event-1);
    EventData.event_info = EventData.event_info(1:n_event-1);
    EventData.signal = EventData.signal(1:n_event-1,:);
end
