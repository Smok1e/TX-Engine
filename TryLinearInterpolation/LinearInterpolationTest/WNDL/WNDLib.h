#include <TXLib.h>

//-----------------------------------------------------------------------------

const int WINDOWS_MAX = 300;

FILE * EventLog = fopen ("eventlog.txt", "w");

#define PATH_MAX 512

#define __PRETTY_FUNCTION__ __FUNCSIG__

//-----------------------------------------------------------------------------

enum MouseState

{

    MouseNone,
    MouseHover,
    MouseClick,
    MouseRelease

};

//-----------------------------------------------------------------------------

struct AbstractWindow;

struct ContainerWindow;

//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------

struct ArrayString

{

    char text_[PATH_MAX];

    int length_;

    ArrayString (const char * text);

    int getLength ();

    void append (char symbol);

    void removeChar (int n);

    const char * getText ();

    void insertChar (int n, char symbol);

    double getTextExtentX (int n);

};

ArrayString::ArrayString (const char * text) :

    text_ (""),

    length_ (0)

{

    strcpy_s (text_, text);

    length_ = strlen (text_);

}

//-----------------------------------------------------------------------------

struct Mouse

{

    int buttons;

    int lastButtons;

    POINT pos;

    int state_;

    Mouse ();

    int getButtons ();

    int getLastButtons ();

    POINT getPos ();

    bool onClickTest ();

    bool onReleaseTest ();

    void update ();

};

Mouse::Mouse () :

    buttons (txMouseButtons ()),

    lastButtons (txMouseButtons ()),

    pos (txMousePos ())

{}

//-----------------------------------------------------------------------------

struct WindowManager

{

    AbstractWindow * windows_[WINDOWS_MAX];

    Mouse mouse_;

    AbstractWindow * activeWindow_;

    WindowManager ();

    ~WindowManager ();

    int addWindow (AbstractWindow * window);

    void drawWindows ();

    void processEvents ();

    int windowsAmount ();

    AbstractWindow * getWindow (int id);

    void onTimeTick ();

    bool setActiveWindow (AbstractWindow * window);

    AbstractWindow * getActiveWindow ();

};

WindowManager::WindowManager () :

    windows_      (),

    mouse_        (),

    activeWindow_ (nullptr)

{}

WindowManager::~WindowManager ()

{

    for (int n = 0; n < WINDOWS_MAX; n++)

    {

        if (!windows_[n]) continue;

        delete (windows_[n]);

        windows_[n] = nullptr;

    }

}

//-----------------------------------------------------------------------------

struct AbstractWindow

{

    double x_;
    double y_;

    double width_;
    double height_;

    COLORREF color_;

    ContainerWindow * parent_;

    bool visible_;

    int id_;

    WindowManager * manager_;

    AbstractWindow (double x, double y, double width, double height, COLORREF color);

    ContainerWindow * getParent ();

    virtual void draw ();

    virtual bool onMouseRelease (Mouse * mouse);

    virtual bool onMouseTest (Mouse * mouse);

    virtual bool onMouseClick (Mouse * mouse);

    virtual bool onKeyDown (char key);

    virtual void onActivate ();

    virtual bool onDeactivate ();

    virtual void onTimeTick ();

    virtual void setId (int id);

    virtual int getId ();

};

AbstractWindow::AbstractWindow (double x, double y, double width, double height, COLORREF color) :

    x_         (x),
    y_         (y),
    width_     (width),
    height_    (height),
    color_     (color),

    visible_   (true),

    id_        (-1)

{}

//-----------------------------------------------------------------------------

struct ContainerWindow : AbstractWindow

{

    WindowManager manager_;

    ContainerWindow (double x, double y, double width, double height, COLORREF color);

    virtual int addWindow (AbstractWindow * wnd);

    virtual int windowsAmount ();

    virtual void onTimeTick () override;

    AbstractWindow * getWindow (int id);

};

ContainerWindow::ContainerWindow (double x, double y, double width, double height, COLORREF color) :

    AbstractWindow (x, y, width, height, color),

    manager_ ({})

{}

//-----------------------------------------------------------------------------

