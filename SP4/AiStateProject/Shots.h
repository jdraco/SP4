#pragma once
#include "Goodies.h"

class CShots : public CGoodies
{
private:


public:
	CShots(void);
	~CShots(void);

	void SelfInit(void);
	bool Update(void);
	void Render();

	 void SetItem(ITEM_ID item_id , int SetItem);
	 int GetItem(ITEM_ID item_id);
};

