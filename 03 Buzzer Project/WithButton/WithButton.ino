//---------초기 선언들---------

//입출력 핀들
const int pin_Buzzer = 10; //부저를 제어할 핀

const int pin_ButtonBuzzer = 4; //버튼(부저)을 감지할 핀

//변수들

//상수들

//재생 속도
float bpm = 0.7f;

//음표 정보를 담은 배열
int list_tone[] = {880, 998, 1046, 1568, 1319, 880, 880, 880, 880, 1047, 880, 880, 880, 880, 1319, 1175, 880, 880, 880, 880, 1047, 880, 880, 880, 880};

//박자 정보를 담은 배열
int list_dur[] =  {300, 200, 1000,  800,  500, 230, 230, 230, 230,  500, 230, 230, 230, 230,  250, 1000, 230, 230, 230, 230,  500, 230, 230, 230, 230};


//구조체들


//---------기능 함수들---------

//---------메인 함수들---------
void setup() {

  //사용할 핀들의 용도를 제어/감지로 설정함
  pinMode(pin_Buzzer, OUTPUT); 
  pinMode(pin_ButtonBuzzer, INPUT);
}

void loop() {

  //버튼의 상태가 활성화 됐다면
  if (digitalRead(pin_ButtonBuzzer) == HIGH)
  {
    //버튼의 활성화가 끝날 때까지 대기
    while (digitalRead(pin_ButtonBuzzer) == HIGH)
    {
      delay(100);
    }

    //부저를 제어함
   
    for (int i = 0; i < sizeof list_tone / sizeof list_tone[0]; ++i)
    {
      tone(pin_Buzzer, list_tone[i]);
      delay(bpm * list_dur[i]);
      noTone(pin_Buzzer);
    }   

  }
}
