#include "GameMenu.h"


GameMenu::GameMenu(void)
:	volume(70)
,	LMouse_down_boolean(false)
,	enable_options(false)
,	showMenu(true)
,	gameInit(false)
{
	LoadTGA( &menuTex[ 0 ], "Texture/Menu/blank.tga");
	LoadTGA( &menuTex[ 1 ], "Texture/Menu/menu_bg.tga");
	LoadTGA( &menuTex[ 2 ], "Texture/Menu/button.tga");
	LoadTGA( &menuTex[ 3 ], "Texture/Menu/button_MO.tga");
	LoadTGA( &menuTex[ 4 ], "Texture/Menu/minus.tga");
	LoadTGA( &menuTex[ 5 ], "Texture/Menu/plus.tga");
	LoadTGA( &menuTex[ 6 ], "Texture/Menu/mutedbutton.tga");
	LoadTGA( &menuTex[ 7 ], "Texture/Menu/unmutedbutton.tga");
	LoadTGA( &menuTex[ 8 ], "Texture/Menu/jameslogo.tga");

	font_style = GLUT_BITMAP_HELVETICA_18;
}


GameMenu::~GameMenu(void)
{
}

void GameMenu::printw (float x, float y, float z, char* format, ...)
{
	va_list args;	//  Variable argument list
	int len;		//	String length
	int i;			//  Iterator
	char * text;	//	Text

	//  Initialize a variable argument list
	va_start(args, format);

	//  Return the number of characters in the string referenced the list of arguments.
	//  _vscprintf doesn't count terminating '\0' (that's why +1)
	len = _vscprintf(format, args) + 1; 

	//  Allocate memory for a string of the specified size
	text = (char *)malloc(len * sizeof(char));

	//  Write formatted output using a pointer to the list of arguments
	vsprintf_s(text, len, format, args);

	//  End using variable argument list 
	va_end(args);

	//  Specify the raster position for pixel operations.
	glRasterPos3f (x, y, z);


	//  Draw the characters one by one
	for (i = 0; text[i] != '\0'; i++)
		glutBitmapCharacter(font_style, text[i]);

	//  Free the allocated memory for the string
	free(text);
}

