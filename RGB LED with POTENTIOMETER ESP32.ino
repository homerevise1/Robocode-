#define POT_PIN 34   
#define RED_PIN 23   
#define GREEN_PIN 17 
#define BLUE_PIN 16   

void setup() {
  Serial.begin(115200);
  ledcAttach(RED_PIN, 5000, 8);   
  ledcAttach(GREEN_PIN, 5000, 8);
  ledcAttach(BLUE_PIN, 5000, 8);
}

void loop() {
  int potValue = analogRead(POT_PIN);
  int hue = map(potValue, 0, 4095, 0, 359);

  int red, green, blue;
  hueToRGB(hue, &red, &green, &blue);

  ledcWrite(RED_PIN, 255 - red);
  ledcWrite(GREEN_PIN, 255 - green);
  ledcWrite(BLUE_PIN, 255 - blue);

  // Debug output
  Serial.print("Pot: "); Serial.print(potValue);
  Serial.print(" Hue: "); Serial.print(hue);
  Serial.print(" RGB: ("); Serial.print(red); Serial.print(", ");
  Serial.print(green); Serial.print(", "); Serial.println(blue);
  delay(50);
}

// Same HSV to RGB converter
void hueToRGB(int hue, int* r, int* g, int* b) {
  float h = (float)hue / 60.0;
  float c = 255.0;
  float x = c * (1.0 - fabs(fmod(h, 2.0) - 1.0));
  float m = 0;
  float rr, gg, bb;

  if (h >= 0 && h < 1) { rr = c; gg = x; bb = 0; }
  else if (h >= 1 && h < 2) { rr = x; gg = c; bb = 0; }
  else if (h >= 2 && h < 3) { rr = 0; gg = c; bb = x; }
  else if (h >= 3 && h < 4) { rr = 0; gg = x; bb = c; }
  else if (h >= 4 && h < 5) { rr = x; gg = 0; bb = c; }
  else { rr = c; gg = 0; bb = x; }

  *r = (int)(rr + m);
  *g = (int)(gg + m);
  *b = (int)(bb + m);
}

