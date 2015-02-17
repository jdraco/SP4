#pragma once

#include "Goodies.h"

//Speed Declarations
#define RUN_SPEED 5
#define TURN_SPEED 100

class CPlayer : public CGoodies 
{
private:
	bool jump;
	float Gravity, JumpPower;

	//global variable class
	CGlobal* theGlobal;

	//texture
	TextureImage PlayerTexture[3];
	CSprite *playerSprite, *playerJumpSprite, *ghostSprite;


protected:
	CPlayer(void);
	static CPlayer* instance;
public:
	static CPlayer* getInstance()
	{
		if (instance == 0)
		{
			instance = new CPlayer();
		}
		return instance;
	};

	~CPlayer(void);

	enum TurnDir
	{
		LEFT,
		RIGHT,
		STOP,
	}; TurnDir TDir;

	//For the parent virtual
	void SelfInit(void) ;
	bool Update(void);
	void Render();

	 void SetItem(ITEM_ID item_id , int SetItem);
	 int GetItem(ITEM_ID item_id);

	//Get & Set Functions

	 Vector3D GetPos() { return this->Pos; }
	Vector3D GetRot() { return this->Rot; }
	void SetPos(float x, float y, float z) { Pos.x = x; Pos.y = y; Pos.z = z; }
	void SetRot(float x, float y, float z) { Rot.x = x; Rot.y = y; Rot.z = z; }
	//float GetCurrentSpeed() { return this->currentSpeed; }


private:
	void InitSceneGraph();
	void keyboardUpdate();
	void UpdateSubGroupChildren(CFrustum *theFrustum);

	void ConstrainPlayer(const int leftBorder, const int rightBorder, 
							  const int topBorder, const int bottomBorder, 
							  float timeDiff,
							  int& mapOffset_x, int& mapOffset_y);

	void moveMeUpDown(bool mode, float timeDiff);
	void moveMeLeftRight(bool mode, float timeDiff);

	//UDLR Flags
	bool UD, LR;
	bool bLeft, bRight, bMoving, stopMovement;
};

