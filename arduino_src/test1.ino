
//문, 컨베이어 동작 아두이노 코드. 라파와 통신


#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif //현재 아두이노 버전 적용

#include <ros.h>
#include <std_msgs/UInt16.h>

#include <Stepper.h> 

#include <SoftwareSerial.h>

//#define PIN_TX 2
//#define PIN_RX 3

//SoftwareSerial SerialROS(PIN_TX, PIN_RX);




// Number of steps per output rotation 360도 회전에 필요한 스탭 수
const int stepsPerRevolution = 200;

int sw =12 ;
char state ;
int end_message =0; //끝날 때 보내는 메세지
int main_process = 0;

//unsigned long prev_time = 0;

// Create Instance of Stepper library !!!!두 스탭의 핀 번호가 서로 뒤바뀌었는 지 확인 필요!!!!
Stepper doorStepper(stepsPerRevolution, 11, 10, 9, 8);
Stepper conStepper(stepsPerRevolution, 7, 6, 5, 4);


void opendoor() // 문 열기 
{
  doorStepper.step(100);
  delay(400);
  doorStepper.step(0);
  delay(100);

}

void landbox() // 물건 내리기
{
  conStepper.step(1000); 
  delay(1000);
  conStepper.step(0);
  delay(100);
}

void closedoor() // 문 닫기
{
  doorStepper.step(-100);
  delay(400);
  doorStepper.step(0);
  delay(100);
}

void setup()
{

  //Serial.begin(9600);
  Serial.begin(9600);
  delay(20); //통신 간격


  // set the speed at 20 rpm:
  doorStepper.setSpeed(60);
  conStepper.setSpeed(60);


  pinMode(sw, INPUT_PULLUP); //버튼 핀 풀업


}

void loop()
{ while (true) 
{
    //unsigned long now_time = millis();

    state = Serial.read(); //라파 시리얼 받기
    //Serial.write(end_message);
    end_message=0;

    int button_state = digitalRead(sw); //버튼 상태. 풀업상태이므로 기본 1, 누를 때 0

    delay(10);
    Serial.println('0');


    if (state == 'a') //-> 기본 상태
    {
      continue;
    }


    if (state == 'b')  // 경유지 동작 -> 문이 열리고 버튼을 누르면 문이 닫힘. 이후 라파에 end_message 전송
    {
      if (main_process == 0)
      {
        opendoor();
      }
      else if (main_process == 1)
      {
        if (button_state == 0)
        {
        closedoor();
        state = 'a';
        //end_message=0;
        Serial.println('1');
        }
      }
      main_process = 1;
    }

    if (state == 'c') // 도착지(직접 수령) 동작 -> 문이 열리고 컨베이어가 작동. 버튼이 눌리면 문이 닫히고 라파에  end_message 전송
    {
      if (main_process == 1)
      {
      opendoor();
      landbox();
      }
      if (main_process == 2)
      {
        if (button_state == 0)
        {
        closedoor();
        state = 'a';
        //end_message=1;
        Serial.println('2');
        }
      }
      main_process = 2;
    }
    if (state == 'd') // 도착지(비대면 수령) 문이 열리고 컨베이어가 작동. 이후 문이 닫히고 라파에 end_message 전송
    {
      if (main_process == 1)
      {
      opendoor();
      landbox();
      closedoor();
      }
      if (main_process == 2)
      {
      state = 'a';
      //end_message=2;
      Serial.println('3');
      }
      main_process= 2;
    }
  }
}
