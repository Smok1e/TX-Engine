#pragma once

void DrawCylinder (double delta = 64, double r = 50)

{

	double z_center = 1;
	double x_center = 0;

	double y1 = -100;
	double y2 =  100;

	double rx = r;
	double rz = rx / 500;

	for (double A = 0; A < M_PI * 2; A += M_PI / delta)

	{
	
		double x = x_center + sin (A) * rx;
		double z = z_center + cos (A) * rz;

		Engine.drawLine3D (x, y1, z, x, y2, z);

	}

}