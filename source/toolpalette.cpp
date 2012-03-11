/******************************************************************************
	toolpalette.cpp
 ******************************************************************************/
#include "toolpalette.h"
#include <QVBoxLayout>
#include "drawingtool.h"
#include "foregroundcolortool.h"
#include "backgroundcolortool.h"


//-----------------------------------------------------------------------------
ToolPalette::ToolPalette(QWidget* parent) :
	QWidget(parent),
    _toolIndex(0)
{   

    setObjectName("toolContainer");

    ForegroundColorTool* foregroundColorTool = new ForegroundColorTool();
    BackgroundColorTool* backgroundColorTool = new BackgroundColorTool();
    DrawingTool* drawingTool = new DrawingTool(foregroundColorTool, backgroundColorTool);


    // Drawing tool button
    QWidget* widget = new QWidget();
    widget->setObjectName("toolContainer");

    QHBoxLayout* hbox = new QHBoxLayout();    
    QVBoxLayout* vbox = new QVBoxLayout();
    hbox->setSpacing(0);
    vbox->setMargin(0);

    QToolButton* toolButton = new QToolButton();
    toolButton->setIcon(QIcon(":/icons/edit.png"));
    toolButton->setCheckable(true);
    toolButton->setToolButtonStyle(Qt::ToolButtonTextOnly);
    toolButton->setAutoRaise(true);
    toolButton->setMinimumWidth(30);
    toolButton->setMinimumHeight(30);
    connect(toolButton, SIGNAL(clicked()), &_toolMap, SLOT(map()));
    connect(this, SIGNAL(deselectToolButtons(bool)), toolButton, SLOT(setChecked(bool)));
    _toolButtons[0] = toolButton;
    _tools[0] = drawingTool;
    _toolMap.setMapping(toolButton, 0);
    hbox->addWidget(toolButton);

    // Foreground Color Tool Button
    toolButton = new QToolButton();
    toolButton->setIcon(QIcon(":/icons/foregroundcolor.png"));
    toolButton->setCheckable(true);
    toolButton->setToolButtonStyle(Qt::ToolButtonTextOnly);
    toolButton->setAutoRaise(true);
    toolButton->setMinimumWidth(30);
    toolButton->setMinimumHeight(30);
    connect(toolButton, SIGNAL(clicked()), &_toolMap, SLOT(map()));
    connect(this, SIGNAL(deselectToolButtons(bool)), toolButton, SLOT(setChecked(bool)));
    _toolButtons[1] = toolButton;
    _tools[1] = foregroundColorTool;
    _toolMap.setMapping(toolButton, 1);
    hbox->addWidget(toolButton);


    // Background Color Tool Button
    toolButton = new QToolButton();
    toolButton->setIcon(QIcon(":/icons/backgroundcolor.png"));
    toolButton->setCheckable(true);
    toolButton->setToolButtonStyle(Qt::ToolButtonTextOnly);
    toolButton->setAutoRaise(true);
    toolButton->setMinimumWidth(30);
    toolButton->setMinimumHeight(30);
    connect(toolButton, SIGNAL(clicked()), &_toolMap, SLOT(map()));
    connect(this, SIGNAL(deselectToolButtons(bool)), toolButton, SLOT(setChecked(bool)));
    _toolButtons[2] = toolButton;
    _tools[2] = backgroundColorTool;
    _toolMap.setMapping(toolButton, 2);
    hbox->addWidget(toolButton);

    hbox->addStretch();
    vbox->addItem(hbox);
    vbox->addStretch();
    widget->setLayout(vbox);



    QVBoxLayout* layout = new QVBoxLayout();
    layout->setMargin(0);
    QToolBox* toolBox = new QToolBox();
    toolBox->setMaximumHeight(80);
    toolBox->addItem(widget, "Tools");

    layout->addWidget(toolBox);
    layout->addWidget(drawingTool->toolWidget());
    layout->addWidget(foregroundColorTool->toolWidget());
    layout->addWidget(backgroundColorTool->toolWidget());
    layout->addStretch();
    setLayout(layout);

    connect(&_toolMap, SIGNAL(mapped(int)), SLOT(selectToolButton(int)));
    _toolButtons[0]->setChecked(true);
}


//-----------------------------------------------------------------------------
ToolPalette::~ToolPalette()
{

}


//-----------------------------------------------------------------------------
Tool* ToolPalette::selectedTool()
{
    return _tools[_toolIndex];
}


//-----------------------------------------------------------------------------
void ToolPalette::selectToolButton(int index)
{
    _toolIndex = index;
    deselectToolButtons(false);
    _toolButtons[index]->setChecked(true);
}

