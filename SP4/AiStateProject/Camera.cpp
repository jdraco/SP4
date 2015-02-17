#include "Camera.h"
#include <iostream>

Camera* Camera::instance = 0;

Camera::Camera(void)
	: MAXSPEED_MOVE(0)
	, distanceFromPlayer(10)
	, angleAroundPlayer(0)
{
	SetCameraType(LAND_CAM);
	Reset();
}

Camera::Camera(CAM_TYPE ct)
	: MAXSPEED_MOVE(0)
	, distanceFromPlayer(7)
	, angleAroundPlayer(0)
{
	SetCameraType(ct);
	Reset();
}

Camera::~Camera(void)

{
}

Camera* Camera::getInstance()
{
	if (instance == 0)
	{
		instance = new Camera(THIRD_CAM);
	}

	return instance;
}

void Camera::SetCameraType(CAM_TYPE ct) {
	CameraType = ct;
}

void Camera::Reset(void)
{
	Position = Vector3D(0.0, 0.0, 0.0);
	Along = Vector3D(1.0, 0.0, 0.0);
	Up = Vector3D(0.0, 1.0, 0.0);
	
	if(CameraType == LAND_CAM){
		Forward = Vector3D(0.0, 0.0, -1.0);
	}
	else if (CameraType == THIRD_CAM){
		Forward = Vector3D(0.0, 5.0, -1.0);
	}
//	Update();
}

void Camera::Update(float dt) 
{

	CalculateCameraPosition(CalculateHorizontalDistance(), CalculateVerticalDistance(), dt);

	//CPlayer *Player = CPlayer::getInstance();

	if(CameraType == LAND_CAM)
	{
		gluLookAt(	Position.x, Position.y, Position.z, 
				Position.x + Forward.x, Position.y + Forward.y, Position.z + Forward.z, 
				0.0f,1.0f,0.0f);
	}
	else if (CameraType == THIRD_CAM)
	{	
		gluLookAt(Position.x, Position.y, Position.z, 
			PlayerPos.x, PlayerPos.y + 5 + Forward.y, PlayerPos.z, 
			  0.0f,1.0f,0.0f);

	}
}

Vector3D Camera::GetPosition() 
{
	return Position;
}

void Camera::SetPosition( GLfloat x, GLfloat y, GLfloat z )
{
	this->Position.Set( x, y, z );
}

void Camera::SetDirection( GLfloat x, GLfloat y, GLfloat z )
{
	this->Forward.Set( x, y, z );
}

void Camera::Pitch(GLfloat theta)
{
	if(CameraType == LAND_CAM){
		Forward.y -= theta;
		if (Forward.y > 3.142f)
			Forward.y = 3.142f;
		else if (Forward.y < -3.142f)
			Forward.y = -3.142f;
	}
	else if (CameraType == THIRD_CAM)
	{
		Forward.y -= theta;
		if (Forward.y > 1.0f)
		Forward.y = 1.0f;
		else if (Forward.y < -1.0f)
		Forward.y = -1.0f;
	}

}
void Camera::Yaw(GLfloat theta)
{
	Forward.x = sin(-theta);
	Forward.z = -cos(-theta);
}
void Camera::Roll(GLfloat theta){}
void Camera::Walk(GLfloat delta)
{
	if (delta > MAXSPEED_MOVE)
		delta = MAXSPEED_MOVE;

	Position.Set( Position.x + Forward.x * delta, Position.y + Forward.y * delta, Position.z + Forward.z * delta );
}
void Camera::Strafe(GLfloat delta)
{
	Along = Forward.crossVector3D( Up );
	Along.normalizeVector3D();
	Position.Set( Position.x + Along.x * delta, Position.y + Along.y * delta, Position.z + Along.z * delta );
}
void Camera::Fly(GLfloat delta)
{
}

// Toggle HUD mode
void Camera::SetHUD(bool m_bHUDmode)
{
	if (m_bHUDmode)
	{
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, -1, 1);      
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_TEXTURE_2D);							// Enable Texture Mapping ( NEW )
	}
	else
	{
		glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping ( NEW )
		glEnable(GL_DEPTH_TEST);
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glEnable(GL_DEPTH_TEST);
	}
}

// Get the direction of the camera
Vector3D Camera::GetDirection(void)
{
	return Forward;
}

//3rd Person
float Camera::CalculateHorizontalDistance()
{
	return (float)(distanceFromPlayer * cos(Math::DegreeToRadian(Forward.y)));
}
float Camera::CalculateVerticalDistance()
{
	return (float)(distanceFromPlayer * sin(Forward.y));
}

void Camera::CalculateCameraPosition(float hDist, float vDist, float dt)
{
	//CPlayer *Player = CPlayer::getInstance();
	Position.y = PlayerPos.y + vDist + 5;

	float theta = PlayerRot.y + angleAroundPlayer;
	float offsetX = (float)(hDist * sin(Math::DegreeToRadian(theta)));
	float offsetZ = (float)(hDist * cos(Math::DegreeToRadian(theta)));

	Position.x = PlayerPos.x - offsetX;
	Position.z = PlayerPos.z - offsetZ;

	Yaw(Math::DegreeToRadian(180+(PlayerRot.y + angleAroundPlayer)));

}