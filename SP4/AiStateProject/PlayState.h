#pragma once
#include "Map.h"
#include "Camera.h"
#include "GameState.h"
#include "GoodiesFactory.h"
#include "SpatialPartition\SpatialPartition.h"


class CPlayer;

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

protected:
	CPlayState() { }

private:
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
	
	//int counter;

	// Goodies and Goodies Factory
	
	CGoodiesFactory theGoodFactory;

	enum OBJ{
		MAIN,
		CHAR,
		TOTAL
	};

	CPlayerInfo *thePlayer;

	Camera* theCamera;
	// Group
	CGroup *theRoot;

	//vector<CGroup*> GroupList;

	//SpatialPartitioning
	CSpatialPartition* theSP;

	//global variable class
	CGlobal* theGlobal;

	//map rendering

	void LoadLevel(short level);
	short currentMap;

	vector<CObjectModel*> theObjectModel;
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
};
