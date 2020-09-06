#pragma once

#pragma pack (push, 1)

struct Color 

{

	int r, g, b;

	Color (int r_, int g_, int b_) :

		r (r_),
		g (g_),
		b (b_)

	{}

	Color (Color & that)

	{
	
		r = that.r;
		g = that.g;
		b = that.b;

	}

	Color (COLORREF color)

	{

		r = GetRValue (color);
		g = GetGValue (color);
		b = GetBValue (color);
	
	}

	Color (int c) :

		Color (c, c, c)

	{}

	Color () :

		Color (0, 0, 0)

	{}

	Color & operator += (const Color & that)

	{
	
		r += that.r;
		g += that.g;
		b += that.b;

		return *this;

	}

	Color & operator -= (const Color & that)

	{
	
		r -= that.r;
		g -= that.g;
		b -= that.b;

		return *this;

	}

	Color & operator /= (const Color & that)

	{
	
		r /= that.r;
		r /= that.g;
		r /= that.b;

		return *this;

	}

	Color & operator *= (const Color & that)

	{
	
		r *= that.r;
		r *= that.g;
		r *= that.b;

		return *this;

	}

	operator COLORREF ()

	{
	
		return RGB (r, g, b);

	}

};
#pragma pack (pop)