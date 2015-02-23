#include "weaponManager.h"

CweaponManager::CweaponManager(void)
{
}
CweaponManager::~CweaponManager(void)
{
}
void CweaponManager::Init(void)
{
	InitDB();
}
void CweaponManager::Update()
{
}
//void CweaponManager::damageManager(CPlayerInfo *player, CEnemy *enemy, bool hit, string weapon)
//{
//	int DMG = getWeapDMG(weapon);
//	string type = getWeapType(weapon);
//	if(DMG == -1)
//	{
//	}
//	else if(hit)
//	{
//		if(type == "Melee")
//			enemy->hp-= DMG*enemy->Mresist*(player->strength/10);
//		else if(type == "Ranged")
//			enemy->hp-= DMG*enemy->Rresist;
//	}
//	else
//	{
//		if(type == "Melee")
//			player->setHP(player->getHP()-(DMG*player->Mresist*(enemy->strength/10))); 
//		else if(type == "Ranged")
//			player->setHP(player->getHP()-(DMG*player->Rresist));
//	}
//}


float CweaponManager::damageManager(float hp, float Mresist, float Rresist, string weapon)
{
	int DMG = getWeapDMG(weapon);
	string type = getWeapType(weapon);
	if(DMG == -1)
	{
		return hp;
	}
	if(type == "Melee")
	{
		hp-= DMG*Mresist;
	}
	else if(type == "Ranged")
	{
		hp-= DMG*Rresist;
	}
	return hp;
}
int CweaponManager::getWeapDMG(string wname)
{
	for(weaponDB::iterator i = DB.begin(); i < DB.end(); i++)
	{
		if((*i)->name == wname)
		{
			return (*i)->dmg;
		}
	}
	return -1;
}

float CweaponManager::getWeapROF(string wname)
{
	for(weaponDB::iterator i = DB.begin(); i < DB.end(); i++)
	{
		if((*i)->name == wname)
		{
			return (*i)->asps;
		}
	}
	return -1;
}

string CweaponManager::getWeapType(string wname)
{
	for(weaponDB::iterator i = DB.begin(); i < DB.end(); i++)
	{
		if((*i)->name == wname)
		{
			return (*i)->type;
		}
	}
	return "UNKNOWN";
}

TextureImage CweaponManager::getWeapTex(string wname)
{
	for(weaponDB::iterator i = DB.begin(); i < DB.end(); i++)
	{
		if((*i)->name == wname)
		{
			return (*i)->tex;
		}
	}
}
void CweaponManager::InitDB()
{
	for(long long i = 0; i < TOTAL_WEAP; i++)
	{
		//LuaReading luaReader;
		string s = to_string(i);
		string Name = "Weapon_name_" + s;
		string Type = "Weapon_type_" + s;
		string Damage = "Weapon_damage_" + s;
		string AttackSpeed = "Weapon_attack_speed_" + s;
		string Special = "Weapon_special_" + s;
		string Texture = "Weapon_tex_" + s;
		DB.push_back(new CWeaponDB(GetStringFromLua("weaponDB.lua" , Name.c_str() ),
		GetStringFromLua("weaponDB.lua" , Type.c_str() ),
		GetIntFromLua("weaponDB.lua" , Damage.c_str()),
		GetFloatFromLua("weaponDB.lua" , AttackSpeed.c_str()),
		GetIntFromLua("weaponDB.lua" , Special.c_str()),
		GetStringFromLua("weaponDB.lua" , Texture.c_str())));
	}
}