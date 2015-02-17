#pragma once


extern "C" {
#include "lua/lua.h"
#include "lua/lualib.h"
#include "lua/lauxlib.h"
}

class LuaReading
{
protected:
	static LuaReading* s_pInstance;

public:
	LuaReading();

	~LuaReading();

	static LuaReading* getInstance()
	{
		if(s_pInstance == NULL){
			s_pInstance = new LuaReading;
		}
		return s_pInstance;
	};

	int	sight_range		;//		= GetIntFromLua("game_init.lua" , "PLAYER_SIGHT_RANGE");
	int  reach_range		;//=		GetIntFromLua("game_init.lua" , "PLAYER_REACH_RANGE");

	int sight_radius		;//=	GetIntFromLua("game_init.lua" , "PLAYER_SIGHT_RADIUS")	,
	int reach_radius		;//=	GetIntFromLua("game_init.lua" , "PLAYER_REACH_RADIUS")	,

	int sp_size_x		;//		GetIntFromLua("game_init.lua" , "SP_SIZE_X")	,
	int sp_size_y	;//=		GetIntFromLua("game_init.lua" , "SP_SIZE_Y")	,
	int sp_num_of_grid_x	;//=	GetIntFromLua("game_init.lua" , "SP_NUM_OF_GRID_X")	,
	int sp_num_of_grid_y	;	//GetIntFromLua("game_init.lua" , "SP_NUM_OF_GRID_Y")	,

	int player_rotate_speed;	//=	GetIntFromLua("game_init.lua" , "PLAYER_ROTATE_SPEED"),		
	int gravity			;//=		GetIntFromLua("game_init.lua" , "GRAVITY")		,

	int luaGetIndex(float objpos, float size, float translate );
	int luaPlusPlus(int x);
};

