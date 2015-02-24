#pragma once

#include "gamestate.h"
#include "GameMenu.h"
#include "Global.h"

class CMenuState : public CGameState
{
public:
	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(CGameStateManager* theGSM);
	void Update(CGameStateManager* theGSM);
	void Draw(CGameStateManager* theGSM);

	static CMenuState* Instance() {
		return &theMenuState;
	}

protected:
	CMenuState() { }

private:
	static CMenuState theMenuState;
	
	CGlobal* theGlobal;

	void drawString();
	Camera* theCamera;
	GameMenu* myMenu;
};
