#include "Inventory.h"


Inventory::Inventory(void)
	:	num_of_items(0)
{
	font_style = GLUT_BITMAP_HELVETICA_18;

	LoadTGA( &item_tex[ 0 ], "Texture/HUD/transparent.tga");
	LoadTGA( &item_tex[ 1 ], "Texture/HUD/knife.tga");
	LoadTGA( &item_tex[ 2 ], "Texture/HUD/bandages.tga");

	for (int i = 0; i < MAX_ITEMS; i++)
	{
		slot[i].item_id = EMPTY;
		slot[i].has_been_rendered = false;
	}
}


Inventory::~Inventory(void)
{
}

void Inventory::printw (float x, float y, float z, char* format, ...)
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

void Inventory::addItem(int item_id)
{
	bool item_added = false;

	switch (item_id)
	{
		case KNIFE:
		for (int i = 0; i < MAX_ITEMS; i++)
		{
			if (slot[i].item_id == EMPTY && item_added == false)
			{
				slot[i].item_id = KNIFE;
				item_added = true;
			}
		}
		break;

		case BANDAGES:
		for (int i = 0; i < MAX_ITEMS; i++)
		{
			if (slot[i].item_id == EMPTY && item_added == false)
			{
				slot[i].item_id = BANDAGES;
				item_added = true;
			}
		}
		break;

		default:
		break;
	}
}

bool Inventory::addItem(int set,int item_id)
{
	if(set < MAX_ITEMS)
		return false;
	slot[set].item_id = item_id;

	return true;
}

void Inventory::emptySlot(int slot_no)
{
	slot[slot_no].item_id = EMPTY;
}

int Inventory::getSlotItem(int slot_no)
{
	return slot[slot_no].item_id;
}

void Inventory::setSlotItem(int slot_no, int item_id)
{
	this->slot[slot_no].item_id = item_id;
}

std::string Inventory::getSlotItemName(int slot_no)
{
	return slot[slot_no].item_name;
}

void Inventory::renderInventorySlot(int slot_no)
{
	if (slot[slot_no].has_been_rendered == false)
	{
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		//glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture(GL_TEXTURE_2D, item_tex[getSlotItem(slot_no)].texID);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 1); glVertex2f(0, 0);
		glTexCoord2f(0, 0); glVertex2f(0, 50);
		glTexCoord2f(1, 0); glVertex2f(50, 50);
		glTexCoord2f(1, 1); glVertex2f(50, 0);
		glEnd();
		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();

		slot[slot_no].has_been_rendered = true;
	}

	for (int i = 0; i < MAX_ITEMS; i++)
	{
		switch (slot[i].item_id)
		{
		case KNIFE:
			slot[i].item_name = "Knife";
			break;

		case BANDAGES:
			slot[i].item_name = "Bandages";
			break;

		default:
			break;
		}
	}
}