#pragma once
#include "Map.h"
#include "weaponManager.h"
#include "Camera.h"
#include "GameState.h"
#include "GoodiesFactory.h"
#include "HUD.h"
#include "Font.h"

class CPlayer;
class CGuard;

class CPlayState : public CGameState
{
public:
	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(CGameStateManager* theGSM);
	void Update(CGameStateManager* theGSM);
	void Draw(CGameStateManager* theGSM);

	static CPlayState* Instance() {
		return &thePlayState;
	}
	
	
	
	// Goodies and Goodies Factory
	
	CGoodiesFactory* theGoodFactory;

	//Player
	CPlayerInfo *thePlayer;
	CweaponManager *weapManager;
	//vector<CGoodies*> GameObjList;

	//Guards
	vector<CGuard*> GuardList;
	

	//Dispaly HUD
	HUD* hud;
	
	//Camera (not in use)
	Camera* theCamera;

	//global variable class
	CGlobal* theGlobal;

	//NPC
	CNpc *theNpc;

	CLock *lock;

	//Path List
	CWayPoint Paths[ CMap::PATH_END - CMap::PATH_START -1 ];

protected:
	CPlayState() { }

private:
	CFont *font;
	static CPlayState thePlayState;
	
	enum TEXTURES {
		LEFT,
		FRONT,
		RIGHT,
		BACK,
		TOP,
		BOTTOM,
		NUM_TEXTURES
	};
	
	//map rendering

	void LoadLevel(short level);
	short currentMap;

	//save last time
	float lastTime;
	int cubeCount;

	void RenderHud();

	void drawString();

	//makes players at the center point, and scrolls the other stuff
	void ConstrainPlayer(const int leftBorder, const int rightBorder, 
							  const int topBorder, const int bottomBorder, 
							  float timeDiff,
							  int& mapOffset_x, int& mapOffset_y);

	void ScanMap();
};
