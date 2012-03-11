/******************************************************************************
	bitmap.cpp
 ******************************************************************************/
#include "bitmap.h"
#include <string.h>

//-----------------------------------------------------------------------------
Bitmap::Bitmap()
{
    _width = 10;
    _height = 10;
    _characters.reserve(_width * _height);
    _foregroundColors.reserve(_width * _height);
    _backgroundColors.reserve(_width * _height);

    for (int i=0; i < _width * _height; ++i) {
        _characters.push_back(0);
        _foregroundColors.push_back(QColor(0, 0, 0));
        _backgroundColors.push_back(QColor(0, 0, 0));
    }
}


//-----------------------------------------------------------------------------
Bitmap::Bitmap(int width, int height) :
    _width(width),
    _height(height)
{
    _characters.reserve(_width * _height);
    _foregroundColors.reserve(_width * _height);
    _backgroundColors.reserve(_width * _height);

    for (int i=0; i < _width * _height; ++i) {
        _characters.push_back(0);
        _foregroundColors.push_back(QColor(0x7F, 0x7F, 0x7F));
        _backgroundColors.push_back(QColor(0,0,0));
    }
}


//-----------------------------------------------------------------------------
Bitmap::Bitmap(const Bitmap& obj) :
    _width(obj._width),
    _height(obj._height),
    _characters(obj._characters),
    _foregroundColors(obj._foregroundColors),
    _backgroundColors(obj._backgroundColors)

{

}


//-----------------------------------------------------------------------------
Bitmap& Bitmap::operator = (const Bitmap& obj)
{
    if (this != &obj) {
        _width = obj._width;
        _height = obj._height;
        _characters = obj._characters;
        _foregroundColors = obj._foregroundColors;
        _backgroundColors = obj._backgroundColors;

    }

    return *this;
}


//-----------------------------------------------------------------------------
Bitmap::~Bitmap()
{
}




//-----------------------------------------------------------------------------
unsigned char Bitmap::characterAt(int x, int y) const
{
    return _characters[x + (y * _width)];
}


//-----------------------------------------------------------------------------
void Bitmap::setCharacterAt(int x, int y, unsigned char ch)
{
    _characters[x + (y * _width)] = ch;
}


//-----------------------------------------------------------------------------
QColor Bitmap::foregroundColorAt(int x, int y) const
{
    return _foregroundColors[x + (y * _width)];
}


//-----------------------------------------------------------------------------
void Bitmap::setForegroundColorAt(int x, int y, const QColor& color)
{
    _foregroundColors[x + (y * _width)] = color;
}


//-----------------------------------------------------------------------------
QColor Bitmap::backgroundColorAt(int x, int y) const
{
    return _backgroundColors[x + (y * _width)];
}


//-----------------------------------------------------------------------------
void Bitmap::setBackgroundColorAt(int x, int y, const QColor& color)
{
    _backgroundColors[x + (y * _width)] = color;
}
