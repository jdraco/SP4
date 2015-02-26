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
	theNpc = new CNpc();
	theNpc->init();
	font = new CFont();
	hud = new HUD();
	//theGlobal->lock = new CLock();
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
	 
	 //Player init
	LoadLevel(currentMap);
	
	ScanMap();

	//thePlayer->Init();
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
	ScanMap();
	//Constrain Hero to middle of screen (unless he reaches the border)
	ConstrainPlayer((const int)(MAP_SCREEN_WIDTH*0.5+LEFT_BORDER), (const int)(MAP_SCREEN_WIDTH*0.5+LEFT_BORDER), 
					(const int)(MAP_SCREEN_HEIGHT*0.5+BOTTOM_BORDER), (const int)(MAP_SCREEN_HEIGHT*0.5+BOTTOM_BORDER),
					1.0f, theGlobal->theMap->mapOffset_x, theGlobal->theMap->mapOffset_y);

	theGlobal->theMap->Update();

	theGlobal->InGameTime->Update();

	//guardupdate
	for(unsigned a = 0; a < GuardList.size(); ++a)
	{
		CGuard *guard = GuardList[a];
		guard->Update();
	}
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
	thePlayer->SetGuardList(GuardList);
	if(!theGlobal->lock->active)
	thePlayer->Update();
	theNpc->Update();
	if(theGlobal->lock->active)//inventory add item type lockpick
	{
		bool movelock = false;
		float dirV = 0;
		if(theGlobal->myKeys[' '])
			movelock = true;
		if(theGlobal->myKeys[8])
			theGlobal->lock->active = false;
		if(theGlobal->myKeys['a'] || theGlobal->myKeys['A'])
			dirV = -1;
		if(theGlobal->myKeys['d'] || theGlobal->myKeys['D'] )
			dirV = 1;

		int lockReturn = theGlobal->lock->Update(dirV,movelock);
		if(lockReturn == 1)
		{	
			theGlobal->lock->active = false;
			theGlobal->lock->Reset(true, 30, 100);
			if(theGlobal->Unlock(thePlayer->GetPos() , thePlayer->GetDir(), theGlobal->theMap, 
			theGlobal->theMap->mapOffset_x, theGlobal->theMap->mapOffset_y,lockReturn))
			{
				int random_loot = rand()%6+1;
				thePlayer->myInventory.addItem(random_loot);
			}
		}
		if(lockReturn == -1)
		{	
			theGlobal->lock->Reset(false, 0 ,0);
		}
	}
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
	theNpc->Popup();
	theNpc->render();
	thePlayer->Render();
	if(theGlobal->lock->active)
		theGlobal->lock->Render();
	for(unsigned a = 0; a < GuardList.size(); ++a)
	{
		CGuard *guard = GuardList[a];
		if(guard->active == true)
			guard->Render();
	}
	//font->Render("HELLO /Bye",thePlayer->GetPos(),Vector3D(0,1,1));
	hud->renderHUD(100,0, 1, theGlobal->MousePos.x,theGlobal->MousePos.y,theGlobal->MouseState,theGlobal->MouseType,glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT),thePlayer->myInventory,thePlayer->getCurrEquipped());
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

		//Scroll Enemies with Map
		for(unsigned a = 0; a < GuardList.size(); ++a)
		{
			CGuard *guard = GuardList[a];

			if (guard->active && mapOffset_x > 0)
			{
				guard->SetPos_x(guard->GetPos().x+ScrollSpeed);

				//Scroll Way Points
				
				for (short i = 0; i < (short)guard->OwnPath.Points.size(); ++i)
					guard->OwnPath.Points[i]->setX (guard->OwnPath.Points[i]->getX() + ScrollSpeed);
					
			}
		}

		/*
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
			float diffX = theNpc->GetPos().x - thePlayer->GetPos().x;
			theNpc->SetPos_x((float)leftBorder + diffX);
		}
		else if (thePlayer->GetPos().x < TILE_SIZE*3)
		{
			thePlayer->SetPos_x( TILE_SIZE*3 );
			for(int i = 0; i < thePlayer->GetBulletListSize(); i++)
			{
				float diffX = thePlayer->GetBullet(i)->GetPos().x - thePlayer->GetPos().x;
				thePlayer->GetBullet(i)->SetPosX(TILE_SIZE*3+diffX);
			}
			float diffX = theNpc->GetPos().x - thePlayer->GetPos().x;
			theNpc->SetPos_x(TILE_SIZE * 3 + diffX);
		}
	}

	else if (thePlayer->GetPos().x > rightBorder)
	{
		mapOffset_x += ScrollSpeed;
		
		//Scroll Enemies with Map
		for(unsigned a = 0; a < GuardList.size(); ++a)
		{
			CGuard *guard = GuardList[a];

			if (guard->active && mapOffset_x < RESOLUTION_WIDTH)
			{
				guard->SetPos_x(guard->GetPos().x-ScrollSpeed);

			for (short i = 0; i < (short)guard->OwnPath.Points.size(); ++i)
					guard->OwnPath.Points[i]->setX (guard->OwnPath.Points[i]->getX() - ScrollSpeed);
					
			}
		}	
		/*
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
			float diffX = theNpc->GetPos().x - thePlayer->GetPos().x;
			theNpc->SetPos_x((float)rightBorder + diffX);
		}
		else if (thePlayer->GetPos().x > RESOLUTION_WIDTH-TILE_SIZE*11)
		{
			thePlayer->SetPos_x( RESOLUTION_WIDTH-TILE_SIZE*11 );
			for(int i = 0; i < thePlayer->GetBulletListSize(); i++)
			{
				float diffX = thePlayer->GetBullet(i)->GetPos().x - thePlayer->GetPos().x;
				thePlayer->GetBullet(i)->SetPosX(RESOLUTION_WIDTH-TILE_SIZE*11+diffX);
			}
			float diffX = theNpc->GetPos().x - thePlayer->GetPos().x;
			theNpc->SetPos_x(RESOLUTION_WIDTH - TILE_SIZE * 11  + diffX);
		}
	}

	if (thePlayer->GetPos().y < topBorder)
	{
		mapOffset_y -= ScrollSpeed;
		
		for(unsigned a = 0; a < GuardList.size(); ++a)
		{
			CGuard *guard = GuardList[a];

			if (guard->active && mapOffset_y > 0)
			{
				guard->SetPos_y(guard->GetPos().y+ScrollSpeed);

				//Scroll Way Points
					for (short i = 0; i < (short)guard->OwnPath.Points.size(); ++i)
					guard->OwnPath.Points[i]->setY (guard->OwnPath.Points[i]->getY() + ScrollSpeed);
					
			}
		}

		//Scroll Skills with Map
		/*
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
			float diffY = theNpc->GetPos().y - thePlayer->GetPos().y;
			theNpc->SetPos_y((float)topBorder + diffY);
		}
		else if (thePlayer->GetPos().y < TILE_SIZE*4)
		{
			thePlayer->SetPos_y(TILE_SIZE*4);
			for(int i = 0; i < thePlayer->GetBulletListSize(); i++)
			{
				float diffY = thePlayer->GetBullet(i)->GetPos().y - thePlayer->GetPos().y;
				thePlayer->GetBullet(i)->SetPosY(TILE_SIZE*4+diffY);
			}
			float diffY = theNpc->GetPos().y - thePlayer->GetPos().y;
			theNpc->SetPos_y(TILE_SIZE * 4 + diffY);
		}
	}

	else if (thePlayer->GetPos().y > bottomBorder)
	{
		mapOffset_y += ScrollSpeed;
		
		//Scroll Enemies with Map
		for(unsigned a = 0; a < GuardList.size(); ++a)
		{
			CGuard *guard = GuardList[a];

			if (guard->active && mapOffset_y < RESOLUTION_HEIGHT*2.15)
			{
				guard->SetPos_y(guard->GetPos().y-ScrollSpeed);

				//Scroll Way Points
			for (short i = 0; i < (short)guard->OwnPath.Points.size(); ++i)
					guard->OwnPath.Points[i]->setY (guard->OwnPath.Points[i]->getY() - ScrollSpeed);
					
			}
		}
		/*
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
			float diffY = theNpc->GetPos().y - thePlayer->GetPos().y;
			theNpc->SetPos_y((float)bottomBorder + diffY);
		}
		else if (thePlayer->GetPos().y > RESOLUTION_HEIGHT*2.15-TILE_SIZE*3)
		{
			thePlayer->SetPos_y ( RESOLUTION_HEIGHT*2.15-TILE_SIZE*3 );
			for(int i = 0; i < thePlayer->GetBulletListSize(); i++)
			{
				float diffY = thePlayer->GetBullet(i)->GetPos().y - thePlayer->GetPos().y;
				thePlayer->GetBullet(i)->SetPosY(RESOLUTION_HEIGHT*2.15-TILE_SIZE*3+diffY);
			}
			float diffY = theNpc->GetPos().y - thePlayer->GetPos().y;
			theNpc->SetPos_y(RESOLUTION_HEIGHT*2.15 - TILE_SIZE * 3 + diffY);
		}
	}
}
void CPlayState::ScanMap()
{

	int NoOfMob = 0;
	//Loop through column

		for (short p = 0; p < theGlobal->theMap->getNumOfTiles_MapHeight(); ++p)
			{
				//Loop through row
				for (short q = 0; q < theGlobal->theMap->getNumOfTiles_MapWidth(); ++q)
				{
					int current = theGlobal->theMap->theScreenMap[p][q];
					switch (current) 
					{
						case CMap::SPAWN_MONSTER:
							NoOfMob++;
							break;
						//WayPoint initing
						case CMap::PATH_ONE:
							///Vector3D * temp = 
							Paths[0].Points.push_back(new Vector3D((float)(q*TILE_SIZE+LEFT_BORDER-theGlobal->theMap->mapOffset_x), (float)(p*TILE_SIZE+BOTTOM_BORDER-theGlobal->theMap->mapOffset_y)));
							break;
						case CMap::PATH_TWO:
							Paths[1].Points.push_back(new Vector3D(((float)(q*TILE_SIZE+LEFT_BORDER-theGlobal->theMap->mapOffset_x), (float)(p*TILE_SIZE+BOTTOM_BORDER-theGlobal->theMap->mapOffset_y))));
							break;
					}

				}
			}


	for (short i = 0; i < theGlobal->theMap->getNumOfTiles_MapHeight(); ++i)
	{
		//Loop through row
		for (short k = 0; k < theGlobal->theMap->getNumOfTiles_MapWidth(); ++k)
		{
			int current = theGlobal->theMap->theScreenMap[i][k];

			//Process Tiles
			switch (current) 
			{
			case CMap::SPAWN_MONSTER:
				
				

				if (NoOfMob > GuardList.size())
				{
					cout << NoOfMob  << " , " << GuardList.size() << endl;
					//Create new Enemy
					CGuard *temp = new CGuard; 
					temp->SelfInit();
					temp->SetPos(Vector3D((float)(k*TILE_SIZE+LEFT_BORDER-theGlobal->theMap->mapOffset_x), (float)(i*TILE_SIZE+BOTTOM_BORDER-theGlobal->theMap->mapOffset_y)));
					temp->SetPath(Paths[0]);
					//temp->SetWayPoints(); //Set Way Points for Enemy
					cout << temp->GetPos().x << " , " <<  temp->GetPos().x << endl;

					GuardList.push_back(temp); 
				}
				break;

			}
		}
	} 

}

