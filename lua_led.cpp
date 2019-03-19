////////////////////////////////////////////////////////////////////////////////
//INCLUDE FILES
////////////////////////////////////////////////////////////////////////////////
#include <arduino.h>
#include "src/led/led_grid.h"
#include "spider.h"
#include "lua.h"
#include "lua_esp.h"




////////////////////////////////////////////////////////////////////////////////
// ??
////////////////////////////////////////////////////////////////////////////////
static int led_read(lua_State *lua) {
	int id				= luaL_checkinteger(lua, 1);
	int pixel			= luaL_checkinteger(lua, 2);
	led_array *array	= ledset.array(id);

	if (likely(array)) {
		lua_pushinteger(lua, (uint32_t) array->read(pixel));
	} else {
		lua_pushboolean(lua, false);
	}

	return 1;
}




////////////////////////////////////////////////////////////////////////////////
// ??
////////////////////////////////////////////////////////////////////////////////
static int led_write(lua_State *lua) {
	int id				= luaL_checkinteger(lua, 1);
	int pixel			= luaL_checkinteger(lua, 2);
	color_t color		= luaL_checkcolor(lua, 3);
	led_array *array	= ledset.array(id);

	if (likely(array)) array->write(pixel, color);

	return 0;
}




////////////////////////////////////////////////////////////////////////////////
// ??
////////////////////////////////////////////////////////////////////////////////
static int led_add(lua_State *lua) {
	int id				= luaL_checkinteger(lua, 1);
	led_array *array	= ledset.array(id);

	if (likely(array)) {
		array->add( luaL_checkcolor(lua, 2) );
	}

	return 0;
}




////////////////////////////////////////////////////////////////////////////////
// ??
////////////////////////////////////////////////////////////////////////////////
static int led_sub(lua_State *lua) {
	int id				= luaL_checkinteger(lua, 1);
	led_array *array	= ledset.array(id);

	if (likely(array)) {
		array->sub( luaL_checkcolor(lua, 2) );
	}

	return 0;
}




////////////////////////////////////////////////////////////////////////////////
// ??
////////////////////////////////////////////////////////////////////////////////
static int led_screen(lua_State *lua) {
	int id				= luaL_checkinteger(lua, 1);
	led_array *array	= ledset.array(id);

	if (likely(array)) {
		array->screen( luaL_checkcolor(lua, 2) );
	}

	return 0;
}




////////////////////////////////////////////////////////////////////////////////
// ??
////////////////////////////////////////////////////////////////////////////////
static int led_multiply(lua_State *lua) {
	int id				= luaL_checkinteger(lua, 1);
	led_array *array	= ledset.array(id);

	if (likely(array)) {
		array->multiply( luaL_checkcolor(lua, 2) );
	}

	return 0;
}




////////////////////////////////////////////////////////////////////////////////
// ??
////////////////////////////////////////////////////////////////////////////////
static int led_draw(lua_State *lua) {
	int id				= luaL_checkinteger(lua, 1);
	int x				= luaL_checkinteger(lua, 2);
	int y				= luaL_checkinteger(lua, 3);
	led_grid *grid		= ledset.grid(id);

	if (likely(grid)) {
		if (lua_gettop(lua) > 3) {
			color_t color = luaL_checkcolor(lua, 4);
			grid->draw(x, y, color);
		} else {
			grid->draw(x, y);
		}
	}

	return 0;
}




////////////////////////////////////////////////////////////////////////////////
// ??
////////////////////////////////////////////////////////////////////////////////
static int led_text(lua_State *lua) {
	int id				= luaL_checkinteger(lua, 1);
	int x				= luaL_checkinteger(lua, 2);
	int y				= luaL_checkinteger(lua, 3);
	color_t color		= luaL_checkcolor(lua, 4);
	const char *text	= luaL_checkstring( lua, 5);
	led_grid *grid		= ledset.grid(id);

	if (likely(grid)) grid->string(text, x, y, color);

	return 0;
}




////////////////////////////////////////////////////////////////////////////////
// ??
////////////////////////////////////////////////////////////////////////////////
static int led_clear(lua_State *lua) {
	if (lua_gettop(lua) > 0) {
		led_array *array	= ledset.array(luaL_checkinteger(lua, 1));
		if (likely(array)) array->clear();

	} else {
		ledset.clear();
	}

	return 0;
}




////////////////////////////////////////////////////////////////////////////////
// ??
////////////////////////////////////////////////////////////////////////////////
static int led_fill(lua_State *lua) {
	if (lua_gettop(lua) > 1) {
		led_array *array	= ledset.array(luaL_checkinteger(lua, 1));
		color_t color		= color_t( luaL_checkcolor(lua, 2) );
		if (likely(array)) array->fill(color);

	} else if (lua_gettop(lua) > 0) {
		color_t color		= color_t( luaL_checkcolor(lua, 1) );
		ledset.fill(color);

	} else {
		ledset.clear();
	}

	return 0;
}




////////////////////////////////////////////////////////////////////////////////
// ??
////////////////////////////////////////////////////////////////////////////////
static int led_fade(lua_State *lua) {
	if (lua_gettop(lua) > 1) {
		led_array *array	= ledset.array(luaL_checkinteger(lua, 1));
		if (likely(array)) array->fade(luaL_checkinteger(lua, 2));

	} else if (lua_gettop(lua) > 0) {
		led_array *array	= ledset.array(luaL_checkinteger(lua, 1));
		if (likely(array)) array->fade();

	} else {
		ledset.fade();
	}

	return 0;
}




////////////////////////////////////////////////////////////////////////////////
// ??
////////////////////////////////////////////////////////////////////////////////
static int led_width(lua_State *lua) {
	int id				= luaL_checkinteger(lua, 1);
	led_grid *grid		= ledset.grid(id);

	if (likely(grid)) {
		lua_pushinteger(lua, grid->width());
	} else {
		lua_pushnil(lua);
	}

	return 1;
}




////////////////////////////////////////////////////////////////////////////////
// ??
////////////////////////////////////////////////////////////////////////////////
static int led_height(lua_State *lua) {
	int id				= luaL_checkinteger(lua, 1);
	led_grid *grid		= ledset.grid(id);

	if (likely(grid)) {
		lua_pushinteger(lua, grid->height());
	} else {
		lua_pushnil(lua);
	}

	return 1;
}




////////////////////////////////////////////////////////////////////////////////
// ??
////////////////////////////////////////////////////////////////////////////////
static int led_length(lua_State *lua) {
	int id				= luaL_checkinteger(lua, 1);
	led_array *array	= ledset.array(id);

	if (likely(array)) {
		lua_pushinteger(lua, array->total());
	} else {
		lua_pushnil(lua);
	}

	return 1;
}



////////////////////////////////////////////////////////////////////////////////
// INIT LUA LED LIBRARY
////////////////////////////////////////////////////////////////////////////////
void lua_led_init(lua_State *lua) {

	//LED library
	static const struct luaL_Reg led_lib[] = {
		{"read",	led_read},
		{"write",	led_write},
		{"add",		led_add},
		{"sub",		led_sub},
		{"screen",	led_screen},
		{"multiply",led_multiply},
		{"clear",	led_clear},
		{"fill",	led_fill},
		{"text",	led_text},
		{"draw",	led_draw},
		{"fade",	led_fade},
		{"width",	led_width},
		{"height",	led_height},
		{"length",	led_length},
		{NULL, NULL}
	};

	luaL_register(lua, "led", led_lib);
}
