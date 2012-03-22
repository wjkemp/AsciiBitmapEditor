/*  drawingtoolundoaction.h
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
#ifndef __DRAWINGTOOLUNDOACTION_H__
#define __DRAWINGTOOLUNDOACTION_H__

#include "toolundoaction.h"


//-----------------------------------------------------------------------------
//	Class Definition
//-----------------------------------------------------------------------------
class DrawingToolUndoAction : public ToolUndoAction
{
public:
    DrawingToolUndoAction(
        int x,
        int y,
        int characterFrom,
        const QColor& foregroundColorFrom,
        const QColor& backgroundColorFrom,
        int characterTo,
        const QColor& foregroundColorTo,
        const QColor& backgroundColorTo);
    void undo(Bitmap& bitmap);
    void redo(Bitmap& bitmap);

protected:
    int _x;
    int _y;
    int _characterFrom;
    QColor _foregroundColorFrom;
    QColor _backgroundColorFrom;
    int _characterTo;
    QColor _foregroundColorTo;
    QColor _backgroundColorTo;

};


#endif
