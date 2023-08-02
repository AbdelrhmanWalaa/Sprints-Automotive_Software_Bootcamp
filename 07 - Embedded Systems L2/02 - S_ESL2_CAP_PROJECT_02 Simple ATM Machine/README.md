# Simple ATM Machine

<p align="center">
  <img src="https://github.com/AbdelrhmanWalaa/Sprints-Automotive_Software_Bootcamp/assets/44446382/10f99409-b314-4e19-afc1-3e9a3ebfb3ae" alt="Simple ATM Machine">
</p>

## Overview

This project aims to develop software for simulating a simple ATM machine transaction. The system will consist of two main components: the ATM ECU (Electronic Control Unit) and the CARD ECU, which communicate with each other to perform various transaction tasks.

The ATM ECU will handle the main transaction flows, including PIN validation, amount withdrawal, and database checks, while the CARD ECU will trigger the ATM to proceed with the transaction.

## Project Goals

- Create a user-friendly interface on the ATM MCU, featuring a 16x2 LCD and a 3x3 Keypad, to guide users through the transaction process.
- Implement a secure PIN verification system, allowing users to enter their PIN in a safe manner, with an alarm triggered after three failed attempts.
- Enable the user to enter the withdrawal amount with a maximum limit of "5000.00," ensuring the ATM performs necessary database checks before approving the transaction.
- Design a hard-coded database (array of structures) on the ATM MCU, containing card details, account states, and balances for transaction validation.
- Implement communication between the ATM ECU and CARD ECU using a Serial Terminal (e.g., Putty on PC) to trigger the transaction and update the account state.

## Expected Outcomes

- A functional ATM simulation software running on the ATM MCU, providing users with clear instructions and feedback during the transaction process.
- A secure PIN verification system, preventing unauthorized access and triggering an alarm after multiple failed attempts.
- A database implementation on the ATM MCU, enabling seamless and efficient checks for card validity, account status, available balance, and daily transaction limits.
- An accurate display of transaction results, including successful transaction approval and the updated account balance.
- A reliable communication mechanism between the ATM ECU and CARD ECU, ensuring smooth initiation and completion of transactions.

## Contributors

> [Abdelrhman Walaa](https://github.com/AbdelrhmanWalaa) |
> [Hossam Elwahsh](https://github.com/HossamElwahsh) |
> [Mahmoud Mowafey](https://github.com/Mahmoud-Mowafy)

## Video
> [Simple ATM Machine](https://drive.google.com/file/d/1Yt83rPD1v7XGVWoWsxdxXpQTE4M2Eeba/view?usp=sharing)

