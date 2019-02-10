//---------초기 선언들---------

//입출력 핀들
const int pin_Led = 8; //LED 제어할 핀
const int pin_Button = 7; //버튼을 감지할 핀

//변수들
int flag_led = LOW; //LED 제어 상태

//---------기능 함수들---------

//---------메인 함수들---------
void setup() {

  //다음 핀들을 제어/감지 용도로 설정함
  pinMode(pin_Led, OUTPUT); 
  pinMode(pin_Button, INPUT);
}

void loop() {

  //LED에게 현재 제어상태를 적용함
  digitalWrite(pin_Led, flag_led); 

  //버튼의 상태에따라 LED제어를 바꿈
  if (digitalRead(pin_Button) == HIGH)
  {
    flag_led = HIGH;
  }
  else
  {
    flag_led = LOW;
  }
  
}
