#include "Function.h"
#include "Variable.h"
#define SMALL_TEXT 10
#define BIG_TEXT 20

class CFont : public CVariable
{
public:
	CFont(void);
	~CFont(void);
	void Render(string text, Vector3D pos, Vector3D color);
	void RenderAlphabet(char text, int count);
};