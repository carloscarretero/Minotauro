#include "components.h"

/* Class Bluetooth --------------------------------------------------*/
myBluetooth::myBluetooth(){}

void myBluetooth::setup()
{
	Serial1.begin(9600);
}

void myBluetooth::test()
{}

void myBluetooth::sendText(const char* text)
{
  	if(strlen(text)<=50)
  	{
		char msg[53] = {};
      	msg[0] = '#';
    	msg[1] = '0';
  		for(int i=0; i<strlen(text); ++i)
  			msg[i+2] = text[i];
  		msg[strlen(text)+2] = '#';
     	msg[strlen(text)+3] = '\0';
		Serial1.print(msg);
	}
}

void myBluetooth::sendMaze(int i, int j)
{
	char ic = i + '0',
		jc = j + '0',
		msgM[] = {'#','1',ic,jc,'#','\0'};
	Serial1.print(msgM);
}

void myBluetooth::sendWall(int pos)
{
	char posc = pos + '0',
		msgW[] = {'#','2',posc,'#','\0'};
	Serial1.print(msgW);
}
/*-------------------------------------------------------------------*/

/* Class Serial -----------------------------------------------------*/
mySerial::mySerial(){}

void mySerial::setup()
{
	Serial.begin(9600);
}

void mySerial::test()
{}

void mySerial::sendText(const char* text)
{
  	if(strlen(text)<=50)
  	{
		char msg[53] = {};
      msg[0] = '#';
    	msg[1] = '0';
  		for(int i=0; i<strlen(text); ++i)
  			msg[i+2] = text[i];
  		msg[strlen(text)+2] = '#';
      msg[strlen(text)+3] = '\0';
		Serial.print(msg);
	}
}

void mySerial::sendMaze(int i, int j)
{
	char ic = i + '0',
		jc = j + '0',
		msgM[] = {'#','1',ic,jc,'#','\0'};
	Serial.print(msgM);
}

void mySerial::sendWall(int pos)
{
	char posc = pos + '0',
		msgW[] = {'#','2',posc,'#','\0'};
	Serial.print(msgW);
}
/*-------------------------------------------------------------------*/

/* Class Led --------------------------------------------------------*/
Led::Led(int pinB, int pinR, int pinG):
pinBlue(pinB), pinRed(pinR), pinGreen(pinG)
{}

void Led::setup()
{
	pinMode(pinBlue,OUTPUT);
	pinMode(pinRed,OUTPUT);
	pinMode(pinGreen,OUTPUT);
}

void Led::test()
{
	no_color(); 	delay(1000);
    green(); 		delay(1000);
    red();			delay(1000);
    blue();			delay(1000);
    yellow();		delay(1000);
    light_blue();	delay(1000);
    pink();			delay(1000);
    white();		delay(1000);
    no_color();
}

void Led::no_color()
{
	digitalWrite(pinBlue,LOW); 
    digitalWrite(pinRed,LOW);  
    digitalWrite(pinGreen,LOW);
}

void Led::red()
{
	digitalWrite(pinBlue,LOW); 
    digitalWrite(pinRed,HIGH);  
    digitalWrite(pinGreen,LOW);
}

void Led::blue()
{
	digitalWrite(pinBlue,HIGH); 
    digitalWrite(pinRed,LOW);  
    digitalWrite(pinGreen,LOW);
}

void Led::green()
{
	digitalWrite(pinBlue,LOW); 
    digitalWrite(pinRed,LOW);  
    digitalWrite(pinGreen,HIGH);
}

void Led::yellow()
{
	digitalWrite(pinBlue,LOW); 
    digitalWrite(pinRed,HIGH); 
    digitalWrite(pinGreen,HIGH); 
}

void Led::light_blue()
{
	digitalWrite(pinBlue,HIGH); 
    digitalWrite(pinRed,LOW); 
    digitalWrite(pinGreen,HIGH);
}

void Led::pink()
{
	digitalWrite(pinBlue,HIGH); 
    digitalWrite(pinRed,HIGH); 
    digitalWrite(pinGreen,LOW);
}

