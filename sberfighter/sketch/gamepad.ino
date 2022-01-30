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

WebUSB WebUSBSerial(0 /* https:// */, "localhost:4443");

#define Serial WebUSBSerial

const int button1Pin = 2;
const int button2Pin = 3;
const int button3Pin = 4;
const int button4Pin = 6;

void setup() {
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  pinMode(button3Pin, INPUT);
  pinMode(button4Pin, INPUT);
  
  while (!Serial) {
    ;
  }
  Serial.begin(9600);
  Serial.write("Sketch begins.\r\n");
  Serial.flush();
}

void loop() {
  if (digitalRead(button1Pin) == HIGH) {
    Serial.write("A");
  } else if(digitalRead(button2Pin) == HIGH) {
    Serial.write("S");
  } else if(digitalRead(button3Pin) == HIGH) {
    Serial.write("D");
  } else if(digitalRead(button4Pin) == HIGH) {
    Serial.write("F");
  }
  
  Serial.flush();
}
