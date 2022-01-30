#include <WebUSB.h>
#include <EEPROM.h>

/**
 * Creating an instance of WebUSBSerial will add an additional USB interface to
 * the device that is marked as vendor-specific (rather than USB CDC-ACM) and
 * is therefore accessible to the browser.d
 *
 * The URL here provides a hint to the browser about what page the user should
 * navigate to to interact with the device.
 */

WebUSB WebUSBSerial(0 /* https:// */, "localhost:8000");

#define Serial WebUSBSerial

const int buzzPin = 10;
int frequency;

const int buttonPin = 2;
const int ledPin = 5;
int buttonState = 0;

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  while (!Serial) {
    ;
  }
  Serial.begin(9600);
  Serial.write("Sketch begins.\r\n");
  Serial.flush();
}

void loop() {
  buttonState = digitalRead(buttonPin);
    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
    Serial.write("W");
    Serial.flush();
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }
  
  if (Serial && Serial.available()) {
    frequency = Serial.read();
    
    tone(buzzPin, frequency, 250);
    // Wait for the specief duration before playing the next note.
    //delay(100);
    
    // stop the waveform generation before the next note.
    //noTone(buzzPin);
  }

  
}
