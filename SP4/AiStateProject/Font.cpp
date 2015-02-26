#include"Font.h"

CFont::CFont(void)
{
	Pos = Vector3D(0,0,0);
	LoadTGA( &(Texture[0]), "Texture/text.tga");
}

CFont::~CFont(void)
{
}

void CFont::Render(string text, Vector3D pos, Vector3D color)
{
	glPushMatrix();
	glColor3f(color.x,color.y,color.z);
	glTranslatef(pos.x,pos.y,pos.z);
	//glRotatef(180,0,1,0);
	for(unsigned i = 0; i < text.size(); i++)
	{
		RenderAlphabet(text.at(i),i);
	}
	glColor3f(1,1,1);
	glPopMatrix();
}

void CFont::RenderAlphabet(char text,int count)
{
	if(text == '/')
		glTranslatef(-count*BIG_TEXT, BIG_TEXT, 0);
	else{
		glEnable( GL_TEXTURE_2D );
		glEnable( GL_BLEND );
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture( GL_TEXTURE_2D, Texture[0].texID );
		if(text == 32)
		{
		}
		else if(text == '?' || text == '!' || text == '.' || text == ',')
		{
			int texLocX = 1;
			if(text == '!')
				texLocX = 2;
			if(text == '.')
				texLocX = 3;
			if(text == ',')
				texLocX = 4;
			glBegin(GL_QUADS);
			glTexCoord2f(0.14285 * texLocX,1-(0.166 *5)); 
			glVertex2f(0,0);
			glTexCoord2f(0.14285 * texLocX,1-(0.166 *5+0.166)); 
			glVertex2f(0,BIG_TEXT);
			glTexCoord2f(0.14285 * texLocX+0.14285,1-(0.166 *5+0.166)); 
			glVertex2f(BIG_TEXT,BIG_TEXT);
			glTexCoord2f(0.14285 * texLocX+0.14285,1-(0.166 *5)); 
			glVertex2f(BIG_TEXT,0);
			glEnd();
		}
		else if(text >= 97)
		{
			float textLocX = text - 97;
			float textLocY = 0;
			for(; textLocX > 6; textLocX-=7)
			{
				textLocY++;
			}
			glPushMatrix();
			glTranslatef(0,9,0);
			glBegin(GL_QUADS);
			glTexCoord2f(0.14285 * textLocX,1-(0.166 *textLocY)); 
			glVertex2f(0,0);
			glTexCoord2f(0.14285 * textLocX,1-(0.166 *textLocY+0.166)); 
			glVertex2f(0,SMALL_TEXT);
			glTexCoord2f(0.14285 * textLocX+0.14285,1-(0.166 *textLocY+0.166)); 
			glVertex2f(SMALL_TEXT,SMALL_TEXT);
			glTexCoord2f(0.14285 * textLocX+0.14285,1-(0.166 *textLocY)); 
			glVertex2f(SMALL_TEXT,0);
			glEnd();
			glPopMatrix();
		}
		else if(text >= 65)
		{
			float textLocX = text - 65;
			float textLocY = 0;
			for(; textLocX > 6; textLocX-=7)
			{
				textLocY++;
			}
			glBegin(GL_QUADS);
			glTexCoord2f(0.14285 * textLocX,1-(0.166 *textLocY)); 
			glVertex2f(0,0);
			glTexCoord2f(0.14285 * textLocX,1-(0.166 *textLocY+0.166)); 
			glVertex2f(0,BIG_TEXT);
			glTexCoord2f(0.14285 * textLocX+0.14285,1-(0.166 *textLocY+0.166)); 
			glVertex2f(BIG_TEXT,BIG_TEXT);
			glTexCoord2f(0.14285 * textLocX+0.14285,1-(0.166 *textLocY)); 
			glVertex2f(BIG_TEXT,0);
			glEnd();
		}
		else if(text >= 30)
		{
			float textLocX = text - 22;
			float textLocY = 6;
			for(; textLocX > 6; textLocX-=7)
			{
				textLocY++;
			}
			glBegin(GL_QUADS);
			glTexCoord2f(0.14285 * textLocX,1-(0.166 *textLocY)); 
			glVertex2f(0,0);
			glTexCoord2f(0.14285 * textLocX,1-(0.166 *textLocY+0.166)); 
			glVertex2f(0,BIG_TEXT);
			glTexCoord2f(0.14285 * textLocX+0.14285,1-(0.166 *textLocY+0.166)); 
			glVertex2f(BIG_TEXT,BIG_TEXT);
			glTexCoord2f(0.14285 * textLocX+0.14285,1-(0.166 *textLocY)); 
			glVertex2f(BIG_TEXT,0);
			glEnd();
		}

		glDisable( GL_BLEND );
		glDisable( GL_TEXTURE_2D );
		if(text >= 97)
			glTranslatef(SMALL_TEXT,0,0);
		else
			glTranslatef(BIG_TEXT,0,0);
	}
}