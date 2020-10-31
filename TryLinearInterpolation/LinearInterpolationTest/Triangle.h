#pragma once

//-------------------------------------------

struct Point

{

	float x;
	float y;

	Color color;

	Point () :

		x (0),
		y (0),

		color (TX_WHITE)

	{}

	Point (float x_, float y_) :

		x (x_),
		y (y_),

		color (TX_WHITE)

	{}

	Point (float x_, float y_, Color color_) :

		x (x_),
		y (y_),

		color (color_)

	{}

	Point (POINT point) :

		Point (point.x, point.y)

	{}

	static Point Random ()

	{
	
		return Point (RANDOMCOORD, Color::Rand ());

	}

	Point & operator= (const Point & that)

	{
	
		if (&that == this) return *this;

		x = that.x;
		y = that.y;

		color = that.color;

		return *this;

	}

	operator POINT ()

	{
	
		return {(LONG) x, (LONG) y};

	}

};

//-------------------------------------------

Point Interpolate (const Point & a, const Point & b, float t);

//-------------------------------------------

Point Interpolate (const Point & a, const Point & b, float t)

{

	float x =    a.x       + t * (b.x       - a.x);
	float y =    a.y       + t * (b.y       - a.y);

	Color color (a.color.r + t * (b.color.r - a.color.r), 
			     a.color.g + t * (b.color.g - a.color.g), 
				 a.color.b + t * (b.color.b - a.color.b),
			     a.color.a + t * (b.color.a - a.color.a));

	return Point (x, y, color);

}

//-------------------------------------------

#define SORT_Y(a, b, c) { if (c.y < a.y) std::swap (a, c);   \
						  if (c.y < b.y) std::swap (b, c);   \
						  if (b.y < a.y) std::swap (a, b); }

//-------------------------------------------

void DrawTriangle (Context * context, Point a, Point b, Point c)

{ 																	   
																			  
	SORT_Y (a, b, c);														  
																			  
	     if (a.y == c.y)															  
																			  
	{																		  
																			  
		if (a.x == c.x) 													//  
																			// A*********B*********C 
		{																	//  
																			  
				context -> setPixel (a.x, a.y, a.color);					  
																			  
			return;															  

		}

		if (a.x > c.x) std::swap (a.x, c.x);

			float dt = 1 / (c.x - a.x);
			float t = dt;

		for (int x = a.x; x < c.x; x ++, t += dt)

		{
	
				Point d = Interpolate (a, c, t);

				context -> setPixel (d.x, d.y, d.color);

		}

		return;

	}

	else if (a.y == b.y)

	{

		if (a.y > c.y) std::swap (a, c);										//
																				//
		float dt0 = 1 / (c.y - a.y);											//		  A* * * * * * * * B
																				//		   *			  *
		for (float y = a.y, t0 = dt0; y < c.y; y++, t0 += dt0)					//		    *		    *
																				//			 *		  *
		{																		//			  *	    *
																				//			   *  *
			Point e = Interpolate (c, a, t0);									//				C
			Point f = Interpolate (c, b, t0);									//
																				//
			if (e.x == f.x)														//
																				//
			{																	//
		
				context -> setPixel (e.x, e.y, e.color);

				continue;

			}

			if (f.x > e.x) std::swap (f, e);

			float dt1 = 1 / (e.x - f.x);

			for (float x = f.x, t1 = dt1; x < e.x; x ++, t1 += dt1)

			{

				Point g = Interpolate (f, e, t1);

				g.x = x;

				context -> setPixel (g.x, g.y, g.color);

			}

		}

		return;

	}

	else if (c.y == b.y)

	{
	
		float dt0 = 1 / (c.y - a.y);
																	//
		for (float y = a.y, t0 = dt0; y < c.y; y ++, t0 += dt0)		//	 A	 
																	//	 *	*	 
		{															//	  *		*	
																	//	   *		*   
			Point e = Interpolate (a, c, t0);						//		*			 *
			Point f = Interpolate (a, b, t0);						//		 B*	* * * * * *C
																	//
			e.y = y;												
			f.y = y;												

			if (e.x == f.x)

			{
		
				context -> setPixel (e.x, e.y, e.color);

				continue;

			}

			if (f.x > e.x) std::swap (f, e);

			float dt1 = 1 / (e.x - f.x);

			for (float x = f.x, t1 = dt1; x < e.x; x ++, t1 += dt1)

			{

				Point g = Interpolate (f, e, t1);

				g.x = x;

				context -> setPixel (g.x, g.y, g.color);

			}

		}

		return;

	}

	else

	{
																				 //
		Point d = Interpolate (a, c, (b.y - a.y) / (c.y - a.y));				 //	           A
																				 //			*   *
		float dt0 = 1 / (d.y - a.y);											 //		 *   	 *
																				 //	  B	  		  *
		for (float y = a.y, t0 = dt0; y < d.y; y ++, t0 += dt0)					 //		 *		   *
																				 //			  *		*
		{																		 //				   * C
																				 //
			Point e = Interpolate (a, d, t0);									 
			Point f = Interpolate (a, b, t0);									 

			e.y = y;
			f.y = y;

			if (e.x == f.x)

			{
		
				context -> setPixel (e.x, e.y, e.color);

				continue;

			}

			if (f.x > e.x) std::swap (f, e);

			float dt1 = 1 / (e.x - f.x);

			for (float x = f.x, t1 = dt1; x < e.x; x ++, t1 += dt1)

			{

				Point g = Interpolate (f, e, t1);

				context -> setPixel (x, g.y, g.color);

			}

		}

		dt0 = 1 / (c.y - d.y);

		for (float y = d.y, t0 = dt0; y < c.y; y ++, t0 += dt0)

		{

			Point e = Interpolate (d, c, t0);
			Point f = Interpolate (b, c, t0);

			e.y = y;
			f.y = y;

			if (e.x == f.x)

			{
		
				context -> setPixel (e.x, e.y, e.color);

				continue;

			}

			if (f.x > e.x) std::swap (f, e);

			float dt1 = 1 / (e.x - f.x);

			for (float x = f.x, t1 = dt1; x < e.x; x ++, t1 += dt1)

			{

				Point g = Interpolate (f, e, t1);

				context -> setPixel (x, g.y, g.color);

			}

		}
	
	}

}

//-------------------------------------------

void DrawQuadangle (Context * context, Point a, Point b, Point c, Point d)

{

	DrawTriangle (context, a, b, c);
	DrawTriangle (context, b, c, d);

}