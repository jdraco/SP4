#include "HUD.h"


HUD::HUD(void)
	:	showHelp(false)
	,	showOptions(false)
	,	showInventory(false)
	,	LMouse_down_boolean(false)
	,	volume(70)
	,	CURRENT_WEAPON(NONE)
{
	LoadTGA( &HUDtex[ 0 ], "Texture/HUD/white.tga");
	LoadTGA( &HUDtex[ 1 ], "Texture/HUD/optionsbutton.tga");
	LoadTGA( &HUDtex[ 2 ], "Texture/HUD/optionsbuttonMO.tga");
	LoadTGA( &HUDtex[ 3 ], "Texture/HUD/helpbutton.tga");
	LoadTGA( &HUDtex[ 4 ], "Texture/HUD/helpbuttonMO.tga");
	LoadTGA( &HUDtex[ 5 ], "Texture/HUD/minus.tga");
	LoadTGA( &HUDtex[ 6 ], "Texture/HUD/plus.tga");
	LoadTGA( &HUDtex[ 7 ], "Texture/HUD/unmutedbutton.tga");
	LoadTGA( &HUDtex[ 8 ], "Texture/HUD/mutedbutton.tga");
	LoadTGA( &HUDtex[ 9 ], "Texture/HUD/inventorybutton.tga");
	LoadTGA( &HUDtex[ 10 ], "Texture/HUD/inventorybuttonMO.tga");
	LoadTGA( &HUDtex[ 11 ], "Texture/HUD/knife.tga");

	font_style = GLUT_BITMAP_HELVETICA_18;
}

HUD::~HUD(void)
{
}

void HUD::printw (float x, float y, float z, char* format, ...)
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

