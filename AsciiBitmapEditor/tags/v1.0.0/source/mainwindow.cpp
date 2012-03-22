/*  mainwindow.cpp
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
#include "mainwindow.h"
#include "bitmapeditor.h"
#include "bitmapresizedialog.h"
#include "bitmapexporter.h"
#include "bitmapserializer.h"
#include "documentwrapper.h"
#include "version.h"
#include <QDockWidget>
#include <QMdiSubWindow>
#include <QFileDialog>
#include <QMessageBox>


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
    connect(ui.actHelpAbout, SIGNAL(activated()), SLOT(onHelpAbout()));

    _cursorPosition = new QLabel();
    ui.statusbar->addPermanentWidget(_cursorPosition);


    setWindowTitle(
        QString("AsciiBitmapEditor [AsciiBitmapEditor ver %1.%2.%3]")
        .arg(ASCIIBITMAPEDITOR_VERSION_MAJOR)
        .arg(ASCIIBITMAPEDITOR_VERSION_MINOR)
        .arg(ASCIIBITMAPEDITOR_VERSION_BUILD));
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
void MainWindow::onHelpAbout()
{
    QMessageBox::about(this, "About Ascii Bitmap Editor",
        "Copyright (C) 2012 Willem Kemp  <http://www.thenocturnaltree.com/>.\n"
        "All rights reserved.\n\n"

        "AsciiBitmapEditor is free software: you can redistribute it and/or modify\n"
        "it under the terms of the GNU General Public License as published by\n"
        "the Free Software Foundation, either version 3 of the License, or\n"
        "(at your option) any later version.\n\n"

        "AsciiBitmapEditor is distributed in the hope that it will be useful,\n"
        "but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
        "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the\n"
        "GNU General Public License for more details.\n\n"

        "You should have received a copy of the GNU General Public License\n"
        "along with AsciiBitmapEditor. If not, see http://www.gnu.org/licenses/.");
}


//-----------------------------------------------------------------------------
void MainWindow::onUpdateCursorPosition(int x, int y)
{
    QString text = QString("%1, %2").arg(x).arg(y);
    _cursorPosition->setText(text);

}
