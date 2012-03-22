/*  drawingtool.h
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
#ifndef __DRAWINGTOOL_H__
#define __DRAWINGTOOL_H__

#include "tool.h"
#include <QToolBox>
#include <QSignalMapper>
#include <QToolButton>
#include <map>
#include "colortool.h"


//-----------------------------------------------------------------------------
//	Class Definition
//-----------------------------------------------------------------------------
class DrawingTool : public Tool
{
    Q_OBJECT

public:
    DrawingTool(ColorTool* foregroundColorTool, ColorTool* backgroundColorTool);
    ~DrawingTool();
    QWidget* toolWidget();
    ToolUndoAction* doPrimaryFunction(Bitmap& bitmap, int x, int y);
    ToolUndoAction* doSecondaryFunction(Bitmap& bitmap, int x, int y);

signals:
    void deselectCharacterTools(bool checked);

protected slots:
    void selectCharacterTool(int index);


protected:
    QWidget* createAlphanumericPalette();
    QWidget* createLinePalette();
    QWidget* createSymbolPalette();

protected:
    QToolBox* _toolWidget;
    ColorTool* _foregroundColorTool;
    ColorTool* _backgroundColorTool;
    unsigned char _characterIndex;
    QSignalMapper _characterMap;
    std::map<int, QToolButton*> _characterButtons;

};


#endif
