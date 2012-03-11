/******************************************************************************
	backroundcolortoolundoaction.cpp
 ******************************************************************************/
#include "backgroundcolortoolundoaction.h"


//-----------------------------------------------------------------------------
BackgroundColorToolUndoAction::BackgroundColorToolUndoAction(
    int x,
    int y,
    const QColor& colorFrom,
    const QColor& colorTo) :
    _x(x),
    _y(y),
    _colorFrom(colorFrom),
    _colorTo(colorTo)
{

}


//-----------------------------------------------------------------------------
void BackgroundColorToolUndoAction::undo(Bitmap& bitmap)
{
    bitmap.setBackgroundColorAt(_x, _y, _colorFrom);
}


//-----------------------------------------------------------------------------
void BackgroundColorToolUndoAction::redo(Bitmap& bitmap)
{
    bitmap.setBackgroundColorAt(_x, _y, _colorTo);
}
