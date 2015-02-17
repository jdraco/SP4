#ifndef OBJECTMODEL_H
#define OBJECTMODEL_H

#include "Global.h"
#include "vector3D.h"


class CObjectModel
{
private:
	Vector3D Position;
	Vector3D Color; // Color
	ObjFile theObj_HighPoly;
	ObjFile theObj_MedPoly;
	ObjFile theObj_LowPoly;

	Vector3D vTopLeft, vBottomRight;
	
	ObjFile theObj_Sofa;

	/*
	//Kakashi
	ObjFile Kakashi;
	TextureImage KakashiTex[1];

	//Thundurus
	ObjFile Thundurus;
	TextureImage ThundurusTex[1];
	*/
public:
	CObjectModel();
	~CObjectModel();

	void Init();
	void Render();
	//void Render(const int RESOLUTION);
	void SetPosition(Vector3D theNewPosition);
	Vector3D GetPosition() { return Position; }

	void SetColor(const float red, const float green, const float blue);

	void DrawBoundingBox();
};

#endif