#include <iostream>
using namespace std;

#include "gamestate.h"
#include "GameStateManager.h"
#include "playstate.h"
#include "menustate.h"

CPlayState CPlayState::thePlayState;

void CPlayState::Init()
{
	cubeCount = 0;
	
	thePlayer = CPlayerInfo::getInstance();
	thePlayer->Init();

	hud = new HUD();
	//weapManager = new CweaponManager();
	//weapManager->InitDB();

	theCamera = Camera::getInstance();

	theGlobal = CGlobal::getInstance();
	
	//Set Up Map
	theGlobal->theMap = CMap::getInstance();
	theGlobal->theMap->mapInit = false;
	theGlobal->theMap->Init(MAP_SCREEN_HEIGHT, MAP_SCREEN_WIDTH, RESOLUTION_HEIGHT*3, RESOLUTION_WIDTH*2, TILE_SIZE);
	currentMap = theGlobal->theMap->STARTING_MAP;
	string MapName = "MapDesign" + static_cast<ostringstream*>(&(ostringstream()<<currentMap))->str() + ".csv";
	theGlobal->theMap->LoadTextures();
	if (!theGlobal->theMap->LoadMap(MapName))
		cout << "Map Failed" << endl;

	theGlobal->theMap->mapInit = true;

	theGlobal->theMap->theBorder = new CMap;
	theGlobal->theMap->theBorder->Init(MAP_SCREEN_HEIGHT, MAP_SCREEN_WIDTH, RESOLUTION_HEIGHT*2, RESOLUTION_WIDTH*2, TILE_SIZE);
	string BorderName = "Border" + static_cast<ostringstream*>(&(ostringstream()<<MAP_SCREEN_WIDTH))->str() + ".csv";
	if (!theGlobal->theMap->theBorder->LoadMap(BorderName))
		cout << "Border Failed" << endl; //Init Failed
	theGlobal->theMap->theBorder->mapInit = true;


	theGlobal->InGameTime->SetCurrent();
	 theGlobal->InGameTime->SetTotalTime(60);
	 lastTime =  theGlobal->InGameTime->GetCurrent();
}



void CPlayState::Cleanup()
{
	for (int i = 0; i < 10; i++)
	{
		delete CGoodies::theArrayOfGoodies[i];
		CGoodies::theArrayOfGoodies[i] = NULL;
	}

	delete theGlobal->theMap ; //thePlayer

	exit(0);
	//cout << "CPlayState::Cleanup\n" << endl;
}

void CPlayState::Pause()
{
	//cout << "CPlayState::Pause\n" << endl;
}

void CPlayState::Resume()
{
	//cout << "CPlayState::Resume\n" << endl;
}

void CPlayState::HandleEvents(CGameStateManager* theGSM)
{
	theGSM->PushState(CMenuState::Instance());
}

void CPlayState::Update(CGameStateManager* theGSM)
{
	//Constrain Hero to middle of screen (unless he reaches the border)
	ConstrainPlayer((const int)(MAP_SCREEN_WIDTH*0.5+LEFT_BORDER), (const int)(MAP_SCREEN_WIDTH*0.5+LEFT_BORDER), 
					(const int)(MAP_SCREEN_HEIGHT*0.5+BOTTOM_BORDER), (const int)(MAP_SCREEN_HEIGHT*0.5+BOTTOM_BORDER),
					1.0f, theGlobal->theMap->mapOffset_x, theGlobal->theMap->mapOffset_y);

	theGlobal->theMap->Update();

	theGlobal->InGameTime->Update();

	/*
	if(theGlobal->InGameTime->GetCurrent() < lastTime-3){ 
		int A = theGlobal->RG.getImmediateResult(0,theGlobal->theMain.size()-1);
		CGroup *go = theGlobal->theMain[A];
		go->SetPos(go->GetPos().x,go->GetPos().y+5,go->GetPos().z);
		go->obtainable = true;
		//Wait for 3sec more
		lastTime = theGlobal->InGameTime->GetCurrent();
	}
	*/
	//theCamera->SetPlayerInfo(thePlayer->GetPos(), thePlayer->GetRot());

	thePlayer->Update();
	//cout << "CPlayState::Update\n" << endl;
}

