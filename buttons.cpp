/*buttons
   Proccess user inpub from buttons
   By: Forrest Lee Erickson
   Date: 20210924

   The button will manage turning OctoUNO capture on and off.
*/

//--------------- Includes ---------------------------
#include "Arduino.h"
#include "buttons.h"
#include <DailyStruggleButton.h> //Loaded from ARduino libray manager. See also: https://github.com/cygig/DailyStruggleButton

//external variables
//extern const String VERSION;
extern const int BUTTON_CAPTURE;   // Button to GND.
extern boolean isCaptureOcotopus;   //Manage the state of catpure

//Button debounce setup
// Time in ms you need to hold down the button to be considered a long press
unsigned int longPressTime = 1000;
  
// How many times you need to hit the button to be considered a multi-hit
byte multiHitTarget = 2; 

// How fast you need to hit all buttons to be considered a multi-hit
unsigned int multiHitTime = 400; 

//Buttons Event handler
// This function will be called whenever an event occurs.
// We pass the name of this callback function in set().
// It needs to take a parameter of the byte datatype.
// This byte will indicate the event.
// It needs to return void.
void buttonEvent(byte btnStatus){

  // We can use switch/case to run through what happens for each event
  switch (btnStatus){

    // onPress is indicated when the button is pushed down
    case onPress:
      //Serial.println("Button Pressed");
      break;

    // onRelease is indicated when the button is let go
    case onRelease:
      //Serial.println("Button Released");
      isCaptureOcotopus = !isCaptureOcotopus;
      break;

    // onHold is indicated whenever the button is held down.
    // It can be annoying so we will comment this out in this example.
//  case onHold:
//    Serial.println("Button Long Pressed");
//    break;

    // onLongPress is indidcated when you hold onto the button 
    // more than longPressTime in milliseconds
    case onLongPress:
      Serial.print("Buttong Long Pressed For ");
      Serial.print(longPressTime);
      Serial.println("ms");
      isCaptureOcotopus = true; // Force capture on.
      break;

    // onMultiHit is indicated when you hit the button
    // multiHitTarget times within multihitTime in milliseconds
    case onMultiHit:
//      Serial.print("Button Pressed ");
//      Serial.print(multiHitTarget);
//      Serial.print(" times in ");
//      Serial.print(multiHitTime);
//      Serial.println("ms");
      break;
    // catch and report error
      default :      
        //Serial.println("Button error.");
        ;
  }
}// end buttonEvent
