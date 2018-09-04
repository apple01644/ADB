unsigned int P_led = 2;
unsigned int P_senser_light = A0;

bool C_led_auto = true;

int D_sense_light;

void setup() {
  Serial.begin(9600);
  pinMode(P_led, OUTPUT);
  pinMode(P_senser_light, INPUT);
  digitalWrite(P_led, HIGH);
}

void loop() {
    if (Serial.available())
    {
        String read_line = Serial.readString();
        Serial.println(read_line);
        if (read_line == "led on")
        {
          digitalWrite(P_led, HIGH);
          C_led_auto = false;
        }
        else if (read_line == "led off")
        {
          digitalWrite(P_led, LOW);
          C_led_auto = false;
        }
        else if (read_line == "led auto")
        {
          C_led_auto = true;
        }

    }
  
    D_sense_light =  analogRead(P_senser_light);

    if (C_led_auto)
    {
      if (D_sense_light > 650)
      {
          digitalWrite(P_led, LOW);
      }
      else
      {
          digitalWrite(P_led, HIGH);
      }
    }
}
