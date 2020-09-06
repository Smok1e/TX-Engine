#pragma once

template <size_t Size = 4>
class Matrix

{

public :

	double data[Size][Size];

	void reset ()

	{
	
		for (size_t i = 0; i < Size; i++)

		{
		
			data [i][i] = 1;

		}

	}

	void print ()

	{
	
		for (size_t x = 0; x < Size; x++)

		{

			for (size_t y = 0; y < Size; y++)

			{
			
				printf ("%3lf ", data[x][y]);

			}

			printf ("\n");

		}

	}

	friend Matrix <Size> operator+ (const Matrix <Size> & a, const Matrix <Size> & b)

	{
	
		Matrix <Size> result;

		for (size_t x = 0; x < Size; x++)

		{
		
			for (size_t y = 0; y < Size; y++)

			{

				result.data [x][y] = a.data[x][y] + b.data[x][y];

			}

		}

		return result;

	}

	friend Matrix <Size> operator- (const Matrix <Size> & a, const Matrix <Size> & b)

	{
	
		Matrix <Size> result;

		for (size_t x = 0; x < Size; x++)

		{
		
			for (size_t y = 0; y < Size; y++)

			{

				result.data [x][y] = a.data[x][y] - b.data[x][y];

			}

		}

		return result;

	}

	friend Matrix <Size> operator* (const Matrix <Size> & a, const Matrix <Size> & b)

	{
	
		Matrix result;

		for (size_t x = 0; x < Size; x++)

		{
		
			for (size_t y = 0; y < Size; y++)

			{
			
				double cell = 0;

				for (size_t i = 0; i < Size; i++)

				{
				
					cell += a.data[x][i] * b.data[i][y];

				}

				result.data[x][y] = cell;

			}

		}

		return result;

	}

	Matrix <Size> & operator+= (const Matrix <Size> & that)

	{
	
		*this = *this + that;

		return *this;

	}

	Matrix <Size> & operator-= (const Matrix <Size> & that)

	{
	
		*this = *this - that;

		return *this;

	}

	Matrix <Size> & operator*= (const Matrix <Size> & that)

	{
	
		*this = *this * that;

		return *this;

	}

	static Matrix <Size> Unity ()

	{
	
		Matrix <Size> matrix;

		for (size_t x = 0; x < Size; x++)

		{
		
			for (size_t y = 0; y < Size; y++)

			{
			
				matrix.data[x][y] = 0;

			}

		}

		for (size_t i = 0; i < Size; i++)

		{
		
			matrix.data[i][i] = 1;

		}

		return matrix;

	}

};

//-------------------------------------------------

template <size_t Size>
bool MatrixAddTest ()

{

	printf ("Matrix <%zu> adding test: ", Size);
    
	Matrix <Size> m1;
	Matrix <Size> m2;

	for (size_t x = 0, n = 0; x < Size; x++)

	{
	
		for (size_t y = 0; y < Size; y++)

		{
		
			m1.data[x][y] = n;

			n++;

		}

	}

	for (size_t x = 0, n = 10; x < Size; x++)

	{
	
		for (size_t y = 0; y < Size; y++)

		{
		
			m2.data[x][y] = n;

			n++;

		}

	}

	Matrix <Size> result = m1 + m2;

	double expected[Size][Size] = {};

	for (size_t x = 0; x < Size; x++)

	{
		
		for (size_t y = 0; y < 3; y++)

		{

			expected[x][y] = m1.data[x][y] + m2.data[x][y];

		}

	}

	for (size_t x = 0; x < Size; x++)

	{
	
		for (size_t y = 0; y < Size; y++)

		{
		
			if (result.data[x][y] != expected[x][y]) 

			{
			
				printf ("Failed: at [%zu][%zu] expected %lf, got %lf\n", x, y, expected[x][y], result.data[x][y]);

				return false;

			}

		}

	}

	printf ("Ok\n");

	return true;

}

//-------------------------------------------------

template <size_t Size>
bool MatrixSubstractTest ()

