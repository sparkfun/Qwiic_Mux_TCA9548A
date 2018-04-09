/*
  Qwiic Mux Shield - PCA9548A/TCA9548A Basic Control
  By: Nathan Seidle
  SparkFun Electronics
  Date: March 30th, 2017
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

  Reads two MMA8452Q accelerometers that have the same I2C address.
  You can read the MMA8452Q hookup guide and get the library from https://learn.sparkfun.com/tutorials/mma8452q-accelerometer-breakout-hookup-guide

  The PCA9548A is a mux. This means when you enableMuxPort(2) then the SDA and SCL lines of the master (Arduino)
  are connected to port 2. Whatever I2C traffic you do, such as accel.init() will be communicated to whatever
  sensor you have on port 2. You don't need accel2.init() or accel5.init().

  Outputs two sets of XYZ acceleration

  Hardware Connections:
  Attach the Qwiic Mux Shield to your RedBoard or Uno.
  Plug two Qwiic MMA8452Q breakout boards into ports 0 and 1.
  Serial.print it out at 9600 baud to serial monitor.

*/

#include <Wire.h>
#include <SparkFun_MMA8452Q.h> // Includes the SFE_MMA8452Q library

MMA8452Q accel;

#define NUMBER_OF_SENSORS 1

const byte portNumber = 4;

void setup()
{
  Serial.begin(9600);
  Serial.println("Qwiic Mux Shield Read Example");

  Wire.begin();

  enableMuxPort(portNumber); //Tell mux to connect to port X
  accel.init(); //Init the sensor connected to this port
  disableMuxPort(portNumber);

  Serial.println("Mux Shield online");
}

void loop()
{
  enableMuxPort(portNumber); //Tell mux to connect to this port, and this port only

  if (accel.available())
  {
    accel.read();

    Serial.print("Accel ");
    Serial.print(portNumber);
    Serial.print(": ");
    Serial.print(accel.cx, 2);
    Serial.print(" ");
    Serial.print(accel.cy, 2);
    Serial.print(" ");
    Serial.print(accel.cz, 2);
    Serial.print(" ");

    Serial.println(); // Print new line every time.
  }

  disableMuxPort(portNumber); //Tell mux to disconnect from this port

  delay(1); //Wait for next reading
}
