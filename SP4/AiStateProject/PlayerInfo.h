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
	void SetAnimationInvert(bool heroAnimationInvert);
	// Get Animation Invert status of the player
	bool GetAnimationInvert(void);
	// Set Animation Counter of the player
	void SetAnimationCounter(int heroAnimationCounter);
	// Get Animation Counter of the player
	int GetAnimationCounter(void);
	// Constrain the position of the Hero to within the border
	void ConstrainHero( int leftBorder, int rightBorder, 
		int topBorder, int bottomBorder, 
		float timeDiff,
		int& mapOffset_x, int& mapOffset_y,
		int screenWidth, int mapWidth,
		int screenHeight, int mapHeight);

	void save();
	void load();

	// Ian
	bool facingup;
	bool facingdown;
	bool isMoving;
	bool isShooting;

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

	int m_iTileSize;

	// Hero's information
	int hero_x, hero_y, jumpspeed;
	bool heroAnimationInvert;
	int heroAnimationCounter;

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