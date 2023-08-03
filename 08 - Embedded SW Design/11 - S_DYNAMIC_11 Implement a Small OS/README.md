# Small OS

<p align="center">
  <img src="https://github.com/AbdelrhmanWalaa/Sprints-Automotive_Software_Bootcamp/assets/44446382/8d7102a1-17ab-4183-87c8-93f0eb594d2b" alt="Small OS">
</p>

## Overview

This project involves the implementation of a small operating system, where tasks are periodic and non-preemptive. The operating system will be designed to run on an ATmega32 microcontroller and will interact with PBUTTON0 and PBUTTON1 for control. The main functionality of the system will be to toggle two LEDs periodically based on defined tasks.

## Project Goals

- **Implement a Small Operating System:** Develop a simple operating system that allows the execution of periodic tasks without preemption.
- **Task Management:** Design a task management system to handle two tasks:
  
   - Task_1: Toggle LED_0 every 300 milliseconds.
   - Task_2: Toggle LED_1 every 500 milliseconds.

- **Periodic Execution:** Ensure that the tasks occur periodically and continue indefinitely.
- **Button Control:** Integrate PBUTTON0 and PBUTTON1 to control the operating system's behavior:

   - When PBUTTON0 is pressed, the operating system (SOS) will stop executing tasks.
   - When PBUTTON1 is pressed, the operating system (SOS) will resume executing tasks.

## Expected Outcomes

- A functional and efficient small operating system designed for the ATmega32 microcontroller.
- Two tasks (Task_1 and Task_2) that accurately toggle the corresponding LEDs at defined time intervals.
- A non-preemptive task management system ensuring periodic execution of the tasks indefinitely.
- The system's responsiveness to PBUTTON0 and PBUTTON1, allowing users to halt and resume task execution as needed.

## Contributors

> [Abdelrhman Walaa](https://github.com/AbdelrhmanWalaa) |
> [Mohamed Abdelsalam](https://github.com/m3adel) |
> [Hazem Ashraf](https://github.com/hazemashrafali)

## Video
> [Small OS](https://drive.google.com/file/d/1HBlgQlkSO54oUB3SGNeSbU-6UzoHl08a/view?usp=sharing)

## Circuit Schematic

<p align="center">
  <img src="https://github.com/AbdelrhmanWalaa/Sprints-Automotive_Software_Bootcamp/assets/44446382/30991d3d-2e58-48c4-b948-a3f7e71566a0" alt="Circuit Schematic">
</p>
