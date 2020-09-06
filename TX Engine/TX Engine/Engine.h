#pragma once

#ifdef _ALLOW_TRACE

	#define TRACE(format__, ...) { printf ("[TRACE] in function '%s' [at line %d]: ", __FUNCSIG__, __LINE__);  \
								   printf (format__, __VA_ARGS__);                                             \
								   printf ("\n"); }

#else

	#define TRACE(format__, ...) ;

#endif

//-------------------------------------------------

class Engine

{

public :

	Engine ();

	~Engine ();

	void setColor (Color color)

	{
	
		color_ = color;

	}

	void setLineThikness (double thikness)

	{
	
		lineThickness_ = lineThickness_;

	}

	void setForwardCutoff (double cutoff)

	{
	
		forwardCutoff_ = cutoff;

	}

	void setTransform (Matrix <4> & transform)

	{
	
		transform_ = transform;

	}

	void reset ();

	void transform (Matrix <4> & transformation);

	void translate (double dx, double dy, double dz);
	void scale     (double sx, double sy, double sz);
	
	void translateCamera (double dx, double dy, double dz);

	void rotateX (double angle);
	void rotateY (double angle);
	void rotateZ (double angle);

	void control ();

	void apply (Vector4d * vector, Matrix <4> * matrix = nullptr);

	void drawLine3D (Vector4d coord1, Vector4d coord2, Color color);

	void drawLine3D (double x1, double y1, double z1, double x2, double y2, double z2)

	{
	
		drawLine3D (Vector4d (x1, y1, z1), Vector4d (x2, y2, z2), color_);

	}

	void drawLine3D (double x1, double y1, double z1, double x2, double y2, double z2, Color color)

	{
	
		drawLine3D (Vector4d (x1, y1, z1), Vector4d (x2, y2, z2), color);

	}

	void setContext (Context * context)

	{
	
		cont_ = context;

	}

	void drawPixel (Vector4d coord, Color color);

	void drawTransform ()

	{
	
		DrawMatrix (transform_, & (HDC&) *cont_, Background, TX_WHITE, wWidth / 2 - (30 * 5 * 4) / 2, wHeight - 30 * 4);

	}

private :

	Matrix <4> transform_;

	Matrix <4> camera_;

	Color color_;

	Context * cont_;

	double controlVelocity_;

	double lineThickness_; 

	double forwardCutoff_;

	double lineDelta_;

	double lightlevel_;

	void onMoveX (int velocity);
	void onMoveY (int velocity);
	void onMoveZ (int velocity);

	void onScaleX (double velocity);
	void onScaleY (double velocity);
	void onScaleZ (double velocity);

	void onRotateX (int velocity);
	void onRotateY (int velocity);
	void onRotateZ (int velocity);

};

//-------------------------------------------------

Engine::Engine () :

	transform_ (Matrix <4>::Unity ()),
	camera_    (Matrix <4>::Unity ()),

	color_ (TX_WHITE),

	cont_ (nullptr),

	controlVelocity_ (1),

	lineThickness_ (1),

	forwardCutoff_ (0),
	
	lineDelta_ (0.1),

	lightlevel_ (5)

{

	TRACE ("Engine created");

}

//-------------------------------------------------

Engine::~Engine ()

{

	TRACE ("Engine dectructed");

}

//-------------------------------------------------

void Engine::reset ()

{

	TRACE ("Engine reset");

	controlVelocity_ = 1;

	transform_ = Matrix <4>::Unity ();
	camera_    = Matrix <4>::Unity ();

	lineDelta_ = 0.01;

	lineThickness_ = 1;

}

//-------------------------------------------------

void Engine::transform (Matrix <4> & transformation)

{

	transform_ *= transformation;

}

//-------------------------------------------------

void Engine::translate (double dx, double dy, double dz)

{

	TRACE ("Translating Engine to [dx: %.3lf, dy: %.3lf, dz: %.3lf]", dx, dy, dz);

	Matrix <4> translate = {{
	
		{1, 0, 0, dx},
		{0, 1, 0, dy},
		{0, 0, 1, dz},
		{0, 0, 0,  1},

	}};

	transform_ *= translate;

}

//-------------------------------------------------

void Engine::translateCamera (double dx, double dy, double dz)

