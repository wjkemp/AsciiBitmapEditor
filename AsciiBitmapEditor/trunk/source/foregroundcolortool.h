/******************************************************************************
	foregroundcolortool.h
 ******************************************************************************/
#ifndef __FOREGROUNDCOLORTOOL_H__
#define __FOREGROUNDCOLORTOOL_H__

#include "colortool.h"


//-----------------------------------------------------------------------------
//	Class Definition
//-----------------------------------------------------------------------------
class ForegroundColorTool : public ColorTool
{

public:
    ForegroundColorTool();
    ~ForegroundColorTool();
    ToolUndoAction* doPrimaryFunction(Bitmap& bitmap, int x, int y);
    ToolUndoAction* doSecondaryFunction(Bitmap& bitmap, int x, int y);

};


#endif