struct AbstractButton : AbstractWindow

{

    void (*action_) (AbstractWindow * wnd);

    int state_;

    AbstractButton (double x, double y, double width, double height, COLORREF color, void (*action) (AbstractWindow * wnd));

    virtual bool onMouseTest (Mouse * mouse);

    virtual bool onMouseClick (Mouse * mouse);

    int getState ();

};

AbstractButton::AbstractButton (double x, double y, double width, double height, COLORREF color, void (*action) (AbstractWindow * wnd)) :

    AbstractWindow (x, y, width, height, color),

    action_ (action),

    state_  (MouseNone)

{}

//-----------------------------------------------------------------------------

struct Button : AbstractButton

{

    COLORREF strokeColor_;

    Button (double x, double y, double width, double height, COLORREF color, COLORREF strokeColor, void (*action) (AbstractWindow * wnd));

    virtual void draw ();

};

Button::Button (double x, double y, double width, double height, COLORREF color, COLORREF strokeColor, void (*action) (AbstractWindow * wnd)) :

    AbstractButton (x, y, width, height, color, action),

    strokeColor_ (strokeColor)

{}

//-----------------------------------------------------------------------------

struct TextButton : Button

{

    const char * text_;
    const char * font_;

    double fontSize_;

    COLORREF textColor_;

    TextButton (double x, double y, double width, double height, COLORREF color, COLORREF strokeColor, const char * text, const char * font, double fontSize, COLORREF textColor, void (*action) (AbstractWindow * wnd));

    virtual void draw ();

};

TextButton::TextButton (double x, double y, double width, double height, COLORREF color, COLORREF strokeColor, const char * text, const char * font, double fontSize, COLORREF textColor, void (*action) (AbstractWindow * wnd)) :

    Button (x, y, width, height, color, strokeColor, action),

    text_      (text),
    font_      (font),

    fontSize_  (fontSize),

    textColor_ (textColor)

{}

//-----------------------------------------------------------------------------

struct ImageButton : Button

{

    HDC image_;

    ImageButton (double x, double y, HDC image, void (*action) (AbstractWindow * wnd));

    ~ImageButton ();

    virtual void draw ();

    virtual bool onMouseTest (Mouse * mouse);

};

ImageButton::ImageButton (double x, double y, HDC image, void (*action) (AbstractWindow * wnd)) :

    Button (x, y, txGetExtentX (image), txGetExtentY (image), TX_TRANSPARENT, TX_TRANSPARENT, action),

    image_ (image)

{}

ImageButton::~ImageButton ()

{

    txDeleteDC (image_);

}

//-----------------------------------------------------------------------------

struct TextBox : AbstractWindow

{

    ArrayString text_;
    const char * font_;

    double fontSize_;

    COLORREF textColor_;

    TextBox (double x, double y, double width, double height, COLORREF color, const char * text, const char * font, double fontSize, COLORREF textColor);

    virtual void draw ();

};

TextBox::TextBox (double x, double y, double width, double height, COLORREF color, const char * text, const char * font, double fontSize, COLORREF textColor) :

    AbstractWindow (x, y, width, height, color),

    text_      (text),
    font_      (font),

    fontSize_  (fontSize),

    textColor_ (textColor)

{}

//-----------------------------------------------------------------------------

struct WriteBox : TextBox

{

    bool isActive_;

    int counter_;

    int cursorPos_;

    COLORREF strokeColor_;

    WriteBox (double x, double y, double width, double height, COLORREF color, const char * text, const char * font, double fontSize, COLORREF textColor, COLORREF strokeColor);

    virtual void draw ();

    virtual void onTimeTick ();

    virtual void onActivate ();

    virtual bool onDeactivate ();

    virtual bool onKeyDown (char key);

};

WriteBox::WriteBox (double x, double y, double width, double height, COLORREF color, const char * text, const char * font, double fontSize, COLORREF textColor, COLORREF strokeColor) :

    TextBox (x, y, width, height, color, text, font, fontSize, textColor),

    isActive_    (false),

    counter_     (0),

    cursorPos_   (0),

    strokeColor_ (strokeColor)

