# SpecialCar
![Special Car](/Images/20200710_134028.jpg)

## Overview
Special car prototype, Arduino based, controlled via android app over Bluetooth. Represents the movement of a real car, equiped with all necessary lights (winkers, front and back lights), as well as special lights.

## Hardware
- Arduino Uno board
- L293D motor driver
- HC-06 bluetooth module
- 2x 1.5V DC motors
- 8x LED
- 2x 9V battery; Copper wires; Resistors; Breadboard; Switch;

![Layout](/Images/Stylized%20schema.jpg)


## Software
- Android Bluetooth app controller made with MIT App Inventor
  - Speed control
  - Automated acceleration
  - Automated slowdown when not pressing move button
  - Emergency break
  - Lights control with button status indication
  
- Arduino source code
  - State management
  - Acceleration and speed control
  - Lights control
  

![Code Blocks Schema](/Images/Code%20Block%20Schema.jpg)
