// C++ code
//
#include <Servo.h>

Servo servo_11;

void setup()
{
  servo_11.attach(11, 500, 2500);

  servo_11.write(90);
  delay(1000); // Wait for 1000 millisecond(s)
  servo_11.write(30);
  delay(2000); // Wait for 2000 millisecond(s)
  servo_11.write(180);
  delay(1000); // Wait for 1000 millisecond(s)
}

void loop()
{
  delay(10); // Delay a little bit to improve simulation performance
}
