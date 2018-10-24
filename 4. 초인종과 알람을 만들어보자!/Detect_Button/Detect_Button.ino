unsigned int P_led = 8;
unsigned int P_bulb = 9;
unsigned int P_buzzer = 10;
unsigned int P_senser_light = A0;
unsigned int P_senser_bio = 2;
unsigned int P_senser_button = 3;

bool C_led_auto = true;

int D_sense_light;
int D_sense_bio;
int D_sense_button;

int V_buzzer_lifetime = 0;

void setup() {
  Serial.begin(9600);
  pinMode(P_led, OUTPUT);
  pinMode(P_bulb, OUTPUT);
  pinMode(P_buzzer, OUTPUT);
  pinMode(P_senser_light, INPUT);
  pinMode(P_senser_bio, INPUT);
  pinMode(P_senser_button, INPUT);
  pinMode(P_bulb, INPUT);
  digitalWrite(P_led, HIGH);
}

void loop() {
    if (Serial.available())
    {
        String read_line = Serial.readString();
        if (read_line == "led on")
        {
          Serial.println("OK");
          digitalWrite(P_led, HIGH);
          C_led_auto = false;
        }
        else if (read_line == "led off")
        {
          Serial.println("OK");
          digitalWrite(P_led, LOW);
          C_led_auto = false;
        }
        else if (read_line == "led auto")
        {
          Serial.println("OK");
          C_led_auto = true;
        }
        else if (read_line == "bulb on")
        {
          Serial.println("OK");
          digitalWrite(P_bulb, HIGH);
        }
        else if (read_line == "bulb off")
        {
          Serial.println("OK");
          digitalWrite(P_bulb, LOW);
        }
        else
        {
          Serial.print("Sorry That isn;t command : ");
          Serial.println(read_line);
        }
    }
  
    D_sense_light =  analogRead(P_senser_light);
    D_sense_bio = digitalRead(P_senser_bio);    
    D_sense_button = digitalRead(P_senser_button);

    if (D_sense_button == HIGH)
    {
      V_buzzer_lifetime = 600;
    }
    
    if (V_buzzer_lifetime > 0)
    {
      if (V_buzzer_lifetime > 300)
      {
        tone(P_buzzer, 210);
      }
      else
      {
        tone(P_buzzer, 410);
      }
      --V_buzzer_lifetime;
      delay(1);
    }
    else
    {
      noTone(P_buzzer);
    }

    

    if (C_led_auto)
    {
      if (D_sense_bio == HIGH)
      {
          digitalWrite(P_led, LOW);
      }
      else
      {
          digitalWrite(P_led, HIGH);
      }
    }
}
