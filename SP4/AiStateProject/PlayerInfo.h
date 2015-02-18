#pragma once
#include <iostream>
#include "Function.h"
#include "Weapon.h"
#include <string>
#include "Variable.h"

#define INVENTORY_SIZE 5

using namespace std;

struct Inventory{
	Inventory(string invent,int amt)
	{
		inventory = invent;
		amount = amt;
	}
	Inventory(): inventory("NIL"),amount(0)
	{
	}
	string inventory;
	int amount;
};
class CPlayerInfo : public CVariable
{
public:

	static CPlayerInfo*
	getInstance();

	//TextureImage HeroTexture[4];
	// Render the Hero onto the screen
	void Render(void);
	// Initialise this class instance
	void Init(void);

	// Set Jumpspeed of the player
	void SetJumpspeed(int jumpspeed);
	
	void save();
	void load();

	// Ian


	int damage;
	int skillLevel;
	int debt;

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
	Inventory getInventory(int slot);

	void setInventory(Inventory set, int slot);

	Inventory* getWInventory();

	void setWInventory(Inventory set[INVENTORY_SIZE]);

	string getCurrEquipped();

	void setCurrEquipped(string weap);

	int getCurrAmmo();

	void setCurrAmmo(int ammo);

protected:
	CPlayerInfo(void);
	~CPlayerInfo(void);


private:

	static CPlayerInfo*
		_instance;



	// Hero's information
	int hero_x, hero_y ;


	// Character State - ian
	string state;

	int HP;
	
	string inventory[INVENTORY_SIZE];

	int inventAmt[INVENTORY_SIZE];

	string currEquipped;

	int currEqAmmo;

	CWeapon *weapon;

	CGlobal* theGlobal;

	bool UD, LR;
	bool bLeft, bRight, bMoving, stopMovement;
};