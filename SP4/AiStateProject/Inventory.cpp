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
	LoadTGA( &item_tex[ 7 ], "Texture/Inventory/lockpick.tga");
	LoadTGA( &item_tex[ 8 ], "Texture/pistol.tga");
	LoadTGA( &item_tex[ 9 ], "Texture/ak.tga");

	LoadTGA( &other_tex[ 0 ], "Texture/Inventory/new.tga");


	for (int i = 0; i < MAX_ITEM_SLOTS; i++)
	{
		slot[i].item_id = EMPTY;
		slot[i].item_name = "";
		slot[i].item_description = "";
		slot[i].item_description2 = "";
		slot[i].is_a_material = false;
		slot[i].is_useable = false;
		slot[i].is_discardable = false;
		slot[i].has_been_rendered = false;
		slot[i].is_equipped = false;
		slot[i].is_new = false;
		slot[i].is_selected_for_crafting = false;
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
				slot[i].item_name = "Bandages";
				slot[i].item_description = "[Consumable]";
				slot[i].item_description2 = "Heals 15HP.";
				slot[i].is_a_material = false;
				slot[i].is_useable = true;
				slot[i].is_discardable = true;
				slot[i].is_equipped = false;
				slot[i].is_new = true;
				slot[i].is_selected_for_crafting = false;

				num_of_items++;
				item_added = true;
			}
		}
		break;

		case CLOTH:
		for (int i = 0; i < MAX_ITEM_SLOTS; i++)
		{
			if (slot[i].item_id == EMPTY && item_added == false)
			{
				slot[i].item_id = CLOTH;
				slot[i].item_name = "Cloth";
				slot[i].item_description = "[Crafting material]";
				slot[i].item_description2 = "";
				slot[i].is_a_material = true;
				slot[i].is_useable = false;
				slot[i].is_discardable = true;
				slot[i].is_equipped = false;
				slot[i].is_new = true;
				slot[i].is_selected_for_crafting = false;
				
				num_of_items++;
				item_added = true;
			}
		}
		break;

		case ALCOHOL:
		for (int i = 0; i < MAX_ITEM_SLOTS; i++)
		{
			if (slot[i].item_id == EMPTY && item_added == false)
			{
				slot[i].item_id = ALCOHOL;
				slot[i].item_name = "Alcohol";
				slot[i].item_description = "[Crafting material]/[Consumable]";
				slot[i].item_description2 = "Heals 5HP.";
				slot[i].is_a_material = true;
				slot[i].is_useable = true;
				slot[i].is_discardable = true;
				slot[i].is_equipped = false;
				slot[i].is_new = true;
				slot[i].is_selected_for_crafting = false;

				num_of_items++;
				item_added = true;
			}
		}
		break;

		case MACHETE:
		for (int i = 0; i < MAX_ITEM_SLOTS; i++)
		{
			if (slot[i].item_id == EMPTY && item_added == false)
			{
				slot[i].item_id = MACHETE;
				slot[i].item_name = "Machete";
				slot[i].item_description = "[Equipable]";
				slot[i].item_description2 = "A melee weapon.";
				slot[i].is_a_material = false;
				slot[i].is_useable = true;
				slot[i].is_discardable = true;
				slot[i].is_equipped = false;
				slot[i].is_new = true;
				slot[i].is_selected_for_crafting = false;

				num_of_items++;
				item_added = true;
			}
		}
		break;

		case BROKEN_WOODEN_HANDLE:
		for (int i = 0; i < MAX_ITEM_SLOTS; i++)
		{
			if (slot[i].item_id == EMPTY && item_added == false)
			{
				slot[i].item_id = BROKEN_WOODEN_HANDLE;
				slot[i].item_name = "Broken wooden handle";
				slot[i].item_description = "[Crafting material]";
				slot[i].item_description2 = "";
				slot[i].is_a_material = true;
				slot[i].is_useable = false;
				slot[i].is_discardable = true;
				slot[i].is_equipped = false;
				slot[i].is_new = true;
				slot[i].is_selected_for_crafting = false;

				num_of_items++;
				item_added = true;
			}
		}
		break;

		case BROKEN_BLADE:
		for (int i = 0; i < MAX_ITEM_SLOTS; i++)
		{
			if (slot[i].item_id == EMPTY && item_added == false)
			{
				slot[i].item_id = BROKEN_BLADE;
				slot[i].item_name = "Broken blade";
				slot[i].item_description = "[Crafting material]";
				slot[i].item_description2 = "";
				slot[i].is_a_material = true;
				slot[i].is_useable = false;
				slot[i].is_discardable = true;
				slot[i].is_equipped = false;
				slot[i].is_new = true;
				slot[i].is_selected_for_crafting = false;

				num_of_items++;
				item_added = true;
			}
		}
		break;

		case LOCKPICK:
		for (int i = 0; i < MAX_ITEM_SLOTS; i++)
		{
			if (slot[i].item_id == EMPTY && item_added == false)
			{
				slot[i].item_id = LOCKPICK;
				slot[i].item_name = "Lockpick";
				slot[i].item_description = "[Tool]";
				slot[i].item_description2 = "For picklocking locked doors/chests.";
				slot[i].is_a_material = false;
				slot[i].is_useable = false;
				slot[i].is_discardable = true;
				slot[i].is_equipped = false;
				slot[i].is_new = true;
				slot[i].is_selected_for_crafting = false;

				num_of_items++;
				item_added = true;
			}
		}
		break;

		case PISTOL:
		for (int i = 0; i < MAX_ITEM_SLOTS; i++)
		{
			if (slot[i].item_id == EMPTY && item_added == false)
			{
				slot[i].item_id = PISTOL;
				slot[i].item_name = "Pistol";
				slot[i].item_description = "[Equipable]";
				slot[i].item_description2 = "A slow-firing ranged weapon.";
				slot[i].is_a_material = false;
				slot[i].is_useable = true;
				slot[i].is_discardable = true;
				slot[i].is_equipped = false;
				slot[i].is_new = true;
				slot[i].is_selected_for_crafting = false;

				num_of_items++;
				item_added = true;
			}
		}
		break;

		case RIFLE:
		for (int i = 0; i < MAX_ITEM_SLOTS; i++)
		{
			if (slot[i].item_id == EMPTY && item_added == false)
			{
				slot[i].item_id = RIFLE;
				slot[i].item_name = "Rifle";
				slot[i].item_description = "[Equipable]";
				slot[i].item_description2 = "A fast-firing ranged weapon.";
				slot[i].is_a_material = false;
				slot[i].is_useable = true;
				slot[i].is_discardable = true;
				slot[i].is_equipped = false;
				slot[i].is_new = true;
				slot[i].is_selected_for_crafting = false;

				num_of_items++;
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
				emptySlot(i);

				item_removed = true;
			}
		}
		break;

		case CLOTH:
		for (int i = 0; i < MAX_ITEM_SLOTS; i++)
		{
			if (slot[i].item_id == CLOTH && item_removed == false)
			{
				emptySlot(i);

				item_removed = true;
			}
		}
		break;

		case ALCOHOL:
		for (int i = 0; i < MAX_ITEM_SLOTS; i++)
		{
			if (slot[i].item_id == ALCOHOL && item_removed == false)
			{
				emptySlot(i);

				item_removed = true;
			}
		}
		break;

		case MACHETE:
		for (int i = 0; i < MAX_ITEM_SLOTS; i++)
		{
			if (slot[i].item_id == MACHETE && item_removed == false)
			{
				emptySlot(i);

				item_removed = true;
			}
		}
		break;

		case BROKEN_WOODEN_HANDLE:
		for (int i = 0; i < MAX_ITEM_SLOTS; i++)
		{
			if (slot[i].item_id == BROKEN_WOODEN_HANDLE && item_removed == false)
			{
				emptySlot(i);

				item_removed = true;
			}
		}
		break;

		case BROKEN_BLADE:
		for (int i = 0; i < MAX_ITEM_SLOTS; i++)
		{
			if (slot[i].item_id == BROKEN_BLADE && item_removed == false)
			{
				emptySlot(i);

				item_removed = true;
			}
		}
		break;

		case LOCKPICK:
		for (int i = 0; i < MAX_ITEM_SLOTS; i++)
		{
			if (slot[i].item_id == LOCKPICK && item_removed == false)
			{
				emptySlot(i);

				item_removed = true;
			}
		}
		break;

		case PISTOL:
		for (int i = 0; i < MAX_ITEM_SLOTS; i++)
		{
			if (slot[i].item_id == PISTOL && item_removed == false)
			{
				emptySlot(i);

				item_removed = true;
			}
		}
		break;

		case RIFLE:
		for (int i = 0; i < MAX_ITEM_SLOTS; i++)
		{
			if (slot[i].item_id == RIFLE && item_removed == false)
			{
				emptySlot(i);

				item_removed = true;
			}
		}
		break;

		default:
		break;
	}
}

