#pragma once

#include "Function.h"
#include "GameMenu.h"
#include "Inventory.h"
#include "weaponManager.h"

enum weapon_list
{
	NONE,
	KNIFE_HUD
};

class HUD
{
private:
	int health, detection_state, level, mouseX, mouseY, mouseType, volume, w, h;
	bool mouseState, showHelp, showOptions, showInventory, mutemusic, LMouse_down_boolean;
	void *font_style;

	Inventory HUDInventory;
	weapon_list CURRENT_WEAPON;
	
	TextureImage HUDtex[20];
	CweaponManager* weapManager;
	string currEquipped;
public:
	HUD(void);
	~HUD(void);

	void printw (float x, float y, float z, char* format, ...);

	void renderHUD (int health, int detection_state, int level, int mouseX, int mouseY, bool mouseState, int mouseType, int w, int h, Inventory& theInventory, string equipped);

	void drawHealthMeter (void);
	void drawDetectionStatus(void);

	void renderCurrentWeapon(void);
	void renderLevel(void);
	void renderHelpButton();
	void renderOptionsButton();
	void renderInventoryButton();

	void renderMisc(void);

	void HelpScreen();
	void OptionsScreen();
	void InventoryScreen();
	void CraftingScreen();
};

