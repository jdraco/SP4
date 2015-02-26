#pragma once
#include <iostream>
#include"Goodies.h"
#include "Global.h"
#include<string>

class CNpc : public CVariable
{
public:
	
	CNpc();
	~CNpc();
	void render();
	void init();
	void Update();
	void Popup();
	void Msg();
private:
	CGlobal *theGlobal;
	int dir;
};
