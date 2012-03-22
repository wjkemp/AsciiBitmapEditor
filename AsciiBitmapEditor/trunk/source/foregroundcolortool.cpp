/*  foregroundcolortool.cpp
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
#include "foregroundcolortool.h"
#include "foregroundcolortoolundoaction.h"


//-----------------------------------------------------------------------------
ForegroundColorTool::ForegroundColorTool() :
    ColorTool("Foreground Colors")
{
    // Select a default
    _paletteIndex = 7;
    _toolButtons[7]->setChecked(true);
}


//-----------------------------------------------------------------------------
ForegroundColorTool::~ForegroundColorTool()
{

}


//-----------------------------------------------------------------------------
ToolUndoAction* ForegroundColorTool::doPrimaryFunction(Bitmap& bitmap, int x, int y)
{
    ToolUndoAction* undoAction = 0;
    QColor colorFrom(bitmap.foregroundColorAt(x, y));
    QColor colorTo(selectedColor());
    if (colorFrom != colorTo) {
        bitmap.setForegroundColorAt(x, y, selectedColor());
        undoAction = new ForegroundColorToolUndoAction(x, y, colorFrom, colorTo);
    }

    return undoAction;
}


//-----------------------------------------------------------------------------
ToolUndoAction* ForegroundColorTool::doSecondaryFunction(Bitmap& bitmap, int x, int y)
{
    return 0;
}

