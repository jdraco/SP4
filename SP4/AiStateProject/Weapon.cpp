#include "Weapon.h"
#include <fstream>

using namespace std;

CWeapon::CWeapon(void)
{
}
CWeapon::~CWeapon(void)
{
}
// Initialise this class instance
void CWeapon::Init(void)
{
	state = "default";
	m_iTileSize = TILE_SIZE;
	weap_x = 200;
	weap_y = 310; 
	facingup = false;
	facingdown = true; 
	weapAnimationCounter = 0;
	weapAnimationInvert = false;
	//HP = 100;
	attack = false;
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
	glTranslatef(weap_x, weap_y, 0);
	glEnable( GL_TEXTURE_2D );
	glEnable( GL_BLEND );
	//glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	if (facingup == false && facingdown == false)
		glBindTexture( GL_TEXTURE_2D, weapTexture[1].texID );
	else if (facingup == true && facingdown == false)
		glBindTexture( GL_TEXTURE_2D, weapTexture[2].texID );
	else if (facingup == false && facingdown == true)
		glBindTexture( GL_TEXTURE_2D, weapTexture[3].texID );
	glBegin(GL_QUADS);
	if (weapAnimationInvert == true)
	{
		glTexCoord2f(0.25 * weapAnimationCounter,1); glVertex2f(0,0);
		glTexCoord2f(0.25 * weapAnimationCounter,0); glVertex2f(0,m_iTileSize);
		glTexCoord2f(0.25 * weapAnimationCounter + 0.25,0); 
		glVertex2f(m_iTileSize,m_iTileSize);
		glTexCoord2f(0.25 * weapAnimationCounter + 0.25,1); 
		glVertex2f(m_iTileSize,0);
	}
	else
	{
		glTexCoord2f(0.25 * weapAnimationCounter + 0.25,1); glVertex2f(0,0);
		glTexCoord2f(0.25 * weapAnimationCounter + 0.25,0); 
		glVertex2f(0,m_iTileSize);
		glTexCoord2f(0.25 * weapAnimationCounter,0); 
		glVertex2f(m_iTileSize,m_iTileSize);
		glTexCoord2f(0.25 * weapAnimationCounter,1); glVertex2f(m_iTileSize,0);
	}
	glEnd();
	glDisable( GL_BLEND );
	glDisable( GL_TEXTURE_2D );
	glPopMatrix();
}

// Set position x of the player
void CWeapon::SetPos_x(int pos_x)
{
	weap_x = pos_x;
}
// Set position y of the player
void CWeapon::SetPos_y(int pos_y)
{
	weap_y = pos_y;
}

// Get position x of the player
int CWeapon::GetPos_x(void)
{
	return weap_x;
}
// Get position y of the player
int CWeapon::GetPos_y(void)
{
	return weap_y;
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