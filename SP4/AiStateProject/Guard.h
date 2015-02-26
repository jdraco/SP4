#pragma once
#include "Goodies.h"

class CPlayerInfo;

class CGuard : public CGoodies 
{

private:
	CGameTime IdleTime; // Time state
	CGameTime AttackTime; // Time state

	//Store player info
	CPlayerInfo* Player;
	CSprite* GuardSprite;



	bool isMoving;
	bool NeedRender;

	bool heroAnimationInvert;
	int heroAnimationCounter;
public:
	CGuard(void);
	~CGuard(void);

	//path point;
	CWayPoint OwnPath;
	void Movement();

	short CurrentState;

	enum Playerstate 
	{
		IDLE = 0,
		ATTACK,
		CHASE,
		PATROL,
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

	 //Get player info over
	 void SetTarget(CPlayerInfo* thePlayer);
	  //set path for guard to walk
	 void SetPath(CWayPoint ownpath) { OwnPath = ownpath; } ;

	 // CPlayerInfo GetTarget();
};

