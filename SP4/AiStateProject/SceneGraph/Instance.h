#pragma once
#include "node.h"
#include "Model.h"

class CInstance :
	public CNode
{
private:
	CModel *Mod;
public:
	CInstance(void);
	~CInstance(void);
	void Draw(void);
	void SetColor(const float red, const float green, const float blue);
	Vector3D GetColor();

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
