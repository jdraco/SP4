#include "weaponManager.h"

CweaponManager::CweaponManager(void)
{
}
CweaponManager::~CweaponManager(void)
{
}
void CweaponManager::InitDB(void)
{
	getWeapDB(weaponDB);
}
void CweaponManager::Update()
{
}
void CweaponManager::damageManager(CPlayerInfo *player, CEnemy *enemy, bool hit, string weapon)
{
	int DMG = getWeapDMG(weapon);
	string type = getWeapType(weapon);
	if(DMG == -1)
	{
	}
	else if(hit)
	{
		if(type == "Melee")
			enemy->hp-= DMG*enemy->Mresist*(player->strength/10);
		else if(type == "Ranged")
			enemy->hp-= DMG*enemy->Rresist;
	}
	else
	{
		if(type == "Melee")
			player->setHP(player->getHP()-(DMG*player->Mresist*(enemy->strength/10))); 
		else if(type == "Ranged")
			player->setHP(player->getHP()-(DMG*player->Rresist));
	}
}

int CweaponManager::getWeapDMG(string wname)
{
	WeaponDB tempDB[TOTAL_WEAP];
	getWeapDB(tempDB);
	for(unsigned i = 0; i < TOTAL_WEAP; i++)
	{
		if(tempDB[i].name == wname)
		{
			return weaponDB[i].dmg;
		}
	}
	return -1;
}

string CweaponManager::getWeapType(string wname)
{
	for(unsigned i = 0; i < TOTAL_WEAP; i++)
	{
		if(weaponDB[i].name == wname)
		{
			return weaponDB[i].type;
		}
	}
	return "UNKNOWN";
}
void CweaponManager::getWeapDB(WeaponDB tempDB[TOTAL_WEAP])
{
	for(long long i = 0; i < TOTAL_WEAP; i++)
	{
		//LuaReading luaReader;
		string s = to_string(i);
		string Name = "Weapon_name_" + s;
		string Type = "Weapon_type_" + s;
		string Damage = "Weapon_damage_" + s;
		string Special = "Weapon_special_" + s;
		tempDB[i] = WeaponDB(GetStringFromLua("weaponDB.lua" , Name.c_str() ),
		GetStringFromLua("weaponDB.lua" , Type.c_str() ),
		GetIntFromLua("weaponDB.lua" , Damage.c_str()),
		GetIntFromLua("weaponDB.lua" , Special.c_str()));
		//tempDB[i] = weaponDB[i];
		cout << tempDB[i].name << " ," << tempDB[i].type << " ," 
			<< tempDB[i].dmg << " ," << tempDB[i].special << endl;
	}
}