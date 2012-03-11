/******************************************************************************
	colortool.cpp
 ******************************************************************************/
#include "colortool.h"
#include <QGridLayout>
#include <QVBoxLayout>


//-----------------------------------------------------------------------------
ColorTool::ColorTool(const QString& name) :
    _paletteIndex(0)
{
    _toolWidget = new QToolBox();
    _toolWidget->addItem(createColorPalette(), name);   
    connect(&_paletteMap, SIGNAL(mapped(int)), SLOT(selectToolButton(int)));

}


//-----------------------------------------------------------------------------
ColorTool::~ColorTool()
{

}


//-----------------------------------------------------------------------------
QWidget* ColorTool::toolWidget()
{
    return _toolWidget;
}


//-----------------------------------------------------------------------------
QColor ColorTool::selectedColor()
{
    return _colors[(int)_paletteIndex];
}


//-----------------------------------------------------------------------------
void ColorTool::selectToolButton(int index)
{
    _paletteIndex = index;
    deselectToolButtons(false);
    _toolButtons[index]->setChecked(true);
}


//-----------------------------------------------------------------------------
QWidget* ColorTool::createColorPalette()
{
    QWidget* widget = new QWidget();
    widget->setObjectName("toolContainer");

    const int colorCount = 16;


    // Add foreground colors to the map
    _colors[0]  = QColor(0x00, 0x00, 0x00);
    _colors[1]  = QColor(0x7F, 0x00, 0x00);
    _colors[2]  = QColor(0x00, 0x7F, 0x00);
    _colors[3]  = QColor(0x00, 0x00, 0x7F);
    _colors[4]  = QColor(0x7F, 0x7F, 0x00);
    _colors[5]  = QColor(0x00, 0x7F, 0x7F);
    _colors[6]  = QColor(0x7F, 0x00, 0x7F);
    _colors[7]  = QColor(0x7F, 0x7F, 0x7F);

    _colors[8]  = QColor(0x00, 0x00, 0x00);
    _colors[9]  = QColor(0xFF, 0x00, 0x00);
    _colors[10] = QColor(0x00, 0xFF, 0x00);
    _colors[11] = QColor(0x00, 0x00, 0xFF);
    _colors[12] = QColor(0xFF, 0xFF, 0x00);
    _colors[13] = QColor(0x00, 0xFF, 0xFF);
    _colors[14] = QColor(0xFF, 0x00, 0xFF);
    _colors[15] = QColor(0xfF, 0xFF, 0xFF);


    QGridLayout* gridLayout = new QGridLayout();
    QVBoxLayout* layout = new QVBoxLayout();
    gridLayout->setSpacing(6);

    int x = 0;
    int y = 0;

    for (int i=0; i < colorCount; ++i) {
        QToolButton* toolButton = new QToolButton();
        toolButton->setStyleSheet(QString("background: rgb(%1, %2, %3)").arg(_colors[i].red()).arg(_colors[i].green()).arg(_colors[i].blue()));
        toolButton->setCheckable(true);
        toolButton->setToolButtonStyle(Qt::ToolButtonTextOnly);
        toolButton->setMinimumWidth(30);
        toolButton->setMinimumHeight(30);
        connect(toolButton, SIGNAL(clicked()), &_paletteMap, SLOT(map()));
        connect(this, SIGNAL(deselectToolButtons(bool)), toolButton, SLOT(setChecked(bool)));
        _toolButtons[i] = toolButton;
        _paletteMap.setMapping(toolButton, i);
        gridLayout->addWidget(toolButton, y, x);
        x++;
        if (x == 4) {
            x = 0;
            y++;
        }
    }

    layout->addItem(gridLayout);
    layout->addStretch();
    widget->setLayout(layout);
    return widget;    
}
