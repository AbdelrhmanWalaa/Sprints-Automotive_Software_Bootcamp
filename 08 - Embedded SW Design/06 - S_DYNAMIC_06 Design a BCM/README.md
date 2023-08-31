# Basic Communication Manager Design

## Description

This project involves developing Basic Communication Manager software.

## Requirements

### Hardware Requirements
1. ATmega32 microcontroller
2. Two LEDs to be toggled

### Software Requirements
1. Send “BCM Operating” string from MCU_1 to MCU_2.
2. When MCU_1 finishes sending, LED_0 in MCU_ 1 will be toggled.
3. When MCU_2 finishes receiving the “BCM Operating” string, LED_1 in MCU_2 will be toggled.
4. MCU_2 will respond with a “Confirm BCM Operating” string to MCU_1.
5. When MCU_2 finishes sending, LED_0 in MCU_2 will be toggled.
6. When MCU_1 finishes receiving the “Confirm BCM Operating” string, LED_1 in MCU_1 will be toggled.

## Video
> [Basic Communication Manager](https://drive.google.com/file/d/1NR1UsJ8t6ufDnGrmhph00tEdxW7Xndsq/view?usp=sharing)

