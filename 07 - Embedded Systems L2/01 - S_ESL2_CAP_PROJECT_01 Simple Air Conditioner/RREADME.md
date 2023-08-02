# Simple Air Conditioner

<p align="center">
  <img src="https://github.com/AbdelrhmanWalaa/Sprints-Automotive_Software_Bootcamp/assets/44446382/890d18cb-2f81-45e1-badd-6622d7512d59" alt="Simple Air Conditioner">
</p>

## Overview

This project involves the development of software to control an AC unit using various components, including an LCD 2x16, a temperature sensor LM35, a buzzer, and a 3x3 keypad with 5 buttons. 

The software allows users to adjust the desired temperature within certain bounds and ensures proper functioning of the AC unit.

## Project Goals

- To create an intuitive user interface for controlling the AC unit using the provided components.
- To allow users to set the desired temperature within the range of 18°C to 35°C.
- To provide visual feedback through an LCD and progress bar to display the current and desired temperature settings.
- To ensure the safety of the AC unit by restricting the temperature range between 18°C to 35°C.
- To enable automatic temperature adjustment and control the buzzer in case the current temperature exceeds the desired temperature.

## Expected Outcomes

- The system will initialize by displaying a welcome message and then show the default temperature of 20°C.
- Users can access the Adjust Screen to modify the desired temperature using the keypad buttons 1 (increase) and 2 (decrease), with a visual representation of the progress bar.
- If the user takes no action for 10 seconds, the system will set the temperature back to the default value of 20°C.
- Pressing keypad button 3 will set and start the AC with the desired temperature setting.
- The Running Screen will display the current temperature from the sensor, and if the current temperature is higher than the desired temperature, a buzzer icon will be shown and the buzzer will activate until the temperature drops.
- During the Running Screen, the buttons 1, 2, and 3 on the keypad will be disabled, preventing any accidental temperature adjustments.
- The buttons 4 and 5 will remain enabled during the Running Screen, allowing users to go back to the Adjust Screen or reset the desired temperature to the default value, respectively.

Additionally, some extra features have been included:

- The buzzer will buzz for 1 second if the user tries to set the temperature below the minimum (18°C) or above the maximum (35°C) allowed range.
- An extra screen is provided before the Adjust Screen to inform users about the controls used for adjusting temperature (e.g., 1 for (+), 2 for (-), and 3 for setting).
- During the Running Screen, the buttons for adjusting (1, 2, 3) and resetting (5) are completely disabled to avoid confusion and unnecessary actions. Similarly, during the Adjust Screen, the buttons for adjusting (1, 2, 3) and resetting (5) are also disabled.

## Contributors

> [Abdelrhman Walaa](https://github.com/AbdelrhmanWalaa) |
> [Hossam Elwahsh](https://github.com/HossamElwahsh) |
> [Mahmoud Mowafey](https://github.com/Mahmoud-Mowafy) |
> [Tarek Elgohary](https://github.com/telgohry)

## Video
> [Simple Air Conditioner](https://drive.google.com/file/d/1ZH06oF34BZV8BQJCRTx4vyjBaZKROIPa/view?usp=sharing)

## Circuit Schematic

<p align="center">
  <img src="https://github.com/AbdelrhmanWalaa/Sprints-Automotive_Software_Bootcamp/assets/44446382/80783184-f8e8-4d76-9d68-98e10aa26614" alt="Circuit Schematic">
</p>

