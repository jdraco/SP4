#pragma once

#include "Grid.h"
#include "../ObjectModel.h"
#include "../Global.h"

class CGrid;
class CObjectModel;

class CSpatialPartition
{
private:
		Vector3D PlayerPos;
		Vector3D PlayerRot;
public:
	CSpatialPartition();
	~CSpatialPartition();

	CGrid* theGrid;
	Vector3D Size, NumOfGrid;
	Vector3D Translate;
	//Vector3D theCameraPosition;

	//Camera* theCamera;
	void SetPlayerInfo(Vector3D Pos, Vector3D Rot)
	{
		PlayerPos = Pos;
		PlayerRot = Rot;
	};

	void Init(const int xSize, const int ySize, const int xNumOfGrid, const int yNumOfGrid, Vector3D Translate);
	CGrid GetGrid(const int xIndex, const int yIndex);
	void RenderScene();//Vector3D* theCameraPosition = NULL
	
	void AddObject(CObjectModel* theObjectModel);
	void AddObject(CGroup* theObjectModel);

	float CalculateDistanceSquare(const int xIndex, const int yIndex, Vector3D Translate , Vector3D NeedPos);//Vector3D* theCameraPosition, 
	float CalculateLowestDistanceSquare(const int xIndex, const int yIndex, Vector3D Translate , Vector3D NeedPos);//Vector3D* theCameraPosition, 
};

