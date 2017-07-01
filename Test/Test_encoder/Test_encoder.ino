/*
 *   ------------------------------------------------------------------------
 *  |  Engines test code                                                    |
 *  |  Author:  Rafa Moreno                                                 |
 *  |  Date:    20 - 16 - 2015                                              |
 *  |  Version: 1.00                                                        |
 *  |  Description: Counts the number of laps and stops when after one lap  |
 *  |                                                                       |         
 *  -------------------------------------------------------------------------
*/

// Encoder Pins: 2 & 3
const int pinEncoderIzq = 3;
const int pinEncoderDer = 2;

// Counts the number of interrupts
int numInterruptIzq;
int numInterruptDer;
 
// Right Engine: Pins 5 & 6
const int   rightEngine1Pin = 5,
            rightEngine2Pin = 6;
      
// Left Engine: Pins 10 & 9
const int   leftEngine1Pin = 10,
            leftEngine2Pin = 9;

void setup() 
{
  Serial.begin(9600); 
  pinMode(pinEncoderIzq,INPUT);
  attachInterrupt(0,ISR_EncoderIzq,FALLING);
  pinMode(pinEncoderDer,INPUT);
  attachInterrupt(1,ISR_EncoderDer,FALLING);
  pinMode(rightEngine1Pin, OUTPUT);
  pinMode(rightEngine2Pin, OUTPUT);
  pinMode(leftEngine1Pin, OUTPUT);
  pinMode(leftEngine2Pin, OUTPUT);
}

void loop() 
{
  if(numInterruptIzq == 0 && numInterruptDer == 0)
  {
    digitalWrite(rightEngine1Pin,HIGH);
    digitalWrite(rightEngine2Pin,LOW);
    
    digitalWrite(leftEngine1Pin,HIGH);
    digitalWrite(leftEngine2Pin,LOW);
  } 

  Serial.println(numInterruptIzq);
  
  if(numInterruptIzq >= 12)
  {
    Serial.print("Vuelta completada: ");
    Serial.print("\nRueda IZQ: ");
    Serial.print(numInterruptIzq);
    digitalWrite(leftEngine1Pin,LOW);
    digitalWrite(leftEngine2Pin,LOW);
  }
  if(numInterruptDer >= 12)
  {
    //Serial.print("Vuelta completada: ");
    //Serial.print("\nRueda DER: ");
    //Serial.print(numInterruptDer);
    digitalWrite(rightEngine1Pin,LOW);
    digitalWrite(rightEngine2Pin,LOW);
  }
}

void ISR_EncoderIzq()
{
  numInterruptIzq++;
}

void ISR_EncoderDer()
{
  numInterruptDer++;  
}

