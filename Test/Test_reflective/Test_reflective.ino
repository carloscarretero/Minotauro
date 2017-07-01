/*
 * 	-------------------------------------------------------------------------
 * 	|  Reflective sensors test code    	         			|
 *	|  Author:  Carlos Carretero                                           	|
 * 	|  Date:    11 - 16 - 2015                                             	|
 * 	|  Version: 1.00                                                       	|
 * 	|  Description: This test proves that the reflective sensors detect     |
 *      |  the change between black and white in a paper located near both      |
 *      |  sensors, which are under the robot, in the front side.               |
 *      |  The tests sends data via bluetooth to the windows app                | 
 * 	-------------------------------------------------------------------------
 */

// El circuito entrega a la salida un nivel bajo cuando no refleja el haz infrarrojo (NEGRO) y un
// nivel alto cuando encuentra un material sobre el que refleja el haz (BLANCO).

const float ResolutionADC=0.00488;

const int   reflectiveDR_pin = A0,
            reflectiveDL_pin = A1;
            
int reflectiveDR_value = 0,    // variable to store the values from both sensors
    reflectiveDL_value = 0;
    
float   reflectiveDR_voltage = 0,
        reflectiveDL_voltage = 0;

void setup()
{
    Serial1.begin(9600);
}
 
void loop()
{
    reflectiveDR_value = analogRead(reflectiveDR_pin);
    reflectiveDL_value = analogRead(reflectiveDL_pin);
    
    //reflectiveDR_voltage = ResolutionADC * reflectiveDR_value;
    //reflectiveDL_voltage = ResolutionADC * reflectiveDL_value;

    delay(1000);
    
    if(reflectiveDR_value <= 255)
        {Serial.print("DR reflective sensor detects: WHITE "); Serial.println(reflectiveDR_value);}
    else                         
        {Serial.print("DR reflective sensor detects: BLACK "); Serial.println(reflectiveDR_value);}
    
    if(reflectiveDL_value <= 255)
    {
        Serial.print("DL reflective sensor detects: WHITE ");Serial.println(reflectiveDL_value);
    }
    else        
    {                 
        Serial.print("DL reflective sensor detects: BLACK ");Serial.println(reflectiveDL_value);
    }

    Serial.println();
    
}
