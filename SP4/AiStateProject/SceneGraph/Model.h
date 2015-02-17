#ifndef MODEL_H
#define MODEL_H

#include <GL/glut.h>
#include "..\vector3D.h"

class CModel
{
private:
	Vector3D vTopLeft, vBottomRight;
	float red, green, blue;
public:
	CModel();
	~CModel();
	void Draw();
	void SetColor(const float red, const float green, const float blue);
	Vector3D GetColor();

	//Draw Lines Surrounding Model
	void DrawLines();

	//Draw Points 
	void DrawSphere();

	//Get corners of the Bounding Box (Back)
	Vector3D GetBackTopLeft();
	Vector3D GetBackTopRight();
	Vector3D GetBackBottomLeft();
	Vector3D GetBackBottomRight();

	//Get corners of the Bounding Box (Front)
	Vector3D GetFrontTopLeft();
	Vector3D GetFrontTopRight();
	Vector3D GetFrontBottomLeft();
	Vector3D GetFrontBottomRight();
};

#endif
