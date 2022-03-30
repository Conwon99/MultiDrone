import serial
#from time import sleep
from pymavlink import mavutil

print("started")

# Start a connection listening to a UDP port
the_connection = mavutil.mavlink_connection('/dev/ttyS0',baud=57600)
ser = serial.Serial(port='/dev/ttyUSB0', baudrate =9600)



# Wait for the first heartbeat 
#   This sets the system and component ID of remote system for the link
the_connection.wait_heartbeat()
print("Heartbeat from system (system %u component %u)" % (the_connection.target_system, the_connection.target_component))

print("end")

while 1:
    
     
    msg =the_connection.recv_match(blocking = True)
     #print(msg)
     #sleep(0.03)
     
    
    
    
    
    msg1 =the_connection.recv_match(type = 'RC_CHANNELS',blocking = True)
    
    chan_6 = the_connection.messages['RC_CHANNELS'].chan6_raw
    
    #print(chan)
    print(chan_6)


    if chan_6 > 1500 and chan_6 <1520:
        GripperOpen = True
        ser.write(b'Gripper/Open\n')
        print (b'Gripper/Open activated')
#         
#     
    if chan_6 > 1900 and chan_6 < 2100:
        GripperOpen = False
        ser.write(b'Gripper/Close\n')
        print (b'Gripper Closed')
    
    
    