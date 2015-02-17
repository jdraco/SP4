#include "Transform.h"
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#include <windows.h> // Header File For Windows
#include <gl\gl.h> // Header File For The OpenGL32 Library
#include <gl\glu.h> // Header File For The GLu32 Library
#include "Group.h"

CTransform::CTransform()
	: Child (NULL)
{
	Mtx.Clear();
	Update_Mtx.Clear();
}

CTransform::CTransform(const float dx, const float dy, const float dz)
{
	Mtx.Translatef(dx, dy, dz);
}

CTransform::~CTransform()
{
	if (Child)
	{
		//delete Child;
		Child = NULL;
	}
}

void CTransform::Draw()
{
	/*if (Child == 0) 
		return;

	glPushMatrix();
		glMultMatrixf(Mtx.matrix);
		Child->Draw();
	glPopMatrix();*/
}

void CTransform::SetGroup(CGroup* theGroup)
{
	this->Child = theGroup;
}

void CTransform::ApplyTranslate(const float dx, const float dy, const float dz, bool local)
{
	Matrix4x4 TempMtx;
	TempMtx.Translatef(dx, dy, dz);
	
	if (local)
		Mtx = Mtx * TempMtx;
	else
		Mtx = TempMtx * Mtx;
}

void CTransform::ApplyRotate(const float angle, const float rx, const float ry, const float rz)
{
	Matrix4x4 TempMtx;
	TempMtx.Rotatef( angle, rx, ry, rz );
	
	Matrix4x4 MtxBackToOrigin;

	MtxBackToOrigin.matrix[ MtxBackToOrigin.INDEX4( 0, 3 ) ] = -Mtx.matrix[ Mtx.INDEX4( 0, 3 ) ];
	MtxBackToOrigin.matrix[ MtxBackToOrigin.INDEX4( 1, 3 ) ] = -Mtx.matrix[ Mtx.INDEX4( 1, 3 ) ];
	MtxBackToOrigin.matrix[ MtxBackToOrigin.INDEX4( 2, 3 ) ] = -Mtx.matrix[ Mtx.INDEX4( 2, 3 ) ];

	Matrix4x4 MtxBackToPosition;
	MtxBackToPosition.matrix[ MtxBackToPosition.INDEX4( 0, 3 ) ] = Mtx.matrix[ Mtx.INDEX4( 0, 3 ) ];
	MtxBackToPosition.matrix[ MtxBackToPosition.INDEX4( 1, 3 ) ] = Mtx.matrix[ Mtx.INDEX4( 1, 3 ) ];
	MtxBackToPosition.matrix[ MtxBackToPosition.INDEX4( 2, 3 ) ] = Mtx.matrix[ Mtx.INDEX4( 2, 3 ) ];

	Mtx = Mtx * MtxBackToOrigin;
	Mtx = TempMtx * Mtx;
	Mtx = Mtx * MtxBackToPosition;
}

void CTransform::ApplyScale(const float sx, const float sy, const float sz)
{
	Mtx.Scalef(sx, sy, sz);	
}

void CTransform::ApplyTransform(Matrix4x4 newMTX)
{
	Mtx = Mtx * newMTX;
}

void CTransform::GetOffset(float& x, float& y, float& z)
{
	x = Mtx.matrix[ Mtx.INDEX4( 0, 3 ) ];
	y = Mtx.matrix[ Mtx.INDEX4( 1, 3 ) ];
	z = Mtx.matrix[ Mtx.INDEX4( 2, 3 ) ];
}

//Get the transformation matrix
Matrix4x4 CTransform::GetTransform()
{
	return Mtx;
}