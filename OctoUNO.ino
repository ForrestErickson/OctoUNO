/*OctoUNO
   A progam for an Arduino Uno
   Makes Uno into an elementary curve tracer like an Ocotpus
   Useful for checking incircuit semiconductors and more.

   Author: Forrest L Erickson
   Date: 20210720  Happy Moon Landing Annaversary
   Lisense: Dedicated to the public domain.
   Free to use. This program is designed to kill you but not guarenteed to do so.

*/

/*  An Ocotpus curve tracers sorces and sinks current into a single port and plots the IV curve.
    If the DUT is and IC we are typicaly typicaly interested in probing the ESD input protection diodes.
    We typicaly test the device unpowered with VCC shorted to VSS (GND) and we probed with a postive and negative current limited voltage ramps.

    For the OcotUNO Ttis will be done with done using two PWM outputs connected to drive the VCC and VSS nodes push pull.

   Pinout
   A0 to ICPin under test
   VssTest, Pin ~5  will be PWM0 to test D2
   A1 to IC Vss and Vcc
   VccTest Pin ~6  will be PWM1 to test D1
*/

int VssTest = 5;
int VccTest = 6;


//Set LED for Uno or ESP32 Dev Kit on board blue LED.
//const int LED_BUILTIN = 2;    // ESP32 Kit
//const int LED_BUILTIN = 13;    //Not really needed for Arduino UNO it is defined in library
const int HIGH_TIME_LED = 900;
const int LOW_TIME_LED = 100;
long lastLEDtime = 0;
long nextLEDchange = 100; //time in ms.


void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);      // set the LED pin mode
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level) Start of setup()
  
  //Set both drive pins to low and to output.
  digitalWrite(VssTest, LOW);
  digitalWrite(VccTest, LOW);
  pinMode(VssTest, OUTPUT);
  pinMode(VccTest, OUTPUT);
  
  digitalWrite(LED_BUILTIN, LOW);   // end of setup()  
}

void loop() {
  // put your main code here, to run repeatedly:

    //Wink the LED
  if (((millis() - lastLEDtime) > nextLEDchange)||(millis()< lastLEDtime)) {
    if (digitalRead(LED_BUILTIN) == LOW) {
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
      nextLEDchange = HIGH_TIME_LED;
    } else {
      digitalWrite(LED_BUILTIN, LOW);   // turn the LED on (HIGH is the voltage level)
      nextLEDchange = LOW_TIME_LED;
    }
    lastLEDtime = millis();
  }//end LED wink

}
