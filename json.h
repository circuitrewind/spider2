#ifndef __JSON_H__
#define __JSON_H__



#include <ArduinoJson.h>
#include "src/binary/inline.h"



struct PACKED json_init {
	int8_t				type;
	int8_t				pin;
	int8_t				mode;
	int8_t				__reserved;
	union PACKED {
		struct PACKED {
			int16_t		width;
			int16_t		height;
		};
		int32_t			length;
	};
};



extern void json_setup();
extern void json_parse(json_init *init, int count);
extern void json_led(JsonArray &leds, json_init *init, int count);
extern void json_wifi(JsonObject &root);


#endif //__JSON_H__
