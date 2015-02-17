#ifndef SPRITE_H
#define SPRITE_H

#include "Define.h"
//#include <GL/freeglut.h>
//#include <iostream>
//#include "definitions.h"
//#include "vector3D.h"
//#include "TextureImage.h"
//#include "Timer.h"

using namespace std;

class CSprite
{
private:
	//timer
	short SpriteDelay, timeRef;
	CGameTime SpriteTime;

	Vector3D SpriteSize;
	bool reverse, loop, AnimationInvert;
	float ratio_x, ratio_y;

public:
	CSprite();
	~CSprite();

	//Textures
	TextureImage Images;

	//Sprite Functions
	bool Stop;
	bool ImageInit(float SubImage, float ImageVar, short SpriteDelay = 0, 
		           short SpriteSizeX = TILE_SIZE, short SpriteSizeY = TILE_SIZE, bool loop = true);
	void Update();
	void changeVariation(float newVar);
	void changeSubImage(float newSub);
	void render(TextureImage imageTexture);
	void changeStop(bool nStop);

	//Public Variables
	float SubImage, ImageVar;

	//Set Animation Invert status of the sprite
	void SetAnimationInvert(bool AnimationInvert);

	//Get Animation Invert status of the sprite
	bool GetAnimationInvert();
	void CSprite::SetReverse(bool nReverse);

	//Sub and Var Variables
	float CurrentVar, CurSubImage;
};

#endif
