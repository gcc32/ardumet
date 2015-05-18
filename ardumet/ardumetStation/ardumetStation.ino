//
//    FILE: ardumetStation.ino
//  AUTHOR: Javier Ramirez
// VERSION: 0.1
// PURPOSE: Multi-sensor weather station based on Arduino (UNO). This is the transmitter module.
// LICENSE: Open-source, under the MIT License
//
// The MIT License (MIT)

// Copyright (c) 2015 Javier Ramirez Diaz <javi.rmrz@gmail.com>

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.


#include <dht.h>           // for the DHT11 humidity-temperature sensor
#include <VirtualWire.h>   // for the RF transmitter

String weatherMsgAsString = "";
unsigned long timeSinceArdumetStartedRunning;

dht DHT;

#define DHT11_PIN A0
#define RAIN_PIN A2
#define LDR_PIN A1
// attach RF transmitter data pin to digital pin 12

#define OPERATION_LED 3    // will light when the ArduMET is up and running
#define TX_LED 5           // will light when the ArduMET is sending data through RF

#define UPDATE_RATE 1000 // time in miliseconds for the update/send rate

void lightOperationLED() {
  analogWrite(OPERATION_LED, 130);
}

void lightTxLED() {
  digitalWrite(TX_LED, HIGH);
  delay(50);
  digitalWrite(TX_LED, LOW);
}

void setup()
{
  Serial.begin(115200);
  Serial.println("ArduMET weather station up and ready.");
  Serial.print("Using DHT library version: ");
  Serial.println(DHT_LIB_VERSION);
  Serial.println("temperature  -  humidity  -  rain  -  light");

  pinMode(OPERATION_LED, OUTPUT);
  pinMode(TX_LED, OUTPUT);

  vw_setup(2000); // Bits per sec for the RF transmission

  lightOperationLED();
}

void loop() {

  int chk = DHT.read11(DHT11_PIN);
  switch (chk)
  {
    case DHTLIB_OK:
      Serial.print("OK,\t");
      break;
    case DHTLIB_ERROR_CHECKSUM:
      Serial.print("Checksum error,\t");
      break;
    case DHTLIB_ERROR_TIMEOUT:
      Serial.print("Time out error,\t");
      break;
    default:
      Serial.print("Unknown error,\t");
      break;
  }

  delay(1000);

  int rainSensor = analogRead(RAIN_PIN);
  int rainValue = map(rainSensor, 0, 1023, 0, 255);
  int LDRSensor = analogRead(LDR_PIN);
  int LDRValue = map(LDRSensor, 0, 1023, 0, 255);

  weatherMsgAsString = String(DHT.temperature) + ";" + String(DHT.humidity) + ";" + String(rainValue)  + ";" + String(LDRValue);

  const char *weatherMsgAsCharArray = weatherMsgAsString.c_str();

  vw_send((uint8_t *)weatherMsgAsCharArray, strlen(weatherMsgAsCharArray));
  vw_wait_tx(); // Wait until the whole message is gone
  lightTxLED();

  Serial.print("Message sent at ");
  timeSinceArdumetStartedRunning = millis();
  Serial.print(timeSinceArdumetStartedRunning);
  Serial.print(": ");
  Serial.println(weatherMsgAsCharArray);
  weatherMsgAsString = ""; // empty for the next iteration
  delay(UPDATE_RATE);
}
