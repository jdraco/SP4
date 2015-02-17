#include "GoodiesFactory.h"


CGoodiesFactory::CGoodiesFactory(void)
{
}


CGoodiesFactory::~CGoodiesFactory(void)
{
}

//CGoodies* 
CGoodies* CGoodiesFactory::CreateID(CVariable::OBJECT_ID Object){
	CGoodies* theNextGoodies = NULL;
		
	switch(Object){

	}
	CGoodies::theArrayOfGoodies.push_back(theNextGoodies);

	return theNextGoodies;
}