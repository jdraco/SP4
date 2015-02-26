#include "myapplication.h"
#include <mmsystem.h>

myApplication * myApplication::s_pInstance = NULL;

// you can use constructor to initialise variables
myApplication::myApplication()
: theCamera(NULL)
{
	//if(FULLSCREEN)
	//glutFullScreen();

	theGlobal = CGlobal::getInstance();
	Score = 0;
}

myApplication::~myApplication()
{

	theGSM->Cleanup();

	if (theCamera != NULL)
	{
		delete theCamera;
		theCamera = NULL;
	}
}

myApplication* myApplication::getInstance()
{
	if(s_pInstance == NULL)
	{
		s_pInstance = new myApplication();
	}

	return s_pInstance;
}

void myApplication::Update(void) 
{
	Score = (int)LuaReading::getInstance()->luaPlusPlus(Score);

	CGameTime::UpdateDelta();
	theGSM->Update();
}

void myApplication::renderScene(void) 
{
	// Clear the buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
		glLoadIdentity();

		if ((timeGetTime() - timelastcall) > 1000 / frequency)
		{
			
			// Calculate the framerate
			calculateFPS();

			timelastcall=timeGetTime();
			
			
			Update();
		}

		theCamera->Update(0.1);

	theGSM->Draw();

	// Enable 2D text display and HUD
	theCamera->SetHUD(true);

	glColor3f(0,0,1);
	//printw (500, 50, 0, "Test");
	drawString();
	theCamera->SetHUD(false);



	// Flush off any entity which is not drawn yet, so that we maintain the frame rate.
	glFlush();

	// swapping the buffers causes the rendering above to be shown
	glutSwapBuffers();
}

void myApplication::changeSize(int w, int h)
{
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
		h = 1;

	float ratio = (float) (1.0f* w / h);

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45, ratio, 1, 1000);
	glMatrixMode(GL_MODELVIEW);
}

void myApplication::moveMeForward(bool mode, float timeDiff) 
{
	//if (Sound_Footstep == NULL)
	//	Sound_Footstep = theSoundEngine->play2D("footsteps.mp3", false, true);
	//if (Sound_Footstep->getIsPaused() == true)
	//	Sound_Footstep->setIsPaused( false );
	//else if (Sound_Footstep->isFinished() == true)
	//	theSoundEngine->play2D( Sound_Footstep->getSoundSource(), false, true);

	if (mode)
	{
		theCamera->Walk( 1.0f );
	}
	else
	{
		theCamera->Walk( -1.0f );

	}
}

void myApplication::moveMeSideway(bool mode, float timeDiff)
{
	if (mode)
	{
		theCamera->Strafe( -1.0f );
	}
	else
	{
		theCamera->Strafe( 1.0f );
	}
}

void myApplication::orientMe(float ang) 
{
	theCamera->Yaw( ang );
}


void myApplication::inputKey(int key, int x, int y) {

	switch (key) {
		case GLUT_KEY_LEFT : 
			moveMeSideway(true, 1.0f);break;
		case GLUT_KEY_RIGHT : 
			moveMeSideway(false, 1.0f);break;
		case GLUT_KEY_UP : 
			moveMeForward(true, 1.0f);break;
		case GLUT_KEY_DOWN : 
			moveMeForward(false, 1.0f);break;
	}
}

void myApplication::MouseMove (int x, int y) {
	int diffX = x - mouseInfo.lastX;
	int diffY = y - mouseInfo.lastY;

	theGlobal->MousePos = Vector3D(x,y);
	/*
	//Update on y axis
	theCamera->Pitch( diffY * 3.142f / 180.0f );

	////Update on x and z axis
	angle += (float) diffX * 3.142f / 180.0f;
	if (angle > 6.284f)
		angle -= 6.284f;
	else if (angle < -6.284f)
		angle += 6.284f;
	theCamera->Yaw( -angle );
	*/
	mouseInfo.lastX = x;
	mouseInfo.lastY = y;
	
	/*
	//Checking mouse boundary. //	 800 is the window width. You may need to change this to suit your program.
	if  (mouseInfo.lastX > 800-20 || mouseInfo.lastX < 20)
	{
		mouseInfo.lastX = (800 >> 1);
		glutWarpPointer(mouseInfo.lastX, mouseInfo.lastY);
	}
	//	 600 is the window height. You may need to change this to suit your program.
	if (mouseInfo.lastY > 600-20 || mouseInfo.lastY < 20)
	{
		mouseInfo.lastY = (600 >> 1);
		glutWarpPointer(mouseInfo.lastX, mouseInfo.lastY);
	}
	*/


	//3rd Person
	float pitchChange = diffY * 0.01f;
	theCamera->Pitch(-pitchChange);
	
	float angleChange = diffX * 0.003f;
	theCamera->angleAroundPlayer += angleChange;
	
	/*if (diffX < 0)
		CPlayer::getInstance()->TDir = CPlayer::RIGHT;
	else if (diffX > 0)
		CPlayer::getInstance()->TDir = CPlayer::LEFT;
	else if (diffX == 0)
		CPlayer::getInstance()->TDir = CPlayer::STOP;*/
		
}

