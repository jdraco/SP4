#include "HUD.h"


HUD::HUD(void)
	:	showHelp(false)
	,	showOptions(false)
	,	showInventory(false)
	,	LMouse_down_boolean(false)
	,	volume(70)
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
/*
bool HUD::LoadTGA(TextureImage *texture, char *filename)			// Loads A TGA File Into Memory
{    
	GLubyte		TGAheader[12]={0,0,2,0,0,0,0,0,0,0,0,0};	// Uncompressed TGA Header
	GLubyte		TGAcompare[12];								// Used To Compare TGA Header
	GLubyte		header[6];									// First 6 Useful Bytes From The Header
	GLuint		bytesPerPixel;								// Holds Number Of Bytes Per Pixel Used In The TGA File
	GLuint		imageSize;									// Used To Store The Image Size When Setting Aside Ram
	GLuint		temp;										// Temporary Variable
	GLuint		type=GL_RGBA;								// Set The Default GL Mode To RBGA (32 BPP)

	FILE *file = fopen(filename, "rb");						// Open The TGA File

	if(	file==NULL ||										// Does File Even Exist?
		fread(TGAcompare,1,sizeof(TGAcompare),file)!=sizeof(TGAcompare) ||	// Are There 12 Bytes To Read?
		memcmp(TGAheader,TGAcompare,sizeof(TGAheader))!=0				||	// Does The Header Match What We Want?
		fread(header,1,sizeof(header),file)!=sizeof(header))				// If So Read Next 6 Header Bytes
	{
		if (file == NULL)									// Did The File Even Exist? *Added Jim Strong*
			return false;									// Return False
		else
		{
			fclose(file);									// If Anything Failed, Close The File
			return false;									// Return False
		}
	}

	texture->width  = header[1] * 256 + header[0];			// Determine The TGA Width	(highbyte*256+lowbyte)
	texture->height = header[3] * 256 + header[2];			// Determine The TGA Height	(highbyte*256+lowbyte)

	if(	texture->width	<=0	||								// Is The Width Less Than Or Equal To Zero
		texture->height	<=0	||								// Is The Height Less Than Or Equal To Zero
		(header[4]!=24 && header[4]!=32))					// Is The TGA 24 or 32 Bit?
	{
		fclose(file);										// If Anything Failed, Close The File
		return false;										// Return False
	}

	texture->bpp	= header[4];							// Grab The TGA's Bits Per Pixel (24 or 32)
	bytesPerPixel	= texture->bpp/8;						// Divide By 8 To Get The Bytes Per Pixel
	imageSize		= texture->width*texture->height*bytesPerPixel;	// Calculate The Memory Required For The TGA Data

	texture->imageData=(GLubyte *)malloc(imageSize);		// Reserve Memory To Hold The TGA Data

	if(	texture->imageData==NULL ||							// Does The Storage Memory Exist?
		fread(texture->imageData, 1, imageSize, file)!=imageSize)	// Does The Image Size Match The Memory Reserved?
	{
		if(texture->imageData!=NULL)						// Was Image Data Loaded
			free(texture->imageData);						// If So, Release The Image Data

		fclose(file);										// Close The File
		return false;										// Return False
	}

	for(GLuint i=0; i<int(imageSize); i+=bytesPerPixel)		// Loop Through The Image Data
	{														// Swaps The 1st And 3rd Bytes ('R'ed and 'B'lue)
		temp=texture->imageData[i];							// Temporarily Store The Value At Image Data 'i'
		texture->imageData[i] = texture->imageData[i + 2];	// Set The 1st Byte To The Value Of The 3rd Byte
		texture->imageData[i + 2] = temp;					// Set The 3rd Byte To The Value In 'temp' (1st Byte Value)
	}

	fclose (file);											// Close The File

	// Build A Texture From The Data
	glGenTextures(1, &texture[0].texID);					// Generate OpenGL texture IDs

	glBindTexture(GL_TEXTURE_2D, texture[0].texID);			// Bind Our Texture
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// Linear Filtered
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	// Linear Filtered

	if (texture[0].bpp==24)									// Was The TGA 24 Bits
	{
		type=GL_RGB;										// If So Set The 'type' To GL_RGB
	}

	glTexImage2D(GL_TEXTURE_2D, 0, type, texture[0].width, texture[0].height, 0, type, GL_UNSIGNED_BYTE, texture[0].imageData);

	return true;											// Texture Building Went Ok, Return True
}
*/

