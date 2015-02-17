#include "Player.h"

CPlayer* CPlayer::instance = 0;

CPlayer::CPlayer(void)
	: Gravity(GRAVITY), JumpPower(20)
{
	theGlobal = CGlobal::getInstance();
}


CPlayer::~CPlayer(void)
{
	
}

void CPlayer::SelfInit(void){
	if (!LoadTGA(&PlayerTexture[0], "images/red.tga"))
		cout << "Load Red fail" << endl;

	bLeft = bRight = bMoving = stopMovement = false;
}


void CPlayer::keyboardUpdate()
{
	//Delta Time
	float dt = CGameTime::GetDelta();


	//Constrain Hero to middle of screen (unless he reaches the border)
	ConstrainPlayer((const int)(MAP_SCREEN_WIDTH*0.5+LEFT_BORDER), (const int)(MAP_SCREEN_WIDTH*0.5+LEFT_BORDER), 
					(const int)(MAP_SCREEN_HEIGHT*0.5+BOTTOM_BORDER), (const int)(MAP_SCREEN_HEIGHT*0.5+BOTTOM_BORDER),
					1.0f, theGlobal->theMap->mapOffset_x, theGlobal->theMap->mapOffset_y);

	//Check Collision to toggle effect
	theGlobal->CheckCollision(Pos, theGlobal->theMap, 
					theGlobal->theMap->mapOffset_x, theGlobal->theMap->mapOffset_y);

	//Determine Player Direction
	Vector3D playerDir;

	//Player is Jumping
	/*
	if (jump)
	{
		//++y pos
		pos.y += PLAYER_MOVEMENT_SPEED * CTimer::getInstance()->getDelta();
		CInputSystem::getInstance()->stopMovement = true;

		//Reset Jump
		if (playerJumpSprite->CurSubImage == PLAYER_JUMP_SUB-1)
			jump = CInputSystem::getInstance()->stopMovement = false;
	}
	*/
	//Check Collision of the player before moving Up
	if ((theGlobal->myKeys['w'] || theGlobal->myKeys['W']))
	{
		//Alter Player Direction
		playerDir.y = 1;
		playerSprite->changeVariation(0);

		//Do not allow movement when stopMovement is true
		if (!theGlobal->myKeys['d'] && !theGlobal->myKeys['D']  && 
			!theGlobal->myKeys['a'] && !theGlobal->myKeys['A'])
		{
			//Check if Collision is detected
			if (!theGlobal->Collided(Pos-Vector3D(0,5,0), true, false, false, false, 
				theGlobal->theMap,theGlobal->theMap->mapOffset_x, theGlobal->theMap->mapOffset_y)
				&& !LR)
			{
				moveMeUpDown(true, CGameTime::GetDelta());
				bMoving = true;
			}
		}
	}

	//Check Collision of the player before moving down
	if ((theGlobal->myKeys['s'] || theGlobal->myKeys['S']))
	{
		//Alter Player Direction
		playerDir.y = -1;
		playerSprite->changeVariation(3);

		//Do not allow movement when stopMovement is true
		if (!stopMovement)
		{
			//Check if Collision is detected
			if (!theGlobal->Collided(Pos+Vector3D(0,5,0), false, true, false, false, 
				theGlobal->theMap, theGlobal->theMap->mapOffset_x,theGlobal->theMap->mapOffset_y)
				&& !LR)
			{
				moveMeUpDown(false, CGameTime::GetDelta());
				bMoving = true;
			}
		}
	}

	//Check Collision of the hero before moving left
	Vector3D posL; //Fixes the Collision 
	posL.Set(Pos.x-7, Pos.y); //Buffer of 7

	//Move Left
	if ((theGlobal->myKeys['a'] || theGlobal->myKeys['A']))
	{
		//Alter Player Direction
		playerDir.x = -1;
		playerSprite->changeVariation(2);

		//Do not allow movement when stopMovement is true
		//if (!CInputSystem::getInstance()->stopMovement)
		{
			//Check if Collision is detected
			if (!theGlobal->Collided(posL, false, false, true, false, 
				theGlobal->theMap, theGlobal->theMap->mapOffset_x, theGlobal->theMap->mapOffset_y))
			{
				moveMeLeftRight(true, CGameTime::GetDelta());
				//bMoving = true;
			}
		}
	}

	//Check Collision of the hero before moving right
	Vector3D posR; //Fixes the Collision 
	posR.Set(Pos.x+7, Pos.y); //Buffer of 7

	//Move Right
	if ((theGlobal->myKeys['d'] || theGlobal->myKeys['D']))
	{
		cout << "lol" << endl;
		//Alter Player Direction
		playerDir.x = 1;
		playerSprite->changeVariation(1);

		//Do not allow movement when stopMovement is true
		if (!stopMovement)
		{
			//Check if Collision is detected
			if (!theGlobal->Collided(posR, false, false, false, true, 
				theGlobal->theMap, theGlobal->theMap->mapOffset_x, theGlobal->theMap->mapOffset_y))
			{
				moveMeLeftRight(false, CGameTime::GetDelta());
				bMoving = true;
			}
		}
	}

	//Check if the player is standing still
	if (!theGlobal->myKeys['w'] && !theGlobal->myKeys['W'] &&
		!theGlobal->myKeys['a'] && !theGlobal->myKeys['A'] &&
		!theGlobal->myKeys['s'] && !theGlobal->myKeys['S'] &&
		!theGlobal->myKeys['d'] && !theGlobal->myKeys['D'])
		bMoving = false;

	//Toggle UD to False if player is not moving UD
	if (!theGlobal->myKeys['w'] && !theGlobal->myKeys['W'] &&
		!theGlobal->myKeys['s'] && !theGlobal->myKeys['S'])
		UD = false;

	//Toggle LR to False if player is not moving LR
	if (!theGlobal->myKeys['a'] && !theGlobal->myKeys['A'] &&
		!theGlobal->myKeys['d'] && !theGlobal->myKeys['D'])
		LR = false;

	//Update Sprite
	if (!bMoving)
	{
		playerSprite->changeSubImage((int)0);
		playerSprite->changeStop(true);
	}

	//Set Player Direction
	if (playerDir.GetMagnitude() != 0)
		Dir = playerDir;
}



