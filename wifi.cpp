#include <Arduino.h>
#include <WiFiUdp.h>
#include <user_interface.h>

#include "wifi.h"
#include "oled.h"
#include "lua.h"




WiFiUDP				_udpSender;
IPAddress			_broadcastIp;
int					_broadcastPort		= 0;
long				_lastHeartbeat		= 0;
struct netif*		_ESPif				= NULL;
netif_input_fn		_originalInputFn	= NULL;
long				_lastNetifInput		= 0;
wl_status_t			wifi_status			= WL_IDLE_STATUS;



extern "C" {
	struct netif* eagle_lwip_getif(uint8_t index);
	#include "netif/etharp.h"
}




err_t netif_input_local(struct pbuf* p, struct netif* inp) {
	_lastNetifInput = millis();
//	printPacketInfo(p);
	return _originalInputFn( p, inp );
}



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


/*
int MACsprintf( const uint8_t* MAC, char* buffer, size_t bufferLength ) {
	return snprintf( buffer, bufferLength, "%02X:%02X:%02X:%02X:%02X:%02X",
		MAC[0], MAC[1], MAC[2], MAC[3], MAC[4], MAC[5]);
}
*/


/*
int IPsprintf( const uint8_t* IP, char* buffer, size_t bufferLength ) {
	return snprintf( buffer, bufferLength, "%d.%d.%d.%d", IP[0], IP[1], IP[2], IP[3]);
}
*/


/*
void printPacketInfo(struct pbuf* p) {
	struct EtherFrame* FrameHeader = (struct EtherFrame*) p->payload;
	uint16_t type = swap16(FrameHeader->typeLength);
	uint8_t* data  = (uint8_t*)(p->payload);
	char text[128];


	if (type == 0x0806) {
//		printARP((uint8_t*)(p->payload));
//		Serial.println("");

	} else if (type == 0x0800) {
//		printIP((uint8_t*)(p->payload));
//		Serial.println("");

	} else {
		char srcMAC[ 32 ];
		char destMAC[ 32 ];
		MACsprintf( FrameHeader->srcMAC, srcMAC, sizeof( srcMAC ) );
		MACsprintf( FrameHeader->destMAC, destMAC, sizeof( destMAC ) );

		snprintf(text, sizeof(text), "Source: %s Dest: %s Type: %04X", srcMAC, destMAC, type );
		Serial.println(text);
		Serial.println("");
	}
}
*/


/*
void printARP(uint8_t* data) {
	char text[256];
	char srcMAC[32];
	char destMAC[32];
	char srcIP[32];
	char destIP[32];
	// uint16_t type = 0;

	struct etharp_packet* arp = (struct etharp_packet*)data;
	uint16_t opcode = swap16(arp->opcode);

	// filter - ONLY ME!!!
	//if (arp->dst_ip_addr[3] != 142 && arp->src_ip_addr[3] != 142 ) return;
	//if (arp->dst_ip_addr[3] == 1 || arp->src_ip_addr[3] == 1 ) return; // from/to the router

	IPsprintf(arp->src_ip_addr, srcIP, sizeof(srcIP) );
	IPsprintf(arp->dst_ip_addr, destIP, sizeof(destIP) );
	if (opcode == 1) snprintf(text, sizeof(text), "ARP => %s, Request", srcIP);
	else if (opcode == 2) snprintf(text, sizeof(text), "ARP <= %s, Reply", destIP);
	else snprintf(text, sizeof(text), ": ARP -----");
	Serial.println(text);

	MACsprintf(arp->hdr.srcMAC, srcMAC, sizeof(srcMAC));
	MACsprintf(arp->hdr.destMAC, destMAC, sizeof(destMAC));
	snprintf(text, sizeof(text), "ETH: Source: %s Dest: %s", srcMAC, destMAC);
	Serial.println(text);

	MACsprintf(arp->src_eth_addr, srcMAC, sizeof(srcMAC));
	MACsprintf(arp->dst_eth_addr, destMAC, sizeof(destMAC));
	snprintf(text, sizeof(text), "MAC: Source: %s Dest: %s", srcMAC, destMAC);
	Serial.println(text);

	snprintf(text, sizeof(text), "IP: Source: %s Dest: %s Opcode: %04X", srcIP, destIP, opcode );
	Serial.println(text);
}
*/


/*
void printIP(uint8_t* data) {
	char text[256];
	char srcMAC[32];
	char destMAC[32];
	char srcIP[32];
	char destIP[32];
	// uint16_t type = 0;

	struct udp_packet* udp = (struct udp_packet*)data;
	IPsprintf(udp->ip.ip_src_addr, srcIP, sizeof(srcIP));
	IPsprintf(udp->ip.ip_dst_addr, destIP, sizeof(destIP));

	snprintf(text, sizeof(text), "IP/%d %s ==> %s: port=%d", udp->ip.ip_proto, srcIP, destIP, swap16(udp->dst_port));
	Serial.println(text);
}
*/


/*
void printMyMac() {
	byte mac[6];
	WiFi.macAddress(mac);
	Serial.print(mac[0], HEX);
	Serial.print(":");
	Serial.print(mac[1], HEX);
	Serial.print(":");
	Serial.print(mac[2], HEX);
	Serial.print(":");
	Serial.print(mac[3], HEX);
	Serial.print(":");
	Serial.print(mac[4], HEX);
	Serial.print(":");
	Serial.print(mac[5], HEX);
}
*/



void wifi_setup() {
	_broadcastIp = ~WiFi.subnetMask() | WiFi.gatewayIP();
	_udpSender.begin(10010);

	if((_ESPif = eagle_lwip_getif(0)) != NULL) {
		_originalInputFn = _ESPif->input;
		_ESPif->input = netif_input_local;
	}

	_lastNetifInput = millis();
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

void wifi_loop() {
	wl_status_t status = WiFi.status();
	if (unlikely(status != wifi_status)) {
		wifi_status = status;
		wifi_display();

		if (wifi_status == WL_CONNECTED) {
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
	}


	if (likely(_broadcastPort > 0)  &&  unlikely(millis() - _lastHeartbeat >= 500)) {
		_lastHeartbeat = millis();
		_udpSender.beginPacket(_broadcastIp, _broadcastPort);
		_udpSender.write("foo");
		_udpSender.endPacket();
	}

	if (unlikely(millis() - _lastNetifInput >= 10000)) {
		_lastNetifInput = millis();
		char buf[100] = "";
		snprintf(buf, 100, FS("Unresponsive, resetting... (uptime %d)"), millis() / 1000);
		//Serial.println(buf);
		//ESP.restart();
	}
}

