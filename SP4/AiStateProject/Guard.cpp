#include "Guard.h"
#include "PlayerInfo.h"

CGuard::CGuard(void)
{
	isMoving = false;
}


CGuard::~CGuard(void)
{
}

void CGuard::SelfInit(void)
{

	//RotateAngle = 0;
	//starting state
	CurrentState = PATROL;

	//Basic Setup
	Scale.Set(1.0f, 1.0f, 1.0f);
	Vel.Set(5.0f,5.0f,0.0f);
	Dir.Set(1.0f,0.0f,0.0f);
	Color.Set(1.0f, 1.0f, 1.0f);
	active = true;
	NeedRender = true;
	
	//Health and Damage
	Health.max = 100;
	Health.current = Health.max;
	Damage = 10;
	//Health.no = 4;

	//Team
	//TeamNo = 1;
	GuardSprite = new CSprite;
	GuardSprite->ImageInit(4, 1, 100);

	if( !LoadTGA( &(Texture[ 0 ]), "Texture/Tiles/Japan1.tga"))
		cout << "No hero texture" << endl;
	if( !LoadTGA( &(Texture[ 1 ]), "Texture/Tiles/Japan1.tga"))
		cout << "No hero texture" << endl;
	if( !LoadTGA( &(Texture[ 2 ]), "Texture/Tiles/Japan1up.tga"))
		cout << "No hero texture" << endl;
	if( !LoadTGA( &(Texture[ 3 ]), "Texture/Tiles/Japan1down.tga"))
		cout << "No hero texture" << endl;
}

