unsigned int P_led = 2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(P_led, OUTPUT);
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
        }
        else if (read_line == "led off")
        {
          digitalWrite(P_led, LOW);
        }

    }
}
