/*
Name: Jonas Rudaitis
*/
#include <Servo.h>

// set pins
int joy_x_pin = A5;
int joy_y_pin = A4;

Servo servo_x;
Servo servo_y;

int leds_x[] = {2, 3, 4};
int leds_y[] = {6, 7, 8};

// positions for joysticks and servos
int joy_x, joy_y;
int x_pos, y_pos;

void setup() {
  Serial.begin(9600);
  
  servo_x.attach(10);
  servo_y.attach(11);

  for (int i = 0; i <= 2; i++) {pinMode(leds_x[i], OUTPUT);}
  for (int i = 0; i <= 2; i++) {pinMode(leds_y[i], OUTPUT);}
}

void loop() {
  joy_x = analogRead(joy_x_pin);
  joy_y = analogRead(joy_y_pin);

  // Calculate Servo position and write
  x_pos = ((joy_x * 22.5) / 1023.0) + (22.5*3.5);
  y_pos = ((joy_y * 22.5) / 1023.0) + (22.5*3.5);
  servo_x.write(x_pos-7);
  servo_y.write(y_pos+8);

  // If statements for x-axis leds
  if (x_pos > 92){
    digitalWrite(leds_x[0], HIGH);
    digitalWrite(leds_x[1], LOW);
    digitalWrite(leds_x[2], LOW);
    Serial.print("Right ")
  }
  else if (x_pos < 88){
    digitalWrite(leds_x[0], LOW);
    digitalWrite(leds_x[1], HIGH);
    digitalWrite(leds_x[2], LOW);
    Serial.print("X Level ")
  }
  else {
    digitalWrite(leds_x[0], LOW);
    digitalWrite(leds_x[1], LOW);
    digitalWrite(leds_x[2], HIGH);
    Serial.print("Left ")
  }

  // if statements for y-axis leds
  if (y_pos > 92){
    digitalWrite(leds_y[0], HIGH);
    digitalWrite(leds_y[1], LOW);
    digitalWrite(leds_y[2], LOW);
  }
  else if (y_pos < 88){
    digitalWrite(leds_y[0], LOW);
    digitalWrite(leds_y[1], HIGH);
    digitalWrite(leds_y[2], LOW);
  }
  else {
    digitalWrite(leds_y[0], LOW);
    digitalWrite(leds_y[1], LOW);
    digitalWrite(leds_y[2], HIGH);
  }

  Serial.print("Joysticks: "); Serial.print(joy_x); Serial.print(", "); Serial.print(joy_y);
  Serial.print(" Servos: "); Serial.print(x_pos); Serial.print(", "); Serial.println(y_pos);
  Serial.println();
  
  delay(25);
}
