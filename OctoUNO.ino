/*OctoUNO
   A progam for an Arduino Uno
   Makes Uno into an elementary curve tracer like an Ocotpus
   Useful for checking incircuit semiconductors and more.

   Author: Forrest L Erickson
   Date: 20210720  Happy Moon Landing Annaversary
   Lisense: Dedicated to the public domain.
   Free to use. This program is designed to kill you but not guarenteed to do so.
   Date: 20210721 Rework circuits per note book Start 2013 Page 79.
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

   RESULES: The ramp voltage is from 1 to about 4.6 Volts. Ramp time is about 250mS.
*/

int VccTest = 5;
const int MAXPWM = 255;
const int STEPSIZE = 1;
int ii = 511; 
  
//Set LED for Uno or ESP32 Dev Kit on board blue LED.
const int HIGH_TIME_LED = 900;
const int LOW_TIME_LED = 100;
long lastLEDtime = 0;
long nextLEDchange = 100; //time in ms.

void wink(){
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
void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);      // set the LED pin mode
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level) Start of setup()
  Serial.begin(115200);
  
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

  //Ramp VccTest
    Serial.println(ii);
    analogWrite(VccTest, ii);
    ii = ii + STEPSIZE;
    if (ii > MAXPWM){
      ii = 0;
    }
    delay(1);     //One millisecond
}//Loop
