
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

#define LEFTBUTTON 4
#define SELECTBUTTON 5
#define RIGHTBUTTON 6


static const byte PROGMEM cow[] = {
  0b00000100, 0b00001000, 
  0b00000100, 0b11101000, 
  0b00000011, 0b11110000, 
  0b00001111, 0b11111100, 
  0b00111110, 0b11110110, 
  0b00111011, 0b11111001, 
  0b00000011, 0b00000000, 
  0b00000010, 0b11111110, 
  0b00000101, 0b10010010, 
  0b00111101, 0b11010110, 
  0b00111101, 0b11111110, 
  0b01111101, 0b11111100, 
  0b10111110, 0b00000000, 
  0b10111111, 0b11110000, 
  0b10110111, 0b11110000, 
  0b00100100, 0b10010000, 
};
static const byte PROGMEM coin[] = {
  0x20, 0x70, 0xd8, 0x88, 0xd8, 0x70, 0x20
};

Adafruit_SSD1306 display(128, 64, &Wire, OLED_RESET);

ThreeWire myWire(RTCDAT, RTCCLK, RTCRST); 
RtcDS1302<ThreeWire> Rtc(myWire);


byte holdBuffer[3] = {0, 0, 0};
byte hunger = 124;
byte happiness = 67;

void menuSelect() {

  if (buttonPressed(LEFTBUTTON)) Serial.println("left button pressed");
  if (buttonPressed(RIGHTBUTTON)) Serial.println("right button pressed");
  if (buttonPressed(SELECTBUTTON)) Serial.println("select button pressed");
}

bool buttonPressed(int button) {
  if (button < 4 || button > 6) return false;
  if (holdBuffer[button-4] == 2) return true;
  return false;
}
void homeScreen() {

}

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
  display.clearDisplay();

  display.drawBitmap(
    (display.width()  - 16) / 2,
    (display.height() - 16) / 2,
    cow, 16, 16, 1);
  
  display.drawBitmap(display.width()-31, 0, coin, 5, 7, 1);

  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(104, 0);     // Money
  display.print("9085");
  // hunger, happy bars
  display.setCursor(0, 0);
  display.write(0x03);
  display.setCursor(0, 9);
  display.write(0x02);

  display.drawRect(7, 2, 20, 5, 1);
  display.drawRect(7, 9, 20, 5, 1);

  display.display();



}

void loop() {
  
  for (int buttonPin=4; buttonPin<=6; buttonPin++) {
    if (digitalRead(buttonPin) == HIGH) {
      holdBuffer[buttonPin-4] = min(3, holdBuffer[buttonPin-4] + 1);
      
        
    } else {
      holdBuffer[buttonPin-4] = 0;
    }
  }
  menuSelect();
  delay(50);
  

}
