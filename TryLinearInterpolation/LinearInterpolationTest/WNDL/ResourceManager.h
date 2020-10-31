#include <TXLib.h>

enum Image

{

    ImageBackground,
    ImageDoritos,
    ImageLightDoritos,
    ImageIlluminati,
    ImageLightIlluminati,

    ImageAmount

};

//-----------------------------------------------------------------------------

struct Resource

{

    int number_;

    const char * path_;

    int frames_;

};

//-----------------------------------------------------------------------------

struct ResourceManager

{

    HDC images_[ImageAmount];

    ResourceManager (Resource * resources, const char * resourcesPath);

    ~ResourceManager ();

    HDC getImage (int image);

    int getFrames (int image);

};

ResourceManager::ResourceManager (Resource * resources, const char * resourcesPath) :

    images_ ()

{

    for (int i = 0; i < ImageAmount; i++)

    {

        assert (!images_[i]);

        char path[PATH_MAX] = "";

        sprintf (path, "%s\\%s", resourcesPath, resources[i].path_);

        images_[i] = txLoadImage (path);

        txSetFillColor (RGB (45, 45, 45));
        txClear ();

        txSetColor (TX_WHITE);
        txSetFillColor (TX_WHITE);

        double A = (M_PI * 2) / ImageAmount * i;

        for (double a = 0; a <= A; a += M_PI / 90)

        {

            int x = wWidth / 2 + sin (a) * 100;
            int y = wHeight / 2 + cos (a) * 100;

            txCircle (x, y, 4);

        }

        char text[100] = "";

        sprintf (text, "Loading resources %d%s", 100 / ImageAmount * i, "%");

        txSelectFont ("Arial", 30);
        txTextOut (wWidth / 2 - txGetTextExtentX (text) / 2, wHeight / 2 + 200 - txGetTextExtentY (text) / 2, text);

        txSleep (20);

    }

}

ResourceManager::~ResourceManager ()

{

    for (int i = 0; i < ImageAmount; i++)

    {

        txDeleteDC (images_[i]);

    }

}

//=============================================================================

Resource Resources[] = {

    {ImageBackground,   "Background.bmp",         1},
    {ImageDoritos,      "Doritos.bmp",            1},
    {ImageLightDoritos, "LightDoritos.bmp",       1},
    {ImageIlluminati,   "illuminati.bmp",         1},
    {ImageLightIlluminati, "illuminatiLight.bmp", 1}

};

//-----------------------------------------------------------------------------

HDC ResourceManager::getImage (int image)

{

    assert (images_[image]);

    return images_[image];

}

//-----------------------------------------------------------------------------

int ResourceManager::getFrames (int image)

{

    return Resources[image].frames_;

}
