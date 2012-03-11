/******************************************************************************
	colortool.h
 ******************************************************************************/
#ifndef __COLORTOOL_H__
#define __COLORTOOL_H__

#include "tool.h"
#include <QToolBox>
#include <QSignalMapper>
#include <QToolButton>
#include <map>


//-----------------------------------------------------------------------------
//	Class Definition
//-----------------------------------------------------------------------------
class ColorTool : public Tool
{
    Q_OBJECT

public:
    ColorTool(const QString& name);
    ~ColorTool();
    QWidget* toolWidget();
    QColor selectedColor();

signals:
    void deselectToolButtons(bool checked);

protected slots:
    void selectToolButton(int index);

protected:
    QWidget* createColorPalette();

protected:
    QToolBox* _toolWidget;
    unsigned char _paletteIndex;
    QSignalMapper _paletteMap;
    std::map<int, QToolButton*> _toolButtons;
    std::map<int, QColor> _colors;

};


#endif
