#include <ezButton.h>                                                // ezButton library
#define SWITCH_OFF 0

ezButton button (A0);                                                // Create ezButton object attached to Analog Read A0

byte ledPins[] = {3, 4, 5, 6};                                       // Array of LED pins
byte notes[] = {1, 2, 3, 4};                                         // Array of Note Messages to be sent via Serial to Processing
long previousMillis;                                                 // Variable which is updated against Millis() in order to loop through LEDs and Note Messages
long interval;                                                       // Variable which sensorValue is mapped to below
int i = 0;
int sensorValue;                                                     // Variable which reads from Analog Input A1 below
int sensorLow = 0;
int sensorHigh = 1023;
int switch_state = SWITCH_OFF;                                       // Switch off as initial state of Button


void setup() {
  Serial.begin(9600);                                                // Begin Serial communication, Baud rate of 9600
  button.setDebounceTime(50);                                        // 50ms debounce time
  
  for (int thisPin = 0; thisPin < sizeof(ledPins); thisPin++) {      // Defines Output Pins of LED pins in Array
    pinMode(ledPins[thisPin], OUTPUT);
  }
  ledPins[3,4,5,6] == notes[1,2,3,4];                                // notes which will be sent to Processing are equivalent to LEDs
  previousMillis = millis();                                         // as this is in setup, it means that previousMillis is 0
}


void loop() {
  sensorValue = analogRead(A1);                                      // Sensor Value is equal to the input from the Phototransistor coming in Analog Input (A1)
  int interval = map(sensorValue,sensorLow,sensorHigh,60,2000);      // The Sensor Value is mapped to an interval between 60ms and 2 seconds
                                                                     // The time values can be adjusted, making them effective to amount of light in a given room
  
  button.loop();                                                     // call the button loop() function

  if (button.isPressed()) {
    switch_state = !switch_state;                                    // change state of switch if button is pressed
  }

  if (switch_state == SWITCH_OFF){                                   // if switch state is off, each LED in the array is off
    for (int l = 0; l < sizeof(ledPins); l++){
      digitalWrite(ledPins[l], LOW);

  }
  }
  
  else{                                                              // if switch state is not off, loop through the following code
    if (millis() - previousMillis > interval) {                      // if time elapsed minus previous time is more than interval (which is adjusted according to light)
      previousMillis = millis();                                     // update the value of previous time

    if (i < sizeof(ledPins) - 1) {                                   // if i is less than the number of LED pins -1
      digitalWrite(ledPins[i], LOW);                                 // Turn off previous LED pin
      digitalWrite(ledPins[++i], HIGH);                              // Turn on next LED (increasing the value of i)
      Serial.write(notes[i]);                                        // Send Equivalent Note-On Messages for each LED HIGH across Serial to Processing
    }

    else if (i == sizeof(ledPins) - 1) {                             // if i is equal to the number of LED pins - 1, which means that it has reached the final LED
      i = 0;                                                         // reset i to 0
      digitalWrite(ledPins[i], HIGH);                                // First LED lights up, completing the loop through LEDs
      Serial.write(notes[i]);                                        // Send Equivalent Note-On Message across Serial to Processing
      digitalWrite(ledPins[sizeof(ledPins) - 1], LOW);               // Turn off previous LED Pin, which is the last LED pin
    }
    }
  }
}
