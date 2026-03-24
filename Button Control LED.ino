// C++ code
//
int read_digital_pin_ = 0;

int button = 0;

void setup()
{
  pinMode(13, INPUT);
  pinMode(4, OUTPUT);
}

void loop()
{
  button = digitalRead(13);
  if (button == HIGH) {
    digitalWrite(4, HIGH);
  } else {
    digitalWrite(4, LOW);
  }
  delay(10); // Delay a little bit to improve simulation performance
}
