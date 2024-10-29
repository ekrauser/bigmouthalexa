#include "AnimateBilly.h"

int sensorPin = A0;    // select the input pin for the audio signal
int ledPin = 13;

int sampleSensor(int pin, int samples = 20, int duration = 250) {
  float sensorValue = 0;
  int iterDelay = duration / samples;
  for (int i = 0; i < samples; i++) {
    sensorValue += analogRead(pin);
    delay(iterDelay);
  }
  digitalWrite(ledPin, LOW);
  return (int)(sensorValue / samples);
}

int sampleAverages(int pin, int samples = 3, int duration = 100) {
  int iterDelay = duration / samples;
  int avgValue = 0;
  for (int i = 0; i < samples; i++) {
    avgValue += sampleSensor(pin, samples, iterDelay);
    delay(iterDelay);
  }
  return (int)(avgValue / samples);
}

void setup() {
  setupFishMotors();
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);      // open the serial port at 9600 bps:    
}

int stillPlaying = 0;
int aniDuration = 500;
int previousValue = 0;
int quietThreshold = 2;

void loop() {
  // read the value from the sensor:
  int sensorValue = sampleSensor(sensorPin);
  float smoothedSensorValue = (sensorValue + previousValue) / 2 ;
  if(smoothedSensorValue > quietThreshold) {
    digitalWrite(ledPin, HIGH);
    stillPlaying = min(stillPlaying + 1, 4);
    moveBilly(stillPlaying, aniDuration);
  } else if (stillPlaying == 0){
      billySleep();
      digitalWrite(ledPin, LOW);
      stillPlaying = 0;
  } else {
    stillPlaying--;
  }
  previousValue = sensorValue;
}
