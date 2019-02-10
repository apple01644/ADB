//---------초기 선언들---------
#include <Servo.h> 

//입출력 핀들
const int pin_BrightSensor = A1; //조도센서를 감지할 핀

const int pin_ServoMotor = 9; //서보모터 제어할 핀

//변수들

int flag_servo = LOW;

//상수들
const int threshold_bright = 40;

//구조체들

Servo servo0; 

//---------기능 함수들---------

//---------메인 함수들---------
void setup() {

  //사용할 핀들의 용도를 제어/감지로 설정함
  pinMode(pin_BrightSensor, INPUT);
  servo0.attach(pin_ServoMotor);
}

void loop() {

  //서보모터에게 현재 제어상태를 적용함
  if (flag_servo == HIGH)
  {
    servo0.write(90);
  }
  else
  {
    servo0.write(180);
  }
  //조도센서의 상태에따라 서보모터제어상태를 바꿈
  if (analogRead(pin_BrightSensor) < threshold_bright)
  {
    flag_servo = HIGH;
  }
  else
  {
    flag_servo = LOW;
  }
}
