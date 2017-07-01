/*
 * 	-------------------------------------------------------------------------
 * 	|  Battery test code                        														|
 *	|  Author:  Carlos Carretero                                           	|
 * 	|  Date:    11 - 16 - 2015                                             	|
 * 	|  Version: 1.00                                                       	|
 * 	|  Description: The test does a permanent read of the battery charge    |
 *  |  value and prints it on the bluetooth Windows app                     |
 * 	-------------------------------------------------------------------------
 */

const float ResolutionADC = 0.00488; //4.88mV 
const int BatteryPin = A6; 
int BatteryValue = 0; 
float Voltage; 

void setup()
{
	Serial.begin(9600);
}
 
void loop()
{
	// Reads the sensor and return a value between 0-1023 
	BatteryValue = analogRead(BatteryPin); 
	// Calculates the equivalent voltage 
	Voltage = BatteryValue*ResolutionADC; 
	Serial.print (" Battery charge: "); 
	Serial.print (Voltage); 
	Serial.println (" V"); 
	delay(1000); 
}
