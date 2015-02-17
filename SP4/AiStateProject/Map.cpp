#include "Map.h"
#include "Player.h"

CMap* CMap::instance = NULL;

CMap::CMap()
	: theScreen_Height(NULL)
	, theScreen_Width(theScreen_Height)
	, theMap_Height(theScreen_Width)
	, theMap_Width(theMap_Height)
	, theNumOfTiles_ScreenHeight(theMap_Width)
	, theNumOfTiles_ScreenWidth(theNumOfTiles_ScreenHeight)
	, theNumOfTiles_MapHeight(theNumOfTiles_ScreenWidth)
	, theNumOfTiles_MapWidth(theNumOfTiles_MapHeight)
	, theTileSize(theNumOfTiles_MapWidth)
	, STARTING_MAP(INDOOR), theMap(MapL(STARTING_MAP))
{
	theScreenMap.clear();
}

CMap::~CMap()
{
	theScreenMap.clear();

	//Delete Border
	if (theBorder != NULL)
	{
		delete theBorder;
		theBorder = NULL;
	}
}

void CMap::Init(const int theScreen_Height, const int theScreen_Width, 
				const int theMap_Height, const int theMap_Width, 
				const int theTileSize)
{
	this->theScreen_Height = theScreen_Height;
	this->theScreen_Width = theScreen_Width;
	this->theMap_Height = theMap_Height;
	this->theMap_Width = theMap_Width;
	this->theTileSize = theTileSize;

	theNumOfTiles_ScreenHeight = (int) (theScreen_Height / theTileSize);
	theNumOfTiles_ScreenWidth = (int) (theScreen_Width / theTileSize);
	theNumOfTiles_MapHeight = (int) (theMap_Height / theTileSize);
	theNumOfTiles_MapWidth = (int) (theMap_Width / theTileSize);

	mapInit = false;

	theScreenMap.resize(theNumOfTiles_MapHeight);
	for (short i = 0; i < theNumOfTiles_MapHeight; ++i)
		theScreenMap[i].resize(theNumOfTiles_MapWidth);
	
	//Init Offset Values
	tileOffset_x = tileOffset_y = mapFineOffset_x = mapFineOffset_y = NULL;

	//Init Map Offset For Specific Maps
	switch (theMap)
	{
	case INDOOR:
		mapOffset_x = 40;
		mapOffset_y = 1800;
		break;
	case LITTLEROOT:
		mapOffset_x = 0;
		mapOffset_y = 1636;
		break;
	case AI_MAP:
	default:
		mapOffset_x = mapOffset_y = 0;
		break;
	}

	//Init TileSet
	TileMap = new CSprite;
	TileMap->ImageInit(TILESET_X, TILESET_Y);
	Littleroot = new CSprite;
	Littleroot->ImageInit(LITTLEROOT_X, LITTLEROOT_Y);
	IndoorMap = new CSprite;
	IndoorMap->ImageInit(INDOOR_X, INDOOR_Y);

	//Init TileChange
	TChange = new CSprite;
	TChange->ImageInit(1,1);
}

//Singleton Structure
CMap* CMap::getInstance()
{
	//Allows only one instance of CMap
	if (instance == NULL)
		instance = new CMap();
	return instance;
}

void CMap::Update()
{
	//Update Map Offset
	tileOffset_x = (int)(mapOffset_x / TILE_SIZE);
	tileOffset_y = (int)(mapOffset_y / TILE_SIZE);

	if (tileOffset_x+theNumOfTiles_ScreenWidth > theNumOfTiles_MapWidth)
		tileOffset_x = theNumOfTiles_MapWidth - theNumOfTiles_ScreenWidth;

	if (tileOffset_y+theNumOfTiles_ScreenHeight > theNumOfTiles_MapHeight)
		tileOffset_y = theNumOfTiles_MapHeight - theNumOfTiles_ScreenHeight;
}

