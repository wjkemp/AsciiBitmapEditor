/*  documentwrapper.h
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
#ifndef __DOCUMENTWRAPPER_H__
#define __DOCUMENTWRAPPER_H__

#include <QMdiSubWindow>
#include "bitmapeditor.h"


//-----------------------------------------------------------------------------
//	Class Definition
//-----------------------------------------------------------------------------
class DocumentWrapper : public QMdiSubWindow
{
    Q_OBJECT

public:
	DocumentWrapper(BitmapEditor* editor, QWidget* parent);
	DocumentWrapper(BitmapEditor* editor, QWidget* parent, const QString& path);
	~DocumentWrapper();
    bool saveDocument();
    bool saveDocumentAs();

protected slots:
    void setDirtyFlag(bool dirty);

protected:
    void updateWindowTitle();
    void closeEvent(QCloseEvent* event);

protected:
    BitmapEditor* _editor;
    QString _path;
    bool _dirty;

};


#endif
