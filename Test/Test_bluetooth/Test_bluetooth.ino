/*
 * 	-------------------------------------------------------------------------
 * 	|  PC/Mobile - Arduino bluetooth connection								|
 *	|  Author:  Carlos Carretero                                           	|
 * 	|  Date:    11 - 16 - 2015                                             	|
 * 	|  Version: 1.00                                                       	|
 * 	|  Description: This test verify the bluetooth connection between 		|
 *	|  Arduino and the PC/mobile by sending some messages from arduino		| 
 * 	-------------------------------------------------------------------------
 */

void setup()
{
	 Serial1.write("AT");
   delay(1001);
   Serial1.write("AT+NAMECARLOS");
   delay(1001);
   Serial1.write("AT+PIN1234");
   delay(1001);
   Serial1.write("AT+BAUD4");
   delay(1001);
}
 
void loop()
{
  Serial1.println("Bluetooth connection...NOT_OK");
  delay(1000);
  Serial1.println("Bluetooth connection...OK");
  delay(1000);
}
