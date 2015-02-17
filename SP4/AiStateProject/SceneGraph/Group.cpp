#include "Group.h"
#include "Matrix4x4.h"
#include <cstdlib>

CGroup::CGroup()
	: theInstance(NULL)
	, theChildren(NULL)
	, theTransform(NULL)
	, sceneNodeID(-1)
	, objectType(NONE)
{
	rendered = false;
	ColorChange = false;
	active = true;
	BeforeColor = Vector3D(0.0f,0.0f,0.0f);

	obtainable = false;
}

CGroup::~CGroup()
{
	if (theChildren.size() != 0)
	{
		CNode* aChild = NULL;
		for (unsigned i=0; i<theChildren.size(); i++)
		{
			aChild = theChildren[i];
			delete aChild;
			aChild = NULL;
		}
		theChildren.clear();
	}

	if (theTransform != NULL)
	{
		delete theTransform;
		theTransform = NULL;
	}
	if (theInstance != NULL)
	{
		delete theInstance;
		theInstance = NULL;
	}
}

void CGroup::Draw()
{
	if (theTransform)
	{
		glPushMatrix();
		glMultMatrixf((theTransform->GetTransform()).matrix);

		if (theInstance)
			theInstance->Draw();

		if (theChildren.size() != 0)
		{
			for (unsigned i=0; i<theChildren.size(); i++)
				theChildren[i]->Draw();
		}

		glPopMatrix();
	}
}

void CGroup::SetInstance(CInstance* theInstance)
{
	this->theInstance = theInstance;
}

short CGroup::SetNode(CTransform* aNewTransform, CInstance* aNewInstance)
{
	/*aNewGroup->SetInstance(aNewInstance);
	aNewTransform->SetGroup(aNewGroup);
	theTransform = aNewTransform;*/

	this->theInstance = aNewInstance;
	this->theTransform = aNewTransform;

	//Set sceneNodeID to 1 as this is the root node
	sceneNodeID = 1;
	return sceneNodeID;
}

short CGroup::AddChild(CTransform* aNewTransform, CInstance* aNewInstance)
{
	/*aNewGroup->SetInstance(aNewInstance);
	aNewGroup->SetSceneNodeID(sceneNodeID*10 + (theChildren.size()+1));
	aNewTransform->SetGroup(aNewGroup);
	theChildren.push_back(aNewTransform);
	NumChildren = theChildren.size();*/

	CGroup* aNewNode = new CGroup();
	aNewNode->SetNode(aNewTransform, aNewInstance);
	aNewNode->SetSceneNodeID(sceneNodeID*10 + (theChildren.size()+1));
	theChildren.push_back(aNewNode);

	return aNewNode->GetSceneNodeID();
}

short CGroup::AddGroup(CGroup *aNewGroup)
{
	aNewGroup->SetSceneNodeID(sceneNodeID*10 + (theChildren.size()+1));
	theChildren.push_back(aNewGroup);

	return aNewGroup->GetSceneNodeID();
}

void CGroup::SetTransform(CTransform* aNewTransform)
{
	theTransform = aNewTransform; 
}

void CGroup::ApplyTranslate(const float dx, const float dy, const float dz, bool local)
{
	if (theTransform)
		theTransform->ApplyTranslate(dx, dy, dz);

	/*list<CNode*>::iterator i;
	for(i=theChildren.begin(); i != theChildren.end(); ++i) 
		((CTransform*)(*i))->SetTranslate(dx, dy, dz);*/

	/*for (unsigned short i = 0; i < theChildren.size(); ++i)
		((CTransform*)(theChildren[i]))->SetTranslate(dx, dy, dz);*/
}

void CGroup::ApplyRotate(const float angle, const float rx, const float ry, const float rz)
{
	if (theTransform)
		theTransform->ApplyRotate(angle, rx, ry, rz);

	/*list<CNode*>::iterator i;
	for(i=theChildren.begin(); i != theChildren.end(); ++i) 
		((CTransform*)(*i))->SetRotate(angle, rx, ry, rz, true);*/

	/*for (unsigned short i = 0; i < theChildren.size(); ++i)
		((CTransform*)(theChildren[i]))->SetRotate(angle, rx, ry, rz, true);*/
}

void CGroup::ApplyScale(const float sx, const float sy, const float sz)
{
	if (theTransform)
		theTransform->ApplyScale(sx, sy, sz);
}

short CGroup::GetNumOfChild()
{
	return (int)theChildren.size();
}

