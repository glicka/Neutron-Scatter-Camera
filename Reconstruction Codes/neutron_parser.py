#!/usr/bin/python

from __future__ import print_function
import struct
import os
import numpy
import h5py
import pylab
import argparse

# Neutron detector mapping
# Det   HVBoard Channel ADCBoard    ADCChan HVValue
# R4    1       0       1           1       1080
# R5    1       1       1           2       1180
# R8    1       2       1           3       1380
# R6    1       3       1           4       1200
# R16   1       4       1           5       1560
# R1    1       5       1           6       1710
# R13   1       6       1           7       1660
# R12   1       7       1           8       1565
# -------------------------------------------------
# R14   2       0       2           1       1510
# R10   2       1       2           2       1300
# R11   2       2       2           3       1525
# R7    2       3       2           4       1495
# R9    2       4       2           5       1255
# R15   2       5       2           6       1595
# R2    2       6       2           7       1585
# R3    2       7       2           8       1590

detector_map = {7: {i: i for i in range(8)},
                8: {i: i + 8 for i in range(8)}}

def get_board_channel(adc_info):
    board = ((adc_info & 0xff00) >> 12)
    channel = (adc_info & 0x000f)
    # print('{:08x} ({},{})'.format(adc_info, board, channel))
    return board, channel


