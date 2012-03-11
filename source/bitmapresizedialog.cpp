/******************************************************************************
	bitmapresizedialog.cpp
 ******************************************************************************/
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
