#include "Goodies.h"


std::vector<CGoodies *> CGoodies::theArrayOfGoodies;


Region CGoodies::SafeArea;
Region CGoodies::Boundary;
Region CGoodies::Inner[3][3];


CGoodies::CGoodies(void)
{

}


CGoodies::~CGoodies(void)
{
}