{

    cursorPos_ = text_.getLength ();

}

//-----------------------------------------------------------------------------

void AbstractWindow::draw ()

{

    txSetColor (color_);
    txSetFillColor (color_);
    txRectangle (x_, y_, x_ + width_, y_ + height_);

}

//-----------------------------------------------------------------------------

bool AbstractWindow::onMouseTest (Mouse * mouse)

{

    POINT mPos = mouse -> getPos ();

    if (mPos.x >= x_ && mPos.x < x_ + width_ && mPos.y >= y_ && mPos.y < y_ + height_) return true;

    return false;

}

//-----------------------------------------------------------------------------

bool AbstractWindow::onMouseClick (Mouse * mouse)

{

    return true;

}

//-----------------------------------------------------------------------------

bool AbstractWindow::onMouseRelease (Mouse * mouse)

{

    return false;

}

//-----------------------------------------------------------------------------

void AbstractWindow::onActivate ()

{

}

//-----------------------------------------------------------------------------

bool AbstractWindow::onDeactivate ()

{

    return true;

}

//-----------------------------------------------------------------------------

bool AbstractWindow::onKeyDown (char key)

{

    return true;

}

//-----------------------------------------------------------------------------

void AbstractWindow::onTimeTick ()

{

}

//-----------------------------------------------------------------------------

void AbstractWindow::setId (int id)

{

    id_ = id;

}

//-----------------------------------------------------------------------------

int AbstractWindow::getId ()

{

    return id_;

}

//-----------------------------------------------------------------------------

int ContainerWindow::addWindow (AbstractWindow * window)

{

    window -> parent_ = this;              

    return manager_.addWindow (window);

}

//-----------------------------------------------------------------------------

ContainerWindow * AbstractWindow::getParent ()

{

    return parent_;

}

//-----------------------------------------------------------------------------

int ContainerWindow::windowsAmount ()

{

    return manager_.windowsAmount ();

}

//-----------------------------------------------------------------------------

void ContainerWindow::onTimeTick ()

{

    draw ();

    manager_.onTimeTick ();

}

//-----------------------------------------------------------------------------

AbstractWindow * ContainerWindow::getWindow (int id)

{

    return manager_.getWindow (id);

}

//-----------------------------------------------------------------------------

bool AbstractButton::onMouseTest (Mouse * mouse)

{

    state_ = MouseNone;

    if (AbstractWindow::onMouseTest (mouse))

    {

        state_ = MouseHover;

        return true;

    }

    return false;

}

//-----------------------------------------------------------------------------

bool AbstractButton::onMouseClick (Mouse * mouse)

{

    if (action_) 
        
    {

        action_ (this);

        return true;

    }

    return false;

}

//-----------------------------------------------------------------------------

int AbstractButton::getState ()

{

    return state_;

}

//-----------------------------------------------------------------------------

void Button::draw ()

{

    if (getState () == MouseHover)

    {

        txSetColor (strokeColor_);
        txSetFillColor (strokeColor_);

        txRectangle (x_ - 2, y_ - 2, x_ + width_ + 2, y_ + height_ + 2);

    }

    AbstractButton::draw ();

}

//-----------------------------------------------------------------------------

void TextButton::draw ()

{

    Button::draw ();

    txSetColor (textColor_);
    txSetFillColor (textColor_);

    txSelectFont (font_, fontSize_);

    txDrawText (x_, y_, x_ + width_, y_ + height_, text_);

}

//-----------------------------------------------------------------------------

void ImageButton::draw ()

{

    txAlphaBlend (txDC (), x_, y_, width_, height_, image_);

}

//-----------------------------------------------------------------------------

bool ImageButton::onMouseTest (Mouse * mouse)

{

    if (!AbstractWindow::onMouseTest (mouse)) return false;

    POINT mPos = txMousePos ();

    COLORREF pixel = txGetPixel (mPos.x - x_, mPos.y - y_, image_);

    if (pixel == 0xFFFFFF) return false;

    return true;

}

//-----------------------------------------------------------------------------

void TextBox::draw ()

