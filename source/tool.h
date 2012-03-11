/******************************************************************************
	tool.h
 ******************************************************************************/
#ifndef __TOOL_H__
#define __TOOL_H__

#include <QWidget>
#include "toolundoaction.h"


//-----------------------------------------------------------------------------
//	Class Definition
//-----------------------------------------------------------------------------
class Tool : public QObject
{
    Q_OBJECT

public:
    virtual QWidget* toolWidget() = 0;
    virtual ToolUndoAction* doPrimaryFunction(Bitmap& bitmap, int x, int y) = 0;
    virtual ToolUndoAction* doSecondaryFunction(Bitmap& bitmap, int x, int y) = 0;
};


#endif
