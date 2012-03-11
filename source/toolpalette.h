/******************************************************************************
	toolpalette.h
 ******************************************************************************/
#ifndef __TOOLPALETTE_H__
#define __TOOLPALETTE_H__

#include <QWidget>
#include <QSignalMapper>
#include <QToolButton>
#include <map>
#include "tool.h"



//-----------------------------------------------------------------------------
//	Class Definition
//-----------------------------------------------------------------------------
class ToolPalette : public QWidget
{
    Q_OBJECT

public:
	ToolPalette(QWidget* parent = 0);
	~ToolPalette();
    Tool* selectedTool();

signals:
    void deselectToolButtons(bool checked);

protected slots:
    void selectToolButton(int index);

protected:
    int _toolIndex;
    QSignalMapper _toolMap;
    std::map<int, QToolButton*> _toolButtons;
    std::map<int, Tool*> _tools;
   
};


#endif
