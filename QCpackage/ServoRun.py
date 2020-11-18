import serial

def ServoRun(sign,signBefore,ser):

    if sign == signBefore :
        ser.write(b'200\n')
    else :
        if sign == 'bad':
            ser.write(b'140\n')
    
        if sign == 'middle':
            ser.write(b'100\n')

        if sign == 'good':
            ser.write(b'178\n')






