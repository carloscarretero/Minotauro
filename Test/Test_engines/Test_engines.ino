/*
 * 	-------------------------------------------------------------------------
 * 	|  Engines test code                                                   	|
 *	|  Author:  Carlos Carretero                                           	|
 * 	|  Date:    11 - 16 - 2015                                             	|
 * 	|  Version: 1.00                                                       	|
 * 	|  Description: This code makes the engines do three things:           	|
 * 	|   1. Go forward                                                      	|	        
 * 	|   2. Go backwards                                                    	|
 * 	|   3. Rotate in different directions at the same time				  	      |
 * 	|  They spend 5 seconds on each step. When they finish the step, they	  |
 * 	|  stop. Then, the tests waits for 5 seconds and then moves to 			    |
 *	|  the next step														                            |
 * 	|  The program sends info via bluetooth to the Windows app             	|
 * 	-------------------------------------------------------------------------
 */
 
// Right Engine: Pins 5 & 6
const int 	rightEngine1Pin = 5,
			      rightEngine2Pin	= 6;
			
// Left Engine: Pins 10 & 9
const int 	leftEngine1Pin = 10,
			      leftEngine2Pin = 9;
						
void setup() 
{
	Serial1.begin(9600);		// Bluetooth conexion set-up
	pinMode(rightEngine1Pin, OUTPUT);
	pinMode(rightEngine2Pin, OUTPUT);
	pinMode(leftEngine1Pin, OUTPUT);
	pinMode(leftEngine2Pin, OUTPUT);
}

void loop() 
{
	
	// 1.- Both engines rotate forward
	Serial1.println("Engines rotating forward");
		digitalWrite(rightEngine1Pin,HIGH);
		digitalWrite(rightEngine2Pin,LOW);
		digitalWrite(leftEngine1Pin,HIGH);
		digitalWrite(leftEngine2Pin,LOW);
	delay(5000);
		digitalWrite(rightEngine1Pin,LOW);
		digitalWrite(rightEngine2Pin,LOW);
		digitalWrite(leftEngine1Pin,LOW);
		digitalWrite(leftEngine2Pin,LOW);
	Serial1.println("Engines stopped. Waiting for next step...");
	delay(5000);
	
	// 2.- Both engines rotate backwards
	Serial1.println("Engines rotating backwards");
		digitalWrite(rightEngine1Pin,LOW);
		digitalWrite(rightEngine2Pin,HIGH);
		digitalWrite(leftEngine1Pin,LOW);
		digitalWrite(leftEngine2Pin,HIGH);
	delay(5000);
		digitalWrite(rightEngine1Pin,LOW);
		digitalWrite(rightEngine2Pin,LOW);
		digitalWrite(leftEngine1Pin,LOW);
		digitalWrite(leftEngine2Pin,LOW);
	Serial1.println("Engines stopped. Waiting for next step...");
	delay(5000);
	
	// 3.- Both engines rotate in different directions
	Serial1.println("Engines rotating in different directions");
		digitalWrite(rightEngine1Pin,HIGH);
		digitalWrite(rightEngine2Pin,LOW);
		digitalWrite(leftEngine1Pin,LOW);
		digitalWrite(leftEngine2Pin,HIGH);
	delay(5000);
		digitalWrite(rightEngine1Pin,LOW);
		digitalWrite(rightEngine2Pin,LOW);
		digitalWrite(leftEngine1Pin,LOW);
		digitalWrite(leftEngine2Pin,LOW);
	Serial1.println("Engines stopped. End of the test");
	delay(1000000);
}