void HUD::HelpScreen(void)
{
	// Help screen
	if (showHelp == true)
	{
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		glPushMatrix();
		glTranslatef(0, 50 * h / 600, 0);
		glScalef(20 * w / 800, 10.75 * h / 600, 1);
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
	}
}

void HUD::OptionsScreen(int mouseX,int mouseY, bool mouseState)
{
	if (showOptions == true)
	{
		// Options window
		glColor4f(0.2f, 0.2f, 0.2f, 0.95f);
		glPushMatrix();
		glTranslatef(250 * w / 800, 50 * h / 600, 0);
		glScalef(7.5 * w / 800, 11.75 * h / 600, 1);
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
		if (mouseX > 305 * w / 800 && mouseX < 335 * w / 800 && mouseY > 165 * h / 600 && mouseY < 190 * h / 600)
		{
			glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
			glPushMatrix();
			glTranslatef(300 * w / 800, 160 * h / 600, 0);
			glScalef(1, 1, 1);
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
			glTranslatef(300 * w / 800, 160 * h / 600, 0);
			glScalef(1, 1, 1);
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
		if(mouseX > 465 * w / 800 && mouseX < 495 * w / 800 && mouseY > 165 * h / 600 && mouseY < 195 * h / 600)
		{
			glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
			glPushMatrix();
			glTranslatef(460 * w / 800, 160 * h / 600, 0);
			glScalef(1, 1, 1);
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
			glTranslatef(460 * w / 800, 160 * h / 600, 0);
			glScalef(1, 1, 1);
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
				printw (392.5 * w / 800, 185.0 * h / 600, 0, "%.i", volume); // SHOW MUSIC VOLUME (WHEN MORE THAN 0)
			else
				printw (392.5 * w / 800, 185.0 * h / 600, 0, "0"); // SHOW MUSIC VOLUME (WHEN 0)
		
		glPopAttrib();

		// Mute/Unmute music button
		if (mutemusic == true)
		{
			if (mouseX > 380 * w / 800 && mouseX < 420 * w / 800 && mouseY > 290 * h / 600 && mouseY < 320 * h / 600)
			{
				glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
				glPushMatrix();
				glTranslatef(380 * w / 800, 285 * h / 600, 0);
				glScalef(1, 1, 1);
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
				glTranslatef(380 * w / 800, 285 * h / 600, 0);
				glScalef(1, 1, 1);
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
			if (mouseX > 380 * w / 800 && mouseX < 420 * w / 800 && mouseY > 290 * h / 600 && mouseY < 320 * h / 600)
			{
				glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
				glPushMatrix();
				glTranslatef(380 * w / 800, 285 * h / 600, 0);
				glScalef(1, 1, 1);
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
				glTranslatef(380 * w / 800, 285 * h / 600, 0);
				glScalef(1, 1, 1);
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
		glTranslatef(291 * w / 800, 400 * h / 600, 0);
		glScalef(5.5 * w / 800, 1, 1);
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

		if(mouseX > 290 * w / 800 && mouseX < 511 * w / 800 && mouseY > 399 * h / 600 && mouseY < 440 * h / 600)
		{
			glLoadIdentity ();
			glPushAttrib(GL_ALL_ATTRIB_BITS);
				glColor3f(0.5f, 0.5f, 0.5f);
				printw (355 * w / 800, 427.5 * h / 600, 0, "Resume Game");
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
				printw (355 * w / 800, 427.5 * h / 600, 0, "Resume Game");
			glPopAttrib();
		}


		// Quit to Main Menu button
		glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
		glPushMatrix();
		glTranslatef(291 * w / 800, 460 * h / 600, 0);
		glScalef(5.5 * w / 800, 1, 1);
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

		if(mouseX > 290 * w / 800 && mouseX < 511 * w / 800 && mouseY > 459 * h / 600 && mouseY < 500 * h / 600)
		{
			glLoadIdentity ();
			glPushAttrib(GL_ALL_ATTRIB_BITS);
				glColor3f(0.5f, 0.5f, 0.5f);
				printw (340 * w / 800, 487.5 * h / 600, 0, "Quit to Main Menu");
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
				printw (340 * w / 800, 487.5 * h / 600, 0, "Quit to Main Menu");
			glPopAttrib();
		}

		// Other text
		glLoadIdentity ();
		glPushAttrib(GL_ALL_ATTRIB_BITS);
			glColor3f(0.0f, 0.0f, 0.0f);
			printw (340.0 * w / 800, 90.0 * h / 600, 0, "OPTIONS MENU");
		glPopAttrib();

		glLoadIdentity ();
		glPushAttrib(GL_ALL_ATTRIB_BITS);
			glColor3f(0.0f, 0.0f, 0.0f);
			printw (355.0 * w / 800, 140.0 * h / 600, 0, "Music volume");
		glPopAttrib();

		glLoadIdentity ();
		glPushAttrib(GL_ALL_ATTRIB_BITS);
			glColor3f(0.0f, 0.0f, 0.0f);
			printw (332.5 * w / 800, 260.0 * h / 600, 0, "Mute/Unmute music");
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
		glTranslatef(220 * w / 800, 120 * h / 600, 0);
		glScalef(9 * w / 800, 8.4 * h / 600, 1);
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
			printw (370 * w / 800, 150 * h / 600, 0, "Inventory");
		glPopAttrib();


		// Close inventory window button
		glColor4f(0.6f, 0.1f, 0.1f, 1.0f);
		glPushMatrix();
		glTranslatef(545 * w / 800, 132 * h / 600, 0);
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

		if(mouseX > 545 * w / 800 && mouseX < 570 * w / 800 && mouseY > 130 * h / 600 && mouseY < 157.5 * h / 600)
		{
			glLoadIdentity();
			glPushAttrib(GL_ALL_ATTRIB_BITS);
				glColor3f(0.5f, 0.5f, 0.5f);
				printw (553 * w / 800, 150 * h / 600, 0, "X");
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
				printw (553 * w / 800, 150 * h / 600, 0, "X");
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
				glTranslatef((245 + (65 * j)) * w / 800, (175 + (65 * i)) * h / 600, 0);
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

				if ((mouseX > (245 + (65 * j)) * w / 800) && (mouseX < (295 + (65 * j)) * w / 800) && (mouseY > (175 + (65 * i)) * h / 600) && (mouseY < (225 + (65 * i)) * h / 600))
				{
					glLoadIdentity();
					glPushAttrib(GL_ALL_ATTRIB_BITS);
						glColor3f(1, 1, 1);
						printw(370 * w / 800, 445 * h / 600, 0, "%s", item_name.c_str());
					glPopAttrib();

					// When clicked
					if (mouseState == false && LMouse_down_boolean == false)
					{
						theInventory.setSlotItem(slot_itr, 0);

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
		printw (10.0 * w / 800, 505.0 * h / 600, 0, "Health - ");
	glPopAttrib();

	if (health >= 70)
	{
		glColor4f(0.0f, 1.0f, 0.0f, 1.0f);

		glPushAttrib(GL_ALL_ATTRIB_BITS);
			printw (85 * w / 800, 505.0 * h / 600, 0, "Good Condition");
		glPopAttrib();
	}
	else if (health >= 30 && health < 70)
	{
		glColor4f(1.0f, 1.0f, 0.0f, 1.0f);

		glPushAttrib(GL_ALL_ATTRIB_BITS);
			printw (85 * w / 800, 505.0 * h / 600, 0, "Injured");
		glPopAttrib();
	}
	else
	{
		glColor4f(1.0f, 0.0f, 0.0f, 1.0f);

		glPushAttrib(GL_ALL_ATTRIB_BITS);
			printw (85 * w / 800, 505.0 * h / 600, 0, "Dying");
		glPopAttrib();
	}

	glPushMatrix();
	glTranslatef(10 * w / 800, 510 * h / 600, 0);
	glEnable( GL_TEXTURE_2D );
	glEnable( GL_BLEND );
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture( GL_TEXTURE_2D, HUDtex[0].texID );
		glBegin(GL_QUADS);
			glTexCoord2f(0,1); glVertex2f(0,5);
			glTexCoord2f(0,0); glVertex2f(0,25);
			glTexCoord2f(1,0); glVertex2f(health*2.1,25);
			glTexCoord2f(1,1); glVertex2f(health*2.1,5);
		glEnd();
	glDisable( GL_BLEND );
	glDisable( GL_TEXTURE_2D );
	glPopMatrix();

	glPushAttrib(GL_ALL_ATTRIB_BITS);
		printw (((health*2.1) + 15) * w / 800, 531.5 * h / 600, 0, "%i", health);
	glPopAttrib();

	
}

void HUD::drawDetectionStatus(void)
{
	glLoadIdentity ();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
		glColor3f(0.0f, 0.0f, 0.0f);
		printw (10.0 * w / 800, 565.0 * h / 600, 0, "Detection Status:");
	glPopAttrib();

	// Undetected
	if (detection_state == 0)
	{
		glPushAttrib(GL_ALL_ATTRIB_BITS);
			glColor3f(0.0f, 1.0f, 0.0f);
			printw (10.0 * w / 800, 590.0 * h / 600, 0, "Undetected");
		glPopAttrib();
	}
	// Detected
	else
	{
		glPushAttrib(GL_ALL_ATTRIB_BITS);
			glColor3f(1.0f, 0.0f, 0.0f);
			printw (10.0 * w / 800, 590.0 * h / 600, 0, "Detected");
		glPopAttrib();
	}
}

void HUD::renderLevel(void)
{
	glLoadIdentity ();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
		glColor3f(0.0f, 0.0f, 0.0f);
		printw (370 * w / 800, 32.5 * h / 600, 0, "Level %.i", level);
	glPopAttrib();
}

void HUD::renderCurrentWeapon(void)
{
	glLoadIdentity ();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
		glColor3f(0.0f, 0.0f, 0.0f);
		printw (337.5 * w / 800, 510.0 * h / 600, 0, "Current weapon");
	glPopAttrib();
}

void HUD::renderHelpButton(int mouseX,int mouseY, bool mouseState, int w, int h)
{
	// When mouse over
	if(mouseX > (700 * w / 800) && mouseX < (740 * w / 800) && mouseY > (5 * h / 600) && mouseY < (45 * h / 600) && showInventory != true)
	{
		glPushMatrix();
		glTranslatef(700 * w / 800, 5 * h / 600, 0);
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
		glTranslatef(700 * w / 800, 5 * h / 600, 0);
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
	if(mouseX > (750 * w / 800) && mouseX < (790 * w / 800) && mouseY > (5 * h / 600) && mouseY < (45 * h / 600) && showHelp != true && showInventory != true)
	{
		glPushMatrix();
		glTranslatef(750 * w / 800, 5 * h / 600, 0);
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
		glTranslatef(750 * w / 800, 5 * h / 600, 0);
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
	if(mouseX > (620 * w / 800) && mouseX < (705 * w / 800) && mouseY > (490 * h / 600) && mouseY < (585 * h / 600) && showHelp != true)
	{
		glPushMatrix();
		glTranslatef(610 * w / 800, 487.5 * h / 600, 0);
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
		glTranslatef(610 * w / 800, 487.5 * h / 600, 0);
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
	glScalef(20 * w / 800, 1.25 * h / 600, 1);
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
	glTranslatef(0, 480 * h / 600, 0);
	glScalef(20 * w / 800, 3 * h / 600, 1);
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
	glTranslatef(282.5 * w / 800, 480 * h / 600, 0);
	glScalef(6 * w / 800, 3 * h / 600, 1);
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

	HelpScreen();
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