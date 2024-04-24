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

**Installation Manual:**
Follow these steps to install the water tank monitoring system:

**Hardware Installation:**
Mount the ultrasonic sensor inside the water tank at an appropriate height to measure water levels accurately.
Install the temperature sensor in the water tank to measure the temperature of the water.
Connect the sensors to the microcontroller according to the provided wiring diagram.
Power up the system using a suitable power source.

**Arduino IDE - ESP32:**
Select Files > Preferences, then it's necessary to enter the following URL in the field:
https://raw.githubsercontent.com/espressif/arduino-esp32/gh-pages/package-esp32_index.json
After that, click "OK", then select Tools > Board > Board Manager
Search for ESP32 and install it.
This ensures that the Arduino IDE installed on the device can upload the program to the ESP32 board.

**Library installation:**
For the ESP32 Wifi connection and MQTT communication of the board with other devices, the installation of two main libraries in the Arduino IDE is required:
<Wifi.h>, which ensures the Wifi connection;
<PubSubClient.h>, which ensures the connection to the MQTT broker, subscribing to a topic, and publishing data related to sensors and actuators.
Subsequently, there is a need to include the libraries related to the sensor used for data capture (Temperature), as they are necessary for converting the electrical magnitude data to physical magnitude (ºC), such as:
<OneWire.h>;
<DallasTemperature.h>;

**Pin Configuration:**
Sensors: For the temperature sensor (ds18B20), connect its pins as follows:/
Power (Vcc) connects to 3V3 (3.3V);/
Ground connects to GND;/
Data connects to pin D4;/
For temperature data capture, it is necessary to have a 4.7k Ohms resistor between the sensor's "Vcc" and the "Data" pin. Now, for the proximity ultrasonic sensor (HC-sr04), the pin configuration is as follows:/
-Power (Vcc) connects to VIN (5V);/
-Ground (Gnd) connects to GND;/
-Trigger (Trig) is connected to pin D5;/
-Echo (Echo) is connected to pin D18;/
Actuator pin configuration (at this stage of development, LEDs are being used to represent both Heating and Pump) in relation to ESP32:/
-For heating, pin D22 is used;/
-For the pump, pin D2 is used;/

**WiFi Connection (script):**
For the device's WiFi connection, after library installation, it is necessary to input the SSID and WiFi password as follows;/
-Line 8 - SSID definition, where the WiFi ID to be connected must be placed;/
-Line 9 - Introduction of the WiFi network password, placed between quotes ("").

**MQTT Connection (script):**
To ensure the connection, some parameters need to be configured, these are;/
-The MQTT ID, configured in line 13 of the script, where the ID used for the connection should be placed between quotes ("");/
-The MQTT Broker, configured in line 14 of the script, where the used broker (in this case, "broker.hivemq.com") should be placed between quotes ("");/
-The PORT, in line 15: in the MQTT_PORT section, it will be 1883 (as in the program);/
-In lines 16 and 17, the topics to subscribe, publish, and subscribe are presented. You must place the topics used for the MQTT connection between quotes ("")./
From this point, the connection to the broker and subscription to the topic will be effective.

**Software Setup:**
Upload the embedded software to the microcontroller using the Arduino IDE or similar software.
Configure the microcontroller to connect to the appropriate Wi-Fi network.
Set up the Arduino IoT Cloud (Device, Sketch, Thing and Dashboard).

**Verification:**
Verify that the sensors are accurately measuring water level and temperature.
Verify that the system is updating when the pump or heater is turned on or off.

**Maintenance:**
Periodically check the system for any issues or malfunctions.
Replace sensors or components as needed.
Keep the software up to date with the latest updates and security patches.

**Justification for using the MQTT protocol:**
The choice to use the MQTT protocol for communication between devices is due to the widespread use of this type of protocol for IoT services, becoming a standard for these types of applications, as it ensures service quality through QoS (Quality of Service) settings, guaranteeing security, and creating a priority scale among services. It is also worth noting that communication occurs through messages that are transmitted lightly and efficiently, making it relatively fast compared to other available protocols, considering the tank monitoring application, which uses message publishing and reading for system control and monitoring.
