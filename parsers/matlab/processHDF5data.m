function [ ] = processHDF5data( hdfname,eventsperpacket,savetomatflag )
%PROCESSDATA Function to process hdf5 files from 3302 and extract raw
%events for filtering, processing, etc.
%Author: Cameron Bates
%Additions: Joseph Curtis

% eventsperpacket = 10000; %number of pulses to process per iteration
fid = H5F.open(hdfname); %open hdf5 file
dset_id = H5D.open(fid,'/RawData');
space_id = H5D.get_space(dset_id);
[ndims,h5_dims] = H5S.get_simple_extent_dims(space_id); %Get number of raw events and length
h5_dims %print dimensions of raw data array [(1) = num pulses] [(2) = pulse length]
cpos = 1; %current position in dataset
if savetomatflag
    filectr = 0; %counter for mat files if saving
    F = strfind(hdfname,'.h5'); %index location where file name ends and extension begins
    hdfnamebase = hdfname(1:F(1)-1); %name of file without extension
end

progressbar(0)

%read events in packets of eventsperpacket (possibly more if you have 64-bit matlab)
while h5_dims(1) - cpos > eventsperpacket
    data = h5read(hdfname,'/RawData',[1 cpos],[h5_dims(2) eventsperpacket])'; %raw data for processing
    EventData = h5read(hdfname,'/EventData',cpos,eventsperpacket)'; %eventdata structure
    EventData.detector = EventData.detector(:)';%cpos:(cpos+eventsperpacket)
    EventData.ADC_value =  EventData.ADC_value(:)';
    EventData.timestamp = EventData.timestamp(:)';
    
    %PROCESS DATA HERE
    %ACCUMULATE
    
    %save to mat file loop
    if savetomatflag
        EventData.Raw = data;
        filectr = filectr + 1;
        matname = [hdfnamebase,'_',num2str(filectr),'.mat'];
        save(matname, 'EventData');
        display(['Saved file to ' hdfnamebase '_' num2str(filectr) '.mat']);
    end
    
    cpos = cpos + eventsperpacket;
    
    progressbar(cpos/h5_dims(1),cpos)
    
end

progressbar(1)

%read remaining events
data = h5read(hdfname,'/RawData',[1 cpos],[h5_dims(2) (h5_dims(1) - cpos)])'; %raw data for processing
EventData = h5read(hdfname,'/EventData',cpos,h5_dims(1)-cpos)'; %eventdata structure
EventData.detector = EventData.detector(:)';
EventData.ADC_value =  EventData.ADC_value(:)';
EventData.timestamp = EventData.timestamp(:)';

%PROCESS DATA HERE
%ACCUMULATE

%save to mat file loop
if savetomatflag
    EventData.Raw = data;
    filectr = filectr + 1;
    matname = [hdfnamebase,'_',num2str(filectr),'.mat'];
    save(matname, 'EventData');
    display(['Saved file to ' hdfnamebase '_' num2str(filectr) '.mat']);
end