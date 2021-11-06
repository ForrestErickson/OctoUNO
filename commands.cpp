/*commands
   Proccess serial port commands
   By: Forrest Lee Erickson
   Date: 20210924
   
   Date: 20211106 Auto format.
*/

//--------------- Includes ---------------------------
#include "Arduino.h"
#include "commands.h"

//external variables
extern String inputString ;         // a String to hold incoming data
extern boolean isCaptureOcotopus ;
extern int RESET_PIN;
extern const String COMPANY;
extern const String MODEL_NAME;
extern const String VERSION;


bool stringComplete = false;  // whether the string is complete
//Serial SCPI like commands
const String START = "START";
const String STOP = "STOP";
const String RESET = "RESET"; //Reset Command
const String RST = "*RST";    //Reset command
const String IDN = "*IDN?";   //Identification Query
const String CLS = "*CLS";    //Clear status command



void checkCommands() {
  //Command strings
  // print the string when a newline arrives:
  if (stringComplete) {
    //Serial.println(inputString);    //For debug of command strings
    inputString.toUpperCase();

    if ( inputString.startsWith(CLS)) {
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
      Serial.println("Clear command status.");
      //To do  Clear ?
    }

    if ( inputString.startsWith(START)) {
      Serial.println("Got command start!");
      isCaptureOcotopus = true;
    }

    if ( inputString.startsWith(STOP)) {
      Serial.println("Got command stop!");
      isCaptureOcotopus = false;
    }
    if ( inputString.startsWith(RST) || inputString.startsWith(RESET) ) {
      Serial.println("Got command to reset!");
      pinMode(RESET_PIN, OUTPUT);
      digitalWrite(RESET_PIN, LOW); // HW Reset
    }
    if ( inputString.startsWith(IDN)) {
      Serial.print(COMPANY); Serial.print(", ");
      Serial.print(MODEL_NAME); Serial.print(", ");
      Serial.print("VERSION: ");
      Serial.println(VERSION);
    }

    //End of strin proccessing so clear the string:
    inputString = "";
    stringComplete = false;
  }// proccessing command strings.
}//end checkCommands


/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}//end serialEvent
