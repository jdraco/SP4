#include "Guard.h"


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
	CurrentState = IDLE;
	//Pos.Set(500, 400 ,0);
	Scale.Set(20, 20, 1);
	Vel.Set(5,5,1);
	Color.Set(1.0f, 1.0f, 1.0f);
	active = true;
	/*
	for(unsigned i = 0; i < CGoodies::theArrayOfGoodies.size(); ++i)
	{
		CGoodies *go = CGoodies::theArrayOfGoodies[i];
		if(go->Object == PLAYER && go->GetItem(TEAMNO) != TeamNo)
		{
			SetTarget(go);
		}
	}
	*/
	//Health and armor
	Health.max = 100;
	Health.current = Health.max;
	//Health.no = 4;

	//Team
	//TeamNo = 1;


	
	LoadTGA(&Texture[0], "Texture/player.tga");
}

bool CGuard::Update(void)
{
	//Direction toward target
	/*
	Dir = ( Pos - Target->GetPos() ) * 0.1 ;
	Dir.normalizeVector3D();
	*/
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

	IndividualAction();
	//TeamAction();

	//Act on the current state
	switch (CurrentState)
	{
		case ATTACK:
		{
			/*
			if(Target->active == false){
				PreviousTarget = Target;
				for(unsigned i = 0; i < CGoodies::theArrayOfGoodies.size(); ++i)
				{
					CGoodies *go = CGoodies::theArrayOfGoodies[i];
					if(go->GetItem(TEAMNO) != TeamNo && go->active != false)
					{
							SetTarget(go);
					}
				}
			}

			Vector3D targetdiff;
			
			targetdiff.Set(Target->GetPos().x - Pos.x , Target->GetPos().y - Pos.y ,Target->GetPos().z - Pos.z);
			RotateAngle = -(atan2(targetdiff.x,targetdiff.z)+90)* 180 / PI;

			AttackTime.Update();

			if ( AttackTime.GetCurrent() < 1){
				AttackTime.SetCurrent();
				AttackTime.SetTotalTime(3);

				Target->setCurrentHealth( Target->getHealth().current - 20); //damage to enemy
				Target->setCurrentArmor(Target->getArmor().current - 4);
			}
		}
		*/
		}
			break;

		case CHASE:
		{
			/*
			if (Target->GetPos().x > this->Pos.x)
			{
				this->Pos.x += speed;
			}
			else
			{
				this->Pos.x += -speed;
			}

			if (Target->GetPos().y > this->Pos.y)
			{
				this->Pos.y += speed;
			}
			else
			{
				this->Pos.y += -speed;
			}
			*/
		}
			break;

		case MOVELEFT:
		{
			this->Pos.x += -moveSpeed;
		}
			break;

		case MOVERIGHT:
		{
			this->Pos.x += moveSpeed;
		}
			break;

		case MOVEUP:
		{
			this->Pos.y += -moveSpeed;
		}
			break;

		case MOVEDOWN:
		{
			this->Pos.y += moveSpeed;
		}
			break;
		
		case RETREAT:
		{
			Pos = Pos - Vel * Dir * -0.1; //run
			CurrentState = IDLE;			//reset to idle if not retreating alr
		}
		break;
		
		case IDLE:
		{
			
		}
		break;
	}

	//cout << CurrentState << endl;
	
	return true;
}

