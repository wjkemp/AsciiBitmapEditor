/******************************************************************************
	mainwindow.h
 ******************************************************************************/
#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

#include <QMainWindow>
#include <QStatusBar>
#include <QLabel>
#include "ui_mainwindow.h"
#include "toolpalette.h"


//-----------------------------------------------------------------------------
//	Class Definition
//-----------------------------------------------------------------------------
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
	MainWindow();
	~MainWindow();

protected slots:
    void onNewBitmap();
    void onOpenBitmap();
    void onSaveBitmap();
    void onSaveBitmapAs();
    void onResizeBitmap();
    void onExportBitmap();

    void onUpdateCursorPosition(int x, int y);

protected:
    Ui::MainWindow ui;
    ToolPalette* _toolPalette;
    QLabel* _cursorPosition;

};


#endif
