/******************************************************************************
	mainwindow.cpp
 ******************************************************************************/
#include "mainwindow.h"
#include "bitmapeditor.h"
#include "bitmapresizedialog.h"
#include "bitmapexporter.h"
#include "bitmapserializer.h"
#include "documentwrapper.h"
#include <QDockWidget>
#include <QMdiSubWindow>
#include <QFileDialog>


//-----------------------------------------------------------------------------
MainWindow::MainWindow() :
	QMainWindow()
{
    ui.setupUi(this);

    _toolPalette = new ToolPalette();
    QDockWidget* dockWidget = new QDockWidget("Tools");
    dockWidget->setWidget(_toolPalette);
    addDockWidget(Qt::RightDockWidgetArea, dockWidget);

    connect(ui.actNewBitmap, SIGNAL(activated()), SLOT(onNewBitmap()));
    connect(ui.actOpenBitmap, SIGNAL(activated()), SLOT(onOpenBitmap()));
    connect(ui.actSaveBitmap, SIGNAL(activated()), SLOT(onSaveBitmap()));
    connect(ui.actSaveBitmapAs, SIGNAL(activated()), SLOT(onSaveBitmapAs()));
    connect(ui.actResizeBitmap, SIGNAL(activated()), SLOT(onResizeBitmap()));
    connect(ui.actExport, SIGNAL(activated()), SLOT(onExportBitmap()));

    _cursorPosition = new QLabel();
    ui.statusbar->addPermanentWidget(_cursorPosition);
}


//-----------------------------------------------------------------------------
MainWindow::~MainWindow()
{

}



//-----------------------------------------------------------------------------
void MainWindow::onNewBitmap()
{
    BitmapResizeDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        BitmapEditor* editor = new BitmapEditor(_toolPalette, Bitmap(dialog.width(), dialog.height()));
        connect(editor, SIGNAL(updateCursorPosition(int, int)), SLOT(onUpdateCursorPosition(int, int)));
        DocumentWrapper* documentWrapper = new DocumentWrapper(editor, ui.mdiArea);
        documentWrapper->setWidget(editor);
        editor->show();
    }
}


//-----------------------------------------------------------------------------
void MainWindow::onOpenBitmap()
{
    QString filename = QFileDialog::getOpenFileName(
        this,
        "Open File",
        QString(),
        "Editor Files (*.meh)");

    if (!filename.isEmpty()) {

        BitmapEditor* editor = new BitmapEditor(_toolPalette);
        connect(editor, SIGNAL(updateCursorPosition(int, int)), SLOT(onUpdateCursorPosition(int, int)));
        DocumentWrapper* documentWrapper = new DocumentWrapper(editor, ui.mdiArea, filename);
        documentWrapper->setWidget(editor);
        editor->show();
    }
}


//-----------------------------------------------------------------------------
void MainWindow::onSaveBitmap()
{
    QMdiSubWindow* subWindow = ui.mdiArea->currentSubWindow();
    if (subWindow) {
        DocumentWrapper* wrapper = (DocumentWrapper*)subWindow;
        wrapper->saveDocument();
    }
}


//-----------------------------------------------------------------------------
void MainWindow::onSaveBitmapAs()
{
    QMdiSubWindow* subWindow = ui.mdiArea->currentSubWindow();
    if (subWindow) {
        DocumentWrapper* wrapper = (DocumentWrapper*)subWindow;
        wrapper->saveDocumentAs();
    }
}


//-----------------------------------------------------------------------------
void MainWindow::onExportBitmap()
{
    QMdiSubWindow* subWindow = ui.mdiArea->currentSubWindow();
    if (subWindow) {

        QString filename = QFileDialog::getSaveFileName(
            this,
            "Export File",
            QString(),
            "Text Files (*.txt)");

        if (!filename.isEmpty()) {

            BitmapEditor* bitmapEditor = (BitmapEditor*)subWindow->widget();
            BitmapExporter exporter;
            exporter.write(bitmapEditor->bitmap(), filename.toStdString());
        }
    }
}


//-----------------------------------------------------------------------------
void MainWindow::onResizeBitmap()
{
    QMdiSubWindow* subWindow = ui.mdiArea->currentSubWindow();
    if (subWindow) {
        BitmapEditor* bitmapEditor = (BitmapEditor*)subWindow->widget();
        BitmapResizeDialog dialog(this);
        if (dialog.exec() == QDialog::Accepted) {
            bitmapEditor->resizeBitmap(dialog.width(), dialog.height());
        }
    }
}


//-----------------------------------------------------------------------------
void MainWindow::onUpdateCursorPosition(int x, int y)
{
    QString text = QString("%1, %2").arg(x).arg(y);
    _cursorPosition->setText(text);

}
