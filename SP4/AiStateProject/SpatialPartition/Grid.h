#pragma once

#include <vector>
#include "../ObjectModel.h"
#include "../vector3D.h"



class CObjectModel;

class CGrid
{
public:
	CGrid();
	~CGrid();

	Vector3D Size, Index;
	Vector3D Translate , Color;
	vector<CObjectModel*> ListOfObjects;
	vector<CGroup*> ListOfGroups;

	void Init(const int index_x, const int index_y, const int xSize, const int ySize , Vector3D Translate);
	void AddObject(CObjectModel* theObject);
	void AddObject(CGroup* theObject);

	void RenderScene();
	void RenderObjects(const int RESOLUTION);
	void DeleteObjects();

	Vector3D GetBtmLeft();
	Vector3D GetTopLeft();
	Vector3D GetBtmRight();
	Vector3D GetTopRight();

	float GetSizeSquare();
	float GetPointRadSquare(float PlayerRad);
	//Vector3D GetPointRadSquare();

	bool CGrid::CheckCollision(Vector3D Pos, float Radius);
};