#pragma once
#include "Goodies.h"

//Minion
class CGuard : public CGoodies 
{

private:
	CGameTime IdleTime; // Time state
	CGameTime AttackTime; // Time state

	bool isMoving;

	bool heroAnimationInvert;
	int heroAnimationCounter;
public:
	CGuard(void);
	~CGuard(void);

	short CurrentState;

	enum Playerstate 
	{
		IDLE = 0,
		ATTACK,
		CHASE,
		MOVELEFT,
		MOVERIGHT,
		MOVEUP,
		MOVEDOWN,
		RETREAT,
		STATE_TOTAL
	};

	void SelfInit(void) ;
	bool Update(void);
	void Render();

	void Info();
	void IndividualAction();
	//void TeamAction();

	 void SetItem(ITEM_ID item_id , int SetItem);
	 int GetItem(ITEM_ID item_id);
};

