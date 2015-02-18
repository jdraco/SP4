#pragma once

#define MAX_ITEMS 20

#include "Function.h"

enum item_list
{
	EMPTY,
	KNIFE,
	BANDAGES
};

struct item
{
	int item_no;
	std::string item_name;
	bool has_been_rendered;
};

class Inventory
{
private:
	int num_of_items;
	item slot[MAX_ITEMS];
	TextureImage item_tex[3];

	void *font_style;

public:
	Inventory(void);
	~Inventory(void);

	void printw (float x, float y, float z, char* format, ...);
	bool LoadTGA(TextureImage *texture, char *filename);

	void addItem(int item_no);
	void emptySlot(int slot_no);
	int getSlotItem(int slot_no);
	std::string getSlotItemName(int slot_no);
	void setSlotItem(int slot_no, int item_no);

	void renderInventorySlot(int slot_no);
};