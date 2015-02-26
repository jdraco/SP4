#pragma once
#include "Define.h"

class CWayPoint
{
public:		
	vector<Vector3D*> Points;	//list of point to go to
	short index;				//point that the char is at;

	CWayPoint(void):index(0){};
	~CWayPoint(void){};

	void IndexPlus()
	{ 
		++index;					//increase index
		if(index+1 >Points.size())	//reset
			index = 0; 
	};

	Vector3D* getCurrentPoint() 
	{
		return Points[index];
	}; 

};

