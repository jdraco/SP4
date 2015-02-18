#pragma once
#include "PlayerInfo.h"
#include "Enemy.h"

#define TOTAL_WEAP 5

struct WeaponDB{
	 WeaponDB(string n,string t,int d,int s)
        {
			name = n;
			type = t;
			dmg = d;
			special = s;
        }
	 WeaponDB(WeaponDB &db)
        {
			name = db.name;
			type = db.type;
			dmg = db.dmg;
			special = db.special;
        }
	 WeaponDB(): name("NIL"),type("NIL"),dmg(0), special(00)
        {
        }
	string name;
	string type;
	int dmg;
	int special;
};
class CweaponManager
{
public:

void damageManager(CPlayerInfo *player, CEnemy *enemy, bool hit, string weapon);

int getWeapDMG(string wname);

string getWeapType(string wname);

void InitDB(void);

void getWeapDB(WeaponDB tempDB[TOTAL_WEAP]);

void Update();

protected:
	CweaponManager(void);
	~CweaponManager(void);

private:
	WeaponDB weaponDB[TOTAL_WEAP];
};