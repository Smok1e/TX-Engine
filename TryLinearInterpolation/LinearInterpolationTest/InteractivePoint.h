#pragma once

//-------------------------------------------

class InteractivePoint : public AbstractWindow 
  
{

public :

	InteractivePoint (Point * point) :

		AbstractWindow (point -> x, point -> y, 0, 0, point -> color),

		followMouse_ (false),

		mouseHover_ (false),

		point_ (point),

		name_ (nullptr)

	{}

	InteractivePoint (Point * point, const char * name) :

		AbstractWindow (point -> x, point -> y, 0, 0, point -> color),

		followMouse_ (false),

		mouseHover_ (false),

		point_ (point),

		name_ (name)

	{}

	virtual void draw ();

	virtual bool onMouseTest (Mouse * mouse);

	virtual bool onMouseClick (Mouse * mouse);

	virtual bool onMouseRelease (Mouse * mouse);

	virtual void onTimeTick ();

	virtual void drawCoord ();

	const float r_ = 8;

	bool followMouse_;

	bool mouseHover_;

	Point * point_;

	const char * name_;

};

//-------------------------------------------

void InteractivePoint::draw ()

{

	txSetColor     (point_ -> color);
	txSetFillColor (point_ -> color);

	if (followMouse_ || mouseHover_)

		txSetColor (TX_WHITE, 1);

	txCircle (point_ -> x, point_ -> y, r_);
	
	if (name_)

	{

		txSetColor     (TX_WHITE);
		txSetFillColor (TX_WHITE);

		txSelectFont   ("Arial", 20);

		txTextOut (point_ -> x - r_ / 2, point_ -> y - r_ * 3, name_);

	}

}

//-------------------------------------------

bool InteractivePoint::onMouseTest (Mouse * mouse)

{

	POINT mPos = mouse -> getPos ();

	float a = point_ -> x - mPos.x;
	float b = point_ -> y - mPos.y;

	float c = sqrt (a * a + b * b);

	if (c <= r_)
	
	{

		mouseHover_ = true;

		return true;

	}

	mouseHover_ = false;

	return false;

}

//-------------------------------------------

bool InteractivePoint::onMouseClick (Mouse * mouse)

{

	followMouse_ = true;

	return true;

}

//-------------------------------------------

bool InteractivePoint::onMouseRelease (Mouse * mouse)

{

	followMouse_ = false;

	return true;

}

//-------------------------------------------

void InteractivePoint::onTimeTick ()

{

	if (followMouse_)

	{

		POINT mPos = manager_ -> mouse_.getPos ();

		POINT wSize = txGetExtent ();

		x_ = Clump <double> (mPos.x, 0, wSize.x);
		y_ = Clump <double> (mPos.y, 0, wSize.y);

		point_ -> x = x_;
		point_ -> y = y_;

	}

	if (!manager_ -> mouse_.getButtons () && followMouse_) followMouse_ = false;

	if (GetAsyncKeyState (VK_TAB) || followMouse_ || mouseHover_)

		drawCoord ();

}

//-------------------------------------------

void InteractivePoint::drawCoord ()

{

	txSelectFont ("Arial", r_ * 2);

	txSetFillColor (TX_WHITE);
	txSetColor     (TX_WHITE);

	char str [256] = "";

	sprintf_s (str, "{%.3f, %.3f}", point_ -> x, point_ -> y);

	float text_width = txGetTextExtentX (str);

	txTextOut (point_ -> x - text_width / 2, point_ -> y + r_ * 2, str);

}