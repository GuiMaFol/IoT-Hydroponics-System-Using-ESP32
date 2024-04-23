# Water-Tank-Monitoring-System-Using-ESP32

**Motivation:**
Water is a precious resource, and its efficient management is crucial for both domestic and industrial purposes. This project aims to address the need for accurate and real-time monitoring of variables that indicate the quality of the water environment, by providing users with real-time information about water level, temperature, pump and heater staus. The User can track the water level and conservation, schedule maintenance and keep the water tank in the desired characteristics.

**Objectives:**
Accurate Monitoring: Develop a system capable of accurately measuring water level and temperatures in a tank.
Real-time Data: Provide the user with real-time data updates through a user-friendly dashboard.
Alert System: Implement an alert system to notify users of critical water level or temperature fluctuations.
Scalability: Design the system to be scalable, allowing for integration with various tank sizes and types.
Accessibility: Ensure that the system is accessible and easy to install, even for users with minimal technical knowledge.

**Hardware:**
Ultrasonic sensor: Used for measuring water level in the tank.
Temperature sensor: Employed to measure the temperature of the water.
Microcontroller (We are using an ESP32 DEV MODULE) : Controls the sensors, processes data, and communicates with the server.

**Software:**
Embedded software: Runs on the microcontroller to collect data from sensors and transmit it to the server.
Arduino IoT Cloud: Receives data from the ESP32, stores it in a database, and shows it to the user through a dashboard.
User interface: A web-based dashboard where the user can view the real-time status of their instalation (water level and temperature and if the pump and heater are on or not), set alerts, and configure the system.

**Architecture:** [Architecture Diagram](https://github.com/GuiMaFol/Water-Tank-Monitoring-System-Using-ESP32/blob/main/Architecture.png)

Installation Manual:
Follow these steps to install the water tank monitoring system:

Hardware Installation:
Mount the ultrasonic sensor inside the water tank at an appropriate height to measure water levels accurately.
Install the temperature sensor in the water tank to measure the temperature of the water.
Connect the sensors to the microcontroller according to the provided wiring diagram.
Power up the system using a suitable power source.

Software Setup:
Upload the embedded software to the microcontroller using the Arduino IDE or similar software.
Configure the microcontroller to connect to the appropriate Wi-Fi network.
Set up the Arduino IoT Cloud (Device, Sketch, Thing and Dashboard).

Verification:
Verify that the sensors are accurately measuring water level and temperature.
Verify that the system is updating when the pump or heater is turned on or off.

Maintenance:
Periodically check the system for any issues or malfunctions.
Replace sensors or components as needed.
Keep the software up to date with the latest updates and security patches.
