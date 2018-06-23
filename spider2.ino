#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiUdp.h>
#include <FS.h>

#include "src/elapsedMillis/elapsedMillis.h"

#include "spider.h"
#include "server.h"
#include "wifi.h"
#include "lua.h"
#include "json.h"
#include "oled.h"



elapsedMillis	render_time;
led_render		ledset		= led_render();



//ENABLE ADC READING OF INPUT VOLTAGE INSTEAD OF EXTERNAL PIN
ADC_MODE(ADC_VCC);



static char flash_buffer[100];
const char *_FS(const void *item) {
	return strncpy_P(flash_buffer, (const char*)item, sizeof(flash_buffer));
}




////////////////////////////////////////////////////////////////////////////////
// INITIALIZE ALL THE THINGS UPON BOOT UP
////////////////////////////////////////////////////////////////////////////////
void setup(void){
	//INITIALIZE SERIAL PORT FIRST FOR DEBUGGING
	Serial.begin(115200);
	Serial.println("\nSpider Board"); //INTENTIONALLY WITHOUT F("")

	//RANDOM DELAY, BECAUSE WHY THE HELL NOT !?
	//THIS HELPS STABILIZE THE OLED DISPLAY
	delay(2000);

	//START WITH WIFI DISABLED
	WiFi.mode(WIFI_OFF);


	//SHOW STARTUP INFORMATION
	Serial.println(F(""));
	Serial.print(F("STARTUP ("));
	Serial.print(ESP.getResetReason());
	Serial.print(F(") "));
	Serial.println(ESP.getChipId());


	Serial.println(F("Turning on OLED..."));
	init_oled();


	Serial.println(F("Starting file system..."));
	SPIFFS.begin();


	Serial.println(F("Loading config.json file..."));
	json_setup();


	Serial.println(F("Starting wifi..."));
	wifi_setup();


	Serial.println(F("Starting web server..."));
	server_setup();


	//INITIALIZE LUA
	lua_setup();


	//LOAD THE INITIAL BOOT SCRIPT
	lua_file(FS("/boot.lua"));


	//TEST LUA
	//EVAL DOESNT LIKE FS("")
	Serial.println(F("Testing lua script..."));
	spider_eval("esp.print('Lua is operational')");

	Serial.println(F("RUNNING!"));
	render_time = 0;
}




////////////////////////////////////////////////////////////////////////////////
// THE MAIN PROGRAM LOOP THAT HAPPENS FOREVER
////////////////////////////////////////////////////////////////////////////////
void ICACHE_RAM_ATTR loop() {
	//PROCESS RENDER LOOP ONLY EVERY 20 MILLISECONDS - 50 FRAMES PER SECOND
	if (unlikely(render_time >= 20)) {
		render_time -= 20;

		//IF WE'RE TOO FAR BEHIND, DROP ALL PENDING FRAMES
		if (unlikely(render_time >= 20)) {
			render_time = 0;
		}

		//UPDATE PALETTE ANIMATIONS
		led_grid::increment();

		//RUN SCRIPT FRAME CODE
		if (likely(can_render)) {
			spider_method("frame");
		}

		//UPDATE THE LEDS
		ledset.render();
	}

	//LUA GARBAGE COLLECTION
	if (likely(lua)) lua_gc(lua, LUA_GCCOLLECT, 1);

	//HANDLE ANY WIFI DATA
	wifi_loop();

	//HANDLE ANY NEW SERVER REQUESTS
	_server.handleClient();
}
