
//#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <EEPROM.h>
#include <RtcDS1302.h>
#define SPEAKER 10
#define SCREEN_ADDRESS 0x3C
#define OLED_RESET -1
#define RTCCLK 7
#define RTCDAT 8
#define RTCRST 9
//static const unsigned char PROGMEM image_data_Saraarray[1024] = {


Adafruit_SSD1306 display(128, 64, &Wire, OLED_RESET);

ThreeWire myWire(RTCDAT, RTCCLK, RTCRST); 
RtcDS1302<ThreeWire> Rtc(myWire);


byte holdBuffer[3] = {0, 0, 0};

void setup() {
  Serial.begin(115200);

  Rtc.Begin();

  // buttons
  for (int pin=4; pin<=6; pin++) {
    pinMode(pin, INPUT);
  }

  pinMode(SPEAKER, OUTPUT);
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 failed to start"));
    while (1);
  }
  display.display();



}

void loop() {
  
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
