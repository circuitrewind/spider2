////////////////////////////////////////////////////////////////////////////////
//INCLUDE FILES
////////////////////////////////////////////////////////////////////////////////
#include <arduino.h>
#include <FS.h>
#include "lua.h"
#include "lua_esp.h"
#include "lua_led.h"
#include "lua_color.h"
#include "spider.h"




/*
//TODO:

spider.esp()
spider.run('file.lua')
spider.uptime()
spider.reboot()
spider.filename() // returns currently loaded lua script file name

pin.mode(id, read/write)
pin.read(id)
pin.write(id)

analog.read(id)
analog.write(id)

led.line
led.box

lua_yeild()
lua_resume()
*/



////////////////////////////////////////////////////////////////////////////////
// ??
////////////////////////////////////////////////////////////////////////////////
bool		can_render		= false;
lua_State	*lua			= nullptr;
String		spider_error;




////////////////////////////////////////////////////////////////////////////////
// INITIALIZE LUA
////////////////////////////////////////////////////////////////////////////////
int lua_setup() {
	if (likely(lua)) {
		Serial.println(F("Closing lua instance..."));
		lua_close(lua);
		lua = nullptr;
	}

	Serial.println(F("Creating lua instance..."));
	lua = luaL_newstate();

	Serial.println(F("Loading lua core libraries..."));
	luaL_openlibs(lua);

	Serial.println(F("Loading lua esp library..."));
	lua_esp_init(lua);

	Serial.println(F("Loading lua color library..."));
	lua_color_init(lua);

	Serial.println(F("Loading lua led library..."));
	lua_led_init(lua);

	Serial.println(F("Creating frame function..."));
	return spider_eval(LUASTR("function frame()\nend"));
}




////////////////////////////////////////////////////////////////////////////////
// LOAD A SPIFFS FILE INTO LUA
////////////////////////////////////////////////////////////////////////////////
int lua_file(const char *filename) {
	if (unlikely(!lua  ||  !filename  ||  !*filename)) return -1;

	if (!unlikely(SPIFFS.exists(filename))) {
		Serial.print(F("Failed to locate lua file: "));
		Serial.println(filename);
		return -2;
	}

	Serial.print(F("Attempting to load lua file: "));
	Serial.println(filename);

	File	file	= SPIFFS.open(filename, "r");

	if (unlikely(!file)) {
		Serial.print(F("Failed to load lua file: "));
		Serial.println(filename);
		return -3;
	}

	String	data	= file.readString();
	file.close();

	return spider_eval(data.c_str());
}




////////////////////////////////////////////////////////////////////////////////
// DO NOTHING
////////////////////////////////////////////////////////////////////////////////
static int spider_void(lua_State *lua) {
	return 0;
}




////////////////////////////////////////////////////////////////////////////////
// EXECUTE A LUA SCRIPT FROM A "C" STRING
////////////////////////////////////////////////////////////////////////////////
int spider_eval(const char *script) {
	if (unlikely(!lua  ||  !script  ||  !*script)) return -1;

	int ret;
	if (unlikely(ret = luaL_dostring(lua, script))) {
		spider_error = lua_tostring(lua, -1);
	}

	//LOCK THE FRAME RENDERER IF WE HAVE SCRIPT ISSUES
	can_render = !ret;

	return ret;
}




////////////////////////////////////////////////////////////////////////////////
// EXECUTE AN EXISTING LUA METHOD BY NAME
////////////////////////////////////////////////////////////////////////////////
int spider_method(const char *name) {
	if (!lua  ||  !name  ||  !*name) return -1;

	lua_getglobal(lua, name);

	int ret;
	if (unlikely(ret = lua_pcall(lua, 0, 0, 0))) {
		spider_error = lua_tostring(lua, -1);
	}

	//LOCK THE FRAME RENDERER IF WE HAVE SCRIPT ISSUES
	can_render = !ret;

	return ret;
}




////////////////////////////////////////////////////////////////////////////////
// LUA 5.2 COMPATIBILITY
////////////////////////////////////////////////////////////////////////////////
static void luaL_setfuncs(lua_State *L, const luaL_Reg *l, int nup) {
	luaL_checkstack(L, nup+1, LUASTR("too many upvalues"));
	for (; l->name != NULL; l++) {  /* fill the table with given functions */
		int i;
		lua_pushstring(L, l->name);
		for (i = 0; i < nup; i++)  /* copy upvalues to the top */
			lua_pushvalue(L, -(nup+1));
		lua_pushcclosure(L, l->func, nup);  /* closure with those upvalues */
		lua_settable(L, -(nup + 3));
	}
	lua_pop(L, nup);  /* remove upvalues */
}

#ifndef luaL_newlib
#define luaL_newlibtable(L,l) \
	lua_createtable(L, 0, sizeof(l) / sizeof((l)[0]) - 1)
#define luaL_newlib(L,l) \
	(luaL_newlibtable((L), (l)), luaL_setfuncs((L), (l), 0))
#endif




////////////////////////////////////////////////////////////////////////////////
// ??
////////////////////////////////////////////////////////////////////////////////
	/*
int foo_gc(lua_State* L);
int foo_index(lua_State* L);
int foo_newindex(lua_State* L);
int foo_dosomething(lua_State* L);
int foo_new(lua_State* L);
*/

/*
	//https://stackoverflow.com/questions/11100435/how-do-i-create-a-class-object-in-lua-c-api-5-2?utm_medium=organic&utm_source=google_rich_qa&utm_campaign=google_rich_qa
	// Create empty methods in our class that a child can replace
	static const struct luaL_Reg game_lib[] = {
		{"upleft",		spider_void},
		{"up",			spider_void},
		{"upright",		spider_void},
		{"left",		spider_void},
		{"center",		spider_void},
		{"right",		spider_void},
		{"downleft",	spider_void},
		{"down",		spider_void},
		{"downright",	spider_void},
		{"back",		spider_void},
		{"home",		spider_void},
		{NULL, NULL}
	};

	static const struct luaL_Reg _meta[] = {
		{"__gc",		foo_gc},
		{"__index",		foo_index},
		{"__newindex",	foo_newindex},
		{NULL, NULL}
	};

	int table, meta;

	// newclass = {}
	lua_createtable(lua, 0, 0);
	table = lua_gettop(lua);

	// metatable = {}
	luaL_newmetatable(lua, "game");
	meta = lua_gettop(lua);
	luaL_setfuncs(lua, _meta, 0);

	// metatable.__index = table
	luaL_newlib(lua, game_lib);
	lua_setfield(lua, meta, "__index");

	// metatable.__metatable = _meta
	luaL_newlib(lua, _meta);
	lua_setfield(lua, meta, "__metatable");

	// class.__metatable = metatable
	lua_setmetatable(lua, table);

	// _G["Foo"] = newclass
	lua_setglobal(lua, "game");
}
*/


/*

struct foo {
	int x;
};

int foo_gc(lua_State* L) {
	Serial.println("## __gc\n");
	return 0;
}

int foo_newindex(lua_State* L) {
	Serial.println("## __newindex\n");
	return 0;
}

int foo_index(lua_State* L) {
	Serial.println("## __index\n");
	return 0;
}

int foo_dosomething(lua_State* L) {
	Serial.println("## dosomething\n");
	return 0;
}

int foo_new(lua_State* L) {
	Serial.println("## new\n");

	lua_newuserdata(L,sizeof(foo));
	luaL_getmetatable(L, "foo");
	lua_setmetatable(L, -2);

	return 1;
}
*/
