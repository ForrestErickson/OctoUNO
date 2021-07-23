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
  } else if ((key== 'v'|| (key== 'V'))) {
    myPort.write("*IDN?\n");  //Request instrument version
  } else {  //Any other key
    myBackground = color(0, 0, 0);
  }
  gotKey = true;
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
    print("Center pressed.");
    gotKey = true;
  } else {  
    // No action
  }
}//end mousePressed