void Led::white()
{
	digitalWrite(pinBlue,HIGH); 
    digitalWrite(pinRed,HIGH);  
    digitalWrite(pinGreen,HIGH);
}
/*-------------------------------------------------------------------*/

/* Class Battery ----------------------------------------------------*/
Battery::Battery(int pinBattery):
pinBattery(pinBattery)
{}

float Battery::test()
{
	float analog_value = analogRead(pinBattery);
	return resolutionADC * analog_value;
}

int Battery::testLevel()
{
	float V = analogRead(pinBattery)*resolutionADC;
	if(V > 3.2f)
		return 0;
	else if(3.1f < V && V < 3.2f)
		return 1;
	else if(V < 3.0f)
		return 2;
}
/*-------------------------------------------------------------------*/

/* Class Reflective -------------------------------------------------*/
Reflective::Reflective(int pinDR, int pinDL):
pinDR(pinDR), pinDL(pinDL)
{}

//void setup(){}

bool Reflective::isLineDR()
{
  return (analogRead(pinDR) > 500);
}

bool Reflective::isLineDL()
{
  return (analogRead(pinDL) > 500); 
}

/*-------------------------------------------------------------------*/

/* Class Engines ----------------------------------------------------*/
Engines::Engines(int pinR1, int pinR2, int pinL1, int pinL2, int pwmER, int pwmEL) : 
pinRight1(pinR1), pinRight2(pinR2), pinLeft1(pinL1), pinLeft2(pinL2),
pwmER(pwmER), pwmEL(pwmEL), reflectives(A0,A1)
{}

void Engines::setup()
{
	pinMode(pinRight1, OUTPUT);
	pinMode(pinRight2, OUTPUT);
	pinMode(pinLeft1, OUTPUT);
	pinMode(pinLeft2, OUTPUT);
}

void Engines::test()
{
	// 1.- Both engines rotate forward
	analogWrite(pinRight1,pwmER);
	analogWrite(pinRight2,0);
	analogWrite(pinLeft1,pwmEL);
	analogWrite(pinLeft2,0);
	delay(1000);
	analogWrite(pinRight1,0);
	analogWrite(pinRight2,0);
	analogWrite(pinLeft1,0);
	analogWrite(pinLeft2,0);
	delay(1000);
	
	// 2.- Both engines rotate backwards
	analogWrite(pinRight1,0);
	analogWrite(pinRight2,pwmER);
	analogWrite(pinLeft1,0);
	analogWrite(pinLeft2,pwmEL);
	delay(1000);
	analogWrite(pinRight1,0);
	analogWrite(pinRight2,0);
	analogWrite(pinLeft1,0);
	analogWrite(pinLeft2,0);
	delay(1000);
	
	// 3.- Both engines rotate in different directions
	analogWrite(pinRight1,pwmER);
	analogWrite(pinRight2,0);
	analogWrite(pinLeft1,0);
	analogWrite(pinLeft2,pwmEL);
	delay(1000);
	analogWrite(pinRight1,0);
	analogWrite(pinRight2,0);
	analogWrite(pinLeft1,0);
	analogWrite(pinLeft2,0);
  	delay(1000);
	
}

void Engines::goForw()
{
	analogWrite(pinRight1,pwmER);
	analogWrite(pinRight2,0);
	analogWrite(pinLeft1,pwmEL);
	analogWrite(pinLeft2,0);

	/*while(!reflectives.isLineDR() && !reflectives.isLineDL());
	if(reflectives.isLineDR())
	{	
		stop_right();
		while(!reflectives.isLineDL());
		stop_all();
	}
	else if(reflectives.isLineDL())
	{
		stop_left();
		while(!reflectives.isLineDR());
		stop_all();
	}

  delay(500);

  analogWrite(pinRight1,pwmER);
  analogWrite(pinRight2,0);
  analogWrite(pinLeft1,pwmEL);
  analogWrite(pinLeft2,0);*/
  
  delay(1500);

  stop_all();

}

