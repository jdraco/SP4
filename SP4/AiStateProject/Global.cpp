#include "Global.h"

CGlobal* CGlobal::s_pInstance = NULL;

CGlobal::CGlobal(void)
:	chestlocked(false)
{
	for(int i=0; i<255; i++){
		myKeys[i] = false;
	}
	InGameTime = new CGameTime;

	RG.Init(CRandomGenerator::RNG_NON_DETERMINISTIC,CRandomGenerator::RNG_RANDOM_TWISTER);
}


CGlobal::~CGlobal(void)
{
}

CGlobal* CGlobal::getInstance(){
	if(s_pInstance == NULL){
		s_pInstance = new CGlobal;
	}
	return s_pInstance;

}

//Check Collision to toggle effect
void CGlobal::CheckCollision(Vector3D pos, CMap *map, int x_offset, int y_offset)
{
	////Set Pos x and y
	//int x = (int)((x_offset+pos.x-LEFT_BORDER)/TILE_SIZE+0.5);
	//int y = (int)((y_offset+pos.y-BOTTOM_BORDER)/TILE_SIZE+0.5);

	////Determine which Tile type has been collided
	//switch (map->theScreenMap[y][x])
	//{
	//case CMap::GRASS:
	//	//Update Tile Change Before Changing Textures*
	//	UpdateTileChange(pos, map, x_offset, y_offset);
	//	//*This is to allow the tiles to change simultaneously.
	//	//Otherwise, the Tiles would not revert back to its
	//	//previous texture. This update function will be called
	//	//again at the end of the function to update any
	//	//other remaining tiles (where collision isn't detected).

	//	//Play Grass Rustling Sound
	//	CSound::getInstance()->PlayMusic(CSound::SOUND_GRASS, false, false);

	//	//Change Texture
	//	map->theScreenMap[y][x] = CMap::GRASS_CHANGE;
	//	break;
	//}

	////Update Tile Change 
	//UpdateTileChange(pos, map, x_offset, y_offset);
}

//Check for collision of player with obstacles in a certain position
bool CGlobal::Collided(Vector3D pos, 
						bool m_bCheckUpwards, bool m_bCheckDownwards, 
						bool m_bCheckLeft, bool m_bCheckRight, CMap *map, int x_offset, int y_offset)
{
	//The pos.x and pos.y are the top left corner of the hero, so we find the tile which this position occupies.
	int tile_topleft_x = (int)floor((float)(x_offset+pos.x-LEFT_BORDER) / TILE_SIZE);
	int tile_topleft_y = (int)floor((float)(y_offset+pos.y-BOTTOM_BORDER) / TILE_SIZE);

	//Init Collision Check Variables
	bool proceed = false;
	Vector3D reference[9];
	short j = 0;

	//If Out-Of-Bound, Return True
	if (tile_topleft_x < 0 || tile_topleft_x > map->getNumOfTiles_MapWidth()-2)
		return true;
	if (tile_topleft_y < 0 || tile_topleft_y > map->getNumOfTiles_MapHeight()-2)
		return true;

	//Player Dir.x = -1
	if (m_bCheckLeft)
	{
		//Check for Tiles without Collision (Free Tiles)
		if (FreeTiles(pos, map, x_offset, y_offset, true, 3) ||
			FreeTiles(pos, map, x_offset, y_offset, false, 3))
		{
			//Proceed to Check for Collision
			proceed = true;
			
			//Set Reference Point
			reference[j].Set((float)((tile_topleft_x)*TILE_SIZE+LEFT_BORDER), (float)((tile_topleft_y)*TILE_SIZE+BOTTOM_BORDER));
		
			++j;
		}
	}

	//Player Dir.x = 1
	if (m_bCheckRight)
	{
		//Check for Tiles without Collision (Free Tiles)
		if (FreeTiles(pos, map, x_offset, y_offset, true, 4) ||
			FreeTiles(pos, map, x_offset, y_offset, false, 4))
		{
			//Proceed to Check for Collision
			proceed = true;

			//Set Reference Point
			reference[j].Set((float)((tile_topleft_x+1)*TILE_SIZE+LEFT_BORDER), (float)((tile_topleft_y)*TILE_SIZE+BOTTOM_BORDER));
			
			++j;
		}
	}

	//Player Dir.y = 1
	if (m_bCheckUpwards)
	{
		//Check for Tiles without Collision (Free Tiles)
		if (FreeTiles(pos, map, x_offset, y_offset, true, 1) ||
			FreeTiles(pos, map, x_offset, y_offset, false, 1))
		{
			//Proceed to Check for Collision
			proceed = true;

			//Set Reference Point
			reference[j].Set((float)((tile_topleft_x)*TILE_SIZE+LEFT_BORDER), (float)((tile_topleft_y)*TILE_SIZE+BOTTOM_BORDER));
			
			++j;
		}
	}
	
	//Player Dir.y = -1
	if (m_bCheckDownwards)
	{
		////Ledge 
		//if (map->theScreenMap[tile_topleft_y+1][tile_topleft_x] == CMap::LEDGE ||
		//	map->theScreenMap[tile_topleft_y+1][tile_topleft_x+1] == CMap::LEDGE)
		//{
		//	//Do not proceed to check for Collision
		//	proceed = false;

		//	//Set Player to jump over ledge
		//	CPlayer::getInstance()->jump = true;

		//	//Play Jump Sound
		//	CSound::getInstance()->PlayMusic(CSound::SOUND_JUMP, false, false);

		//	//All Clear
		//	return false;
		//}

		////Usual Collision Check
		//else
		{
			//Check for Tiles without Collision (Free Tiles)
			if (FreeTiles(pos, map, x_offset, y_offset, true, 2) ||
				FreeTiles(pos, map, x_offset, y_offset, false, 2))
			{
				//Proceed to Check for Collision
				proceed = true;

				//Set Reference Point
				reference[j].Set((float)((tile_topleft_x)*TILE_SIZE+LEFT_BORDER), (float)((tile_topleft_y+1)*TILE_SIZE+BOTTOM_BORDER));

				++j;
			}
		}
	}

	//Collision Detection Check
	if (proceed)
	{
		//Check against reference points
		for (short i = 0; i < j; ++i)
		{
			//if collision is detected, return True
			if(abs(reference[i].x-x_offset-pos.x) < TILE_SIZE && abs(reference[i].y-y_offset-pos.y) < TILE_SIZE)
			{
				//Play Bump Music when collision is detected
				//if (CTimer::getInstance()->executeTime(bumpTime))
					//CSound::getInstance()->PlayMusic(CSound::SOUND_BUMP, false, false);
				return true;
			}
		}
	}

	//All Clear
	return false;
}

