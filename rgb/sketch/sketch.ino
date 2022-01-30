#include <WebUSB.h>
#include <EEPROM.h>

/**
 * Creating an instance of WebUSBSerial will add an additional USB interface to
 * the device that is marked as vendor-specific (rather than USB CDC-ACM) and
 * is therefore accessible to the browser.
 *
 * The URL here provides a hint to the browser about what page the user should
 * navigate to to interact with the device.
 */

WebUSB WebUSBSerial(1 /* https:// */, "webusb.github.io/arduino/demos/rgb");

#define Serial WebUSBSerial

const int redPin = 5;
const int greenPin = 6;
const int bluePin = 9;

int color[3];
int colorIndex;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  
  analogWrite(redPin, EEPROM.read(0));
  analogWrite(greenPin, EEPROM.read(1));
  analogWrite(bluePin, EEPROM.read(2));

  while (!Serial) {
    ;
  }
  Serial.begin(9600);
  Serial.write("Sketch begins.\r\n");
  Serial.flush();
  
  colorIndex = 0;
}

void loop() {
  if (Serial && Serial.available()) {
    color[colorIndex++] = Serial.read();
    if (colorIndex == 3) {
      analogWrite(redPin, color[0]);
      analogWrite(greenPin, color[1]);
      analogWrite(bluePin, color[2]);

      EEPROM.write(0, color[0]);
      EEPROM.write(1, color[1]);
      EEPROM.write(2, color[2]);
      
      Serial.print("Set LED to ");
      Serial.print(color[0]);
      Serial.print(", ");
      Serial.print(color[1]);
      Serial.print(", ");
      Serial.print(color[2]);
      Serial.print(".\r\n");
      Serial.flush();
      colorIndex = 0;
    }
  }
}
