/*  colortool.h
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
#ifndef __COLORTOOL_H__
#define __COLORTOOL_H__

#include "tool.h"
#include <QToolBox>
#include <QSignalMapper>
#include <QToolButton>
#include <map>


//-----------------------------------------------------------------------------
//	Class Definition
//-----------------------------------------------------------------------------
class ColorTool : public Tool
{
    Q_OBJECT

public:
    ColorTool(const QString& name);
    ~ColorTool();
    QWidget* toolWidget();
    QColor selectedColor();

signals:
    void deselectToolButtons(bool checked);

protected slots:
    void selectToolButton(int index);

protected:
    QWidget* createColorPalette();

protected:
    QToolBox* _toolWidget;
    unsigned char _paletteIndex;
    QSignalMapper _paletteMap;
    std::map<int, QToolButton*> _toolButtons;
    std::map<int, QColor> _colors;

};


#endif
