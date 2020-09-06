#pragma once

//-------------------------------------------

typedef RGBQUAD * PixelMap;

//-------------------------------------------

class Context

{

public :

	Context (size_t width, size_t height);

	Context (HDC & dc);

	~Context ();

	bool setPixel (int x, int y, Color color);

	Color getPixel (int x, int y);

	size_t getSizeX ();

	size_t getSizeY ();

	operator HDC & ();

private :

	PixelMap buffer_;

	HDC dc_;

	size_t width_;
	size_t height_;

};

//-------------------------------------------

Context::Context (size_t width, size_t height) :

	buffer_ (nullptr),

	width_  (width),
	height_ (height)

{

	dc_ = txCreateDIBSection (width_, height_, &buffer_);

}

//-------------------------------------------

Context::Context (HDC & dc) :

	Context (txGetExtentX (dc), txGetExtentY (dc))

{

	txBitBlt (dc_, 0, 0, 0, 0, dc);

}

//-------------------------------------------

Context::~Context ()

{

	txDeleteDC (dc_);

}

//-------------------------------------------

bool Context::setPixel (int x, int y, Color color)

{

	if (x < 0 || x >= width_ || y < 0 || y >= height_) return false;

	y = height_ - y;

	size_t index = x + y * width_;

	if (index >= width_ * height_ || index < 0) return false;

	//printf ("x: %zu, y: %zu, index: %zu\n", x, y, index);

	RGBQUAD * pixel = &buffer_[index];

	pixel -> rgbRed   = color.r;
	pixel -> rgbGreen = color.g;
	pixel -> rgbBlue  = color.b;

	return true;

}

//-------------------------------------------

Color Context::getPixel (int x, int y)

{

	if (x < 0 || x >= width_ || y < 0 || y >= height_) return Color (0, 0, 0);

	y = height_ - y;

	size_t index = x + y * width_;

	if (index >= width_ * height_ || index < 0) return Color (0, 0, 0);

	RGBQUAD * pixel = &buffer_[index];

	return Color (pixel -> rgbRed, pixel -> rgbGreen, pixel -> rgbBlue);

}

//-------------------------------------------

size_t Context::getSizeX ()

{

	return width_;

}

//-------------------------------------------

size_t Context::getSizeY ()

{

	return height_;

}

//-------------------------------------------

Context::operator HDC & ()

{

	return dc_;

}