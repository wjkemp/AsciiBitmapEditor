/******************************************************************************
	drawingtoolundoaction.h
 ******************************************************************************/
#ifndef __DRAWINGTOOLUNDOACTION_H__
#define __DRAWINGTOOLUNDOACTION_H__

#include "toolundoaction.h"


//-----------------------------------------------------------------------------
//	Class Definition
//-----------------------------------------------------------------------------
class DrawingToolUndoAction : public ToolUndoAction
{
public:
    DrawingToolUndoAction(
        int x,
        int y,
        int characterFrom,
        const QColor& foregroundColorFrom,
        const QColor& backgroundColorFrom,
        int characterTo,
        const QColor& foregroundColorTo,
        const QColor& backgroundColorTo);
    void undo(Bitmap& bitmap);
    void redo(Bitmap& bitmap);

protected:
    int _x;
    int _y;
    int _characterFrom;
    QColor _foregroundColorFrom;
    QColor _backgroundColorFrom;
    int _characterTo;
    QColor _foregroundColorTo;
    QColor _backgroundColorTo;

};


#endif