void GameMenu::OptionsScreen(void)
{
	if (show_options == true)
	{
		// Options window
		glColor4f(0.2f, 0.2f, 0.2f, 0.95f);
		glPushMatrix();
		glTranslatef(360, 150, 0);
		glScalef(7.5/* * w / 1024*/, 12.25 * h / 745, 1);
		glEnable( GL_TEXTURE_2D );
		glEnable( GL_BLEND );
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindTexture( GL_TEXTURE_2D, menuTex[0].texID );
			glBegin(GL_QUADS);
				glTexCoord2f(0,1); glVertex2f(0,0);
				glTexCoord2f(0,0); glVertex2f(0,40);
				glTexCoord2f(1,0); glVertex2f(40,40);
				glTexCoord2f(1,1); glVertex2f(40,0);
			glEnd();
		glDisable( GL_BLEND );
		glDisable( GL_TEXTURE_2D );
		glPopMatrix();

		// Lower volume button
		if (mouseX > 405 * w / 1024 && mouseX < 445 * w / 1024 && mouseY > 245 * h / 745 && mouseY < 285 * h / 745)
		{
			glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
			glPushMatrix();
			glTranslatef(410, 260, 0);
			glEnable( GL_TEXTURE_2D );
			glEnable( GL_BLEND );
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				glBindTexture( GL_TEXTURE_2D, menuTex[4].texID );
				glBegin(GL_QUADS);
					glTexCoord2f(0,1); glVertex2f(0,0);
					glTexCoord2f(0,0); glVertex2f(0,40);
					glTexCoord2f(1,0); glVertex2f(40,40);
					glTexCoord2f(1,1); glVertex2f(40,0);
				glEnd();
			glDisable( GL_BLEND );
			glDisable( GL_TEXTURE_2D );
			glPopMatrix();

			// When clicked
			if (mouseState == false && LMouse_down_boolean == false)
			{
				// DECREASE MUSIC VOLUME
				volume -= 5;
				
				if (volume < 0)
				{
					volume = 0;
				}

				LMouse_down_boolean = true;
			}
			else if (mouseState == true)
			{
				LMouse_down_boolean = false;
			}
		}
		else
		{
			glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
			glPushMatrix();
			glTranslatef(410, 260, 0);
			glEnable( GL_TEXTURE_2D );
			glEnable( GL_BLEND );
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				glBindTexture( GL_TEXTURE_2D, menuTex[4].texID );
				glBegin(GL_QUADS);
					glTexCoord2f(0,1); glVertex2f(0,0);
					glTexCoord2f(0,0); glVertex2f(0,40);
					glTexCoord2f(1,0); glVertex2f(40,40);
					glTexCoord2f(1,1); glVertex2f(40,0);
				glEnd();
			glDisable( GL_BLEND );
			glDisable( GL_TEXTURE_2D );
			glPopMatrix();
		}

		// Increase volume button
		if(mouseX > 575 * w / 1024 && mouseX < 610 * w / 1024 && mouseY > 245 * h / 745 && mouseY < 285 * h / 745)
		{
			glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
			glPushMatrix();
			glTranslatef(570, 260, 0);
			glEnable( GL_TEXTURE_2D );
			glEnable( GL_BLEND );
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				glBindTexture( GL_TEXTURE_2D, menuTex[5].texID );
				glBegin(GL_QUADS);
					glTexCoord2f(0,1); glVertex2f(0,0);
					glTexCoord2f(0,0); glVertex2f(0,40);
					glTexCoord2f(1,0); glVertex2f(40,40);
					glTexCoord2f(1,1); glVertex2f(40,0);
				glEnd();
			glDisable( GL_BLEND );
			glDisable( GL_TEXTURE_2D );
			glPopMatrix();

			// When clicked
			if (mouseState == false && LMouse_down_boolean == false)
			{
				// INCREASE MUSIC VOLUME
				volume += 5;

				if (volume > 100)
				{
					volume = 100;
				}

				LMouse_down_boolean = true;
			}
			else if (mouseState == true)
			{
				LMouse_down_boolean = false;
			}
		}
		else
		{
			glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
			glPushMatrix();
			glTranslatef(570, 260, 0);
			glEnable( GL_TEXTURE_2D );
			glEnable( GL_BLEND );
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				glBindTexture( GL_TEXTURE_2D, menuTex[5].texID );
				glBegin(GL_QUADS);
					glTexCoord2f(0,1); glVertex2f(0,0);
					glTexCoord2f(0,0); glVertex2f(0,40);
					glTexCoord2f(1,0); glVertex2f(40,40);
					glTexCoord2f(1,1); glVertex2f(40,0);
				glEnd();
			glDisable( GL_BLEND );
			glDisable( GL_TEXTURE_2D );
			glPopMatrix();
		}

		// Volume number (text)
		glLoadIdentity ();
		glPushAttrib(GL_ALL_ATTRIB_BITS);
			glColor3f(0.0f, 0.0f, 0.0f);

			if (volume > 0)
				printw (500, 285.0, 0, "%.i", volume); // SHOW MUSIC VOLUME (WHEN MORE THAN 0)
			else
				printw (500, 285.0, 0, "0"); // SHOW MUSIC VOLUME (WHEN 0)
		
		glPopAttrib();

		// Mute/Unmute music button
		if (mute_music == true)
		{
			if (mouseX > 490 * w / 1024 && mouseX < 530 * w / 1024 && mouseY > 360 * h / 745 && mouseY < 400 * h / 745)
			{
				glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
				glPushMatrix();
				glTranslatef(490, 385, 0);
				glEnable( GL_TEXTURE_2D );
				glEnable( GL_BLEND );
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					glBindTexture( GL_TEXTURE_2D, menuTex[6].texID );
					glBegin(GL_QUADS);
						glTexCoord2f(0,1); glVertex2f(0,0);
						glTexCoord2f(0,0); glVertex2f(0,40);
						glTexCoord2f(1,0); glVertex2f(40,40);
						glTexCoord2f(1,1); glVertex2f(40,0);
					glEnd();
				glDisable( GL_BLEND );
				glDisable( GL_TEXTURE_2D );
				glPopMatrix();

				// When clicked
				if (mouseState == false && LMouse_down_boolean == false)
				{
					mute_music = false;
					LMouse_down_boolean = true;
				}
				else if (mouseState == true)
				{
					LMouse_down_boolean = false;
				}
			}
			else
			{
				glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
				glPushMatrix();
				glTranslatef(490, 385, 0);
				glEnable( GL_TEXTURE_2D );
				glEnable( GL_BLEND );
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					glBindTexture( GL_TEXTURE_2D, menuTex[6].texID );
					glBegin(GL_QUADS);
						glTexCoord2f(0,1); glVertex2f(0,0);
						glTexCoord2f(0,0); glVertex2f(0,40);
						glTexCoord2f(1,0); glVertex2f(40,40);
						glTexCoord2f(1,1); glVertex2f(40,0);
					glEnd();
				glDisable( GL_BLEND );
				glDisable( GL_TEXTURE_2D );
				glPopMatrix();
			}
		}
		else
		{
			if (mouseX > 490 * w / 1024 && mouseX < 530 * w / 1024 && mouseY > 360 * h / 745 && mouseY < 400 * h / 745)
			{
				glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
				glPushMatrix();
				glTranslatef(490, 385, 0);
				glEnable( GL_TEXTURE_2D );
				glEnable( GL_BLEND );
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					glBindTexture( GL_TEXTURE_2D, menuTex[7].texID );
					glBegin(GL_QUADS);
						glTexCoord2f(0,1); glVertex2f(0,0);
						glTexCoord2f(0,0); glVertex2f(0,40);
						glTexCoord2f(1,0); glVertex2f(40,40);
						glTexCoord2f(1,1); glVertex2f(40,0);
					glEnd();
				glDisable( GL_BLEND );
				glDisable( GL_TEXTURE_2D );
				glPopMatrix();

				// When clicked
				if (mouseState == false && LMouse_down_boolean == false)
				{
					mute_music = true;
					LMouse_down_boolean = true;
				}
				else if (mouseState == true)
				{
					LMouse_down_boolean = false;
				}
			}
			else
			{
				glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
				glPushMatrix();
				glTranslatef(490, 385, 0);
				glEnable( GL_TEXTURE_2D );
				glEnable( GL_BLEND );
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					glBindTexture( GL_TEXTURE_2D, menuTex[7].texID );
					glBegin(GL_QUADS);
						glTexCoord2f(0,1); glVertex2f(0,0);
						glTexCoord2f(0,0); glVertex2f(0,40);
						glTexCoord2f(1,0); glVertex2f(40,40);
						glTexCoord2f(1,1); glVertex2f(40,0);
					glEnd();
				glDisable( GL_BLEND );
				glDisable( GL_TEXTURE_2D );
				glPopMatrix();
			}
		}


		// Go Back button
		glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
		glPushMatrix();
		glTranslatef(401, 560, 0);
		glScalef(5.5/* * w / 1024*/, 1, 1);
		glEnable( GL_TEXTURE_2D );
		glEnable( GL_BLEND );
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindTexture( GL_TEXTURE_2D, menuTex[0].texID );
			glBegin(GL_QUADS);
				glTexCoord2f(0,1); glVertex2f(0,0);
				glTexCoord2f(0,0); glVertex2f(0,40);
				glTexCoord2f(1,0); glVertex2f(40,40);
				glTexCoord2f(1,1); glVertex2f(40,0);
			glEnd();
		glDisable( GL_BLEND );
		glDisable( GL_TEXTURE_2D );
		glPopMatrix();

		if(mouseX > 400 * w / 1024 && mouseX < 620 * w / 1024 && mouseY > 520 * h / 745 && mouseY < 560 * h / 745)
		{
			glLoadIdentity ();
			glPushAttrib(GL_ALL_ATTRIB_BITS);
				glColor3f(0.5f, 0.5f, 0.5f);
				printw (475, 587.5, 0, "Go Back");
			glPopAttrib();

			// When clicked
			if (mouseState == false)
			{
				// GO BACK TO MAIN MENU
				show_options = false;
				enable_options = false;
			}
			else
			{
			}
		}
		else
		{
			glLoadIdentity ();
			glPushAttrib(GL_ALL_ATTRIB_BITS);
				glColor3f(1, 1, 1);
				printw (475, 587.5, 0, "Go Back");
			glPopAttrib();
		}

		// Other text
		glLoadIdentity ();
		glPushAttrib(GL_ALL_ATTRIB_BITS);
			glColor3f(0.0f, 0.0f, 0.0f);
			printw (437.5, 190.0, 0, "OPTIONS MENU");
		glPopAttrib();

		glLoadIdentity ();
		glPushAttrib(GL_ALL_ATTRIB_BITS);
			glColor3f(0.0f, 0.0f, 0.0f);
			printw (455.0, 240.0, 0, "Music volume");
		glPopAttrib();

		glLoadIdentity ();
		glPushAttrib(GL_ALL_ATTRIB_BITS);
			glColor3f(0.0f, 0.0f, 0.0f);
			printw (432.5, 360.0, 0, "Mute/Unmute music");
		glPopAttrib();
	}
	else
	{
	}
}

