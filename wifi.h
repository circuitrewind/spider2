#ifndef __WIFI_H__
#define __WIFI_H__



#include <ESP8266WiFi.h>
#include <lwip/netif.h>
#include "src/pingalive/src/PingAlive.h"



void wifi_setup();
void wifi_loop();
void wifi_display();
void wifi_connected();



#endif //__WIFI_H__
