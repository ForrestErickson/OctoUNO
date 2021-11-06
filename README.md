# OctoUNO
20210803 NOTE: I have made a project repository with a schematic and PCB. I have copied and this repository into that product and intend to do any updates there 
See; https://github.com/ForrestErickson/OctoUNO_Product  
**CAUTION:** the software here at the OctoUNO web site may be out of date. 

## A Curve Tracer "Ocotopus" program for an Arduino Uno with Display in Processing   
   Makes UNO into an elementary curve tracer like an Ocotpus    
   DISPLAY IV plot on PC with Processing.    
   Useful for checking in circuit semiconductors and more.     
   Author: Forrest L Erickson    
   Date: 20210720  Happy Moon Landing Anniversary    
   License: Dedicated to the public domain.    
   Free to use. This program is designed to kill you but not guaranteed to do so.   
   Date: 20210721 Rework circuits per note book Start 2013 Page 79 and then page 81. 
   Date: 20210722 Got working with Proccessing DISPLAY program
   Date: 20210723 Added SCPI like command processor for start, stop, reset and IDN. Add version number.   
   Date: 20210924 Broke out Wink into module. Broke out Commands into module.
   Date: 20210924 Debounce the start and stop button with DailyStruggleButton library. NICE!.
   Date: 20210311 Change button capture from D2 to D3 to match the KiCAD SMD PCB Version 0.0.1.
   Date: 20211101 Add delay at bottom of ramp so the falling edge at output of the filter gets low.
   Date: 20211101 Impliment minimal CLS command.
   Date: 20211101 Change version to 4.
   Date: 20211103 Change version to 5.  Add offset to zero current measurement.
   Date: 20211103 Change version to 6.  Fixed call to wink in loop.
   Date: 20211105 Change version to 7.  Send Idut as uA on serial port. Remove dead button code.
   Date: 20211106 Auto format.*/
   
For some theory, here is a video presentation and explination about component testing using an "Ocotopus"   https://www.youtube.com/watch?v=WWY-pakm_OM   
   
The OctoUNO in action  
Screen shot of display  
![DISPLAY](/ScreenShotDisplay.png)


Schematic  
![SCHEMATIC](/SchematicLabNoteBook81.png)

Breadboard  
![Breadboard](/OctoUnoBreadboard.jpg)


