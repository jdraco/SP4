#ifndef GROUP_H
#define GROUP_H

#include "Node.h"
#include "Instance.h"
#include "Transform.h"
#include "../Global.h"

#include <list>
#include <vector>
#include <math.h>

class CGroup : public CNode
{
private:
	CInstance* theInstance;
	CTransform* theTransform;

	short sceneNodeID;

public:
	CGroup();
	~CGroup();

	bool rendered;
	bool active;
	//gameplay
	bool obtainable;

	Vector3D BeforeColor;

	//CNode *Child;
	vector<CNode*> theChildren;

	enum TYPE{
		NONE,
		CUBE
	};

	TYPE objectType;

	bool ColorChange;
	//Get Transform
	CTransform* getTransform() { return theTransform; }

	//Get & Set Pos
	Vector3D GetPos();
	void SetPos(float x, float y, float z);
	Vector3D GetRot();
	void SetRot(float angle, short x, short y, short z);

	void Draw();
	void SetInstance(CInstance* theInstance);
	short SetNode(CTransform* aNewTransform, CInstance* aNewInstance);
	short AddChild(CTransform* aNewTransform, CInstance* aNewInstance);

	void SetTransform(CTransform* aNewTransform);
	void ApplyTranslate(const float dx, const float dy, const float dz, bool local = true);
	void ApplyRotate(const float angle, const float rx, const float ry, const float rz);
	void ApplyScale(const float sx, const float sy, const float sz);

	short AddGroup(CGroup *aNewGroup);

	//Get corners of the ROOT (Back)
	Vector3D GetBackTopLeft();
	Vector3D GetBackTopRight();
	Vector3D GetBackBottomLeft();
	Vector3D GetBackBottomRight();

	//Get corners of the ROOT (Front)
	Vector3D GetFrontTopLeft();
	Vector3D GetFrontTopRight();
	Vector3D GetFrontBottomLeft();
	Vector3D GetFrontBottomRight();


	//Get corners of the CHILD (Back)
	Vector3D GetBackTopLeftChild();
	Vector3D GetBackTopRightChild();
	Vector3D GetBackBottomLeftChild();
	Vector3D GetBackBottomRightChild();

	//Get corners of the CHILD (Front)
	Vector3D GetFrontTopLeftChild();
	Vector3D GetFrontTopRightChild();
	Vector3D GetFrontBottomLeftChild();
	Vector3D GetFrontBottomRightChild();


	//Get top corner of a child (Front)
	bool GetFrontTopLeftChild(const int m_iChildIndex, Vector3D& vector3D_TopLeft);
	bool GetFrontTopRightChild(const int m_iChildIndex, Vector3D& vector3D_TopLeft);
	bool GetFrontBottomLeftChild(const int m_iChildIndex, Vector3D& vector3D_TopLeft);
	bool GetFrontBottomRightChild(const int m_iChildIndex, Vector3D& vector3D_TopLeft);

	//Get bottom corner of a child (Back)
	bool GetBackTopLeftChild(const int m_iChildIndex, Vector3D& vector3D_BottomRight);
	bool GetBackTopRightChild(const int m_iChildIndex, Vector3D& vector3D_BottomRight);
	bool GetBackBottomLeftChild(const int m_iChildIndex, Vector3D& vector3D_BottomRight);
	bool GetBackBottomRightChild(const int m_iChildIndex, Vector3D& vector3D_BottomRight);


	//Return the number of children in this group
	short GetNumOfChild();

	//Get & Set Functions
	void SetSceneNodeID(const int sceneNodeID);
	short GetSceneNodeID();

	//Set the Colour of a child
	void SetColorForChild(const int m_iChildIndex, const float red, const float green, const float blue);

	//Set colour of the instance
	void SetColor(const float red, const float green, const float blue);
	Vector3D GetColor();

	void DeleteOwn(CGroup* temp){
		delete temp;
	}
};

#endif