# Drone-control-system-using-gyro-and-micro-speech-model
The hands-free control system for the DJI Tello drone.

The project involves creating a head-mounted platform that allows controlling the flight of a DJI Tello drone using gyroscope readings and recognized voice commands using a model trained on the Tensorflow Lite engine.

To create the project, please assemble the following components:
  - MPU6050 3-axis gyro module,
  - ESP32,
  - Arduino Nano 33 BLE Sense (The rev2 version was used, but the basic version can also be utilized),
  - On/off switch like e.g SMRS-1,
  - 18650 battery and charging module with 5V step-up converter,
  - couple of wires,
  - DJI Tello drone.

****CONNECTION DIAGRAM****

Connect the elements according to the following diagram. You can power the microcontrollers via the USB port or directly to the pins, but remember that Arduino Nano Sense cannot be powered with 5V directly to the pins. If you want to power this board using the pins, you must first connect the jumper at the bottom of the board. The connected GPIO pins between the two boards are responsible for 6 voice commands, the recognition of which is signaled by a high state.
The commands available in the project are: up, down, left, right, forward and backward.

![schemat](https://github.com/oskar0701/Drone-control-system-using-gyro-and-micro-speech-model/assets/117591871/7119259e-32fd-4274-ad60-23505d97c64e)

**ESP SIDE**

It's best to start by uploading the program to the control side of the drone, i.e., the ESP32. The program also includes sending flight instructions based on gyroscope axis deflections and handling voice commands coming from another microcontroller, but more on that in a moment.

The changes you need to make in the code involve declaring the SSID broadcasted by your drone and the password. If you don't know the password, you probably never changed it - by default, it's empty. 

![image](https://github.com/oskar0701/Drone-control-system-for-users-with-extended-requirements/assets/117591871/17051d70-2e70-4379-9c60-8179ad4e07ba)

If you wish, you can make changes to the threshold values in ifology(:D) ​​for axis deflections for your convenience of use.

Flash the code to the board. Now you can control the flight of the drone using the gyroscope connected to the board. The startup procedure is automatic as soon as the connection with the drone is established. However, remember that at this stage, the code does not include landing (unless you set a high state on the pin corresponding to the 'down' command).

**ARDUINO SIDE**

Flash the code to the board using Arduino mbedOS package that you can find in your board manager. The code provides for the recognition of 6 voice commands, the recognition of which causes a high state on the appropriate pin. 

If you want to train your own model, read this article: https://www.hackster.io/shahizat/micro-speech-command-recognition-with-tensorflow-lite-44dc5a

Check whether command recognition does not enter the noise band by manipulating the value of the detection_threshold variable in the recognize commands.h header file. In my case, setting the value of this variable to 160 gave the best results.

![image](https://github.com/oskar0701/Drone-control-system-for-users-with-extended-requirements/assets/117591871/d2107676-92cf-4ee0-9bea-3a17f48db99f)

**SOFTWARE INTEGRATION**

The boards communicate using logical 0 and 1. When a voice command is recognized, the high state is displayed for a second. During this time, it is received by ESP32 and, depending on the pin, the drone's flight instructions are handled. 

Functionalities available for each command:
- up: increasing the height by 50cm,
- down: decreasing the height by 40cm or landing if the drone is at a height below 30 cm,
- left: ccw 40 degress,
- right: cw 40 degress,
- forward: frontflip,
- backward: backflip,

If you want, you can declare your own command support.

The project's operation is presented in the following network of activities:

![Diagram bez tytułu (1)](https://github.com/oskar0701/Drone-control-system-using-gyro-and-micro-speech-model/assets/117591871/02dcdab9-21d5-4d84-9e8c-e92f13e86955)


**BIBLIOGRAPHY**

Tello control lib: https://github.com/akshayvernekar/telloArduino

Tensorflow Lite examples: https://www.tensorflow.org/lite/microcontrollers
