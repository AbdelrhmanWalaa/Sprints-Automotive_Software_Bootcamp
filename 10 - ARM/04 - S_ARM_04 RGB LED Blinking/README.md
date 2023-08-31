# RGB LED Blinking

## Description

The RGB LED Control project aims to demonstrate the capabilities of the Tiva C TM4C123GXL LaunchPad board by implementing 
a simple user interface using the SW1 button. The project enables users to control the color and behavior of an RGB LED 
by pressing the SW1 button on the board. By combining the power of the Tiva C microcontroller and the versatility of the 
RGB LED, this project offers an interactive and visually engaging experience.

## Requirements

### Hardware Requirements

- TivaC board.
- SW1 as an input button.
- RGB LED.

### Software Requirements

- The RGB LED is OFF initially.
- The PWM signal has a 500ms duration.
- The system has four states:

  1. SW1 - First press:
     - The Green LED will be on with a 30% duty cycle.
 
  2. SW1 - Second press:
     - The Green LED will be on with a 60% duty cycle.

  3. SW1 - Third press:
     - The Green LED will be on with a 90% duty cycle.
  
  4. SW1 - Fourth press:
     - The Green LED will be off.
  
  5. SW1 - Fifth press:
     - The system state will return to state 1.

## Video
> [RGB LED Blinking](https://drive.google.com/file/d/1J1CSkIBNtMWOHEj-CEod7Uwtp42XUg4R/view?usp=sharing)