{

    AbstractWindow::draw ();

    txSelectFont (font_, fontSize_);
    txSetColor (textColor_);
    txSetFillColor (textColor_);

    txDrawText (x_, y_, x_ + width_, y_ + height_, text_.getText ());

}

//-----------------------------------------------------------------------------

void WriteBox::draw ()

{

    if (isActive_)

    {

        txSetColor (strokeColor_);
        txSetFillColor (strokeColor_);
        txRectangle (x_ - 2, y_ - 2, x_ + width_ + 2, y_ + height_ + 2);

    }

    TextBox::draw ();

    if (isActive_)

    {

        if (counter_ < 40)

        {

            POINT line = {0, y_ + height_ / 2 - (fontSize_ * 0.75) / 2};

            line.x = x_ + width_ / 2 - txGetTextExtentX (text_.text_) / 2 + text_.getTextExtentX (cursorPos_);

            if (line.x > x_ + width_) line.x = x_ + width_;

            txSetColor (textColor_, 1);
            txSetFillColor (textColor_);

            txLine (line.x, line.y, line.x, line.y + (fontSize_ * 0.75));

        }

    }

}

//-----------------------------------------------------------------------------

void WriteBox::onTimeTick ()

{

    counter_ ++;

    if (counter_ >= 80) counter_ = 0;

}

//-----------------------------------------------------------------------------

void WriteBox::onActivate ()

{

    isActive_ = true;

}

//-----------------------------------------------------------------------------

bool WriteBox::onDeactivate ()

{

    isActive_ = false;

    return true;

}

//-----------------------------------------------------------------------------

bool WriteBox::onKeyDown (char key)

{

    switch (key)

    {

        case VK_BACK:

        {

            text_.removeChar (cursorPos_ - 1);

            if (cursorPos_ > 0) cursorPos_ --;

            break;

        }

        case '2':

        {

            if (text_.getLength () > cursorPos_) cursorPos_ ++;

            break;

        }

        case '1':

        {

            if (cursorPos_ > 0) cursorPos_ --;

            break;

        }

        default:

        {

            text_.insertChar (cursorPos_, key);

            cursorPos_++;

        }

    }

    fprintf (EventLog, "%s: key = %c (%d), window #%p, return true\n", __PRETTY_FUNCTION__, key, key, this);

    return true;

}

//-----------------------------------------------------------------------------

int ArrayString::getLength ()

{

    return length_;

}

//-----------------------------------------------------------------------------

void ArrayString::append (char symbol)

{

    if (getLength () < PATH_MAX)

    {

        int n = getLength ();

        text_[n] = symbol;

        length_ ++;

    }

}

//-----------------------------------------------------------------------------

void ArrayString::removeChar (int n)

{

    if (n >= 0 && n < PATH_MAX)

    {

        char text[PATH_MAX] = "";

        sprintf_s (text, "%s", text_);

        text [n] = NULL;

        for (int i = n; i <= length_; i++)

        {

            text [i] = text_ [i + 1];

        }

        sprintf_s (text_, "%s", text);

        length_ --;

    }

}

//-----------------------------------------------------------------------------

const char * ArrayString::getText ()

{

    return text_;

}

//-----------------------------------------------------------------------------

void ArrayString::insertChar (int n, char symbol)

{

    char text[PATH_MAX] = "";

    int i = 0;

    for (i = 0; i < n; i++)

    {

        text [i] = text_ [i];

    }

    text [i] = symbol;

    i++;

    for (i = i; i <= getLength (); i++)

    {

        text [i] = text_ [i - 1];

    }

    sprintf_s (text_, "%s", text);

    length_ ++;

}

//-----------------------------------------------------------------------------

double ArrayString::getTextExtentX (int n)

{

    char symbol = text_ [n];

    text_ [n] = '\0';

    double length = txGetTextExtentX (text_);

    text_ [n] = symbol;

    return length;

}

//-----------------------------------------------------------------------------

void Mouse::update ()

{

    lastButtons = buttons;

    buttons = txMouseButtons ();

    pos = txMousePos ();

    state_ = MouseNone;

}

//-----------------------------------------------------------------------------

