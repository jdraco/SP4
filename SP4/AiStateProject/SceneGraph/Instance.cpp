#include "Instance.h"
#include <cstdlib>

CInstance::CInstance()
	: Mod (NULL)
{
	Mod = new CModel();
}

CInstance::~CInstance()
{
	if (Mod != NULL)
	{
		delete Mod;
		Mod = NULL;
	}
}

void CInstance::Draw()
{
	if(Mod) 
		Mod->Draw();
}

void CInstance::SetColor(const float red, const float green, const float blue)
{
	Mod->SetColor(red, green, blue);
}

Vector3D CInstance::GetColor()
{
	return Mod->GetColor();
}

// Get the top left of the bounding box of the instance
Vector3D CInstance::GetFrontTopLeft()
{
	return Mod->GetFrontTopLeft();
}

Vector3D CInstance::GetFrontTopRight()
{
	return Mod->GetFrontTopRight();
}

Vector3D CInstance::GetFrontBottomLeft()
{
	return Mod->GetFrontBottomLeft();
}

Vector3D CInstance::GetFrontBottomRight()
{
	return Mod->GetFrontBottomRight();
}

// Get the bottomright of the bounding box of the instance
Vector3D CInstance::GetBackBottomRight()
{
	return Mod->GetBackBottomRight();
}

Vector3D CInstance::GetBackTopLeft()
{
	return Mod->GetBackTopLeft();
}

Vector3D CInstance::GetBackTopRight()
{
	return Mod->GetBackTopRight();
}

Vector3D CInstance::GetBackBottomLeft()
{
	return Mod->GetBackBottomLeft();
}