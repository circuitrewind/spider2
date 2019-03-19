////////////////////////////////////////////////////////////////////////////////
//INCLUDE FILES
////////////////////////////////////////////////////////////////////////////////
#include <arduino.h>
#include "oled.h"



Adafruit_SSD1306 oled = Adafruit_SSD1306();



void init_oled() {

	// INITIALIZE WITH THE I2C ADDR 0x3C (for the 128x32)
	oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
	oled.clearDisplay();
	oled.display();

	// SET THE TEXT COLOR TO WHITE
	oled.setTextColor(WHITE);

	// RENDER "SPIDER BOARD"
	oled.setTextSize(2);
	oled.setCursor(0,0);
	oled.print(F("Spider\nBoard"));

	// RENDER "2"
	oled.setTextSize(3);
	oled.setCursor(84,8);
	oled.print(F("2"));

	// RENDER "0"
	oled.setCursor(110,8);
	oled.print(F("0"));

	// RENDER "." (BETWEEN 2 AND 0)
	oled.setTextSize(2);
	oled.setCursor(99,16);
	oled.print(F("."));

	// DISPLAY THE RESULT
	oled.display();
}
