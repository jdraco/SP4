#pragma once

#include "Global.h"

#define FOVY 45
#define ASPECT_RATIO 1.33f

class CFrustum 
{
private:
	GLfloat angle, farDist, nearDist, heightNear, heightFar, widthNear, widthFar;

	Vector3D Color;

	float Scale;

	float rotationAngle;
	Vector3D rotation;

	Vector3D farC,nearC;
	Vector3D fPosition, fDirection, fUp;
	Vector3D up, right;

	Vector3D ftl,ftr,fbl,fbr;
	Vector3D ntl,ntr,nbl,nbr;
	Vector3D farV,nearV,leftV,rightV,topV,btmV;

	bool changeX, changeZ;

public:
	CFrustum(void);
	~CFrustum(void);

	void SelfInit(void);
	// Update the frustum
	bool Update(void);
	// Draw the frustum
	void Render(void);

	void RotateY(float angle);
	// Perform containment check for a position with respect to the Frustum
	bool ContainmentCheck(const Vector3D position);

	//get/set
	void SetColor(float R, float G, float B) { Color.Set(R,G,B); };
	Vector3D GetColor(){return Color;};

	void SetScale(float Scale) { this->Scale = Scale; };

	void SetPos(float x, float y, float z) { fPosition.Set(x,y,z); }
	Vector3D GetPos() { return this->fPosition; }
	void SetDir(float x, float y, float z) { fDirection.Set(x,y,z); }
	Vector3D GetDir() { return this->fDirection; }
	//void RotateY(float angle);
};
