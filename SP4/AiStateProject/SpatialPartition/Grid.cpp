#include "Grid.h"

CGrid::CGrid()
	: Index(Vector3D(0,0))
	, Size(Vector3D(1,1))
	, Translate(Vector3D(0,0))
	, ListOfObjects(NULL)
{}

CGrid::~CGrid() {
	//DeleteObjects(); 
}

void CGrid::Init(const int index_x, const int index_y, const int xSize, const int ySize, Vector3D Translate)
{
	this->Index.Set((float)index_x, (float)index_y);
	this->Size.Set((float)xSize, (float)ySize);
	this->Translate.Set(Translate);
}

void CGrid::AddObject(CObjectModel* theObject) { ListOfObjects.push_back(theObject); }

void CGrid::AddObject(CGroup* theObject) { ListOfGroups.push_back(theObject); }

void CGrid::RenderScene()
{
	for(short i = 0; i < (short)ListOfObjects.size(); ++i)
		ListOfObjects[i]->Render();

	glPushMatrix();
	glTranslatef((float)(Index.x*Size.x)+Translate.x, Translate.z , (float)(Index.y*Size.y)+Translate.y );

		glPushAttrib(GL_ENABLE_BIT);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			
			glColor3f(Color.x, Color.y, Color.z);
			//glColor4f(Color.x, Color.y, Color.z, 0.6f);
			glBegin(GL_QUADS);
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f(Size.x, 0.0f, 0.0f);

				glVertex3f(Size.x, 0.0f, Size.y);
				glVertex3f(0.0f, 0.0f, Size.y);
			glEnd();
			glDisable(GL_BLEND);
		glPopAttrib();

		glPushAttrib(GL_ENABLE_BIT);
			glColor3f(1.0f, 1.0f, 1.0f);
			glLineWidth(10);
			glBegin(GL_LINES);
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f(Size.x, 0.0f, 0.0f);
				
				glVertex3f(Size.x, 0.0f, 0.0f);
				glVertex3f(Size.x, 0.0f, Size.y);
				
				glVertex3f(Size.x, 0.0f, Size.y);
				glVertex3f(0.0f, 0.0f, Size.y);
				
				glVertex3f(0.0f, 0.0f, Size.y);
				glVertex3f(0.0f, 0.0f, 0.0f);
			glEnd();
			glLineWidth(1);
		glPopAttrib();

	glPopMatrix();
}

void CGrid::RenderObjects(const int RESOLUTION)
{
	glPushAttrib(GL_ENABLE_BIT);

	if( RESOLUTION == 0)
	{
		
		for(short i = 0; i < (short)ListOfGroups.size(); ++i)
			ListOfGroups[i]->SetColor( LOWRES );
			
		for(short x = 0; x < (short)ListOfObjects.size(); ++x)
			ListOfObjects[x]->SetColor(LOWRES);

	}
	if( RESOLUTION == 1)
	{
		
		for(short i = 0; i < (short)ListOfGroups.size(); ++i)
			ListOfGroups[i]->SetColor( MIDRES );
		

		for(short x = 0; x < (short)ListOfObjects.size(); ++x)
			ListOfObjects[x]->SetColor(MIDRES);
	}
	if( RESOLUTION == 2)
	{
		
		for(short i = 0; i < (short)ListOfGroups.size(); ++i)
			ListOfGroups[i]->SetColor( HIGHRES );
			
		for(short x = 0; x < (short)ListOfObjects.size(); ++x)
			ListOfObjects[x]->SetColor(HIGHRES);
	}

	glPopAttrib();
}

void CGrid::DeleteObjects()
{
	if (ListOfObjects.size() != 0)
	{
		CObjectModel* theObject = NULL;
		for (short i = 0; i < (short)ListOfObjects.size(); ++i)
		{
			theObject = ListOfObjects[i];
			delete theObject;
			theObject = NULL;
		}
		ListOfObjects.clear();
	}
}

Vector3D CGrid::GetBtmLeft()
{
	return Vector3D((float)(Index.x*Size.x)+Translate.x+Size.x, 0, (float)(Index.y*Size.y)+Translate.y);
}
Vector3D CGrid::GetTopLeft()
{
	return Vector3D((float)(Index.x*Size.x)+Translate.x+Size.x, 0, (float)(Index.y*Size.y)+Translate.y+Size.y);
}
Vector3D CGrid::GetBtmRight()
{
	return Vector3D((float)(Index.x*Size.x)+Translate.x, 0, (float)(Index.y*Size.y)+Translate.y);
}
Vector3D CGrid::GetTopRight()
{
	return Vector3D((float)(Index.x*Size.x)+Translate.x, 0, (float)(Index.y*Size.y)+Translate.y+Size.y);
}

float CGrid::GetPointRadSquare(float PlayerRad)
{
	return (  GetSizeSquare() + (PlayerRad * PlayerRad) );  // a*2 + b*2 = c*2 //point radius 
}

float CGrid::GetSizeSquare(){
	return (Size.x * 0.5) * (Size.x * 0.5); //a*2
}

bool CGrid::CheckCollision(Vector3D Pos, float Radius)
{
	if (((Pos-GetTopLeft()).GetMagnitudeSquare() < Radius*Radius) ||
		((Pos-GetTopRight()).GetMagnitudeSquare() < Radius*Radius) ||
		((Pos-GetBtmLeft()).GetMagnitudeSquare() < Radius*Radius) ||
		((Pos-GetBtmRight()).GetMagnitudeSquare() < Radius*Radius))
		return true;

	if ( GetPointRadSquare(Radius)  >  (Pos - GetBtmLeft()).GetMagnitudeSquare() 
		&& GetPointRadSquare(Radius)  >  (Pos - GetBtmRight()).GetMagnitudeSquare()
		//&& (Pos.y < GetTopLeft().y) && (Pos.y > GetBtmLeft().y) 
		|| GetPointRadSquare(Radius)  > (Pos - GetBtmLeft()) .GetMagnitudeSquare()
		&& GetPointRadSquare(Radius)   >  (Pos - GetTopLeft())  .GetMagnitudeSquare()

		|| GetPointRadSquare(Radius)  > (Pos - GetTopRight()) .GetMagnitudeSquare()
		&& GetPointRadSquare(Radius)   >  (Pos - GetBtmRight())  .GetMagnitudeSquare()

		|| GetPointRadSquare(Radius)  > (Pos - GetTopRight()) .GetMagnitudeSquare()
		&& GetPointRadSquare(Radius)   >  (Pos - GetTopLeft())  .GetMagnitudeSquare()

		)
		//&& (Pos.x > GetBtmLeft().x) && (Pos.x < GetBtmRight().x) ) 
		
	{
		
		return true;
	}
	return false;
}