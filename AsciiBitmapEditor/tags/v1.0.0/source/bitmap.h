/*  bitmap.h
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
#ifndef __BITMAP_H__
#define __BITMAP_H__

#include <QColor>
#include <vector>


//-----------------------------------------------------------------------------
//	Class Definition
//-----------------------------------------------------------------------------
class Bitmap
{
public:
	Bitmap();
    Bitmap(int width, int height);
    Bitmap(const Bitmap& obj);
    Bitmap& operator = (const Bitmap& obj);
	~Bitmap();

    int width() const { return _width; }
    int height() const { return _height; }

    unsigned char characterAt(int x, int y) const;
    void setCharacterAt(int x, int y, unsigned char ch);

    QColor foregroundColorAt(int x, int y) const;
    void setForegroundColorAt(int x, int y, const QColor& color);

    QColor backgroundColorAt(int x, int y) const;
    void setBackgroundColorAt(int x, int y, const QColor& color);


private:
    int _width;
    int _height;
    std::vector<unsigned char> _characters;
    std::vector<QColor> _foregroundColors;
    std::vector<QColor> _backgroundColors;
};


#endif
