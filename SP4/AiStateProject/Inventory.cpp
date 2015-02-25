#include "Inventory.h"
#include "PlayerInfo.h"


Inventory::Inventory(void)
	:	num_of_items(0)
	,	craft_in_first_slot(true)
{
	font_style = GLUT_BITMAP_HELVETICA_18;

	LoadTGA( &item_tex[ 0 ], "Texture/Inventory/transparent.tga");
	LoadTGA( &item_tex[ 1 ], "Texture/Inventory/bandages.tga");
	LoadTGA( &item_tex[ 2 ], "Texture/Inventory/cloth.tga");
	LoadTGA( &item_tex[ 3 ], "Texture/Inventory/alcohol.tga");
	LoadTGA( &item_tex[ 4 ], "Texture/Inventory/machete.tga");
	LoadTGA( &item_tex[ 5 ], "Texture/Inventory/broken_wooden_handle.tga");
	LoadTGA( &item_tex[ 6 ], "Texture/Inventory/broken_blade.tga");


	for (int i = 0; i < MAX_ITEM_SLOTS; i++)
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

	// Assign item ID, name and material status to added items
	switch (item_id)
	{
		case BANDAGES:
		for (int i = 0; i < MAX_ITEM_SLOTS; i++)
		{
			if (slot[i].item_id == EMPTY && item_added == false)
			{
				slot[i].item_id = BANDAGES;
				slot[i].is_a_material = false;

				item_added = true;
			}
		}

		num_of_items++;
		break;

		case CLOTH:
		for (int i = 0; i < MAX_ITEM_SLOTS; i++)
		{
			if (slot[i].item_id == EMPTY && item_added == false)
			{
				slot[i].item_id = CLOTH;
				slot[i].is_a_material = true;
				
				item_added = true;
			}
		}

		num_of_items++;
		break;

		case ALCOHOL:
		for (int i = 0; i < MAX_ITEM_SLOTS; i++)
		{
			if (slot[i].item_id == EMPTY && item_added == false)
			{
				slot[i].item_id = ALCOHOL;
				slot[i].is_a_material = true;

				item_added = true;
			}
		}

		num_of_items++;
		break;

		case MACHETE:
		for (int i = 0; i < MAX_ITEM_SLOTS; i++)
		{
			if (slot[i].item_id == EMPTY && item_added == false)
			{
				slot[i].item_id = MACHETE;
				slot[i].is_a_material = false;

				item_added = true;
			}
		}

		num_of_items++;
		break;

		case BROKEN_WOODEN_HANDLE:
		for (int i = 0; i < MAX_ITEM_SLOTS; i++)
		{
			if (slot[i].item_id == EMPTY && item_added == false)
			{
				slot[i].item_id = BROKEN_WOODEN_HANDLE;
				slot[i].is_a_material = true;

				item_added = true;
			}
		}

		num_of_items++;
		break;

		case BROKEN_BLADE:
		for (int i = 0; i < MAX_ITEM_SLOTS; i++)
		{
			if (slot[i].item_id == EMPTY && item_added == false)
			{
				slot[i].item_id = BROKEN_BLADE;
				slot[i].is_a_material = true;

				item_added = true;
			}
		}

		num_of_items++;
		break;

		default:
		break;
	}
}

bool Inventory::addItem(int set,int item_id)
{
	if(set < MAX_ITEM_SLOTS)
		return false;
	slot[set].item_id = item_id;

	return true;
}

void Inventory::removeItem(int item_id)
{
	bool item_removed = false;

	switch (item_id)
	{
		case BANDAGES:
		for (int i = 0; i < MAX_ITEM_SLOTS; i++)
		{
			if (slot[i].item_id == BANDAGES && item_removed == false)
			{
				slot[i].item_id = EMPTY;
				item_removed = true;
			}
		}

		num_of_items--;
		break;

		case CLOTH:
		for (int i = 0; i < MAX_ITEM_SLOTS; i++)
		{
			if (slot[i].item_id == CLOTH && item_removed == false)
			{
				slot[i].item_id = EMPTY;
				item_removed = true;
			}
		}

		num_of_items--;
		break;

		case ALCOHOL:
		for (int i = 0; i < MAX_ITEM_SLOTS; i++)
		{
			if (slot[i].item_id == ALCOHOL && item_removed == false)
			{
				slot[i].item_id = EMPTY;
				item_removed = true;
			}
		}

		num_of_items--;
		break;

		case MACHETE:
		for (int i = 0; i < MAX_ITEM_SLOTS; i++)
		{
			if (slot[i].item_id == MACHETE && item_removed == false)
			{
				slot[i].item_id = EMPTY;
				item_removed = true;
			}
		}

		num_of_items--;
		break;

		case BROKEN_WOODEN_HANDLE:
		for (int i = 0; i < MAX_ITEM_SLOTS; i++)
		{
			if (slot[i].item_id == BROKEN_WOODEN_HANDLE && item_removed == false)
			{
				slot[i].item_id = EMPTY;
				item_removed = true;
			}
		}

		num_of_items--;
		break;

		case BROKEN_BLADE:
		for (int i = 0; i < MAX_ITEM_SLOTS; i++)
		{
			if (slot[i].item_id == BROKEN_BLADE && item_removed == false)
			{
				slot[i].item_id = EMPTY;
				item_removed = true;
			}
		}

		num_of_items--;
		break;

		default:
		break;
	}
}

