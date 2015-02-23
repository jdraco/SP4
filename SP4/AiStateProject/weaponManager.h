#pragma once
//#include "PlayerInfo.h"
//#include "Enemy.h"
#include "WeaponDB.h"
#include <vector>
#include "Function.h"
#define TOTAL_WEAP 5



class CweaponManager
{
public:

	CweaponManager(void);
	~CweaponManager(void);

//void damageManager(CPlayerInfo *player, CEnemy *enemy, bool hit, string weapon);

float damageManager(float hp, float Mresist, float Rresist, string weapon);

int getWeapDMG(string wname);

float getWeapROF(string wname);

string getWeapType(string wname);

TextureImage getWeapTex(string wname);

void InitDB(void);

void Init();

void Update();

protected:
	

private:
	typedef std::vector<CWeaponDB*> weaponDB;
	weaponDB DB;
};