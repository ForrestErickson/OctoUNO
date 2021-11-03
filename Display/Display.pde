/*Display
 * Forrest Lee Erickson
 * Date: 20210721
 Based on a serial example by Tom Igoe
 License: Dedicated to the public domain.
 Free to use. This program is designed to kill you but not guaranteed to do so.
 Date: 20210723 Added Mouse control and SCPI like command processor for start, stop, reset and IDN.  
 Date: 20211101 Added *CLS command. Add 'q' to send reset command to instrument and user instructions.  Incremet to Rev 0.0.3.  
 Date: 20211103 Rev 0.0.4. Parameterize margins for text placement. Enlarge display for full dynamic range. Add tick marks and axis lables.   
 */

//final int COMPORTNUM = 4;    //Change the port number as necessary
final int COMPORTNUM = 5;    //Change the port number as necessary

import processing.serial.*;

String COMPANY = "Amused Scientist";
String MODELNAME = "OctoUNO";
String VERSION = "0.0.4";


int lf = 10;    // Linefeed in ASCII
String myString = null;
Serial myPort;  // The serial port
int BAUDRATE = 1000000 ;

//Setup display
//scale and colors 
final int myWidth = 800;
final int myHeight = 800;
final int DATA_SIZE = 5;  //Size of points
final int TICK_LEN = 2; 
//final int MINOR_TICK_LEN = 1; 
final color myBLACK = color(0, 0, 0);
final color myGRAY = color(128, 128, 128);
color myBackground = myBLACK;  //Start out gray.
final int VOLTAGE_SCALE = 1024/5 ; //Volts
final int CURRENT_SCALE = 1024/5 ;  //uAmps

boolean gotKey = false;

PFont f;                          // Declare regular body text PFont variable
PFont fBig;                          // Declare heading PFont variable
PFont fFoot;                          // Declare footer PFont variable

//Margins for text relative to edges
final int TOP_MARGIN = 20;
final int RIGHT_MARGIN = 10;
final int LEFT_MARGIN = 10;
final int BOTTOM_MARGIN = 10;


void setup() {
  // List all the available serial ports
  printArray(Serial.list());
  // Open the port you are using at the rate you want:
  myPort = new Serial(this, Serial.list()[COMPORTNUM], BAUDRATE);  //Arduino
  myPort.clear();
  // Throw out the first reading, in case we started reading 
  // in the middle of a string from the sender.
  myString = myPort.readStringUntil(lf);
  myString = null;

  //Display setup. The Arduino ADC has a range of 1023 split in half for the measurements. 
  size(800, 800);
  f = createFont("Arial", 15, true);     // Create Font normal text.
  fBig = createFont("Arial", 20, true);     // Create Font for large text on heading 
  fFoot = createFont("Arial", 10, true);     // Create Font for smaller text on footer 

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
        circle(int(myPoints[0])+myWidth/2, myHeight/2-int(trim(myPoints[1])), DATA_SIZE);
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
  text("OctoUNO", RIGHT_MARGIN, TOP_MARGIN);
  textFont(f);
  text("Left Mouse Start", RIGHT_MARGIN*2, TOP_MARGIN*2);
  text("Right Mouse Stop", RIGHT_MARGIN*2, TOP_MARGIN*3);
  text("Escape to exit", RIGHT_MARGIN*2, TOP_MARGIN*4);
  text("'r,g,b' background", RIGHT_MARGIN*2, TOP_MARGIN*5);
  text("'q' to reset", RIGHT_MARGIN*2, TOP_MARGIN*6);
  text("Any key to erase", RIGHT_MARGIN*2, TOP_MARGIN*7);
  textFont(fFoot);
  text(COMPANY + ", " + MODELNAME + ", Display Version: " + VERSION, RIGHT_MARGIN, (myHeight-BOTTOM_MARGIN));
  text("By Forrest Erickson", myWidth-100, (myHeight-10));
}//menuDisplay

void axisDraw() {
  pushMatrix();
  // draw graph -- center on origin
  translate(myWidth/2, myHeight/2);
  stroke(255);
  // draw axes
  line(-myWidth, 0, myWidth, 0); //Horizontal axis
  //Minor horizontal axis
  text("Volts", -(myWidth/2-RIGHT_MARGIN), -TOP_MARGIN);                              //Scale Lable
  line(VOLTAGE_SCALE, -(myHeight/100+TICK_LEN), VOLTAGE_SCALE, (myHeight/100+TICK_LEN)); //Horizontal mark
  text("-1", -(VOLTAGE_SCALE), TOP_MARGIN);                              //Scale Lable
  line(-VOLTAGE_SCALE, -(myHeight/100+TICK_LEN), -VOLTAGE_SCALE, (myHeight/100+TICK_LEN)); //Horizontal mark
  text("+1", VOLTAGE_SCALE, TOP_MARGIN);                              //Scale Lable
  
  line(0, -myHeight, 0, myHeight); //Vertical axis
  //Minor vertical axis
  text("Current", RIGHT_MARGIN, -(myHeight/2-TOP_MARGIN));                              //Scale Lable
  line(-(myWidth/100+TICK_LEN), -CURRENT_SCALE, (myWidth/100+TICK_LEN), -CURRENT_SCALE); //Vertical mark
  text("-500uA", -(RIGHT_MARGIN+3), (CURRENT_SCALE-1));                              //Scale Lable
  line(-(myWidth/100+TICK_LEN), CURRENT_SCALE, (myWidth/100+TICK_LEN), CURRENT_SCALE); //Vertical mark
  text("+500uA", -(RIGHT_MARGIN+3), -(CURRENT_SCALE+1));                              //Scale Lable
  
  stroke(32);
  popMatrix();
}//axisDraw

//end of program.
