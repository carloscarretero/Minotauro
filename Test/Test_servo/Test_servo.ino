/*
 * 	-------------------------------------------------------------------------
 * 	|  Engines test code                                                   	|
 *	|  Author:  Carlos Carretero                                           	|
 * 	|  Date:    11 - 16 - 2015                                             	|
 * 	|  Version: 1.00                                                       	|
 * 	|  Description: This code test the servomotors movement. The'll turn	  |
 *	|  180º in one direction and 180º on the opposite way.				          |    					        
 *  |  The test will send to the pc/mobile information about                |
 *  |  the progression.                                                     |
 * 	-------------------------------------------------------------------------
 */
 
#include <Servo.h>

Servo Servo_sonic, Servo_infra;
int pinServo_sonic = 11,
	  pinServo_infra = 7;

void setup() 
{
  Serial.begin(9600);
  //Serial1.begin(9600);
  Servo_sonic.attach(pinServo_sonic);
  Servo_infra.attach(pinServo_infra);
}

void loop() 
{
   Servo_sonic.write(0);
   Servo_infra.write(0);
   
   delay(1000);
   
   Servo_sonic.write(180);
   Servo_infra.write(180);
   
   delay(1000);
   
   Servo_sonic.write(0);
   Servo_infra.write(0);

   Serial.println("Test_servo finalizado.");
   //Serial1.println("Test_servo finalizado.");
}
