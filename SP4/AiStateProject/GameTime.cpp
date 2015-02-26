#include "GameTime.h"

float CGameTime::dt = 0;

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

void CGameTime::UpdateDelta(){
	static int previousTime = 0;
	int currentTime = timeGetTime();

	//Calculate Time Passed
	int timeInterval = currentTime - previousTime;
	int dtPTime = currentTime;
	dt = (float)((currentTime-previousTime)*0.01);

	if(dt > 0.5)
		dt = 0.17;

	previousTime = currentTime;
}


float CGameTime::GetDelta(){
	//Set Time
	return dt;
}