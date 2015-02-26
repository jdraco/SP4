#include "Npc.h"

 CNpc::CNpc()
{
	 theGlobal = CGlobal::getInstance();
}

 CNpc::~CNpc()
 {

 }
void CNpc::init()
{
	if (!LoadTGA(&(Texture[0]), "Texture/Tiles/James.tga"))
		cout << "No hero texture" << endl;
	if (!LoadTGA(&(Texture[1]), "Texture/Tiles/pupup.tga"))
		cout << "No hero2 texture" << endl;
	Pos = Vector3D(500 + 40 , 300 + 1800, 0);;
	dir = 1;
}

void CNpc::render()
{
	glPushMatrix();
	glTranslatef(Pos.x - theGlobal->theMap->mapOffset_x, Pos.y - theGlobal->theMap->mapOffset_y, 1);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, Texture[0].texID);
	glBegin(GL_QUADS);                // draw quad 

	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(0.0f, 0.0f);	// top left 

	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(0.0f, 40.0f);	// top right

	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(40.0f, 40.0f);	// bottom right

	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(40.0f, 0.0f);	// bottom left
	
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	
}

void CNpc::Update()
{
	if (dir ==1 )
	{
		Pos.y += 1;
	}
	else if (dir == 2)
	{
		Pos.y -= 1;
	}
	if (theGlobal->Collided(Pos - Vector3D(theGlobal->theMap->mapOffset_x, theGlobal->theMap->mapOffset_y,0)
		- Vector3D(0, 5, 0), true, false, false, false,
		theGlobal->theMap, theGlobal->theMap->mapOffset_x, theGlobal->theMap->mapOffset_y))
	{
		dir = 1;
	}

	if (theGlobal->Collided(Pos - Vector3D(theGlobal->theMap->mapOffset_x, theGlobal->theMap->mapOffset_y, 0) 
		+Vector3D(0, 5, 0), false, true, false, false,
		theGlobal->theMap, theGlobal->theMap->mapOffset_x, theGlobal->theMap->mapOffset_y))
	{
		dir = 2;
	}

	
}
void CNpc::Popup()
{
	glPushMatrix();
	glTranslatef(Pos.x - theGlobal->theMap->mapOffset_x+30, Pos.y - theGlobal->theMap->mapOffset_y-80, 1);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, Texture[1].texID);
	glBegin(GL_QUADS);                // draw quad 

	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(0.0f, 0.0f);	// top left 

	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(0.0f, 100.0f);	// top right

	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(100.0f, 100.0f);	// bottom right

	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(100.0f, 0.0f);	// bottom left

	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}
void CNpc::Msg()
{
	printw(Pos.x - theGlobal->theMap->mapOffset_x + 30, Pos.y - theGlobal->theMap->mapOffset_y - 80, 1, "HI!fsdakljfsdakljfl;dsakflsdjklf;sad");

}