/*
Name: Jonas Rudaitis
Date: Thursday, April 18, 2025
Description: A 4x4x3 LED matrix. Each floor is the anode of a LED, connected to a 220 ohm resistor, and to a digital pin
  Each collumn is the cathode. The LED write function takes an XYZ coordinate, and turns on that specific LED by:
      Setting all the floors to LOW
      Set all the cathodes (-) To HIGH (this makes sure no unintended lights turn on)
      Set the desired Z floor to HIGH
      Set the desired XY collumn to LOW
  Each game is a function: snake(), diagonal(), name(), pong() that use the ledWrite() function to play
  SNAKE: The leds snake accross each row in a zig-zag pattern
  DIAGONAL: Like snake, but diagonally instead of straight forward and back
  NAME: Displays my initials JFR, one letter at a time
  PONG: Control an indivdual LED using 3 potentiometer- one for X, Y, and Z
*/

// potentiometer inputs
int potX = A0;
int potY = A1;
int potZ = A2;

// Game Select Button inuts
int btns[] = {13, 12, 11, 10};

int leds[4][4] = { // collumns
  {39, 38, 41, 40},
  {43, 42, 45, 44},
  {47, 46, 49, 48},
  {51, 50, 53, 52}
}; 

int floors[3] = { 5, 6, 7}; 

// arrays for my initials (the x's are fliped [from perspective below the matrix])
int JFR[3][4][4] = {
  { // J
    {1, 1, 1, 1},
    {0, 1, 0, 0},
    {0, 1, 0, 1},
    {0, 1, 1, 0}
  },
  { // F
    {0, 1, 1, 1},
    {0, 0, 0, 1},
    {0, 1, 1, 1},
    {0, 0, 0, 1}
  },
  { // R
    {0, 0, 1, 1},
    {0, 1, 0, 1},
    {0, 0, 1, 1},
    {0, 1, 0, 1}
  }
}

void setup() {
  Serial.begin(9600);

  // Set all the negatives to outputs
  for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        pinMode(leds[i][j], OUTPUT);
      }
    }
  
  // set all the floors to outputs
  for (int i = 0; i < 3; i++) {
    pinMode(floors[i], OUTPUT);
  }

  // Game button inputs
  for (int i = 0; i < 4; i++) {
        pinMode(btn[i], INPUT);
      }
}

void loop() {
  // button inputs for games
  if (digitalRead(btn[0)){
    snake();
  }
  else if (digitalRead(btn[1)){
    diagonal();
  }
  else if (digitalRead(btn[2)){
    pong();
  }
  else if (digitalRead(btn[3)){
    name();
  }
}

// this function takes an xyz and turns on that specific led
void ledWrite(int x, int y, int z){
  for (int i = 0; i < 4; i++) {// turn each pin to high
    for (int j = 0; j < 4; j++) {
      digitalWrite(leds[i][j], HIGH);
    }
    digitalWrite(floors[z], 1);
    digitalWrite(leds[x][y], 0);
  }
}

// turns all pins to LOW (not off for led, the ledWrite function makes the - terminal to high)
void allOff(){
  // set everything to ground
  for (int i = 0; i < 3; i++) {
    digitalWrite(floors[i], 0);
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      digitalWrite(leds[i][j], 0);
    }
  }
}

// diagonal game
void diagonal(){
  for (int z = 0; z < 3; z++) {  
    for (int MAX = 0; MAX <= 7; MAX++) {
      int x = MAX;
      int y = 0;
      for (int i = 0; i <= MAX; i++) {
        if ((x < 4) && (y < 4)) { // only if the led is in the matrix
          ledWrite(x, y, z);
          delay(150);
          allOff();
        }
        x--; //this makes diagonal do diagonal
        y++; 
      }
    }
  }
}

// snake game
void snake() {
  allOff();
  for (int z = 0; z < 3; z++) { //repeat the following code for each layer
    if (z % 2 == 0) { //run the following code on even layers
      for (int i = 0; i < 4; i++) { //repeat for x values of the matrix
        if ( (i % 2) == 0) { // If even X
          for (int j = 0; j < 4; j++) {
            ledWrite(i, j, z);
            delay(250);
            allOff();
          }
        }
        else { // If odd X, go opposite direction (snake)
          for (int k = 3; k >= 0; k--) {
            ledWrite(i, k, z);  
            delay(250);
            allOff();
          }
        }
      }
    }
    else { // middle layer code (reverse of the others)
      for (int i = 3; i >= 0; i--) {
        if ( (i % 2) == 0) { // If even X, go opposite direction (snake)
          for (int k = 3; k >= 0; k--) {
            ledWrite(i, k, 1);  
            delay(250);
            allOff();
          }
        }
        else { // If odd X
          for (int j = 0; j < 4; j++) {
            ledWrite(i, j, 1);  
            delay(250);
            allOff();
          }
        }
      }
    }
  }
}

// name game (displays JFR) (uses multiplexing to give the illusion of multiple LEDS on at once)
void name(){
  int time_per_letter = 500;
  // J
  int counter = 0;
  for(int i;i<3;i++){}
    while(counter < time_per_letter){ // repeat until the time has reached
      for (int x=0; x<4;x++){
        for (int y=0; y<4;y++){
          if (JFR[i][x][y] == 1){
            ledWrite(x, y, 2);
            delay(1);
            counter++;
          }
        }
      }
    }
    counter = 0; // reset counter
  }
}

// Pong game
void pong(){
  allOff();
  int x = map(analogRead(potX), 0, 1023, 0, 3);
  int y = map(analogRead(potY), 0, 1023, 0, 3);
  int z = map(analogRead(potZ), 0, 1023, 0, 2);
  ledWrite(x, y, z);
  delay(5);
}