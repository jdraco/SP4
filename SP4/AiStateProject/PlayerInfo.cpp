#include "PlayerInfo.h"
#include <fstream>

using namespace std;

CPlayerInfo* CPlayerInfo::_instance = 0;

CPlayerInfo*CPlayerInfo::getInstance()
{
	if (_instance == 0)
	{
		_instance = new CPlayerInfo;
	}
	return _instance;
}

CPlayerInfo::CPlayerInfo(void)
{
	theGlobal = CGlobal::getInstance();
}
CPlayerInfo::~CPlayerInfo(void)
{
}
// Initialise this class instance
void CPlayerInfo::Init(void)
{
	state = "default";
	m_iTileSize = TILE_SIZE;
	
	if( !LoadTGA( &(Texture[ 0 ]), "Texture/Tiles/James.tga"))
		cout << "No hero texture" << endl;
	if( !LoadTGA( &(Texture[ 1 ]), "Texture/Tiles/James.tga"))
		cout << "No hero texture" << endl;
	if( !LoadTGA( &(Texture[ 2 ]), "Texture/Tiles/James.tga"))
		cout << "No hero texture" << endl;
	if( !LoadTGA( &(Texture[ 3 ]), "Texture/Tiles/James.tga"))
		cout << "No hero texture" << endl;
	Pos = Vector3D(200,310,0);
	//hero_x = 200;
	//hero_y = 310;
	jumpspeed = 0;
	facingup = false;
	facingdown = true;
	isMoving = false;
	heroAnimationCounter = 0;
	heroAnimationInvert = false;
	isShooting = false;

	damage = 1;
	skillLevel = 1;
	debt = 0;

	HP = 100;

	weapon = new CWeapon();
	//weapen = CWeapon::GetInstance();
	weapon->Init();

}
/****************************************************************************************************
Draw the hero
****************************************************************************************************/
void CPlayerInfo::Render(void) {

	if (isMoving == false)
	{
		if (GetAnimationCounter() != 1)
			SetAnimationCounter(1);
	}
	//cout << Pos.x << " , " << Pos.y << endl; 

	glPushMatrix();
	glTranslatef(Pos.x, Pos.y, 1);
	glEnable( GL_TEXTURE_2D );
	glEnable( GL_BLEND );
	//glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	if (facingup == false && facingdown == false)
		glBindTexture( GL_TEXTURE_2D, Texture[1].texID );
	else if (facingup == true && facingdown == false)
		glBindTexture( GL_TEXTURE_2D, Texture[2].texID );
	else if (facingup == false && facingdown == true)
		glBindTexture( GL_TEXTURE_2D, Texture[3].texID );
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
	weapon->Renderweap();//sss
}


// Set Animation Invert status of the player
void CPlayerInfo::SetAnimationInvert(bool heroAnimationInvert)
{
	this->heroAnimationInvert = heroAnimationInvert;
}
// Get Animation Invert status of the player
bool CPlayerInfo::GetAnimationInvert(void)
{
	return heroAnimationInvert;
}
// Set Animation Counter of the player
void CPlayerInfo::SetAnimationCounter(int heroAnimationCounter)
{
	int time = glutGet(GLUT_ELAPSED_TIME);
	static int ctime = glutGet(GLUT_ELAPSED_TIME);
	if (time - ctime > 50)
	{
		this->heroAnimationCounter = heroAnimationCounter;
		ctime = time;
	}
}
// Get Animation Counter of the player
int CPlayerInfo::GetAnimationCounter(void)
{
		return heroAnimationCounter;
}

