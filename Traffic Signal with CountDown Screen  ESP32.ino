#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// LED pins
const int RED_PIN    = 25;
const int YELLOW_PIN = 26;
const int GREEN_PIN  = 27;

// I2C pins
const int SDA_PIN = 21;
const int SCL_PIN = 22;

// Timings (milliseconds) — change as needed
unsigned long GREEN_TIME  = 6000; // green duration
unsigned long YELLOW_TIME = 2000; // yellow duration
unsigned long RED_TIME    = 6000; // red duration

enum TrafficState { STATE_GREEN, STATE_YELLOW, STATE_RED };
TrafficState state = STATE_GREEN;

unsigned long stateStart = 0;

void setup() {
  Serial.begin(115200);

  // LED outputs
  pinMode(RED_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  // ensure all off initially
  digitalWrite(RED_PIN, LOW);
  digitalWrite(YELLOW_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);

  // start I2C with explicit pins
  Wire.begin(SDA_PIN, SCL_PIN);

  // init OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // don't proceed, loop forever
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("Traffic Signal Starting...");
  display.display();
  delay(800);

  // start with green
  state = STATE_GREEN;
  stateStart = millis();
  updateOutputs();   // set LED pins for initial state
}

void loop() {
  unsigned long now = millis();
  unsigned long elapsed = now - stateStart;
  unsigned long stateDuration = getStateDuration(state);

  // transition if needed
  if (elapsed >= stateDuration) {
    // move to next state
    switch (state) {
      case STATE_GREEN:  state = STATE_YELLOW; break;
      case STATE_YELLOW: state = STATE_RED;    break;
      case STATE_RED:    state = STATE_GREEN;  break;
    }
    stateStart = now;
    updateOutputs();
  }

  // update OLED (countdown and simple indicator)
  updateDisplay(now);

  // small delay so OLED & serial aren't spammed
  delay(100);
}

unsigned long getStateDuration(TrafficState s) {
  switch (s) {
    case STATE_GREEN:  return GREEN_TIME;
    case STATE_YELLOW: return YELLOW_TIME;
    case STATE_RED:    return RED_TIME;
  }
  return GREEN_TIME;
}

void updateOutputs() {
  // turn on only the LED corresponding to the state
  digitalWrite(GREEN_PIN, (state == STATE_GREEN) ? HIGH : LOW);
  digitalWrite(YELLOW_PIN, (state == STATE_YELLOW) ? HIGH : LOW);
  digitalWrite(RED_PIN, (state == STATE_RED) ? HIGH : LOW);

  // debug
  Serial.print("State -> ");
  if (state == STATE_GREEN)  Serial.println("GREEN");
  if (state == STATE_YELLOW) Serial.println("YELLOW");
  if (state == STATE_RED)    Serial.println("RED");
}

void updateDisplay(unsigned long now) {
  unsigned long elapsed = now - stateStart;
  unsigned long duration = getStateDuration(state);
  long remaining_ms = (long)duration - (long)elapsed;
  if (remaining_ms < 0) remaining_ms = 0;
  int remaining_s = (remaining_ms + 500) / 1000; // rounded seconds

  display.clearDisplay();

  // Title
  display.setTextSize(2);
  display.setCursor(0,0);

  if (state == STATE_GREEN) {
    display.println("GREEN");
  } else if (state == STATE_YELLOW) {
    display.println("YELLOW");
  } else {
    display.println("RED");
  }

  // Countdown
  display.setTextSize(1);
  display.setCursor(0, 30);
  display.print("Remaining: ");
  display.print(remaining_s);
  display.println(" s");

  // draw simple LED indicators: filled circles
  int cx = 95;
  int cy = 12;
  int r = 8;
  // red circle
  display.drawCircle(cx, cy, r, SSD1306_WHITE);
  display.drawCircle(cx, cy + 22, r, SSD1306_WHITE);
  display.drawCircle(cx, cy + 44, r, SSD1306_WHITE);

  // fill the active one
  if (state == STATE_RED) {
    // fill top (red)
    for (int y=-r; y<=r; y++) for (int x=-r; x<=r; x++) {
      if (x*x + y*y <= r*r) display.drawPixel(cx + x, cy + y, SSD1306_WHITE);
    }
  } else if (state == STATE_YELLOW) {
    for (int y=-r; y<=r; y++) for (int x=-r; x<=r; x++) {
      if (x*x + y*y <= r*r) display.drawPixel(cx + x, cy + 22 + y, SSD1306_WHITE);
    }
  } else if (state == STATE_GREEN) {
    for (int y=-r; y<=r; y++) for (int x=-r; x<=r; x++) {
      if (x*x + y*y <= r*r) display.drawPixel(cx + x, cy + 44 + y, SSD1306_WHITE);
    }
  }

  display.display();
}
