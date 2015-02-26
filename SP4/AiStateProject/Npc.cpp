#include "Npc.h"

 CNpc::CNpc()
{
	 theGlobal = CGlobal::getInstance();
	 LoadTGA(&Npctex[0], "Texture/Npc/npcup.tga");
	 LoadTGA(&Npctex[1], "Texture/Npc/npcdown.tga");
	 LoadTGA(&Npctex[2], "Texture/Npc/popup.tga");
}

 CNpc::~CNpc()
 {

 }
void CNpc::init()
{
	Pos = Vector3D(500 + 40 , 300 + 1800, 0);;
	dir = 1;
	font = new CFont();
	NpcSprite = new CSprite;
	AnimationCounter = 0;
}

void CNpc::render()
{
	glPushMatrix();
	glTranslatef(Pos.x - theGlobal->theMap->mapOffset_x, Pos.y - theGlobal->theMap->mapOffset_y, 1);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	if (dir == 2)
	glBindTexture(GL_TEXTURE_2D, Npctex[0].texID);
	if (dir == 1)
	glBindTexture(GL_TEXTURE_2D, Npctex[1].texID);
	glBegin(GL_QUADS);                // draw quad 

	//	if (AnimationInvert == true)
	//{
		glTexCoord2f(0.25 * AnimationCounter,1); 
		glVertex2f(0,0);
		glTexCoord2f(0.25 * AnimationCounter,0); 
		glVertex2f(0,40);
		glTexCoord2f(0.25 * AnimationCounter + 0.25,0); 
		glVertex2f(40,40);
		glTexCoord2f(0.25 * AnimationCounter + 0.25,1); 
		glVertex2f(40,0);
	/*}
	else
	{
		glTexCoord2f(0.25 * AnimationCounter + 0.25,1); 
		glVertex2f(0,0);
		glTexCoord2f(0.25 * AnimationCounter + 0.25,0); 
		glVertex2f(0,40);
		glTexCoord2f(0.25 * AnimationCounter,0); 
		glVertex2f(40,40);
		glTexCoord2f(0.25 * AnimationCounter,1); 
		glVertex2f(40,0);
	}*/
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	/*glPushMatrix();
	glTranslatef(Pos.x - theGlobal->theMap->mapOffset_x, Pos.y - theGlobal->theMap->mapOffset_y, 1);
	NpcSprite->render(Texture[0]);;
	glPopMatrix();*/
}

void CNpc::Update()
{
	if (dir ==1 )
	{
		Pos.y += 1;
		AnimationCounter += 1;
	}
	else if (dir == 2)
	{
		Pos.y -= 1;
		AnimationCounter += 1;
	}

	if (AnimationCounter > 4)
	{
		AnimationCounter = 0;
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
	glBindTexture(GL_TEXTURE_2D, Npctex[2].texID);
	
	
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

	font->Render("AWAS",Vector3D(Pos.x - theGlobal->theMap->mapOffset_x + 30, Pos.y - theGlobal->theMap->mapOffset_y - 80,1), Vector3D(0, 0, 0));
}
void CNpc::Msg()
{
	//printw(Pos.x - theGlobal->theMap->mapOffset_x + 30, Pos.y - theGlobal->theMap->mapOffset_y - 80, 1, "HI!fsdakljfsdakljfl;dsakflsdjklf;sad");

}