void CPlayerInfo::keyboardUpdate()
{
	//Delta Time
	float dt = CGameTime::GetDelta();


	//Constrain Hero to middle of screen (unless he reaches the border)
	/*
	ConstrainHero((const int)(MAP_SCREEN_WIDTH*0.5+LEFT_BORDER), (const int)(MAP_SCREEN_WIDTH*0.5+LEFT_BORDER), 
					(const int)(MAP_SCREEN_HEIGHT*0.5+BOTTOM_BORDER), (const int)(MAP_SCREEN_HEIGHT*0.5+BOTTOM_BORDER),
					1.0f, theGlobal->theMap->mapOffset_x, theGlobal->theMap->mapOffset_y, 
					SCREEN_WIDTH, MAP_SCREEN_WIDTH, SCREEN_HEIGHT, MAP_SCREEN_HEIGHT);
					*/
	/*
	ConstrainPlayer((const int)(MAP_SCREEN_WIDTH*0.5+LEFT_BORDER), (const int)(MAP_SCREEN_WIDTH*0.5+LEFT_BORDER), 
					(const int)(MAP_SCREEN_HEIGHT*0.5+BOTTOM_BORDER), (const int)(MAP_SCREEN_HEIGHT*0.5+BOTTOM_BORDER),
					1.0f, theGlobal->theMap->mapOffset_x, theGlobal->theMap->mapOffset_y);
	*/

	//Vector3D Pos = Vector3D(hero_x,hero_y,0);
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
		facingup = true;
		facingdown = false;

		SetAnimationCounter( GetAnimationCounter() - 1);
		if (GetAnimationCounter()==0)
			SetAnimationCounter( 3 );

		//Do not allow movement when stopMovement is true
		if (!theGlobal->myKeys['d'] && !theGlobal->myKeys['D']  && 
			!theGlobal->myKeys['a'] && !theGlobal->myKeys['A'])
		{
			//Check if Collision is detected
			if (!theGlobal->Collided(Pos-Vector3D(0,5,0), true, false, false, false, 
				theGlobal->theMap,theGlobal->theMap->mapOffset_x, theGlobal->theMap->mapOffset_y)
				&& !LR)
			{
				Pos.y =  Pos.y - (int) (5.0f *  1.0f) ;
				bMoving = true;
			}
		}
	}

	//Check Collision of the player before moving down
	if ((theGlobal->myKeys['s'] || theGlobal->myKeys['S']))
	{
		//Alter Player Direction
		playerDir.y = -1;
		facingup = false;
		facingdown = true;

		SetAnimationCounter( GetAnimationCounter() + 1);
		if (GetAnimationCounter()> 3)
			SetAnimationCounter( 0 );

		//Do not allow movement when stopMovement is true
		//if (!stopMovement)
		//{
			//Check if Collision is detected
			if (!theGlobal->Collided(Pos+Vector3D(0,5,0), false, true, false, false, 
				theGlobal->theMap, theGlobal->theMap->mapOffset_x,theGlobal->theMap->mapOffset_y)
				&& !LR)
			{
				Pos.y = Pos.y + (int) (5.0f *  1.0f) ;
				bMoving = true;
			}
		//}
	}

	//Check Collision of the hero before moving left
	Vector3D posL; //Fixes the Collision 
	posL.Set(Pos.x-7, Pos.y); //Buffer of 7

	//Move Left
	if ((theGlobal->myKeys['a'] || theGlobal->myKeys['A']))
	{
		//Alter Player Direction
		playerDir.x = -1;
		SetAnimationInvert( true );
		facingup = false;
		facingdown = false;
		SetAnimationCounter( GetAnimationCounter() - 1);
		if (GetAnimationCounter()==0)
			SetAnimationCounter( 3 );

		//Do not allow movement when stopMovement is true
		//if (!CInputSystem::getInstance()->stopMovement)
		//{
			//Check if Collision is detected
			if (!theGlobal->Collided(posL, false, false, true, false, 
				theGlobal->theMap, theGlobal->theMap->mapOffset_x, theGlobal->theMap->mapOffset_y))
			{
				SetPos_x( GetPos().x - (int) (5.0f *  1.0f) );
				bMoving = true;
			}
		//}
			//Check Collision of the hero before moving right

	}

			Vector3D posR; //Fixes the Collision 
		posR.Set(Pos.x+7, Pos.y); //Buffer of 7

	//Move Right
	if ((theGlobal->myKeys['d'] || theGlobal->myKeys['D']))
	{
		cout << "lol" << endl;
		//Alter Player Direction
		playerDir.x = 1;
		SetAnimationInvert( false );
		facingup = false;
		facingdown = false;
		SetAnimationCounter( GetAnimationCounter() + 1);
		if (GetAnimationCounter()>3)
			SetAnimationCounter( 0 );

		//Do not allow movement when stopMovement is true
		//if (!stopMovement)
		//{
			//Check if Collision is detected
			if (!theGlobal->Collided(posR, false, false, false, true, 
				theGlobal->theMap, theGlobal->theMap->mapOffset_x, theGlobal->theMap->mapOffset_y))
			{
				SetPos_x( GetPos().x + (int) (5.0f *  1.0f) );
				bMoving = true;
			}
		//}
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
		SetAnimationCounter(0);
	}

	//Set Player Direction
	//if (playerDir.GetMagnitude() != 0)
		//Dir = playerDir;
}



bool CPlayerInfo::Update(){
	keyboardUpdate();
	return true;

}
	
void CPlayerInfo::load()
{	
	ifstream read;
	int data[9];

	read.open ("SaveData.txt", fstream::in | fstream::app);
	for (int i = 0; i < 9; i++)
	{
		read >> data[i];
	}

	Pos.x = data[0];
	Pos.y = data[1];
}
void CPlayerInfo::save()
{
	ofstream outFile;

	outFile.open("SaveData.txt");

	outFile << hero_x << endl 
		<< hero_y << endl;
	cout << endl;

	outFile.close();
}

int CPlayerInfo::getHP(){
	return HP;
}
void CPlayerInfo::setHP(int h){
	HP = h;

	if (HP > 100)
		HP = 100;
	else if (HP < 0)
		HP = 0;
}
string CPlayerInfo::getState()
{
	return state;
}

void CPlayerInfo::setState(string state)
{
	this->state = state;
}

Inventory CPlayerInfo::getInventory(int slot)
{
	Inventory temp = Inventory(inventory[slot],inventAmt[slot]);

	return temp;
}
void CPlayerInfo::setInventory(Inventory set, int slot)
{
	inventory[slot] = set.inventory;
	inventAmt[slot] = set.amount;
}

Inventory* CPlayerInfo::getWInventory()
{
	Inventory temp[INVENTORY_SIZE];
	for(unsigned i = 0; i < INVENTORY_SIZE; i++)
	{
		temp[i] = Inventory(inventory[i],inventAmt[i]);
	}
	return temp;
}

void CPlayerInfo::setWInventory(Inventory set[INVENTORY_SIZE])
{
	for(unsigned i = 0; i < INVENTORY_SIZE; i++)
	{
		inventory[i] = set[i].inventory;
		inventAmt[i] = set[i].amount;
	}
}

string CPlayerInfo::getCurrEquipped()
{
	return weapon->getCurrEquipped();
}
void CPlayerInfo::setCurrEquipped(string weap)
{
	weapon->setCurrEquipped(weap);
}
int CPlayerInfo::getCurrAmmo()
{
	return weapon->getCurrAmmo();
}
void CPlayerInfo::setCurrAmmo(int ammo)
{
	weapon->setCurrAmmo(ammo);
}

