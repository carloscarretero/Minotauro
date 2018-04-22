
#ifndef COMPONENTS_H_
#define COMPONENTS_H_
	
#include <Arduino.h>
#include <Servo.h>
#include <stdlib.h>


const float resolutionADC = 0.00488;

class myBluetooth
{
	public:
		myBluetooth();
		void setup();
		void test();
		void sendText(const char* text);
		void sendMaze(int i, int j);
		void sendWall(int pos);
};

class mySerial
{
	public:
		mySerial();
		void setup();
		void test();
		void sendText(const char* text);
		void sendMaze(int i, int j);
		void sendWall(int pos);
};

class Led
{
  public:
    	Led(int pinB, int pinR, int pinG);
    	void setup();
    	void test();
   	 	void no_color();
	    void red();
	    void blue();
	    void green();
	    void yellow();
	    void light_blue();
	    void pink();
	    void white();
  private:
  		int pinRed, pinBlue, pinGreen;
};

class Battery
{
	public:
		Battery(int pinBattery);
		//void setup();
		float test();
		int testLevel();
	private:
		int pinBattery;
};

class Reflective
{
  public:
    Reflective(int pinDR, int pinDL);
    //void test();
    bool isLineDR();
    bool isLineDL();
  private:
    int pinDR, pinDL;
};

class Engines

{
	public:
		Engines(int pinR1, int pinR2, int pinL1, int pinL2, int pwmER, int pwmEL);
		void setup();
		void test();
		void goForw(/*...*/);
		void pivot(int dir);
		void stop_right();
		void stop_left();
		void stop_all();
	private:
		int pinRight1, pinRight2,
			pinLeft1, pinLeft2,
			pwmER, pwmEL;
		 Reflective reflectives;
};

class myServo
{
	public:
		myServo(int pin);
    	void setup();
		void test();
		void goTo(int degree);
	private:
		int pinServo;
		Servo servo;
};

class Sharp
{
	public:
		Sharp(int pinSharp, int pinServo);
		void setup();
		void test();
		int lookLeft();
		int lookRight();
		int lookFront();
		// 1-Muro, 0-No muro
	private:
		int pinSharp;
    	myServo servo;
};

#endif
