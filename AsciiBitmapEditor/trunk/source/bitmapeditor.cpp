/*  bitmapeditor.cpp
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
#include "bitmapeditor.h"
#include <QPainter>
#include <QFont>
#include <QMouseEvent>
#include <QKeyEvent>



//-----------------------------------------------------------------------------
BitmapEditor::BitmapEditor(ToolPalette* toolPalette, QWidget* parent) :
	QWidget(parent),
    _toolPalette(toolPalette),
    _gridWidth(12),
    _gridHeight(18)

{    
    QPalette p(palette());
    p.setColor(QPalette::Background, Qt::black);
    setPalette(p);
    setAutoFillBackground(true);
    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);
}


//-----------------------------------------------------------------------------
BitmapEditor::BitmapEditor(ToolPalette* toolPalette, const Bitmap& bitmap, QWidget* parent) :
    _toolPalette(toolPalette),
    _bitmap(bitmap),
    _gridWidth(12),
    _gridHeight(18)
{
    QPalette p(palette());
    p.setColor(QPalette::Background, Qt::black);
    setPalette(p);
    setAutoFillBackground(true);
    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);
}


//-----------------------------------------------------------------------------
BitmapEditor::~BitmapEditor()
{

}


//-----------------------------------------------------------------------------
void BitmapEditor::resizeBitmap(int width, int height)
{
    _bitmap = Bitmap(width, height);
    repaint();
}


//-----------------------------------------------------------------------------
void BitmapEditor::undo()
{
    if (_undoStack.size()) {
        ToolUndoAction* undoAction = _undoStack.back();
        _undoStack.pop_back();
        undoAction->undo(_bitmap);
        _redoStack.push_back(undoAction);
        setDirtyFlag(true);
        repaint();
    }
}


//-----------------------------------------------------------------------------
void BitmapEditor::redo()
{
    if (_redoStack.size()) {
        ToolUndoAction* undoAction = _redoStack.back();
        _redoStack.pop_back();
        undoAction->redo(_bitmap);
        _undoStack.push_back(undoAction);
        setDirtyFlag(true);
        repaint();
    }
}


//-----------------------------------------------------------------------------
void BitmapEditor::clearRedoStack()
{
    while(_redoStack.size()) {
        ToolUndoAction* undoAction = _redoStack.back();
        _redoStack.pop_back();
        delete undoAction;
    }

}


//-----------------------------------------------------------------------------
void BitmapEditor::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    QFont font("Terminal", 10);
    painter.setFont(font);

    QPen pen;
    pen.setStyle(Qt::DotLine);
    pen.setWidth(1);
    pen.setColor(QColor(80, 80, 90));
    painter.setPen(pen);


    QRect boundary(0, 0, _gridWidth * _bitmap.width(), _gridHeight * _bitmap.height());
    painter.drawRect(translateSurfaceToWindow(boundary));

    
    for (int i = 0; i < _bitmap.width() - 1; ++i) {

        painter.drawLine(
            translateSurfaceToWindow(QPoint((i + 1) * _gridWidth, boundary.top())), 
            translateSurfaceToWindow(QPoint((i + 1) * _gridWidth, boundary.bottom())));
    }   
    
    for (int i = 0; i < _bitmap.height() - 1; ++i) {
        painter.drawLine(
            translateSurfaceToWindow(QPoint(boundary.left(), (i + 1) * _gridHeight)), 
            translateSurfaceToWindow(QPoint(boundary.right(), (i + 1) * _gridHeight)));
    }
    

    for (int w = 0; w < _bitmap.width(); ++w) {
        for (int h = 0; h < _bitmap.height(); ++h) {
            QRect charRect(
                translateSurfaceToWindow(QRect((w * _gridWidth) + 1, (h * _gridHeight) + 1, _gridWidth - 2, _gridHeight - 2)));

            QColor backgroundColor(_bitmap.backgroundColorAt(w, h));
            painter.fillRect(charRect, backgroundColor);

            QString text;
            text += _bitmap.characterAt(w, h);

            QColor foregroundColor(_bitmap.foregroundColorAt(w, h));

            if (_bitmap.characterAt(w,h)) {
                pen.setColor(foregroundColor);
                painter.setPen(pen);
                painter.drawText(charRect, Qt::AlignCenter, text);
            }
        }
    }
    

}


//-----------------------------------------------------------------------------
void BitmapEditor::keyPressEvent(QKeyEvent* event)
{
    if ((event->key() == Qt::Key_Z) && (event->modifiers() == Qt::ControlModifier)) {
        undo();
        event->accept();
    }

    if ((event->key() == Qt::Key_Y) && (event->modifiers() == Qt::ControlModifier)) {
        redo();
        event->accept();
    }
}



//-----------------------------------------------------------------------------
void BitmapEditor::mousePressEvent(QMouseEvent* event)
{
    QWidget::mousePressEvent(event);

    QPoint pos(translateWindowToSurface(event->pos()));

    int w = (pos.x() / _gridWidth);
    int h = (pos.y() / _gridHeight);

    if (surfaceContains(pos)) {

        if (event->buttons() & Qt::LeftButton) {
            Tool* tool = _toolPalette->selectedTool();
            ToolUndoAction* undoAction = tool->doPrimaryFunction(_bitmap, w, h);
            if (undoAction) {
                _undoStack.push_back(undoAction);
                clearRedoStack();
                setDirtyFlag(true);
            }

            repaint();
        }

        if (event->buttons() & Qt::RightButton) {
            Tool* tool = _toolPalette->selectedTool();
            ToolUndoAction* undoAction = tool->doSecondaryFunction(_bitmap, w, h);
            if (undoAction) {
                _undoStack.push_back(undoAction);
                clearRedoStack();
                setDirtyFlag(true);
            }

            repaint();
        }

    }
}


//-----------------------------------------------------------------------------
void BitmapEditor::mouseMoveEvent(QMouseEvent* event)
{
    QWidget::mouseMoveEvent(event);

    QPoint pos(translateWindowToSurface(event->pos()));

    if (surfaceContains(pos)) {

        int w = (pos.x() / _gridWidth);
        int h = (pos.y() / _gridHeight);

        if (event->buttons() & Qt::LeftButton) {

            Tool* tool = _toolPalette->selectedTool();
            ToolUndoAction* undoAction = tool->doPrimaryFunction(_bitmap, w, h);
            if (undoAction) {
                _undoStack.push_back(undoAction);
                clearRedoStack();
                setDirtyFlag(true);
            }

            repaint();
        }

        if (event->buttons() & Qt::RightButton) {

            Tool* tool = _toolPalette->selectedTool();
            ToolUndoAction* undoAction = tool->doSecondaryFunction(_bitmap, w, h);
            if (undoAction) {
                _undoStack.push_back(undoAction);
                clearRedoStack();
                setDirtyFlag(true);
            }

            repaint();
        }


        emit updateCursorPosition(w, h);
    }
}


//-----------------------------------------------------------------------------
QSize BitmapEditor::sizeHint() const
{
    return QSize((_bitmap.width() + 2) * _gridWidth, (_bitmap.height() + 2) * _gridHeight);
}


//-----------------------------------------------------------------------------
QSize BitmapEditor::minimumSizeHint() const
{
    return QSize((_bitmap.width() + 2) * _gridWidth, (_bitmap.height() + 2) * _gridHeight);
}


//-----------------------------------------------------------------------------
bool BitmapEditor::surfaceContains(const QPoint& point) const
{
    QRect rect(0, 0, _bitmap.width() * _gridWidth, _bitmap.height() * _gridHeight);
    return rect.contains(point);
}


//-----------------------------------------------------------------------------
QPoint BitmapEditor::translateWindowToSurface(const QPoint& point) const
{
    return QPoint(point.x() - _gridWidth, point.y() - _gridHeight);
}


//-----------------------------------------------------------------------------
QRect BitmapEditor::translateWindowToSurface(const QRect& rect) const
{
    return QRect(rect.left() - _gridWidth, rect.top() - _gridHeight, rect.width(), rect.height());
}


//-----------------------------------------------------------------------------
QPoint BitmapEditor::translateSurfaceToWindow(const QPoint& point) const
{
    return QPoint(point.x() + _gridWidth, point.y() + _gridHeight);
}


//-----------------------------------------------------------------------------
QRect BitmapEditor::translateSurfaceToWindow(const QRect& rect) const
{
    return QRect(rect.left() + _gridWidth, rect.top() + _gridHeight, rect.width(), rect.height());
}
