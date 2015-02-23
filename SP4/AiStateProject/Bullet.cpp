#include "Bullet.h"


Bullet::Bullet(void)
{
	//theGlobal = CGlobal::getInstance();
	name = "NIL";
	type = 0;
	range = 1000;
	dtravelled = 0;
	Vel = Vector3D(5,5,0);
	theGlobal = CGlobal::getInstance();
LoadTGA( &(Texture[0]), "Texture/bullet.tga");
}

Bullet::Bullet(bool melee)
{
	//theGlobal = CGlobal::getInstance();
	name = "NIL";
	type = 0;
	range = TILE_SIZE;
	dtravelled = 0;
	Vel = Vector3D(5,5,0);
	theGlobal = CGlobal::getInstance();
	AnimationCounter = 0;
LoadTGA( &(Texture[0]), "Texture/swipeanimation.tga");
}

Bullet::~Bullet(void)
{
}

void Bullet::Render(void) 
{
	glPushMatrix();
	glTranslatef(Pos.x, Pos.y, 1);
	/*glRotatef(Dir.x,1,0,0);
	glRotatef(Dir.y,0,1,0);*/
	glEnable( GL_TEXTURE_2D );
	glEnable( GL_BLEND );
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture( GL_TEXTURE_2D, Texture[0].texID );
	if(range < 100)
	{
		//glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		
		if (AnimationInvert == true)
		{
			glTexCoord2f(0.166 * AnimationCounter,1); 
			glVertex2f(0,0);
			glTexCoord2f(0.166 * AnimationCounter,0); 
			glVertex2f(0,m_iTileSize);
			glTexCoord2f(0.166 * AnimationCounter + 0.166,0); 
			glVertex2f(m_iTileSize,m_iTileSize);
			glTexCoord2f(0.166 * AnimationCounter + 0.166,1); 
			glVertex2f(m_iTileSize,0);
		}
		else
		{
			/*glTexCoord2f(0.166 * AnimationCounter + 0.166,1); 
			glVertex2f(0,0);
			glTexCoord2f(0.166 * AnimationCounter + 0.166,0); 
			glVertex2f(0,m_iTileSize);
			glTexCoord2f(0.166 * AnimationCounter,0); 
			glVertex2f(m_iTileSize,m_iTileSize);
			glTexCoord2f(0.166 * AnimationCounter,1); 
			glVertex2f(m_iTileSize,0);*/
			glBegin(GL_QUADS);
			glTexCoord2f(0.166 * AnimationCounter,0); 
			glVertex2f(0,0);
			glTexCoord2f(0.166 * AnimationCounter,1); 
			glVertex2f(0,TILE_SIZE);
			glTexCoord2f(0.166 * AnimationCounter + 0.166,1); 
			glVertex2f(TILE_SIZE,TILE_SIZE);
			glTexCoord2f(0.166 * AnimationCounter + 0.166,0); 
			glVertex2f(TILE_SIZE,0);
		}
	}
	else
	{
		glBegin(GL_QUADS);
		glTexCoord2f(0,0); 
		glVertex2f(0,0);
		glTexCoord2f(0,1); 
		glVertex2f(0,TILE_SIZE);
		glTexCoord2f(1,1); 
		glVertex2f(TILE_SIZE,TILE_SIZE);
		glTexCoord2f(1,0); 
		glVertex2f(TILE_SIZE,0);
	}
	glEnd();
	glDisable( GL_BLEND );
	glDisable( GL_TEXTURE_2D );
	glPopMatrix();

}

bool Bullet::Update(void)
{
	if(dtravelled >= range)
		return false;
	Pos.x+=Vel.x * Dir.x;
	Pos.y+=Vel.y * Dir.y;
	dtravelled+= sqrtf((Vel.x * Dir.x)*(Vel.x * Dir.x)+(Vel.y * Dir.y)*(Vel.y * Dir.y));
	//ConstrainPlayer((const int)(MAP_SCREEN_WIDTH*0.5+LEFT_BORDER), (const int)(MAP_SCREEN_WIDTH*0.5+LEFT_BORDER), 
	//				(const int)(MAP_SCREEN_HEIGHT*0.5+BOTTOM_BORDER), (const int)(MAP_SCREEN_HEIGHT*0.5+BOTTOM_BORDER),
	//				1.0f, theGlobal->theMap->mapOffset_x, theGlobal->theMap->mapOffset_y);
	if(range < 100 && AnimationCounter < 5)
		AnimationCounter++;
}

void Bullet::SetDir(Vector3D dir)
{ Dir = dir;}
Vector3D Bullet::GetDir()
{ return Dir;}
void Bullet::SetPos(Vector3D pos)
{ Pos = pos;}
Vector3D Bullet::GetPos()
{ return Pos;}
void Bullet::SetPosX(float x)
{ Pos.x = x;}
void Bullet::SetPosY(float y)
{ Pos.y = y;}