bool CMap::LoadTextures()
{
	//Load All Textures, if loading failed, return False
	
	/*
	if (!LoadTGA(&TileSet[0], "images/tile_blank.tga"))
		return false;
	if (!LoadTGA(&TileSet[1], "images/tileset_world.tga"))
		return false;
	if (!LoadTGA(&LRoot[0], "images/tileset_littleroot.tga"))
		return false;
	if (!LoadTGA(&TileChange[0], "images/grass.tga"))
		return false;
		*/
	if (!LoadTGA(&border[0], "Texture/Tiles/border.tga"))
		return false;
	if (!LoadTGA(&IndoorTex[0], "Texture/Tiles/indoorTileset.tga"))
		return false;

	//All Textures Successfully Loaded
	return true;
}

//Returns Map Name
string CMap::MapName(short mName)
{
	switch (mName)
	{
	case PLAYER_HOUSE:
		return "Player's House";
		break;
	case LITTLEROOT:
		return "Little Root Town";
		break;
	case INDOOR:
		return "Gallery Room";
		break;
	case AI_MAP:
	default:
		return "Undefined Map";
		break;
	}
}

//Returns Map List
CMap::MapList CMap::MapL(short mName)
{
	switch (mName)
	{
	case PLAYER_HOUSE:
		return PLAYER_HOUSE;
		break;
	case LITTLEROOT:
		return LITTLEROOT;
		break;
	case INDOOR:
		return INDOOR;
		break;
	case AI_MAP:
	default:
		return MAP_NULL;
		break;
	}
}

 /****************************************************************************************************
   Draw the tile map
 ****************************************************************************************************/
