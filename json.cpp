////////////////////////////////////////////////////////////////////////////////
// INCLUDE FILES
////////////////////////////////////////////////////////////////////////////////
#include <arduino.h>
#include <FS.h>

#include "json.h"
#include "spider.h"
#include "lua.h"
#include "wifi.h"




////////////////////////////////////////////////////////////////////////////////
// INITIALIZE LED ARRAYS FROM JSON CONFIG
////////////////////////////////////////////////////////////////////////////////
void json_setup() {
	json_init init[8];
	memset(init, 0xff, sizeof(init));
	json_parse(init, sizeof(init)/sizeof(json_init));

	for (auto &item : init) {
		switch (item.mode) {
			case LED_RGB:
			case LED_GRB:
			case LED_WRGB:
			case LED_WGRB:
				break;

			default:
				item.mode = LED_GRB;
		}



		switch (item.type) {


			case LED_ARRAY:

				if (item.pin >= 64  ||  item.pin < 0) {
					Serial.print(F("Invalid Array GPIO Pin: "));
					Serial.println(item.pin);
					continue;
				}

				if (item.length > 300  ||  item.length < 0) {
					Serial.print(F("Invalid Array Length: "));
					Serial.println(item.length);
					continue;
				}

				ledset.add(new led_array(
					item.pin,
					item.length,
					static_cast<LED_MODE>(item.mode)
				));

			break;




			case LED_GRID:

				if (item.pin >= 64  ||  item.pin < 0) {
					Serial.print(F("Invalid Grid GPIO Pin: "));
					Serial.println(item.pin);
				}


				if (item.width >= 256  ||  item.width < 0) {
					Serial.print(F("Invalid Grid Width: "));
					Serial.println(item.width);
					continue;
				}


				if (item.height >= 256  ||  item.height < 0) {
					Serial.print(F("Invalid Grid Width: "));
					Serial.println(item.height);
					continue;
				}

				ledset.add(new led_grid(
					item.pin,
					item.width,
					item.height,
					static_cast<LED_MODE>(item.mode)
				));

			break;


		}
	}
}




////////////////////////////////////////////////////////////////////////////////
// LOAD AND PARSE JSON DATA
////////////////////////////////////////////////////////////////////////////////
void json_parse(json_init *init, int count) {
	File json = SPIFFS.open(FS("/config.json"), "r");

	if (!json) {
		Serial.println(F("Failed to locate config.json"));
		return;
	}

	char *bytes = (char*) malloc(json.size()+1);
	json.readBytes(bytes, json.size());
	bytes[json.size()] = NULL;

	DynamicJsonBuffer config(4000);
	JsonObject &root = config.parseObject(bytes);

	if (!root.success()) {
		Serial.println(F("Error parsing JSON content"));
		free(bytes);
		return;
	}


	////////////////////////////////////////////////////////////////////////////////
	// PARSE JSON LED CONFIGURATION
	////////////////////////////////////////////////////////////////////////////////
	int x = -1;
	JsonArray &leds = root["led"];
	for (JsonObject &led : leds) {

		//IF THIS OBJECT DOESN'T HAVE THE TYPE PROPERTY, IGNORE IT
		if (!led.containsKey("type")) continue;

		//IF WE HAVE TOO MANY OBJECTS, BAIL
		if (++x >= count) break;

		String	type		= led["type"];

		if (type == "array") {
			init[x].type	= LED_ARRAY;
			if (led.containsKey("pin"))		init[x].pin		= led["pin"];
			if (led.containsKey("mode"))	init[x].mode	= led["mode"];
			if (led.containsKey("length"))	init[x].length	= led["length"];

		} else if (type == "grid") {
			init[x].type	= LED_GRID;
			if (led.containsKey("pin"))		init[x].pin		= led["pin"];
			if (led.containsKey("mode"))	init[x].mode	= led["mode"];
			if (led.containsKey("width"))	init[x].width	= led["width"];
			if (led.containsKey("height"))	init[x].height	= led["height"];

		} else {
			Serial.print(F("Unknown type: "));
			Serial.println(type);
		}

	}




	////////////////////////////////////////////////////////////////////////////////
	// PARSE WIFI CONFIGURATION
	////////////////////////////////////////////////////////////////////////////////
	String		mode	= root["wifi"];
	const char *ssid	= "Cosplay.Lighting";
	const char *pass	= "password";

	if (root.containsKey("ssid")) ssid = root["ssid"];
	if (root.containsKey("pass")) pass = root["pass"];


	if (mode == "station") {
		WiFi.mode(WIFI_STA);
		WiFi.begin(ssid, pass);

	} else {
		WiFi.softAPConfig(				//	TODO: MAKE THIS JSON CONFIGURABLE
			IPAddress(192,168,1,1),		//	IP ADDRESS
			IPAddress(192,168,1,1),		//	DEFAULT GATEWAY
			IPAddress(255,255,255,0)	//	SUBNET MASK
		);
		WiFi.mode(WIFI_AP);
		WiFi.softAP(ssid, pass);
	}



	free(bytes);
}
