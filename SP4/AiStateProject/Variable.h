#ifndef VARIABLE_H
#define VARIABLE_H
#include "Global.h"
#include "GameTime.h"

class CGoodies;
class CGoodiesFactory;

class CVariable
{
protected:	
	//Basic needs
	Vector3D Pos;	// Position
	Vector3D Color; // Color
	Vector3D Vel;	// Velocity
	Vector3D Dir;	// Direction
	Vector3D Scale;	// Scale
	Vector3D Rot;	// Rotation

	Region Collision;

	Vector3D Min;
	Vector3D Max;

	//Game logic
	
	STATE Health;
	float Damage;
	int delay;
	CGlobal* theGlobal;
	
	//Image Logic
	int m_iTileSize;
	
	bool AnimationInvert;
	int AnimationCounter;

	//Movement logic
	int jumpspeed;
	int moveSpeed;
	bool facingup;
	bool facingdown;
	bool isMoving;
	bool isShooting;


	CGoodies* Target;
		
public:
	CVariable(void);
	~CVariable(void);

	//Texture
	TextureImage Texture[10];

	//Variable to check outside
	bool active;


	enum OBJECT_ID
	{
		ENEMY,
		PLAYER,
		SHOTS,
		FUSTRUM
	};
	OBJECT_ID Object;

	enum ITEM_ID
	{
		THINNERITEM = 0,
		SIRENITEM,
		HEALTH,
		DELAY,
	};

	enum OBJECT_STATE
	{
		//INVULNERABLE,
		IDLE,
		MOVING,
		ATTACK,
		RUNNING,
		DEAD
	};
	OBJECT_STATE State;

	enum OBJECT_STATUS
	{ 
		TARGETABLE = 0,
		UNTARGETABLE
	};
	OBJECT_STATUS Status;

	enum OBJECT_AREA
	{
		OUTSIDE = 0,
		SAFEAREA,
	};

	OBJECT_AREA CharArea;

	//Get/Set function
	void SetPos(Vector3D tempPos);
	Vector3D GetPos(void);
	Vector3D GetDir(void);
	void SetPos_x(float pos_x);
	void SetPos_y(float pos_y);
	

	//Image 
	// Set Animation Counter of the player
	void SetAnimationCounter(int heroAnimationCounter);
	int GetAnimationCounter(void);

	void SetAnimationInvert(bool heroAnimationInvert);
	bool GetAnimationInvert(void);

	
	//Health
	void setCurrentHealth(float health){Health.current = health;};
	STATE getHealth(){return Health;};
	int getNoOfHealth(){return Health.no;};
	
	//damage
	void setDamage(float damage){Damage = damage;};
	float getDamage(){return Damage;};

	int GetDelay(void);

	Vector3D GetMin(void);
	Vector3D GetMax(void);
		
	//Function for all class
	int CalculateDistance(Vector3D tempPos);

	//aim target
	void SetTarget(CGoodies *tempTarget);

	/*
	void Init (bool active ,Vector3D Pos , Vector3D Color, Vector3D Scale = 1.0f, int Health = 0, OBJECT_STATE State = IDLE ,
				Vector3D Vel = 0.0f );
	*/
	void DrawBox(Vector3D Size , Vector3D Color = 1.0f); // For box object and if rendering of collision box if needed
};


#endif 