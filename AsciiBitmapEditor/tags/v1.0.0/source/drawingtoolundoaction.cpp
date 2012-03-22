/*  drawingtoolundocation.cpp
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
#include "drawingtoolundoaction.h"


//-----------------------------------------------------------------------------
DrawingToolUndoAction::DrawingToolUndoAction(
    int x,
    int y,
    int characterFrom,
    const QColor& foregroundColorFrom,
    const QColor& backgroundColorFrom,
    int characterTo,
    const QColor& foregroundColorTo,
    const QColor& backgroundColorTo) :
    _x(x),
    _y(y),
    _characterFrom(characterFrom),
    _foregroundColorFrom(foregroundColorFrom),
    _backgroundColorFrom(backgroundColorFrom),
    _characterTo(characterTo),
    _foregroundColorTo(foregroundColorTo),
    _backgroundColorTo(backgroundColorTo)
{

}


//-----------------------------------------------------------------------------
void DrawingToolUndoAction::undo(Bitmap& bitmap)
{
    bitmap.setCharacterAt(_x, _y, _characterFrom);
    bitmap.setForegroundColorAt(_x, _y, _foregroundColorFrom);
    bitmap.setBackgroundColorAt(_x, _y, _backgroundColorFrom);
}


//-----------------------------------------------------------------------------
void DrawingToolUndoAction::redo(Bitmap& bitmap)
{
    bitmap.setCharacterAt(_x, _y, _characterTo);
    bitmap.setForegroundColorAt(_x, _y, _foregroundColorTo);
    bitmap.setBackgroundColorAt(_x, _y, _backgroundColorTo);
}
