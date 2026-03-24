// Moisture Sensor with LED Indicator

int moisture = 0;

void setup() {
  Serial.begin(9600);

  pinMode(A0, OUTPUT);   // Power pin for sensor
  pinMode(A1, INPUT);    // Moisture analog input

  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
}

void loop() {

  digitalWrite(A0, HIGH);     // Turn sensor ON
  delay(10);                  // Wait 10 ms

  moisture = analogRead(A1);  // Read moisture value

  digitalWrite(A0, LOW);      // Turn sensor OFF

  Serial.println(moisture);   // Print value to Serial Monitor

  // Turn OFF all LEDs first
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);

  // Moisture level conditions
  if (moisture < 200) {
    digitalWrite(12, HIGH);
  }
  else if (moisture < 400) {
    digitalWrite(11, HIGH);
  }
  else if (moisture < 600) {
    digitalWrite(10, HIGH);
  }
  else if (moisture < 800) {
    digitalWrite(9, HIGH);
  }
  else {
    digitalWrite(8, HIGH);
  }

  delay(100);   // Wait 100 ms
}

