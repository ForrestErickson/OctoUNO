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

const String COMPANY = "Amused Scientist";
const String MODEL_NAME = "OctoUNO";
const String VERSION = "0.0.2";

//Serial input variables
String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete
//Serial SCPI like commands
const String START = "START";
const String STOP = "STOP";
const String RESET = "RESET"; //Reset Command
const String RST = "*RST";    //Reset command 
const String IDN = "*IDN?";   //Identification Query
const String CLS = "*CLS";    //Clear status command


//Hardware setup
const int VccTest = 5;    //Use PWM output 5, 980Hz.
const int BUTTON_CAPTURE = 2;   // Button to GND.
const int RESET_PIN = 12;   // To Drive HW Reset.

const int VCC = 5;  //Volts
const int REQ = 5000;   //REQ is the Rthevenin of 10K // 10K
const int MAXPWM = 255;
const int STEPSIZE = 1;

//Variables for measurements
int ii = MAXPWM / 2; // Mid point
int Vdut = 0;
int Idut = 0;

//State of Octopus curve tracing set at start.
boolean isCaptureOcotopus = false;  


//Set Wink time for BUILT IN LED for Uno or ESP32 Dev Kit on board blue LED.
const int HIGH_TIME_LED = 900;
const int LOW_TIME_LED = 100;
long lastLEDtime = 0;
long nextLEDchange = 100; //time in ms.

void wink() {
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
  }
}//end LED wink


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
  Serial.begin(1000000);
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
  wink();
  if (isCaptureOcotopus) {
    captureOctopus();
  }

  //Proccess button function
  if (!digitalRead(BUTTON_CAPTURE)) {
    delay(10);
    isCaptureOcotopus = !isCaptureOcotopus;
  }

  //Command strings
  // print the string when a newline arrives:
  if (stringComplete) {
    //Serial.println(inputString);    //For debug of command strings
    inputString.toUpperCase();

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
      digitalWrite(RESET_PIN,LOW); // HW Reset
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
  }

}//Loop

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
