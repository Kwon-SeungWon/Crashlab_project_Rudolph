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
{ while (true) 
{
    //unsigned long now_time = millis();

    state = Serial.read();
    Serial.write(end_message);
    end_message=0;

    int button_state = digitalRead(sw);

    /*if(now_time - prev_time >=500)
    {
      prev_time=now_time;
      
    }*/





    if (state == 0) //-> 기본 상태
    {
      continue;
    }


    if (state == 1) //-> 경유지 동작
    {
      opendoor();
      if (button_state == 0)
      {
        closedoor();
        state = 0;
        end_message=1;
      }
    }

    if (state == 2) //->도착지(직접 수령) 동작
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
    if (state == 3) //->state = 3 ->도착지(비대면 수령)
    {
      opendoor();
      landbox();
      closedoor();
      state = 0;
      end_message=1;
    }
  }
}


//state = 0 -> 기본, state = 1 -> 경유지, state = 2 ->도착지(직접 수령) , state = 3 ->도착지(비대면 수령)

/*#sudo code

  open_door()
  land_box()
  close_door()


  while True:
    state = 시리얼()
    sleep.(1)

    if state == 0:
        # 경유지
        open_door()
        if button == 1:
            close_door()

    if state == 1:
        # 도착지
        open_door()
        land_box()
        close_door()*/