void CPlayState::Draw(CGameStateManager* theGSM)
{
	/*
	for(unsigned a = 0; a < theGlobal->theMain.size(); ++a)
	{
		CGroup *go = theGlobal->theMain[a];
			
		if(go->rendered == false)
		{
			if(go->active == true)
			{
				go->Draw();
			}
		}
	}
	*/
	
		
	theCamera->SetHUD(true);
	glColor3f(1,1,1);
	LoadLevel(currentMap);
	thePlayer->Render();
	hud->renderHUD(100,0, 1, theGlobal->MousePos.x,theGlobal->MousePos.y,theGlobal->MouseState,70,glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT),thePlayer->myInventory);
	//glColor3f(0,0,1);
	//printw (500, 50, 0, "Test");
	//drawString();
	theCamera->SetHUD(false);
	

	//cout << "CPlayState::Draw : " << counter << "\n" << endl;
}


void CPlayState::drawString()
{
	//  Load the identity matrix so that FPS string being drawn
	//  won't get animates
	glLoadIdentity ();
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		//  Print the FPS to the window
		glColor3f( 1.0f, 1.0f, 1.0f);
		//printw (25.0, 25.0, 0, "FPS: %4.2f", fps);

		printw (25.0, 50.0, 0, "Time Left: %4d", theGlobal->InGameTime->GetCurrent());
		printw (25.0, 75.0, 0, "Cube Gotten: %4d", cubeCount);

		//printw (25.0, 75.0, 0, "Cubes Gotten: %4d", theGlobal->InGameTime->GetCurrent());
	glPopAttrib();
}

void CPlayState::LoadLevel(short level)
{
	//Set Current Level 
	currentMap = level;

	//Set Map
	theGlobal->theMap->theMap = theGlobal->theMap->MapL(level);

	//Re-Init Map
	if (!theGlobal->theMap->mapInit)
	{
		theGlobal->theMap->Init(MAP_SCREEN_HEIGHT, MAP_SCREEN_WIDTH, RESOLUTION_HEIGHT*3, RESOLUTION_WIDTH*2, TILE_SIZE);

		//Load Map from CSV
		string MapName = "MapDesign" + static_cast<ostringstream*>(&(ostringstream()<<theGlobal->theMap->theMap))->str() + ".csv";
		if (!theGlobal->theMap->LoadMap(MapName))
		{
			cout << "Loading Map \"MapDesign" << theGlobal->theMap->STARTING_MAP << ".csv\" instead." << endl << endl;
			LoadLevel(theGlobal->theMap->STARTING_MAP);
		}

		theGlobal->theMap->mapInit = true;
		return;
	}
	

	//Render Map
	theGlobal->theMap->RenderTileMap(theGlobal->theMap);
	//Render Map Border
	theGlobal->theMap->RenderMapBorder();
}

