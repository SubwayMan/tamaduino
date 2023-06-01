
#include <SPI.h>
#include <SD.h>
#include <TMRpcm.h>

#define SPEAKER 3
#define SDCS 9

byte holdBuffer[3] = {0, 0, 0};


void setup() {
  Serial.begin(115200);
  // buttons
  for (int pin=4; pin<=6; pin++) {
    pinMode(pin, INPUT);
  }

  if (!SD.begin(SDCS)) {
    Serial.print("Fuck");
    while (1);
  }
  Serial.print("SD card workie workie");

}

void loop() {
  // put your main code here, to run repeatedly:
  for (int buttonPin=4; buttonPin<=6; buttonPin++) {
    if (digitalRead(buttonPin) == HIGH) {
      holdBuffer[buttonPin-4] = min(3, holdBuffer[buttonPin-4] + 1);    

      if (holdBuffer[buttonPin-4] == 2) {
        Serial.print("Press event: button ");
        Serial.println(buttonPin-4);
      }
    } else {
      holdBuffer[buttonPin-4] = 0;
    }
    
  }
  delay(50);

}
