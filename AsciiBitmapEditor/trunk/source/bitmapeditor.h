/******************************************************************************
	bitmapeditor.h
 ******************************************************************************/
#ifndef __BITMAPEDITOR_H__
#define __BITMAPEDITOR_H__

#include <QWidget>
#include "bitmap.h"
#include "toolpalette.h"
#include "toolundoaction.h"


//-----------------------------------------------------------------------------
//	Class Definition
//-----------------------------------------------------------------------------
class BitmapEditor : public QWidget
{
    Q_OBJECT

public:
	BitmapEditor(ToolPalette* toolPalette, QWidget* parent = 0);
	BitmapEditor(ToolPalette* toolPalette, const Bitmap& bitmap, QWidget* parent = 0);
	~BitmapEditor();
    void setBitmap(const Bitmap& bitmap) { _bitmap = bitmap; }
    Bitmap bitmap() const { return _bitmap; }
    void resizeBitmap(int width, int height);

signals:
    void setDirtyFlag(bool dirty);
    void updateCursorPosition(int x, int y);

protected:
    void undo();
    void redo();
    void clearRedoStack();

    void paintEvent(QPaintEvent* event);
    void keyPressEvent(QKeyEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

private:
    bool surfaceContains(const QPoint& point) const;
    QPoint translateWindowToSurface(const QPoint& point) const;
    QRect translateWindowToSurface(const QRect& rect) const;
    QPoint translateSurfaceToWindow(const QPoint& point) const;
    QRect translateSurfaceToWindow(const QRect& rect) const;

private:
    Bitmap _bitmap;
    ToolPalette* _toolPalette;
    int _gridWidth;
    int _gridHeight;
    std::list<ToolUndoAction*> _undoStack;
    std::list<ToolUndoAction*> _redoStack;



};


#endif