void Inventory::emptySlot(int slot_no)
{
	slot[slot_no].item_id = EMPTY;
	num_of_items--;
}

int Inventory::getSlotItem(int slot_no)
{
	return slot[slot_no].item_id;
}

void Inventory::setSlotItem(int slot_no, int item_id)
{
	if (item_id == EMPTY)
		num_of_items--;

	this->slot[slot_no].item_id = item_id;
}

std::string Inventory::getSlotItemName(int slot_no)
{
	return slot[slot_no].item_name;
}

void Inventory::useSlotItem(int slot_no)
{
	switch (slot[slot_no].item_id)
	{
	// BANDAGES (CONSUMABLE)
	case 1:
		// Add 15HP

		emptySlot(slot_no);
		break;

	// CLOTH (MATERIAL)
	case 2:
		break;

	// ALCOHOL (CONSUMABLE) (MATERIAL)
	case 3:
		// Add 5HP

		emptySlot(slot_no);
		break;

	// MACHETE (EQUIPABLE)
	case 4:
		CPlayerInfo::getInstance()->setCurrAmmo(1);
		CPlayerInfo::getInstance()->setCurrEquipped("Machete");
		break;

	// BROKEN WOODEN HANDLE (MATERIAL)
	case 5:
		break;

	// BROKEN BLADE (MATERIAL)
	case 6:
		break;

	default:
		break;
	}
}

void Inventory::craftWithSlotItem(int slot_no)
{
	if (craft_in_first_slot == true && slot[slot_no].is_a_material == true)
	{
		resetCraftingSlots();

		crafting_slot[0].item_id = slot[slot_no].item_id;
		craft_in_first_slot = false;
	}
	else if (craft_in_first_slot == false && slot[slot_no].is_a_material == true && crafting_slot[0].item_id != slot[slot_no].item_id)
	{
		crafting_slot[1].item_id = slot[slot_no].item_id;
		craft_in_first_slot = true;
	}
}

void Inventory::resetCraftingSlots()
{
	crafting_slot[0].item_id = 0;
	crafting_slot[1].item_id = 0;
	crafting_slot[2].item_id = 0;
	
	craft_in_first_slot = true;
}

void Inventory::attemptCrafting()
{
	// CRAFTING BANDAGES
	if (crafting_slot[0].item_id == CLOTH && crafting_slot[1].item_id == ALCOHOL)
	{
		removeItem(CLOTH);
		removeItem(ALCOHOL);

		addItem(BANDAGES);

		resetCraftingSlots();
	}
	else if (crafting_slot[1].item_id == CLOTH && crafting_slot[0].item_id == ALCOHOL)
	{
		removeItem(CLOTH);
		removeItem(ALCOHOL);

		addItem(BANDAGES);

		resetCraftingSlots();
	}

	// CRAFTING A MACHETE
	if (crafting_slot[0].item_id == BROKEN_WOODEN_HANDLE && crafting_slot[1].item_id == BROKEN_BLADE)
	{
		removeItem(BROKEN_WOODEN_HANDLE);
		removeItem(BROKEN_BLADE);

		addItem(MACHETE);

		resetCraftingSlots();
	}
	else if (crafting_slot[1].item_id == BROKEN_WOODEN_HANDLE && crafting_slot[0].item_id == BROKEN_BLADE)
	{
		removeItem(BROKEN_WOODEN_HANDLE);
		removeItem(BROKEN_BLADE);

		addItem(MACHETE);

		resetCraftingSlots();
	}
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

	for (int i = 0; i < MAX_ITEM_SLOTS; i++)
	{
		switch (slot[i].item_id)
		{

		case BANDAGES:
			slot[i].item_name = "Bandages";
			break;
			
		case CLOTH:
			slot[i].item_name = "Cloth";
			break;

		case ALCOHOL:
			slot[i].item_name = "Alcohol";
			break;

		case MACHETE:
			slot[i].item_name = "Machete";
			break;

		case BROKEN_WOODEN_HANDLE:
			slot[i].item_name = "Broken handle";
			break;

		case BROKEN_BLADE:
			slot[i].item_name = "Broken blade";
			break;

		default:
			break;
		}
	}
}

