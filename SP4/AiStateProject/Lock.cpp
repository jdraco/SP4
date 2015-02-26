#include"Lock.h"

CLock::CLock(void)
{
	Pos = Vector3D(0,0,0);
	LoadTGA( &(Texture[0]), "Texture/Lock/lock01.tga");
	LoadTGA( &(Texture[1]), "Texture/Lock/lock02.tga");
	LoadTGA( &(Texture[2]), "Texture/Lock/sdriver.tga");
	LoadTGA( &(Texture[3]), "Texture/Lock/lockpick.tga");
	Math::InitRNG();
	Dir.y = rand()%250;
	active = false;
	stuckCount = 0;
	stuckDir = 1;
}

CLock::~CLock(void)
{
}

void CLock::Render()//Rot.x is the value for lock rotation
{					//Dir.x is the val for lockpick movement
					//Dir.y is the randomed required val for lockpicking
					//Dir.z is the val for lockpick animation
	glPushMatrix();
	glEnable( GL_TEXTURE_2D );
	glEnable( GL_BLEND );
	//glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTranslatef(400, 300, 0);
	glBindTexture( GL_TEXTURE_2D, Texture[0].texID );//render lock bg
	glBegin(GL_QUADS);
	glTexCoord2f(0,1); 
	glVertex2f(0,0);
	glTexCoord2f(0,0); 
	glVertex2f(0,LOCK_SIZE);
	glTexCoord2f(1,0); 
	glVertex2f(LOCK_SIZE,LOCK_SIZE);
	glTexCoord2f(1,1); 
	glVertex2f(LOCK_SIZE,0);
	glEnd();
	glPushMatrix();
	glTranslatef(LOCK_SIZE/2, LOCK_SIZE/2, 0);
	glRotatef(Rot.x,0,0,1);
	glTranslatef(-LOCK_SIZE/2,-LOCK_SIZE/2, 0);
	glBindTexture( GL_TEXTURE_2D, Texture[1].texID );//render lock
	glBegin(GL_QUADS);
	glTexCoord2f(0,1); 
	glVertex2f(0,0);
	glTexCoord2f(0,0); 
	glVertex2f(0,LOCK_SIZE);
	glTexCoord2f(1,0); 
	glVertex2f(LOCK_SIZE,LOCK_SIZE);
	glTexCoord2f(1,1); 
	glVertex2f(LOCK_SIZE,0);
	glEnd();
	glTranslatef(-75, -75, 0);
	glBindTexture( GL_TEXTURE_2D, Texture[2].texID );//render sdriver
	glBegin(GL_QUADS);
	glTexCoord2f(0,1); 
	glVertex2f(0,0);
	glTexCoord2f(0,0); 
	glVertex2f(0,LOCK_SIZE*1.5);
	glTexCoord2f(1,0); 
	glVertex2f(LOCK_SIZE*1.5,LOCK_SIZE*1.5);
	glTexCoord2f(1,1); 
	glVertex2f(LOCK_SIZE*1.5,0);
	glEnd();
	glPopMatrix();
	glTranslatef(LOCK_SIZE/2, LOCK_SIZE/2, 0);
	glRotatef(Dir.x+Dir.z-210,0,0,1);
	glTranslatef(-LOCK_SIZE/2,-LOCK_SIZE/2, 0);
	glTranslatef(-75, -75, 0);
	glBindTexture( GL_TEXTURE_2D, Texture[3].texID );//render lockpick
	glBegin(GL_QUADS);
	glTexCoord2f(0,1); 
	glVertex2f(0,0);
	glTexCoord2f(0,0); 
	glVertex2f(0,LOCK_SIZE*1.5);
	glTexCoord2f(1,0); 
	glVertex2f(LOCK_SIZE*1.5,LOCK_SIZE*1.5);
	glTexCoord2f(1,1); 
	glVertex2f(LOCK_SIZE*1.5,0);
	glEnd();
	glDisable( GL_BLEND );
	glDisable( GL_TEXTURE_2D );
	glPopMatrix();


}

bool CLock::Update(int D,bool turn)
{
	if(turn && Dir.x >= Dir.y-RANGE && Dir.x <= Dir.y+RANGE)
	{
		if(Rot.x >= 70)
			return true;
		Rot.x+=2;
		Dir.z+=2;
	}
	else if(turn)
	{
		Dir.z+=stuckDir;
		stuckCount++;
		if(stuckCount >= 10)
		{
			stuckDir = -stuckDir;
			stuckCount = 0;
		}
	}
	else if(!turn)
	{
		Dir.z = 0;
		if(Dir.x >= 0 && Dir.x <= 250)
			Dir.x += D;
		else if(Dir.x < 0)
			Dir.x = 0;
		else if(Dir.x > 250)
			Dir.x = 250;
	}
	return false;
}

void CLock::Reset()
{
	Rot = Vector3D(0,0,0);
	Dir = Vector3D(0,0,0);
	Dir.y = rand()%250;
	stuckCount = 0;
	stuckDir = 1;
}