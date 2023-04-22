import processing.serial.*;
import ddf.minim.*;
 
Serial myPort;
Minim minim;
AudioPlayer player;
byte arbitraryCode = 97;
 
void setup()
{
  // In the next line, you'll need to change this based on your USB port name
  //myPort = new Serial(this, "/dev/tty.usbserial-A601FUX6", 9600);
  println(Serial.list());  // prints serial port list
  String portName = Serial.list()[1];  // find the right one from the print port list (see the console output). Your port might not be the first one on the list. 
  myPort = new Serial(this, portName, 115200);  // open the serial port  
  minim = new Minim(this);
 
  // Put in the name of your sound file below, and make sure it is in the same directory
  player = minim.loadFile("soundfile.mp3");
}
 
void draw() {
  while (myPort.available() > 0) {
    int inByte = myPort.read();
    if (inByte == arbitraryCode) {
      player.rewind();
      player.play();
    }
  }
}
