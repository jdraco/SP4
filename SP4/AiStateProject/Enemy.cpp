#include "Enemy.h"


CEnemy::CEnemy(void)
{


}



CEnemy::~CEnemy(void)
{
}

void CEnemy::SelfInit(void){
		
	Pos.Set(400, 600 ,0);
	Scale.Set(20,20,1);
	Vel.Set(5,5,1);
	Color.Set(1.0f,1.0f,1.0f);

	active = true;
	placing = false;
	State = OBJECT_STATE::ATTACK;

	for(unsigned i = 0; i < CGoodies::theArrayOfGoodies.size(); ++i)
	{
		CGoodies *go = CGoodies::theArrayOfGoodies[i];
		if(go->Object == PLAYER )
		{
			SetTarget(go);
		}
	}

	LoadTGA(&Texture[0], "Texture/TopDownMarisa.tga");
}

bool CEnemy::Update(void){
	//State making
	/*
	if(placing == false){
		for(unsigned i = 0; i < CGoodies::theArrayOfGoodies.size(); ++i)
		{
			CGoodies *go = CGoodies::theArrayOfGoodies[i];
			if(go->Object == PLAYER )
			{
				Player = go;
				placing = true;
				break;
			}
		}
	}
	*/
	Dir = ( Pos - Target->GetPos() ) * 0.1;
	Dir.normalizeVector3D();
	
	
	//cout << State << endl;
	
	StateTime.Update();

	if(StateTime.GetCurrent()< 1){
		if(State == OBJECT_STATE::MOVING || State == OBJECT_STATE::ATTACK){
			StateTime.SetCurrent();
			StateTime.SetTotalTime(5);
			if ( (int)theGlobal->RG.getImmediateResult(1,10) % 2 == 0 )
			{
				State = OBJECT_STATE::MOVING;
			}
			else
			{
				 State = OBJECT_STATE::ATTACK;
			}
		}
	}

	switch (State)
	{
	case OBJECT_STATE::MOVING:
		{
			//cout << ( Pos - Target->GetPos() ).GetMagnitude2D() << endl;
			if( ( Pos - Target->GetPos() ).GetMagnitude2D() > 150){
				Pos = Pos - Vel * Dir * 0.1; //* tempSiren->GetItem(ITEM_ID::SIRENITEM) ;
			}
			else
			{
				static Vector3D SideDir;

				DirTime.Update();

				if(DirTime.GetCurrent()< 1){
					DirTime.SetCurrent();
					DirTime.SetTotalTime(3);

					if( (int)theGlobal->RG.getImmediateResult(1,10) % 2 == 0 ){
						SideDir = Vector3D(Dir.y,Dir.x,1);
					}
					else
					{
						SideDir = Vector3D(-Dir.y,-Dir.x,1);
					}
					SideDir.normalizeVector3D();
				}
					
				Pos = Pos -  Vel * SideDir * 0.1; //* tempSiren->GetItem(ITEM_ID::SIRENITEM) ;
			}
			break;
		}

	case OBJECT_STATE::ATTACK:
		{
			//theGoodFactory.CreateID(CVariable::PLAYER);
			ShotTime.Update();
			
			if(ShotTime.GetCurrent()< 1){
				ShotTime.SetCurrent();
				ShotTime.SetTotalTime(2);
				for(unsigned i = 0; i < CGoodies::theArrayOfGoodies.size(); ++i)
				{
					CGoodies *go = CGoodies::theArrayOfGoodies[i];
					if(!go->active){
						if(go->Object == SHOTS ){
							go->Init(true,Vector3D(Pos.x,Pos.y),Vector3D(0.0f,1.0f,0.0f),Vector3D(5.0f,5.0f,1.0f),0,CVariable::ATTACK,Vector3D(5.0f,5.0f,1.0f) );
							break;
						}
					}
				}
			}
			break;
		}
	default:
		{

			break;
		}
	}
	return true;
}
	
void CEnemy::Render(){
	//glColor3f(0.0f,0.0f,0.0f);
	
	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glColor3f( Color.x,  Color.y,  Color.z);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture(GL_TEXTURE_2D,Texture[0].texID);
	
	
		glTranslatef(Pos.x,Pos.y, 1.0f);
		glScalef(Scale.x,Scale.y,Scale.z);
		//glutSolidCube(2);
		
		glBegin(GL_QUADS);
		
			glTexCoord2f(1.0f,1.0f);
			glVertex2f(1,1);

			glTexCoord2f(0.0f,1.0f);
			glVertex2f(-1,1);

			glTexCoord2f(0.0f,0.0f);
			glVertex2f(-1,-1);

			glTexCoord2f(1.0f,0.0f);
			glVertex2f(1,-1);
		
		glEnd();

		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void CEnemy::SetItem(ITEM_ID item_id , int SetItem){

}

int CEnemy::GetItem(ITEM_ID item_id){
	return 1;
}