#pragma once

#define MAX_ITEMS 20

#include "Function.h"

struct item
{
	int item_id;
	std::string item_name;
	bool has_been_rendered;
};

class Inventory
{
private:
	enum item_list
	{
		EMPTY,
		KNIFE,
		BANDAGES
	};

	int num_of_items;
	item slot[MAX_ITEMS];

	TextureImage item_tex[3];
	void *font_style;

public:
	Inventory(void);
	~Inventory(void);

	void printw (float x, float y, float z, char* format, ...);

	void addItem(int item_no);
	bool addItem(int set,int item_id);
	void emptySlot(int slot_no);
	int getSlotItem(int slot_no);
	void setSlotItem(int slot_no, int item_no);
	std::string getSlotItemName(int slot_no);

	void renderInventorySlot(int slot_no);
};