void myApplication::KeyboardDown(unsigned char key, int x, int y)
{
	theGlobal->myKeys[key]= true;
		
	if(key == 'q')
		theGSM->HandleEvents();
	if(key == 27)
		exit(0);
}

void myApplication::KeyboardUp(unsigned char key, int x, int y)
{

	theGlobal->myKeys[key]= false;
}



void myApplication::MouseClick(int button, int state, int x, int y) 
{
	switch (button) 
	{
		case GLUT_LEFT_BUTTON:
			mouseInfo.mLButtonUp = state;
			theGlobal->MouseState = state;
			theGlobal->MouseType = 0;
			mouseInfo.lastX = x;
			mouseInfo.lastY = y;

			if (mouseInfo.mLButtonUp) 
			{
				//	Add codes to manage the bullets shot out and the remaining bullets
			}

			break;

		case GLUT_RIGHT_BUTTON:
			mouseInfo.mRButtonUp = state;
			theGlobal->MouseState = state;
			theGlobal->MouseType = 1;
			mouseInfo.lastX = x;
			mouseInfo.lastY = y;

			break;

		case GLUT_MIDDLE_BUTTON:
			mouseInfo.middleButtonUp = state;
			theGlobal->MouseState = state;
			theGlobal->MouseType = 2;
			mouseInfo.lastX = x;
			mouseInfo.lastY = y;
			break;
	}
}

void myApplication::MouseWheel(int button, int dir, int x, int y) {
	float zoomLevel = 0.2f;

	if (dir > 0)
		theCamera->distanceFromPlayer -= zoomLevel; //Zoom In
    else
		theCamera->distanceFromPlayer += zoomLevel; //Zoom Out
}

bool myApplication::Init(void)
{
	//Set State
	theGSM = new CGameStateManager;
	theGSM->Init("Teck Wei's project");
	theGSM->ChangeState( CPlayState::Instance() );


	// Set camera position
	theCamera = Camera::getInstance();
	theCamera->SetPosition(0.0, 2.0, -5.0);
	theCamera->SetDirection(0.0, 0.0, 1.0);

	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping ( NEW )
	

	//  The number of frames
	frameCount = 0;
	//  Number of frames per second
	fps = 0;
	//  currentTime - previousTime is the time elapsed
	//  between every call of the Idle function
	currentTime = 0, previousTime = 0;
	//  Pointer to a font style..
	//  Fonts supported by GLUT are: GLUT_BITMAP_8_BY_13, 
	//  GLUT_BITMAP_9_BY_15, GLUT_BITMAP_TIMES_ROMAN_10, 
	//  GLUT_BITMAP_TIMES_ROMAN_24, GLUT_BITMAP_HELVETICA_10,
	//  GLUT_BITMAP_HELVETICA_12, and GLUT_BITMAP_HELVETICA_18.
	//GLvoid *font_style = GLUT_BITMAP_TIMES_ROMAN_24;
	//font_style = GLUT_BITMAP_TIMES_ROMAN_24;

	// realtime loop control
	timelastcall=timeGetTime();
	frequency = 70.0f;

	for(int i = 0;  i < 255; i++)
	{
		theGlobal->myKeys[i] = false;
	}

	angle = 0.0f;
	mouseInfo.lastX = SCREEN_WIDTH >> 1;
	mouseInfo.lastY = SCREEN_HEIGHT >> 1;


	return true;
}



//-------------------------------------------------------------------------
// Calculates the frames per second
//-------------------------------------------------------------------------
void myApplication::calculateFPS()
{
	//  Increase frame count
	frameCount++;

	//  Get the number of milliseconds since glutInit called
	//  (or first call to glutGet(GLUT ELAPSED TIME)).
	currentTime = glutGet(GLUT_ELAPSED_TIME);

	//  Calculate time passed
	int timeInterval = currentTime - previousTime;

	if(timeInterval > 1000)
	{
		//  calculate the number of frames per second
		fps = frameCount / (timeInterval / 1000.0f);

		//  Set time
		previousTime = currentTime;

		//  Reset frame count
		frameCount = 0;
	}
}

//-------------------------------------------------------------------------
//  Draw FPS
//-------------------------------------------------------------------------
void myApplication::drawString()
{
	//  Load the identity matrix so that FPS string being drawn
	//  won't get animates
	glLoadIdentity ();
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		//  Print the FPS to the window
		glColor3f( 1.0f, 1.0f, 1.0f);
		printw (25.0, 25.0, 0, "FPS: %4.2f", fps);
		printw (455.0, 25.0, 0, "Score: %d", Score);
		//printw (25.0, 50.0, 0, "Time Left: %4d", theGlobal->InGameTime->GetCurrent());

		//printw (25.0, 75.0, 0, "Cubes Gotten: %4d", theGlobal->InGameTime->GetCurrent());
	glPopAttrib();
}

//-------------------------------------------------------------------------
//  Draws a string at the specified coordinates.
//-------------------------------------------------------------------------





