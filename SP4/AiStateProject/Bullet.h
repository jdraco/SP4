#pragma once

#include "Goodies.h"

class Bullet : public CVariable
{
public:
	Bullet(void);
	~Bullet(void);
	Bullet(bool melee);
	string name;
	int type;
	float range;
	float dtravelled;
	bool Update(void);
	void Render();
	void SetDir(Vector3D dir);
	Vector3D GetDir();
	void SetPos(Vector3D pos);
	Vector3D GetPos();
private:	
	CGlobal* theGlobal;
};