void CGroup::SetSceneNodeID(const int sceneNodeID)
{
	this->sceneNodeID = sceneNodeID;
}

short CGroup::GetSceneNodeID()
{
	return sceneNodeID;	
}

void CGroup::SetColorForChild(const int m_iChildIndex, const float red, const float green, const float blue)
{
	CGroup* aChild = NULL;

	for (unsigned i = 0; i < theChildren.size(); ++i)
	{
		aChild = (CGroup*)theChildren[i];

		if (aChild->GetSceneNodeID() == m_iChildIndex) 
			aChild->SetColor(red, green, blue);
	}
}

bool CGroup::GetBackTopLeftChild(const int m_iChildIndex, Vector3D& vector3D_BottomRight)
{
	vector3D_BottomRight = Vector3D(-999, -999, -999);
	CGroup* aChild = NULL;
	for (unsigned i=0; i<theChildren.size(); i++)
	{
		aChild = (CGroup*)theChildren[i];

		if (aChild->GetSceneNodeID() == m_iChildIndex)
		{
			vector3D_BottomRight = aChild->GetBackTopLeftChild() * theTransform->GetTransform();
			return true;
		}
	}
	return false;
}

bool CGroup::GetBackTopRightChild(const int m_iChildIndex, Vector3D& vector3D_BottomRight)
{
	vector3D_BottomRight = Vector3D(-999, -999, -999);
	CGroup* aChild = NULL;
	for (unsigned i=0; i<theChildren.size(); i++)
	{
		aChild = (CGroup*)theChildren[i];

		if (aChild->GetSceneNodeID() == m_iChildIndex)
		{
			vector3D_BottomRight = aChild->GetBackTopRightChild() * theTransform->GetTransform();
			return true;
		}
	}
	return false;
}

bool CGroup::GetBackBottomLeftChild(const int m_iChildIndex, Vector3D& vector3D_BottomRight)
{
	vector3D_BottomRight = Vector3D(-999, -999, -999);
	CGroup* aChild = NULL;
	for (unsigned i=0; i<theChildren.size(); i++)
	{
		aChild = (CGroup*)theChildren[i];

		if (aChild->GetSceneNodeID() == m_iChildIndex)
		{
			vector3D_BottomRight = aChild->GetBackBottomLeftChild() * theTransform->GetTransform();
			return true;
		}
	}
	return false;
}

//Original
bool CGroup::GetBackBottomRightChild(const int m_iChildIndex, Vector3D& vector3D_BottomRight)
{
	vector3D_BottomRight = Vector3D(-999, -999, -999);
	CGroup* aChild = NULL;
	for (unsigned i=0; i<theChildren.size(); i++)
	{
		aChild = (CGroup*)theChildren[i];

		if (aChild->GetSceneNodeID() == m_iChildIndex)
		{
			vector3D_BottomRight = aChild->GetBackBottomRightChild() * theTransform->GetTransform();
			return true;
		}
	}
	return false;
}

//Original
bool CGroup::GetFrontTopLeftChild(const int m_iChildIndex, Vector3D& vector3D_TopLeft)
{
	vector3D_TopLeft = Vector3D(-999, -999, -999);
	CGroup* aChild = NULL;

	for (unsigned i = 0; i < theChildren.size(); ++i)
	{
		aChild = (CGroup*)theChildren[i];

		if (aChild->GetSceneNodeID() == m_iChildIndex)
		{
			vector3D_TopLeft = aChild->GetFrontTopLeftChild() * theTransform->GetTransform();
			return true;
		}
	}
	return false;
}

bool CGroup::GetFrontTopRightChild(const int m_iChildIndex, Vector3D& vector3D_TopLeft)
{
	vector3D_TopLeft = Vector3D(-999, -999, -999);
	CGroup* aChild = NULL;

	for (unsigned i = 0; i < theChildren.size(); ++i)
	{
		aChild = (CGroup*)theChildren[i];

		if (aChild->GetSceneNodeID() == m_iChildIndex)
		{
			vector3D_TopLeft = aChild->GetFrontTopRightChild() * theTransform->GetTransform();
			return true;
		}
	}
	return false;
}

bool CGroup::GetFrontBottomLeftChild(const int m_iChildIndex, Vector3D& vector3D_TopLeft)
{
	vector3D_TopLeft = Vector3D(-999, -999, -999);
	CGroup* aChild = NULL;

	for (unsigned i = 0; i < theChildren.size(); ++i)
	{
		aChild = (CGroup*)theChildren[i];

		if (aChild->GetSceneNodeID() == m_iChildIndex)
		{
			vector3D_TopLeft = aChild->GetFrontBottomLeftChild() * theTransform->GetTransform();
			return true;
		}
	}
	return false;
}

