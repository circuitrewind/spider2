#ifndef __LUA_H__
#define __LUA_H__



#include "src/lua/lua.hpp"
#include "src/led/optimize.h"
#include "src/color/color.h"



extern bool			can_render;
extern lua_State	*lua;
extern String		spider_error;


int spider_eval(const char *script);
int spider_method(const char *name);




LUALIB_API INLINE color_t luaL_checkcolor(lua_State *lua, int narg) {
	switch (lua_type(lua, narg)) {
		case LUA_TSTRING:
			return color_t( luaL_checkstring(lua, narg) );

		case LUA_TNUMBER:
			return color_t( luaL_checkinteger(lua, narg) );
	}

	return color_t::black();
}



#endif //__LUA_H__
