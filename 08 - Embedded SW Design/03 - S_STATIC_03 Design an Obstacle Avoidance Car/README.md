# Obstacle Avoidance Car Design

## Description

In this project, the task involves developing software for a robot to avoid any object in front.

## Requirements

### Hardware Requirements

1. ATmega32 microcontroller
2. Fourmotors (M1, M2, M3, M4)
3. One button to change default direction of rotation (PBUTTON0)
4. Keypad button 1 to start
5. Keypad button 2 to stop
6. One Ultrasonic sensor connected as follows:

      1. Vcc to 5V in the Board
      2. GND to the ground In the Board
      3. Trig to PB3 (Port B, Pin 3)
      4. Echo to PB2 (Port B, Pin 2)

7. LCD

### Software Requirements

1. The car starts initially from 0 speed.

2. The default rotation direction is to the right.

3. Press (Keypad Btn 1), (Keypad Btn 2) to start or stop the robot respectively.

4. After Pressing Start:

      1. The LCD will display a centered message in line 1 “Set Def. Rot.”.
      2. The LCD will display the selected option in line 2 “Right”.
      3. The robot will wait for 5 seconds to choose between Right and Left
            
            1. When PBUTTON0 is pressed once, the default rotation will be Left and the LCD line 2 will be updated.
            2. When PBUTTON0 is pressed again, the default rotation will be Right and the LCD line 2 will be updated.
            3. For each press the default rotation will change and the LCD line 2 is updated.
            4. After 5 seconds the default value of rotation is set.

      4. The robot will move after 2 seconds from setting the default direction of rotation.

5. For No obstacles or object is far than 70 centimeters:
      1. The robot will move forward with 30% speed for 5 seconds.
      2. After 5 seconds it will move with 50% speed as long as there is no object or objects are located at more than 70 centimeters       
         distance.
      3. The LCD will display the speed and moving direction in line 1: “Speed:00% Dir: F/B/R/S”, F: forward, B: Backwards, R: Rotating, and 
         S: Stopped.
      4. The LCD will display Object distance in line 2 “Dist.: 000 Cm”.

6. For Obstacles located between 30 and 70 centimeters:
      1. The robot will decrease its speed to 30%.
      2. LCD data is updated.

7. For Obstacles located between 20 and 30 centimeters:
      1. The robot will stop and rotate 90 degrees to right/left according to the chosen configuration.
      2. The LCD data is updated.

8. For Obstacles located less than 20 centimeters:
      1. The robot will stop, move backwards with 30% speed until distance is greater than 20 and less than 30.
      2. The LCD data is updated.
      3. Then perform point 7.

9. Obstacles surrounding the robot
      1. If the robot rotated for 360 degrees without finding any distance greater than 20 it would stop.
      2. LCD data will be updated.
      3. The robot will frequently (each 3 seconds) check if any of the obstacles was removed or not and move in the direction of the 
         furthest object.

## Video
> [Obstacle Avoidance Car](https://drive.google.com/file/d/1ySaMgl5F18mIlnHH4Pd5KhPO9Bulsy3x/view?usp=sharing)
