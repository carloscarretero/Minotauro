/*
 * 	-------------------------------------------------------------------------
 * 	|  Start test code														|
 *	|  Author:  Carlos Carretero                                           	|
 * 	|  Date:    11 - 16 - 2015                                             	|
 * 	|  Version: 1.00                                                       	|
 * 	|  Description: The test light red and green led when the robot is 		|
 * 	|  switched on
 * 	-------------------------------------------------------------------------
 */

int pinLed_rojo  = 13,
	pinLed_verde = 12;
 
void setup()
{
	Serial.begin(9600);
	//Serial1.begin(9600);
	pinMode(pinLed_rojo,OUTPUT);
	pinMode(pinLed_verde,OUTPUT);
}
 
void loop()
{
	digitalWrite(pinLed_rojo,HIGH);
	digitalWrite(pinLed_verde,HIGH);
}
