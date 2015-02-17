#include "LuaReading.h"
#include <iostream>
LuaReading* LuaReading::s_pInstance = NULL;

int GetIntFromLua(const char* LuaFile , const char* Variable  )
{
	static int s=-1;
	lua_State *L = lua_open();
	 // Do stuff with lua code.
	//Read a value from the lua text file
	luaL_openlibs(L);
	if (luaL_loadfile(L, LuaFile) || lua_pcall(L, 0, 0, 0))
	{
	 printf("error: %s", lua_tostring(L, s));
	 system("pause");
	 return -1;
	}
	lua_getglobal(L, Variable);

	int temp = (int)lua_tonumber(L, s);

	lua_close(L);

	return temp;

	system("pause");
	return 0;
}

std::string GetStringFromLua(const char* LuaFile , const char* Variable  )
{
	static int s=-1;
	lua_State *L = lua_open();
	 // Do stuff with lua code.
	//Read a value from the lua text file
	luaL_openlibs(L);
	if (luaL_loadfile(L, LuaFile) || lua_pcall(L, 0, 0, 0))
	{
	 printf("error: %s", lua_tostring(L, s));
	 system("pause");
	 return NULL;
	}
	lua_getglobal(L, Variable);

	std::string temp = (std::string)lua_tostring(L, s);

	lua_close(L);

	return temp;

	system("pause");
	return NULL;
}


LuaReading::LuaReading()
{
		sight_range = GetIntFromLua("game_init.lua" , "PLAYER_SIGHT_RANGE");
		reach_range = GetIntFromLua("game_init.lua" , "PLAYER_REACH_RANGE");

		sight_radius = GetIntFromLua("game_init.lua" , "PLAYER_SIGHT_RADIUS");
		reach_radius = GetIntFromLua("game_init.lua" , "PLAYER_REACH_RADIUS");

		sp_size_x = GetIntFromLua("game_init.lua" , "SP_SIZE_X");
		sp_size_y = GetIntFromLua("game_init.lua" , "SP_SIZE_Y");
		sp_num_of_grid_x = GetIntFromLua("game_init.lua" , "SP_NUM_OF_GRID_X");
		sp_num_of_grid_y = GetIntFromLua("game_init.lua" , "SP_NUM_OF_GRID_Y");

		player_rotate_speed = GetIntFromLua("game_init.lua" , "PLAYER_ROTATE_SPEED");
		gravity = GetIntFromLua("game_init.lua" , "GRAVITY");
}


LuaReading::~LuaReading(void)
{
}

int LuaReading::luaGetIndex(float objpos, float size, float translate )
{
	lua_State *L = lua_open();
	int index;
	 // Do stuff with lua code.
	//Read a value from the lua text file
	luaL_openlibs(L);
	if (luaL_loadfile(L, "game_init.lua") || lua_pcall(L, 0, 0, 0))
	{
		system("pause");
		return NULL;
	}
	
	lua_getglobal(L, "getIndex"); /* the function name */
	lua_pushnumber(L, objpos); /* the first argument */
	lua_pushnumber(L, size); /* the second argument */
	lua_pushnumber(L, translate); /* the second argument */
	/* call the function with 2 arguments, return 1 result */
	lua_call(L, 3, 1);
	/* get the result */
	index = (int)lua_tointeger(L, -1);
	lua_pop(L, 1);
	return index;
	
}

int LuaReading::luaPlusPlus(int x)
{
	lua_State *L = lua_open();
	int index;
	 // Do stuff with lua code.
	//Read a value from the lua text file
	luaL_openlibs(L);
	if (luaL_loadfile(L, "game_init.lua") || lua_pcall(L, 0, 0, 0))
	{
		system("pause");
		return NULL;
	}
	
	lua_getglobal(L, "plusplus"); /* the function name */
	lua_pushnumber(L, x); /* the first argument */

	/* call the function with 2 arguments, return 1 result */
	lua_call(L, 1, 1);
	/* get the result */
	index = (int)lua_tointeger(L, -1);
	lua_pop(L, 1);
	return index;
	
}