bool CGuard::Update(void)
{
	
	float dt = CGameTime::GetDelta();
	//cout << dt << endl;

	//decide whether to render or not
	if (Pos.x < LEFT_BORDER || Pos.x > RESOLUTION_WIDTH-LEFT_BORDER-TILE_SIZE*3 || 
		Pos.y < BOTTOM_BORDER || Pos.y > RESOLUTION_HEIGHT-BOTTOM_BORDER+TILE_SIZE)
	{
		NeedRender = false;
	}
	else
	{
		NeedRender = true;
	}

	//health system
	if (Health.current < 0)
	{
		if(Health.no > 0)
		{
			Health.current = Health.max;
			Health.no -= 1;
		}
		else
		{
			active = false;
		}
	}

	//individual
	IndividualAction();

	
	//TeamAction();

	//Act on the current state
	switch (CurrentState) //Switch to decide dir
	{
		case ATTACK:
		{
			Dir = Vector3D();		//stop movement
			if(Player->getHealth().current > 0)
				Player->setCurrentHealth(Player->getHealth().current - Damage);
			//attack
		}
			break;

		case CHASE:
		{
			Dir = Pos - Player->GetPos();
		}
			break;

		case PATROL:
		{
			WayPointDir(); //follow way point
		}
		break;

		case RETREAT:
		{
			Dir = (Pos - Player->GetPos()).negative(); //run away
			//only needed if using msgboard
			//CurrentState = IDLE;			//reset to idle if not retreating alr
		}
		break;
		
		case COLLIDED_D://THIS IS ACTUALLY UP
		{
			float distbetween = (Pos - Player->GetPos()).GetMagnitude();
			if(PrevState == CHASE || distbetween < 200)
			{
				Dir = Pos - Player->GetPos();
				if(Dir.y > 0)
				Dir.y = 0;
			}
			else if(PrevState == PATROL)
			{
				WayPointDir();
				if(Dir.y > 0)
				Dir.y = 0;
			}
			else if(PrevState == RETREAT)
			{
				Dir = (Pos - Player->GetPos()).negative();
				if(Dir.y > 0)
				Dir.y = 0;
			}
			else
			{
				CurrentState = PATROL;
			}
			if (!theGlobal->Collided(Pos, false, true, false, false, 
			theGlobal->theMap, theGlobal->theMap->mapOffset_x,theGlobal->theMap->mapOffset_y))
			{
				CurrentState = PrevState;
			}
		}
		break;
		case COLLIDED_U://THIS IS ACTUALLY DOWN
		{
			float distbetween = (Pos - Player->GetPos()).GetMagnitude();
			
			if(PrevState == CHASE || distbetween < 200)
			{
				Dir = Pos - Player->GetPos();
				if(Dir.y < 0)
				Dir.y = 0;
			}
			else if(PrevState == PATROL)
			{
				WayPointDir();
				if(Dir.y < 0)
				Dir.y = 0;
			}
			else if(PrevState == RETREAT)
			{
				Dir = (Pos - Player->GetPos()).negative();
				if(Dir.y < 0)
				Dir.y = 0;
			}
			else
			{
				CurrentState = PATROL;
			}
			if (!theGlobal->Collided(Pos, false, true, false, false, 
			theGlobal->theMap, theGlobal->theMap->mapOffset_x,theGlobal->theMap->mapOffset_y))
			{
				CurrentState = PrevState;
			}
		}
		break;
		case COLLIDED_L:
		{
			float distbetween = (Pos - Player->GetPos()).GetMagnitude();
			if(PrevState == CHASE || distbetween < 200)
			{
				Dir = Pos - Player->GetPos();
				if(Dir.x < 0)
				Dir.x = 0;
			}
			else if(PrevState == PATROL)
			{
				WayPointDir();
				if(Dir.x < 0)
				Dir.x = 0;
			}
			else if(PrevState == RETREAT)
			{
				Dir = (Pos - Player->GetPos()).negative();
				if(Dir.x < 0)
				Dir.x = 0;
			}
			else
			{
				CurrentState = PATROL;
			}
			Vector3D posL; //Fixes the Collision 
			posL.Set(Pos.x-7, Pos.y); //Buffer of 7
			if (!theGlobal->Collided(posL, false, false, true, false, 
				theGlobal->theMap, theGlobal->theMap->mapOffset_x, theGlobal->theMap->mapOffset_y))
			{
				CurrentState = PrevState;
			}
		}
		break;
		case COLLIDED_R:
		{
			float distbetween = (Pos - Player->GetPos()).GetMagnitude();
			if(PrevState == CHASE || distbetween < 200)
			{
				Dir = Pos - Player->GetPos();
				if(Dir.x > 0)
				Dir.x = 0;
			}
			else if(PrevState == PATROL)
			{
				WayPointDir();
				if(Dir.x > 0)
				Dir.x = 0;
			}
			else if(PrevState == RETREAT)
			{
				Dir = (Pos - Player->GetPos()).negative();
				if(Dir.x > 0)
				Dir.x = 0;
			}
			else
			{
				CurrentState = PATROL;
			}
			Vector3D posR; //Fixes the Collision 
			posR.Set(Pos.x+7, Pos.y); //Buffer of 7
			if (!theGlobal->Collided(posR, false, false, false, true, 
				theGlobal->theMap, theGlobal->theMap->mapOffset_x, theGlobal->theMap->mapOffset_y))
			{
				CurrentState = PrevState;
			}
		}
		break;
		case IDLE:	
		{
			//do nothing
		}
		break;
	}
	if (theGlobal->Collided(Pos-Vector3D(0,5,0), true, false, false, false, 
		theGlobal->theMap,theGlobal->theMap->mapOffset_x, theGlobal->theMap->mapOffset_y) && CurrentState != COLLIDED_D)
	{
		//Pos.y =  Pos.y + (int) (5.0f *  1.0f) ;
		PrevState = CurrentState;
		CurrentState = COLLIDED_D;
	}
	if (theGlobal->Collided(Pos+Vector3D(0,5,0), false, true, false, false, 
		theGlobal->theMap, theGlobal->theMap->mapOffset_x,theGlobal->theMap->mapOffset_y) && CurrentState != COLLIDED_U)
	{
		//Pos.y = Pos.y - (int) (5.0f *  1.0f) ;
		PrevState = CurrentState;
		CurrentState = COLLIDED_U;
	}
	Vector3D posL; //Fixes the Collision 
	posL.Set(Pos.x-7, Pos.y); //Buffer of 7
	if (theGlobal->Collided(posL, false, false, true, false, 
		theGlobal->theMap, theGlobal->theMap->mapOffset_x, theGlobal->theMap->mapOffset_y) && CurrentState != COLLIDED_L)
	{
		//SetPos_x( GetPos().x + (int) (5.0f *  1.0f) );
		PrevState = CurrentState;
		CurrentState = COLLIDED_L;
	}
	Vector3D posR; //Fixes the Collision 
	posR.Set(Pos.x+7, Pos.y); //Buffer of 7
	if (theGlobal->Collided(posR, false, false, false, true, 
		theGlobal->theMap, theGlobal->theMap->mapOffset_x, theGlobal->theMap->mapOffset_y) && CurrentState != COLLIDED_R)
	{
		//SetPos_x( GetPos().x - (int) (5.0f *  1.0f) );
		PrevState = CurrentState;
		CurrentState = COLLIDED_R;
	}
	if(CurrentState != ATTACK)			//cause dir = 0 at attack
		Dir.normalizeVector3D();				//normalise dir before using
	Pos = Pos - Vel * Dir * dt;	//move character

	cout << CurrentState << endl;
//	cout << dt << endl;
	//cout << CurrentState << endl;
	//cout << active << endl;

	return true;
}

