#pragma once

#define MAX_ITEM_SLOTS 20

#include "Function.h"

struct item
{
	int item_id;
	std::string item_name;
	bool has_been_rendered, is_a_material;
};

class Inventory
{
private:
	enum item_list
	{
		EMPTY,
		BANDAGES,	// CONSUMABLE
		CLOTH,		// MATERIAL
		ALCOHOL		// MATERIAL + CONSUMABLE
	};

	int num_of_items;
	item slot[MAX_ITEM_SLOTS];
	item crafting_slot[3];		// Crafting-slot 3 is a product slot (DO NOT ALLOW USER TO PLACE ANYTHING INSIDE)

	TextureImage item_tex[10];
	void *font_style;

public:
	Inventory(void);
	~Inventory(void);

	void printw (float x, float y, float z, char* format, ...);

	void addItem(int item_no);
	bool addItem(int set,int item_id);
	void removeItem(int item_id);
	void emptySlot(int slot_no);
	int getSlotItem(int slot_no);
	void setSlotItem(int slot_no, int item_no);
	std::string getSlotItemName(int slot_no);

	void useSlotItem(int slot_no);

	void craftWithSlotItem(int slot_no);
	void resetCraftingSlots();
	void attemptCrafting();

	void renderInventorySlot(int slot_no);
	void renderCraftingSlots();

	bool craft_in_first_slot;
};