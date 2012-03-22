/*  bitmap.cpp
 *
 *  Copyright (C) 2012 Willem Kemp <http://www.thenocturnaltree.com/>
 *  All rights reserved.
 *
 *  This file is part of AsciiBitmapEditor.
 *
 *  AsciiBitmapEditor is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  AsciiBitmapEditor is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with AsciiBitmapEditor. If not, see http://www.gnu.org/licenses/.
 *
 */
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
