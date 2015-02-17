#include "Shots.h"


CShots::CShots(void)
{

}


CShots::~CShots(void)
{
}


void CShots::SelfInit(void){
	Scale.Set(5,5,1);
	Vel.Set(5,5,1);
	Color.Set(1.0f,1.0f,0.0f);

	active = false;

	for(unsigned i = 0; i < CGoodies::theArrayOfGoodies.size(); ++i)
	{
		CGoodies *go = CGoodies::theArrayOfGoodies[i];
		if(go->Object == PLAYER )
		{
			SetTarget(go);
		}
	}
}

bool CShots::Update(void){
	//State making
	Dir = ( Pos - Target->GetPos() ) * 0.1;
	Dir.normalizeVector3D();

	Pos = Pos - Vel * Dir * 0.1; //* tempSiren->GetItem(ITEM_ID::SIRENITEM) ;
	
	//cout << "shot" << endl;
	///cout <<( Pos - Target->GetPos() ).GetMagnitude2D()<<endl;


	if(  ( Pos - Target->GetPos() ).GetMagnitude2D() < 10){
		active = false;
		cout << "gone" << endl;
	}
	

	return true;

}
	
void CShots::Render(){
	glPushMatrix();
		glColor3f( Color.x, Color.y, Color.z);
		glTranslatef(Pos.x,Pos.y,Pos.z);
		glScalef(Scale.x,Scale.y,Scale.z);
		glutSolidCube(2);
	glPopMatrix();
}

void CShots::SetItem(ITEM_ID item_id , int SetItem){

}

int CShots::GetItem(ITEM_ID item_id){
	return 1;
}