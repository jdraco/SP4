#include <string>
#include "Function.h"
class CWeaponDB
{
public:
	 CWeaponDB(std::string n,std::string ty,int d,float a,int s, std::string tx)
        {
			name = n;
			type = ty;
			dmg = d;
			asps = a;
			special = s;
			char *ctex = new char;
			strcpy(ctex, tx.c_str());
			LoadTGA( &(tex), ctex);
        }

	 CWeaponDB(): name("NIL"),type("NIL"),dmg(0), asps(0.0), special(0)
        {
        }
	std::string name;
	std::string type;
	int dmg;
	float asps;
	int special;
	TextureImage tex;

};