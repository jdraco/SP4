#include "Weapon.h"
#include <fstream>

using namespace std;

CWeapon::CWeapon(void)
{
	theGlobal = CGlobal::getInstance();
}
CWeapon::~CWeapon(void)
{
}
// Initialise this class instance
void CWeapon::Init(void)
{
	state = "Melee";
	m_iTileSize = TILE_SIZE;
	Pos = Vector3D(200,310,0);
	facingup = false;
	facingdown = true; 
	weapAnimationCounter = 0;
	weapAnimationInvert = false;
	//HP = 100;
	attack = false;
	currEquipped = "NIL";
	currEqAmmo = 0;
	weapManager = new CweaponManager();
	weapManager->InitDB();
	cooldown = 0;
}
/****************************************************************************************************
Draw the weap
****************************************************************************************************/
void CWeapon::Renderweap(void) {

	if (attack == false)
	{
		if (GetAnimationCounter() != 1)
			SetAnimationCounter(1);
	}

	glPushMatrix();
	if (weapAnimationInvert == true)
	glTranslatef(Pos.x,Pos.y+m_iTileSize/2, 0);
	else
	glTranslatef(Pos.x+m_iTileSize/2,Pos.y+m_iTileSize/2, 0);
	glEnable( GL_TEXTURE_2D );
	glEnable( GL_BLEND );
	//glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture( GL_TEXTURE_2D, weapManager->getWeapTex(currEquipped).texID );
	glBegin(GL_QUADS);
	if (weapAnimationInvert == true)
	{
		glTexCoord2f(1,1); glVertex2f(0,0);
		glTexCoord2f(1,0); glVertex2f(0,m_iTileSize/2);
		glTexCoord2f(0,0); 
		glVertex2f(m_iTileSize/2,m_iTileSize/2);
		glTexCoord2f(0,1); 
		glVertex2f(m_iTileSize/2,0);
	}
	else
	{
		glTexCoord2f(0,1); glVertex2f(0,0);
		glTexCoord2f(0,0); glVertex2f(0,m_iTileSize/2);
		glTexCoord2f(1,0); 
		glVertex2f(m_iTileSize/2,m_iTileSize/2);
		glTexCoord2f(1,1); 
		glVertex2f(m_iTileSize/2,0);
	}
	glEnd();
	glDisable( GL_BLEND );
	glDisable( GL_TEXTURE_2D );
	glPopMatrix();

}

void CWeapon::Update(void) 
{
	for(int i = 0; i < (int)ListOfBullets.size(); i++)
	{
		ListOfBullets[i]->Render();
		if(!ListOfBullets[i]->Update())
		{
			ListOfBullets.erase(ListOfBullets.begin()+i);
		}
		else if(theGlobal->Collided(ListOfBullets[i]->GetPos(), false, true, false, false, 
				theGlobal->theMap, theGlobal->theMap->mapOffset_x,theGlobal->theMap->mapOffset_y))
		{
			ListOfBullets.erase(ListOfBullets.begin()+i);
		}
		/*for(int j = 0; j < (int)ListOfEnemies.size(); i++)
		{
			if(bullet pos * tilesize is in range of enemy * tilesize)
			{
				ListOfBullets.erase(ListOfBullets.begin()+i);
				if(enemy hp > 0)
				{ 
					enemy->hp = damageManager(enemy->hp, enemy->Mresist, enemy->Rresist, currEquipped)
				}
				if(enemy hp <= 0)
				{
					ListOfEnemies.erase(ListOfEnemies.begin()+j);
				}
			}
		}*/
	}
	if(cooldown < 5/weapManager->getWeapROF(currEquipped))
		cooldown+=0.01;
}
// Set position x of the player
void CWeapon::SetPos_x(int pos_x)
{
	Pos.x = pos_x;
}
// Set position y of the player
void CWeapon::SetPos_y(int pos_y)
{
	Pos.y = pos_y;
}

// Get position x of the player
int CWeapon::GetPos_x(void)
{
	return Pos.x;
}
// Get position y of the player
int CWeapon::GetPos_y(void)
{
	return Pos.y;
}

// Set Animation Invert status of the player
void CWeapon::SetAnimationInvert(bool weapAnimationInvert)
{
	this->weapAnimationInvert = weapAnimationInvert;
}


// Get Animation Invert status of the player
bool CWeapon::GetAnimationInvert(void)
{
	return weapAnimationInvert;
}
// Set Animation Counter of the player
void CWeapon::SetAnimationCounter(int weapAnimationCounter)
{
	int time = glutGet(GLUT_ELAPSED_TIME);
	static int ctime = glutGet(GLUT_ELAPSED_TIME);
	if (time - ctime > 50)
	{
		this->weapAnimationCounter = weapAnimationCounter;
		ctime = time;
	}
}
bool CWeapon::Attack(Vector3D dir,Vector3D pos)
{
	if(currEqAmmo <= 0)
		return false;
	if(cooldown < 5/weapManager->getWeapROF(currEquipped))
		return false;
	if(weapManager->getWeapType(currEquipped) == "Ranged")
	{
		Bullet *tempBullet = new Bullet();
		tempBullet->name = currEquipped;
		tempBullet->SetDir(dir);
		tempBullet->SetPos(pos);
		ListOfBullets.push_back(tempBullet);
		currEqAmmo-=1;
		cooldown = 0;
		return true;
	}
	if(weapManager->getWeapType(currEquipped) == "Melee")
	{
		Bullet *tempMelee = new Bullet(true);
		tempMelee->name = currEquipped;
		tempMelee->SetDir(dir);
		tempMelee->SetPos(pos);
		ListOfBullets.push_back(tempMelee);
		cooldown = 0;
		return true;
	}
}
// Get Animation Counter of the player
int CWeapon::GetAnimationCounter(void)
{
		return weapAnimationCounter;
}

string CWeapon::getState()
{
	return state;
}

void CWeapon::setState(string state)
{
	this->state = state;
}


string CWeapon::getCurrEquipped()
{
	return currEquipped;
}
void CWeapon::setCurrEquipped(string weap)
{
	currEquipped = weap;
}
int CWeapon::getCurrAmmo()
{
	return currEqAmmo;
}
void CWeapon::setCurrAmmo(int ammo)
{
	currEqAmmo = ammo;
}
Bullet* CWeapon::GetBullet(int bullet)
{
	return ListOfBullets[bullet];
}

int CWeapon::GetBulletListSize()
{
	return (int)ListOfBullets.size();
}

bool CWeapon::checkProjectileCollision(Vector3D Target)
{
	for(unsigned i = 0; i < GetBulletListSize(); i++)
	{
		if ( (Target - GetBullet(i)->GetPos()).GetMagnitude2D() < 25)
		{
			if(GetBullet(i)->range > 100)
				delete GetBullet(i);
			return true;
		}
	}
	return false;
}