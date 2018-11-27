//---------라이브러리들--------

#include <Servo.h> 

//---------초기 선언들---------


//입출력 핀들
const int pin_Led = 8; //LED 제어할 핀
const int pin_Servo = 9; //서보를 제어할 핀

const int pin_BrightSensor = A0; //밝기 센서를 감지할 핀

//변수들
int flag_led = LOW; //LED 제어 상태
int flag_bright = 0; //밝기 센서 감지 상태
int flag_servo0_angle = 0; //서보 제어 상태

//객체들
Servo servo0;

//---------기능 함수들---------

//---------메인 함수들---------
void setup() {
  //다음 핀들을 제어/감지 용도로 설정함
  pinMode(pin_Led, OUTPUT); 
  servo0.attach(pin_Servo);
}

void loop() {

  //LED에게 현재 제어상태를 적용함
  digitalWrite(pin_Led, flag_led); 
  flag_bright = analogRead(pin_BrightSensor);
  //서보에게 현재 제어상태를 적용함
  servo0.write(flag_servo0_angle);
  
  //밝기 센서의 상태에따라 LED제어를 바꿈
  if (flag_bright < 150)
  {
    flag_led = HIGH;
    flag_servo0_angle = 180;
  }
  else
  {
    flag_led = LOW;
    flag_servo0_angle = 0;
  }
  
}
