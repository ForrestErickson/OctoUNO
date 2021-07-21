/*OctoUNO
   A progam for an Arduino Uno
   Makes Uno into an elementary curve tracer like an Ocotpus
   Useful for checking incircuit semiconductors and more.

   Author: Forrest L Erickson
   Date: 20210720  Happy Moon Landing Annaversary
   License: Dedicated to the public domain.
   Free to use. This program is designed to kill you but not guarenteed to do so.
   Date: 20210721 Rework circuits per note book Start 2013 Page 79 and then page 81.
*/

/*  An Ocotpus curve tracers sorces and sinks current into a single port and plots the IV curve.
    If the DUT is and IC we are typicaly typicaly interested in probing the ESD input protection diodes.
    We typicaly test the device unpowered with VCC shorted to VSS (GND) and we probed with a postive and negative current limited voltage ramps.

    For the OcotUNO This will be done with done using one PWM output filtered and double buffered to make Vtest.
    The DUT will be tested by connecting from the Vtest into a theven source at Vcc/2 with Req =10K/2

   Pinout
   Vtest from WPM on Pin 5.
   A0 to ICPin under test at Vtest
   A1 to ICPin under test at Vthev

   The current in the DUT is about 1uA per setup size from 1023/2

   RESULES: The ramp voltage is from 1 to about 4.6 Volts. Ramp time is about 210mS when delay is 300uS.
*/

int VccTest = 5;    //Use PWM output 5, 980Hz.
const int VCC = 5;  //Volts
const int REQ = 5000;   //REQ is the Rthevenin of 10K // 10K
const int MAXPWM = 255;
const int STEPSIZE = 1;
int ii = MAXPWM / 2; // Mid point
int Vdut = 0;
int Idut =0; 


//Set LED for Uno or ESP32 Dev Kit on board blue LED.
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
  }//end LED wink

}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(1000000);

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

  //Curve Trace. Measure A0, A1
  //Calculate Vdut and Idut
  int VdutPlus = analogRead(A0);
  int VdutMinus = analogRead(A1);
  Vdut = VdutPlus-VdutMinus;
  Idut = (VdutMinus- 512);  //uAmps
 
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
  
}//Loop
