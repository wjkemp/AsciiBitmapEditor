/******************************************************************************
	toolundoaction.h
 ******************************************************************************/
#ifndef __TOOLUNDOACTION_H__
#define __TOOLUNDOACTION_H__

#include "bitmap.h"


//-----------------------------------------------------------------------------
//	Class Definition
//-----------------------------------------------------------------------------
class ToolUndoAction
{
public:
    virtual void undo(Bitmap& bitmap) = 0;
    virtual void redo(Bitmap& bitmap) = 0;

};


#endif