{

	printf ("Matrix <%zu> substracting test: ", Size);
    
	Matrix <Size> m1;
	Matrix <Size> m2;

	for (size_t x = 0, n = 0; x < Size; x++)

	{
	
		for (size_t y = 0; y < Size; y++)

		{
		
			m1.data[x][y] = n;

			n++;

		}

	}

	for (size_t x = 0, n = 10; x < Size; x++)

	{
	
		for (size_t y = 0; y < Size; y++)

		{
		
			m2.data[x][y] = n;

			n++;

		}

	}

	Matrix <Size> result = m1 - m2;

	double expected[Size][Size] = {};

	for (size_t x = 0; x < Size; x++)

	{
		
		for (size_t y = 0; y < 3; y++)

		{

			expected[x][y] = m1.data[x][y] - m2.data[x][y];

		}

	}

	for (size_t x = 0; x < Size; x++)

	{
	
		for (size_t y = 0; y < Size; y++)

		{
		
			if (result.data[x][y] != expected[x][y]) 

			{
			
				printf ("Failed: at [%zu][%zu] expected %lf, got %lf\n", x, y, expected[x][y], result.data[x][y]);

				return false;

			}

		}

	}

	printf ("Ok\n");

	return true;

}

//-------------------------------------------------

template <size_t Size>
bool MatrixMultiplyTest ()

{

	printf ("Matrix <%zu> multiplicating test: ", Size);
    
	Matrix <Size> m1;
	Matrix <Size> m2;

	for (size_t x = 0, n = 0; x < Size; x++)

	{
	
		for (size_t y = 0; y < Size; y++)

		{
		
			m1.data[x][y] = n;

			n++;

		}

	}

	for (size_t x = 0, n = 10; x < Size; x++)

	{
	
		for (size_t y = 0; y < Size; y++)

		{
		
			m2.data[x][y] = n;

			n++;

		}

	}

	Matrix <Size> result = m1 * m2;

	double expected[Size][Size] = {};

	for (size_t x = 0; x < Size; x++)

	{
		
		for (size_t y = 0; y < 3; y++)

		{
			
			double cell = 0;

			for (size_t i = 0; i < Size; i++)

			{
				
				cell += m1.data[x][i] * m2.data[i][y];

			}

			expected[x][y] = cell;

		}

	}

	for (size_t x = 0; x < Size; x++)

	{
	
		for (size_t y = 0; y < Size; y++)

		{
		
			if (result.data[x][y] != expected[x][y]) 

			{
			
				printf ("Failed: at [%zu][%zu] expected %lf, got %lf\n", x, y, expected[x][y], result.data[x][y]);

				return false;

			}

		}

	}

	printf ("Ok\n");

	return true;

}

//-------------------------------------------------

template <size_t Size>
void MatrixTest ()

{

	size_t result = 0;

	printf ("Matrix <%zu> unit test:\n", Size);

	result += MatrixAddTest       <Size> ();
	result += MatrixSubstractTest <Size> ();
	result += MatrixMultiplyTest  <Size> ();

	printf ("Done: %zu succeed, %zu failed.\n", result, 3 - result);

}

template <size_t Size>
void DrawMatrix (Matrix <Size> & matrix, HDC * dc, Color background, Color foreground, int x = 0, int y = 0)

{

	size_t charsize = 30;
	size_t max_digit_count = 5;

	const char * font = "Consolas";

	int rectx = x, 
		recty = y;

	int rectw = charsize * max_digit_count * Size,
	    recth = charsize * Size;

	txSetFillColor (background,    *dc);
	txSetColor     (background, 1, *dc);

	txRectangle (rectx, recty, rectx + rectw, recty + recth, *dc);

	txSetFillColor (foreground,    *dc);
	txSetColor     (foreground, 3, *dc);

	for (size_t i = 1; i < Size; i++)

	{

		int lx = x + max_digit_count * charsize * i;

		txLine (lx, y, lx, y + recth, *dc);

	}

	for (size_t i = 1; i < Size; i++)

	{

		int ly = y + charsize * i;

		txLine (x, ly, x + rectw, ly, *dc);

	}

	txSelectFont (font, charsize, charsize / 2.3, 1000, false, false, false, 0, *dc);

	for (size_t mx = 0; mx < Size; mx++)

	{
	
		for (size_t my = 0; my < Size; my++)

		{

			char str[32] = "";
			sprintf (str, "%.3lf", matrix.data[mx][my]);

			int textw = txGetTextExtentX (str, *dc);

			int tx = x + mx * charsize * max_digit_count + (charsize * max_digit_count / 2) - textw / 2;
			int ty = y + my * charsize;

			txTextOut (tx, ty, str, *dc);

		}

	}

}