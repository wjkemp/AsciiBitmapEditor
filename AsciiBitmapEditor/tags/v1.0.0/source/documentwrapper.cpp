/*  documentwrapper.cpp
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
#include "documentwrapper.h"
#include "bitmapserializer.h"
#include <QFileDialog>
#include <QCloseEvent>
#include <QMessageBox>


//-----------------------------------------------------------------------------
DocumentWrapper::DocumentWrapper(BitmapEditor* editor, QWidget* parent) :
	QMdiSubWindow(parent),
    _editor(editor),
    _dirty(false)
{
    connect(_editor, SIGNAL(setDirtyFlag(bool)), SLOT(setDirtyFlag(bool)));
    updateWindowTitle();
}


//-----------------------------------------------------------------------------
DocumentWrapper::DocumentWrapper(BitmapEditor* editor, QWidget* parent, const QString& path) :
	QMdiSubWindow(parent),
    _editor(editor),
    _path(path),
    _dirty(false)
{
    BitmapSerializer serializer;
    Bitmap bitmap(serializer.read(path.toStdString()));
    _editor->setBitmap(bitmap);
    connect(_editor, SIGNAL(setDirtyFlag(bool)), SLOT(setDirtyFlag(bool)));
    updateWindowTitle();
}


//-----------------------------------------------------------------------------
DocumentWrapper::~DocumentWrapper()
{

}


//-----------------------------------------------------------------------------
bool DocumentWrapper::saveDocument()
{
    if (_path.isEmpty()) {
        QString filename = QFileDialog::getSaveFileName(
            this,
            "Save File",
            QString(),
            "Editor Files (*.meh)");

        if (!filename.isEmpty()) {
            _path = filename;
            BitmapSerializer serializer;
            serializer.write(_editor->bitmap(), _path.toStdString());
            _dirty = false;
            updateWindowTitle();
        }
        
    } else {
        BitmapSerializer serializer;
        serializer.write(_editor->bitmap(), _path.toStdString());
        _dirty = false;
        updateWindowTitle();
    }


    return false;
}


//-----------------------------------------------------------------------------
bool DocumentWrapper::saveDocumentAs()
{
    QString filename = QFileDialog::getSaveFileName(
        this,
        "Save File",
        QString(),
        "Editor Files (*.meh)");

    if (!filename.isEmpty()) {
        _path = filename;
        BitmapSerializer serializer;
        serializer.write(_editor->bitmap(), _path.toStdString());
        _dirty = false;
        updateWindowTitle();
    }

    return false;
}


//-----------------------------------------------------------------------------
void DocumentWrapper::setDirtyFlag(bool dirty)
{
    _dirty = dirty;
    updateWindowTitle();
}


//-----------------------------------------------------------------------------
void DocumentWrapper::updateWindowTitle()
{
    if (_path.isEmpty()) {
        if (_dirty) {
            setWindowTitle("Untitled *");
        } else {
            setWindowTitle("Untitled");
        }

    } else {
        QString title(_path);
        if (_dirty) {
            title += " *";
        }
        setWindowTitle(title);
    }    
}


//-----------------------------------------------------------------------------
void DocumentWrapper::closeEvent(QCloseEvent* event)
{
    if (_dirty) {

        QMessageBox::StandardButton result(QMessageBox::question(this, "Save", "Do you want to save changes?", QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel, QMessageBox::Yes));
        switch (result) {

            case QMessageBox::Yes: {

                if (_path.isEmpty()) {
                    QString filename = QFileDialog::getSaveFileName(
                        this,
                        "Save File",
                        QString(),
                        "Editor Files (*.meh)");

                    if (!filename.isEmpty()) {
                        _path = filename;
                        BitmapSerializer serializer;
                        serializer.write(_editor->bitmap(), _path.toStdString());
                        _dirty = false;
                        updateWindowTitle();
                    }

                } else {
                    BitmapSerializer serializer;
                    serializer.write(_editor->bitmap(), _path.toStdString());
                    _dirty = false;
                    updateWindowTitle();
                }
            } break;

            case QMessageBox::No: {

            } break;

            case QMessageBox::Cancel: {
                event->ignore();
            } break;
        }

    }

}
