#include <AFMotor.h>

#define NUM_MOTORS 3
AF_DCMotor head(1, MOTOR12_1KHZ); // create motor #2, 64KHz pwm
AF_DCMotor mouth(2, MOTOR12_1KHZ); 
AF_DCMotor tail(3, MOTOR34_1KHZ); 


void runMotorOnOff(AF_DCMotor motor, int aniDelay = 500){
      motor.run(FORWARD);
      delay(aniDelay);
      motor.run(BACKWARD);
      delay(5);
      motor.run(RELEASE);
      delay(aniDelay);
}

void runTwoMotorsOnOff(AF_DCMotor motor1, AF_DCMotor motor2, int aniDelay = 500){
      motor1.run(FORWARD);
      motor2.run(FORWARD);
      delay(aniDelay);
      motor1.run(BACKWARD);
      motor2.run(BACKWARD);
      delay(5);
      motor1.run(RELEASE);
      motor2.run(RELEASE);
      delay(aniDelay);
}

bool randomDecisionToTurnOn(int oddsOn) {
  int score = random(1,100);
  return score < oddsOn;
}

void releaseMotor(AF_DCMotor motor) {
  motor.run(BACKWARD);
  delay(15);
  motor.run(RELEASE);
}

void tapTail(int duration, int times=5){
  int iterDuration = duration / times;
  for (int i = 0; i < times; i++) {
     runMotorOnOff(tail, iterDuration);
  }
}
void dance(int duration, int times = 1){
  int elapsedTime = 0;
  int iterDuration = duration / times;
  for (int i = 0; i < times; i++) {
    if(randomDecisionToTurnOn(60)){
      runTwoMotorsOnOff(head, tail, iterDuration);
    } else {
     tapTail(iterDuration/2, times*2);
    }
  }
}

void talk(int duration, int wordCount) {
  int iterDuration = duration / wordCount;
  head.run(FORWARD);
  for (int i = 0; i < wordCount; i++) {
     runMotorOnOff(mouth, iterDuration);
  }
}

AF_DCMotor motors[NUM_MOTORS] = {head, mouth, tail};
void setupFishMotors() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor test!");
  for (int i = 0; i < NUM_MOTORS; i++) {
    motors[i].setSpeed(255);
  }
}

void billySleep(){
  head.run(RELEASE);
  tail.run(RELEASE);
  mouth.run(RELEASE);
}

void moveBilly(int movementCount, int duration){
  if (movementCount > 3 && randomDecisionToTurnOn(50)) {
    billySleep();
    dance(duration);
  } else {
    talk(duration, random(2,6));
  }
}
