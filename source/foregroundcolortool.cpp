/******************************************************************************
	foregroundcolortool.cpp
 ******************************************************************************/
#include "foregroundcolortool.h"
#include "foregroundcolortoolundoaction.h"


//-----------------------------------------------------------------------------
ForegroundColorTool::ForegroundColorTool() :
    ColorTool("Foreground Colors")
{
    // Select a default
    _paletteIndex = 7;
    _toolButtons[7]->setChecked(true);
}


//-----------------------------------------------------------------------------
ForegroundColorTool::~ForegroundColorTool()
{

}


//-----------------------------------------------------------------------------
ToolUndoAction* ForegroundColorTool::doPrimaryFunction(Bitmap& bitmap, int x, int y)
{
    ToolUndoAction* undoAction = 0;
    QColor colorFrom(bitmap.foregroundColorAt(x, y));
    QColor colorTo(selectedColor());
    if (colorFrom != colorTo) {
        bitmap.setForegroundColorAt(x, y, selectedColor());
        undoAction = new ForegroundColorToolUndoAction(x, y, colorFrom, colorTo);
    }

    return undoAction;
}


//-----------------------------------------------------------------------------
ToolUndoAction* ForegroundColorTool::doSecondaryFunction(Bitmap& bitmap, int x, int y)
{
    return 0;
}

