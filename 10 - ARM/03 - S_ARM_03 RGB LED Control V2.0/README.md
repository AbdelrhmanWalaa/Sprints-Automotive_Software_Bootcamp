# RGB LED Control V2.0

## Description

The RGB LED Control project aims to demonstrate the capabilities of the Tiva C TM4C123GXL LaunchPad board by implementing 
a simple user interface using the SW1 button. The project enables users to control the color and behavior of an RGB LED by 
pressing the SW1 button on the board. Additionally, a one-second delay functionality is incorporated, ensuring that if the 
switch is pressed, the LED turns off after a brief pause. By combining the power of the Tiva C microcontroller, 
the versatility of the RGB LED, and the added delay feature, this project offers an interactive and visually engaging
experience.

## Requirements

### Hardware Requirements

- TivaC board.
- SW1 as an input button.
- RGB LED.

### Software Requirements

- The RGB LED should be OFF initially.

- Functionality Requirements:

  - Pressing SW1:
    1. After the first press, the Red LED should be on for 1 second only.
    2. After the second press, the Green LED should be on for 1 second only.
    3. After the third press, the Blue LED should be on for 1 second only.
    4. After the fourth press, all LEDs should be on for 1 second only.
    5. After the fifth press, all LEDs should be disabled (OFF).
    6. After the sixth press, the cycle should repeat from step 1 to step 6.

## Video
> [RGB LED Control V2.0](https://drive.google.com/file/d/1h2TQ8Yu2JskwJdpywz2WhRW6NTgTMVLa/view?usp=sharing)
