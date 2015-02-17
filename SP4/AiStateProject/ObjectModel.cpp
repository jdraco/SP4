#include "ObjectModel.h"
#include "GL/glut.h"

#include <iostream>
using namespace std;

CObjectModel::CObjectModel()
	: Position(10,0,10)
	, theObj_HighPoly(0)
	, theObj_MedPoly(0)
	, theObj_LowPoly(0)
{}

CObjectModel::~CObjectModel() {}

void CObjectModel::Init()
{
	
	 theObj_HighPoly = LoadOBJ("Obj/SideTable_High.obj");
	 theObj_MedPoly = LoadOBJ("Obj/SideTable_Med.obj");
	 theObj_LowPoly = LoadOBJ("Obj/SideTable_Low.obj");

	 //theObj_Sofa = LoadOBJ("Obj/Sofa.obj");
		
	vTopLeft = Vector3D(3.0f , 3.0f, 3.0f);
	vBottomRight = Vector3D(-3.0f, -3.0f, -3.0f);


	
}

void CObjectModel::Render()
{

	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glColor3f(Color.x,Color.y,Color.z);
	glTranslatef(Position.x, Position.y, Position.z);
	glRotatef(180, 0, 1, 0);
	//float ScaleValue = 0.3f;
	//glScalef(ScaleValue,ScaleValue,ScaleValue);

	if(Color == Vector3D(LOWRES))
		DrawOBJ(theObj_LowPoly);
	if(Color == Vector3D(MIDRES))
		DrawOBJ(theObj_MedPoly);
	if(Color == Vector3D(HIGHRES))
		DrawOBJ(theObj_HighPoly);

	//DrawBoundingBox();
		//glPushMatrix();
		//	DrawBoundingBox();
	//	glPopMatrix();

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}
/*
void CObjectModel::Render(const int RESOLUTION)
{
	glPushMatrix();

		glTranslatef(Position.x, Position.y, Position.z);
		switch (RESOLUTION)
		{
		case 0:
			glColor3f(0,1,0);
			DrawOBJ(theObj_HighPoly);
			break;
		case 1:
			glColor3f(0,0,1);
			DrawOBJ(theObj_MedPoly);
			break;
		case 2:
			glColor3f(1,0,0);
			DrawOBJ(theObj_LowPoly);
			break;
		} glColor3f(1,1,1);

	glPopMatrix();
}
*/
void CObjectModel::SetPosition(Vector3D theNewPosition)
{
	this->Position = theNewPosition;
}

void CObjectModel::SetColor(const float red, const float green, const float blue)
{
	Vector3D temp =  Vector3D(red, green, blue);
	this->Color = temp;
}

void CObjectModel::DrawBoundingBox()
{
	
	glColor3f(0,0,0);
	glPushMatrix();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(Color.x,Color.y,Color.z, 0.05f);
	//glTranslatef(Position.x, Position.y, Position.z);
	glBegin(GL_QUADS);

	/*      This is the top face*/
	glVertex3f(vTopLeft.x, vTopLeft.y, vTopLeft.z);
	glVertex3f(vTopLeft.x, vTopLeft.y, vBottomRight.z);
	glVertex3f(vBottomRight.x, vTopLeft.y, vBottomRight.z);
	glVertex3f(vBottomRight.x, vTopLeft.y, vTopLeft.z);

	/*      This is the front face*/
	glVertex3f(vTopLeft.x, vTopLeft.y, vTopLeft.z);
	glVertex3f(vBottomRight.x, vTopLeft.y, vTopLeft.z);
	glVertex3f(vBottomRight.x, vBottomRight.y, vTopLeft.z);
	glVertex3f(vTopLeft.x, vBottomRight.y, vTopLeft.z);


	/*      This is the right face*/
	glVertex3f(vTopLeft.x, vTopLeft.y, vTopLeft.z);
	glVertex3f(vTopLeft.x, vBottomRight.y, vTopLeft.z);
	glVertex3f(vTopLeft.x, vBottomRight.y, vBottomRight.z);
	glVertex3f(vTopLeft.x, vTopLeft.y, vBottomRight.z);

	/*      This is the left face*/
	glVertex3f(vBottomRight.x, vTopLeft.y, vTopLeft.z);
	glVertex3f(vBottomRight.x, vTopLeft.y, vBottomRight.z);
	glVertex3f(vBottomRight.x, vBottomRight.y, vBottomRight.z);
	glVertex3f(vBottomRight.x, vBottomRight.y, vTopLeft.z);

	/*      This is the bottom face*/
	glVertex3f(vTopLeft.x, vBottomRight.y, vTopLeft.z);
	glVertex3f(vTopLeft.x, vBottomRight.y, vBottomRight.z);
	glVertex3f(vBottomRight.x, vBottomRight.y, vBottomRight.z);
	glVertex3f(vBottomRight.x, vBottomRight.y, vTopLeft.z);

	/*      This is the back face*/
	glVertex3f(vTopLeft.x, vTopLeft.y, vBottomRight.z);
	glVertex3f(vBottomRight.x, vTopLeft.y, vBottomRight.z);
	glVertex3f(vBottomRight.x, vBottomRight.y, vBottomRight.z);
	glVertex3f(vTopLeft.x, vBottomRight.y, vBottomRight.z);

	glEnd();
	glColor4f(1,1,1,1);
	glDisable(GL_BLEND);
	glPopMatrix();
}