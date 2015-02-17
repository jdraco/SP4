#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <math.h>
#include "SceneGraph\Matrix4x4.h"

class Vector3D
{
public:
	float x, y, z;

	//default constructor
	Vector3D(float X = 0, float Y = 0, float Z = 0)
	{
		x = X;
		y = Y;
		z = Z;
	}

	~Vector3D(){};

	void Set(float X = 0.0, float Y = 0.0, float Z = 0.0)
	{
		x = X;
		y = Y;
		z = Z;
	}

	void Set(Vector3D temp)
	{
		x = temp.x;
		y = temp.y;
		z = temp.z;
	}


	//calculate and return the magnitude of this vector
	float GetMagnitude()
	{
		return sqrtf(x * x + y * y + z * z);
	}

	float GetMagnitudeSquare()
	{
		return x * x + y * y + z * z;
	}


	float GetMagnitude2D()
	{
		return sqrtf(x * x + y * y);
	}
		
	//Multiply 2 vector
	Vector3D operator*(const Vector3D &vec) const
	{
		return Vector3D(x * vec.x , y * vec.y , z * vec.z);
	}

	//multiply this vector by a scalar
	Vector3D operator*(float num) const
	{
		return Vector3D(x * num, y * num, z * num);
	}

	//pass in a vector, pass in a scalar, return the product
	friend Vector3D operator*(float num, Vector3D const &vec)
	{
		return Vector3D(vec.x * num, vec.y * num, vec.z * num);
	}

	//multiply this vector by a scalar
	Vector3D operator*(const Matrix4x4 &m) const
	{
		return Vector3D( x*m.matrix[0] + y*m.matrix[4] + z*m.matrix[8] + 1*m.matrix[12],
						 x*m.matrix[1] + y*m.matrix[5] + z*m.matrix[9] + 1*m.matrix[13],
						 x*m.matrix[2] + y*m.matrix[6] + z*m.matrix[10] + 1*m.matrix[14] );
	}


	//add two vectors
	Vector3D operator+(const Vector3D &vec) const
	{
		return Vector3D(x + vec.x, y + vec.y, z + vec.z);
	}

	//subtract two vectors
	Vector3D operator-(const Vector3D &vec) const
	{
		return Vector3D(x - vec.x, y - vec.y, z - vec.z);
	}

	bool operator==(const Vector3D &vec) const
	{
		if(x==vec.x&&y==vec.y&&z==vec.z)
			return true;
		else
			return false;
		return false;
	}


	//normalize this vector
	void normalizeVector3D()
	{
		float magnitude = sqrtf(x * x + y * y + z * z);
		x /= magnitude;
		y /= magnitude;
		z /= magnitude;
	}
	
	//calculate and return dot product
	float dotVector3D(const Vector3D &vec) const
	{
		return x * vec.x + y * vec.y + z * vec.z;
	}

	//calculate and return cross product
	Vector3D crossVector3D(const Vector3D &vec) const
	{
		return Vector3D(y * vec.z - z * vec.y,
				z * vec.x - x * vec.z,
				x * vec.y - y * vec.x);
	}

	Vector3D normalized()
	{   
		return  Vector3D(x/GetMagnitude(), y/GetMagnitude(), z/GetMagnitude());
	}

			void setX(float value)
		{
			x = value;
		}



	void setY(float value)
		{
			y = value;
		}

	void setZ(float value)
		{
			z = value;
		}


	float getX(void)
		{
			return x;
		}

	float getY(void)
		{
			return y;
		}

	float getZ(void)
		{
			return z;
		}
};

#endif