int Mouse::getButtons ()

{

    return buttons;

}

//-----------------------------------------------------------------------------

int Mouse::getLastButtons ()

{

    return lastButtons;

}

//-----------------------------------------------------------------------------

POINT Mouse::getPos ()

{

    return pos;

}

//-----------------------------------------------------------------------------

bool Mouse::onClickTest ()

{

    if (getLastButtons () == 0 && getButtons () == 1)

    {

        state_ = MouseClick;

        return true;

    }

    return false;

}

//-----------------------------------------------------------------------------

bool Mouse::onReleaseTest ()

{

    if (getLastButtons () == 1 && getButtons () == 0)

    {

        state_ = MouseRelease;

        return true;

    }

    return false;

}

//-----------------------------------------------------------------------------

int WindowManager::addWindow (AbstractWindow * window)

{

    for (int n = 0; n < WINDOWS_MAX; n++)

    {

        if (!windows_[n])

        {

            windows_[n] = window;

            setActiveWindow (window);

            window -> manager_ = this;

            return n;

        }

    }

    TX_ERROR ("The array of windows is full.");

    return -1;

}

//-----------------------------------------------------------------------------

void WindowManager::drawWindows ()

{

    for (int n = 0; n < WINDOWS_MAX; n++)

    {

        if (!windows_[n] || !windows_[n] -> visible_) return;

        windows_[n] -> draw ();

    }

}

//-----------------------------------------------------------------------------

void WindowManager::processEvents ()

{

    mouse_.update ();

    char key = 0;

    if (_kbhit ())

    {

        key = _getch ();

    }

    if (key)

    {

        fprintf (EventLog, "%s: key = %c (%d), active window = %p\n", __PRETTY_FUNCTION__, key, key, getActiveWindow ());

        bool res = getActiveWindow () -> onKeyDown (key);

        fprintf (EventLog, "%s: getActiveWindow -> onKeyDown (key) = %d\n", __PRETTY_FUNCTION__, res);

        if (!res)

        {

            for (int n = 0; n < WINDOWS_MAX; n++)

            {

                if (!windows_[n]) continue;

                if (windows_[n] == getActiveWindow ()) continue;

                if (windows_[n] -> onKeyDown (key)) break;

            }

        }

    }

    for (int n = 0; n < WINDOWS_MAX; n++)

    {

        if (!windows_[n] || !windows_[n] -> visible_) return;

        if (windows_[n] -> onMouseTest (&mouse_))

        {

            if (mouse_.onClickTest ())

            {

                windows_[n] -> onMouseClick (&mouse_);

                setActiveWindow (windows_[n]);

            }

            else if (mouse_.onReleaseTest ())

            {
            
                windows_[n] -> onMouseRelease (&mouse_);

            }

        }

        windows_[n] -> onTimeTick ();

    }

}

//-----------------------------------------------------------------------------

int WindowManager::windowsAmount ()

{

    int amount = 0;

    for (int n = 0; n < WINDOWS_MAX; n++)

    {

        if (!windows_[n] || !windows_[n] -> visible_) continue;

        amount ++;

    }

    return amount;

}

//-----------------------------------------------------------------------------

AbstractWindow * WindowManager::getWindow (int id)

{

    for (int n = 0; n < WINDOWS_MAX; n++)

    {

        if (!windows_[n]) continue;

        if (windows_[n] -> getId () == id) return windows_[n];

    }

    return NULL;

}

//-----------------------------------------------------------------------------

void WindowManager::onTimeTick ()

{

    drawWindows ();
    processEvents ();

}

//-----------------------------------------------------------------------------

bool WindowManager::setActiveWindow (AbstractWindow * window)

{

    if (activeWindow_)

    {

        if (!activeWindow_ -> onDeactivate ()) return false;

    }

    fprintf (EventLog, "%s: changing active window from %p to %p\n", __PRETTY_FUNCTION__, activeWindow_, window);

    activeWindow_ = window;

    activeWindow_ -> onActivate ();

    return true;

}

AbstractWindow * WindowManager::getActiveWindow ()

{

    return activeWindow_;

}
