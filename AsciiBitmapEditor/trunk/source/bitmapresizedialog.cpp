/*  bitmapresizedialog.cpp
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
#include "bitmapresizedialog.h"


//-----------------------------------------------------------------------------
BitmapResizeDialog::BitmapResizeDialog(QWidget* parent) :
	QDialog(parent)
{
    ui.setupUi(this);

}


//-----------------------------------------------------------------------------
BitmapResizeDialog::~BitmapResizeDialog()
{

}


//-----------------------------------------------------------------------------
int BitmapResizeDialog::width() const
{
    return ui.width->text().toInt();
}


//-----------------------------------------------------------------------------
int BitmapResizeDialog::height() const
{
    return ui.height->text().toInt();

}
