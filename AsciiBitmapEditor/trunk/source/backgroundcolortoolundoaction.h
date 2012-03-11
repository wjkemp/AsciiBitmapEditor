/******************************************************************************
	backgroundcolortoolundoaction.h
 ******************************************************************************/
#ifndef __BACKGROUNDCOLORTOOLUNDOACTION_H__
#define __BACKGROUNDTOOLUNDOACTION_H__

#include "toolundoaction.h"


//-----------------------------------------------------------------------------
//	Class Definition
//-----------------------------------------------------------------------------
class BackgroundColorToolUndoAction : public ToolUndoAction
{
public:
    BackgroundColorToolUndoAction(
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