{

	TRACE ("Translating camera to [dx: %.3lf, dy: %.3lf, dz: %.3lf]", dx, dy, dz);

	Matrix <4> translate = {{
	
		{1, 0, 0, dx},
		{0, 1, 0, dy},
		{0, 0, 1, dz},
		{0, 0, 0,  1},

	}};

	camera_ *= translate;

}

//-------------------------------------------------

void Engine::scale (double sx, double sy, double sz)

{

	TRACE ("Scaling Engine to [sx: %.3lf, sy: %.3lf, sz: %.3lf]", sx, sy, sz);

	Matrix <4> scale = {{
	
		{sx, 0,  0,  0},
		{0,  sy, 0,  0},
		{0,  0,  sz, 0},
		{0,  0,  0,  1}

	}};

	transform_ *= scale;

}

//-------------------------------------------------

void Engine::rotateX (double A)

{

	TRACE ("Rotating by x to %.3lf", A);

	translate (1.12, 0, 0);

	Matrix <4> rotation = {{
	
		{1,       0,        0, 0},
		{0, cos (A), -sin (A), 0},
		{0, sin (A),  cos (A), 0},
		{0,       0,        0, 1}

	}};

	transform_ *= rotation;

	translate (-1.12, 0, 0);

}

//-------------------------------------------------

void Engine::rotateY (double A)

{

	TRACE ("Rotating by y to %.3lf", A);

	Matrix <4> rotation = {{
	
		{ cos (A), 0, sin (A), 0},
		{ 0,       1,       0, 0},
		{-sin (A), 0, cos (A), 0},
		{ 0,       0,       0, 1}

	}};

	transform_ *= rotation;

}

//-------------------------------------------------

void Engine::rotateZ (double A)

{

	TRACE ("Rotating by z to %.3lf", A);

	Matrix <4> rotation = {{
	
		{cos (A), -sin (A), 0, 0},
		{sin (A),  cos (A), 0, 0},
		{0,        0,       1, 0},
		{0,        0,       0, 1}

	}};

	transform_ *= rotation;

}

//-------------------------------------------------

void Engine::control ()

{

	#define ifpressed(key__) if (GetAsyncKeyState (key__))

	//Moving

	ifpressed (VK_RIGHT) onMoveX ( 1);
	ifpressed (VK_LEFT)  onMoveX (-1);

	ifpressed (VK_UP)    onMoveY ( 1);
	ifpressed (VK_DOWN)  onMoveY (-1);

	ifpressed (VK_PRIOR) onMoveZ ( 1);
	ifpressed (VK_NEXT)  onMoveZ (-1);

	//Scaling 
	
	ifpressed ('L') onScaleX ( 1);
	ifpressed ('J') onScaleX (-1);

	ifpressed ('I') onScaleY ( 1);
	ifpressed ('K') onScaleY (-1);

	ifpressed ('O') onScaleZ ( 1);
	ifpressed ('U') onScaleZ (-1);

	//Rotating

	ifpressed ('D') onRotateX ( 1);
	ifpressed ('A') onRotateX (-1);

	ifpressed ('W') onRotateY ( 1);
	ifpressed ('S') onRotateY (-1);

	ifpressed ('E') onRotateZ ( 1);
	ifpressed ('Q') onRotateZ (-1);

	//Thikness

	ifpressed ('1') lineThickness_ += 0.1;
	ifpressed ('2') lineThickness_ -= 0.1;

	//Reset

	ifpressed ('R') reset ();

	//Camera

	ifpressed ('M') translateCamera (0, 0,  controlVelocity_ / 100);
	ifpressed ('N') translateCamera (0, 0, -controlVelocity_ / 100);

	//Line delta

	ifpressed ('Z') if (lineDelta_ - 0.001 > 0) lineDelta_ -= 0.001;
	ifpressed ('X')                             lineDelta_ += 0.001;

	//Light

	ifpressed ('9') lightlevel_ -= 0.1;
	ifpressed ('0') lightlevel_ += 0.1;

	//Velocity

	ifpressed (VK_OEM_PLUS)  { controlVelocity_ += 1; printf ("Control velocity: %.3lf\n", controlVelocity_);}
	ifpressed (VK_OEM_MINUS) { controlVelocity_ -= 1; printf ("Control velocity: %.3lf\n", controlVelocity_);}

}

//-------------------------------------------------

void Engine::apply (Vector4d * vector, Matrix <4> * matrix)

