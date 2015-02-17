#pragma once

#include <vector>
using namespace std;

class CGameState;

class CGameStateManager
{
public:

	void Init(const char* title, int width=640, int height=480, 
		      int bpp=0, bool fullscreen=false);
	void Cleanup();

	void ChangeState(CGameState* state);
	void PushState(CGameState* state);
	void PopState();

	void HandleEvents();
	void Update();
	void Draw();

	bool Running() { return m_bRunning; }
	void Quit() { m_bRunning = false; }

private:
	// the stack of states
	vector<CGameState*> StackOfStates;

	bool m_bRunning;
	bool m_bFullscreen;
};
