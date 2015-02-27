#pragma once
#include <iostream>
#include "Weapon.h"
#include "Inventory.h"
#include <string>
#include "Lock.h"

#define INVENTORY_SIZE 5

using namespace std;

class CGuard;

class CPlayerInfo : public CVariable
{
private:

	static CPlayerInfo*
		_instance;


	string state;

	int HP;
	
	int Money;
	//string inventory[INVENTORY_SIZE];

	//int inventAmt[INVENTORY_SIZE];

	//string currEquippedArm;//armor

	int currEqAmmo;

	CWeapon *weapon;//weap

	CGlobal* theGlobal;

	//store enemy
	vector<CGuard*> guardlist;
	
	//Inventory* inventory;

	bool UD, LR;
	bool bLeft, bRight, bMoving, stopMovement;

	string curr_inv_weap;

public:

	static CPlayerInfo*getInstance();

	//TextureImage HeroTexture[4];
	// Render the Hero onto the screen
	void Render(void);
	// Initialise this class instance
	void Init(void);

	// Set Jumpspeed of the player
	void SetJumpspeed(int jumpspeed);
	
	void save();
	void load();

	//check for initialisation
	bool IsPos;

	void keyboardUpdate();
	bool Update();

	string getState();
	void setState(string state);

	int getHP();

	void setHP(int);

	int strength;
	int Mresist;
	int Rresist;
	//Inventory = string1,string2
	/*Inventory getInventory(int slot);

	void setInventory(Inventory set, int slot);

	Inventory* getWInventory();

	void setWInventory(Inventory set[INVENTORY_SIZE]);*/

	Inventory myInventory;
	int getInventory(int slot);

	bool CPlayerInfo::setInventory(int set, int slot);

	int* getWInventory();

	bool CPlayerInfo::setWInventory(int set[INVENTORY_SIZE]);

	string getCurrEquipped();//weap

	void setCurrEquipped(string weap);

	void setCurrEquippedFromInv(string weap);

	void handleCurrEquipped();

	//string getCurrEquippedArmor();//armor

	//void setCurrEquippedArmor(string arm);

	int getCurrAmmo();

	void setCurrAmmo(int ammo);

	int getMoney();//get money

	void setMoney(int m);//set money

	Bullet * GetBullet(int bullet);//calls GetBullet from weapon.cpp
	int GetBulletListSize();//Get bullet list size
	
	void SetGuardList(vector<CGuard*> tempguardlist) { guardlist = tempguardlist;} ;
	
protected:
	CPlayerInfo(void);
	~CPlayerInfo(void);

};