/*
  Software serial multple serial test
 
 Receives from the two software serial ports, 
 sends to the hardware serial port. 
 
 In order to listen on a software port, you call port.listen(). 
 When using two software serial ports, you have to switch ports
 by listen()ing on each one in turn. Pick a logical time to switch
 ports, like the end of an expected transmission, or when the 
 buffer is empty. This example switches ports when there is nothing
 more to read from a port
 
 Two devices which communicate serially are needed.
 * First serial device's TX attached to digital pin 0, RX to pin 1
 * Second serial device's TX attached to digital pin 7, RX to pin 8

 With serial devices, always connect a TX to RX and RX to TX.
 Avoid the common mistake of automatically connecting signals with
 the same name together, as is done with SPI and Wire.  With Serial
 the signal names indicate direction.
 
 created 18 Apr. 2011
 modified 25 May 2012
 by Tom Igoe
 based on Mikal Hart's twoPortRXExample
 
 This example code is in the public domain.
 
 */

#include <SoftwareSerial.h>
// software serial #1: RX = digital pin 0, TX = digital pin 1
SoftwareSerial portOne(0,1);

// software serial #2: RX = digital pin 7, TX = digital pin 8
SoftwareSerial portTwo(7,8);

void setup()
{
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }


  // Start each software serial port
  portOne.begin(9600);
  portTwo.begin(9600);
}

void loop()
{
  // By default, the last intialized port is listening.
  // when you want to listen on a port, explicitly select it:
  portOne.listen();
  Serial.println("Data from port one:");
  // while there is data coming in, read it
  // and send to the hardware serial port:
  while (portOne.available() > 0) {
    char inByte = portOne.read();
    Serial.write(inByte);
  }

  // blank line to separate data from the two ports:
  Serial.println();

  // Now listen on the second port
  portTwo.listen();
  // while there is data coming in, read it
  // and send to the hardware serial port:
  Serial.println("Data from port two:");
  while (portTwo.available() > 0) {
    char inByte = portTwo.read();
    Serial.write(inByte);
  }

  // blank line to separate data from the two ports:
  Serial.println();
}






