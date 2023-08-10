# LED Sequence V2.0

## Description

This project entails the creation of a system designed to manage the sequence of LED lighting through button interactions. By pressing specific buttons, you can control the order and timing of the LED illumination. This project combines hardware control with user interaction, offering an engaging way to explore the dynamics of LEDs and buttons in action. 

## Requirements

### Hardware Requirements:

1. Four LEDs (LED0, LED1, LED2, LED3)
2. One button (BUTTON0)

### Software Requirements:

1. Initially, all LEDs are OFF
2. Once BUTTON0 is pressed, LED0 will be ON
3. Each press further will make another LED is ON
4. At the fifth press, LED0 will changed to be OFF
5. Each press further will make only one LED is OFF
6. This will be repeated forever
7. The sequence is described below

    1. Initially (OFF, OFF, OFF, OFF)
    2. Press 1 (ON, OFF, OFF, OFF)
    3. Press 2 (ON, ON, OFF, OFF)
    4. Press 3 (ON, ON, ON, OFF)
    5. Press 4 (ON, ON, ON, ON)
    6. Press 5 (OFF, ON, ON, ON)
    7. Press 6 (OFF, OFF, ON, ON)
    8. Press 7 (OFF, OFF, OFF, ON)
    9. Press 8 (OFF, OFF, OFF, OFF)
    10. Press 9 (ON, OFF, OFF, OFF)

8. Use External Interrupts

## Video
> [LED Sequence V2.0](https://drive.google.com/file/d/160H5Uc33Mh7ju0Dv7-tB356NEH77_dGf/view?usp=drive_link)
