/******************************************************************************
	foregroundcolortoolundoaction.cpp
 ******************************************************************************/
#include "foregroundcolortoolundoaction.h"


//-----------------------------------------------------------------------------
ForegroundColorToolUndoAction::ForegroundColorToolUndoAction(
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
void ForegroundColorToolUndoAction::undo(Bitmap& bitmap)
{
    bitmap.setForegroundColorAt(_x, _y, _colorFrom);
}


//-----------------------------------------------------------------------------
void ForegroundColorToolUndoAction::redo(Bitmap& bitmap)
{
    bitmap.setForegroundColorAt(_x, _y, _colorTo);
}