void CPlayState::ConstrainPlayer(const int leftBorder, const int rightBorder, 
							  const int topBorder, const int bottomBorder, 
							  float timeDiff,
							  int& mapOffset_x, int& mapOffset_y)
{
	//Map's Scrolling Speed
	int ScrollSpeed = (int)(MAP_SCROLL_SPEED * timeDiff);

	if (thePlayer->GetPos().x < leftBorder)
	{
		mapOffset_x -= ScrollSpeed;
		/*
		//Scroll Enemies with Map
		for (vector<CEnemy*>::iterator it = CPlayState::Instance()->EnemyList.begin(); it < CPlayState::Instance()->EnemyList.end(); ++it)
		{
			CEnemy *CurrentEnemy = *it;

			if (CurrentEnemy->active && mapOffset_x > 0)
			{
				CurrentEnemy->setPosX(CurrentEnemy->getPos().x+ScrollSpeed);

				//Scroll Way Points
				for (short i = 0; i < (short)CurrentEnemy->Path->WayPointList.size(); ++i)
					CurrentEnemy->Path->WayPointList[i].x += ScrollSpeed;
			}
		}

		//Scroll Skills with Map
		for (vector<CSkill*>::iterator it = SkillsList.begin(); it != SkillsList.end(); ++it)
		{
			if ((*it)->active && mapOffset_x > 0)
				(*it)->SetPosX((*it)->GetPos().x+ScrollSpeed);
		}
		*/	
		//Set Limit
		if (mapOffset_x < 0)
			mapOffset_x = 0;
		//Player will be at the middle of the screen
		if (mapOffset_x != 0)
		{
			thePlayer->SetPos_x((float)leftBorder);
			for(int i = 0; i < thePlayer->GetBulletListSize(); i++)
			{
				float diffX = thePlayer->GetBullet(i)->GetPos().x - thePlayer->GetPos().x;
				thePlayer->GetBullet(i)->SetPosX((float)leftBorder+diffX);
			}
		}
		else if (thePlayer->GetPos().x < TILE_SIZE*3)
		{
			thePlayer->SetPos_x( TILE_SIZE*3 );
			for(int i = 0; i < thePlayer->GetBulletListSize(); i++)
			{
				float diffX = thePlayer->GetBullet(i)->GetPos().x - thePlayer->GetPos().x;
				thePlayer->GetBullet(i)->SetPosX(TILE_SIZE*3+diffX);
			}
		}
	}

	else if (thePlayer->GetPos().x > rightBorder)
	{
		mapOffset_x += ScrollSpeed;
		/*
		//Scroll Enemies with Map
		for (vector<CEnemy*>::iterator it = CPlayState::Instance()->EnemyList.begin(); it < CPlayState::Instance()->EnemyList.end(); ++it)
		{
			CEnemy *CurrentEnemy = *it;

			if (CurrentEnemy->active && mapOffset_x < RESOLUTION_WIDTH)
			{
				CurrentEnemy->setPosX(CurrentEnemy->getPos().x-ScrollSpeed);

				//Scroll Way Points
				for (short i = 0; i < (short)CurrentEnemy->Path->WayPointList.size(); ++i)
					CurrentEnemy->Path->WayPointList[i].x -= ScrollSpeed;
			}
		}	

		//Scroll Skills with Map
		for (vector<CSkill*>::iterator it = SkillsList.begin(); it != SkillsList.end(); ++it)
		{
			if ((*it)->active && mapOffset_x < RESOLUTION_WIDTH)
				(*it)->SetPosX((*it)->GetPos().x-ScrollSpeed);
		}
		*/
		//Set Limit
		if (mapOffset_x > RESOLUTION_WIDTH)
			mapOffset_x = RESOLUTION_WIDTH;

		//Player will be at the middle of the screen
		if (mapOffset_x < 999)
		{
			thePlayer->SetPos_x( (float)rightBorder );
			for(int i = 0; i < thePlayer->GetBulletListSize(); i++)
			{
				float diffX = thePlayer->GetBullet(i)->GetPos().x - thePlayer->GetPos().x;
				thePlayer->GetBullet(i)->SetPosX((float)rightBorder+diffX);
			}
		}
		else if (thePlayer->GetPos().x > RESOLUTION_WIDTH-TILE_SIZE*11)
		{
			thePlayer->SetPos_x( RESOLUTION_WIDTH-TILE_SIZE*11 );
			for(int i = 0; i < thePlayer->GetBulletListSize(); i++)
			{
				float diffX = thePlayer->GetBullet(i)->GetPos().x - thePlayer->GetPos().x;
				thePlayer->GetBullet(i)->SetPosX(RESOLUTION_WIDTH-TILE_SIZE*11+diffX);
			}
		}
	}

	if (thePlayer->GetPos().y < topBorder)
	{
		mapOffset_y -= ScrollSpeed;
		/*
		//Scroll Enemies with Map
		for (vector<CEnemy*>::iterator it = CPlayState::Instance()->EnemyList.begin(); it < CPlayState::Instance()->EnemyList.end(); ++it)
		{
			CEnemy *CurrentEnemy = *it;

			if (CurrentEnemy->active && mapOffset_y > 0)
			{
				CurrentEnemy->setPosY(CurrentEnemy->getPos().y+ScrollSpeed);

				//Scroll Way Points
				for (short i = 0; i < (short)CurrentEnemy->Path->WayPointList.size(); ++i)
					CurrentEnemy->Path->WayPointList[i].y += ScrollSpeed;
			}
		}

		//Scroll Skills with Map
		for (vector<CSkill*>::iterator it = SkillsList.begin(); it != SkillsList.end(); ++it)
		{
			if ((*it)->active && mapOffset_y > 0)
				(*it)->SetPosY((*it)->GetPos().y+ScrollSpeed);
		}
		*/
		//Set Limit
		if (mapOffset_y < 0)
			mapOffset_y = 0;

		//Player will be at the middle of the screen
		if (mapOffset_y != 0)
		{
			thePlayer->SetPos_y( (float)topBorder );
			for(int i = 0; i < thePlayer->GetBulletListSize(); i++)
			{
				float diffY = thePlayer->GetBullet(i)->GetPos().y - thePlayer->GetPos().y;
				thePlayer->GetBullet(i)->SetPosY((float)topBorder+diffY);
			}
		}
		else if (thePlayer->GetPos().y < TILE_SIZE*4)
		{
			thePlayer->SetPos_y(TILE_SIZE*4);
			for(int i = 0; i < thePlayer->GetBulletListSize(); i++)
			{
				float diffY = thePlayer->GetBullet(i)->GetPos().y - thePlayer->GetPos().y;
				thePlayer->GetBullet(i)->SetPosY(TILE_SIZE*4+diffY);
			}
		}
	}

	else if (thePlayer->GetPos().y > bottomBorder)
	{
		mapOffset_y += ScrollSpeed;
		/*
		//Scroll Enemies with Map
		for (vector<CEnemy*>::iterator it = CPlayState::Instance()->EnemyList.begin(); it < CPlayState::Instance()->EnemyList.end(); ++it)
		{
			CEnemy *CurrentEnemy = *it;

			if (CurrentEnemy->active && mapOffset_y < RESOLUTION_HEIGHT*2.15)
			{
				CurrentEnemy->setPosY(CurrentEnemy->getPos().y-ScrollSpeed);

				//Scroll Way Points
				for (short i = 0; i < (short)CurrentEnemy->Path->WayPointList.size(); ++i)
					CurrentEnemy->Path->WayPointList[i].y -= ScrollSpeed;
			}
		}

		//Scroll Skills with Map
		for (vector<CSkill*>::iterator it = SkillsList.begin(); it != SkillsList.end(); ++it)
		{
			if ((*it)->active && mapOffset_y < RESOLUTION_HEIGHT*2.15)
				(*it)->SetPosY((*it)->GetPos().y-ScrollSpeed);
		}
		*/
		//Set Limit
		if (mapOffset_y > RESOLUTION_HEIGHT*2.15)
			mapOffset_y = (int)(RESOLUTION_HEIGHT*2.15);

		//Player will be at the middle of the screen
		if (mapOffset_y < 1715) //1750
		{
			thePlayer->SetPos_y ((float)bottomBorder);
			for(int i = 0; i < thePlayer->GetBulletListSize(); i++)
			{
				float diffY = thePlayer->GetBullet(i)->GetPos().y - thePlayer->GetPos().y;
				thePlayer->GetBullet(i)->SetPosY((float)bottomBorder+diffY);
			}
		}
		else if (thePlayer->GetPos().y > RESOLUTION_HEIGHT*2.15-TILE_SIZE*3)
		{
			thePlayer->SetPos_y ( RESOLUTION_HEIGHT*2.15-TILE_SIZE*3 );
			for(int i = 0; i < thePlayer->GetBulletListSize(); i++)
			{
				float diffY = thePlayer->GetBullet(i)->GetPos().y - thePlayer->GetPos().y;
				thePlayer->GetBullet(i)->SetPosY(RESOLUTION_HEIGHT*2.15-TILE_SIZE*3+diffY);
			}
		}
	}
}
