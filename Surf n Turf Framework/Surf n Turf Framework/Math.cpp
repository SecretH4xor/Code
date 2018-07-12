#include	"Main.h"

Vector::Vector ()
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
}

Vector::Vector ( float _X, float _Y, float _Z )
{
	this->x = _X;
	this->y= _Y;
	this->z = _Z;
}

Vector Vector::operator+ ( const Vector &A )
{
	return Vector( this->x + A.x, this->y + A.y, this->z + A.z );
}

Vector Vector::operator+ ( const float A )
{
	return Vector( this->x + A, this->y + A, this->z + A );
}

Vector Vector::operator+= ( const Vector &A )
{
	this->x += A.x;
	this->y += A.y;
	this->z += A.z;
	return *this;
}

Vector Vector::operator+= ( const float A )
{
	this->x += A;
	this->y += A;
	this->z += A;
	return *this;
}

Vector Vector::operator- ( const Vector &A )
{
	return Vector( this->x - A.x, this->y - A.y, this->z - A.z );
}

Vector Vector::operator- ( const float A )
{
	return Vector( this->x - A, this->y - A, this->z - A );
}

Vector Vector::operator-= ( const Vector &A )
{
	this->x -= A.x;
	this->y -= A.y;
	this->z -= A.z;
	return *this;
}

Vector Vector::operator-= ( const float A )
{
	this->x -= A;
	this->y -= A;
	this->z -= A;
	return *this;
}

Vector Vector::operator* ( const Vector &A )
{
	return Vector( this->x * A.x, this->y * A.y, this->z * A.z );
}

Vector Vector::operator* ( const float A )
{
	return Vector( this->x * A, this->y * A, this->z * A );
}

Vector Vector::operator*= ( const Vector &A )
{
	this->x *= A.x;
	this->y *= A.y;
	this->z *= A.z;
	return *this;
}

Vector Vector::operator*= ( const float A )
{
	this->x *= A;
	this->y *= A;
	this->z *= A;
	return *this;
}

Vector Vector::operator/ ( const Vector &A )
{
	return Vector( this->x / A.x, this->y / A.y, this->z / A.z );
}

Vector Vector::operator/ ( const float A )
{
	return Vector( this->x / A, this->y / A, this->z / A );
}

Vector Vector::operator/= ( const Vector &A )
{
	this->x /= A.x;
	this->y /= A.y;
	this->z /= A.z;
	return *this;
}

Vector Vector::operator/= ( const float A )
{
	this->x /= A;
	this->y /= A;
	this->z /= A;
	return *this;
}

bool Vector::operator== ( const Vector &A )
{
	if ( this->x == A.x 
		&& this->y == A.y
		&& this->z == A.z )
		return true;

	return false;
}

bool Vector::operator!= ( const Vector &A )
{
	if ( this->x != A.x 
		|| this->y != A.y
		|| this->z != A.z )
		return true;

	return false;
}

bool Vector::IsValid ()
{
	return *this != Vector( 0, 0, 0 );
}