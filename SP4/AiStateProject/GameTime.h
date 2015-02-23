
#ifndef CGAMETIME_H
#define CGAMETIME_H	

#include <time.h>
#include <Windows.h>

class CGameTime
{
private:
	int
		TotalTime,		//Starting time
		CurrentTime,	//time that goes ticking
		PreviousTime,	//the time before
		current_clock,
		elapsedSecond,
		old_clock;

public:
	CGameTime(void);
	~CGameTime(void);
	
	enum EVENT						
	{
		GAMEROUND = 0,
		GAMEBREAK
	};
	
	EVENT EventState;				//Check Which event is up
	//either
	void Init(void);				//Init different time for each state
	//or
	void SetTotalTime(int TempTT);	//Set your timer

	int GetTotalTime(void);			//Get Start time
	int GetCurrent(void);			//Get the current time
	void SetCurrent();
	
	static float GetDelta();			//for delta time

	void Update(void);	
};

#endif