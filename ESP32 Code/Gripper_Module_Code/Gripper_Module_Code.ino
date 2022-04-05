/*  Multidrone - ESP32 Gripper Module Code
    Function: Reads incoming serial data and actuates grippers
    Author: Connor Dorward
    Last Modified : 22/02/2022
*/


#include <ESP32Servo.h>
#include <SoftwareSerial.h>

SoftwareSerial piSerial(27, 26); // rx= 27,tx = 26

//Create 3 servo objects
Servo gripper1;
Servo gripper2;
Servo gripper3;


// Function Prototypes
void openGrippers();
void closeGrippers();

// Appends received serial message to rx_buffer
char rx_buffer[20];
int i=0; //character index
int c=0, o=0;

// Define Angles
short openAngle = 179;       // open angle
short middleAngle = 90;    // middle angle
short closeAngle = 0;       // close angle

// Recommended PWM GPIO pins on the ESP32 include 2,4,12-19,21-23,25-27,32-33 
// Possible PWM GPIO pins on the ESP32-S2: 0(used by on-board button),1-17,18(used by on-board LED),19-21,26,33-42

//Before: Pin 22,27,38 = GPIO2 , GPIO17, GPIO19

//Works: D2, 
//Not work:  18, 3
int gripper1_pin = 2;  //22, 27, 38
int gripper2_pin = 17; // was 17      - 4 works
int gripper3_pin = 19;


char GripperOpen[] = "Gripper/Open";
char GripperClose[] = "Gripper/Close";


void setup() 

{
  Serial.begin(9600);
  
  // Allow allocation of all timers
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);

  
  gripper1.setPeriodHertz(50);    // standard 50 hz servo
  gripper2.setPeriodHertz(50);    // standard 50 hz servo
  gripper3.setPeriodHertz(50);    // standard 50 hz servo

 
 // myservo.attach(servoPin, 1000, 2000); // attaches the servo on pin 18 to the servo object

 gripper1.attach(gripper1_pin, 600, 2400);  // was at 580
 gripper2.attach(gripper2_pin, 600, 2400);  // was at 580
 gripper3.attach(gripper3_pin, 600, 2400);  // was at 580
  
  // using default min/max of 1000us and 2000us
  // different servos may require different min/max settings
  // for an accurate 0 to 180 sweep
}

void loop() 
{

  while (Serial.available() > 0)
    {
              
      char incomingChar = Serial.read();

           
      if (incomingChar !='\n')                  // if not the end of the message, continue adding to buffer
      {

          rx_buffer[i] = incomingChar; 
          Serial.print(incomingChar);
          i++;


      }


      
      else                                     // if received full message
      {
        Serial.print("Received buffer:");
        Serial.println(rx_buffer);
        



        for (int i=0;i < strlen(GripperOpen);i++)
        {
          
          if (rx_buffer[i] == GripperOpen[i])
          {
            o++;
            
          }
          if (rx_buffer[i] == GripperClose[i])
          {
            c++;
            
          }
          
        
        }

        if (o ==strlen(GripperOpen))
        {
          openGrippers();
          
        }
        
        if (c ==strlen(GripperOpen))
        {
          closeGrippers();
          
        }


        o=0;
        c=0;
        strcpy(rx_buffer, "");
        i=0;

      }

      
  }


// Serial.println("Hi");
// delay(2000);
//openGrippers();
//
//delay(3000);
//
//closeGrippers();
//
//delay(3000);

}




void openGrippers()
{
  Serial.println("Opening Grippers...");
  gripper1.write(openAngle);
  gripper2.write(openAngle);
  gripper3.write(openAngle);

}

void closeGrippers()
{
  Serial.println("Closing Grippers...");
  gripper1.write(closeAngle);
  gripper2.write(closeAngle);
  gripper3.write(closeAngle);

}
