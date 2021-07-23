/*Display
 * Forrest Lee Erickson
 * Date: 20210721
 Based on a serial example by Tom Igoe
 License: Dedicated to the public domain.
 Free to use. This program is designed to kill you but not guaranteed to do so.
 Date: 20210723 Added Mouse control and SCPI like command processor for start, stop, reset and IDN.  
 */

import processing.serial.*;

String COMPANY = "Amused Scientist";
String MODELNAME = "OctoUNO";
String VERSION = "0.0.2";


int lf = 10;    // Linefeed in ASCII
String myString = null;
Serial myPort;  // The serial port
int BAUDRATE = 1000000 ;

int myWidth = 600;
int myHeight = 600;
color myBackground = color(0, 0, 0);  //Start out black.
boolean gotKey = false;

PFont f;                          // Declare regular body text PFont variable
PFont fBig;                          // Declare heading PFont variable
PFont fFoot;                          // Declare footer PFont variable

void setup() {
  // List all the available serial ports
  printArray(Serial.list());
  // Open the port you are using at the rate you want:
  myPort = new Serial(this, Serial.list()[4], BAUDRATE);  //Arduino
  myPort.clear();
  // Throw out the first reading, in case we started reading 
  // in the middle of a string from the sender.
  myString = myPort.readStringUntil(lf);
  myString = null;

  //Display setup. The Arduino ADC has a range of 1023 split in half for the measurements. 
  size(600, 600);
  f = createFont("Arial", 15, true);     // Create Font 
  fBig = createFont("Arial", 20, true);     // Create Font for heading 
  fFoot = createFont("Arial", 10, true);     // Create Font for heading 

  stroke(153);
  background(myBackground);
}

//Gather measurements of V and I from the Arduino serial port and plot same. 
void draw() {
  menuDisplay();
  axisDraw();

  //PLot curve trace points
  while ( (myPort.available() > 0)) {
    myString = myPort.readStringUntil(lf);
    if (myString != null) {
      print(myString);
      String myPoints[] = splitTokens(myString, ", ");  
      //print(int(myPoints[0]));
      //print(", ");
      //println(int(trim(myPoints[1])));
      //      println(int(myPoints[1]));
      if (myPoints.length == 2) { //Plot only if two elements to select only XY data.
        circle(int(myPoints[0])+300, 300-int(trim(myPoints[1])), 5);
      }
    }
  }//end PLot curve trace points

  //Clear screen on key. Update screen color
  if (gotKey) {
    background(myBackground);
    gotKey = false;
  }//clear screen
}//draw()


void menuDisplay() {  
  textFont(fBig);
  text("OctoUNO", 30, 20);
  textFont(f);
  text("Left Mouse Start", 30, 40);
  text("Right Mouse Stop", 30, 60);
  text("Escape to exit", 30, 80);
  text("Any key to erase", 30, 100);
  textFont(fFoot);
  text(COMPANY + ", " + MODELNAME + ", Version: " + VERSION, 10, 590);
  text("By Forrest Erickson", 500, 590);
}//menuDisplay

void axisDraw() {
  pushMatrix();
  // draw graph -- center on origin
  translate(myWidth/2, myHeight/2);
  stroke(255);
  // draw axes
  line(-myWidth, 0, myWidth, 0);
  line(0, -myHeight, 0, myHeight);
  stroke(32);
  popMatrix();
}//axisDraw

//end of program.
