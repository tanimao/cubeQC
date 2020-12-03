#!/usr/bin/env python3
''' Module for ARDAD (motor driver) '''

from struct import pack, unpack
from time import sleep
from functools import reduce
from pathlib import Path
import argparse
import serial
import numpy as np


VERBOSE = True
DEVICE_PATH = '/dev/serial/by-id/usb-FTDI_USB-RS485_Cable_FT0871UR-if00-port0'
SLAVE_ADDR = 1
UNTEN_NO = 0
LOCKFILE_PATH = '/home/gb/.ardad.lock'

class ARDAD(object):
    ''' Class for ARDAD (motor driver) '''
    def __init__(self, devfile, slave_addr, lockpath=LOCKFILE_PATH):
        ''' initialize the class '''
        assert isinstance(slave_addr, int)
        assert slave_addr >= 0x00 and slave_addr <= 0xff
        self.dev = serial.Serial(devfile,
                                 9600,
                                 timeout=1.,
                                 parity=serial.PARITY_EVEN,
                                 bytesize=serial.EIGHTBITS,
                                 stopbits=serial.STOPBITS_ONE)
        assert self.dev != None, 'Device (%s) is not ready.' % devfile
        self.slave_addr = slave_addr
        self._lockpath = Path(lockpath)
        if self._lockpath.exists():
            raise RuntimeError('Locked.')
        else:
            self._lockpath.touch()

    def __del__(self):
        self.dev.close()
        self._lockpath.unlink()
        return

    def __write(self, data):
        assert isinstance(data, bytes)
        self.dev.write(data)
        sleep(0.1)
        return

    def __read(self, length):
        return self.dev.read(length)

    def __readline(self):
        return self.dev.readline()

    def _write(self, func_code, data):
        assert isinstance(func_code, int)
        assert isinstance(data, list)
        assert 0x00 <= func_code <= 0xff
        header = pack('BB', self.slave_addr, func_code)
        body = pack(str(len(data))+'B', *data)
        crc_val = crc16([self.slave_addr, func_code] + data)
        footer = pack('BB', crc_val & 0x00FF, (crc_val & 0xFF00) >> 8)
        self.__write(header + body + footer)
        return

    def _read(self, length=None):
        if length is None:
            ret = self.__readline()
        else:
            ret = self.__read(length+4)
        tmplen = len(ret)

        up_data = list(unpack(str(tmplen) + 'B', ret))

        header = up_data[:2]
        body = up_data[2:-2]
        footer = up_data[-2:]
        crc_val = crc16(header + body)
        assert crc_val == (footer[0] + (footer[1] << 8))
        return header, body

    def _rw(self, func_code, data, read_length):
        self._write(func_code, data)
        read_header, read_body = self._read(read_length)
        assert read_header[0] == self.slave_addr
        assert read_header[1] == func_code
        return read_body

    def diagnosis(self):
        ''' Carry out diagnosis '''
        function_code = 0x08
        data = [0x00, 0x00, 0x12, 0x34]
        self._write(function_code, data)
        print(self._read(len(data)))

    def read_register(self, reg_addr, reg_num):
        ''' Read register value at [reg_addr] for [reg_num] length '''
        read_func = 0x03
        reg_vals = self._rw(read_func, blist(reg_addr) + blist(reg_num), 2*reg_num + 1)
        assert len(reg_vals) - 1 == reg_vals[0]
        upper_bytes = np.array(reg_vals[1:][::2])
        lower_bytes = np.array(reg_vals[2:][::2])
        return (upper_bytes << 8) + lower_bytes

    def write_register(self, reg_addr, value_list):
        ''' Write [value_list] from [reg_addr] '''
        write_func = 0x10
        reg_num = len(value_list)
        for value in value_list:
            assert 0 <= value <= 0xFFFF
        self._write(write_func,
                    blist(reg_addr) + blist(reg_num) + [reg_num*2] + \
                    reduce(lambda x, y: x + y, [blist(value) for value in value_list]))

        header, body = self._read()
        if header[1] == 0x90:
            exception_code = body[0]
            communication_error_code = self.read_register_single(0x00AC)
            print("Exception code: {0:X}".format(exception_code))
            print("Communication error code: {0:X}".format(communication_error_code))
            raise Exception('Communication error')
        return

    def read_register_single(self, reg_addr):
        ''' Read single value at [reg_addr] '''
        val_list = self.read_register(reg_addr, 2)
        return (val_list[0] << 16) + val_list[1]

    def write_register_single(self, reg_addr, value):
        ''' Write single value at [reg_addr] '''
        upper = (value & 0xFFFF0000) >> 16
        lower = (value & 0x0000FFFF)
        return self.write_register(reg_addr, [upper, lower])

    def get_unten_no(self):
        return self.read_register_single(0x00C2)

    def set_unten_no(self, unten_no):
        assert isinstance(unten_no, int)
        self.write_register_single(0x00C2, unten_no)
        return self.get_unten_no()

    def set_speed(self, speed_hz, unten_no=0):
        ''' Set speed of rotation '''
        assert isinstance(speed_hz, int)
        assert isinstance(unten_no, int)
        assert 0 <= unten_no < 64
        assert 0 <= speed_hz <= 1000000
        reg_addr = 0x0480 + unten_no*2
        self.write_register_single(reg_addr, speed_hz)
        return self.get_speed(unten_no=unten_no)

    def get_speed(self, unten_no=0):
        reg_addr = 0x0480 + unten_no*2
        return self.read_register_single(reg_addr)

    def test_set_parameter(self):
        ''' For test '''
        self._write(0x10, [0x04, 0x80, 0x00, 0x02, 0x00, 0x00, 0x19, 0x00])

    def set_incremental(self, unten_no=0):
        ''' Set to incremental mode'''
        assert isinstance(unten_no, int)
        assert 0 <= unten_no < 64
        reg_addr = 0x0500 + unten_no*2
        self.write_register_single(reg_addr, 0)
        return self.read_register_single(reg_addr)

    def set_absolute(self, unten_no=0):
        ''' Set to absolute mode'''
        assert isinstance(unten_no, int)
        assert 0 <= unten_no < 64
        reg_addr = 0x0500 + unten_no*2
        self.write_register_single(reg_addr, 1)
        return self.read_register_single(reg_addr)

    def set_position(self, position, unten_no=0):
        ''' Set position '''
        assert isinstance(position, int)
        assert isinstance(unten_no, int)
        assert 0 <= unten_no < 64
        assert -8388608 <= position <= 8388607
        reg_addr = 0x0400 + unten_no*2
        self.write_register_single(reg_addr, position)
        return self.get_position(unten_no=unten_no)

    def get_position(self, unten_no=0):
        reg_addr = 0x0400 + unten_no*2
        return self.read_register_single(reg_addr)

    def continuous(self, polarity):
        ''' Do continuous move.
        Args:
            polarity: True  -> reduce tilt
                      False -> tilt
        '''
        command = 0b01000000 if polarity else 0b10000000
        self.write_register_single(0x007C, command << 8)

    def jog(self, polarity):
        command = 0b00000010 if polarity else 0b00000001
        self.write_register_single(0x007C, command << 8)

    def clear(self):
        ''' Clear operation register '''
        self.write_register_single(0x007C, 0)

    def start(self):
        self.write_register_single(0x007C, 0b00001000)
    
    def stop(self):
        self.write_register_single(0x007C, 0b00100000)

    def is_moving(self):
        reg = self.read_register_single(0x007E)
        return (reg & (0b00100000 << 8) !=0)


