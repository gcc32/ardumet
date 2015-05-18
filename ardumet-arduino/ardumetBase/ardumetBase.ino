//
//    FILE: ardumetBase.ino
//  AUTHOR: Gonzalo de la Cruz
// VERSION: 0.1
//  CREDIT: Based on original work from the VirtualWire lib developers
// PURPOSE: Multi-sensor weather station based on Arduino (UNO). This is the base (receiver) module.
// LICENSE: Open-source, under the MIT License
//
// The MIT License (MIT)

// Copyright (c) 2015 Gonzalo de la Cruz de la Cueva

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

/* 
Connect the Receiver data pin to Arduino pin 11 
*/

#include <VirtualWire.h>

byte message[VW_MAX_MESSAGE_LEN]; // a buffer to store the incoming messages 
byte messageLength = VW_MAX_MESSAGE_LEN; // the size of the message

void setup() 
{ 
    Serial.begin(9600);

    //Serial.println("Dispositivo listo para recibir datos:");
      
    // Initialize the IO and ISR 
    vw_setup(2000); // Bits per sec
    vw_rx_start(); // Start the receiver 
    
}
 
void receive_data(){
  String data;
    if (vw_get_message(message, &messageLength)) // Comprobamos la recepcion del mensaje y lo mostramos en tal caso. 
    { 
        for (int i = 0; i < messageLength; i++) 
        { 
        Serial.write(message[i]); 
        }
    Serial.println(data);     
    
    }  
}


void loop() 
{ 
  receive_data(); //Ejecutamos la funcion para capturar los datos recibidos
  delay(1000);  
}

