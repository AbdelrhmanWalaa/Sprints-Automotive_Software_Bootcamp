## Task 1: Toggle LED Every 1000ms

### Description:
In this task, you are required to modify an existing RTOS project to create a program that toggles an LED every 1000ms (1 second). The project already includes the necessary setup for the RTOS.

### Requirements:
- Use the existing RTOS project as a base.
- Create a new task that toggles an LED every 1000ms.
- Implement the necessary code to control the LED and timing.
- Ensure the task runs at a regular interval using the RTOS scheduler.

## Task 2: Toggle 3 LEDs at Different Rates

### Description:
In this task, you will extend the existing RTOS project to include three tasks, each responsible for toggling a different LED at a specific rate. The LED toggling rates for the three tasks are as follows: 100ms, 500ms, and 1000ms.

### Requirements:
- Use the existing RTOS project from Task 1 as a base.
- Create three new tasks, each responsible for toggling a specific LED at the given rate.
- Implement the necessary code to control the LEDs and timing for each task.
- Ensure each task runs at its designated interval using the RTOS scheduler.

## Task 3: User-Controlled LED Toggling Rate

### Description:
In this task, you will enhance the existing RTOS project further by introducing user control over the LED toggling rate using a push button. The LED will toggle based on the duration of the button press, with different durations resulting in different toggling rates.

### Requirements:
- Use the existing RTOS project from Task 2 as a base.
- Implement a mechanism to detect button presses and releases.
- Define the following behavior for different button press durations:
  - Press longer than 2 seconds but less than 4 seconds: Toggle the LED with a periodicity of 400ms.
  - Press longer than 4 seconds: Toggle the LED with a periodicity of 100ms.
  - Press shorter than 2 seconds: Turn off the LED.
- Implement the necessary code to handle button events and control the LED toggling rate accordingly.
