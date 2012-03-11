/******************************************************************************
	foregroundcolortoolundoaction.h
 ******************************************************************************/
#ifndef __FOREGROUNDCOLORTOOLUNDOACTION_H__
#define __FOREGROUNDTOOLUNDOACTION_H__

#include "toolundoaction.h"


//-----------------------------------------------------------------------------
//	Class Definition
//-----------------------------------------------------------------------------
class ForegroundColorToolUndoAction : public ToolUndoAction
{
public:
    ForegroundColorToolUndoAction(
        int x,
        int y,
        const QColor& colorFrom,
        const QColor& colorTo);
    void undo(Bitmap& bitmap);
    void redo(Bitmap& bitmap);

protected:
    int _x;
    int _y;
    QColor _colorFrom;
    QColor _colorTo;

};


#endif
