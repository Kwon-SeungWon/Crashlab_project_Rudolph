//아두이노 문, 컨베이어 동작 코드. 라파와 통신


#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif  //아두이노 현재 버전 자동 적용

#include <ros.h>
#include <std_msgs/UInt16.h>

#include <Stepper.h> 




// Number of steps per output rotation
const int stepsPerRevolution = 200;

int sw = 6;
char state ;
int end_message =0; //동작이 끝날 때 보내는 메세지

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
  delay(20); //통신 간격


  // set the speed at 20 rpm:
  doorStepper.setSpeed(20);
  conStepper.setSpeed(20);


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

    delay(100);

    /*if(now_time - prev_time >=500)
    {
      prev_time=now_time;
      
    }*/





    if (state == 'a') //-> 기본 상태
    {
      continue;
    }


    if (state == 'b') // 경유지 동작 -> 문이 열리고 버튼을 누르면 문이 닫힘. 이후 라파에 end_message 전송
    {
      opendoor();
      if (button_state == 0)
      {
        closedoor();
        state = 0;
        end_message=1;
      }
    }

    if (state == 'c') // 도착지(직접 수령) 동작 -> 문이 열리고 컨베이어가 작동. 버튼이 눌리면 문이 닫히고 라파에  end_message 전송
    {
      opendoor();
      landbox();
      if (button_state == 0)
      {
        closedoor();
        state = 0;
        end_message=1;
      }
    }
    if (state == 'd') // 도착지(비대면 수령) 문이 열리고 컨베이어가 작동. 이후 문이 닫히고 라파에 end_message 전송
    {
      opendoor();
      landbox();
      closedoor();
      state = 0;
      end_message=1;
    }
  }
}