bool CPlayer::Update(void){
	keyboardUpdate();
	return true;

}
	
void CPlayer::Render(){
	if (!jump)
	{
		//Player Sprite
		if (active)
		{
			playerSprite->Update();
			glPushMatrix();
				glTranslatef((float)(Pos.x+TILE_SIZE*0.5), (float)(Pos.y+TILE_SIZE*0.5), 0);
				playerSprite->render(PlayerTexture[0]);
			glPopMatrix();
		}

		//Ghost Sprite
		else
		{
			ghostSprite->Update();
			glPushMatrix();
				glTranslatef((float)(Pos.x+TILE_SIZE*0.5-10), (float)(Pos.y+TILE_SIZE*0.5), 0);
				ghostSprite->render(PlayerTexture[2]);
			glPopMatrix();
		}
	}

	//Jump Sprite
	else
	{
		playerJumpSprite->Update();
		glPushMatrix();
			glTranslatef((float)(Pos.x+TILE_SIZE*0.5), (float)(Pos.y+TILE_SIZE*0.1), 0);
			playerJumpSprite->render(PlayerTexture[1]);
		glPopMatrix();
	}
}

void CPlayer::SetItem(ITEM_ID item_id , int SetItem){

}

int CPlayer::GetItem(ITEM_ID item_id){
	return 1;
}

//Constrain the position of the Player to within the border
void CPlayer::ConstrainPlayer(const int leftBorder, const int rightBorder, 
							  const int topBorder, const int bottomBorder, 
							  float timeDiff,
							  int& mapOffset_x, int& mapOffset_y)
{
	//Map's Scrolling Speed
	int ScrollSpeed = (int)(MAP_SCROLL_SPEED * timeDiff);

	if (Pos.x < leftBorder)
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
			Pos.x = (float)leftBorder;
		else if (Pos.x < TILE_SIZE*3)
			Pos.x = TILE_SIZE*3;
	}

	else if (Pos.x > rightBorder)
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
			Pos.x = (float)rightBorder;
		else if (Pos.x > RESOLUTION_WIDTH-TILE_SIZE*11)
			Pos.x = RESOLUTION_WIDTH-TILE_SIZE*11;
	}

	if (Pos.y < topBorder)
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
			Pos.y = (float)topBorder;
		else if (Pos.y < TILE_SIZE*4)
			Pos.y = TILE_SIZE*4;
	}

	else if (Pos.y > bottomBorder)
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
			Pos.y = (float)bottomBorder;
		else if (Pos.y > RESOLUTION_HEIGHT*2.15-TILE_SIZE*3)
			Pos.y = RESOLUTION_HEIGHT*2.15-TILE_SIZE*3;
	}
}


//Up & Down Movement
void CPlayer::moveMeUpDown(bool mode, float timeDiff)
{
	UD = true;

	//Up
	if (mode)
	{
		Pos.y = ((float)(Pos.y-(PLAYER_MOVEMENT_SPEED * timeDiff)));
		playerSprite->changeStop(false);
		playerSprite->changeVariation(0);
	}

	//Down
	else
	{
		Pos.y = ((float)(Pos.y+(PLAYER_MOVEMENT_SPEED * timeDiff * 1.15)));
		playerSprite->changeStop(false);
		playerSprite->changeVariation(3);
	}
}

//Left & Right Movement
void CPlayer::moveMeLeftRight(bool mode, float timeDiff)
{
	LR = true;

	//Left
	if (mode)
	{
		//bLeft = true;
		//bRight = false;

		Pos.x = ((float)(Pos.x-(PLAYER_MOVEMENT_SPEED * timeDiff)));
		playerSprite->changeStop(false);
		playerSprite->changeVariation(2);
	}

	//Right
	else
	{
		//bLeft = false;
		//bRight = true;

		Pos.x = ((float)(Pos.x+(PLAYER_MOVEMENT_SPEED * timeDiff * 1.15)));
		playerSprite->changeStop(false);
		playerSprite->changeVariation(1);
	}
}