void GameMenu::renderMenuBackground(void)
{
	// Render background image
	glEnable(GL_TEXTURE_2D);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture(GL_TEXTURE_2D, menuTex[1].texID );
		glPushMatrix();
			glBegin(GL_QUADS);
				int height = 100 * 1.333/1.5;
				glTexCoord2f(0,0); glVertex2f(0,800);
				glTexCoord2f(1,0); glVertex2f(1024,800);
				glTexCoord2f(1,1); glVertex2f(1024,0);
				glTexCoord2f(0,1); glVertex2f(0,0);				
			glEnd();
		glPopMatrix();
		glDisable(GL_BLEND);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void GameMenu::renderLogo(void)
{
	glEnable(GL_TEXTURE_2D);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	// Draw James logo
	glPushMatrix();
		glTranslatef(200, 75, 0);
		glScalef(3, 1.5, 1);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture(GL_TEXTURE_2D, menuTex[8].texID );
		glPushMatrix();
			glBegin(GL_QUADS);
				int height = 100 * 1.333/1.5;
				glTexCoord2f(0,0); glVertex2f(0,150);
				glTexCoord2f(1,0); glVertex2f(200,150);
				glTexCoord2f(1,1); glVertex2f(200,0);
				glTexCoord2f(0,1); glVertex2f(0,0);				
			glEnd();
		glPopMatrix();
		glDisable(GL_BLEND);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void GameMenu::renderStartButton()
{
	// Start game button
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		glPushMatrix();
		glTranslatef(400, 360, 0);
		glScalef(5.5, 1.5, 1);
		glEnable( GL_TEXTURE_2D );
		glEnable( GL_BLEND );
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindTexture( GL_TEXTURE_2D, menuTex[2].texID );
			glBegin(GL_QUADS);
				glTexCoord2f(0,1); glVertex2f(0,0);
				glTexCoord2f(0,0); glVertex2f(0,40);
				glTexCoord2f(1,0); glVertex2f(40,40);
				glTexCoord2f(1,1); glVertex2f(40,0);
			glEnd();
		glDisable( GL_BLEND );
		glDisable( GL_TEXTURE_2D );
		glPopMatrix();

		glLoadIdentity ();
		glPushAttrib(GL_ALL_ATTRIB_BITS);
			glColor3f(1.0f, 1.0f, 1.0f);
			printw (462.5, 397.5, 0, "Start game");
		glPopAttrib();

		if (mouseX > 312.5 * w /800 && mouseX < 485 * w / 800 && mouseY > 270 * h / 600 && mouseY < 315 * h / 600)
		{
			// Start game button MO
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			glPushMatrix();
			glTranslatef(400, 360, 0);
			glScalef(5.5, 1.5, 1);
			glEnable( GL_TEXTURE_2D );
			glEnable( GL_BLEND );
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				glBindTexture( GL_TEXTURE_2D, menuTex[3].texID );
				glBegin(GL_QUADS);
					glTexCoord2f(0,1); glVertex2f(0,0);
					glTexCoord2f(0,0); glVertex2f(0,40);
					glTexCoord2f(1,0); glVertex2f(40,40);
					glTexCoord2f(1,1); glVertex2f(40,0);
				glEnd();
			glDisable( GL_BLEND );
			glDisable( GL_TEXTURE_2D );
			glPopMatrix();

			glLoadIdentity ();
			glPushAttrib(GL_ALL_ATTRIB_BITS);
				glColor3f(1.0f, 1.0f, 1.0f);
				printw (462.5, 397.5, 0, "Start game");
			glPopAttrib();

				// When clicked
				if (mouseState == false && LMouse_down_boolean == false)
				{
					// START THE GAME
					/*showMenu = false;*/
					gameInit = true;
					LMouse_down_boolean = true;
				}
				else if (mouseState == true)
				{
					LMouse_down_boolean = false;
				}
		}
}

void GameMenu::renderOptionsButton(void)
{
	// Options button
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glTranslatef(400, 460, 0);
	glScalef(5.5, 1.5, 1);
	glEnable( GL_TEXTURE_2D );
	glEnable( GL_BLEND );
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture( GL_TEXTURE_2D, menuTex[2].texID );
	glBegin(GL_QUADS);
	glTexCoord2f(0,1); glVertex2f(0,0);
	glTexCoord2f(0,0); glVertex2f(0,40);
	glTexCoord2f(1,0); glVertex2f(40,40);
	glTexCoord2f(1,1); glVertex2f(40,0);
	glEnd();
	glDisable( GL_BLEND );
	glDisable( GL_TEXTURE_2D );
	glPopMatrix();

	glLoadIdentity();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glColor3f(1.0f, 1.0f, 1.0f);
	printw (475, 497.5, 0, "Options");
	glPopAttrib();

	// Options button MO
	if (mouseX > 312.5 * w /800 && mouseX < 485 * w / 800 && mouseY > 345 * h / 600 && mouseY < 390 * h / 600)
	{
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		glPushMatrix();
		glTranslatef(400, 460, 0);
		glScalef(5.5, 1.5, 1);
		glEnable( GL_TEXTURE_2D );
		glEnable( GL_BLEND );
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture( GL_TEXTURE_2D, menuTex[3].texID );
		glBegin(GL_QUADS);
		glTexCoord2f(0,1); glVertex2f(0,0);
		glTexCoord2f(0,0); glVertex2f(0,40);
		glTexCoord2f(1,0); glVertex2f(40,40);
		glTexCoord2f(1,1); glVertex2f(40,0);
		glEnd();
		glDisable( GL_BLEND );
		glDisable( GL_TEXTURE_2D );
		glPopMatrix();

		glLoadIdentity ();
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		glColor3f(1.0f, 1.0f, 1.0f);
		printw (475, 497.5, 0, "Options");
		glPopAttrib();

		// When clicked
		if (mouseState == false && LMouse_down_boolean == false)
		{
			enable_options = true;
			show_options = true;
			
			LMouse_down_boolean = true;
		}
		else if (mouseState == true)
		{
			LMouse_down_boolean = false;
		}

		
	}
	else if (mouseState == true)
	{
		LMouse_down_boolean = false;
	}
}

void GameMenu::renderExitButton()
{
	// Exit game button
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		glPushMatrix();
		glTranslatef(400, 625, 0);
		glScalef(5.5, 1.5, 1);
		glEnable( GL_TEXTURE_2D );
		glEnable( GL_BLEND );
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindTexture( GL_TEXTURE_2D, menuTex[2].texID );
			glBegin(GL_QUADS);
				glTexCoord2f(0,1); glVertex2f(0,0);
				glTexCoord2f(0,0); glVertex2f(0,40);
				glTexCoord2f(1,0); glVertex2f(40,40);
				glTexCoord2f(1,1); glVertex2f(40,0);
			glEnd();
		glDisable( GL_BLEND );
		glDisable( GL_TEXTURE_2D );
		glPopMatrix();

		glLoadIdentity ();
		glPushAttrib(GL_ALL_ATTRIB_BITS);
			glColor3f(1.0f, 1.0f, 1.0f);
			printw (450, 662.5, 0, "Quit the Game");
		glPopAttrib();

		if (mouseX > 312.5 * w /800 && mouseX < 485 * w / 800 && mouseY > 470 * h / 600 && mouseY < 515 * h / 600)
		{
			// Exit game button MO
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			glPushMatrix();
			glTranslatef(400, 625, 0);
			glScalef(5.5, 1.5, 1);
			glEnable( GL_TEXTURE_2D );
			glEnable( GL_BLEND );
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				glBindTexture( GL_TEXTURE_2D, menuTex[3].texID );
				glBegin(GL_QUADS);
					glTexCoord2f(0,1); glVertex2f(0,0);
					glTexCoord2f(0,0); glVertex2f(0,40);
					glTexCoord2f(1,0); glVertex2f(40,40);
					glTexCoord2f(1,1); glVertex2f(40,0);
				glEnd();
			glDisable( GL_BLEND );
			glDisable( GL_TEXTURE_2D );
			glPopMatrix();

			glLoadIdentity ();
			glPushAttrib(GL_ALL_ATTRIB_BITS);
				glColor3f(1.0f, 1.0f, 1.0f);
				printw (450, 662.5, 0, "Quit the Game");
			glPopAttrib();

			// When clicked
			if (mouseState == false)
			{
				exit(0);
			}
		}
}

bool GameMenu::getMusicMuted(void)
{
	return mute_music;
}

int GameMenu::getVolume(void)
{
	return volume;
}

void GameMenu::renderMenu(int mouseX, int mouseY, bool mouseState, int w, int h)
{
	this->mouseX = mouseX;
	this->mouseY = mouseY;
	this->mouseState = mouseState;
	this->w = w;
	this->h = h;

	renderMenuBackground();
	renderLogo();
	OptionsScreen();

	if (enable_options == false)
	{
		renderStartButton();
		renderOptionsButton();
		renderExitButton();
	}
	else
	{
	}
}