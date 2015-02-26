#pragma once
#include "Function.h"
#include "Vector3D.h"//Removed variable.h due to circular dependency

#define LOCK_SIZE 300

class CLock
{
public:
	 CLock(void);
	~CLock(void);
	void Render();
	int Update(int D,bool turn);
	void Reset(bool fullReset, int range, int lpd);//resets lock for next usage
	bool active;
	int currLPD;//lock pick durability
	int RANGE;
private:
	int Delay;
	int stuckCount;//this 2 stuck val creates the shaking animation
	int stuckDir;//
	Vector3D Dir;
	Vector3D Rot;
	//Rot.x is the value for lock rotation
	//Dir.x is the val for lockpick movement
	//Dir.y is the randomed required val for lockpicking
	//Dir.z is the val for lockpick animation
	TextureImage Texture[5];
};