/******************************************************************************
	documentwrapper.cpp
 ******************************************************************************/
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
