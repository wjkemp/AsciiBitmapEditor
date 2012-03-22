/*  bitmapresizedialog.h
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
#ifndef __BITMAPRESIZEDIALOG_H__
#define __BITMAPRESIZEDIALOG_H__

#include <QDialog>

#include "ui_bitmapresizedialog.h"


//-----------------------------------------------------------------------------
//	Class Definition
//-----------------------------------------------------------------------------
class BitmapResizeDialog : public QDialog
{
    Q_OBJECT

public:
	BitmapResizeDialog(QWidget* parent);
	~BitmapResizeDialog();
    int width() const;
    int height() const;

protected:
    Ui::BitmapResizeDialog ui;

};


#endif
