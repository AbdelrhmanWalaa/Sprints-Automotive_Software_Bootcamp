# Small OS Design

## Description

In this project, the task is to design a small OS with a priority based preemptive scheduler based on time-triggered.

## Requirements

### Hardware Requirements
1. ATmega32 microcontroller
2. PBUTTON0 to stop the SOS
3. PBUTTON1 to run the SOS
4. Two LEDs to be toggled

### Software Requirements
1. Implement an application that calls SOS module and use 2 tasks
2. Task_1: Toggle LED_0 (Every 300 Millisecond)
2. Task_2: Toggle LED_1 (Every 500 Millisecond)
3. Make sure these tasks occur periodically and forever
4. When pressing  BUTTON 0, the SOS will stop
5. When pressing  BUTTON 1, the SOS will run

## Video
> [Small OS](https://drive.google.com/file/d/134TnuFbZfW89E1ddrbLacKc8HiRsD8lT/view?usp=sharing)
