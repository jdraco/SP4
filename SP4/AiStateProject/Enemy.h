#pragma once

#include "Goodies.h"

class CEnemy : public CGoodies 
{
private:
	CGameTime StateTime;
	CGameTime ShotTime;
	CGameTime DirTime;

	CGoodies *Player;
	bool placing;
public:
	CEnemy(void);
	~CEnemy(void);

	void SelfInit(void) ;
	bool Update(void);
	void Render();

	//For the states
	int hp;
	
	int strength;
	float Rresist;
	float Mresist;

	 void SetItem(ITEM_ID item_id , int SetItem);
	 int GetItem(ITEM_ID item_id);

};

