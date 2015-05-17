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
    if (vw_get_message(message, &messageLength)) // Comprobamos la recepcin del mensaje y lo mostramos en tal caso. 
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

