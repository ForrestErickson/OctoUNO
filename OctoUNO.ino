/*OctoUNO
   A program for an Arduino Uno
   Makes UNO into an elementary curve tracer like an Ocotpus
   DISPLAY IV plot on PC with Processing.
   Useful for checking in circuit semiconductors and more.

   Author: Forrest L Erickson
   Date: 20210720  Happy Moon Landing Anniversary
   License: Dedicated to the public domain.
   Free to use. This program is designed to kill you but not guaranteed to do so.
   Date: 20210721 Rework circuits per note book Start 2013 Page 79 and then page 81.
   Date: 20210722 Got working with Proccessing DISPLAY program
   Date: 20210723 Added SCPI like command processor for start, stop, reset and IDN. 
   Add version number.
   Date: 20210924 Broke out Wink into module. Broke out Commands into module.   
*/

/*  An Ocotpus curve tracers sources and sinks current into a single port and plots the IV curve.
    If the DUT is and IC we are typicaly typicaly interested in probing the ESD input protection diodes.
    We typically test the device unpowered with VCC shorted to VSS (GND) and we probed with a positive and negative current limited voltage ramps.

    For the OcotUNO This will be done with done using one PWM output filtered and double buffered to make Vtest.
    The DUT will be tested by connecting from the Vtest into a Theven source at Vcc/2 with RThev = Req =10K/2

   Pinout
   Vtest from WPM on Pin 5.
   A0 to ICPin under test at Vtest
   A1 to ICPin under test at Vthev

   The current in the DUT is about 1uA per setup size from 1023/2

   RESULTS: The ramp voltage is from 1 to about 4.6 Volts. Ramp time is about 210mS when delay is 300uS.
*/

// Import required libraries


//--------------- Includes ---------------------------
#include "Arduino.h"
#include "wink.h"
#include "commands.h"

//Some program constants
extern const String COMPANY = "Amused Scientist";
extern const String MODEL_NAME = "OctoUNO";
extern const String VERSION = "0.0.3";

//Hardware setup
const int VccTest = 5;    //Use PWM output 5, 980Hz.
const int BUTTON_CAPTURE = 2;   // Button to GND.
extern const int RESET_PIN = 12;   // To Drive HW Reset.

const int VCC = 5;  //Volts
const int REQ = 5000;   //REQ is the Rthevenin of 10K // 10K
const int MAXPWM = 255;
const int STEPSIZE = 1;

//const long BAUD =  115200;  // Slower but compatible with other deveopment.
const long BAUD =  1000000;  // For fast curve tracing.

//Variables for measurements
int ii = MAXPWM / 2; // Mid point
int Vdut = 0;
int Idut = 0;

//State of Octopus curve tracing set at start.
extern boolean isCaptureOcotopus = false;  

//String variable global
String inputString = "";         // a String to hold incoming data

//Set Wink time for BUILT IN LED for Uno or ESP32 Dev Kit on board blue LED.
//const int HIGH_TIME_LED = 900;
//const int LOW_TIME_LED = 100;
//long lastLEDtime = 0;
//long nextLEDchange = 100; //time in ms.

//void wink() {
//  //Wink the LED
//  if (((millis() - lastLEDtime) > nextLEDchange) || (millis() < lastLEDtime)) {
//    if (digitalRead(LED_BUILTIN) == LOW) {
//      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
//      nextLEDchange = HIGH_TIME_LED;
//    } else {
//      digitalWrite(LED_BUILTIN, LOW);   // turn the LED on (HIGH is the voltage level)
//      nextLEDchange = LOW_TIME_LED;
//    }
//    lastLEDtime = millis();
//  }
//}//end LED wink


void captureOctopus() {
  //Curve Trace. Measure A0, A1
  //Calculate Vdut and Idut
  int VdutPlus = analogRead(A0);
  int VdutMinus = analogRead(A1);
  Vdut = VdutPlus - VdutMinus;
  Idut = (VdutMinus - 512); //uAmps

  //  Serial.print(VdutPlus);
  Serial.print(Vdut);
  Serial.print(", ");
  Serial.println(Idut);
  //  Serial.println(Idut-Vdut);

  //Ramp VccTest
  //Serial.println(ii);
  analogWrite(VccTest, ii);
  ii = ii + STEPSIZE;
  if (ii > MAXPWM) {
    ii = 0;
  }
  delayMicroseconds(300);     // This makes a display good for oscilliscope.
  //  delayMicroseconds(2000);     // Sweep on Display is notacibly slow.
}//captureOcotpus


void setup() {
  // put your setup code here, to run once:
  Serial.begin(BAUD);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);

  pinMode(BUTTON_CAPTURE, INPUT_PULLUP);      // set

  pinMode(LED_BUILTIN, OUTPUT);      // set the LED pin mode
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level) Start of setup()

  //Set PWM drive pins to output.
  pinMode(VccTest, OUTPUT);
  analogWrite(VccTest, 127);  //Set to mid point
  digitalWrite(LED_BUILTIN, LOW);   // end of setup()
}

void loop() {
  // put your main code here, to run repeatedly:
  winkLED_BUILTIN;
  //wink(); //the built in LED.
 
  if (isCaptureOcotopus) {
    captureOctopus();
  }

  //Proccess button function
  if (!digitalRead(BUTTON_CAPTURE)) {
    delay(10);
    isCaptureOcotopus = !isCaptureOcotopus;
  }

 checkCommands(); //from serial port

}//Loop
