/******************************************************************************
	drawingtool.h
 ******************************************************************************/
#ifndef __DRAWINGTOOL_H__
#define __DRAWINGTOOL_H__

#include "tool.h"
#include <QToolBox>
#include <QSignalMapper>
#include <QToolButton>
#include <map>
#include "colortool.h"


//-----------------------------------------------------------------------------
//	Class Definition
//-----------------------------------------------------------------------------
class DrawingTool : public Tool
{
    Q_OBJECT

public:
    DrawingTool(ColorTool* foregroundColorTool, ColorTool* backgroundColorTool);
    ~DrawingTool();
    QWidget* toolWidget();
    ToolUndoAction* doPrimaryFunction(Bitmap& bitmap, int x, int y);
    ToolUndoAction* doSecondaryFunction(Bitmap& bitmap, int x, int y);

signals:
    void deselectCharacterTools(bool checked);

protected slots:
    void selectCharacterTool(int index);


protected:
    QWidget* createAlphanumericPalette();
    QWidget* createLinePalette();
    QWidget* createSymbolPalette();

protected:
    QToolBox* _toolWidget;
    ColorTool* _foregroundColorTool;
    ColorTool* _backgroundColorTool;
    unsigned char _characterIndex;
    QSignalMapper _characterMap;
    std::map<int, QToolButton*> _characterButtons;

};


#endif