bool Inventory::findItem(int item_id)
{
	int count = 0;
	
	for (int i = 0; i < MAX_ITEM_SLOTS; i++)
	{
		if (slot[i].item_id == item_id)
		{
			count++;
		}
	}

	if (count > 0)
		return true;
	else
		return false;
}

bool Inventory::findItem(string item_name)
{
	int count = 0;
	
	for (int i = 0; i < MAX_ITEM_SLOTS; i++)
	{
		if (slot[i].item_name == item_name)
		{
			count++;
		}
	}

	if (count > 0)
		return true;
	else
		return false;
}

void Inventory::emptySlot(int slot_no)
{
	slot[slot_no].item_id = EMPTY;
	slot[slot_no].item_name = "";
	slot[slot_no].item_description = "";
	slot[slot_no].item_description2 = "";
	slot[slot_no].has_been_rendered = false;
	slot[slot_no].is_a_material = false;
	slot[slot_no].is_useable = false;
	slot[slot_no].is_discardable = false;
	slot[slot_no].is_equipped = false;
	slot[slot_no].is_new = false;
	slot[slot_no].is_selected_for_crafting = false;

	num_of_items--;
}

int Inventory::getSlotItem(int slot_no)
{
	return slot[slot_no].item_id;
}

string Inventory::getSlotItemName(int slot_no)
{
	return slot[slot_no].item_name;
}

