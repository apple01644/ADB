//---------초기 선언들---------
#include <Servo.h> 

//입출력 핀들
const int pin_ButtonServoMotor = 5; //버튼(서보모터)을 감지할 핀

const int pin_ServoMotor = 9; //서보모터 제어할 핀

//변수들

int flag_servo = LOW;

//상수들

//구조체들

Servo servo0; 

//---------기능 함수들---------

//---------메인 함수들---------
void setup() {

  //사용할 핀들의 용도를 제어/감지로 설정함
  pinMode(pin_ButtonServoMotor, INPUT);
  
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
  
  //버튼의 상태가 활성화 됐다면
  if (digitalRead(pin_ButtonServoMotor) == HIGH)
  {
    //서보모터의 제어 상태를 바꿈
    flag_servo = flag_servo == HIGH ? LOW : HIGH;
    
    //버튼의 활성화가 끝날 때까지 대기
    while (digitalRead(pin_ButtonServoMotor) == HIGH)
    {
      delay(100);
    }
  }
}