void CGuard::IndividualAction(){


	//State making

	//Chasing/attacking for target
	/*
	if(CurrentState != RETREAT){
		for(unsigned i = 0; i < CGoodies::theArrayOfGoodies.size(); ++i)
			{
				CGoodies *go = CGoodies::theArrayOfGoodies[i];
				if(go->GetItem(TEAMNO) != TeamNo && ( Pos - go->GetPos() ).GetMagnitude2D() < 150 )
				{
						SetTarget(go);

						if((Target->GetPos()-this->Pos).GetMagnitude2D() < chasesight)
						{
							CurrentState = CHASE;
						}
	
						if((Target->GetPos()-this->Pos).GetMagnitude2D() < attacksight)
						{
							CurrentState = ATTACK;

						}
				}
			}
	}
	*/
	//else
	//{

		int chance = (int)theGlobal->RG.getImmediateResult(1, 100);
		IdleTime.Update();

		if (CurrentState == IDLE && IdleTime.GetCurrent() < 1)
		{
			IdleTime.SetCurrent();
			IdleTime.SetTotalTime(1);
			
			if (chance > 0 && chance < 20)
			{
				CurrentState = MOVERIGHT;
			}
			else if (chance > 19 && chance < 40)
			{
				CurrentState = MOVELEFT;
			}
			else if (chance > 39 && chance < 60)
			{
				CurrentState = MOVEUP;
			}
			else if (chance > 59 && chance < 80)
			{
				CurrentState = MOVEDOWN;
			}
			else
			{
				CurrentState = IDLE;
			}
		}
		else if (CurrentState == MOVELEFT || CurrentState == MOVERIGHT || CurrentState == MOVEUP 
			|| CurrentState == MOVEDOWN || CurrentState == ATTACK || CurrentState == CHASE)
		{
			if (rand() % 100 < 2)
			{
				CurrentState = IDLE;

			}
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
	if (isMoving == false)
	{
		if (GetAnimationCounter() != 1)
			SetAnimationCounter(1);
	}
	//cout << Pos.x << " , " << Pos.y << endl; 
	
	Info();

	glPushMatrix();
	glTranslatef(Pos.x, Pos.y, 1);
	glEnable( GL_TEXTURE_2D );
	glEnable( GL_BLEND );
	//glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBindTexture( GL_TEXTURE_2D, Texture[0].texID );
	glBegin(GL_QUADS);
	if (heroAnimationInvert == true)
	{
		glTexCoord2f(0.25 * heroAnimationCounter,1); 
		glVertex2f(0,0);
		glTexCoord2f(0.25 * heroAnimationCounter,0); 
		glVertex2f(0,m_iTileSize);
		glTexCoord2f(0.25 * heroAnimationCounter + 0.25,0); 
		glVertex2f(m_iTileSize,m_iTileSize);
		glTexCoord2f(0.25 * heroAnimationCounter + 0.25,1); 
		glVertex2f(m_iTileSize,0);
	}
	else
	{
		glTexCoord2f(0.25 * heroAnimationCounter + 0.25,1); 
		glVertex2f(0,0);
		glTexCoord2f(0.25 * heroAnimationCounter + 0.25,0); 
		glVertex2f(0,m_iTileSize);
		glTexCoord2f(0.25 * heroAnimationCounter,0); 
		glVertex2f(m_iTileSize,m_iTileSize);
		glTexCoord2f(0.25 * heroAnimationCounter,1); 
		glVertex2f(m_iTileSize,0);
	}
	glEnd();
	glDisable( GL_BLEND );
	glDisable( GL_TEXTURE_2D );
	glPopMatrix();

	glColor3f( 0.0f, 0.0f, 0.0f);
	

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

		case MOVELEFT:
		{
			tempState = "MOVELEFT STATE";
			//printw(Pos.x,Pos.y+repos,0,"MOVELEFT STATE");
		}
			break;

		case MOVERIGHT:
		{
			tempState = "MOVERIGHT STATE";
			//printw(Pos.x-30,Pos.y+repos,0,"MOVERIGHT STATE");
		}
			break;

		case MOVEUP:
		{
			tempState = "MOVEUP STATE";
			//printw(Pos.x-30,Pos.y+repos,0,"MOVEUP STATE");
		}
			break;

		case MOVEDOWN:
		{
			tempState = "MOVEDOWN STATE";
			//printw(Pos.x-30,Pos.y+repos,0,"MOVEDOWN STATE");
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