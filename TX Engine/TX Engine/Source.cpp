#define _CRT_SECURE_NO_WARNINGS
//#define _ALLOW_TRACE
#define _TX_MY_CAT_DOES_NOT_LIKE_CONSOLE_TEXT

#include "C:\Users\Fedor\Downloads\TX\TXLib.h"
#include "Color.h"
#include "Matrix.h"
#include "Vector4.h"
#include "Context.h"
#include "Config.h"
#include "Engine.h"

class Engine Engine = {};

#include "Cube.h"
#include "Cylinder.h"
#include "Image.h"

//-------------------------------------------------

#define RANDOMCOLOR Color (rand () % 255, rand () % 255, rand () % 255)

//-------------------------------------------------

int main ()

{

	_txConsoleMode = SW_SHOW;

	txCreateWindow (wWidth, wHeight);
	txDisableAutoPause ();

	SetWindowText (txWindow (), "TX Engine");

	Context context (wWidth, wHeight);

	Engine.setContext (&context);
	Engine.setColor (Foreground);

	HDC image        = txLoadImage ("C:\\Users\\Fedor\\Desktop\\3D Engine\\image.bmp");
	HDC transparency = txLoadImage ("C:\\Users\\Fedor\\Desktop\\3D Engine\\transparency.bmp");

	Matrix <4> transform = {{
		
		{1,      0,     0, 0},
		{0,  0.770, -0.001, 0},
		{0,  0.002,  1.729, 0},
		{0,      0,     0, 1}

	}};

	//Engine.transform (transform);

	txBegin ();

	while (!GetAsyncKeyState (VK_ESCAPE))

	{

		//Engine.rotateZ (0.01);

		txSetFillColor (Background, context);
		txClear (context);

		TransparentImage (image, transparency);

		if (GetKeyState (VK_NUMLOCK)) Engine.drawTransform ();

		if (GetAsyncKeyState (VK_CONTROL))

		{

			if (GetAsyncKeyState ('S')) txSaveImage ("Preview.bmp"), printf ("Image saved as 'Preview.bmp'\n");

			Sleep (50);

		}
		
		else Engine.control ();

		txBitBlt (txDC (), 0, 0, 0, 0, context);

		txSleep (0);

	}

	txDeleteDC (image);
	txDeleteDC (transparency);

	return 0;

}