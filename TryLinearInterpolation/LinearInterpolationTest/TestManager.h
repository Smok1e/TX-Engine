#pragma once

//-------------------------------------------

enum TestManagerRunResult

{

	RunResultNone,
	RunResultOk,
	RunResultError

};

//-------------------------------------------

const char * strRunResult (TestManagerRunResult result);

//-------------------------------------------

struct TestManager

{

	WindowManager wManager_;

	Context context_;

	size_t wWidth_;
	size_t wHeight_;

	Color background_;

	const char * windowTitle_;

	Point a_;
	Point b_;
	Point c_;

	long lastDisplayTime_;

	TestManager (size_t wWidth, size_t wHeight, Color background, const char * name);

	TestManager (Color background, const char * name);

	~TestManager ();

	void _init ();

	TestManagerRunResult run ();

	void onTimeTick ();

	void drawDisplayTime ();

	void resetPoints ()

	{
	
		a_ = Point (100, 300, Color::Pink    );
		b_ = Point (200, 100, Color::Green   );
		c_ = Point (300, 300, Color::DarkCyan);

	}

};

//-------------------------------------------

TestManager::TestManager (size_t wWidth, size_t wHeight, Color background, const char * name) :

	wManager_ (),

	context_ (wWidth, wHeight),

	wWidth_  (wWidth),
	wHeight_ (wHeight),

	background_ (background),

	windowTitle_ (name),

	a_ (),
	b_ (),
	c_ (),

	lastDisplayTime_ (0)

{

	_init ();
	
	TRACE ("Test manager constructed width window size {%zu, %zu}", wWidth, wHeight);

}

//-------------------------------------------

TestManager::TestManager (Color background, const char * name) :

	wManager_ (),

	context_ (GetSystemMetrics (SM_CXSCREEN), GetSystemMetrics (SM_CYSCREEN)),

	wWidth_  (GetSystemMetrics (SM_CXSCREEN)),
	wHeight_ (GetSystemMetrics (SM_CYSCREEN)),

	background_ (background),

	windowTitle_ (name),

	a_ (),
	b_ (),
	c_ (),

	lastDisplayTime_ (0)

{
	
	_txWindowStyle &= ~WS_CAPTION;

	_init ();

	TRACE ("Test manager constructed in fullscreen mode");

}

//-------------------------------------------

TestManager::~TestManager ()

{

	TRACE ("Test manager destructed");

}

//-------------------------------------------

void TestManager::_init ()

{

	srand (time (0));

	_txConsoleMode = SW_SHOW;

	txCreateWindow (wWidth_, wHeight_);
	txDisableAutoPause ();
	txBegin ();

	SetWindowText (txWindow (), windowTitle_);

	wManager_.addWindow (new InteractivePoint (&a_, "A"));
	wManager_.addWindow (new InteractivePoint (&b_, "B"));
	wManager_.addWindow (new InteractivePoint (&c_, "C"));

}

//-------------------------------------------

TestManagerRunResult TestManager::run ()

{
	
	resetPoints ();

	while (!GetAsyncKeyState (VK_ESCAPE) && !_txWindowClosed)

	{

		long start = GetTickCount ();

		onTimeTick ();

		lastDisplayTime_ = GetTickCount () - start;

		txSleep (0);

	}

	return RunResultOk;

}

//-------------------------------------------

void TestManager::onTimeTick ()

{

	context_.clear (background_);

	try

	{

		DrawTriangle (&context_, a_, b_, c_);

	}

	catch (mc_exception exc)

	{

		TRACE_ERROR ("Unexpected exception while drawing triangle!");
			
		printf ("Points dump:\n"
			    "A: {%.0f, %.0f}\n"
			    "B: {%.0f, %.0f}\n"
			    "C: {%.0f, %.0f}\n", a_.x, a_.y, b_.x, b_.y, c_.x, c_.y);

		throw (exc);
	
	}

	context_.drawInTxDC ();

	wManager_.onTimeTick ();

	if (GetKeyState (VK_NUMLOCK)) drawDisplayTime ();

	if (GetAsyncKeyState ('R')) resetPoints ();

	if (GetAsyncKeyState ('E'))

	{
	
		mcThrowTestException ();

	}

}

//-------------------------------------------

void TestManager::drawDisplayTime ()

{

	Color color (0, 180, 255);

	char str[256] = "";

	sprintf_s (str, "Drawing last frame took %d msec", lastDisplayTime_);

	txSetColor     (color);
	txSetFillColor (color);

	txSelectFont ("Consolas", 30, 15);

	txTextOut (5, 5, str);

}

//-------------------------------------------

const char * strRunResult (TestManagerRunResult result)

{

	#define STR_RESULT(result, descr) case result: return #result ": " descr;

	switch (result)

	{
	
		STR_RESULT (RunResultNone,  "Undefined result"          );
		STR_RESULT (RunResultOk,    "Manager succesfully closed");
		STR_RESULT (RunResultError, "Manager closed with error" );

	}

	return "Unknown run result";

}