class neutronParser(object):

    def __init__(self, dat_filename, verbose_level=0):
        self.filename = dat_filename
        print('MISTI neutron file: opening ', self.filename)
        try:
            self.dat_file = open(self.filename, "rb")
            self.dat_file_size_bytes = os.path.getsize(self.filename)
        except:
            print('Error opening file')
            exit(0)
        self.header = {}
        self.data = {}
        self.data['ADCBoard'] = []
        self.data['ADCChannel'] = []
        self.data['Detector'] = []
        self.data['Timestamp'] = []
        self.data['Energy'] = []
        self.data['RawSamples'] = []
        self.data_words = None
        self.num_words = 0
        self.num_buffers = 0
        self.verbose_level = verbose_level

    def read_next_n_words(self, N):
        assert(N >= 1)
        try:
            data = self.dat_file.read(4 * N)
        except:
            print('Error reading next {:d} words from file'.format(N))
            print('  Number of MB read: {:.1f}'.format(float(self.num_words) * 4. / (1024. * 1024.)))
            print('  Percentage of file read: {:5.1f}%'.format(100. * self.num_words * 4. / self.dat_file_size_bytes))
            exit(0)
        try:
            self.data_words = struct.unpack('<{:d}I'.format(N), data)
        except:
            print('Error: cannot unpack next {:d} words from file'.format(N))
            print('  Number of MB read: {:.1f}'.format(float(self.num_words) * 4. / (1024. * 1024.)))
            print('  Percentage of file read: {:5.1f}%'.format(100. * self.num_words * 4. / self.dat_file_size_bytes))
            exit(0)
        self.num_words += N
        if self.verbose_level >= 5:
            print('Percentage of file read: {:5.1f}%'.format(100. * self.num_words * 4. / self.dat_file_size_bytes))
            print('Data words read:')
            for j in range(N):
                print('  {:08x}'.format(self.data_words[j]))

    def read_header(self):
        self.read_next_n_words(32)
        self.header['FileNumber']          = self.data_words[0]
        self.header['FileDataFormat']      = self.data_words[1]
        self.header['NumberOf3302Modules'] = self.data_words[2]
        self.header['SIS3820ClockMode']    = (self.data_words[3] & 0xffff0000) >> 16
        self.header['SIS3302ClockMode']    =  self.data_words[3] & 0x0000ffff
        self.header['RawSampleStartIndex'] = (self.data_words[4] & 0xffff0000) >> 16
        self.header['RawSampleLength']     =  self.data_words[4] & 0x0000ffff
        self.header['DecimationMode']      = (self.data_words[5] & 0xf0000000) >> 28
        self.header['FIREnergyGap']        = (self.data_words[5] & 0x0000ff00) >> 8
        self.header['FIREnergyLength']     = (self.data_words[5] & 0x000000ff)
        self.header['EnergySampleMode']    = self.data_words[6]
        self.header['ReadoutMode']         = self.data_words[7]
        self.header['EnergySampleStartIndex2'] = (self.data_words[8] & 0xffff0000) >> 16
        self.header['EnergySampleStartIndex1'] =  self.data_words[8] & 0x0000ffff
        self.header['EnergySampleLength']      = (self.data_words[9] & 0xffff0000) >> 16
        self.header['EnergySampleStartIndex3'] =  self.data_words[9] & 0x0000ffff
        self.header['EnergyGateLength']    = self.data_words[10]
        self.header['TriggerGateLength']   = self.data_words[11]
        self.header['PreTriggerDelay']     = self.data_words[12]
        self.header['Reserved_1']          = self.data_words[13]
        self.header['Reserved_2']          = self.data_words[14]
        self.header['Reserved_3']          = self.data_words[15]
        if self.verbose_level >= 1:
            for key in ['FileNumber', 'FileDataFormat', 'NumberOf3302Modules',
                        'SIS3820ClockMode', 'SIS3302ClockMode',
                        'RawSampleStartIndex', 'RawSampleLength',
                        'DecimationMode', 'FIREnergyGap', 'FIREnergyLength',
                        'EnergySampleMode', 'ReadoutMode',
                        'EnergySampleStartIndex2', 'EnergySampleStartIndex1',
                        'EnergySampleLength', 'EnergySampleStartIndex3',
                        'EnergyGateLength', 'TriggerGateLength',
                        'PreTriggerDelay', 'Reserved_1', 'Reserved_2',
                        'Reserved_3']:
                print('{:25s}: {:08x}'.format(key, self.header[key]))

    def read_single_event_data(self):
        CD = {}
        # read single event header information
        self.read_next_n_words(10)
        CD['ADCID']     =  self.data_words[0] & 0x0000ffff
        CD['Timestamp'] = (self.data_words[0] & 0xffff0000) << 16 \
                        | (self.data_words[1] & 0xffffffff)
        CD['PeakHigh']  =  self.data_words[2] & 0x000007ff
        CD['PeakHighIndex']        = (self.data_words[2] & 0x01ff0000) >> 16
        CD['PileupInfo']           = (self.data_words[3] & 0xff000000) >> 24
        CD['AccumulatorSumGate1']  =  self.data_words[3] & 0x001fffff
        CD['AccumulatorSumGate2']  =  self.data_words[4] & 0x001fffff
        CD['AccumulatorSumGate3']  =  self.data_words[5] & 0x001fffff
        CD['AccumulatorSumGate4']  =  self.data_words[6] & 0x001fffff
        CD['AccumulatorSumGate5']  =  self.data_words[7] & 0x0000ffff
        CD['AccumulatorSumGate6']  = (self.data_words[7] & 0xffff0000) >> 16
        CD['AccumulatorSumGate7']  =  self.data_words[8] & 0x0000ffff
        CD['AccumulatorSumGate8']  = (self.data_words[8] & 0xffff0000) >> 16
        CD['NumberRawSamples']     =  self.data_words[9] & 0x0000ffff
        CD['Trailer']              = (self.data_words[9] & 0xffff0000) >> 16
        assert(CD['Trailer'] == 0xdada)
        if self.verbose_level >= 2:
            print('    ADC ID: {:04x}   Time: {:012x}'.format(CD['ADCID'], CD['Timestamp']))
        if self.verbose_level >= 3:
            for key in ['ADCID', 'Timestamp', 'PeakHigh', 'PeakHighIndex',
                        'PileupInfo', 'AccumulatorSumGate1', 'AccumulatorSumGate2',
                        'AccumulatorSumGate3', 'AccumulatorSumGate4',
                        'AccumulatorSumGate5', 'AccumulatorSumGate6',
                        'AccumulatorSumGate7', 'AccumulatorSumGate8',
                        'NumberRawSamples', 'Trailer']:
                print('        {:25s}: {:08x}'.format(key, CD[key]))
        # read ADC samples
        self.read_next_n_words(CD['NumberRawSamples'] / 2)
        CD['RawSamples'] = []
        for j in range(CD['NumberRawSamples'] / 2):
            sample_1 =  self.data_words[j] & 0x0000ffff
            sample_2 = (self.data_words[j] & 0xffff0000) >> 16
            CD['RawSamples'].append(sample_1)
            CD['RawSamples'].append(sample_2)
            if self.verbose_level >= 4:
                # print('Raw samples: {:04x}, {:04x}'.format(sample_2, sample_1))
                print('            Raw samples: {:4d}, {:4d}'.format(sample_2, sample_1))
        return CD

    def read_single_buffer(self):
        self.read_next_n_words(1)
        if self.verbose_level >= 2:
            print('{:08x}'.format(self.data_words[0]))
        buffer_header = self.data_words[0]
        if buffer_header == 0xdeadbeef:
            pass
        elif buffer_header == 0xe0f0e0f:
            print('End of file reached')
            return False
        else:
            print('Unknown error -- buffer header does not match')
            exit(0)
        self.read_next_n_words(4)
        if self.verbose_level >= 2:
            for j in range(4):
                print('{:08x}'.format(self.data_words[j]))
        num_events = self.data_words[1]
        # assert(self.data_words[2] == 0x80000000)
        assert(self.data_words[3] == 0x0000006e)
        print('Buffer number: {:d}   # of events: {:d}'.format(self.num_buffers, num_events))
        print('  Percentage of file read: {:5.1f}%'.format(
            100. * self.num_words * 4. / self.dat_file_size_bytes))
        for j in range(num_events):
            CD = self.read_single_event_data()
            if CD is not None:
                board, channel = get_board_channel(CD['ADCID'])
                self.data['ADCBoard'].append(board)
                self.data['ADCChannel'].append(channel)
                detector = detector_map[board][channel]
                self.data['Detector'].append(detector)
                self.data['Timestamp'].append(CD['Timestamp'])
                self.data['Energy'].append(max(CD['RawSamples']) - CD['RawSamples'][0])
                self.data['RawSamples'].append(CD['RawSamples'])
                del CD
            else:
                print('Error: No event data read')
                # exit(0)
                return False
        self.num_buffers += 1
        return True

    def parse(self):
        self.read_header()
        while self.read_single_buffer():
            pass
        self.convert_to_numpy()
        print('Done reading MISTI neutron file')

    def convert_to_numpy(self):
        """Convert all data to numpy arrays."""
        for key in self.data.keys():
            self.data[key] = numpy.array(self.data[key])

    def write(self):
        try:
            out_filename = self.filename.split('.dat')[0] + '.h5'
            h5_file = h5py.File(out_filename, 'w')
        except:
            print('Error opening HDF5 file for writing: ' + out_filename)
            exit(0)
        print('MISTI neutron file: writing to file ' + out_filename)
        # create and write datasets to HDF5 file
        dataset_formats = {
            'ADCBoard': 'i2',
            'ADCChannel': 'i2',
            'Detector': 'i2',
            'Timestamp': 'i8',
            'Energy': 'i2',
            'RawSamples': 'i2'
        }
        for dataset in dataset_formats:
            dset = h5_file.create_dataset(dataset, self.data[dataset].shape, dataset_formats[dataset])
            dset[:] = self.data[dataset]