void CGuard::IndividualAction(){
	//can be lua-ed
	float distbetween = (Pos - Player->GetPos()).GetMagnitude();

	if ( distbetween < 50 )
	{
		CurrentState = ATTACK;
	}
	else if ( distbetween < 200 )
	{
		if (CurrentState != COLLIDED_D && CurrentState != COLLIDED_U
		&& CurrentState != COLLIDED_L && CurrentState != COLLIDED_R)
		CurrentState = CHASE;
	}
	else
	{
		//random between partrol and idle
		CurrentState = PATROL;
	}


}

/*
void CGuard::TeamAction(){
	/*
	for(unsigned i = 0; i < CGoodies::theArrayOfGoodies.size(); ++i)
	{
		CGoodies *go = CGoodies::theArrayOfGoodies[i];
	}
	
	if(Health.current < 50) // health bar below 1x
	{
		//Send help message
		CMessageBoard::MsgInfo* tempMsg = new CMessageBoard::MsgInfo;
		tempMsg->CharID = ID;
		tempMsg->message = CMessageBoard::ID_SAVEME;
		theGlobal->theMsgBoard->SetMSG( tempMsg );
	}
	/*
	if(Target->State == OBJECT_STATE::SKILLING)
	{
		//Send help message
		CMessageBoard::MsgInfo* tempMsg = new CMessageBoard::MsgInfo;
		tempMsg->CharID = ID;
		tempMsg->message = CMessageBoard::ID_RETREAT;
		theGlobal->theMsgBoard->SetMSG( tempMsg );
	}
	

	vector<CMessageBoard::MsgInfo*> MsgInfoList = theGlobal->theMsgBoard->GetMSGList();

	if( MsgInfoList.size() != 0){// check if there is message
		for(unsigned x = 0; x < MsgInfoList.size(); ++x)
		{
			CGoodies *go = NULL;
			CMessageBoard::MsgInfo* msg = MsgInfoList[x];

			if(msg->message !=  CMessageBoard::ID_NOMSG || msg->message != NULL )
				go = CGoodies::theArrayOfGoodies[msg->CharID-1]; //using the id of the sender to find him
			
			if(go){
				if (go->GetItem(TEAMNO) == TeamNo)
				{
					switch(msg->message)
					{
					case CMessageBoard::ID_NOMSG:
						{

						}
						break;
					case CMessageBoard::ID_ATTACKSTUNENEMY:
						{
							//inverse = -1;
						}
						break;
		
					case CMessageBoard::ID_PROTECTME:
						{
							//inverse = -1;
						}
						break;

					case CMessageBoard::ID_RETREAT:
						{
							//inverse = -1;
							for(unsigned i = 0; i < CGoodies::theArrayOfGoodies.size(); ++i)
							{
								CGoodies *go = CGoodies::theArrayOfGoodies[i];
								//check for boss
								if(go->Object == CGoodies::ENEMY && go->GetItem(ITEM_ID::TEAMNO) != TeamNo)
								{
									//set target as boss
									Target = go;
									break;
								}
							}


							if(Target->GetItem(CVariable::TEAMNO) != this->TeamNo)
							{
								CurrentState = RETREAT;
							}
						}
						break;
					case CMessageBoard::ID_SAVEME:
						{
							//CurrentState = RETREAT; //
			
						}
						break;
					}
				}
			}
		}
	}
}
*/
	