void CMap::RenderTileMap(CMap* map) {

	//Initialise mapFineOffset
	mapFineOffset_x = mapOffset_x % TILE_SIZE;
	mapFineOffset_y = mapOffset_y % TILE_SIZE;

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);

	//Loop through column
	for (short i = 0; i < map->getNumOfTiles_ScreenHeight(); ++i)
	{
		//Loop through row
		for (short k = 0; k < map->getNumOfTiles_ScreenWidth()+1; ++k)
		{
			//if we have reached the right side of the Map, then do not display the extra column of tiles.
			if ((tileOffset_x+k) >= map->getNumOfTiles_MapWidth())
				break;

			//if we have reached the top side of the Map, then do not display the extra row of tiles.
			if ((tileOffset_y+i) >= map->getNumOfTiles_MapHeight())
				break;

			//Render Tiles
			switch (map->theScreenMap[tileOffset_y+i][tileOffset_x+k])
			{
			case WALL:
				IndoorMap->changeSubImage(19); 
				IndoorMap->changeVariation(2);

				//cout << k*TILE_SIZE-mapFineOffset_x+LEFT_BORDER+TILE_SIZE*0.5 << endl;
				//Render Tile
				glPushMatrix();
					glTranslatef((float)(k*TILE_SIZE-mapFineOffset_x+LEFT_BORDER+TILE_SIZE*0.5), (float)(i*TILE_SIZE-mapFineOffset_y+BOTTOM_BORDER+TILE_SIZE*0.5), 0);
					IndoorMap->render(IndoorTex[0]);
				glPopMatrix();
				break;
			case WALL_CROSS:
				IndoorMap->changeSubImage(19); 
				IndoorMap->changeVariation(8);

				//Render Tile
				glPushMatrix();
					glTranslatef((float)(k*TILE_SIZE-mapFineOffset_x+LEFT_BORDER+TILE_SIZE*0.5), (float)(i*TILE_SIZE-mapFineOffset_y+BOTTOM_BORDER+TILE_SIZE*0.5), 0);
					IndoorMap->render(IndoorTex[0]);
				glPopMatrix();
				break;
			case WALL_CROSS_BOTTOM:
				IndoorMap->changeSubImage(19); 
				IndoorMap->changeVariation(7);

				//Render Tile
				glPushMatrix();
					glTranslatef((float)(k*TILE_SIZE-mapFineOffset_x+LEFT_BORDER+TILE_SIZE*0.5), (float)(i*TILE_SIZE-mapFineOffset_y+BOTTOM_BORDER+TILE_SIZE*0.5), 0);
					IndoorMap->render(IndoorTex[0]);
				glPopMatrix();
				break;
			case WALL_BOTTOM1:
				IndoorMap->changeSubImage(20); 
				IndoorMap->changeVariation(8);

				//Render Tile
				glPushMatrix();
					glTranslatef((float)(k*TILE_SIZE-mapFineOffset_x+LEFT_BORDER+TILE_SIZE*0.5), (float)(i*TILE_SIZE-mapFineOffset_y+BOTTOM_BORDER+TILE_SIZE*0.5), 0);
					IndoorMap->render(IndoorTex[0]);
				glPopMatrix();
				break;
			case WALL_BOTTOM2:
				IndoorMap->changeSubImage(26); 
				IndoorMap->changeVariation(7);

				//Render Tile
				glPushMatrix();
					glTranslatef((float)(k*TILE_SIZE-mapFineOffset_x+LEFT_BORDER+TILE_SIZE*0.5), (float)(i*TILE_SIZE-mapFineOffset_y+BOTTOM_BORDER+TILE_SIZE*0.5), 0);
					IndoorMap->render(IndoorTex[0]);
				glPopMatrix();
				break;
			case WALL_BOTTOM3:
				IndoorMap->changeSubImage(20); 
				IndoorMap->changeVariation(16);

				//Render Tile
				glPushMatrix();
					glTranslatef((float)(k*TILE_SIZE-mapFineOffset_x+LEFT_BORDER+TILE_SIZE*0.5), (float)(i*TILE_SIZE-mapFineOffset_y+BOTTOM_BORDER+TILE_SIZE*0.5), 0);
					IndoorMap->render(IndoorTex[0]);
				glPopMatrix();
				break;
			case LEFT_WALL_SIDE:
				IndoorMap->changeSubImage(19); 
				IndoorMap->changeVariation(16);

				//Render Tile
				glPushMatrix();
					glTranslatef((float)(k*TILE_SIZE-mapFineOffset_x+LEFT_BORDER+TILE_SIZE*0.5), (float)(i*TILE_SIZE-mapFineOffset_y+BOTTOM_BORDER+TILE_SIZE*0.5), 0);
					IndoorMap->render(IndoorTex[0]);
				glPopMatrix();
				break;
			case ENTRANCE1:
				IndoorMap->changeSubImage(27); 
				IndoorMap->changeVariation(0);

				//Render Tile
				glPushMatrix();
					glTranslatef((float)(k*TILE_SIZE-mapFineOffset_x+LEFT_BORDER+TILE_SIZE*0.5), (float)(i*TILE_SIZE-mapFineOffset_y+BOTTOM_BORDER+TILE_SIZE*0.5), 0);
					IndoorMap->render(IndoorTex[0]);
				glPopMatrix();
				break;
			case ENTRANCE2:
				IndoorMap->changeSubImage(28); 
				IndoorMap->changeVariation(0);

				//Render Tile
				glPushMatrix();
					glTranslatef((float)(k*TILE_SIZE-mapFineOffset_x+LEFT_BORDER+TILE_SIZE*0.5), (float)(i*TILE_SIZE-mapFineOffset_y+BOTTOM_BORDER+TILE_SIZE*0.5), 0);
					IndoorMap->render(IndoorTex[0]);
				glPopMatrix();
				break;
			case RIGHT_CORNER1:
				IndoorMap->changeSubImage(26); 
				IndoorMap->changeVariation(18);

				//Render Tile
				glPushMatrix();
					glTranslatef((float)(k*TILE_SIZE-mapFineOffset_x+LEFT_BORDER+TILE_SIZE*0.5), (float)(i*TILE_SIZE-mapFineOffset_y+BOTTOM_BORDER+TILE_SIZE*0.5), 0);
					IndoorMap->render(IndoorTex[0]);
				glPopMatrix();
				break;
			case RIGHT_CORNER2:
				IndoorMap->changeSubImage(26); 
				IndoorMap->changeVariation(17);

				//Render Tile
				glPushMatrix();
					glTranslatef((float)(k*TILE_SIZE-mapFineOffset_x+LEFT_BORDER+TILE_SIZE*0.5), (float)(i*TILE_SIZE-mapFineOffset_y+BOTTOM_BORDER+TILE_SIZE*0.5), 0);
					IndoorMap->render(IndoorTex[0]);
				glPopMatrix();
				break;
			case RIGHT_CORNER3:
				IndoorMap->changeSubImage(26); 
				IndoorMap->changeVariation(16);

				//Render Tile
				glPushMatrix();
					glTranslatef((float)(k*TILE_SIZE-mapFineOffset_x+LEFT_BORDER+TILE_SIZE*0.5), (float)(i*TILE_SIZE-mapFineOffset_y+BOTTOM_BORDER+TILE_SIZE*0.5), 0);
					IndoorMap->render(IndoorTex[0]);
				glPopMatrix();
				break;
			case RIGHT_WALL:
				IndoorMap->changeSubImage(26); 
				IndoorMap->changeVariation(15);

				//Render Tile
				glPushMatrix();
					glTranslatef((float)(k*TILE_SIZE-mapFineOffset_x+LEFT_BORDER+TILE_SIZE*0.5), (float)(i*TILE_SIZE-mapFineOffset_y+BOTTOM_BORDER+TILE_SIZE*0.5), 0);
					IndoorMap->render(IndoorTex[0]);
				glPopMatrix();
				break;
			case WALL_PIC1:
				IndoorMap->changeSubImage(26); 
				IndoorMap->changeVariation(13);

				//Render Tile
				glPushMatrix();
					glTranslatef((float)(k*TILE_SIZE-mapFineOffset_x+LEFT_BORDER+TILE_SIZE*0.5), (float)(i*TILE_SIZE-mapFineOffset_y+BOTTOM_BORDER+TILE_SIZE*0.5), 0);
					IndoorMap->render(IndoorTex[0]);
				glPopMatrix();
				break;
			case WALL_PIC2:
				IndoorMap->changeSubImage(27); 
				IndoorMap->changeVariation(13);

				//Render Tile
				glPushMatrix();
					glTranslatef((float)(k*TILE_SIZE-mapFineOffset_x+LEFT_BORDER+TILE_SIZE*0.5), (float)(i*TILE_SIZE-mapFineOffset_y+BOTTOM_BORDER+TILE_SIZE*0.5), 0);
					IndoorMap->render(IndoorTex[0]);
				glPopMatrix();
				break;
			case WALL_PIC3:
				IndoorMap->changeSubImage(28); 
				IndoorMap->changeVariation(13);

				//Render Tile
				glPushMatrix();
					glTranslatef((float)(k*TILE_SIZE-mapFineOffset_x+LEFT_BORDER+TILE_SIZE*0.5), (float)(i*TILE_SIZE-mapFineOffset_y+BOTTOM_BORDER+TILE_SIZE*0.5), 0);
					IndoorMap->render(IndoorTex[0]);
				glPopMatrix();
				break;
			case WALL_PIC4:
				IndoorMap->changeSubImage(29); 
				IndoorMap->changeVariation(13);

				//Render Tile
				glPushMatrix();
					glTranslatef((float)(k*TILE_SIZE-mapFineOffset_x+LEFT_BORDER+TILE_SIZE*0.5), (float)(i*TILE_SIZE-mapFineOffset_y+BOTTOM_BORDER+TILE_SIZE*0.5), 0);
					IndoorMap->render(IndoorTex[0]);
				glPopMatrix();
				break;
			case WALL_PIC5:
				IndoorMap->changeSubImage(26); 
				IndoorMap->changeVariation(12);

				//Render Tile
				glPushMatrix();
					glTranslatef((float)(k*TILE_SIZE-mapFineOffset_x+LEFT_BORDER+TILE_SIZE*0.5), (float)(i*TILE_SIZE-mapFineOffset_y+BOTTOM_BORDER+TILE_SIZE*0.5), 0);
					IndoorMap->render(IndoorTex[0]);
				glPopMatrix();
				break;
			case WALL_PIC6:
				IndoorMap->changeSubImage(27); 
				IndoorMap->changeVariation(12);

				//Render Tile
				glPushMatrix();
					glTranslatef((float)(k*TILE_SIZE-mapFineOffset_x+LEFT_BORDER+TILE_SIZE*0.5), (float)(i*TILE_SIZE-mapFineOffset_y+BOTTOM_BORDER+TILE_SIZE*0.5), 0);
					IndoorMap->render(IndoorTex[0]);
				glPopMatrix();
				break;
			case WALL_PIC7:
				IndoorMap->changeSubImage(28); 
				IndoorMap->changeVariation(12);

				//Render Tile
				glPushMatrix();
					glTranslatef((float)(k*TILE_SIZE-mapFineOffset_x+LEFT_BORDER+TILE_SIZE*0.5), (float)(i*TILE_SIZE-mapFineOffset_y+BOTTOM_BORDER+TILE_SIZE*0.5), 0);
					IndoorMap->render(IndoorTex[0]);
				glPopMatrix();
				break;
			case WALL_PIC8:
				IndoorMap->changeSubImage(29); 
				IndoorMap->changeVariation(12);

				//Render Tile
				glPushMatrix();
					glTranslatef((float)(k*TILE_SIZE-mapFineOffset_x+LEFT_BORDER+TILE_SIZE*0.5), (float)(i*TILE_SIZE-mapFineOffset_y+BOTTOM_BORDER+TILE_SIZE*0.5), 0);
					IndoorMap->render(IndoorTex[0]);
				glPopMatrix();
				break;
			case WALL_PIC9:
				IndoorMap->changeSubImage(26); 
				IndoorMap->changeVariation(11);

				//Render Tile
				glPushMatrix();
					glTranslatef((float)(k*TILE_SIZE-mapFineOffset_x+LEFT_BORDER+TILE_SIZE*0.5), (float)(i*TILE_SIZE-mapFineOffset_y+BOTTOM_BORDER+TILE_SIZE*0.5), 0);
					IndoorMap->render(IndoorTex[0]);
				glPopMatrix();
				break;
			case WALL_PIC10:
				IndoorMap->changeSubImage(27); 
				IndoorMap->changeVariation(11);

				//Render Tile
				glPushMatrix();
					glTranslatef((float)(k*TILE_SIZE-mapFineOffset_x+LEFT_BORDER+TILE_SIZE*0.5), (float)(i*TILE_SIZE-mapFineOffset_y+BOTTOM_BORDER+TILE_SIZE*0.5), 0);
					IndoorMap->render(IndoorTex[0]);
				glPopMatrix();
				break;
			case WALL_PIC11:
				IndoorMap->changeSubImage(29); 
				IndoorMap->changeVariation(11);

				//Render Tile
				glPushMatrix();
					glTranslatef((float)(k*TILE_SIZE-mapFineOffset_x+LEFT_BORDER+TILE_SIZE*0.5), (float)(i*TILE_SIZE-mapFineOffset_y+BOTTOM_BORDER+TILE_SIZE*0.5), 0);
					IndoorMap->render(IndoorTex[0]);
				glPopMatrix();
				break;
			case LEFT_WALL:
				IndoorMap->changeSubImage(29); 
				IndoorMap->changeVariation(14);

				//Render Tile
				glPushMatrix();
					glTranslatef((float)(k*TILE_SIZE-mapFineOffset_x+LEFT_BORDER+TILE_SIZE*0.5), (float)(i*TILE_SIZE-mapFineOffset_y+BOTTOM_BORDER+TILE_SIZE*0.5), 0);
					IndoorMap->render(IndoorTex[0]);
				glPopMatrix();
				break;
			case WALL_TOP:
				IndoorMap->changeSubImage(28); 
				IndoorMap->changeVariation(14);

				//Render Tile
				glPushMatrix();
					glTranslatef((float)(k*TILE_SIZE-mapFineOffset_x+LEFT_BORDER+TILE_SIZE*0.5), (float)(i*TILE_SIZE-mapFineOffset_y+BOTTOM_BORDER+TILE_SIZE*0.5), 0);
					IndoorMap->render(IndoorTex[0]);
				glPopMatrix();
				break;
			case LEFT_CORNER1:
				IndoorMap->changeSubImage(29); 
				IndoorMap->changeVariation(18);

				//Render Tile
				glPushMatrix();
					glTranslatef((float)(k*TILE_SIZE-mapFineOffset_x+LEFT_BORDER+TILE_SIZE*0.5), (float)(i*TILE_SIZE-mapFineOffset_y+BOTTOM_BORDER+TILE_SIZE*0.5), 0);
					IndoorMap->render(IndoorTex[0]);
				glPopMatrix();
				break;
			case LEFT_CORNER2:
				IndoorMap->changeSubImage(29); 
				IndoorMap->changeVariation(17);

				//Render Tile
				glPushMatrix();
					glTranslatef((float)(k*TILE_SIZE-mapFineOffset_x+LEFT_BORDER+TILE_SIZE*0.5), (float)(i*TILE_SIZE-mapFineOffset_y+BOTTOM_BORDER+TILE_SIZE*0.5), 0);
					IndoorMap->render(IndoorTex[0]);
				glPopMatrix();
				break;
			case LEFT_CORNER3:
				IndoorMap->changeSubImage(29); 
				IndoorMap->changeVariation(16);

				//Render Tile
				glPushMatrix();
					glTranslatef((float)(k*TILE_SIZE-mapFineOffset_x+LEFT_BORDER+TILE_SIZE*0.5), (float)(i*TILE_SIZE-mapFineOffset_y+BOTTOM_BORDER+TILE_SIZE*0.5), 0);
					IndoorMap->render(IndoorTex[0]);
				glPopMatrix();
				break;
			case SOFA_1:
				IndoorMap->changeSubImage(25); 
				IndoorMap->changeVariation(14);

				//Render Tile
				glPushMatrix();
					glTranslatef((float)(k*TILE_SIZE-mapFineOffset_x+LEFT_BORDER+TILE_SIZE*0.5), (float)(i*TILE_SIZE-mapFineOffset_y+BOTTOM_BORDER+TILE_SIZE*0.5), 0);
					IndoorMap->render(IndoorTex[0]);
				glPopMatrix();
				break;
			case SOFA_2:
				IndoorMap->changeSubImage(26); 
				IndoorMap->changeVariation(14);

				//Render Tile
				glPushMatrix();
					glTranslatef((float)(k*TILE_SIZE-mapFineOffset_x+LEFT_BORDER+TILE_SIZE*0.5), (float)(i*TILE_SIZE-mapFineOffset_y+BOTTOM_BORDER+TILE_SIZE*0.5), 0);
					IndoorMap->render(IndoorTex[0]);
				glPopMatrix();
				break;
			case SOFA_3:
				IndoorMap->changeSubImage(25); 
				IndoorMap->changeVariation(13);

				//Render Tile
				glPushMatrix();
					glTranslatef((float)(k*TILE_SIZE-mapFineOffset_x+LEFT_BORDER+TILE_SIZE*0.5), (float)(i*TILE_SIZE-mapFineOffset_y+BOTTOM_BORDER+TILE_SIZE*0.5), 0);
					IndoorMap->render(IndoorTex[0]);
				glPopMatrix();
				break;
			case SOFA_4:
				IndoorMap->changeSubImage(25); 
				IndoorMap->changeVariation(12);

				//Render Tile
				glPushMatrix();
					glTranslatef((float)(k*TILE_SIZE-mapFineOffset_x+LEFT_BORDER+TILE_SIZE*0.5), (float)(i*TILE_SIZE-mapFineOffset_y+BOTTOM_BORDER+TILE_SIZE*0.5), 0);
					IndoorMap->render(IndoorTex[0]);
				glPopMatrix();
				break;
			default: //Ground
				IndoorMap->changeSubImage(2); 
				IndoorMap->changeVariation(9); 

				//Render Tile
				glPushMatrix();
					glTranslatef((float)(k*TILE_SIZE-mapFineOffset_x+LEFT_BORDER+TILE_SIZE*0.5), (float)(i*TILE_SIZE-mapFineOffset_y+BOTTOM_BORDER+TILE_SIZE*0.5), 0);
					IndoorMap->render(IndoorTex[0]);
				glPopMatrix();
				break;
			}
		}
	}

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

 /****************************************************************************************************
   Draw the Minimap
 ****************************************************************************************************/
