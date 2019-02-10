//---------라이브러리들--------

#include <SoftwareSerial.h>

//---------초기 선언들---------

//입출력 핀들
const int pin_Motor = 12; //모터 제어할 핀
const int pin_HeatSensor = A0; //온도 센서를 감지할 핀

//변수들
int flag_motor = LOW; //모터 제어 상태

//객체들
SoftwareSerial bluetooth0(2, 3); //블루투스와 연결할 핀

//---------기능 함수들---------

//---------메인 함수들---------
void setup() {

  //다음 핀들을 제어/감지 용도로 설정함
  pinMode(pin_Motor, OUTPUT); 
  pinMode(pin_HeatSensor, INPUT); 
}

void loop() {

  bluetooth0.begin(9600);
  //모터에게 현재 제어상태를 적용함
  digitalWrite(pin_Motor, flag_motor); 
  
  while (bluetooth0.available())//블루투스를 기다림
  {
    char c = bluetooth0.read();//블루투스가 보낸 값을 char로 저장함
    switch (c)
    {
      case 'a':
        flag_motor = HIGH;
        break;
      case 'd':
        delay(1000);
        break;
      case 's':
        flag_motor = LOW;
        break;
      case 'g':
        bluetooth0.println((analogRead(pin_HeatSensor) * 5.0 / 1024 - 0.5) * 100);
        break;
    }
  }
  
}