bool CGroup::GetFrontBottomRightChild(const int m_iChildIndex, Vector3D& vector3D_TopLeft)
{
	vector3D_TopLeft = Vector3D(-999, -999, -999);
	CGroup* aChild = NULL;

	for (unsigned i = 0; i < theChildren.size(); ++i)
	{
		aChild = (CGroup*)theChildren[i];

		if (aChild->GetSceneNodeID() == m_iChildIndex)
		{
			vector3D_TopLeft = aChild->GetFrontBottomRightChild() * theTransform->GetTransform();
			return true;
		}
	}
	return false;
}

Vector3D CGroup::GetBackTopLeftChild()
{
	if (theTransform == NULL)
		return Vector3D(theInstance->GetFrontTopLeft().x, 
						theInstance->GetFrontTopLeft().y, 
						theInstance->GetBackBottomRight().z);
	else
		return (theInstance->GetBackTopLeft() * theTransform->GetTransform());
}

Vector3D CGroup::GetBackTopRightChild()
{
	if (theTransform == NULL)
		return Vector3D(theInstance->GetBackBottomRight().x, 
						theInstance->GetFrontTopLeft().y, 
						theInstance->GetBackBottomRight().z);
	else
		return (theInstance->GetBackTopRight() * theTransform->GetTransform());
}

Vector3D CGroup::GetBackBottomLeftChild()
{
	if (theTransform == NULL)
		return Vector3D(theInstance->GetFrontTopLeft().x, 
						theInstance->GetBackBottomRight().y, 
						theInstance->GetBackBottomRight().z);
	else
		return (theInstance->GetBackBottomLeft() * theTransform->GetTransform());
}

//Original
Vector3D CGroup::GetBackBottomRightChild()
{
	if (theTransform == NULL)
		return Vector3D(theInstance->GetBackBottomRight().x, 
						theInstance->GetBackBottomRight().y, 
						theInstance->GetBackBottomRight().z);
	else
		return (theInstance->GetBackBottomRight() * theTransform->GetTransform());
}

//Original
Vector3D CGroup::GetFrontTopLeftChild()
{
	if (theTransform == NULL)
		return Vector3D(theInstance->GetFrontTopLeft().x, 
						theInstance->GetFrontTopLeft().y, 
						theInstance->GetFrontTopLeft().z);
	else
		return (theInstance->GetFrontTopLeft() * theTransform->GetTransform());
}

Vector3D CGroup::GetFrontTopRightChild()
{
	if (theTransform == NULL)
		return Vector3D(theInstance->GetBackBottomRight().x, 
						theInstance->GetFrontTopLeft().y, 
						theInstance->GetFrontTopLeft().z);
	else
		return (theInstance->GetFrontTopRight() * theTransform->GetTransform());
}

Vector3D CGroup::GetFrontBottomLeftChild()
{
	if (theTransform == NULL)
		return Vector3D(theInstance->GetFrontTopLeft().x, 
						theInstance->GetBackBottomRight().y, 
						theInstance->GetFrontTopLeft().z);
	else
		return (theInstance->GetFrontBottomLeft() * theTransform->GetTransform());
}

Vector3D CGroup::GetFrontBottomRightChild()
{
	if (theTransform == NULL)
		return Vector3D(theInstance->GetBackBottomRight().x, 
						theInstance->GetBackBottomRight().y, 
						theInstance->GetFrontTopLeft().z);
	else
		return (theInstance->GetFrontBottomRight() * theTransform->GetTransform());
}

Vector3D CGroup::GetBackTopLeft() 
{
	return (theInstance->GetBackTopLeft()*theTransform->GetTransform());
}

Vector3D CGroup::GetBackTopRight() 
{
	return (theInstance->GetBackTopRight()*theTransform->GetTransform());
}

Vector3D CGroup::GetBackBottomLeft() 
{
	return (theInstance->GetBackBottomLeft()*theTransform->GetTransform());
}

Vector3D CGroup::GetBackBottomRight() //Original
{
	return (theInstance->GetBackBottomRight()*theTransform->GetTransform());
}

Vector3D CGroup::GetFrontTopLeft() //Original
{
	return (theInstance->GetFrontTopLeft()*theTransform->GetTransform());
}

