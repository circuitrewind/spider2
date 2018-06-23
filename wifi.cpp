#include <Arduino.h>
#include <WiFiUdp.h>
#include <user_interface.h>

#include "wifi.h"
#include "oled.h"
#include "lua.h"




wl_status_t			wifi_status			= WL_IDLE_STATUS;




static String softAPSSID() {
	struct softap_config config;
	wifi_softap_get_config(&config);
	const char* name = reinterpret_cast<const char*>(config.ssid);
	char ssid[sizeof(config.ssid) + 1];
	memcpy(ssid, name, sizeof(config.ssid));
	ssid[sizeof(config.ssid)] = '\0';

	return String(ssid);
}



static String softAPPSK() {
	struct softap_config config;
	wifi_softap_get_config(&config);
	const char* pass = reinterpret_cast<const char*>(config.password);
	char psk[sizeof(config.password) + 1];
	memcpy(psk, pass, sizeof(config.password));
	psk[sizeof(config.password)] = '\0';

	return String(psk);
}



void wifi_setup() {
}



void wifi_display() {
	//Prep OLED for display
	oled.clearDisplay();
	oled.setTextColor(WHITE);
	oled.setTextSize(1);

	bool ap = false;

	oled.setCursor(0,0);
	switch (WiFi.getMode()) {
		case WIFI_OFF:		oled.print(F("--: ")); break;
		case WIFI_STA :		oled.print(F("ST: ")); break;
		case WIFI_AP :		oled.print(F("AP: ")); ap=true; break;
		case WIFI_AP_STA:	oled.print(F("EX: ")); ap=true; break;
		default:			oled.print(F("??: ")); break;
	}
	oled.print(ap ? softAPSSID() : WiFi.SSID());

	oled.setCursor(0,12);
	oled.print(F("PW: "));
	oled.print(ap ? softAPPSK() : WiFi.psk());

	oled.setCursor(0,24);
	oled.print(F("IP: "));
	oled.print(ap ? WiFi.softAPIP() : WiFi.localIP());

	//Show final render on OLED
	oled.display();
}


/*
WL_NO_SHIELD        = 255,   // for compatibility with WiFi Shield library
WL_IDLE_STATUS      = 0,
WL_NO_SSID_AVAIL    = 1,
WL_SCAN_COMPLETED   = 2,
WL_CONNECTED        = 3,
WL_CONNECT_FAILED   = 4,
WL_CONNECTION_LOST  = 5,
WL_DISCONNECTED     = 6
*/


//TODO: DO SOMETHING HERE
void pingFault (void) {}



void wifi_connected() {
	startPingAlive();
	//TODO: FIND A WAY TO TURN PING ALIVE OFF ONCE CONNECTION IS LOST

	Serial.println(F("\nWifi connection established"));

	Serial.print(F("\tNetwork:\t"));
	Serial.println(WiFi.SSID());

	Serial.print(F("\tIP address:\t"));
	Serial.println(WiFi.localIP());

	Serial.print(F("\tSubnet mask:\t"));
	Serial.println(WiFi.subnetMask());

	Serial.print(F("\tGateway:\t"));
	Serial.println(WiFi.gatewayIP());

	Serial.print(F("\tDNS:\t\t"));
	Serial.println(WiFi.dnsIP());

	Serial.print(F("\tHostname:\t"));
	Serial.println(WiFi.hostname());

	Serial.println(F(""));
}




void wifi_loop() {
	wl_status_t status = WiFi.status();
	if (unlikely(status != wifi_status)) {
		wifi_status = status;
		wifi_display();

		if (wifi_status == WL_CONNECTED) {
			wifi_connected();
		}
	}
}

