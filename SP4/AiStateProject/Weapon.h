#pragma once
#include <iostream>
#include "Variable.h"
#include <string>
#include "Function.h"
#include "weaponManager.h"
#include "bullet.h"

#define INVENTORY_SIZE 5

using namespace std;

class CWeapon : public CVariable
{
public:

	static CWeapon*
	GetInstance();

	TextureImage weapTexture[4];
	// Render the weap onto the screen
	void Renderweap(void);
	// Initialise this class instance
	void Init(void);
	// Set position x of the player
	void SetPos_x(int pos_x);
	// Set position y of the player
	void SetPos_y(int pos_y);
	// Set Jumpspeed of the player
	void SetJumpspeed(int jumpspeed);
	// Get position x of the player
	int GetPos_x(void);
	// Get position y of the player
	int GetPos_y(void);
	// Set Animation Invert status of the player
	void SetAnimationInvert(bool weapAnimationInvert);
	// Get Animation Invert status of the player
	bool GetAnimationInvert(void);
	// Set Animation Counter of the player
	void SetAnimationCounter(int weapAnimationCounter);
	// Get Animation Counter of the player
	int GetAnimationCounter(void);
	// Constrain the position of the weap to within the border
	// Ian
	bool facingup;
	bool facingdown;

	string getState();
	void setState(string state);

	string getCurrEquipped();

	void setCurrEquipped(string weap);

	int getCurrAmmo();

	void setCurrAmmo(int ammo);

	bool Attack(Vector3D dir,Vector3D pos);

	void Update(void);

	CWeapon(void);
	~CWeapon(void);

	Bullet* GetBullet(int bullet);
	int GetBulletListSize();//Get bullet list size

	bool checkProjectileCollision(Vector3D Target);

private:


	int m_iTileSize;

	// weap's information
	int weap_x, weap_y;
	bool weapAnimationInvert;
	int weapAnimationCounter;

	// Character State - ian
	string state;

	string currEquipped;

	int currEqAmmo;

	bool attack;

	float cooldown;

	CweaponManager *weapManager;

	std::vector<Bullet *> ListOfBullets;
	//CGlobal* theGlobal;
};