#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Node.h"
#include "Matrix4x4.h"

class CGroup;

class CTransform : public CNode
{
private:
	Matrix4x4 Update_Mtx;

public:
	Matrix4x4 Mtx;

	CTransform();
	CTransform(const float dx, const float dy, const float dz);
	~CTransform();
	void Draw();
	void SetGroup(CGroup* theGroup);

	CGroup* Child;

	void ApplyTranslate(const float dx, const float dy, const float dz, bool local = true);
	void ApplyRotate(const float angle, const float rx, const float ry, const float rz);
	void ApplyScale(const float sx, const float sy, const float sz);
	void ApplyTransform(Matrix4x4 newMTX);

	void GetOffset(float& x, float& y, float& z);

	//Get the transformation matrix
	Matrix4x4 GetTransform();
};

#endif