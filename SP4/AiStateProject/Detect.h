#include "Variable.h"

inline bool checkVision(string playerArmor,Vector3D playerPos, Vector3D guardPos, Vector3D guardDir,int tileRange, CMap *map, int x_offset, int y_offset)
{
	for(unsigned i = 0; i < tileRange; i++)
	{
		Vector3D avaliableVision = Vector3D(i*TILE_SIZE,i*TILE_SIZE,i*TILE_SIZE) * guardDir;
		if( (playerPos - (guardPos+avaliableVision)).GetMagnitude2D() < TILE_SIZE 
			&& checkCamo(playerArmor, playerPos, map, x_offset, y_offset))
			return true;
	}
	return false;
}

bool checkCamo(string playerArmor, Vector3D pos, CMap *map, int x_offset, int y_offset)
{
	int x = (int)floor((float)(x_offset+pos.x-LEFT_BORDER) / TILE_SIZE);
	int y = (int)floor((float)(y_offset+pos.y-BOTTOM_BORDER) / TILE_SIZE);
	float CamoVal = camo(playerArmor,map->theScreenMap[y][x]);
	float CamoRng = rand() % 100 + 1;
	if(CamoRng < CamoVal && CamoVal > 0)
		return true;
	else
		return false;
}

float camo(string playerArmor,int tile)
{
	float camo = 70;
	Vector3D colorDiff = ArmorColor(playerArmor) - TileColor(tile);
	if(colorDiff == 0)
		return camo;
	else 
	{
		camo-=(sqrtf(colorDiff.x*colorDiff.x)+sqrtf(colorDiff.y*colorDiff.y)+sqrtf(colorDiff.z*colorDiff.z))*30;
		return camo;
	}
	return 0;
}

Vector3D TileColor(int tile)
{
	if(tile == CMap::TILE_NULL)
		return Vector3D(1,1,0);
	else if(tile >= 35 && tile <= 40)
		return Vector3D(0.5,0.0,0.5);
	return Vector3D(1,1,1);
}

Vector3D ArmorColor(string playerArmor)
{
	if(playerArmor == "Sand camo")
		return Vector3D(1,1,0);
	if(playerArmor == "Purple camo")
		return Vector3D(0.5,0.0,0.5);
	if(playerArmor == "Grass camo")
		return Vector3D(0,1,0);
	return Vector3D(1,1,1);
}
