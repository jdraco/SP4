#pragma once

#include <stdio.h>
#include <GL/glut.h>
#include <iostream>
#include "Function.h"

class GameMenu
{
private:
	int mouseX, mouseY, mouseState, volume, w, h;
	bool LMouse_down_boolean, enable_options, mute_music, show_options;
	void *font_style;
	TextureImage menuTex[10];

public:
	GameMenu(void);
	~GameMenu(void);

	void printw (float x, float y, float z, char* format, ...);

	void renderMenuBackground(void);
	void renderLogo(void);
	void renderStartButton();
	void OptionsScreen(void);
	void renderOptionsButton(void);
	void renderExitButton(void);
	bool getMusicMuted(void);
	int getVolume(void);

	void renderMenu(int mouseX, int mouseY, bool mouseState, int w, int h);
	bool showMenu, gameInit;
};