def crc16(data):
    ''' Calc CRC16 '''
    assert isinstance(data, list)
    tmpval = 0xFFFF
    for val in data:
        tmpval = tmpval ^ val
        for _ in range(8):
            if tmpval & 0x01:
                tmpval = (tmpval >> 1) ^ 0xA001
            else:
                tmpval = tmpval >> 1
    return tmpval

def blist(val):
    ''' I don't remember '''
    return [(0xFF00 & val) >> 8, 0x00FF & val]

def main(argv=None):
    ''' Main function '''
    parser = argparse.ArgumentParser()
    parser.add_argument('--direction', '-d', type=str, required=True,
                        help=''' Polarity of motion.\nAccept [tilt] or [untilt]. ''')
    parser.add_argument('--speed', '-s', type=int,
                        help=''' Motion speed ''',
                        default=2000)
    args = parser.parse_args(argv)
    if args.direction == 'tilt':
        polarity = False
    elif args.direction == 'untilt':
        polarity = True
    else:
        parser.print_help()
        exit(1)

    ardad = ARDAD(DEVICE_PATH, SLAVE_ADDR)

    unten_no = ardad.get_unten_no()
    print('Unten No: {0}'.format(unten_no))

    ### DEBUG
    if unten_no != UNTEN_NO:
        raise RuntimeError('Unten no {} != {}'.format(unten_no, UNTEN_NO))

    print('Speed: {0}'.format(ardad.get_speed(unten_no=unten_no)))

    try:
        ardad.set_speed(args.speed, unten_no=unten_no)
    except:
        print('Error codes: ')
        print('-------------------')
        for code in 2*np.arange(11) + 0x00AC:
            print(ardad.read_register_single(code))
    print('Speed: {0}'.format(ardad.get_speed(unten_no=unten_no)))

    try:
        ardad.continuous(polarity)
        while True:
            sleep(1)
    except KeyboardInterrupt:
        pass
    finally:
        ardad.clear()
    exit(0)

if __name__ == '__main__':
    main()
