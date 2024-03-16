# Drone-control-system-for-users-with-extended-requirements
The hands-free control system for the DJI Tello drone.

The project involves creating a head-mounted platform that allows controlling the flight of a DJI Tello drone using gyroscope readings and recognized voice commands.

To create the project, please assemble the following components:
  - MPU6050 3-axis gyro module,
  - ESP32,
  - Arduino Nano 33 BLE Sense (The rev2 version was used, but the basic version can also be utilized),
  - On/off switch like e.g SMRS-1,
  - 18650 battery and charging module with 5V step-up converter,
  - couple of wires,
  - DJI Tello drone.

**CONNECTION DIAGRAM**


Connect the elements according to the following diagram. You can power the microcontrollers via the USB port or directly to the pins, but remember that Arduino Nano Sense cannot be powered with 5V directly to the pins. If you want to power this board using the pins, you must first connect the jumper at the bottom of the board. The connected GPIO pins between the two boards are responsible for 6 voice commands, the recognition of which is signaled by a high state.
The commands available in the project are: up, down, left, right, forward and backward.

![schemat](https://github.com/oskar0701/Drone-control-system-for-users-with-extended-requirements/assets/117591871/3c22c7b4-028c-46c5-8c77-407cc2828be0)

**ESP SIDE**

It's best to start by uploading the program to the control side of the drone, i.e., the ESP32. The program also includes sending flight instructions based on gyroscope axis deflections and handling voice commands coming from another microcontroller, but more on that in a moment.

The changes you need to make in the code involve declaring the SSID broadcasted by your drone and the password. If you don't know the password, you probably never changed it - by default, it's empty. 

![image](https://github.com/oskar0701/Drone-control-system-for-users-with-extended-requirements/assets/117591871/17051d70-2e70-4379-9c60-8179ad4e07ba)

If you wish, you can make changes to the threshold values in ifology(:D) ​​for axis deflections for your convenience of use.

Flash the code to the board. Now you can control the flight of the drone using the gyroscope connected to the board. The startup procedure is automatic as soon as the connection with the drone is established. However, remember that at this stage, the code does not include landing (unless you set a high state on the pin corresponding to the 'down' command).
