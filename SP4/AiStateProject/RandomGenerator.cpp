#include "RandomGenerator.h"
CRandomGenerator::CRandomGenerator()
{
	randomtype = RNG_NONETYPE;
	randommode = RNG_NONEMODE;
}
CRandomGenerator::~CRandomGenerator()
{

}
void CRandomGenerator::Init(RNG_MODE mode,RNG_TYPE type)
{
	randommode = mode;
	randomtype = type;

	if(mode == RNG_NON_DETERMINISTIC && type == RNG_RAND)
	{
		srand (static_cast<unsigned> (time(NULL)));
	}
}
double CRandomGenerator::getImmediateResult(double min,double max)
{
	if( (randommode == RNG_NON_DETERMINISTIC || randommode == RNG_DETERMINISTIC)  && randomtype == RNG_RAND)
	{
		immediateresult = RandIntMinMax(min,max);
	}
	if(randommode == RNG_NON_DETERMINISTIC && randomtype == RNG_RANDOM_TWISTER)
	{
		RD rd;
		MT mt(rd());
		uniform_int_distribution<int> dist(min, max);
		immediateresult =  dist(mt);
	}//don have deterministic vary for this

	//if(randommode == RNG_DETERMINISTIC && randomtype == RNG_TWISTER)
	//{
	//	MT mt(seed);//got error =P
	//	uniform_int_distribution<int> dist(-5, 5);
	//	immediateresult = dist(mt);
	//}
	if(randommode == RNG_DETERMINISTIC && randomtype == RNG_TWISTER)
	{
		MT mt(time(NULL));
		uniform_int_distribution<int> dist(min, max);
		immediateresult = dist(mt);
	}// twister don really have a non deterministic unless i pass in something random to init it.However it will still behavour like rand() with srand()

	if(randommode == RNG_NON_DETERMINISTIC && randomtype == RNG_RANDOM_DEVICE)
	{
		RD rd;
		uniform_int_distribution<int> dist(min, max);
		immediateresult = dist(rd);
	}
	return immediateresult;
}
void CRandomGenerator::PopulateResult(double size,RNG_MODE mode,RNG_TYPE type,double min,double max)
{
	double result = 0;
	if( (randommode == RNG_NON_DETERMINISTIC || randommode == RNG_DETERMINISTIC)  && randomtype == RNG_RAND)
	{
		for(double i = 0; i<size;++i)
		{
			result = RandIntMinMax(min,max);
			ResultList.push_back(result);
		}
	}

	if(randommode == RNG_NON_DETERMINISTIC && randomtype == RNG_RANDOM_TWISTER)
	{
		RD rd;
		MT mt(rd());

		uniform_int_distribution<int> dist(min, max);

		for(double i = 0; i<size;++i)
		{
			result = dist(mt);
			ResultList.push_back(result);
		}
	}//don have deterministic vary for this

	//if(randommode == RNG_DETERMINISTIC && randomtype == RNG_TWISTER)
	//{
	//	MT mt(seed);//got error =P
	//	uniform_int_distribution<int> dist(-5, 5);
	//	immediateresult = dist(mt);
	//}
	if(randommode == RNG_DETERMINISTIC && randomtype == RNG_TWISTER)
	{
		MT mt(time(NULL));
		//MT mt(seed);//dunno why got error =P
		//have to ve MT mt(10); or some other fix intergel
		uniform_int_distribution<int> dist(min, max);
		for(double i = 0; i<size;++i)
		{
			result = dist(mt);
			ResultList.push_back(result);
		}
	}// twister don really have a non deterministic unless i pass in something random to init it.However it will still behavour like rand() with srand()

	if(randommode == RNG_NON_DETERMINISTIC && randomtype == RNG_RANDOM_DEVICE)
	{
		RD rd;
		uniform_int_distribution<int> dist(min, max);
		for(double i = 0; i<size;++i)
			{
				result = dist(rd);
				ResultList.push_back(result);
			}
	}

}
void CRandomGenerator::RecordResult()
{
	ResultList.push_back(immediateresult);
}
void CRandomGenerator::RecordResult(double result)
{
	ResultList.push_back(result);
}
void CRandomGenerator::PrintResultList()
{
	for(int i = 0 ; i<ResultList.size(); ++i )
	{
		cout <<"<"<<i<<"> :"<< ResultList[i] << endl;
	}
}
void CRandomGenerator::setRNGMode(RNG_MODE mode)
{
	randommode = mode;
}
void CRandomGenerator::setRNGType(RNG_TYPE type)
{
	randomtype = type;
}
CRandomGenerator::RNG_MODE CRandomGenerator::getRNGMode()
{
	return randommode;
}
CRandomGenerator::RNG_TYPE CRandomGenerator::getRNGType()
{
	return randomtype;
}