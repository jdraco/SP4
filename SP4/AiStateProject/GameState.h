#pragma once

#include "GameStateManager.h"

class CGameState
{
public:
	virtual void Init() = 0;
	virtual void Cleanup() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual void HandleEvents(CGameStateManager* theGSM) = 0;
	virtual void Update(CGameStateManager* theGSM) = 0;
	virtual void Draw(CGameStateManager* theGSM) = 0;

	void ChangeState(CGameStateManager* theGSM, CGameState* state) {
		theGSM->ChangeState(state);
	}

protected:
	CGameState() { }
};