string Inventory::getSlotItemDescription(int slot_no)
{
	return slot[slot_no].item_description;
}

string Inventory::getSlotItemDescription2(int slot_no)
{
	return slot[slot_no].item_description2;
}
 
bool Inventory::getSlotItemUseableStatus(int slot_no)
{
	return slot[slot_no].is_useable;
}

bool Inventory::getSlotItemDiscardableStatus(int slot_no)
{
	return slot[slot_no].is_discardable;
}

bool Inventory::getSlotItemEquippedStatus(int slot_no)
{
	return slot[slot_no].is_equipped;
}

bool Inventory::getSlotItemSelectedForCraftingStatus(int slot_no)
{
	return slot[slot_no].is_selected_for_crafting;
}

void Inventory::clearAllEquippedStatus()
{
	for (int i = 0; i < MAX_ITEM_SLOTS; i++)
	{
		slot[i].is_equipped = false;
	}
}

void Inventory::setNextSameItemToBeEquipped(string item_name)
{
	bool other_same_weapon_equipped = false, has_set_to_equipped = false;

	for (int i = 0; i < MAX_ITEM_SLOTS; i++)
	{
		if (slot[i].is_equipped == true)
		{
			other_same_weapon_equipped = true;
		}
	}

	for (int i = 0; i < MAX_ITEM_SLOTS; i++)
	{
		if (slot[i].item_name == item_name && other_same_weapon_equipped == false && has_set_to_equipped == false)
		{
			slot[i].is_equipped = true;

			has_set_to_equipped = true;
		}
	}
}

void Inventory::setAllItemsToBeOld()
{
	for (int i = 0; i < MAX_ITEM_SLOTS; i++)
	{
		slot[i].is_new = false;
	}
}

void Inventory::resetAllItemsSelectedForCrafting()
{
	for (int i = 0; i < MAX_ITEM_SLOTS; i++)
	{
		slot[i].is_selected_for_crafting = false;
	}
}

void Inventory::useSlotItem(int slot_no)
{
	switch (slot[slot_no].item_id)
	{
	case BANDAGES:	// CONSUMABLE
		CPlayerInfo::getInstance()->setHP(CPlayerInfo::getInstance()->getHP() + 15);

		emptySlot(slot_no);
		break;

	case ALCOHOL:	// CONSUMABLE + MATERIAL
		CPlayerInfo::getInstance()->setHP(CPlayerInfo::getInstance()->getHP() + 5);

		emptySlot(slot_no);
		break;

	case MACHETE:	// EQUIPABLE
		clearAllEquippedStatus();

		CPlayerInfo::getInstance()->setCurrAmmo(1);
		CPlayerInfo::getInstance()->setCurrEquippedFromInv("Machete");

		slot[slot_no].is_equipped = true;
		break;

	case PISTOL:	// EQUIPABLE
		clearAllEquippedStatus();

		CPlayerInfo::getInstance()->setCurrAmmo(20);
		CPlayerInfo::getInstance()->setCurrEquippedFromInv("Pistol");

		slot[slot_no].is_equipped = true;
		break;

	case RIFLE:	// EQUIPABLE
		clearAllEquippedStatus();

		CPlayerInfo::getInstance()->setCurrAmmo(20);
		CPlayerInfo::getInstance()->setCurrEquippedFromInv("Rifle");

		slot[slot_no].is_equipped = true;
		break;

	default:
		break;
	}
}

void Inventory::craftWithSlotItem(int slot_no)
{
	if (craft_in_first_slot == true && slot[slot_no].is_a_material == true)
	{
		resetAllItemsSelectedForCrafting();
		resetCraftingSlots();

		slot[slot_no].is_selected_for_crafting = true;
		crafting_slot[0].item_id = slot[slot_no].item_id;
		craft_in_first_slot = false;
	}
	else if (craft_in_first_slot == false && slot[slot_no].is_a_material == true && crafting_slot[0].item_id != slot[slot_no].item_id)
	{
		slot[slot_no].is_selected_for_crafting = true;
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
	if (slot[slot_no].has_been_rendered == false && slot[slot_no].is_new == true)
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
		//glPopMatrix();

		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindTexture(GL_TEXTURE_2D, other_tex[0].texID);
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
	else if (slot[slot_no].has_been_rendered == false && slot[slot_no].is_new == false)
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
	else if (crafting_slot[1].item_id == CLOTH && crafting_slot[0].item_id == ALCOHOL)
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
	else if (crafting_slot[1].item_id == BROKEN_WOODEN_HANDLE && crafting_slot[0].item_id == BROKEN_BLADE)
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
}