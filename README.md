# ardumet
ardumet is a wireless, Arduino-based weather station. The project is open-source software and hardware, relased under the MIT license.

##Purpose
ardumet was first engineered as a college project. Therefore, it's not very mature and sophisticated, and can be improved in so many ways.

##What does it consist of
At the time of the first release, it consists on one wireless station (the data collector and RF transmitter), and the base station (RF receiver), which should be connected to a computer.

##Features
* Temperature sensor (±2ºC, not very accurate) [DHT11]
* Humidity sensor [DHT11]
* Ambient light sensor [LDR]
* Rain/water sensor [Funduino rain sensor]

* Wireless communication through a 433Mhz RF module (transmitter+receiver)
* Operation+transmission LEDs

##How-to
ardumet's station pinout
> * DHT11 to analog pin 0
> * LDR to analog pin 1
> * Rain sensor to analog pin 2
> * RF transmitter to digital pin 12
> * Operation LED to digital pin 3
> * Transmission LED to digital pin 5

ardumet's base pinout
> * RF receiver to digital pin 11

You will need at least two Arduino boards (UNO works as well as Mega). Wire as explained and load ardumetStation.ino and ardumetBase.ino, one in each board.

##To-do
* ardumet's receiver code does not work well :( (it takes the length of the first message, and if some following message is larger (due to changes in sensors, for example) it will just ignore the last part of the message)
* RF modules could be changed to Xbee or Bluetooth modules, though those are more expensive
* Solar panel with servo-based automatic orientation would be nice
* Add as many sensors as you can! ardumet lacks of any barometer, wind direction/speed sensor (anemometer)...
* Record data locally in a SD card in the remote station
* GPS location for precise forecasts