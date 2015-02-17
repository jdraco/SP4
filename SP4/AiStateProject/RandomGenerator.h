#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H
#include <iostream>
#include <random>
#include <algorithm>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;

typedef mt19937 MT;
typedef random_device RD;
//namespace DEFAULT_SEED
//{
//	double DefaultRand = time(NULL);
//};
class CRandomGenerator
{
	public:
		enum RNG_TYPE
		{
			RNG_NONETYPE,
			RNG_RAND,
			RNG_TWISTER,
			RNG_RANDOM_DEVICE,
			RNG_RANDOM_TWISTER,
			RNG_TOTAL
		};
		enum RNG_MODE
		{
			RNG_NONEMODE,
			RNG_DETERMINISTIC,
			RNG_NON_DETERMINISTIC,
			RNG_TOTALMODE
		};



	private:
		vector <int> ResultList;
		RNG_TYPE randomtype;
		RNG_MODE randommode;
		double immediateresult;
	protected:
	public:
		CRandomGenerator();
		~CRandomGenerator();
		void Init(RNG_MODE mode,RNG_TYPE type);
		double getImmediateResult(double min,double max);
		void setRNGMode(RNG_MODE mode);
		void setRNGType(RNG_TYPE type);
		RNG_MODE getRNGMode();
		RNG_TYPE getRNGType();
		void PopulateResult(double size,RNG_MODE mode,RNG_TYPE type,double min,double max);
		void RecordResult();
		void RecordResult(double result);
		void PrintResultList();


	//Return a random integer
	inline unsigned RandInt(void)
	{
		return rand();
	}
	
	//Return a random integer between min and max
	inline int RandIntMinMax (int min, int max)
	{
		int num = rand() % (max - min + 1);
		return (num + min);
	}
	
	//Return a random float
	inline float RandFloat (void)
	{
		return rand() / static_cast <float> (RAND_MAX);
	}

	//Return a random float between min and max
	inline float RandFloatMinMax (float min, float max)
	{
		float num = (max - min) * RandFloat ();
		return (num + min);
	}
};
#endif

