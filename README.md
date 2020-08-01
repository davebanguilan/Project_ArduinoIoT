# Project_ArduinoIoT
Arduino IoT - Firebase

Soil Monitoring System
  An Arduino project that monitors soil moisture using soil moisture sensor. It uses 2 WeMos D1 mini where one microcontroller acts as a transmitter and the other one acts as a receiver. The soil moisture sensor is connected to the transmitter and 2 LED lights (Red and Green) is connected to it to indicate the soil moisture content (Red - Below 50%, Green - Greater than 50%), the transmitter sends the data to the Firebase Cloud. The Receiver reads the data on the Firebase Cloud and saves the read data in a MicroSD card using the Arduino Micro SD card Module. The two microcontroller can work even in great distance as long as they are connected in WiFi.

DS3231 Library
Firebase Library

