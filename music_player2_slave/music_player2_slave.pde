import processing.serial.*;
import ddf.minim.*;
 
Serial myPort;
Minim minim;
AudioPlayer player;
AudioPlayer player2;
byte arbitraryCode = 97;
//byte arbitraryCode2 = 98;
int lf = 10;    // Linefeed in ASCII
 
void setup()
{
  // In the next line, you'll need to change this based on your USB port name
  //myPort = new Serial(this, "/dev/tty.usbserial-A601FUX6", 9600);
  println(Serial.list());  // prints serial port list
  String portName = Serial.list()[2];  // find the right one from the print port list (see the console output). Your port might not be the first one on the list. 
  myPort = new Serial(this, portName, 9600);  // open the serial port  
  myPort.bufferUntil(lf);
  minim = new Minim(this);
 
  // Put in the name of your sound file below, and make sure it is in the same directory
  player = minim.loadFile("key01.mp3");
  //player2 = minim.loadFile("key03.mp3");
}
 
void draw() {
  println(myPort.available());
  while (myPort.available() > 0) {
    int inByte = myPort.read();
    //println("play");
    if (inByte == arbitraryCode) {
      
      player.rewind();
      player.play();
    }
    /*if (inByte == arbitraryCode2) {
      //println("play");
      player2.rewind();
      player2.play();
    }*/
  }
}
