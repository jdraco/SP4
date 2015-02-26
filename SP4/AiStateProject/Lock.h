#include "Function.h"
#include "Variable.h"
#define LOCK_SIZE 300
#define RANGE 30
class CLock : public CVariable
{
public:
	 CLock(void);
	~CLock(void);
	void Render();
	bool Update(int D,bool turn);
	void Reset();
	bool active;
	int stuckCount;
	int stuckDir;
};