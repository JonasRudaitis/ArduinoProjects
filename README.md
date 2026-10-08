# Arduino Projects by me!
## Line Following Robot
A line following robot made in grade 10 that follows a black electrical tape line on a white tile background.
<video src="./LineFollowingRobot/img/robot-showcase.mov" controls width="600"></video>

It features two QRD sensors with 4 pins:
1. IR LED input
2. IR LED GND
3. Phototransistor output
4. Phototransitor GND

And uses a single motor driver to control the speed and direction of two hobby gearmotors. 

<video src="./LineFollowingRobot/img/robot-close-look.mov" controls width="600"></video>
## LED Matrix
A 4x4x3 LED matrix where each LED can be individually controlled to create unique patterns. 

How it works:
Each "floor" (z level) the anode of the LEDs are connected. 
Each collumn's cathodes are soldered together. 

To turn on led (1,1,1), you would:
```
// Turn off ALL LEDs
for (int i = 0; i < 3; i++) {
    digitalWrite(floors[i], HIGH); // all the anodes are ON 
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      digitalWrite(leds[i][j], LOW); // all the cathodes are OFF
    }                                // so electricity CANNOT flow
  }
// Turn on JUST LED (1,1,1)
digitalWrite(leds[1][1], HIGH); // This sets the cathodes of all LEDs at (1,1,z) on
digitalWrite(floors[1], LOW);   // This sets the floor to act as ground, allowing the electricity
                                //  to flow through the cathode and anode ONLY on LED (1,1,1)


```
<video controls src="./LEDMatrix/img/matrix.MOV" title="Title"></video>

Diagonal program running on the matrix

## Marble Maze
This project is a tilting marble maze where the maze tilts to move a marble to a goal. The tilt is controlled by two servo motors, receiving input from a joystick. 

7 LEDS (4 on x, 3 on y) also are controlled as a visual feedback to the tilt: 
- if the maze is balanced, only the middle LEDs will be ON
- if the maze is tilted, only the LEDs in the direction of the tilt will be ON.