//---------라이브러리들--------

#include <Servo.h> 
#include <time.h>

//---------초기 선언들---------


//입출력 핀들
const int pin_Led = 8; //LED 제어할 핀
const int pin_Servo = 9; //서보를 제어할 핀

const int pin_BrightSensor = A0; //밝기 센서를 감지할 핀
const int pin_Button = 7; //버튼을 감지할 핀
//변수들
int flag_led = LOW; //LED 제어 상태
int value_bright = 0; //밝기 센서 감지 상태
int angle_servo0 = 0; //서보 제어 상태

int rate_time = 0; // 남은 시간

//객체들
Servo servo0;

//---------기능 함수들---------

//---------메인 함수들---------
void setup() {
  Serial.begin(9600);
  //다음 핀들을 제어/감지 용도로 설정함
  pinMode(pin_Led, OUTPUT); 
  pinMode(pin_Button, INPUT); 
  servo0.attach(pin_Servo);
}

void loop() {

  //LED에게 현재 제어상태를 적용함
  digitalWrite(pin_Led, flag_led); 
  value_bright = analogRead(pin_BrightSensor);
  //서보에게 현재 제어상태를 적용함
  servo0.write(angle_servo0);

  //알람을 1초 증가시킴
  if (digitalRead(pin_Button) == HIGH)
  {
    while (digitalRead(pin_Button) == HIGH);
    rate_time += 1000;
  }

  //버튼의 상태에따라 LED제어를 바꿈
  if (value_bright < 150)
  {
    flag_led = HIGH;
    angle_servo0 = 180;
  }
  else
  {
    flag_led = LOW;
    angle_servo0 = 0;
  }
  
  delay(1);
  if (rate_time > 0) rate_time -= 1;
  else if (rate_time == 0)
  {
    //do something
    rate_time -= 1;
  }
  
}
