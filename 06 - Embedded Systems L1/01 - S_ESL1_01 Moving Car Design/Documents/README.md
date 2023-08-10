# Moving Car Design

## Description

In this project, the task is to design a system for a four-wheel diving robot that enables it to move in a precise rectangular path. By implementing the appropriate control logic, the robot can effectively navigate and execute turns, ensuring that its trajectory adheres to the rectangular shape.

## Requirements

1. The car starts initially from 0 speed.
2. When PB1 is pressed, the car will move forward after 1 second.
3. The car will move forward to create the longest side of the rectangle for 3 seconds with 50% of its maximum speed.
4. After finishing the first longest side the car will stop for 0.5 seconds, rotate 90 degrees to the right, and stop for 0.5 second.
5. The car will move to create the short side of the rectangle at 30% of its speed for 2 seconds.
6. After finishing the shortest side the car will stop for 0.5 seconds, rotate 90 degrees to the right, and stop for 0.5 second.
7. Steps 3 to 6 will be repeated infinitely until you press the stop button (PB2)
8. PB2 acts as a sudden break, and it has the highest priority.