//Free Tiles
bool CGlobal::FreeTiles(Vector3D pos, CMap *map, int x_offset, int y_offset, bool start, short UDLR)
{
	//The pos.x and pos.y are the top left corner of the hero, so we find the tile which this position occupies.
	int x = (int)floor((float)(x_offset+pos.x-LEFT_BORDER) / TILE_SIZE);
	int y = (int)floor((float)(y_offset+pos.y-BOTTOM_BORDER) / TILE_SIZE);

	//Set Collision Dir
	switch (UDLR) 
	{
	//Up
	case 1: 
		if (!start)
			++x;
		break;

	//Down
	case 2: 
		if (start)
			++y;
		else 
		{
			++y;
			++x;
		}
		break;

    //Left
	case 3:
		if (!start)
			++y;
		break;

	//Right
	case 4: 
		if (start)
			++x;
		else
		{
			++y;
			++x;
		}
		break;
	}

	//Free Tiles (No-Collision)
	if (map->theScreenMap[y][x] != CMap::TILE_NULL &&
		map->theScreenMap[y][x] != CMap::ENTRANCE1 && map->theScreenMap[y][x] != CMap::ENTRANCE2 &&
		! (map->theScreenMap[y][x] < -1) )
		return true;

	return false;
}

bool CGlobal::CheckTreasure(Vector3D pos, CMap *map, int x_offset, int y_offset)//check if there is treasure
{
	//The pos.x and pos.y are the top left corner of the hero, so we find the tile which this position occupies.
	int x = (int)floor((float)(x_offset+pos.x-LEFT_BORDER) / TILE_SIZE);
	int y = (int)floor((float)(y_offset+pos.y-BOTTOM_BORDER) / TILE_SIZE);

	int random_openedORlocked = rand()%5;	//random from 0 to 4

	if(random_openedORlocked < 4)
	{
		if (chestlocked == true)
		{
			chestlocked = false;
		}

		if(map->theScreenMap[y+1][x] == CMap::CHEST_CLOSED)
		{
			//gettreasurefunc
			map->theScreenMap[y+1][x] = CMap::CHEST_OPENED;
			return true;
		}
		if(map->theScreenMap[y-1][x] == CMap::CHEST_CLOSED)
		{
			//gettreasurefunc
			map->theScreenMap[y-1][x] = CMap::CHEST_OPENED;
			return true;
		}
		if(map->theScreenMap[y][x+1] == CMap::CHEST_CLOSED)
		{
			//gettreasurefunc
			map->theScreenMap[y][x+1] = CMap::CHEST_OPENED;
			return true;
		}
		if(map->theScreenMap[y][x-1] == CMap::CHEST_CLOSED)
		{
			//gettreasurefunc
			map->theScreenMap[y][x-1] = CMap::CHEST_OPENED;
			return true;
		}
	}
	else
	{
		if (chestlocked == false)
		{
			chestlocked = true;
		}

		if(map->theScreenMap[y+1][x] == CMap::CHEST_CLOSED)
		{
			//gettreasurefunc
			map->theScreenMap[y+1][x] = CMap::CHEST_LOCKED;
			return true;
		}
		if(map->theScreenMap[y-1][x] == CMap::CHEST_CLOSED)
		{
			//gettreasurefunc
			map->theScreenMap[y-1][x] = CMap::CHEST_LOCKED;
			return true;
		}
		if(map->theScreenMap[y][x+1] == CMap::CHEST_CLOSED)
		{
			//gettreasurefunc
			map->theScreenMap[y][x+1] = CMap::CHEST_LOCKED;
			return true;
		}
		if(map->theScreenMap[y][x-1] == CMap::CHEST_CLOSED)
		{
			//gettreasurefunc
			map->theScreenMap[y][x-1] = CMap::CHEST_LOCKED;
			return true;
		}
	}

	return false;
}