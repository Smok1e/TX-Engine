#pragma once

#pragma pack (push, 1)

template <typename Type>
union Vector4

{

	struct { Type x, y, z, w; };

	Type data[4];

	Vector4 (Type x_, Type y_, Type z_, Type w_) :

		x (x_),
		y (y_),
		z (z_),
		w (w_)

	{}

	Vector4 (Type x_, Type y_, Type z_) :

		Vector4 (x_, y_, z_, 1)

	{}

	Vector4 & operator += (const Vector4 & that)

	{
	
		x += that.x;
		y += that.y;
		z += that.z;
		w += that.w;

		return *this;

	}

	Vector4 & operator -= (const Vector4 & that)

	{
	
		x -= that.x;
		y -= that.y;
		z -= that.z;
		w -= that.w;

		return *this;

	}

	Vector4 & operator *= (const Vector4 & that)

	{
	
		x *= that.x;
		y *= that.y;
		z *= that.z;
		w *= that.w;

		return *this;

	}

	Vector4 & operator /= (const Vector4 & that)

	{
	
		x /= that.x;
		y /= that.y;
		z /= that.z;
		w /= that.w;

		return *this;

	}

};

typedef Vector4 <int>    Vector4i;
typedef Vector4 <double> Vector4d;

#pragma pack (pop)