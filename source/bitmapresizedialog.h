/******************************************************************************
	bitmapresizedialog.h
 ******************************************************************************/
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
