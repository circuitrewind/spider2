////////////////////////////////////////////////////////////////////////////////
//INCLUDE FILES
////////////////////////////////////////////////////////////////////////////////
#include <arduino.h>

#include "src/ESP8266TrueRandom/ESP8266TrueRandom.h"

#include "lua.h"
#include "lua_esp.h"




////////////////////////////////////////////////////////////////////////////////
// RESET THE ENTIRE MICROCONTROLLER
////////////////////////////////////////////////////////////////////////////////
static int esp_reset(lua_State *lua) {
	ESP.reset();
	return 0;
}




////////////////////////////////////////////////////////////////////////////////
// RESTART THE ENTIRE MICROCONTROLLER
////////////////////////////////////////////////////////////////////////////////
static int esp_restart(lua_State *lua) {
	ESP.restart();
	return 0;
}




////////////////////////////////////////////////////////////////////////////////
// GET THE CURRENT NUMBER OF BYTES FREE IN THE HEAP (FREE RAM / MEMORY)
////////////////////////////////////////////////////////////////////////////////
static int esp_heap(lua_State *lua) {
	lua_pushinteger(lua, ESP.getFreeHeap());
	return 1;
}




////////////////////////////////////////////////////////////////////////////////
// PRINT TO THE SERIAL CONSOLE
////////////////////////////////////////////////////////////////////////////////
static int esp_print(lua_State *lua) {
	const char *text = luaL_checkstring(lua, 1);
	Serial.println(text ? text : "");
	return 0;
}




////////////////////////////////////////////////////////////////////////////////
// PUSH A RANDOM NUMBER ONTO THE STACK
////////////////////////////////////////////////////////////////////////////////
static int esp_rand(lua_State *lua) {
	lua_pushinteger(lua, ESP8266TrueRandom.rand());
	return 1;
}




////////////////////////////////////////////////////////////////////////////////
// PUSH A RANDOM NUMBER ONTO THE STACK
////////////////////////////////////////////////////////////////////////////////
static int esp_random(lua_State *lua) {
	switch (lua_gettop(lua)) {
		case 0:
			lua_pushinteger(lua, ESP8266TrueRandom.random());
		break;

		case 1:
			lua_pushinteger(lua, ESP8266TrueRandom.random(
				luaL_checkinteger(lua, 1)
			));
		break;

		default:
			lua_pushinteger(lua, ESP8266TrueRandom.random(
				luaL_checkinteger(lua, 1),
				luaL_checkinteger(lua, 2)
			));
	}
	return 1;
}




////////////////////////////////////////////////////////////////////////////////
// PUSH A RANDOM BIT ONTO THE STACK
////////////////////////////////////////////////////////////////////////////////
static int esp_bit(lua_State *lua) {
	lua_pushboolean(lua, ESP8266TrueRandom.randomBit());
	return 1;
}




////////////////////////////////////////////////////////////////////////////////
// PUSH A RANDOM BYTE ONTO THE STACK
////////////////////////////////////////////////////////////////////////////////
static int esp_byte(lua_State *lua) {
	lua_pushinteger(lua, ESP8266TrueRandom.randomByte());
	return 1;
}




////////////////////////////////////////////////////////////////////////////////
// GET THE INPUT VOLTAGE REFERENCE
////////////////////////////////////////////////////////////////////////////////
static int esp_vcc(lua_State *lua) {
	lua_pushinteger(lua, ESP.getVcc());
	return 1;
}




////////////////////////////////////////////////////////////////////////////////
// GET THE CHIP ID
////////////////////////////////////////////////////////////////////////////////
static int esp_id(lua_State *lua) {
	lua_pushinteger(lua, ESP.getChipId());
	return 1;
}




////////////////////////////////////////////////////////////////////////////////
// GET THE ESP SDK VERSION STRING
////////////////////////////////////////////////////////////////////////////////
static int esp_sdk(lua_State *lua) {
	lua_pushstring(lua, ESP.getSdkVersion());
	return 1;
}




////////////////////////////////////////////////////////////////////////////////
// GET THE CORE VERSION STRING
////////////////////////////////////////////////////////////////////////////////
static int esp_core(lua_State *lua) {
	String ver = ESP.getCoreVersion();
	lua_pushstring(lua, ver.c_str());
	return 1;
}




////////////////////////////////////////////////////////////////////////////////
// GET THE CURRENT CPU CLOCK CYCLE COUNT
////////////////////////////////////////////////////////////////////////////////
static int esp_cycle(lua_State *lua) {
	lua_pushinteger(lua, ESP.getCycleCount());
	return 1;
}




////////////////////////////////////////////////////////////////////////////////
// GET THE CURRENT CPU CLOCK CYCLE COUNT
////////////////////////////////////////////////////////////////////////////////
static int esp_mhz(lua_State *lua) {
	lua_pushinteger(lua, ESP.getCpuFreqMHz());
	return 1;
}




////////////////////////////////////////////////////////////////////////////////
// REGISTER THE ESP LUA OBJECT
////////////////////////////////////////////////////////////////////////////////
void lua_esp_init(lua_State *lua) {

	//ESP library (hardware functions)
	static const struct luaL_Reg esp_lib[] = {
		{"reset",	esp_reset},
		{"restart",	esp_restart},
		{"heap",	esp_heap},
		{"print",	esp_print},
		{"rand",	esp_rand},
		{"random",	esp_random},
		{"bit",		esp_bit},
		{"byte",	esp_byte},
		{"vcc",		esp_vcc},
		{"id",		esp_id},
		{"sdk",		esp_sdk},
		{"core",	esp_core},
		{"cycle",	esp_cycle},
		{"mhz",		esp_mhz},
		{NULL, NULL}
	};

	luaL_register(lua, "esp", esp_lib);
}