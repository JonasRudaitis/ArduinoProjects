/*
Name: Jonas Rudaitis
Date: June 1st 2024
Description: Line following robot
*/

// Define Pins
int leftMotor1 = 2;
int leftMotor2 = 3;
int rightMotor1 = 5;
int rightMotor2 = 6;

int sensorLeft = A0;
int sensorRight = A1;

int leftValue;
int rightValue;

void setup() {
  Serial.begin(9600);

  pinMode(leftMotor1, OUTPUT);
  pinMode(leftMotor2, OUTPUT);
  pinMode(rightMotor1, OUTPUT);
  pinMode(rightMotor2, OUTPUT);
}

void loop() {
  leftValue = analogRead(sensorLeft);
  rightValue = analogRead(sensorRight);

  // approxomate sensor values to make it easier
  leftValue = (int) (leftValue / 200) * 200;
  rightValue = (int) (rightValue / 200) * 200;

  Serial.print("Left:"); Serial.print(leftValue); Serial.print(" Right: "); Serial.print(rightValue);

  if (leftValue > rightValue){
    left();
  }
  else if (leftValue < rightValue){
    right();
  }
  else {
    forward();
  }

  Serial.println();
}

void forward(){
  digitalWrite(leftMotor1, HIGH);
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, HIGH);
  digitalWrite(rightMotor2, LOW);
}

void left(){
  digitalWrite(leftMotor1, HIGH);
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, LOW);
  digitalWrite(rightMotor2, LOW);
}

void right(){
  digitalWrite(leftMotor1, LOW);
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, HIGH);
  digitalWrite(rightMotor2, LOW);
}