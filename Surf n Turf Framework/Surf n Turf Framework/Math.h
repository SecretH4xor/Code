#include "Main.h"
#include <xtgmath.h>
#include <math.h>
#ifndef	Q_MATH_H
#define	Q_MATH_H

//Globals
#define M_PI 3.14159265358979323846f
#define CHECK_VALID( _v ) 0

//struct Color;
struct Vector;

double inline __declspec (naked) __fastcall SquareRoot(double n)
{
	_asm fld qword ptr[esp + 4]
		_asm fsqrt
	_asm ret 8
}

struct Vector
{
	float x;
	float y;
	float z;

	Vector ();
	Vector ( float _x, float _y, float _z );

	Vector operator+ ( const Vector &A );
	Vector operator+ ( const float A );
	Vector operator+= ( const Vector &A );
	Vector operator+= ( const float A );
	Vector operator- ( const Vector &A );
	Vector operator- ( const float A );
	Vector operator-= ( const Vector &A );
	Vector operator-= ( const float A );
	Vector operator* ( const Vector &A );
	Vector operator* ( const float A );
	Vector operator*= ( const Vector &A );
	Vector operator*= ( const float A );
	Vector operator/ ( const Vector &A );
	Vector operator/ ( const float A );
	Vector operator/= ( const Vector &A );
	Vector operator/= ( const float A );

	bool operator== ( const Vector &A );
	bool operator!= ( const Vector &A );

	float Size ();
	inline float Vector::Dot(const Vector& vOther) const
{
	const Vector& a = *this;

	return(a.x*vOther.x + a.y*vOther.y + a.z*vOther.z);
}

	bool IsValid ();

   inline float Vector::NormalizeInPlace()
   {
	   Vector& v = *this;

	   float iradius = 1.f / (this->Length() + 1.192092896e-07F); //FLT_EPSILON

	   v.x *= iradius;
	   v.y *= iradius;
	   v.z *= iradius;
	   return true;
   } 

	static void CrossProduct(const Vector &vector1, const Vector &vector2, Vector &cross)
	{
		cross.x = ((vector1.y * vector2.z) - (vector1.z * vector2.y));
		cross.y = ((vector1.z * vector2.x) - (vector1.x * vector2.z));
		cross.z = ((vector1.x * vector2.y) - (vector1.y * vector2.x));
	}

	static void NormalizeVector(Vector &vec)
	{
		float length = SquareRoot((float)(vec.x * vec.x) + (float)(vec.y * vec.y) + (float)(vec.z * vec.z));

		if (length != 0.f)
		{
			vec /= length;
		}
	}

	static void NormalizeAngles(Vector &angle)
	{
		for (int axis = 2; axis >= 0; --axis)
		{
			while (angle[axis] > 180.f)
			{
				angle[axis] -= 360.f;
			}

			while (angle[axis] < -180.f)
			{
				angle[axis] += 360.f;
			}
		}
	}
	static float flNormalizeVector(Vector &vec)
	{
		float length = SquareRoot((float)(vec.x * vec.x) + (float)(vec.y * vec.y) + (float)(vec.z * vec.z));

		if (length != 0.f)
		{
			vec /= length;
		}
	}

	float& operator[](int i)
	{
		return ((float*)this)[i];
	}

	float operator[](int i) const
	{
		return ((float*)this)[i];
	}


	inline float To3DSquareSpace()
	{
		return x*x + y*y + z*z;
	}

   void Init(float _x = 0, float _y = 0, float _z = 0)
	{
		this->x = _x;
		this->y = _y;
		this->z = _z;
	}


	void Set( float x = 0.0f, float y = 0.0f, float z = 0.0f )
	{
		x = x; y = y; z = z;
	}
  
   	float Length()
	{
		return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
	}

	float LengthSqr() const
	{
		return (this->x * this->x + this->y * this->y + this->z * this->z);
	}
	Vector Normalize()
	{
		if (this->x != this->x)
			this->x = 0;
		if (this->y != this->y)
			this->y = 0;
		if (this->z != this->z)
			this->z = 0;

		if (this->x > 89.f)
			this->x = 89.f;
		if (this->x < -89.f)
			this->x = -89.f;

		while (this->y > 180)
			this->y -= 360;
		while (this->y <= -180)
			this->y += 360;

		if (this->y > 180.f)
			this->y = 180.f;
		if (this->y < -180.f)
			this->y = -180.f;

		this->z = 0;

		return *this;
	}

	bool Iszero( float tolerance = 0.01f ) const
	{
		return ( x > -tolerance && x < tolerance &&
			y > -tolerance && y < tolerance &&
			z > -tolerance && z < tolerance );
	}
	inline void Vector::zero()
	{
		x = y = z = 0.0f;
	}

	static __forceinline float RadiansToDegrees(const float &radians)
	{
		return (float)(radians * (float)(180.f / M_PI));
	}
	
	static void VectorToAngles(const Vector &direction, Vector &angles)
	{
		// gimbal lock
		if ((direction.y == 0.f) && (direction.x == 0.f))
		{
			if (direction.z > 0.f)
			{
				angles.x = 270.f;
			}
			else
			{
				angles.x = 90.f;
			}

			angles.y = 0.f;
		}
		else
		{
			angles.x = RadiansToDegrees(atan2(-direction.z, SquareRoot((direction.x * direction.x) + (direction.y * direction.y))));

			angles.y = RadiansToDegrees(atan2(direction.y, direction.x));

			if (angles.y < 0.f)
			{
				angles.y += 360.f;
			}
		}

		angles.z = 0.f;


		angles.NormalizeAngles(angles);
	}

};

	inline void VectorSubtract(const Vector& a, const Vector& b, Vector& c)
	{
		CHECK_VALID(a);
		CHECK_VALID(b);
		c.x = a.x - b.x;
		c.y = a.y - b.y;
		c.z = a.z - b.z;
	}




class __declspec(align(16)) VectorAligned : public Vector
{
public:
    inline VectorAligned(void) {};
    inline VectorAligned(float x, float y, float z) 
    {
		Vector(x,y,z);
    }
public:
    explicit VectorAligned(const Vector &vOther) 
    {
        Vector(vOther.x, vOther.y, vOther.z);
    }
    
    VectorAligned& operator=(const Vector &vOther)    
    {
        Vector(vOther.x, vOther.y, vOther.z);
        return *this;
    }
    
    float w;
};
#endif