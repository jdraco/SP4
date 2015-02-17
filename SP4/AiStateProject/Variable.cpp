#include "Variable.h"
CVariable::CVariable(void)
		:Pos(0,0,0)
		,Scale(1,1,1)
		,Vel(0,0,0)
		,Dir(1,0,0)
		,active(true)
{
	theGlobal = CGlobal::getInstance();
}

CVariable::~CVariable(void)
{

}


void CVariable::Init (bool active ,Vector3D Pos , Vector3D Color, Vector3D Scale , int Health , OBJECT_STATE State ,
				Vector3D Vel )
{
	this->active = active;
	this->Pos = Pos;
	this->Color = Color;
	this->Health = Health;
	this->Status = Status;
	this->State = State;
	this->Scale = Scale;
	this->Vel = Vel;


	this->Min = Pos-Scale;
	this->Max = Pos+Scale;
}


int CVariable::CalculateDistance(Vector3D tempPos){
	return( (Pos.x- tempPos.x )*(Pos.x - tempPos.x ) + ( Pos.y - tempPos.y)*(Pos.y-tempPos.y )  );
}

void CVariable::SetPos(Vector3D tempPos){
	Pos = tempPos;
}

Vector3D CVariable::GetPos(void){
	return Pos;
}

int CVariable::GetHealth(){
	return Health;
}

void CVariable::SetHealth(int h){
	Health = h;
}

int CVariable::GetDelay(){
	return delay;
}

Vector3D CVariable::GetMin(void){
	return Min;
}

Vector3D CVariable::GetMax(void){
	return Max;
}


/*
void CGoodies::SetmyKeys(bool myKeys[255]){
	CGoodies::myKeys = myKeys;
}
*/
void CVariable::SetTarget(CGoodies *tempTarget){
	Target = tempTarget;
}


void CVariable::DrawBox (Vector3D Size, Vector3D Color)
{
	float cube[][3] = 
	{ 
		-Size.x, Size.y, Size.z, 
		-Size.x,-Size.y, Size.z, 
		Size.x,-Size.y, Size.z, 
		Size.x, Size.y, Size.z, 
		-Size.x, Size.y,-Size.z,
		-Size.x,-Size.y,-Size.z,
		Size.x,-Size.y,-Size.z, 
		Size.x, Size.y,-Size.z, 
	};

	float normal[][3] = 
	{
		0, 0, 1, //TOP
		1, 0, 0,//FRONT
		0, 1, 0, //LEFT
		0, 0, -1,//RIGHT
		-1, 0, 0, //BACK
		0, -1, 0, //DOWN
	};


	//glBindTexture(GL_TEXTURE_2D, texture[TOP].id);
	glColor3f(Color.x, Color.y, Color.z);
	glBegin( GL_QUADS );
	glNormal3fv(normal [5]);
	//glTexCoord2f(0.0f, 10.0f);
	glVertex3fv(cube[4]); 
	//glTexCoord2f(0.0f, 0.0f);
	glVertex3fv(cube[7]); 
	//glTexCoord2f(10.0f, 0.0f);
	glVertex3fv(cube[3]); 
	//glTexCoord2f(10.0f, 10.0f);
	glVertex3fv(cube[0]); 
	glEnd();


	//glBindTexture(GL_TEXTURE_2D, texture[FRONT].id);
	
	//glColor3f(0,0,0);
	glBegin( GL_QUADS );
	glNormal3fv(normal [0]);
	//glTexCoord2f(0.0f, 3.0f);
	glVertex3fv(cube[4]); 
	//glTexCoord2f(0.0f, 0.0f);
	glVertex3fv(cube[5]); 
	//glTexCoord2f(5.0f, 0.0f);
	glVertex3fv(cube[6]); 
	//glTexCoord2f(5.0f, 3.0f);
	glVertex3fv(cube[7]); 
	glEnd();


	//glBindTexture(GL_TEXTURE_2D, texture[RIGHT].id); 
	glColor3f(Color.x, Color.y, Color.z);
	glBegin( GL_QUADS );
	glNormal3fv(normal [4]);
	//glTexCoord2f(10.0f, 2.0f);
	glVertex3fv(cube[3]); 
	//glTexCoord2f(0.0f, 2.0f);
	glVertex3fv(cube[7]); 
	//glTexCoord2f(0.0f, 0.0f);
	glVertex3fv(cube[6]); 
	//glTexCoord2f(10.0f, 0.0f);
	glVertex3fv(cube[2]); 
	glEnd();


	//glBindTexture(GL_TEXTURE_2D, texture[LEFT].id); 
	glColor3f(Color.x, Color.y, Color.z);
	glBegin( GL_QUADS ); 
	glNormal3fv(normal [1]);
	//glTexCoord2f(0.0f, 0.0f);
	glVertex3fv(cube[1]); 
	//glTexCoord2f(15.0f, 0.0f);
	glVertex3fv(cube[5]);
	//glTexCoord2f(15.0f, 3.0f);
	glVertex3fv(cube[4]); 
	//glTexCoord2f(0.0f, 3.0f);
	glVertex3fv(cube[0]); 
	glEnd();

	//glBindTexture(GL_TEXTURE_2D, texture[BACK].id);
	glColor3f(Color.x, Color.y, Color.z);
	glBegin(GL_QUADS); 
	glNormal3fv(normal [3]);
	//glTexCoord2f(10.0f, 2.0f); 
	glVertex3fv(cube[0]); 
	//glTexCoord2f(0.0f, 2.0f); 
	glVertex3fv(cube[3]); 
	//glTexCoord2f(0.0f, 0.0f); 
	glVertex3fv(cube[2]); 
	//glTexCoord2f(10.0f, 0.0f); 
	glVertex3fv(cube[1]); 
	glEnd();


	//glBindTexture(GL_TEXTURE_2D, texture[BOTTOM].id); 
	glColor3f(Color.x, Color.y, Color.z);
	glBegin( GL_QUADS ); 
	glNormal3fv(normal [2]);
	//glTexCoord2f(6, 0);
	glVertex3fv(cube[1]); 
	//glTexCoord2f(0, 0);
	glVertex3fv(cube[2]); 
	//glTexCoord2f(0, 18);
	glVertex3fv(cube[6]);
	//glTexCoord2f(6, 18);
	glVertex3fv(cube[5]);                 
	glEnd();


	glColor3f(1,1,1);	//revert the color back
}