void CMap::RenderMiniMap(CMap* map) {

	glPushMatrix();

	int miniTileSize = 2;
	int yStart = -10;
	int renderExtraY = 0;

	if (yStart+tileOffset_y < 0)
		yStart=-tileOffset_y;
	
	renderExtraY = 20 + yStart;
	int xStart = -10;
	int renderExtraX = 0;

	if (xStart+tileOffset_x < 0)
		xStart = -tileOffset_x;

	renderExtraX = 20 + xStart;

	//Loop through column
	for (short i = yStart; i < map->getNumOfTiles_ScreenHeight()+renderExtraY; ++i)
	{
		//Loop through row
		for (short k = xStart; k < map->getNumOfTiles_ScreenWidth()+1+renderExtraX; ++k)
		{
			bool stop = false;

			//if we have reached the right side of the Map, then do not display the extra column of tiles.
			if ((tileOffset_x+k) >= map->getNumOfTiles_MapWidth())
				stop = true;

			//if we have reached the top side of the Map, then do not display the extra row of tiles.
			if ((tileOffset_y+i) >= map->getNumOfTiles_MapHeight())
				stop = true;

			if (!stop)
			{
				//Wall texture
				if (map->theScreenMap[tileOffset_y+i][tileOffset_x+k] == 1)
					glColor3f(0,0,0);
				else
					glColor3f(1,1,1);

				glPushMatrix();
					glTranslatef((float)((k-xStart)*miniTileSize), (float)((i-yStart)*miniTileSize), 0);
					//glEnable(GL_TEXTURE_2D);
					glEnable(GL_BLEND);
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					//glBindTexture(GL_TEXTURE_2D, TileMapTexture[map->theScreenMap[tileOffset_y+i][tileOffset_x+k]].texID);
					glBegin(GL_QUADS);
						glTexCoord2f(0,1); glVertex2f(0,0);
						glTexCoord2f(0,0); glVertex2f(0,(float)miniTileSize);
						glTexCoord2f(1,0); glVertex2f((float)miniTileSize,(float)miniTileSize);
						glTexCoord2f(1,1); glVertex2f((float)miniTileSize,0);
					glEnd();
					glDisable(GL_BLEND);
					//glDisable(GL_TEXTURE_2D);
				glPopMatrix();
			}

			else
			{
				glColor3f(0,0,0);
				glPushMatrix();
					glTranslatef((float)((k-xStart)*miniTileSize), (float)((i-yStart)*miniTileSize), 0);
					//glEnable(GL_TEXTURE_2D);
					glEnable(GL_BLEND);
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					//glBindTexture(GL_TEXTURE_2D, TileMapTexture[map->theScreenMap[tileOffset_y+i][tileOffset_x+k]].texID);
					glBegin(GL_QUADS);
						glTexCoord2f(0,1); glVertex2f(0,0);
						glTexCoord2f(0,0); glVertex2f(0,(float)miniTileSize);
						glTexCoord2f(1,0); glVertex2f((float)miniTileSize,(float)miniTileSize);
						glTexCoord2f(1,1); glVertex2f((float)miniTileSize,0);
					glEnd();
					glDisable(GL_BLEND);
					//glDisable(GL_TEXTURE_2D);
				glPopMatrix();
			}
		}
	}

	int miniOffset_y = yStart+tileOffset_y;
	int miniOffset_x = xStart+tileOffset_x;
	glColor3f(1,0,0);

	float xTranslate = (((CPlayer::getInstance()->GetPos().x-LEFT_BORDER)/32)+tileOffset_x-miniOffset_x)*2;
	float yTranslate = (((CPlayer::getInstance()->GetPos().y-BOTTOM_BORDER)/32)+tileOffset_y-miniOffset_y)*2;

	glColor3f(0,0.6f,1);
	glPushMatrix();
		glTranslatef(xTranslate, yTranslate, 0);
		//glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//glBindTexture(GL_TEXTURE_2D, TileMapTexture[map->theScreenMap[tileOffset_y+i][tileOffset_x+k]].texID);
		glBegin(GL_QUADS);
			glTexCoord2f(0,1); glVertex2f(0,0);
			glTexCoord2f(0,0); glVertex2f(0,(float)miniTileSize);
			glTexCoord2f(1,0); glVertex2f((float)miniTileSize,(float)miniTileSize);
			glTexCoord2f(1,1); glVertex2f((float)miniTileSize,0);
		glEnd();
		glDisable(GL_BLEND);
		//glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glColor3f(1,1,1);
	glPopMatrix();
}

 /****************************************************************************************************
   Draw the map border
 ****************************************************************************************************/
