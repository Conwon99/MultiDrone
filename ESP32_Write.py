import serial
from time import sleep

ser = serial.Serial(port='/dev/ttyUSB0', baudrate =9600)

print("started")

while 1:
        
#     print(ser.read())
#     sleep(0.03)
    
    userInput = input("enter command")
    
    if userInput== "Gripper/Open":
        ser.write(b'Gripper/Open\n')
    elif userInput== 'Gripper/Close':
        ser.write(b'Gripper/Close\n') 