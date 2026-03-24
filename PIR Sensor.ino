// C++ code
//
int pir = 0;

void setup()
{
  pinMode(2, INPUT);
  Serial.begin(9600);
  pinMode(4, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  pir = digitalRead(2);
  Serial.println(pir);
  delay(100); // Wait for 100 millisecond(s)
  if (pir < HIGH) {
    digitalWrite(4, HIGH);
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(4, LOW);
    digitalWrite(LED_BUILTIN, HIGH);
  }
}
