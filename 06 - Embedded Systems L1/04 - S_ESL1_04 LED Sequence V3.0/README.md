# LED Sequence V3.0

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
    2. Press 7 (OFF, OFF, OFF, BLINK_1)
    3. Press 1 (BLINK_1, OFF, OFF, OFF)
    4. Press 2 (BLINK_1, BLINK_1, OFF, OFF)
    5. Press 3 (BLINK_1, BLINK_1, BLINK_1, OFF)
    6. Press 4 (BLINK_1, BLINK_1, BLINK_1, BLINK_1)
    7. Press 5 (OFF, BLINK_1, BLINK_1, BLINK_1)
    8. Press 6 (OFF, OFF, BLINK_1, BLINK_1)
    9. Press 7 (OFF, OFF, OFF, BLINK_1)
    10. Press 7 (OFF, OFF, OFF, BLINK_1)

8. When BUTTON1 has pressed the blinking on and off durations will be changed

    1. No press → BLINK_1 mode (ON: 100ms, OFF: 900ms)
    2. First press → BLINK_2 mode (ON: 200ms, OFF: 800ms)
    3. Second press → BLINK_3 mode (ON: 300ms, OFF: 700ms)
    4. Third press → BLINK_4 mode (ON: 500ms, OFF: 500ms)
    5. Fourth press → BLINK_5 mode (ON: 800ms, OFF: 200ms)
    6. Fifth press → BLINK_1 mode

10. Use External Interrupts

## Video
> [LED Sequence V3.0](https://drive.google.com/file/d/1WfbNe7RLprakrV_B0G_XuCTiiov-nO2S/view?usp=drive_link)

