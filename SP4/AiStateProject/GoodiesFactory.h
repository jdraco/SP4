#ifndef CGOODIESFACTORY_H
#define CGOODIESFACTORY_H

#include "Goodies.h"

#include "PlayerInfo.h"
#include "Enemy.h"
#include "Shots.h"

class CGoodiesFactory
{
public:
	CGoodiesFactory(void);
	~CGoodiesFactory(void);

	//CGoodies* 
	CGoodies* CreateID(CVariable::OBJECT_ID Object);
	
};

#endif