void Engines::pivot(int dir)
{
	if(dir == 0) 
	{ // pivot left
		analogWrite(pinRight1,pwmER);
		analogWrite(pinRight2,0);
		analogWrite(pinLeft1,0);
		analogWrite(pinLeft2,pwmEL);

		delay(600);

		analogWrite(pinRight1,0);
		analogWrite(pinRight2,0);
		analogWrite(pinLeft1,0);
		analogWrite(pinLeft2,0);
	}
	else if (dir == 1) 
	{ // pivot right
		analogWrite(pinRight1,0);
		analogWrite(pinRight2,pwmER);
		analogWrite(pinLeft1,pwmEL);
		analogWrite(pinLeft2,0);

		delay(600);

		analogWrite(pinRight1,0);
		analogWrite(pinRight2,0);
		analogWrite(pinLeft1,0);
		analogWrite(pinLeft2,0);
	}
	else if (dir == 2) 
	{ // pivot front
		analogWrite(pinRight1,0);
		analogWrite(pinRight2,pwmER);
		analogWrite(pinLeft1,pwmEL);
		analogWrite(pinLeft2,0);

		delay(1100);

		analogWrite(pinRight1,0);
		analogWrite(pinRight2,0);
		analogWrite(pinLeft1,0);
		analogWrite(pinLeft2,0);
	}
}

void Engines::stop_right()
{
	analogWrite(pinRight1,0);
	analogWrite(pinRight2,0);
	analogWrite(pinLeft1,pwmEL);
	analogWrite(pinLeft2,0);
}

void Engines::stop_left()
{
	analogWrite(pinRight1,pwmER);
	analogWrite(pinRight2,0);
	analogWrite(pinLeft1,0);
	analogWrite(pinLeft2,0);
}

void Engines::stop_all()
{
	analogWrite(pinRight1,0);
	analogWrite(pinRight2,0);
	analogWrite(pinLeft1,0);
	analogWrite(pinLeft2,0);
}

int Engines::finish()
{
	if(/*reflectives.isLineDR() &&*/ reflectives.isLineDL())
		return 1;
	else 
		return 0;
}
/*-------------------------------------------------------------------*/

/* Class Servo ------------------------------------------------------*/
myServo::myServo(int pin):
pinServo(pin)
{}

void myServo::setup()
{
    servo.attach(this->pinServo);
}

void myServo::test()
{
     servo.write(0);
     delay(1000);
     servo.write(180);
     delay(1000);
     servo.write(90);
     delay(1000);
     servo.write(0);
}

void myServo::goTo(int degree)
{
    servo.write(degree);
}
/*-------------------------------------------------------------------*/

/* Class Sharp ------------------------------------------------------*/
Sharp::Sharp(int pinSharp, int pinServo) : 
pinSharp(pinSharp), servo(pinServo)
{}

void Sharp::setup()
{
	servo.setup();
}

void Sharp::test()
{
	servo.test();
	int sharpAnalogValue;
	float sharpVoltage;
	for(int i=0; i<5; ++i)
	{
		sharpAnalogValue = analogRead(pinSharp);
		sharpVoltage = sharpAnalogValue * resolutionADC;
		// print(sharpVoltage)
		delay(1000);
	}
}

int Sharp::lookLeft()
{
	servo.goTo(180); // CAMBIAR A IZQUIERDA
	delay(1000); // Wait for servo to take position
	float sharpVoltage = analogRead(pinSharp)*resolutionADC;
	servo.goTo(90); // CAMBIAR A FRENTE
	if( sharpVoltage > 0.5f)
	{ // Distance less than 20cm
		return 1;
	}
	else 
		return 0;
}

int Sharp::lookRight()
{
	servo.goTo(0); // CAMBIAR A DERECHA
	delay(1000); // Wait for servo to take position
	float sharpVoltage = analogRead(pinSharp)*resolutionADC;
	servo.goTo(90); // CAMBIAR A FRENTE
	if( sharpVoltage > 0.5f)
	{ // Distance less than 20cm
		return 1;
	}
	else 
		return 0;
}

int Sharp::lookFront()
{
	servo.goTo(90); // CAMBIAR A FRENTE
	delay(1000); // Wait for servo to take position
	float sharpVoltage = analogRead(pinSharp)*resolutionADC;
	if( sharpVoltage > 0.5f)
	{ // Distance less than 20cm
		return 1;
	}
	else 
		return 0;
}
/* ------------------------------------------------------------------*/
