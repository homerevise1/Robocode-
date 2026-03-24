#include <IRremote.hpp>

int IR_PIN = 6;

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK); 

  Serial.println("IR Ready... Press any remote button");
}

void loop() {
  if (IrReceiver.decode()) {

    Serial.print("HEX value: ");
    Serial.println(IrReceiver.decodedIRData.command, HEX);

    IrReceiver.resume();
  }
}
