/******************************************************************************
	backgroundcolortool.cpp
 ******************************************************************************/
#include "backgroundcolortool.h"
#include "backgroundcolortoolundoaction.h"


//-----------------------------------------------------------------------------
BackgroundColorTool::BackgroundColorTool() :
    ColorTool("Background Colors")
{
    // Select a default
    _paletteIndex = 0;
    _toolButtons[0]->setChecked(true);
}


//-----------------------------------------------------------------------------
BackgroundColorTool::~BackgroundColorTool()
{

}


//-----------------------------------------------------------------------------
ToolUndoAction* BackgroundColorTool::doPrimaryFunction(Bitmap& bitmap, int x, int y)
{
    ToolUndoAction* undoAction = 0;
    QColor colorFrom(bitmap.backgroundColorAt(x, y));
    QColor colorTo(selectedColor());
    if (colorFrom != colorTo) {
        bitmap.setBackgroundColorAt(x, y, selectedColor());
        undoAction = new BackgroundColorToolUndoAction(x, y, colorFrom, colorTo);
    }

    return undoAction;
}


//-----------------------------------------------------------------------------
ToolUndoAction* BackgroundColorTool::doSecondaryFunction(Bitmap& bitmap, int x, int y)
{
    return 0;
}

