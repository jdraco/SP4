#ifndef MYAPPLICATOIN_H
#define MYAPPLICATION_H

#include <stdio.h>
//#include <iostream>

#include "Global.h"
#include <GL/glut.h>
#include <GL/freeglut.h>

#include "vector3D.h"
#include "Math.h"
#include "Camera.h"
#include "GoodiesFactory.h"

#include "GameState.h"
#include "PlayState.h"
#include "MenuState.h"

//using std::vector;

class myApplication 
{
public:
	// this is a constructor, it is implemented in myapplication.cpp
	myApplication();
	// this is a destructor, it is implemented in myapplication.cpp
	~myApplication();

	bool Init();

	void renderScene(void);

	void changeSize(int w, int h);

	void inputKey(int key, int x, int y);
	void KeyboardDown(unsigned char key, int x, int y);
	void KeyboardUp(unsigned char key, int x, int y);
	void MouseMove (int x, int y);
	void MouseClick(int button, int state, int x, int y);
	void MouseWheel(int button, int dir, int x, int y);
	static myApplication* getInstance();

private:
	
	static myApplication *s_pInstance;

	// Camera
	Vector3D theCameraPosition;
	Vector3D theCameraDirection;
	float angle;

	void Update(void);

	void scrollMap(float timeDiff, int& mapOffset_x, int& mapOffset_y);

	// The hero
	//CPlayerInfo *theHero;

	//  The number of frames
	int frameCount;
	//  Number of frames per second
	float fps;
	//  currentTime - previousTime is the time elapsed
	//  between every call of the Idle function
	int currentTime, previousTime;
	//  Pointer to a font style..
	//  Fonts supported by GLUT are: GLUT_BITMAP_8_BY_13, 
	//  GLUT_BITMAP_9_BY_15, GLUT_BITMAP_TIMES_ROMAN_10, 
	//  GLUT_BITMAP_TIMES_ROMAN_24, GLUT_BITMAP_HELVETICA_10,
	//  GLUT_BITMAP_HELVETICA_12, and GLUT_BITMAP_HELVETICA_18.
	//GLvoid *font_style;
	
	//void *font_style;

	// Calculate the FPS
	void calculateFPS();
	// Display FPS
	void drawString();
	//  Draws a string at the specified coordinates.
	//void printw (float x, float y, float z, char* format, ...);

	// realtime loop control
	long timelastcall;
	// realtime loop control - frequency
	float frequency;

	//bool myKeys[255];
	theMouseInfo mouseInfo;

	// The camera
	Camera* theCamera;

	CGlobal* theGlobal;

	CGameStateManager* theGSM;
	int Score;

	void moveMeForward(bool mode, float timeDiff) ;
	void moveMeSideway(bool mode, float timeDiff);
	void orientMe(float ang);


	void RenderGoodies(void);
	void GameObjectUpdate();
	void ReadExcel(void);

};

#endif