{

	if (!matrix) matrix = &transform_;

	Matrix <4> & transform = *matrix;

	Vector4d v = *vector;

	vector -> x = v.x * transform.data[0][0] +
		          v.y * transform.data[0][1] +
		          v.z * transform.data[0][2] +
				  v.w * transform.data[0][3];

	vector -> y = v.x * transform.data[1][0] +
		          v.y * transform.data[1][1] +
		          v.z * transform.data[1][2] +
				  v.w * transform.data[1][3];

	vector -> z = v.x * transform.data[2][0] +
		          v.y * transform.data[2][1] +
		          v.z * transform.data[2][2] +
				  v.w * transform.data[2][3];

	vector -> w = v.x * transform.data[3][0] +
		          v.y * transform.data[3][1] +
		          v.z * transform.data[3][2] +
				  v.w * transform.data[3][3];

	vector -> x /= vector -> w;
	vector -> y /= vector -> w;
	vector -> z /= vector -> w;

}

//-------------------------------------------------

void Engine::drawLine3D (Vector4d coord1, Vector4d coord2, Color color)

{

	apply (&coord1);
	apply (&coord2);

	apply (&coord1, &camera_);
	apply (&coord2, &camera_);

	if (GetKeyState (VK_SCROLL))
		
	{

		txSetColor     (color, lineThickness_, *cont_);
		txSetFillColor (color,                 *cont_);

		if (fabs (coord1.z) < EPSILON || coord1.z < forwardCutoff_) return;
		if (fabs (coord2.z) < EPSILON || coord2.z < forwardCutoff_) return;

		double x1 = coord1.x / coord1.z;
		double y1 = coord1.y / coord1.z;

		double x2 = coord2.x / coord2.z;
		double y2 = coord2.y / coord2.z;

		txLine (wWidth / 2 + x1, wHeight / 2 - y1, wWidth / 2 + x2, wHeight / 2 - y2, *cont_);

	}

	else

	{

		double maxcolorz = lightlevel_;
	
		for (double t = 0; t <= 1; t += lineDelta_)

		{

			double x = coord1.x + t * (coord2.x - coord1.x);
			double y = coord1.y + t * (coord2.y - coord1.y);
			double z = coord1.z + t * (coord2.z - coord1.z);

			if (fabs (z) < EPSILON) continue;
			if (z < forwardCutoff_) continue;

			//double c = maxcolorz - z;

			//if (c < 0) c = 0;

			//Color color ((double) color_.r / maxcolorz * c, 
			//	         (double) color_.g / maxcolorz * c, 
			//	         (double) color_.b / maxcolorz * c);
			
			x = (wWidth  / 2) + x / z;
			y = (wHeight / 2) - y / z;

			cont_ -> setPixel (x, y, color);

		}

	}

}

//-------------------------------------------------

void Engine::drawPixel (Vector4d coord, Color color)

{

	apply (&coord);
	apply (&coord, &camera_);

	if (fabs (coord.z) < EPSILON) return;
	if (coord.z < forwardCutoff_) return;

	double x = (wWidth  / 2) + coord.x / coord.z;
	double y = (wHeight / 2) - coord.y / coord.z;

	cont_ -> setPixel (x, y, color);

}

//-------------------------------------------------

void Engine::onMoveX (int velocity)

{

	translate (velocity * controlVelocity_, 0, 0);

}

//-------------------------------------------------

void Engine::onMoveY (int velocity)

{

	translate (0, velocity * controlVelocity_, 0);

}

//-------------------------------------------------

void Engine::onMoveZ (int velocity)

{

	translate (0, 0, velocity * controlVelocity_ / 10);

}

//-------------------------------------------------

void Engine::onScaleX (double velocity)

{

	scale (1 + velocity / 100, 1, 1);

}

//-------------------------------------------------

void Engine::onScaleY (double velocity)

{

	scale (1, 1 + velocity / 100, 1);

}

//-------------------------------------------------

void Engine::onScaleZ (double velocity)

{

	scale (1, 1, 1 + velocity / 100);

}

//-------------------------------------------------

void Engine::onRotateX (int velocity)

{

	rotateX (-velocity * controlVelocity_ / 1000);

}

//-------------------------------------------------

void Engine::onRotateY (int velocity)

{

	rotateY (-velocity * controlVelocity_ / 1000);

}

//-------------------------------------------------

void Engine::onRotateZ (int velocity)

{

	rotateZ (-velocity * controlVelocity_ / 100);

}