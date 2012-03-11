/******************************************************************************
	documentwrapper.h
 ******************************************************************************/
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