void HUD::HelpScreen(int mouseX,int mouseY, bool mouseState)
{
	// Help screen
	if (showHelp == true)
	{
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		glPushMatrix();
		glTranslatef(0, 62.5, 0);
		glScalef(25.6/* * w / 1024*/, 15.35/* * h / 745*/, 1);
		glEnable( GL_TEXTURE_2D );
		glEnable( GL_BLEND );
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindTexture( GL_TEXTURE_2D, HUDtex[0].texID );
			glBegin(GL_QUADS);
				glTexCoord2f(0,1); glVertex2f(0,0);
				glTexCoord2f(0,0); glVertex2f(0,40);
				glTexCoord2f(1,0); glVertex2f(40,40);
				glTexCoord2f(1,1); glVertex2f(40,0);
			glEnd();
		glDisable( GL_BLEND );
		glDisable( GL_TEXTURE_2D );
		glPopMatrix();

		// Close help window button
		glColor4f(0.6f, 0.1f, 0.1f, 1.0f);
		glPushMatrix();
		glTranslatef(985, 77.5, 0);
		glEnable( GL_TEXTURE_2D );
		glEnable( GL_BLEND );
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindTexture( GL_TEXTURE_2D, HUDtex[0].texID );
			glBegin(GL_QUADS);
				glTexCoord2f(0,1); glVertex2f(0,0);
				glTexCoord2f(0,0); glVertex2f(0,25);
				glTexCoord2f(1,0); glVertex2f(25,25);
				glTexCoord2f(1,1); glVertex2f(25,0);
			glEnd();
		glDisable( GL_BLEND );
		glDisable( GL_TEXTURE_2D );
		glPopMatrix();

		if(mouseX > 985 * w / 1024 && mouseX < 1010 * w / 1024 && mouseY > 70 * h / 745 && mouseY < 95 * h / 745)
		{
			glLoadIdentity();
			glPushAttrib(GL_ALL_ATTRIB_BITS);
				glColor3f(0.5f, 0.5f, 0.5f);
				printw (992, 97.5, 0, "X");
			glPopAttrib();

			// When clicked
			if (mouseState == false)
			{
				showHelp = false;
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
				printw (992, 97.5, 0, "X");
			glPopAttrib();
		}
	}
}

void HUD::OptionsScreen(int mouseX,int mouseY, bool mouseState)
{
	if (showOptions == true)
	{
		// Options window
		glColor4f(0.2f, 0.2f, 0.2f, 0.95f);
		glPushMatrix();
		glTranslatef(360, 150, 0);
		glScalef(7.5/* * w / 1024*/, 12.25 * h / 745, 1);
		glEnable( GL_TEXTURE_2D );
		glEnable( GL_BLEND );
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindTexture( GL_TEXTURE_2D, HUDtex[0].texID );
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
				glBindTexture( GL_TEXTURE_2D, HUDtex[5].texID );
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
				glBindTexture( GL_TEXTURE_2D, HUDtex[5].texID );
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
				glBindTexture( GL_TEXTURE_2D, HUDtex[6].texID );
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
				glBindTexture( GL_TEXTURE_2D, HUDtex[6].texID );
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
		if (mutemusic == true)
		{
			if (mouseX > 490 * w / 1024 && mouseX < 530 * w / 1024 && mouseY > 360 * h / 745 && mouseY < 400 * h / 745)
			{
				glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
				glPushMatrix();
				glTranslatef(490, 385, 0);
				glEnable( GL_TEXTURE_2D );
				glEnable( GL_BLEND );
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					glBindTexture( GL_TEXTURE_2D, HUDtex[8].texID );
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
					mutemusic = false;
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
					glBindTexture( GL_TEXTURE_2D, HUDtex[8].texID );
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
					glBindTexture( GL_TEXTURE_2D, HUDtex[7].texID );
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
					mutemusic = true;
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
					glBindTexture( GL_TEXTURE_2D, HUDtex[7].texID );
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

		// Resume Game button
		glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
		glPushMatrix();
		glTranslatef(401, 500, 0);
		glScalef(5.5/* * w / 1024*/, 1, 1);
		glEnable( GL_TEXTURE_2D );
		glEnable( GL_BLEND );
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindTexture( GL_TEXTURE_2D, HUDtex[0].texID );
			glBegin(GL_QUADS);
				glTexCoord2f(0,1); glVertex2f(0,0);
				glTexCoord2f(0,0); glVertex2f(0,40);
				glTexCoord2f(1,0); glVertex2f(40,40);
				glTexCoord2f(1,1); glVertex2f(40,0);
			glEnd();
		glDisable( GL_BLEND );
		glDisable( GL_TEXTURE_2D );
		glPopMatrix();

		if(mouseX > 400 * w / 1024 && mouseX < 620 * w / 1024 && mouseY > 465 * h / 745 && mouseY < 505 * h / 745)
		{
			glLoadIdentity ();
			glPushAttrib(GL_ALL_ATTRIB_BITS);
				glColor3f(0.5f, 0.5f, 0.5f);
				printw (455, 527.5, 0, "Resume Game");
			glPopAttrib();

			// When clicked
			if (mouseState == false)
			{
				showOptions = false;
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
				printw (455, 527.5, 0, "Resume Game");
			glPopAttrib();
		}


		// Quit to Main Menu button
		glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
		glPushMatrix();
		glTranslatef(401, 560, 0);
		glScalef(5.5/* * w / 1024*/, 1, 1);
		glEnable( GL_TEXTURE_2D );
		glEnable( GL_BLEND );
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindTexture( GL_TEXTURE_2D, HUDtex[0].texID );
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
				printw (435, 587.5, 0, "Quit to Main Menu");
			glPopAttrib();

			// When clicked
			if (mouseState == false)
			{
				// EXIT TO MAIN MENU
				//showMenu = true;
				//showOptions = false;
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
				printw (435, 587.5, 0, "Quit to Main Menu");
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

void HUD::InventoryScreen(int mouseX,int mouseY, bool mouseState, Inventory theInventory)
{
	if (showInventory == true)
	{
		// Inventory window
		glColor4f(0.2f, 0.2f, 0.2f, 1.0f);
		glPushMatrix();
		glTranslatef(330, 200, 0);
		glScalef(9/* * w / 1024*/, 8.75 * h / 745, 1);
		glEnable( GL_TEXTURE_2D );
		glEnable( GL_BLEND );
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindTexture( GL_TEXTURE_2D, HUDtex[0].texID );
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
			glColor3f(1, 1, 1);
			printw (465, 230, 0, "Inventory");
		glPopAttrib();


		// Close inventory window button
		glColor4f(0.6f, 0.1f, 0.1f, 1.0f);
		glPushMatrix();
		glTranslatef(655, 212, 0);
		glEnable( GL_TEXTURE_2D );
		glEnable( GL_BLEND );
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindTexture( GL_TEXTURE_2D, HUDtex[0].texID );
			glBegin(GL_QUADS);
				glTexCoord2f(0,1); glVertex2f(0,0);
				glTexCoord2f(0,0); glVertex2f(0,25);
				glTexCoord2f(1,0); glVertex2f(25,25);
				glTexCoord2f(1,1); glVertex2f(25,0);
			glEnd();
		glDisable( GL_BLEND );
		glDisable( GL_TEXTURE_2D );
		glPopMatrix();

		if(mouseX > 655 * w / 1024 && mouseX < 680 * w / 1024 && mouseY > 202 * h / 745 && mouseY < 227 * h / 745)
		{
			glLoadIdentity();
			glPushAttrib(GL_ALL_ATTRIB_BITS);
				glColor3f(0.5f, 0.5f, 0.5f);
				printw (662, 231, 0, "X");
			glPopAttrib();

			// When clicked
			if (mouseState == false)
			{
				showInventory = false;
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
				printw (662, 231, 0, "X");
			glPopAttrib();
		}


		// Inventory slots
		int slot_itr = 0;

		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				glColor4f(0.35f, 0.35f, 0.35f, 1.0f);
				glPushMatrix();
				glTranslatef(355 + (65 * j), 255 + (65 * i), 0);
				glEnable( GL_TEXTURE_2D );
				glEnable( GL_BLEND );
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					glBindTexture( GL_TEXTURE_2D, HUDtex[0].texID );
					glBegin(GL_QUADS);
						glTexCoord2f(0,1); glVertex2f(0,0);
						glTexCoord2f(0,0); glVertex2f(0,50);
						glTexCoord2f(1,0); glVertex2f(50,50);
						glTexCoord2f(1,1); glVertex2f(50,0);
					glEnd();
				glDisable( GL_BLEND );
				glDisable( GL_TEXTURE_2D );
				//glPopMatrix();

				theInventory.renderInventorySlot(slot_itr);
				

				// Mouse over inventory item slot
				std::string item_name;
				item_name = theInventory.getSlotItemName(slot_itr);

				if ((mouseX > (355 + (65 * j)) * w / 1024) && (mouseX < (405 + (65 * j)) * w / 1024) && (mouseY > (240 + (65 * i)) * h / 745) && (mouseY < (290 + (65 * i)) * h / 745))
				{
					glLoadIdentity();
					glPushAttrib(GL_ALL_ATTRIB_BITS);
						glColor3f(1, 1, 1);
						printw(480, 525, 0, "%s", item_name.c_str());
					glPopAttrib();

					// When clicked
					if (mouseState == false && LMouse_down_boolean == false)
					{
						theInventory.emptySlot(slot_itr);
						//theInventory.setSlotItem(slot_itr, 0);

						LMouse_down_boolean = true;
					}
					else if (mouseState == true)
					{
						LMouse_down_boolean = false;
					}
				}


				slot_itr++;
			}
		}
	}
}

void HUD::drawHealthMeter(void)
{
	glLoadIdentity ();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
		glColor3f(0.0f, 0.0f, 0.0f);
		printw (110.0, 700.0, 0, "Health -");
	glPopAttrib();

	if (health >= 70)
	{
		glColor4f(0.0f, 1.0f, 0.0f, 1.0f);

		glPushAttrib(GL_ALL_ATTRIB_BITS);
			printw (185, 700.0, 0, "Good Condition");
		glPopAttrib();
	}
	else if (health >= 30 && health < 70)
	{
		glColor4f(1.0f, 1.0f, 0.0f, 1.0f);

		glPushAttrib(GL_ALL_ATTRIB_BITS);
			printw (185, 700.0, 0, "Injured");
		glPopAttrib();
	}
	else
	{
		glColor4f(1.0f, 0.0f, 0.0f, 1.0f);

		glPushAttrib(GL_ALL_ATTRIB_BITS);
			printw (185, 700.0, 0, "Dying");
		glPopAttrib();
	}

	glPushMatrix();
	glTranslatef(95, 705, 0);
	glEnable( GL_TEXTURE_2D );
	glEnable( GL_BLEND );
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture( GL_TEXTURE_2D, HUDtex[0].texID );
		glBegin(GL_QUADS);
			glTexCoord2f(0,1); glVertex2f(0,5);
			glTexCoord2f(0,0); glVertex2f(0,25);
			glTexCoord2f(1,0); glVertex2f(health*2.25,25);
			glTexCoord2f(1,1); glVertex2f(health*2.25,5);
		glEnd();
	glDisable( GL_BLEND );
	glDisable( GL_TEXTURE_2D );
	glPopMatrix();

	glPushAttrib(GL_ALL_ATTRIB_BITS);
		printw (((health*2.25) + 100), 726.5, 0, "%i", health);
	glPopAttrib();

	
}

void HUD::drawDetectionStatus(void)
{
	glLoadIdentity ();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
		glColor3f(0.0f, 0.0f, 0.0f);
		printw (125.0, 760.0, 0, "Detection Status:");
	glPopAttrib();

	// Undetected
	if (detection_state == 0)
	{
		glPushAttrib(GL_ALL_ATTRIB_BITS);
			glColor3f(0.0f, 1.0f, 0.0f);
			printw (145.0, 785.0, 0, "Undetected");
		glPopAttrib();
	}
	// Detected
	else
	{
		glPushAttrib(GL_ALL_ATTRIB_BITS);
			glColor3f(1.0f, 0.0f, 0.0f);
			printw (145.0, 785.0, 0, "Detected");
		glPopAttrib();
	}
}

void HUD::renderLevel(void)
{
	glLoadIdentity ();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
		glColor3f(0.0f, 0.0f, 0.0f);
		printw (475, 40, 0, "Level %.i", level);
	glPopAttrib();
}

void HUD::renderCurrentWeapon(void)
{
	// Display literal "Current weapon" text
	glLoadIdentity ();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
		glColor3f(0.0f, 0.0f, 0.0f);
		printw (432.5, 700.0, 0, "Current weapon");
	glPopAttrib();

	// Display current weapon image
	switch (CURRENT_WEAPON)
	{
		case KNIFE_HUD:
			glPushMatrix();
			glTranslatef(455, 710, 0);
			glEnable( GL_TEXTURE_2D );
			glEnable( GL_BLEND );
				glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				glBindTexture( GL_TEXTURE_2D, HUDtex[11].texID );
				glBegin(GL_QUADS);
					glTexCoord2f(0,1); glVertex2f(0,0);
					glTexCoord2f(0,0); glVertex2f(0,85);
					glTexCoord2f(1,0); glVertex2f(85,85);
					glTexCoord2f(1,1); glVertex2f(85,0);
				glEnd();
			glDisable( GL_BLEND );
			glDisable( GL_TEXTURE_2D );
			glPopMatrix();
			break;

		default:
			break;
	}
}

void HUD::renderHelpButton(int mouseX,int mouseY, bool mouseState, int w, int h)
{
	// When mouse over
	if(mouseX > (850 * w / 1024) && mouseX < (900 * w / 1024) && mouseY > (5 * h / 745) && mouseY < (55 * h / 745) && showInventory != true)
	{
		glPushMatrix();
		glTranslatef(850, 5, 0);
		glScalef(1.3 * w / 1024, 1.3 * h / 745, 1);
		glEnable( GL_TEXTURE_2D );
		glEnable( GL_BLEND );
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindTexture( GL_TEXTURE_2D, HUDtex[4].texID );
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
			if (showHelp == false)
				showHelp = true;
			else showHelp = false;

			LMouse_down_boolean = true;
		}
		else if (mouseState == true)
		{
			LMouse_down_boolean = false;
		}
	}
	else
	{
		glPushMatrix();
		glTranslatef(850, 5, 0);
		glScalef(1.3 * w / 1024, 1.3 * h / 745, 1);
		glEnable( GL_TEXTURE_2D );
		glEnable( GL_BLEND );
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindTexture( GL_TEXTURE_2D, HUDtex[3].texID );
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

void HUD::renderOptionsButton(int mouseX,int mouseY, bool mouseState, int w, int h)
{
	// When mouse over
	if(mouseX > (940 * w / 1024) && mouseX < (990 * w / 1024) && mouseY > (5 * h / 745) && mouseY < (55 * h / 745) && showHelp != true && showInventory != true)
	{
		glPushMatrix();
		glTranslatef(940, 5, 0);
		glScalef(1.3 * w / 1024, 1.3 * h / 745, 1);
		glEnable( GL_TEXTURE_2D );
		glEnable( GL_BLEND );
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindTexture( GL_TEXTURE_2D, HUDtex[2].texID );
			glBegin(GL_QUADS);
				glTexCoord2f(0,1); glVertex2f(0,0);
				glTexCoord2f(0,0); glVertex2f(0,40);
				glTexCoord2f(1,0); glVertex2f(40,40);
				glTexCoord2f(1,1); glVertex2f(40,0);
			glEnd();
		glDisable( GL_BLEND );
		glDisable( GL_TEXTURE_2D );
		glPopMatrix();

		if (mouseState == false && LMouse_down_boolean == false)
		{
			if (showOptions == false)
				showOptions = true;
			else showOptions = false;

			LMouse_down_boolean = true;
		}
		else if (mouseState == true)
		{
			LMouse_down_boolean = false;
		}
	}
	else
	{
		glPushMatrix();
		glTranslatef(940, 5, 0);
		glScalef(1.3 * w / 1024, 1.3 * h / 745, 1);
		glEnable( GL_TEXTURE_2D );
		glEnable( GL_BLEND );
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindTexture( GL_TEXTURE_2D, HUDtex[1].texID );
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

void HUD::renderInventoryButton(int mouseX,int mouseY, bool mouseState, int w, int h)
{
	// When mouse over
	if(mouseX > (770 * w / 1024) && mouseX < (870 * w / 1024) && mouseY > (630 * h / 745) && mouseY < (730 * h / 745) && showHelp != true)
	{
		glPushMatrix();
		glTranslatef(770, 685, 0);
		glEnable( GL_TEXTURE_2D );
		glEnable( GL_BLEND );
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindTexture( GL_TEXTURE_2D, HUDtex[10].texID );
			glBegin(GL_QUADS);
				glTexCoord2f(0,1); glVertex2f(0,0);
				glTexCoord2f(0,0); glVertex2f(0,105);
				glTexCoord2f(1,0); glVertex2f(105,105);
				glTexCoord2f(1,1); glVertex2f(105,0);
			glEnd();
		glDisable( GL_BLEND );
		glDisable( GL_TEXTURE_2D );
		glPopMatrix();

		// When clicked
		if (mouseState == false && LMouse_down_boolean == false)
		{
			if (showInventory == false)
				showInventory = true;
			else
				showInventory = false;

			LMouse_down_boolean = true;
		}
		else if (mouseState == true)
		{
			LMouse_down_boolean = false;
		}
	}
	else
	{
		glPushMatrix();
		glTranslatef(770, 685, 0);
		glEnable( GL_TEXTURE_2D );
		glEnable( GL_BLEND );
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindTexture( GL_TEXTURE_2D, HUDtex[9].texID );
			glBegin(GL_QUADS);
				glTexCoord2f(0,1); glVertex2f(0,0);
				glTexCoord2f(0,0); glVertex2f(0,105);
				glTexCoord2f(1,0); glVertex2f(105,105);
				glTexCoord2f(1,1); glVertex2f(105,0);
			glEnd();
		glDisable( GL_BLEND );
		glDisable( GL_TEXTURE_2D );
		glPopMatrix();
	}
}

void HUD::renderMisc(void)
{
	// Top bar
	glPushMatrix();
	glScalef(25.6 * w / 1024, 1.6 * h / 745, 1);
	glEnable( GL_TEXTURE_2D );
	glEnable( GL_BLEND );
		glColor4f(0.3f, 0.3f, 0.3f, 0.85f);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture( GL_TEXTURE_2D, HUDtex[0].texID );
		glBegin(GL_QUADS);
			glTexCoord2f(0,1); glVertex2f(0,0);
			glTexCoord2f(0,0); glVertex2f(0,40);
			glTexCoord2f(1,0); glVertex2f(40,40);
			glTexCoord2f(1,1); glVertex2f(40,0);
		glEnd();
	glDisable( GL_BLEND );
	glDisable( GL_TEXTURE_2D );
	glPopMatrix();

	// Bottom bar
	glPushMatrix();
	glTranslatef(0, 675, 0);
	glScalef(25.6 * w / 1024, 3.3 * h / 745, 1);
	glEnable( GL_TEXTURE_2D );
	glEnable( GL_BLEND );
		glColor4f(0.3f, 0.3f, 0.3f, 0.85f);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture( GL_TEXTURE_2D, HUDtex[0].texID );
		glBegin(GL_QUADS);
			glTexCoord2f(0,1); glVertex2f(0,0);
			glTexCoord2f(0,0); glVertex2f(0,40);
			glTexCoord2f(1,0); glVertex2f(40,40);
			glTexCoord2f(1,1); glVertex2f(40,0);
		glEnd();
	glDisable( GL_BLEND );
	glDisable( GL_TEXTURE_2D );
	glPopMatrix();

	// Mid-bottom bar
	glPushMatrix();
	glTranslatef(380, 675, 0);
	glScalef(6 * w / 1024, 3.3 * h / 745, 1);
	glEnable( GL_TEXTURE_2D );
	glEnable( GL_BLEND );
		glColor4f(0.2f, 0.2f, 0.2f, 0.9f);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture( GL_TEXTURE_2D, HUDtex[0].texID );
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

void HUD::renderHUD (int health, int detection_state, int level, int mouseX, int mouseY, bool mouseState, int volume, int w, int h, Inventory theInventory)
{
	if (health <= 100 && health >= 0)
		this->health = health;
	else if (health > 100) 
		this->health = 100;
	else if (health < 0)
		this->health = 0;

	this->detection_state = detection_state;
	this->level = level;

	this->w = w;
	this->h = h;

	this->theInventory = theInventory;

	HelpScreen(mouseX, mouseY, mouseState);
	OptionsScreen(mouseX, mouseY, mouseState);
	InventoryScreen(mouseX, mouseY, mouseState, theInventory);

	if (showOptions != true)
	{
		renderMisc();

		drawHealthMeter ();
		drawDetectionStatus();

		renderCurrentWeapon();
		renderLevel();
		renderHelpButton(mouseX, mouseY, mouseState, w, h);
		renderOptionsButton(mouseX, mouseY, mouseState, w, h);
		renderInventoryButton(mouseX, mouseY, mouseState, w, h);
	}
}