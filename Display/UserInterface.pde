//Signal key press. Change color on some keys
void keyPressed() {
  //Proccess keys of UI.
  //Clears screen and changes background color

  if (key!=CODED) { //Ignore ALT, CONTROL, SHIFT, UP, DOWN, LEFT and RIGHT
    if ((key== 'r'|| (key== 'R'))) {
      //background(255,0,0); // Red for no serial
      myBackground = color(127, 0, 0);
    } else if ((key== 'c'|| (key== 'C'))) {
      myPort.write("*CLS\n");  //Clear status command
      serialTimeStart = millis();
    } else if ((key== 'g'|| (key== 'G'))) {
      //background(255,0,0); // Red for no serial
      myBackground = color(0, 127, 0);
    } else if ((key== 'b'|| (key== 'B'))) {
      //background(255,0,0); // Red for no serial
      myBackground = color(0, 0, 127);
    } else if ((key== 'q'|| (key== 'Q'))) {
      myPort.write("*RST\n");  //Reset instrument on 'q'
    } else if ((key== 't'|| (key== 'T'))) {
      myPort.write("TRIG\n");  //Trigger instrument on 't'
      myPort.write("START\n");  //Trigger instrument on 't'  //Not a SCPI command.
    } else if ((key== 'v'|| (key== 'V'))) {
      myPort.write("*IDN?\n");  //Request instrument version
      serialTimeStart = millis();
    } else {  //Any other key
      myBackground = color(0, 0, 0);
    }
    gotKey = true;
  }// key not codded
}//keyPressed()


//Mouse commands
void mousePressed() {

  if (mouseButton == LEFT) {
    myPort.write("START\n");
    print("Start pressed.");
  } else if (mouseButton == RIGHT) {
    myPort.write("STOP\n"); 
    print("Stop pressed.");
  } else if (mouseButton == CENTER) {
    print("Center pressed.\n");
    gotKey = true;
  } else {  
    // No action
  }
}//end mousePressed
