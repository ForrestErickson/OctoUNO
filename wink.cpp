/* wink.cpp
    Winkes the LED_BUILTIN


*/

//--------------- Includes ---------------------------
#include "Arduino.h"
#include "wink.h"


//Wink constants and variables.
//Set LED for Uno or ESP32 Dev Kit on board blue LED.
//const int LED_BUILTIN = 2;    // ESP32 Kit
//const int LED_BUILTIN = 13;    //Not really needed for Arduino UNO it is defined in library
const int HIGH_TIME_LED = 900;
const int LOW_TIME_LED = 100;
long lastLEDtime = 0;
long nextLEDchange = 100; //time in ms.



void setupWinkStart(void) {
  //Use LED_BUILDIN to instrument start and stop of setup().
  pinMode(LED_BUILTIN, OUTPUT);      // set the LED pin mode
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
}


void setupWinkEnd(void) {
  //Use LED_BUILDIN to instrument start and stop of setup().
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off at end of setup
}




void winkLED_BUILTIN(void) {

  //Wink the LED
  if (((millis() - lastLEDtime) > nextLEDchange) || (millis() < lastLEDtime)) {
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