Vector3D CGroup::GetFrontTopRight() 
{
	return (theInstance->GetFrontTopRight()*theTransform->GetTransform());
}

Vector3D CGroup::GetFrontBottomLeft() 
{
	return (theInstance->GetFrontBottomLeft()*theTransform->GetTransform());
}

Vector3D CGroup::GetFrontBottomRight() 
{
	return (theInstance->GetFrontBottomRight()*theTransform->GetTransform());
}

void CGroup::SetColor(const float red, const float green, const float blue)
{
	theInstance->SetColor(red, green, blue);
}

Vector3D CGroup::GetColor()
{
	return theInstance->GetColor();
}

Vector3D CGroup::GetPos()
{
	float x = theTransform->GetTransform().matrix[theTransform->GetTransform().INDEX4(0,3)];
	float y = theTransform->GetTransform().matrix[theTransform->GetTransform().INDEX4(1,3)];
	float z = theTransform->GetTransform().matrix[theTransform->GetTransform().INDEX4(2,3)];

	return Vector3D(x,y,z);
}

void CGroup::SetPos(float x, float y, float z)
{
	theTransform->Mtx.matrix[theTransform->GetTransform().INDEX4(0,3)] = x;
	theTransform->Mtx.matrix[theTransform->GetTransform().INDEX4(1,3)] = y;
	theTransform->Mtx.matrix[theTransform->GetTransform().INDEX4(2,3)] = z;
}

Vector3D CGroup::GetRot()
{
	Matrix4x4 Source = theTransform->GetTransform();

	float thetaX, thetaY, thetaZ = 0.0f;
	thetaX = asin(Source.matrix[Source.INDEX4(2,1)]); //M32

    if (thetaX < (Math::PI * 0.5))
    {
        if (thetaX > (-Math::PI * 0.5))
        {
            thetaZ = atan2(-(float)(Source.INDEX4(0,1)), (float)(Source.INDEX4(1,1))); //M12, M22
            thetaY = atan2(-(float)(Source.INDEX4(2,0)), (float)(Source.INDEX4(2,2))); //M31, M33
        }
        else
        {
            thetaZ = -atan2(-(float)(Source.INDEX4(0,0)), (float)(Source.INDEX4(1,0))); //M13, M11
            thetaY = 0;
        }
    }
    else
    {
        thetaZ = atan2((float)(Source.INDEX4(0,0)), (float)(Source.INDEX4(1,0))); //M13, M11
        thetaY = 0;
    }

	return Vector3D(Math::RadianToDegree(thetaX), 
					Math::RadianToDegree(thetaY),
					Math::RadianToDegree(thetaZ));
}

void CGroup::SetRot(float angle, short x, short y, short z)
{
	//X
	if (x >= 1)
	{
		theTransform->Mtx.matrix[theTransform->Mtx.INDEX4(1,1)] = cos(Math::DegreeToRadian(angle));
		theTransform->Mtx.matrix[theTransform->Mtx.INDEX4(1,2)] = -sin(Math::DegreeToRadian(angle));
		theTransform->Mtx.matrix[theTransform->Mtx.INDEX4(2,1)] = sin(Math::DegreeToRadian(angle));
		theTransform->Mtx.matrix[theTransform->Mtx.INDEX4(2,2)] = cos(Math::DegreeToRadian(angle));
	}

	//Y
	if (y >= 1)
	{
		theTransform->Mtx.matrix[theTransform->Mtx.INDEX4(0,0)] = cos(Math::DegreeToRadian(angle));
		theTransform->Mtx.matrix[theTransform->Mtx.INDEX4(2,0)] = -sin(Math::DegreeToRadian(angle));
		theTransform->Mtx.matrix[theTransform->Mtx.INDEX4(0,2)] = sin(Math::DegreeToRadian(angle));
		theTransform->Mtx.matrix[theTransform->Mtx.INDEX4(2,2)] = cos(Math::DegreeToRadian(angle));
	}

	//Z
	if (z >= 1)
	{
		theTransform->Mtx.matrix[theTransform->Mtx.INDEX4(0,0)] = cos(Math::DegreeToRadian(angle));
		theTransform->Mtx.matrix[theTransform->Mtx.INDEX4(0,1)] = -sin(Math::DegreeToRadian(angle));
		theTransform->Mtx.matrix[theTransform->Mtx.INDEX4(1,0)] = sin(Math::DegreeToRadian(angle));
		theTransform->Mtx.matrix[theTransform->Mtx.INDEX4(1,1)] = cos(Math::DegreeToRadian(angle));
	}
}