/*  backgroundcolortool.cpp
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
#include "backgroundcolortool.h"
#include "backgroundcolortoolundoaction.h"


//-----------------------------------------------------------------------------
BackgroundColorTool::BackgroundColorTool() :
    ColorTool("Background Colors")
{
    // Select a default
    _paletteIndex = 0;
    _toolButtons[0]->setChecked(true);
}


//-----------------------------------------------------------------------------
BackgroundColorTool::~BackgroundColorTool()
{

}


//-----------------------------------------------------------------------------
ToolUndoAction* BackgroundColorTool::doPrimaryFunction(Bitmap& bitmap, int x, int y)
{
    ToolUndoAction* undoAction = 0;
    QColor colorFrom(bitmap.backgroundColorAt(x, y));
    QColor colorTo(selectedColor());
    if (colorFrom != colorTo) {
        bitmap.setBackgroundColorAt(x, y, selectedColor());
        undoAction = new BackgroundColorToolUndoAction(x, y, colorFrom, colorTo);
    }

    return undoAction;
}


//-----------------------------------------------------------------------------
ToolUndoAction* BackgroundColorTool::doSecondaryFunction(Bitmap& bitmap, int x, int y)
{
    return 0;
}

