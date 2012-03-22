/*  bitmapexporter.cpp
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
#include "bitmapexporter.h"
#include <fstream>

//-----------------------------------------------------------------------------
BitmapExporter::BitmapExporter()
{
}


//-----------------------------------------------------------------------------
BitmapExporter::~BitmapExporter()
{
}


//-----------------------------------------------------------------------------
bool BitmapExporter::write(const Bitmap& bitmap, const std::string& filename)
{
    bool result = false;
    std::ofstream file(filename.c_str());
    if (file.is_open()) {

        file << "const unsigned long BITMAP[] = {" << std::endl;

        file << '\t' << bitmap.width() << ", " << bitmap.height() << "," << std::endl;

        for (int h=0; h < bitmap.height(); h++) {

            file << '\t';

            for (int w=0; w < bitmap.width(); w++) {

                unsigned long character = (unsigned long)bitmap.characterAt(w, h);
                unsigned long foregroundColorMap = 0;
                unsigned long backgroundColorMap = 0;

                QColor foregroundColor(bitmap.foregroundColorAt(w, h));
                QColor backgroundColor(bitmap.backgroundColorAt(w, h));

                if (foregroundColor.blue()) {
                    foregroundColorMap |= 0x01;
                }

                if (foregroundColor.green()) {
                    foregroundColorMap |= 0x02;
                }

                if (foregroundColor.red()) {
                    foregroundColorMap |= 0x04;
                }

                if ((foregroundColor.red() > 0x7F) || (foregroundColor.green() > 0x7F) || (foregroundColor.blue() > 0x7F)) {
                    foregroundColorMap |= 0x08;
                }

                if (backgroundColor.blue()) {
                    backgroundColorMap |= 0x01;
                }

                if (backgroundColor.green()) {
                    backgroundColorMap |= 0x02;
                }

                if (backgroundColor.red()) {
                    backgroundColorMap |= 0x04;
                }

                if ((backgroundColor.red() > 0x7F) || (backgroundColor.green() > 0x7F) || (backgroundColor.blue() > 0x7F)) {
                    backgroundColorMap |= 0x08;
                }


                character |= foregroundColorMap << 8;
                character |= backgroundColorMap << 12;

                file << character << ",";
            }

            file << std::endl;
        }

        file << "};" << std::endl;
        result = true;
    }

    return result;
}
