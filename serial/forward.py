import serial

ser = serial.Serial('/dev/tty.usbserial-AQ4LKZ6R',200)
ser2= serial.Serial('/dev/tty.usbserial-AO3SHQC8',200)

#ser2.write(1)
ser.write(1)
