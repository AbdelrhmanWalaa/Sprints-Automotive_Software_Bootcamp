# EDF Scheduling Algorithm for Real-Time Systems

## Overview
This project focuses on implementing the Earliest Deadline First (EDF) scheduling algorithm for a real-time system. EDF is a dynamic priority-based preemptive scheduling policy that ensures efficient task management by prioritizing tasks based on their deadlines. The algorithm allows for the changing of task priorities during execution, and any lower periodicity task can preempt the execution of higher periodicity tasks.

The project involves the scheduling of six tasks using the EDF algorithm. The first four tasks, namely Button_1_Monitor, Button_2_Monitor, Periodic_Transmitter, and Uart_Receiver, have specific periodicities and deadlines. Button_1_Monitor and Button_2_Monitor tasks monitor button events and send them to the consumer task. Periodic_Transmitter sends periodic strings, while Uart_Receiver receives strings and writes them to the UART.

To simulate a heavier workload, two additional tasks, Load_1_Simulation and Load_2_Simulation, are included. These tasks are implemented as empty loops that need to be executed a specific number of times to achieve the desired execution time. Adjusting the loop iterations allows for the simulation of varying workload scenarios, impacting the system's overall performance.

## Project Goals
- Implement the EDF scheduling algorithm for a real-time system.
- Schedule tasks based on their deadlines and adjust priorities dynamically.
- Monitor the rising and falling edges of buttons and transmit periodic strings.
- Receive strings from tasks and write them to the UART.
- Simulate heavier loads using empty loops executed with specific loop iterations.

## Expected Outcomes
- Successful implementation of the EDF scheduling algorithm.
- Task execution prioritization based on deadlines.
- Proper monitoring of button events and transmission of periodic strings.
- Reception and writing of strings from tasks to the UART.
- Simulation of varying workloads with Load_1_Simulation and Load_2_Simulation.
- Efficient task execution while maintaining system responsiveness and meeting timing requirements.

## Contributors
> [Abdelrhman Walaa](https://github.com/AbdelrhmanWalaa) |
> [Amr El-Abd](https://github.com/AmrElAbd09) |
> [Mohamed AbdelSalam](https://github.com/m3adel) |
> [Hazem Ashraf](https://github.com/hazemashrafali)

## Video Link
> [EDF Scheduler](https://drive.google.com/file/d/18fT2M_iGboBTeThPvK7_me9P3f5lazBn/view?usp=drive_link)
