/*
Author: 321tseug@gmail.com
Date: 2024/07/28
Board Type: Raspberry Pi Pico [Tools - Board - Board Manager - Search Pico - Install RP2040]
Used library: AccelStepper [ Sketch - Include Library - Manage Libraries - Search AccelStepper - Install ]
Version : 1.0
Notes: Besides Pico , RP2040 series is compitable.
Project: https://github.com/321tseug/watch_winder
*/


#include <AccelStepper.h>
 
 // Pin Configuration, Pls modify what the connection between driver board and Pico 
#define motor1Pin1  8    // No.1 ULN2003 driver board in1 connect to Pin number of Pico
#define motor1Pin2  9    // No.1 ULN2003 driver board in2 connect to Pin number of Pico
#define motor1Pin3  7    // No.1 ULN2003 driver board in3 connect to Pin number of Pico
#define motor1Pin4  6    // No.1 ULN2003 driver board in4 connect to Pin number of Pico
                                   
#define motor2Pin1  13     // No.2 ULN2003 driver board in1 connect to Pin number of Pico
#define motor2Pin2  12     // No.2 ULN2003 driver board in2 connect to Pin number of Pico
#define motor2Pin3  11     // No.2 ULN2003 driver board in3 connect to Pin number of Pico
#define motor2Pin4  10     // No.2 ULN2003 driver board in4 connect to Pin number of Pico

#define motor3Pin1  2     // No.3 ULN2003 driver board in1 connect to Pin number of Pico
#define motor3Pin2  3     // No.3 ULN2003 driver board in2 connect to Pin number of Pico
#define motor3Pin3  4    // No.3 ULN2003 driver board in3 connect to Pin number of Pico
#define motor3Pin4  5    // No.3 ULN2003 driver board in4 connect to Pin number of Pico
                                   
#define motor4Pin1  18     // No.4 ULN2003 driver board in1 connect to Pin number of Pico
#define motor4Pin2  19     // No.4 ULN2003 driver board in2 connect to Pin number of Pico
#define motor4Pin3  20     // No.4 ULN2003 driver board in3 connect to Pin number of Pico
#define motor4Pin4  21     // No.4 ULN2003 driver board in4 connect to Pin number of Pico

// Running Configuration 
// Default Setting is : every 4 hours, the winder will rotate 1 hour continuously.
// In 1 hours, winder will change the direction every 20 rounds Approximately.
int round_number = 20;     // Default Round Number
const unsigned long _runTime = 1*60*60*1000 ;// Continuous running time, Default is 1 Hours
const unsigned long _totalTime = 4*60*60*1000 ; // Total counting time


AccelStepper stepper1(AccelStepper::FULL4WIRE, motor1Pin1, motor1Pin3, motor1Pin2, motor1Pin4);
AccelStepper stepper2(AccelStepper::FULL4WIRE, motor2Pin1, motor2Pin3, motor2Pin2, motor2Pin4);
AccelStepper stepper3(AccelStepper::FULL4WIRE, motor3Pin1, motor3Pin3, motor3Pin2, motor3Pin4);
AccelStepper stepper4(AccelStepper::FULL4WIRE, motor4Pin1, motor4Pin3, motor4Pin2, motor4Pin4);

unsigned long lastTime; 
unsigned long startTime; 
unsigned long endTime;   
unsigned short ran = 0;

 
void setup()
{  
    Serial.begin(115200);
    stepper1.setMaxSpeed(500.0);
    stepper1.setAcceleration(50.0);
    stepper1.moveTo(2048*round_number);    
    
    stepper2.setMaxSpeed(500.0);
    stepper2.setAcceleration(50.0);
    stepper2.moveTo(2048*round_number);    

    stepper3.setMaxSpeed(500.0);
    stepper3.setAcceleration(50.0);
    stepper3.moveTo(2048*round_number);    

    stepper4.setMaxSpeed(500.0);
    stepper4.setAcceleration(50.0);
    stepper4.moveTo(2048*round_number);    

    startTime = millis();

}
 
void loop()
{
  lastTime = millis() - startTime;
  if (lastTime < _runTime) {
      if ( stepper1.distanceToGo() == 0 ) {
        Serial.println("Change Direction of motor 1");
        stepper1.moveTo(-stepper1.currentPosition());             
      }
      if ( stepper2.distanceToGo() == 0) {
        Serial.println("Change Direction of motor 2");
        stepper2.moveTo(-stepper2.currentPosition());      
      }
      if (stepper3.distanceToGo() == 0) {
        Serial.println("Change Direction of motor 3");
        stepper3.moveTo(-stepper3.currentPosition());                 
      }
      if ( stepper4.distanceToGo() == 0 ) {
        Serial.println("Change Direction of motor 4");
        stepper4.moveTo(-stepper4.currentPosition());      
      }
      if ( lastTime % 1000 == 0 ){ 
        Serial.print("Start to rotate ( ");
        Serial.print(millis());
        Serial.print(" ):");
        Serial.print(lastTime / 1000);
      }
      stepper1.run();
      stepper2.run();
      stepper3.run();
      stepper4.run();
  } else if ( lastTime >= _totalTime ) {
      Serial.print("Staring:");
      Serial.println(lastTime / 1000);
      startTime = millis();
      ran = 0;
      Serial.print("Setting all motors EnableOutput");
      stepper1.enableOutputs();
      stepper2.enableOutputs();
      stepper3.enableOutputs();
      stepper4.enableOutputs();      
  } else if ( lastTime % 1000 == 0 ) {
      Serial.print("Waiting to Rotate:");
      Serial.println( lastTime / 1000 );
      if ( ran == 0 ) {
        Serial.print("Setting all motors DisableOutput");
        stepper1.disableOutputs();
        stepper2.disableOutputs();
        stepper3.disableOutputs();
        stepper4.disableOutputs();
        ran = 1;
      }
  }
}
