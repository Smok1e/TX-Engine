
const int wWidth = 800;
const int wHeight = 800;

//-----------------------------------------------------------------------------

#include <TXLib.h>
#include "WNDLib.h"
#include "ResourceManager.h"

//-----------------------------------------------------------------------------

void testAction (AbstractWindow * wnd);

double rnd (double from, double to);

//-----------------------------------------------------------------------------

int main ()

{

    txCreateWindow (wWidth, wHeight);
    txDisableAutoPause ();

    txBegin ();

    ResourceManager ResManager = {Resources, "Resources\\Images"};

    ContainerWindow * container = new ContainerWindow ({0, 0, wWidth, wHeight, TX_WHITE});

    container -> addWindow (new WriteBox {100, 375, 600, 20, RGB (45, 45, 45), "Test", "Arial", 20, TX_WHITE, RGB (255, 0, 0)});

    while (!GetAsyncKeyState (VK_ESCAPE))

    {

        container -> onTimeTick ();

        txSleep (1);

    }

    fclose (EventLog);

}

//-----------------------------------------------------------------------------

void testAction(AbstractWindow * wnd)

{

    wnd -> color_ = RGB (rnd (0, 255), rnd (0, 255), rnd (0, 255));

}

//-----------------------------------------------------------------------------

double rnd (double from, double to)

{

    return from + 1.0 * rand () / RAND_MAX * (to - from);

}
