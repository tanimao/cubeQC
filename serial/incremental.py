#!/usr/bin/env python3
import argparse
import serial
import numpy as np
import sys
from time import sleep

from ardad import ARDAD

def go(dev, steps, speed=2000):
    try:
        unten_no = dev.get_unten_no()
        dev.set_incremental(unten_no=unten_no)
        dev.set_position(steps, unten_no=unten_no)
        dev.set_speed(speed, unten_no=unten_no)
    except:
        print('Error codes: ')
        print('-------------------')
        for code in 2*np.arange(11) + 0x00AC:
            print(dev.read_register_single(code))
        sys.exit(1)
    
    print('Start')

    try:
        dev.start()
        sleep(0.1)
        dev.clear()

        while dev.is_moving():
            sleep(1)
    except:
        dev.stop()
        raise Exception('Aborted.')


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--speed', '-s', type=int,
                        help=''' Motion speed ''',
                        default=2000)

    parser.add_argument('--position', '-p', type=int,
                        help=''' Position ''',
                        default=0)

    args = parser.parse_args()

    ardad = ARDAD('/dev/serial/by-id/usb-FTDI_USB-RS485_Cable_FT0871UR-if00-port0', 1)

    print('Unten No: {0}'.format(ardad.read_register_single(0x00C2)))
    print('Position: {0}'.format(ardad.read_register_single(0x0400)))
    print('Speed: {0}'.format(ardad.read_register_single(0x0480)))

    go(ardad, args.steps, args.speed)

    print('Fin!')
