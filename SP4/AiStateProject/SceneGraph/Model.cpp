#include "Model.h"

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#include <windows.h> // Header File For Windows
#include <gl\gl.h> // Header File For The OpenGL32 Library
#include <gl\glu.h> // Header File For The GLu32 Library

#include <stdio.h>

CModel::CModel()
{
	vTopLeft = Vector3D(1.0f, 1.0f, 1.0f);
	vBottomRight = Vector3D(-1.0f, -1.0f, -1.0f);
	red = 128;
	green = 255;
	blue = 0;
}

CModel::~CModel() {}

void CModel::DrawSphere()
{
	glPushMatrix();
		glTranslatef(vTopLeft.x, vTopLeft.y, vTopLeft.z);
		glColor3f(1.0,1.0,1.0); 
		glutSolidSphere(0.1f, 9, 9); 
	glPopMatrix();

	glPushMatrix();
		glTranslatef(vBottomRight.x, vBottomRight.y, vBottomRight.z);
		glColor3f(1.0,1.0,1.0); 
		glutSolidSphere(0.1f, 9, 9); 
	glPopMatrix();

	glPushMatrix();
		glTranslatef(vTopLeft.x, vTopLeft.y, vBottomRight.z);
		glColor3f(1.0,1.0,1.0); 
		glutSolidSphere(0.1f, 9, 9); 
	glPopMatrix();

	glPushMatrix();
		glTranslatef(vBottomRight.x, vTopLeft.y, vBottomRight.z);
		glColor3f(1.0,1.0,1.0); 
		glutSolidSphere(0.1f, 9, 9); 
	glPopMatrix();

	glPushMatrix();
		glTranslatef(vTopLeft.x, vBottomRight.y, vBottomRight.z);
		glColor3f(1.0,1.0,1.0); 
		glutSolidSphere(0.1f, 9, 9); 
	glPopMatrix();

	glPushMatrix();
		glTranslatef(vBottomRight.x, vTopLeft.y, vTopLeft.z);
		glColor3f(1.0,1.0,1.0); 
		glutSolidSphere(0.1f, 9, 9); 
	glPopMatrix();

	glPushMatrix();
		glTranslatef(vTopLeft.x, vBottomRight.y, vTopLeft.z);
		glColor3f(1.0,1.0,1.0); 
		glutSolidSphere(0.1f, 9, 9); 
	glPopMatrix();

	glPushMatrix();
		glTranslatef(vBottomRight.x, vBottomRight.y, vTopLeft.z);
		glColor3f(1.0,1.0,1.0); 
		glutSolidSphere(0.1f, 9, 9); 
	glPopMatrix();
}

void CModel::DrawLines()
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glLineWidth(5);
	glBegin(GL_LINES);

		//Lines for the top face
		glVertex3f(vTopLeft.x, vTopLeft.y, vTopLeft.z);
		glVertex3f(vTopLeft.x, vTopLeft.y, vBottomRight.z);

		glVertex3f(vTopLeft.x, vTopLeft.y, vBottomRight.z);
		glVertex3f(vBottomRight.x, vTopLeft.y, vBottomRight.z);

		glVertex3f(vBottomRight.x, vTopLeft.y, vBottomRight.z);
		glVertex3f(vBottomRight.x, vTopLeft.y, vTopLeft.z);

		glVertex3f(vBottomRight.x, vTopLeft.y, vTopLeft.z);
		glVertex3f(vTopLeft.x, vTopLeft.y, vTopLeft.z);

		//Lines for the bottom face
		glVertex3f(vTopLeft.x, vBottomRight.y, vTopLeft.z);
		glVertex3f(vTopLeft.x, vBottomRight.y, vBottomRight.z);

		glVertex3f(vTopLeft.x, vBottomRight.y, vBottomRight.z);
		glVertex3f(vBottomRight.x, vBottomRight.y, vBottomRight.z);

		glVertex3f(vBottomRight.x, vBottomRight.y, vBottomRight.z);
		glVertex3f(vBottomRight.x, vBottomRight.y, vTopLeft.z);

		glVertex3f(vBottomRight.x, vBottomRight.y, vTopLeft.z);
		glVertex3f(vTopLeft.x, vBottomRight.y, vTopLeft.z);

		//Lines for the sides of the box
		glVertex3f(vTopLeft.x, vTopLeft.y, vTopLeft.z);
		glVertex3f(vTopLeft.x, vBottomRight.y, vTopLeft.z);

		glVertex3f(vBottomRight.x, vTopLeft.y, vTopLeft.z);
		glVertex3f(vBottomRight.x, vBottomRight.y, vTopLeft.z);

		glVertex3f(vTopLeft.x, vTopLeft.y, vBottomRight.z);
		glVertex3f(vTopLeft.x, vBottomRight.y, vBottomRight.z);

		glVertex3f(vBottomRight.x, vTopLeft.y, vBottomRight.z);
		glVertex3f(vBottomRight.x, vBottomRight.y, vBottomRight.z);

	glEnd();
	glLineWidth(1);
}

void CModel::Draw()
{
	glPushMatrix();

	glColor3f(red, green, blue);
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
	glPopMatrix();

	//Draw lines surrounding the Model
	DrawLines();

	//Draw Points
	//DrawSphere();
}

void CModel::SetColor(const float red, const float green, const float blue)
{
	this->red = red;
	this->green = green;
	this->blue = blue;
}

Vector3D CModel::GetColor(){
	return Vector3D(red,green,blue);
}


//Get the top left of the bounding box of the instance
Vector3D CModel::GetFrontTopLeft()
{
	return Vector3D(vTopLeft.x, vTopLeft.y, vTopLeft.z);
}

Vector3D CModel::GetFrontTopRight() 
{
	return Vector3D(vBottomRight.x, vTopLeft.y, vTopLeft.z);
}

Vector3D CModel::GetFrontBottomLeft() 
{
	return Vector3D(vTopLeft.x, vBottomRight.y, vTopLeft.z);
}

Vector3D CModel::GetFrontBottomRight()
{
	return Vector3D(vBottomRight.x, vBottomRight.y, vTopLeft.z);
}

//Get the bottomright of the bounding box of the instance
Vector3D CModel::GetBackBottomRight()
{
	return Vector3D(vBottomRight.x, vBottomRight.y, vBottomRight.z);
}

Vector3D CModel::GetBackTopLeft()
{
	return Vector3D(vTopLeft.x, vTopLeft.y, vBottomRight.z);
}

Vector3D CModel::GetBackTopRight()
{
	return Vector3D(vBottomRight.x, vTopLeft.y, vBottomRight.z);
}

Vector3D CModel::GetBackBottomLeft()
{
	return Vector3D(vTopLeft.x, vBottomRight.y, vBottomRight.z);
}