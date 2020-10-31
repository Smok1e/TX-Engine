#define _CRT_SECURE_NO_WARNINGS
#define _TX_MY_CAT_DOES_NOT_LIKE_CONSOLE_TEXT
#define _TX_MY_CAT_DOES_NO_LIKE_CLOSE_DIALOG
//#define _MC_IGNORE_MAX_EXCEPTIONS_COUNT
//#define _MC_MY_CAT_DOES_NOT_LIKE_TRACE

//-------------------------------------------

const size_t wWidth  = 800;
const size_t wHeight = 800;

//-------------------------------------------

#define WARN(expr__) { if (!(expr__)) printf ("WARING: in '%s' [at line %d]: '%s' check failed\n", __FUNCSIG__, __LINE__, #expr__); }

#define RANDOMCOORD rand () % wWidth, rand () % wHeight

//-------------------------------------------

#include "C:\Lib\TXNew\TXNew.h"
#include "C:\Lib\Trace\Main.h"
#include "C:\Lib\McException\Main.h"
#include "C:\Lib\Context\Main.h"
#include "Triangle.h"
#include "WNDL\WNDLib.h"
#include "InteractivePoint.h"
#include "TestManager.h"

//-------------------------------------------

Color Background (32, 32, 32);

int main ()

{

	TestManager manager (wWidth, wHeight, Background, "Linear interpolation");

	TestManagerRunResult runresult = RunResultNone;

	while (true)

	{

		try

		{

			runresult = manager.run ();

			if (runresult != RunResultOk)

			{

				TRACE_WARNING ("Process ended with result 0x%X: '%s'\n", runresult, strRunResult (runresult));

			}

		 	break; 

		}

		catch (mc_exception exc)

		{

			int res = _mcMessage (MB_ICONERROR | MB_YESNO, "Unexpected exception", "Unexpected exception thrown: '%s'\n"
				                                                                   "Press yes to leave peacefully or no to restart\n", exc.what ());

			if (res == IDYES)

				break;

		} 

	}

	return 0;

}