def main(filename, verbosity, plots=False, **kwargs):

    print('here!', filename)

    print('\n' + '-' * 40 + '\n')
    f = neutronParser(filename, verbose_level=1)
    f.parse()
    print()
    f.write()

    print('ADC Boards:   ', pylab.unique(f.data['ADCBoard']))
    print('ADC Channels: ', pylab.unique(f.data['ADCChannel']))
    print('Detectors:    ', pylab.unique(f.data['Detector']))
    for j in pylab.unique(f.data['ADCBoard']):
        print(j, pylab.unique((f.data['ADCChannel'])[f.data['ADCBoard'] == j]))

    if plots:
        pylab.figure()
        for j in range(10):
            pylab.plot(f.data['RawSamples'][j], label='{:d}'.format(j))
        pylab.legend()

        pylab.figure()
        for j in pylab.unique(f.data['Detector']):
            print(j)
            h = pylab.histogram((f.data['Energy'])[f.data['Detector'] == j], range=[0., 4096.], bins=1000)
            bin_centers = 0.5 * (h[1][1:] + h[1][:-1])
            pylab.plot(bin_centers, h[0], label='D{:02d}'.format(j), drawstyle='steps-mid')
        pylab.xlim(0., 4096.)
        pylab.legend()
        pylab.show()


if __name__ == '__main__':

    parser = argparse.ArgumentParser(
        description='RadMAP Neutron Parser + HDF5 Saving',
        formatter_class=argparse.ArgumentDefaultsHelpFormatter)
    parser.add_argument('filenames', nargs='*',
                        help='Parse these files')
    parser.add_argument('-v', '--verbosity', default=1, type=int,
                        help='Level of verbosity')
    parser.add_argument('-p', '--plots', action='store_true', default=False,
                        help='Display plots of spectra and some raw traces after parsing')
    args = parser.parse_args()
    for filename in args.filenames:
        main(filename, verbosity=args.verbosity, plots=args.plots)
