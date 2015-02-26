#pragma once

//#include "GoodiesFactory.h"

#ifndef GLOBAL_H
#define GLOBAL_H

#include "Define.h"
#include "RandomGenerator.h"

//Camera
#include "Camera.h"

//Map
#include "Map.h"

class CGlobal
{
protected:
	static CGlobal* s_pInstance;
public:
	CGlobal(void);
	~CGlobal(void);

	Vector3D MousePos;
	bool MouseState;
	int MouseType;

	static CGlobal* getInstance();

	bool myKeys[255];

	//game time
	CGameTime* InGameTime;
	//random generator
	CRandomGenerator RG;
	
	//game map
	CMap* theMap;
	
	bool chestlocked;
		
	bool Collided(Vector3D pos, 
				  bool m_bCheckUpwards, bool m_bCheckDownwards, 
				  bool m_bCheckLeft, bool m_bCheckRight, CMap *map, int x_offset, int y_offset);
	void CheckCollision(Vector3D pos, CMap *map, int x_offset, int y_offset);
	bool FreeTiles(Vector3D pos, CMap *map, int x_offset, int y_offset, bool start, short UDLR);
	bool CheckTreasure(Vector3D pos, CMap *map, int x_offset, int y_offset);
	bool CheckDoor(Vector3D pos, Vector3D dir, CMap *map, int x_offset, int y_offset);
};

#endif