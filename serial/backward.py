import serial
import time

ser = serial.Serial('/dev/tty.usbserial-AQ4LKZ6R',190)
ser2= serial.Serial('/dev/tty.usbserial-AO3SHQC8',190)
start= time.time()
ser2.write(1)
time.sleep(0.025)
ser.write(1)
time.sleep(0.3)
ser2.write(1)
time.sleep(0.025)
ser.write(1)
print('operation time is ', time.time()-start)