void CGuard::Render()
{
	DrawHealthBar(Health.current, Health.max ,  Pos.x-110 ,Pos.y-20);

	if (isMoving == false)
	{
		if (GetAnimationCounter() != 1)
			SetAnimationCounter(1);
	}

	SetAnimationCounter( GetAnimationCounter() + 1);
	if (GetAnimationCounter()> 3)
			SetAnimationCounter( 0 );
	//cout << Pos.x << " , " << Pos.y << endl; 
	
	//Info();
	if(NeedRender == true){
		glPushMatrix();
			glTranslatef((float)(Pos.x+TILE_SIZE*0.5), (float)(Pos.y+TILE_SIZE*0.5), 0);
			GuardSprite->render(Texture[0]);
		glPopMatrix();
	}

}


void CGuard::Info(){
	//DrawHealthBar(Health.current, Health.max ,  Pos.x-110 ,Pos.y-40);

	glPushMatrix();
	//glScalef(0.5,0.5,1);

	printw(1,Pos.x ,Pos.y-40 , 0 , "Health: %d", Health.no);
	//printw(1,Pos.x-35 ,Pos.y-40 , 0 , "%d." , ID);
	//printw(1,Pos.x-70 ,Pos.y-40 , 0 , "%d." , Target->GetID());

	int repos = 35;

	std::string tempState;

	switch(CurrentState)
	{		
		case ATTACK:
		{
			tempState = "ATTACK STATE";
			//printw(Pos.x-30 ,Pos.y+repos ,0,"ATTACK STATE");
			//StateTexture(Atk[0]);
		}
			break;

		case CHASE:
		{
			tempState = "CHASING STATE";
			//printw(Pos.x-30 ,Pos.y+repos ,0,"CHASING STATE");
		}
			break;

		case PATROL:
		{
			tempState = "PATROL STATE";
		}
			break;
		case IDLE:
		{
			tempState = "IDLE STATE";
			//printw(Pos.x-30,Pos.y+repos,0,"IDLE STATE");
			//StateTexture(Def[0]);
		}
			break;
		default:
		{
			tempState = "NO STATE";
		}
		break;
	}
	//printw(0,Pos.x-30,Pos.y+repos,0,"%s", tempState);

	glPopMatrix();
}

void CGuard::SetItem(ITEM_ID item_id , int SetItem)
{
	/*
	switch (item_id)
	{
		case TEAMNO	:
		{
			TeamNo = SetItem;
		}
		break;
	}
	*/
}

int CGuard::GetItem(ITEM_ID item_id)
{
	/*
	switch (item_id)
	{
		case TEAMNO	:
		{
			return TeamNo;
		}
		break;
	}
	*/
	return 0;
}

void CGuard::WayPointDir()
{
	//Vector3D Point = Vector3D(OwnPath.getCurrentPoint().getX() ,OwnPath.getCurrentPoint().getY() , OwnPath.getCurrentPoint()->getZ() );

	Vector3D DistFromPoint =  Pos - OwnPath.getCurrentPoint()  ;
		
	//Direction toward target
	Dir = DistFromPoint;
	

	if ( DistFromPoint.GetMagnitude2D() < 1 )
		OwnPath.IndexPlus();

}