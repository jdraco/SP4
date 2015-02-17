#include "GameTime.h"


CGameTime::CGameTime(void)
{
	current_clock=old_clock=CurrentTime=0;
}


CGameTime::~CGameTime(void)
{
}


void CGameTime::Update(void){

	if (CurrentTime > 0){
			current_clock = clock();
			elapsedSecond = ((current_clock - old_clock) / CLOCKS_PER_SEC) ;
			CurrentTime = TotalTime - elapsedSecond;
	}
}

void CGameTime::SetTotalTime(int TempTT){
	CurrentTime = TotalTime = TempTT;
}

int CGameTime::GetTotalTime(void){
	return TotalTime;
}

void CGameTime::SetCurrent(){
	current_clock = old_clock = CurrentTime = 0;
	old_clock = clock();
}
	
int CGameTime::GetCurrent(void){
	return CurrentTime;
}

float CGameTime::GetDelta(){
	//Set Time
	static int previousTime = 0;
	int currentTime = timeGetTime();

	//Calculate Time Passed
	int timeInterval = currentTime - previousTime;
	int dtPTime = currentTime;
	int dt = (float)((currentTime-dtPTime)*0.001);
	return dt;
}