void CMap::RenderMapBorder()
{
	glPushMatrix();

	//Loop through column
	for(int i = 0; i < theBorder->getNumOfTiles_ScreenHeight()+3; ++i)
	{
		//Loop through row
		for(int k = 0; k < theBorder->getNumOfTiles_ScreenWidth()+2; k ++)
		{
			//Border texture
			if (theBorder->theScreenMap[i][k] == 1)
			{
				glPushMatrix();
				glTranslatef((float)(k*TILE_SIZE+LEFT_BORDER-TILE_SIZE), (float)(i*TILE_SIZE+BOTTOM_BORDER-2*TILE_SIZE), 0);
				glEnable(GL_TEXTURE_2D);
				glEnable(GL_BLEND);
				glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				glBindTexture(GL_TEXTURE_2D, border[0].texID);
				glBegin(GL_QUADS);
					glTexCoord2f(0,1); glVertex2f(0,0);
					glTexCoord2f(0,0); glVertex2f(0,TILE_SIZE);
					glTexCoord2f(1,0); glVertex2f(TILE_SIZE,TILE_SIZE);
					glTexCoord2f(1,1); glVertex2f(TILE_SIZE,0);
				glEnd();
				glDisable(GL_BLEND);
				glDisable(GL_TEXTURE_2D);
				glPopMatrix();
			}
		}
	}
	glPopMatrix();
}

