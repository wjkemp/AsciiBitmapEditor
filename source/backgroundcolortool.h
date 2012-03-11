/******************************************************************************
	backgroundcolortool.h
 ******************************************************************************/
#ifndef __BACKGROUNDCOLORTOOL_H__
#define __BACKGROUNDCOLORTOOL_H__

#include "colortool.h"


//-----------------------------------------------------------------------------
//	Class Definition
//-----------------------------------------------------------------------------
class BackgroundColorTool : public ColorTool
{

public:
    BackgroundColorTool();
    ~BackgroundColorTool();
    ToolUndoAction* doPrimaryFunction(Bitmap& bitmap, int x, int y);
    ToolUndoAction* doSecondaryFunction(Bitmap& bitmap, int x, int y);

};


#endif
