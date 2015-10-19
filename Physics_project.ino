#include <Wire.h>
#include "rgb_lcd.h"
int pinButton = 3; //button
int pinSound = A0; //mic
int speakerPin = 4; //buzzer
int pinTouch = 7; //touch sensor
int rotatePin = A1; //spinny thingy
int pinLight = A2; // light sensor
rgb_lcd lcd; //screen display
int cutout = 1000 * 10;
int beep = cutout / 10;
long startTime = 0;
long num = 0;
int score = 0;
boolean shouldContinue = true;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setRGB(0, 0, 255);
  pinMode(pinTouch, INPUT);
  pinMode(rotatePin, INPUT);
  pinMode(speakerPin, OUTPUT);
  pinMode(pinButton, INPUT);
}

void loop() {
  num = random(1, 6);
  if (shouldContinue) {
    num = random(1, 6);
    if (num == 1) {
      lcd.print("Bop It");
      shouldContinue = bopIt();
    } else if (num == 2) {
      lcd.print("Touch Sensor");
      shouldContinue = touch();
    } else if (num == 3) {
      lcd.print("Spinny Thingy");
      shouldContinue = spin();
    } else if (num == 4) {
      lcd.print("Light Sensor");
      shouldContinue = light();
    } else if (num == 5) {
      lcd.print("Mic");
      shouldContinue = speak();
    }
  } else {
    lcd.clear();
    lcd.print("You Lose");
    digitalWrite(speakerPin, HIGH);
    delay(2000);
    digitalWrite(speakerPin, LOW);
    lcd.clear();
    lcd.print(score);
    delay(100000000);
  }
  cutout = cutout * 11 / 12;
  beep = cutout / 10;
}


boolean bopIt() {
  startTime = millis();
  while (millis() - startTime <= cutout) {
    if ((millis() - startTime) % beep == 0) {
      digitalWrite(speakerPin, HIGH);
      delay(cutout / 100);
      digitalWrite(speakerPin, LOW);
    }
    if (digitalRead(pinButton)) {
      score++;
      lcd.clear();
      lcd.print("Good Job");
      delay(2000);
      lcd.clear();
      return true;
    }
  }
  return false;
}

boolean touch() {
  startTime = millis();
  while (millis() - startTime <= cutout) {
    if ((millis() - startTime) % beep == 0) {
      digitalWrite(speakerPin, HIGH);
      delay(cutout / 100);
      digitalWrite(speakerPin, LOW);
    }
    if (digitalRead(pinTouch)) {
      score++;
      lcd.clear();
      lcd.print("Good Job");
      delay(2000);
      lcd.clear();
      return true;
    }
  }
  return false;
}

boolean spin() {
  startTime = millis();
  int value = analogRead(rotatePin);
  while (millis() - startTime <= cutout) {
    if ((millis() - startTime) % beep == 0) {
      digitalWrite(speakerPin, HIGH);
      delay(cutout / 100);
      digitalWrite(speakerPin, LOW);
    }
    if (analogRead(rotatePin) > value + 100 || analogRead(rotatePin) < value - 100) {
      score++;
      lcd.clear();
      lcd.print("Good Job");
      delay(2000);
      lcd.clear();
      return true;
    }
  }
  return false;
}

boolean speak() {
  startTime = millis();
  while (millis() - startTime <= cutout) {
    if ((millis() - startTime) % beep == 0) {
      digitalWrite(speakerPin, HIGH);
      delay(cutout / 100);
      digitalWrite(speakerPin, LOW);
    }
    if (analogRead(pinSound) > 700) {
      score++;
      lcd.clear();
      lcd.print("Good Job");
      delay(2000);
      lcd.clear();
      return true;
    }
  }
  return false;
}

boolean light() {
  startTime = millis();
  while (millis() - startTime <= cutout) {
    if ((millis() - startTime) % beep == 0) {
      digitalWrite(speakerPin, HIGH);
      delay(cutout / 100);
      digitalWrite(speakerPin, LOW);
    }
    if (analogRead(pinLight) < 400) {
      score++;
      lcd.clear();
      lcd.print("Good Job");
      delay(2000);
      lcd.clear();
      return true;
    }
  }
  return false;
}
