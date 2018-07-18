import time
import serial


ser = serial.Serial(
   
    port='/dev/ttyACM0',
    baudrate = 115200,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=1
)
counter=0


while 1:
    ser.write(str.encode('i'))
    x=ser.readline()
    y = x.rstrip()
    if (y == 'o'):
       ser.write(str.encode('s'))
       print('enviei: s')  
    print x
