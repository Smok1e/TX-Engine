#pragma once

void DrawImage (HDC & image, double z = 1)

{

	Context context (image);

	double width  = context.getSizeX ();
	double height = context.getSizeY ();

	double stroke = 0.1;

	for (size_t i = 1; i < width; i++)

	{
	
		for (size_t j = 1; j < height; j++)

		{

			Color color = context.getPixel (i, j);

			if (color == TX_BLACK) continue;

			double c = 255 - (color.r + color.g + color.b) / 3;

			double z0 = z + c / 1000;

			double x =          -width  / 2 + i;
			double y = height - (height / 2 + j);

			Engine.drawPixel (Vector4d (x, y, z), color);

		}

	}

}

//-------------------------------------------------

void TransparentImage (HDC & image, HDC & alpha, double z = 1)

{

	Context context      (image);
	Context transparency (alpha);

	double width  = context.getSizeX ();
	double height = context.getSizeY ();

	double stroke = 0.1;

	for (size_t i = 1; i < width; i++)

	{
	
		for (size_t j = 1; j < height; j++)

		{

			if (transparency.getPixel (i, j) != TX_WHITE) continue;

			Color color = context.getPixel (i, j);

			if (color == TX_BLACK) continue;

			double c = 255 - (color.r + color.g + color.b) / 3;

			double z0 = z + c / 1000;

			double x =          -width  / 2 + i;
			double y = height - (height / 2 + j);

			Engine.drawPixel (Vector4d (x, y, z), color);

		}

	}

}