void Inventory::renderCraftingSlots()
{
	for (int i = 0; i < MAX_ITEM_SLOTS; i++)
	{
		if (crafting_slot[0].item_id == slot[i].item_id)
		{
			// Display of 1st crafting slot item
			switch (crafting_slot[0].item_id)
			{
			case CLOTH:
				glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
				glPushMatrix();
				glTranslatef(650, 255, 0);
				glEnable( GL_TEXTURE_2D );
				glEnable( GL_BLEND );
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					glBindTexture( GL_TEXTURE_2D, item_tex[2].texID );
					glBegin(GL_QUADS);
						glTexCoord2f(0,1); glVertex2f(0,0);
						glTexCoord2f(0,0); glVertex2f(0,50);
						glTexCoord2f(1,0); glVertex2f(50,50);
						glTexCoord2f(1,1); glVertex2f(50,0);
					glEnd();
				glDisable( GL_BLEND );
				glDisable( GL_TEXTURE_2D );
				glPopMatrix();
				break;

			case ALCOHOL:
				glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
				glPushMatrix();
				glTranslatef(650, 255, 0);
				glEnable( GL_TEXTURE_2D );
				glEnable( GL_BLEND );
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					glBindTexture( GL_TEXTURE_2D, item_tex[3].texID );
					glBegin(GL_QUADS);
						glTexCoord2f(0,1); glVertex2f(0,0);
						glTexCoord2f(0,0); glVertex2f(0,50);
						glTexCoord2f(1,0); glVertex2f(50,50);
						glTexCoord2f(1,1); glVertex2f(50,0);
					glEnd();
				glDisable( GL_BLEND );
				glDisable( GL_TEXTURE_2D );
				glPopMatrix();
				break;

			case BROKEN_WOODEN_HANDLE:
				glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
				glPushMatrix();
				glTranslatef(650, 255, 0);
				glEnable( GL_TEXTURE_2D );
				glEnable( GL_BLEND );
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					glBindTexture( GL_TEXTURE_2D, item_tex[5].texID );
					glBegin(GL_QUADS);
						glTexCoord2f(0,1); glVertex2f(0,0);
						glTexCoord2f(0,0); glVertex2f(0,50);
						glTexCoord2f(1,0); glVertex2f(50,50);
						glTexCoord2f(1,1); glVertex2f(50,0);
					glEnd();
				glDisable( GL_BLEND );
				glDisable( GL_TEXTURE_2D );
				glPopMatrix();
				break;

			case BROKEN_BLADE:
				glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
				glPushMatrix();
				glTranslatef(650, 255, 0);
				glEnable( GL_TEXTURE_2D );
				glEnable( GL_BLEND );
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					glBindTexture( GL_TEXTURE_2D, item_tex[6].texID );
					glBegin(GL_QUADS);
						glTexCoord2f(0,1); glVertex2f(0,0);
						glTexCoord2f(0,0); glVertex2f(0,50);
						glTexCoord2f(1,0); glVertex2f(50,50);
						glTexCoord2f(1,1); glVertex2f(50,0);
					glEnd();
				glDisable( GL_BLEND );
				glDisable( GL_TEXTURE_2D );
				glPopMatrix();
				break;

			default:
				break;
			}

			// Display of 2nd crafting slot item
			switch (crafting_slot[1].item_id)
			{
			case CLOTH:
				glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
				glPushMatrix();
				glTranslatef(765, 255, 0);
				glEnable( GL_TEXTURE_2D );
				glEnable( GL_BLEND );
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					glBindTexture( GL_TEXTURE_2D, item_tex[2].texID );
					glBegin(GL_QUADS);
						glTexCoord2f(0,1); glVertex2f(0,0);
						glTexCoord2f(0,0); glVertex2f(0,50);
						glTexCoord2f(1,0); glVertex2f(50,50);
						glTexCoord2f(1,1); glVertex2f(50,0);
					glEnd();
				glDisable( GL_BLEND );
				glDisable( GL_TEXTURE_2D );
				glPopMatrix();
				break;

			case ALCOHOL:
				glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
				glPushMatrix();
				glTranslatef(765, 255, 0);
				glEnable( GL_TEXTURE_2D );
				glEnable( GL_BLEND );
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					glBindTexture( GL_TEXTURE_2D, item_tex[3].texID );
					glBegin(GL_QUADS);
						glTexCoord2f(0,1); glVertex2f(0,0);
						glTexCoord2f(0,0); glVertex2f(0,50);
						glTexCoord2f(1,0); glVertex2f(50,50);
						glTexCoord2f(1,1); glVertex2f(50,0);
					glEnd();
				glDisable( GL_BLEND );
				glDisable( GL_TEXTURE_2D );
				glPopMatrix();
				break;

			case BROKEN_WOODEN_HANDLE:
				glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
				glPushMatrix();
				glTranslatef(765, 255, 0);
				glEnable( GL_TEXTURE_2D );
				glEnable( GL_BLEND );
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					glBindTexture( GL_TEXTURE_2D, item_tex[5].texID );
					glBegin(GL_QUADS);
						glTexCoord2f(0,1); glVertex2f(0,0);
						glTexCoord2f(0,0); glVertex2f(0,50);
						glTexCoord2f(1,0); glVertex2f(50,50);
						glTexCoord2f(1,1); glVertex2f(50,0);
					glEnd();
				glDisable( GL_BLEND );
				glDisable( GL_TEXTURE_2D );
				glPopMatrix();
				break;

			case BROKEN_BLADE:
				glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
				glPushMatrix();
				glTranslatef(765, 255, 0);
				glEnable( GL_TEXTURE_2D );
				glEnable( GL_BLEND );
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					glBindTexture( GL_TEXTURE_2D, item_tex[6].texID );
					glBegin(GL_QUADS);
						glTexCoord2f(0,1); glVertex2f(0,0);
						glTexCoord2f(0,0); glVertex2f(0,50);
						glTexCoord2f(1,0); glVertex2f(50,50);
						glTexCoord2f(1,1); glVertex2f(50,0);
					glEnd();
				glDisable( GL_BLEND );
				glDisable( GL_TEXTURE_2D );
				glPopMatrix();
				break;

			default:
				break;
			}
		}
	}

	// DISPLAY OF PRODUCT ITEM
	// BANDAGES
	if (crafting_slot[0].item_id == CLOTH && crafting_slot[1].item_id == ALCOHOL)
	{
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
				glPushMatrix();
				glTranslatef(880, 255, 0);
				glEnable( GL_TEXTURE_2D );
				glEnable( GL_BLEND );
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					glBindTexture( GL_TEXTURE_2D, item_tex[1].texID );
					glBegin(GL_QUADS);
						glTexCoord2f(0,1); glVertex2f(0,0);
						glTexCoord2f(0,0); glVertex2f(0,50);
						glTexCoord2f(1,0); glVertex2f(50,50);
						glTexCoord2f(1,1); glVertex2f(50,0);
					glEnd();
				glDisable( GL_BLEND );
				glDisable( GL_TEXTURE_2D );
				glPopMatrix();
	}
	else if (crafting_slot[1].item_id == CLOTH && crafting_slot[0].item_id == BROKEN_BLADE)
	{
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
				glPushMatrix();
				glTranslatef(880, 255, 0);
				glEnable( GL_TEXTURE_2D );
				glEnable( GL_BLEND );
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					glBindTexture( GL_TEXTURE_2D, item_tex[4].texID );
					glBegin(GL_QUADS);
						glTexCoord2f(0,1); glVertex2f(0,0);
						glTexCoord2f(0,0); glVertex2f(0,50);
						glTexCoord2f(1,0); glVertex2f(50,50);
						glTexCoord2f(1,1); glVertex2f(50,0);
					glEnd();
				glDisable( GL_BLEND );
				glDisable( GL_TEXTURE_2D );
				glPopMatrix();
	}

	// MACHETE
	if (crafting_slot[0].item_id == BROKEN_WOODEN_HANDLE && crafting_slot[1].item_id == BROKEN_BLADE)
	{
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
				glPushMatrix();
				glTranslatef(880, 255, 0);
				glEnable( GL_TEXTURE_2D );
				glEnable( GL_BLEND );
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					glBindTexture( GL_TEXTURE_2D, item_tex[4].texID );
					glBegin(GL_QUADS);
						glTexCoord2f(0,1); glVertex2f(0,0);
						glTexCoord2f(0,0); glVertex2f(0,50);
						glTexCoord2f(1,0); glVertex2f(50,50);
						glTexCoord2f(1,1); glVertex2f(50,0);
					glEnd();
				glDisable( GL_BLEND );
				glDisable( GL_TEXTURE_2D );
				glPopMatrix();
	}
	else if (crafting_slot[1].item_id == BROKEN_WOODEN_HANDLE && crafting_slot[0].item_id == ALCOHOL)
	{
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
				glPushMatrix();
				glTranslatef(880, 255, 0);
				glEnable( GL_TEXTURE_2D );
				glEnable( GL_BLEND );
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					glBindTexture( GL_TEXTURE_2D, item_tex[1].texID );
					glBegin(GL_QUADS);
						glTexCoord2f(0,1); glVertex2f(0,0);
						glTexCoord2f(0,0); glVertex2f(0,50);
						glTexCoord2f(1,0); glVertex2f(50,50);
						glTexCoord2f(1,1); glVertex2f(50,0);
					glEnd();
				glDisable( GL_BLEND );
				glDisable( GL_TEXTURE_2D );
				glPopMatrix();
	}
}