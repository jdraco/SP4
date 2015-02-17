#ifndef GOODIES_H
#define GOODIES_H
//#include "Global.h"
#include "Variable.h"

class CGoodies: public CVariable
{
//protected:

public:
	CGoodies(void);
	~CGoodies(void);
	
	static Region SafeArea;
	static Region Boundary;
	static Region Inner[3][3];
	static CGameTime theGameTime;
	/*
	//Variable to check outside
	bool active;
	*/
	static std::vector<CGoodies *> theArrayOfGoodies;

	//Function that needs to be added in for classes inheriting this class 
	virtual void SelfInit(void) = 0;
	virtual bool Update(void) = 0;
	virtual void Render(void) = 0;
	virtual void SetItem(ITEM_ID item_id , int SetItem ) = 0;
	virtual int GetItem(ITEM_ID item_id) = 0;

};

#endif 