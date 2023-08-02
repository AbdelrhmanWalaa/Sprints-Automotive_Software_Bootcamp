# Moving Car V2.0

<p align="center">
  <img src="https://github.com/AbdelrhmanWalaa/Sprints-Automotive_Software_Bootcamp/assets/44446382/9bdb36d3-1466-48cd-ae16-7bbc94a2dc68" alt="Moving Car">
</p>

## Overview

This project involves developing a robot using four motors, two buttons, and four LEDs, with the control system implemented on a Tiva C board. The Tiva C board utilizes ARM processors, enabling precise control and efficient programming. 

The robot is designed to move in a continuous rectangular path, howcasing the programmer's skills in controlling the robot's movements and designing an effective control system. The four motors provide the necessary propulsion for the robot, while the two buttons allow for user interaction and control. Additionally, the four LEDs can be utilized for status indication or visual feedback. 

Overall, this project demonstrates the programmer's proficiency in programming robotic systems, utilizing ARM processors, and implementing a control system that enables precise movements and efficient operation

Apologies for the confusion. Let's rewrite the Project Goals and Expected Outcomes based on the provided ARM microcontroller specifications:

## Project Goals

- Develop a moving car application on an ARM microcontroller using the Sprints Kit with TivaC launch pad.
- Control the movement of the car with four motors (M1, M2, M3, M4), one start button (PB1), and one stop button (PB2).
- Utilize four LEDs (LED1, LED2, LED3, LED4) to indicate the car's status (moving forward on the long side, moving forward on the short side, stopped, and rotating).
- Implement the following behavior for the car:

  1. The car starts initially from 0 speed.
  2. When PB1 is pressed, the car will move forward after 1 second.
  3. The car will move forward to create the longest side of the rectangle for 3 seconds with 50% of its maximum speed.
  4. After finishing the first longest side, the car will stop for 0.5 seconds, rotate 90 degrees to the right, and stop for 0.5 seconds.
  5. The car will move to create the short side of the rectangle at 30% of its speed for 2 seconds.
  6. After finishing the shortest side, the car will stop for 0.5 seconds, rotate 90 degrees to the right, and stop for 0.5 seconds.
  7. Steps 3 to 6 will be repeated infinitely until you press the stop button (PB2).
  8. PB2 acts as a sudden brake with the highest priority.

## Expected Outcomes

- Successful development of the moving car application on the ARM microcontroller.
- Proper control of the car's motors, start button, and stop button, following the specified behavior.
- Accurate indication of the car's status using the LEDs (LED1, LED2, LED3, LED4).
- The car follows the rectangular movement pattern as described in the behavior.
- The system functions efficiently and reliably, ensuring timely responses to button presses and movements.

## Contributors

> [Abdelrhman Walaa](https://github.com/AbdelrhmanWalaa) |
> [Mohamed Abdelsalam](https://github.com/m3adel) |
> [Hazem Ashraf](https://github.com/hazemashrafali)

## Video
> [Moving Car V2.0](https://drive.google.com/file/d/1F0vETK0dewLjJqKIzRUAVG6O3WssU2ig/view?usp=sharing)
