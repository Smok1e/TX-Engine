#pragma once

void DrawCube ()

{

	double z1 = 1;
	double z2 = z1 + 0.12;

	                  //x1   y1  z1   x2   y2  z2
	Engine.drawLine3D (-50,  50, z1,  50,  50, z1);
	Engine.drawLine3D (-50, -50, z1,  50, -50, z1);
	Engine.drawLine3D (-50,  50, z1, -50, -50, z1);
	Engine.drawLine3D ( 50,  50, z1,  50, -50, z1);

	Engine.drawLine3D (-50,  50, z2,  50,  50, z2);
	Engine.drawLine3D (-50, -50, z2,  50, -50, z2);
	Engine.drawLine3D (-50,  50, z2, -50, -50, z2);
	Engine.drawLine3D ( 50,  50, z2,  50, -50, z2);

	Engine.drawLine3D ( 50,  50, z1,  50,  50, z2);
	Engine.drawLine3D ( 50, -50, z1,  50, -50, z2);

	Engine.drawLine3D (-50,  50, z1, -50,  50, z2);
	Engine.drawLine3D (-50, -50, z1, -50, -50, z2);

}