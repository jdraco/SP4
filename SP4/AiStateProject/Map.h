#pragma once


#include <vector>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

#include "Define.h"
#include "Sprite.h"
//Waypoint
#include "WayPoint.h"
#define TILESET_X 30.05f
#define TILESET_Y 15.99f
#define LITTLEROOT_X 7.98f
#define LITTLEROOT_Y 14.01f
#define INDOOR_X 39.02f
#define INDOOR_Y 18.98f

using namespace std;

class CMap
{
public:

	//The Tile List
	enum TileList
	{
		TILE_NULL, //Ground
		WALL,
		WALL_CROSS = 3,
		WALL_BOTTOM1,
		WALL_CROSS_BOTTOM,
		WALL_BOTTOM2,
		ENTRANCE1, ENTRANCE2,
		RIGHT_CORNER1, RIGHT_CORNER2, RIGHT_CORNER3,
		RIGHT_WALL,
		WALL_BOTTOM3, LEFT_WALL_SIDE,
		WALL_PIC1, WALL_PIC2, WALL_PIC3, WALL_PIC4,
		WALL_PIC5, WALL_PIC6, WALL_PIC7, WALL_PIC8,
		WALL_PIC9, WALL_PIC10, WALL_PIC11, 
		LEFT_WALL, WALL_TOP,
		LEFT_CORNER1, LEFT_CORNER2, LEFT_CORNER3,
		SOFA_1, SOFA_2, SOFA_3, SOFA_4,
		JAIL_BARS_FRONT, JAIL_WALL_LEFT, JAIL_WALL_RIGHT, JAIL_WINDOW_FRONT, JAIL_WINDOW_LEFT, JAIL_WINDOW_RIGHT,
		HOLE,
		CHEST_CLOSED, CHEST_OPENED, CHEST_LOCKED,
		GRASS,
		DOOR_LEFT,DOOR_RIGHT,
		TILE_TOTAL
	};

	//The Map List
	enum MapList
	{
		MAP_NULL,
		INDOOR,
		LITTLEROOT,
		AI_MAP,
		PLAYER_HOUSE,
		MAP_TOTAL
	};

	enum OtherList
	{
		INVERSE_START_POINT = -200,
		SPAWN_PLAYER,
		SPAWN_MONSTER,
		INVERSE_END_POINT,

		PATH_START = -100,
		PATH_ONE,
		PATH_TWO,
		PATH_END,
	};

	//Starting Map
	const short STARTING_MAP;

	//Map
	MapList theMap;

	//Returns Map Name
	string MapName(short mName);

	//Returns Map List
	MapList MapL(short mName);

private:
	static CMap *instance;

	//Map Info
	int theScreen_Height;
	int theScreen_Width;
	int theMap_Height;
	int theMap_Width;
	int theNumOfTiles_ScreenHeight;
	int theNumOfTiles_ScreenWidth;
	int theNumOfTiles_MapHeight;
	int theNumOfTiles_MapWidth;
	int theTileSize;
	
	//Sprites
	CSprite *TileMap;
	TextureImage TileSet[10];
	CSprite *TChange;
	TextureImage TileChange[1];
	CSprite *Littleroot;
	TextureImage LRoot[1];
	CSprite *IndoorMap;
	TextureImage IndoorTex[1];

	//Border Texture
	TextureImage border[1];

	bool LoadFile(const string mapName);

public:
	static CMap* getInstance();
	CMap();
	~CMap();

	//Flag to check if Map has initialised
	bool mapInit;

	void Init(int theScreen_Height, int theScreen_Width, 
		      const int theMap_Height, const int theMap_Width, 
		      const int theTileSize);
	bool LoadMap(const string mapName);

	int getNumOfTiles_ScreenHeight();	// Get the number of tiles for height of the screen
	int getNumOfTiles_ScreenWidth();	// Get the number of tiles for width of the screen
	int getNumOfTiles_MapHeight();		// Get the number of tiles for height of the map
	int getNumOfTiles_MapWidth();		// Get the number of tiles for width of the map

	vector<vector<int> > theScreenMap;

	//Offsets
	int mapOffset_x, mapOffset_y;
	int tileOffset_x, tileOffset_y;
	int mapFineOffset_x, mapFineOffset_y;

	//Map Border
	CMap *theBorder;

	//Map Render Functions
	void RenderMiniMap(CMap* map);
	void RenderTileMap(CMap* map);
	void RenderMapBorder();

	//Load Textures
	bool LoadTextures();

	//Update Function
	void Update();
};
