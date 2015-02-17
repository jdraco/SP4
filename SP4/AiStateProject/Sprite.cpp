#include "Sprite.h"

//Constructor
CSprite::CSprite()
	: Stop(true), reverse(false), AnimationInvert(reverse)
	, CurrentVar(NULL), CurSubImage(CurrentVar)
{}

//Destructor
CSprite::~CSprite() {}

bool CSprite::ImageInit(float SubImage, float ImageVar, short SpriteDelay, short SpriteSizeX, short SpriteSizeY, bool loop)
{
	//Initialise Image Variables
	this->SubImage = SubImage;
	this->ImageVar = ImageVar;
	ratio_x = 1.0f / SubImage;
	ratio_y = 1.0f / ImageVar;
	this->loop = loop;
	this->SpriteDelay = SpriteDelay;
	this->SpriteSize.Set(SpriteSizeX, SpriteSizeY);
	//timeRef = CTimer::getInstance()->insertNewTime(SpriteDelay);
	SpriteTime.SetTotalTime(SpriteDelay);

	return true;
}

void CSprite::changeStop(bool bStop)
{
	Stop = bStop;
}

void CSprite::SetAnimationInvert(bool AnimationInvert)
{
	this->AnimationInvert = AnimationInvert;
}

void CSprite::SetReverse(bool bReverse)
{
	this->reverse = bReverse;

	switch(reverse)
	{
	case true:
		CurSubImage = SubImage-1;
		break;
	case false:
		CurSubImage = 0;
		break;
	}
}

void CSprite::render(TextureImage imageTexture)
{
	glScalef(SpriteSize.x, SpriteSize.y, 1);
	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
	
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture(GL_TEXTURE_2D, imageTexture.texID);

		if (AnimationInvert)
		{
			glBegin(GL_TRIANGLE_STRIP);
				glTexCoord2f(ratio_x * (CurSubImage + 1), ratio_y * CurrentVar);
				glVertex3f(-0.5, 0.5, 0);
		
				glTexCoord2f(ratio_x * (CurSubImage + 1), ratio_y * (CurrentVar+1));
				glVertex3f(-0.5,-0.5,0);

				glTexCoord2f(ratio_x * CurSubImage, ratio_y * CurrentVar);
				glVertex3f(0.5,0.5,0);

				glTexCoord2f(ratio_x * CurSubImage, ratio_y * (CurrentVar+1));
				glVertex3f(0.5,-0.5,0);
			glEnd();
		}

		else
		{
			glBegin(GL_TRIANGLE_STRIP);
				glTexCoord2f(ratio_x * CurSubImage, ratio_y * CurrentVar);
				glVertex3f(-0.5, 0.5, 0);
		
				glTexCoord2f(ratio_x * CurSubImage, ratio_y * (CurrentVar+1));
				glVertex3f(-0.5,-0.5,0);

				glTexCoord2f(ratio_x * (CurSubImage + 1), ratio_y * CurrentVar);
				glVertex3f(0.5,0.5,0);

				glTexCoord2f(ratio_x * (CurSubImage + 1), ratio_y * (CurrentVar+1));
				glVertex3f(0.5,-0.5,0);
			glEnd();
		}

		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void CSprite::changeVariation(float newVar)
{
	if (newVar >= ImageVar)
		CurrentVar = ImageVar-1;
	else if (newVar < 0)
		CurrentVar = 0;
	else
		CurrentVar = newVar;
}

void CSprite::changeSubImage(float newSub)
{
	//Input
	if (newSub >= SubImage)
		CurSubImage = SubImage-1;
	else if (newSub < 0)
		CurSubImage = 0;
	else
		CurSubImage = newSub;
}

void CSprite::Update()
{
	if (!Stop)
	{
		SpriteTime.Update();
		if(SpriteTime.GetCurrent() < 1){
			SpriteTime.SetCurrent();
			SpriteTime.SetTotalTime(4);
			if (!reverse)
			{
				CurSubImage++;
				if (CurSubImage > SubImage-1)
				{
					if (loop)
						CurSubImage = 0;
					else
						CurSubImage--;
				}
			}

			else
			{
				CurSubImage--;
				if (CurSubImage < 0)
				{
					if (loop)
						CurSubImage = SubImage-1;
					else
						CurSubImage++;
				}
			}
		}
	}
}