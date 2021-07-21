/*Display
 * Forrest Lee Erickson
 * Date: 20210721
 Based on a serial example by Tom Igoe
 License: Dedicated to the public domain.
 Free to use. This program is designed to kill you but not guarenteed to do so.
 */

import processing.serial.*;

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
PFont fFoot;                          // Declare heading PFont variable


void setup() {
  // List all the available serial ports
  printArray(Serial.list());
  // Open the port you are using at the rate you want:
  myPort = new Serial(this, Serial.list()[5], BAUDRATE);  //Arduino
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
  while ( (myPort.available() > 0)) {
    myString = myPort.readStringUntil(lf);
    if (myString != null) {
      //     print(myString);
      String myPoints[] = splitTokens(myString, ", ");  
      //print(int(myPoints[0]));
      //print(", ");
      //println(int(trim(myPoints[1])));
      //      println(int(myPoints[1]));
      circle(int(myPoints[0])+300, 300-int(trim(myPoints[1])), 5);
    }
  }

  //Clear screen on key. Update screen color
  if (gotKey) {
    background(myBackground);
    gotKey = false;
  }//clear screen
}//draw()

//Signal key press. Change color on some keys
void keyPressed() {
  //Proccess keys of UI.
  //Clears screen and changes background color
  if ((key== 'r'|| (key== 'R'))) {
    //background(255,0,0); // Red for no serial
    myBackground = color(127, 0, 0);
  } else if ((key== 'g'|| (key== 'G'))) {
    //background(255,0,0); // Red for no serial
    myBackground = color(0, 127, 0);
  } else if ((key== 'b'|| (key== 'B'))) {
    //background(255,0,0); // Red for no serial
    myBackground = color(0, 0, 127);
  } else {  //Any other key
    myBackground = color(0, 0, 0);
  }
  gotKey = true;
}//keyPressed()


void menuDisplay() {  
  textFont(fBig);
  text("OctoUNO", 30, 20);
  textFont(f);
  text("Escape to exit", 30, 40);
  text("Any key to erase", 30, 60);
  textFont(fFoot);
  text("By Forrest Erickson, Amused Scientist", 310, 590);
}//menuDisplay

void axisDraw() {
  pushMatrix();
  // draw graph -- center on origin
  translate(myWidth/2, myHeight/2);
  stroke(255);
  // draw axes
  line(-myWidth, 0, myWidth, 0);
  line(0, -myHeight, 0, myHeight);
  stroke(127);
  popMatrix();
}//axisDraw