bool CMap::LoadMap(const string mapName)
{
	if (!LoadFile(mapName))
	{
		printf("Failed to load Map \"%s\" !\n\n", mapName.c_str());
		return false;
	}

	//Map Successfully Loaded
	printf("Map \"%s\" has been successfully loaded!\n\n", mapName.c_str());
	return true;
}

bool CMap::LoadFile(const string mapName)
{
	int theLineCounter = 0;
	int theMaxNumOfColumns = 0;

	ifstream file(mapName.c_str());

	//File Does Not Exist
	if (file == NULL)
		return false;

	if(file.is_open())
	{
		int i = 0, k = 0;
		while(file.good())
		{
			string aLineOfText = "";
			getline(file, aLineOfText);

			//if this line is not a comment line, then process it
			if(!(aLineOfText.find("//") == NULL) && aLineOfText != "")
			{
				if (theLineCounter == 0)
				{
					//This is the first line of the map data file
					string token;
					istringstream iss(aLineOfText);
					while(getline(iss, token, ','))
						//Count the number of columns
						theMaxNumOfColumns = atoi(token.c_str());
				}
				else
				{
					int theColumnCounter = 0;

					string token;
					istringstream iss(aLineOfText);
					while(getline(iss, token, ','))
						theScreenMap[theLineCounter][theColumnCounter++] = atoi(token.c_str());
				}
				theLineCounter++;
			}
		}
	}
	return true;
}

//Get the number of tiles for height of the screen
int CMap::getNumOfTiles_ScreenHeight()
{
	return theNumOfTiles_ScreenHeight;
}

//Get the number of tiles for width of the screen
int CMap::getNumOfTiles_ScreenWidth()
{
	return theNumOfTiles_ScreenWidth;
}

//Get the number of tiles for height of the map
int CMap::getNumOfTiles_MapHeight()
{
	return theNumOfTiles_MapHeight;
}

//Get the number of tiles for width of the map
int CMap::getNumOfTiles_MapWidth()
{
	return theNumOfTiles_MapWidth;
}