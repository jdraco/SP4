#include "SpatialPartition.h"

CSpatialPartition::CSpatialPartition()
	: theGrid(NULL)
	, Size(Vector3D(0,0))
	, NumOfGrid(Size)
{
}

CSpatialPartition::~CSpatialPartition()
{
	for (short i = 0; i < (short)NumOfGrid.x; ++i)
	{
		for (short j = 0; j < (short)NumOfGrid.y; ++j)
			theGrid[(short)(i*NumOfGrid.y+j)].DeleteObjects();
	}
	delete [] theGrid;
}

void CSpatialPartition::Init(const int xSize, const int ySize, const int xNumOfGrid, const int yNumOfGrid , Vector3D Translate)
{
	Size.Set((float)xSize, (float)ySize);
	NumOfGrid.Set((float)xNumOfGrid, (float)yNumOfGrid);

	this->Translate = Translate;

	theGrid = new CGrid[xNumOfGrid*yNumOfGrid];

	for (short i = 0; i < (short)xNumOfGrid; ++i)
	{
		for (short j = 0; j < yNumOfGrid; ++j)
			theGrid[i*yNumOfGrid+j].Init(i, j, xSize, ySize, Translate);
	}
}

CGrid CSpatialPartition::GetGrid(const int xIndex, const int yIndex) 
{ 
	return theGrid[(short)(xIndex*NumOfGrid.y+yIndex)]; 
}

void CSpatialPartition::RenderScene()//Vector3D* theCameraPosition
{

	for (short i = 0; i < (short)NumOfGrid.x; ++i)
	{
		for (short j = 0; j < (short)NumOfGrid.y; ++j)
		{
			CGrid temp = theGrid[(short)(i*NumOfGrid.y+j)];
			//int distance = CalculateLowestDistanceSquare(temp.Index.x, temp.Index.y , temp.Translate, PlayerPos );
				
			if(temp.CheckCollision(PlayerPos,REACH_RADIUS) ) // close
			{
				temp.Color =  Vector3D(HIGHRES);
				temp.RenderObjects(2);
			}
			else if(temp.CheckCollision(PlayerPos,SIGHT_RADIUS))	// mid
			{
				temp.Color =  Vector3D(MIDRES);
				temp.RenderObjects(1);
			}
			else								// mid
			{
				temp.Color = Vector3D(LOWRES);
				temp.RenderObjects(0);
			}
			glPushMatrix();
				temp.RenderScene();
			glPopMatrix();
		}
	}

		
}

void CSpatialPartition::AddObject(CObjectModel* theObjectModel)
{
	Vector3D theObjectPosition = theObjectModel->GetPosition();
	int index_x =(int)((theObjectPosition.x / Size.x) - (Translate.x / Size.x)); 
	//int index_x = (int)LuaReading::getInstance()->luaGetIndex(theObjectPosition.x, Size.x , Translate.x);
	int index_y = (int)((theObjectPosition.z / Size.y) - (Translate.y / Size.y));
	//int index_y = (int)LuaReading::getInstance()->luaGetIndex(theObjectPosition.z, Size.y , Translate.y);
	cout << index_x << " , " << index_y << endl;

	if (((index_x >= 0) && (index_x < (int)NumOfGrid.x)) && ((index_y >= 0) && (index_y < (int)NumOfGrid.y)))
	{
		theGrid[(short)(index_x*NumOfGrid.y+index_y)].AddObject(theObjectModel);
		//cout << "going to grid : " << index_x*NumOfGrid.y+index_y;
	}
	else {} //Object is outside of grid
}

void CSpatialPartition::AddObject(CGroup* theObjectModel)
{
	Vector3D theObjectPosition = theObjectModel->GetPos();

	int index_x = (int)((theObjectPosition.x / Size.x) - (Translate.x / Size.x));
	int index_y = (int)((theObjectPosition.z / Size.y) - (Translate.y / Size.y));

	cout << index_x << " , " << index_y << endl;

	if (((index_x >= 0) && (index_x < (int)NumOfGrid.x)) && ((index_y >= 0) && (index_y < (int)NumOfGrid.y)))
		theGrid[(short)(index_x*NumOfGrid.y+index_y)].AddObject(theObjectModel);

	else {} //Object is outside of grid
}

float CSpatialPartition::CalculateDistanceSquare( const int xIndex, const int yIndex , Vector3D Translate, Vector3D NeedPos )//with playerpos
{
	float xDistance = (float)(( ( xIndex * Size.x ) + Translate.x + (Size.x*0.5))-NeedPos.x);
	float yDistance = (float)((	( yIndex * Size.y ) + Translate.y + (Size.y*0.5))-NeedPos.z);

	return (xDistance*xDistance + yDistance*yDistance);
}

float CSpatialPartition::CalculateLowestDistanceSquare( const int xIndex, const int yIndex , Vector3D Translate, Vector3D NeedPos )//with playerpos
{
	float shortestDis;

	float xDistance_Mid = (float)(( ( xIndex * Size.x ) + Translate.x + (Size.x*0.5))-NeedPos.x);
	float yDistance_Mid = (float)((	( yIndex * Size.y ) + Translate.y + (Size.y*0.5))-NeedPos.z);
	float Mid_Total = xDistance_Mid*xDistance_Mid + yDistance_Mid*yDistance_Mid;

	shortestDis = Mid_Total;

	float xDistance_Btm_Left = (float)(( ( xIndex * Size.x ) + Translate.x  )-NeedPos.x);
	float yDistance_Btm_Left = (float)((	( yIndex * Size.y ) + Translate.y  )-NeedPos.z);
	float Btm_Left_Total = xDistance_Btm_Left*xDistance_Btm_Left + yDistance_Btm_Left*yDistance_Btm_Left;

	if(shortestDis > Btm_Left_Total)
		shortestDis = Btm_Left_Total;

	float xDistance_Btm_Right = (float)(( ( xIndex * Size.x ) + Translate.x + (Size.x) )-NeedPos.x);
	float yDistance_Btm_Right = (float)((	( yIndex * Size.y ) + Translate.y  )-NeedPos.z);

	float Btm_Right_Total = xDistance_Btm_Right*xDistance_Btm_Right + yDistance_Btm_Right*yDistance_Btm_Right;
		
	if(shortestDis > Btm_Right_Total)
		shortestDis = Btm_Right_Total;

	float xDistance_Top_Left = (float)(( ( xIndex * Size.x ) + Translate.x  )-NeedPos.x);
	float yDistance_Top_Left = (float)((	( yIndex * Size.y ) + Translate.y +  (Size.y) )-NeedPos.z);

	float Top_Left_Total = xDistance_Top_Left*xDistance_Top_Left + yDistance_Top_Left*yDistance_Top_Left;

	if(shortestDis > Top_Left_Total)
		shortestDis = Top_Left_Total;

	float xDistance_Top_Right = (float)(( ( xIndex * Size.x ) + Translate.x + (Size.x) )-NeedPos.x);
	float yDistance_Top_Right = (float)((	( yIndex * Size.y ) + Translate.y + (Size.y)  )-NeedPos.z);

	float Top_Right_Total = xDistance_Top_Right*xDistance_Top_Right + yDistance_Top_Right*yDistance_Top_Right;

	if(shortestDis > Top_Right_Total)
		shortestDis = Top_Right_Total;

	return shortestDis;
}