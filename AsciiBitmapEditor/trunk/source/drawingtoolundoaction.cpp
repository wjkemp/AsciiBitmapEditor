/******************************************************************************
	drawingtoolundoaction.cpp
 ******************************************************************************/
#include "drawingtoolundoaction.h"


//-----------------------------------------------------------------------------
DrawingToolUndoAction::DrawingToolUndoAction(
    int x,
    int y,
    int characterFrom,
    const QColor& foregroundColorFrom,
    const QColor& backgroundColorFrom,
    int characterTo,
    const QColor& foregroundColorTo,
    const QColor& backgroundColorTo) :
    _x(x),
    _y(y),
    _characterFrom(characterFrom),
    _foregroundColorFrom(foregroundColorFrom),
    _backgroundColorFrom(backgroundColorFrom),
    _characterTo(characterTo),
    _foregroundColorTo(foregroundColorTo),
    _backgroundColorTo(backgroundColorTo)
{

}


//-----------------------------------------------------------------------------
void DrawingToolUndoAction::undo(Bitmap& bitmap)
{
    bitmap.setCharacterAt(_x, _y, _characterFrom);
    bitmap.setForegroundColorAt(_x, _y, _foregroundColorFrom);
    bitmap.setBackgroundColorAt(_x, _y, _backgroundColorFrom);
}


//-----------------------------------------------------------------------------
void DrawingToolUndoAction::redo(Bitmap& bitmap)
{
    bitmap.setCharacterAt(_x, _y, _characterTo);
    bitmap.setForegroundColorAt(_x, _y, _foregroundColorTo);
    bitmap.setBackgroundColorAt(_x, _y, _backgroundColorTo);
}
