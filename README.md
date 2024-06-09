# IoT-Hydroponics-System-Using-ESP32

**Motivation:**

Hydroponic farming, powered by IoT technology, is a revolutionizing method of agriculture, optimizing resource use and increasing yields. Traditional methods face constraints like limited land and water scarcity, which hydroponics overcomes by growing plants in a soil-less, nutrient-rich water solution. IoT integration enables precise monitoring and management of environmental factors like temperature, luminosity and water level, leading to higher yields and reduced resource consumption. With scalability and adaptability, hydroponics with IoT offer sustainable solutions for local food production.

**Objectives:**
* Accurate Monitoring: Develop a system capable of accurately measuring water level and temperatures in a tank.
* Real-time Data: Provide the user with real-time data updates through a user-friendly dashboard.
* Data storage: Store data in a visual database, that allows for analysis of the system health and results.
* Scalability: Design the system to be scalable, allowing for integration with various tank sizes and types.
* Accessibility: Ensure that the system is easy to develop, requiring minimal technical knowledge for repoduction.

**Hardware:**
* Ultrasonic sensor: Used for measuring water level in the tank.
* Temperature sensor: Employed to measure the temperature of the water.
* Microcontroller (We are using an ESP32 DEV MODULE) : Controls the sensors, processes data, and communicates with the server.

**Software:**
* Embedded software: Runs on the microcontroller to collect data from sensors and transmit it to the server.
* HiveMQ: MQTT mechanism used to send data from/to the device.
* Node-Red: Configures the flow of data to de the Database.
* InfluxDB: Database used in the project.
* Grafana: Integrated with InfluxDB To analyze data and show a dashboard.

**Architecture:** [Architecture Diagram](https://github.com/GuiMaFol/Water-Tank-Monitoring-System-Using-ESP32/blob/main/Architecture.png)

# Installation Manual
Follow these steps to install the water tank monitoring system:

**Hardware Installation:**

* Mount the ultrasonic sensor inside the water tank at an appropriate height to measure water levels accurately.
* Install the temperature sensor in the water tank to measure the temperature of the water.
* Connect the sensors to the microcontroller according to the provided wiring diagram.
* Power up the system using a suitable power source.

**Arduino IDE - ESP32:**

Select Files > Preferences, then it's necessary to enter the following URL in the field:
https://raw.githubsercontent.com/espressif/arduino-esp32/gh-pages/package-esp32_index.json <br/>
After that, click "OK", then select Tools > Board > Board Manager
Search for ESP32 and install it.
This ensures that the Arduino IDE installed on the device can upload the program to the ESP32 board.

**Library installation:**

For the ESP32 Wifi connection and MQTT communication of the board with other devices, the installation of two main libraries in the Arduino IDE is required:<br/>
<Wifi.h>, which ensures the Wifi connection;<br/>
<PubSubClient.h>, which ensures the connection to the MQTT broker, subscribing to a topic, and publishing data related to sensors and actuators.<br/>
Subsequently, there is a need to include the libraries related to the sensor used for data capture (Temperature), as they are necessary for converting the electrical magnitude data to physical magnitude (ºC), such as:<br/>
<OneWire.h>;<br/>
<DallasTemperature.h>;<br/>

**Circuit:**[Circuit](https://github.com/GuiMaFol/Water-Tank-Monitoring-System-Using-ESP32/blob/main/Circuit.png)

**Pin Configuration:**

Sensors: For the temperature sensor (ds18B20), connect its pins as follows:<br/>
* Power (Vcc) connects to 3V3 (3.3V);<br/>
* Ground connects to GND;<br/>
* Data connects to pin D4;<br/>
For temperature data capture, it is necessary to have a 4.7k Ohms resistor between the sensor's "Vcc" and the "Data" pin. Now, for the proximity ultrasonic sensor (HC-sr04), the pin configuration is as follows:<br/>
* Power (Vcc) connects to VIN (5V);<br/>
* Ground (Gnd) connects to GND;<br/>
* Trigger (Trig) is connected to pin D5;<br/>
* Echo (Echo) is connected to pin D18;<br/>
Actuator pin configuration (at this stage of development, LEDs are being used to represent both Heating and Pump) in relation to ESP32:<br/>
* For heating, pin D22 is used;<br/>
* For the pump, pin D2 is used;<br/>

**WiFi Connection (script):**

For the device's WiFi connection, after library installation, it is necessary to input the SSID and WiFi password as follows;<br/>
* Line 8 - SSID definition, where the WiFi ID to be connected must be placed;<br/>
* Line 9 - Introduction of the WiFi network password, placed between quotes ("").

**MQTT Connection (script):**

To ensure the connection, some parameters need to be configured, these are;<br/>
* The MQTT ID, configured in line 13 of the script, where the ID used for the connection should be placed between quotes ("");<br/>
* The MQTT Broker, configured in line 14 of the script, where the used broker (in this case, "broker.hivemq.com") should be placed between quotes ("");<br/>
* The PORT, in line 15: in the MQTT_PORT section, it will be 1883 (as in the program);<br/>
* In lines 16 and below, the topics to publish and subscribe are presented. You must place the topics used for the MQTT connection between quotes ("").<br/>
From this point, the connection to the broker and subscription to the topic will be effective.

**Software Setup:**

* Upload the embedded software to the microcontroller using the Arduino IDE or similar software.
* Configure the microcontroller to connect to the appropriate Wi-Fi network.
* Set-up Node-Red, InfluxDB and Grafana.
* Import the provided .json file to Node-Red.
* Configure the Influxdb out nodes with your information, especially the API Token.
* Now the sensor information should be displayed in InfluxDB, and can be sent to Grafana for the creation of a dashboard.
* To do That, create a InfluxDB database in Grafana, fill the correct information and import the data by copying the bucket script.
* if necessary, this video can help with the intergration of the three softwares: https://www.youtube.com/watch?v=riBycGMDJMo

**Verification:**
Verify that the sensors are accurately measuring water level and temperature.
Verify that the system is updating when the pump is turned on or off.

**Maintenance:**
Periodically check the system for any issues or malfunctions.
Replace sensors or components as needed.
Keep the software up to date with the latest updates and security patches.

**Justification for using the MQTT protocol:**
The choice to use the MQTT protocol for communication between devices is due to the widespread use of this type of protocol for IoT services, becoming a standard for these types of applications, as it ensures service quality through QoS (Quality of Service) settings, guaranteeing security, and creating a priority scale among services. It is also worth noting that communication occurs through messages that are transmitted lightly and efficiently, making it relatively fast compared to other available protocols, considering the tank monitoring application, which uses message publishing and reading for system control and monitoring.
