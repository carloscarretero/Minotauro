/*
 * 	-------------------------------------------------------------------------
 * 	|  Sharp infrared sensor test code										|
 *	|  Author:  Carlos Carretero                                           	|
 * 	|  Date:    11 - 16 - 2015                                             	|
 * 	|  Version: 1.00                                                       	|
 * 	|  Description: The test consists in a permanent reading of the 		|
 *	|  IR sensor to prove that it reads the distance correctly				|
 * 	|  The distance read from the IR sensor will be printed on the PC/mobile|
 * 	-------------------------------------------------------------------------
 */

const float ResolutionADC=0.00488;
const int sharpPin = A3; 	// Analog pin of sharp sensor
int Value_Sharp_Pin = 0;    // variable to store the values from sensor
float Voltage = 0;
float distance = 0;
void setup()
{
	Serial.begin(9600);
	//Serial1.begin(9600);
}
 
void loop()
{
	Value_Sharp_Pin = analogRead(A3);     	
	Voltage = Value_Sharp_Pin*ResolutionADC;
	if (0.4 <= Voltage && Voltage <= 2.6)
	{
		distance = 12.629*pow(Voltage,-1.064);
		Serial.println(Voltage);        
		//Serial1.println(val);	
	}		
	delay(100);                	
}
