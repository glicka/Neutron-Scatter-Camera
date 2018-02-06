function convert3350mattohdf5(matfile)

F = strfind(matfile,'.mat'); %index location where file name ends and extension begins
matnamebase = matfile(1:F(1)-1); %name of file without extension
load(matfile)
dim = size(EventData.signal);
h5file = [matnamebase '.h5'];

delete(h5file)
h5create(h5file, '/signal', dim);
h5write(h5file, '/signal', EventData.signal);