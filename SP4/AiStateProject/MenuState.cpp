#include <iostream>
using namespace std;

#include "GameStateManager.h"
#include "playstate.h"
#include "menustate.h"

CMenuState CMenuState::theMenuState;

void CMenuState::Init()
{
	theCamera = Camera::getInstance();
	cout << "CMenuState::Init\n" << endl;
}

void CMenuState::Cleanup()
{
	cout << "CMenuState::Cleanup\n" << endl;
}

void CMenuState::Pause()
{
	cout << "CMenuState::Pause\n" << endl;
}

void CMenuState::Resume()
{
	cout << "CMenuState::Resume\n" << endl;
}

void CMenuState::HandleEvents(CGameStateManager* theGSM)
{
	theGSM->PopState();
	//theGSM->PushState(CPlayState::Instance());
}

void CMenuState::Update(CGameStateManager* theGSM) 
{
	cout << "CMenuState::Update\n" << endl;
}

void CMenuState::Draw(CGameStateManager* theGSM) 
{
	theCamera->SetHUD(true);

	glColor3f(0,0,1);
	drawString();

	theCamera->SetHUD(false);
	
	cout << "CMenuState::Draw\n" << endl;
}

void CMenuState::drawString(){



	glLoadIdentity ();
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		//  Print the FPS to the window
		glColor3f( 1.0f, 1.0f, 1.0f);
		//printw (25.0, 25.0, 0, "FPS: %4.2f", fps);

		printw (350.0, 200.0, 0, "Menu Screen");

		//printw (25.0, 75.0, 0, "Cubes Gotten: %4d", theGlobal->InGameTime->GetCurrent());
	glPopAttrib();
}
