#ifndef DEFINE_H
#define DEFINE_H		

#include "Function.h"

//defining of standard game 
/*
#define MAX_ANGLE		45
#define SURRENDER_ANGLE 160
#define MAX_THINNER		5
#define MAX_DELAY		100
*/
//#define PI				3.1415926535897932384626433832795028841971693993751058209749445

//OpenGL init
//#define FULLSCREEN			GetIntFromLua("confiq.lua" , "FULLSCREEN")

#define PROGRAM_NAME		GetStringFromLua("confiq.lua" , "PROGRAM_NAME").c_str()

//Windows
#define SCREEN_WIDTH		GetIntFromLua("confiq.lua" , "SCREENWIDTH")
#define SCREEN_HEIGHT		GetIntFromLua("confiq.lua" , "SCREENHEIGHT")



#define RESOLUTION_WIDTH	1024
#define RESOLUTION_HEIGHT	800

//Game Logic

//Map
#define MAP_SCREEN_WIDTH	850 //700 or 850
#define MAP_SCREEN_HEIGHT	700

#define TILE_SIZE			32
#define MAX_TILE			17
#define LEFT_BORDER			TILE_SIZE*2
#define BOTTOM_BORDER		TILE_SIZE*3

//Movement Speed
#define PLAYER_MOVEMENT_SPEED 120.0f
#define MAP_SCROLL_SPEED PLAYER_MOVEMENT_SPEED*(1/41.0f)

//For Spartial part
#define SIGHT_RANGE				(int)LuaReading::getInstance()->sight_range
#define REACH_RANGE				(int)LuaReading::getInstance()->reach_range

#define SIGHT_RADIUS			(int)LuaReading::getInstance()->sight_radius
#define REACH_RADIUS			(int)LuaReading::getInstance()->reach_radius

#define SP_SIZE_X				(int)LuaReading::getInstance()->sp_size_x
#define SP_SIZE_Y				(int)LuaReading::getInstance()->sp_size_y
#define SP_NUM_OF_GRID_X		(int)LuaReading::getInstance()->sp_num_of_grid_x
#define SP_NUM_OF_GRID_Y		(int)LuaReading::getInstance()->sp_num_of_grid_y

#define PLAYER_ROTATE_SPEED		(int)LuaReading::getInstance()->player_rotate_speed		
#define GRAVITY					(int)LuaReading::getInstance()->gravity


//color code
#define RED				1.0f,0.0f,0.0f
#define GREEN			0.0f,1.0f,0.0f
#define BLUE			0.0f,0.0f,1.0f

#define HIGHRES			1.0f,0.5f,0.0f
#define	MIDRES			0.0f,1.0f,0.5f
#define LOWRES			0.5f,0.0f,1.0f



#include <cmath>
#include <exception>
#include <ctime>
#include <cstdlib>

//Math Namespace
namespace Math
{
	const float	EPSILON    = 0.00001f; //Used for error checking
	const float	PI         = 3.1415926535897932384626433832795f;
	const float TWO_PI     = PI * 2.0f;
	const float HALF_PI    = PI / 2.0f;
	const float QUARTER_PI = PI / 4.0f;

	inline float FAbs(float value)
	{
		return (value < 0) ? -value : value;
	}

	//Converts from degrees to radians
	inline float DegreeToRadian(float value)
	{
		return value * PI / 180.0f;
	}

	//Converts from radians to degrees
	inline float RadianToDegree(float value)
	{
		return value * 180.0f / PI;
	}

	//Keeps a value between a min and max point. If it goes to low, it will 
	//become the max. If the value gets too high, it will become the min.
	template<typename T>
	T Wrap(T val, T minVal, T maxVal)
	{
		if (val < minVal)
			return maxVal;
		
		else if (val > maxVal)
			return minVal;

		return val;
	}

	//Keeps a value between a min and max point. If it goes to low, it will 
	//become the min. If the value gets too high, it will become the max.
	template<typename T>
	T Clamp(T val, T minVal, T maxVal)
	{
		if (val < minVal)
			return minVal;
		
		else if (val > maxVal)
			return maxVal;

		return val;
	}

	//Returns the smaller of the two values
	template<typename T>
	T Min(T x, T y)
	{
		return (x < y) ? x : y;
	}

	//Returns the larger of the two values
	template<typename T>
	T Max(T x, T y)
	{
		return (x > y) ? x : y;
	}

	//Initialize Random Number Generator
	inline void InitRNG()
	{
		srand (static_cast<unsigned> (time(0)));
	}
	
	//Return a random integer
	inline unsigned RandInt()
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
	inline float RandFloat ()
	{
		return rand() / static_cast <float> (RAND_MAX);
	}

	//Return a random float between min and max
	inline float RandFloatMinMax (float min, float max)
	{
		float num = (max - min) * RandFloat ();
		return (num + min);
	}
}

//Class DivideByZero:
//Exception for divide by zero
class DivideByZero : public std::exception
{
public:
	const char* what() {return "Divide By Zero";}
};

inline void printw (float x, float y, float z, char* format, ...)
{
	va_list args;	//  Variable argument list
	int len;		//	String length
	int i;			//  Iterator
	char * text;	//	Text
	void *font_style = GLUT_BITMAP_TIMES_ROMAN_24;

	//  Initialize a variable argument list
	va_start(args, format);

	//  Return the number of characters in the string referenced the list of arguments.
	//  _vscprintf doesn't count terminating '\0' (that's why +1)
	len = _vscprintf(format, args) + 1; 

	//  Allocate memory for a string of the specified size
	text = (char *)malloc(len * sizeof(char));

	//  Write formatted output using a pointer to the list of arguments
	vsprintf_s(text, len, format, args);

	//  End using variable argument list 
	va_end(args);

	//  Specify the raster position for pixel operations.
	glRasterPos3f (x, y, z);


	//  Draw the characters one by one
	for (i = 0; text[i] != '\0'; i++)
		glutBitmapCharacter(font_style, text[i]);

	//  Free the allocated memory for the string
	free(text);
}



#endif