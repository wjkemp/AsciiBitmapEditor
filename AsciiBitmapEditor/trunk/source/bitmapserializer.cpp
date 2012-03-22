/*  bitmapserializer.cpp
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
#include "bitmapserializer.h"
#include <fstream>


//-----------------------------------------------------------------------------
BitmapSerializer::BitmapSerializer()
{
}


//-----------------------------------------------------------------------------
BitmapSerializer::~BitmapSerializer()
{
}


//-----------------------------------------------------------------------------
Bitmap BitmapSerializer::read(const std::string& filename)
{
    Bitmap bitmap;
    std::ifstream file(filename.c_str());

    if (file.is_open()) {
        int width;
        int height;
        file >> width >> height;

        bitmap = Bitmap(width, height);

        for (int w=0; w < bitmap.width(); w++) {
            for (int h=0; h < bitmap.height(); h++) {
                int character;
                int r, g, b;
                file >> character;
                bitmap.setCharacterAt(w, h, character);

                file >> r >> g >> b;
                bitmap.setForegroundColorAt(w, h, QColor(r, g, b));

                file >> r >> g >> b;
                bitmap.setBackgroundColorAt(w, h, QColor(r, g, b));
            }
        }

    }

    return bitmap;
}


//-----------------------------------------------------------------------------
bool BitmapSerializer::write(const Bitmap& bitmap, const std::string& filename)
{
    bool result = false;
    std::ofstream file(filename.c_str());
    if (file.is_open()) {
        file << bitmap.width() << ' ' << bitmap.height();
        for (int w=0; w < bitmap.width(); w++) {
            for (int h=0; h < bitmap.height(); h++) {
                QColor foregroundColor(bitmap.foregroundColorAt(w, h));
                QColor backgroundColor(bitmap.backgroundColorAt(w, h));
                file << ' ' << (int)bitmap.characterAt(w, h);
                file << 
                    ' ' << foregroundColor.red() << 
                    ' ' << foregroundColor.green() << 
                    ' ' << foregroundColor.blue();
                file << 
                    ' ' << backgroundColor.red() << 
                    ' ' << backgroundColor.green() << 
                    ' ' << backgroundColor.blue();
            }
        }

        result = true;
    }

    return result;
}
