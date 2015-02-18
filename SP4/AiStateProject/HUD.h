#pragma once

#include "Function.h"
#include "Inventory.h"

class HUD
{
private:
	int health, detection_state, level, mouseX, mouseY, volume, w, h;
	bool mouseState, showHelp, showOptions, showInventory, mutemusic, LMouse_down_boolean;
	void *font_style;

	Inventory theInventory;
	
	TextureImage HUDtex[11];

public:
	HUD(void);
	~HUD(void);

	void printw (float x, float y, float z, char* format, ...);
	//bool LoadTGA(TextureImage *texture, char *filename);

	void renderHUD (int health, int detection_state, int level, int mouseX, int mouseY, bool mouseState, int volume, int w, int h, Inventory theInventory);

	void drawHealthMeter (void);
	void drawDetectionStatus(void);

	void renderCurrentWeapon(void);
	void renderLevel(void);
	void renderHelpButton(int mouseX,int mouseY, bool mouseState, int w, int h);
	void renderOptionsButton(int mouseX,int mouseY, bool mouseState, int w, int h);
	void renderInventoryButton(int mouseX,int mouseY, bool mouseState, int w, int h);

	void renderMisc(void);

	void HelpScreen(void);
	void OptionsScreen(int mouseX,int mouseY, bool mouseState);
	void InventoryScreen(int mouseX,int mouseY, bool mouseState, Inventory theInventory);
};

