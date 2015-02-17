#ifndef CAMERA_H
#define CAMERA_H

#include "Define.h"
//#include "Player.h"



class Camera
{
public:
	static Camera* getInstance();
	enum CAM_TYPE { LAND_CAM, AIR_CAM, THIRD_CAM };

private:
	static Camera* instance;
	CAM_TYPE CameraType;
	Vector3D Position;
	Vector3D Along;
	Vector3D Up;
	Vector3D Forward;

	//storing players info
	Vector3D PlayerPos;
	Vector3D PlayerRot;

	float MAXSPEED_MOVE;

public:
	Camera(void);
	Camera(CAM_TYPE ct);
	~Camera(void);

	void SetCameraType(CAM_TYPE ct);
	void Reset(void);
	void Update(float dt);
	Vector3D GetPosition();
	// Get the direction of the camera

	//void GetPlayerPos(Vector3D temp);
	void SetPlayerInfo(Vector3D Pos, Vector3D Rot)
	{
		PlayerPos = Pos;
		PlayerRot = Rot;
	};

	Vector3D GetDirection(void);
	void SetPosition( GLfloat x, GLfloat y, GLfloat z );
	void SetDirection( GLfloat x, GLfloat y, GLfloat z );

	void Pitch(GLfloat theta);
	void Yaw(GLfloat theta);
	void Roll(GLfloat theta);
	void Walk(GLfloat delta);//, bool Wall[4]);
	void Strafe(GLfloat delta);//, bool Wall[4]);
	void Fly(GLfloat delta);
	// Toggle HUD mode
	void SetHUD(bool m_bHUDmode);

	//3rd Person
	float distanceFromPlayer, angleAroundPlayer;
	float CalculateHorizontalDistance(), CalculateVerticalDistance();
	void CalculateCameraPosition(float hDist, float vDist, float dt);
};

#endif