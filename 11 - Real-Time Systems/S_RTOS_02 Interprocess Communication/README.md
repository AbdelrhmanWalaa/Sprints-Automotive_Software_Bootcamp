## Task 1: Button-LED Interaction

### Description:
In this task, you are required to modify an existing RTOS project to implement a program with two tasks. One task will monitor a button's state (ON/OFF) and generate events when the button is pressed and released. The other task will toggle an LED based on the button events.

### Requirements:
- Use the existing RTOS project as a base.
- Create a task to read the button state and generate events when the button is pressed and released.
- Create another task to toggle the LED based on the button events.
- Implement the necessary code to handle button events and control the LED accordingly.

## Task 2: UART String Writing

### Description:
In this task, you will extend the existing RTOS project to include two tasks responsible for writing strings to the UART. Each task will write a specific string repeatedly for a certain number of cycles, with different cycle times. One task will have a cycle time of 100ms, and the other task will have a cycle time of 500ms. Additionally, the task with the 500ms cycle time will simulate heavy load by executing an empty loop after each string write.

### Requirements:
- Use the existing RTOS project from Task 1 as a base.
- Create two tasks to write strings to the UART.
- Each task should write its assigned string 10 times in each cycle.
- The first task should have a cycle time of 100ms.
- The second task should have a cycle time of 500ms and include a simulated heavy load by executing an empty loop 100,000 times after each string write.
- Ensure that the UART writing tasks are not interrupted by each other.

## Task 3: Button and UART Interaction

### Description:
In this task, you will further enhance the existing RTOS project by adding four tasks. Two tasks will monitor rising and falling edges on two buttons, generating events when edges occur. These events will be sent to a consumer task responsible for writing the events on the UART. Additionally, a periodic task will send a predefined string to the consumer task every 100ms.

### Requirements:
- Use the existing RTOS project from Task 2 as a base.
- Create two tasks to detect rising and falling edges on two buttons.
- Each button task should generate events when a button edge occurs.
- Create a consumer task responsible for receiving events and writing them on the UART.
- Create a periodic task that sends a predefined string to the consumer task every 100ms.
- Implement the necessary code to handle button events, write events on the UART, and send periodic strings.
