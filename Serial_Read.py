import serial
from time import sleep

# ser = serial.Serial(port='/dev/ttyUSB0', baudrate =9600)
ser_FC = serial.Serial(port='/dev/ttyS0', baudrate =57600)


print("started")

while 1:
    print(ser_FC.read())
    sleep(0.03)