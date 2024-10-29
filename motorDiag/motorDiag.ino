#include <AFMotor.h>
#define NUM_MOTORS 3

AF_DCMotor head(1, MOTOR12_1KHZ);
AF_DCMotor mouth(2, MOTOR12_1KHZ);
AF_DCMotor tail(3, MOTOR34_1KHZ);

AF_DCMotor motors[NUM_MOTORS] = {head, mouth, tail};
void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor test!");
  for (int i = 0; i < NUM_MOTORS; i++) {
    motors[i].setSpeed(255);
  }
}

void runMotorOnOff(AF_DCMotor motor, int animationDelay = 500) {
  motor.run(FORWARD);
  delay(animationDelay);
  motor.run(BACKWARD);
  delay(5);
  motor.run(RELEASE);
  delay(animationDelay / 2);
}

void loop() {
  runMotorOnOff(head, 1000);
  runMotorOnOff(mouth, 500);
  runMotorOnOff(tail, 1000);
}
