#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <ros.h>
#include <std_msgs/UInt16.h>

#include <Stepper.h>




// Number of steps per output rotation
const int stepsPerRevolution = 200;

int sw = 6;
int state = 0;
int end_message =0; //끝날 때 보내는 메세지

//unsigned long prev_time = 0;

// Create Instance of Stepper library
Stepper doorStepper(stepsPerRevolution, 5, 4, 3, 2);
Stepper conStepper(stepsPerRevolution, 10, 9, 8, 7);


void opendoor() // 문 열기
{
  doorStepper.step(200);
  delay(1000); //1초
  doorStepper.step(0);

}

void landbox() // 물건 내리기
{
  conStepper.step(600);
  delay(1000);
  conStepper.step(0);
}

void closedoor() // 문 닫기
{
  doorStepper.step(-200);
  delay(1000);
  doorStepper.step(0);
}

void setup()
{

  Serial.begin(9600);
  delay(20);
  state = 0;

  // set the speed at 20 rpm:
  doorStepper.setSpeed(20);
  conStepper.setSpeed(20);


  pinMode(sw, INPUT_PULLUP);


}

void loop()
{ 

delay(1000);
Serial.println('1');
}