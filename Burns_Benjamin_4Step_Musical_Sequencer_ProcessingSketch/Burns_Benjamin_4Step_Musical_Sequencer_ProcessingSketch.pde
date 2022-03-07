import processing.serial.*;                                  //import serial and sound libraries
import processing.sound.*;

SinOsc sine;                                                 // Create object from SinOsc class
Env env;                                                     // Create object from Env class

float attackTime = 0.2;                                      // Define envelope characteristics
float sustainTime = 0.1;
float sustainLevel = 0.01;
float releaseTime = 0.03;

Serial myPort;                                               // Create object from Serial class
int val;                                                     // Data received from the serial port
int change;                                                  // 

void setup(){
  String portName = Serial.list()[1];
  myPort = new Serial(this, portName, 9600);
  sine = new SinOsc(this);
  env  = new Env(this);
}

void draw(){
  if (myPort.available() > 0) {                              // If data is available
    val = myPort.read();                                     // read it and store it in val
  }
  
  println(val);                                              // check that serial communication is incoming correctly

  if (val != change){                                        // Run this code if val is not equal to glob, and each time val changes store it in glob
    change = val;                                            // So notes will only trigger when data input no. changes, preventing multiple triggering of notes
    if (val == 1) {                                          // If the serial value is 1
    sine.play();                                             // play a sine wave at 494Hz with envelope values globally defined
    sine.freq(494);
    env.play(sine, attackTime, sustainTime, sustainLevel, releaseTime);
    }
    else if (val == 2) {                                     // If the serial value is 2
    sine.play();
    sine.freq(677);
    env.play(sine, attackTime, sustainTime, sustainLevel, releaseTime);
    }
        else if (val == 3) {                                 // If the serial value is 3
    sine.play();
    sine.freq(783);
    env.play(sine, attackTime, sustainTime, sustainLevel, releaseTime);
    }
        else if (val == 4) {                                 // If the serial value is 4
    sine.play();
    sine.freq(999);
    env.play(sine, attackTime, sustainTime, sustainLevel, releaseTime);
    }
}
}
