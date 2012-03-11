/******************************************************************************
	drawingtool.cpp
 ******************************************************************************/
#include "drawingtool.h"
#include "drawingtoolundoaction.h"
#include <QGridLayout>


//-----------------------------------------------------------------------------
DrawingTool::DrawingTool(ColorTool* foregroundColorTool, ColorTool* backgroundColorTool) :
    _characterIndex(0),
    _foregroundColorTool(foregroundColorTool),
    _backgroundColorTool(backgroundColorTool)
{
    _toolWidget = new QToolBox();
    _toolWidget->addItem(createAlphanumericPalette(), "Alphanumeric");
    _toolWidget->addItem(createLinePalette(), "Lines");
    _toolWidget->addItem(createSymbolPalette(), "Symbols");
        
    connect(&_characterMap, SIGNAL(mapped(int)), SLOT(selectCharacterTool(int)));

}


//-----------------------------------------------------------------------------
DrawingTool::~DrawingTool()
{

}


//-----------------------------------------------------------------------------
QWidget* DrawingTool::toolWidget()
{
    return _toolWidget;
}


//-----------------------------------------------------------------------------
ToolUndoAction* DrawingTool::doPrimaryFunction(Bitmap& bitmap, int x, int y)
{
    ToolUndoAction* undoAction = 0;
    unsigned char currentCharacter = bitmap.characterAt(x, y);
    QColor currentForegroundColor(bitmap.foregroundColorAt(x, y));
    QColor currentBackgroundColor(bitmap.backgroundColorAt(x, y));

    if ((currentCharacter != _characterIndex) || 
        (currentForegroundColor != _foregroundColorTool->selectedColor()) ||
        (currentBackgroundColor != _backgroundColorTool->selectedColor())) {

        undoAction = new DrawingToolUndoAction(
            x,
            y,
            currentCharacter,
            currentForegroundColor,
            currentBackgroundColor,
            _characterIndex,
            _foregroundColorTool->selectedColor(),
            _backgroundColorTool->selectedColor()
            );

        bitmap.setCharacterAt(x, y, _characterIndex);
        bitmap.setForegroundColorAt(x, y, _foregroundColorTool->selectedColor());
        bitmap.setBackgroundColorAt(x, y, _backgroundColorTool->selectedColor());
    }
    return undoAction;
}


//-----------------------------------------------------------------------------
ToolUndoAction* DrawingTool::doSecondaryFunction(Bitmap& bitmap, int x, int y)
{
    ToolUndoAction* undoAction = 0;
    unsigned char currentCharacter = bitmap.characterAt(x, y);
    QColor currentForegroundColor(bitmap.foregroundColorAt(x, y));
    QColor currentBackgroundColor(bitmap.backgroundColorAt(x, y));

    if (currentCharacter != 0) {

        undoAction = new DrawingToolUndoAction(
            x,
            y,
            currentCharacter,
            currentForegroundColor,
            currentBackgroundColor,
            0,
            QColor(0, 0, 0),
            QColor(0, 0, 0)
            );

        bitmap.setCharacterAt(x, y, 0);
        bitmap.setForegroundColorAt(x, y, QColor(0, 0, 0));
        bitmap.setBackgroundColorAt(x, y, QColor(0, 0, 0));
    }

    return undoAction;
}



//-----------------------------------------------------------------------------
void DrawingTool::selectCharacterTool(int index)
{
    _characterIndex = index;
    deselectCharacterTools(false);
    _characterButtons[index]->setChecked(true);
}



//-----------------------------------------------------------------------------
QWidget* DrawingTool::createAlphanumericPalette()
{
    QWidget* widget = new QWidget();
    widget->setObjectName("toolContainer");
    widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QGridLayout* gridLayout = new QGridLayout();
    QVBoxLayout* layout = new QVBoxLayout();
    gridLayout->setSpacing(0);
    gridLayout->setMargin(0);
    layout->setMargin(0);

    int x = 0;
    int y = 0;

    for (int i=33; i <= 126; ++i) {
        QString text;
        text += (char)i;
        QToolButton* toolButton = new QToolButton();
        toolButton->setStyleSheet("font: 10pt \"Terminal\";");
        toolButton->setCheckable(true);
        toolButton->setToolButtonStyle(Qt::ToolButtonTextOnly);
        toolButton->setAutoRaise(true);
        toolButton->setText(text);
        toolButton->setMinimumWidth(30);
        toolButton->setMinimumHeight(30);
        connect(toolButton, SIGNAL(clicked()), &_characterMap, SLOT(map()));
        connect(this, SIGNAL(deselectCharacterTools(bool)), toolButton, SLOT(setChecked(bool)));
        _characterButtons[i] = toolButton;
        _characterMap.setMapping(toolButton, i);
        gridLayout->addWidget(toolButton, y, x);
        x++;
        if (x == 8) {
            x = 0;
            y++;
        }
    }


    layout->addItem(gridLayout);
    layout->addStretch();
    widget->setLayout(layout);
    return widget;
}


//-----------------------------------------------------------------------------
QWidget* DrawingTool::createLinePalette()
{
    QWidget* widget = new QWidget();
    widget->setObjectName("toolContainer");
    widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QGridLayout* gridLayout = new QGridLayout();
    QVBoxLayout* layout = new QVBoxLayout();
    gridLayout->setSpacing(0);
    gridLayout->setMargin(0);
    layout->setMargin(0);


    int x = 0;
    int y = 0;


    unsigned char translation[] = 
    {
        218, 191, 192, 217, 196, 219,
        213, 184, 212, 190, 205, 221,
        214, 183, 211, 189, 179, 221,       
        201, 187, 200, 188, 186, 222,

        195, 180, 194, 193, 197, 223,
        198, 181, 210, 208, 216, 176,
        199, 182, 209, 207, 215, 177,
        204, 185, 203, 202, 206, 178
    };





    for (int i=0; i < sizeof(translation); ++i) {
        int character = translation[i];
        QString text;
        text += (char)character;
        QToolButton* toolButton = new QToolButton();
        toolButton->setStyleSheet("font: 10pt \"Terminal\";");
        toolButton->setCheckable(true);
        toolButton->setToolButtonStyle(Qt::ToolButtonTextOnly);
        toolButton->setAutoRaise(true);
        toolButton->setText(text);
        toolButton->setMinimumWidth(30);
        toolButton->setMinimumHeight(30);
        connect(toolButton, SIGNAL(clicked()), &_characterMap, SLOT(map()));
        connect(this, SIGNAL(deselectCharacterTools(bool)), toolButton, SLOT(setChecked(bool)));
        _characterButtons[character] = toolButton;
        _characterMap.setMapping(toolButton, character);
        gridLayout->addWidget(toolButton, y, x);
        x++;
        if (x == 6) {
            x = 0;
            y++;
        }
    }


    layout->addItem(gridLayout);
    layout->addStretch();
    widget->setLayout(layout);
    return widget;
}


//-----------------------------------------------------------------------------
QWidget* DrawingTool::createSymbolPalette()
{
    QWidget* widget = new QWidget();
    widget->setObjectName("toolContainer");
    widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QGridLayout* gridLayout = new QGridLayout();
    QVBoxLayout* layout = new QVBoxLayout();
    gridLayout->setSpacing(0);
    gridLayout->setMargin(0);
    layout->setMargin(0);


    int x = 0;
    int y = 0;

    for (int i=1; i <= 31; ++i) {
        switch (i) {
            case '\t':
            case '\n':
            case '\r': break;
            default:

            QString text;
            text += (char)i;
            QToolButton* toolButton = new QToolButton();
            toolButton->setStyleSheet("font: 10pt \"Terminal\";");
            toolButton->setCheckable(true);
            toolButton->setToolButtonStyle(Qt::ToolButtonTextOnly);
            toolButton->setAutoRaise(true);
            toolButton->setText(text);
            toolButton->setMinimumWidth(30);
            toolButton->setMinimumHeight(30);
            connect(toolButton, SIGNAL(clicked()), &_characterMap, SLOT(map()));
            connect(this, SIGNAL(deselectCharacterTools(bool)), toolButton, SLOT(setChecked(bool)));
            _characterButtons[i] = toolButton;
            _characterMap.setMapping(toolButton, i);
            gridLayout->addWidget(toolButton, y, x);
            x++;
            if (x == 8) {
                x = 0;
                y++;
            }
        }
    }


    for (int i=225; i <= 254; ++i) {
        QString text;
        text += (char)i;
        QToolButton* toolButton = new QToolButton();
        toolButton->setStyleSheet("font: 10pt \"Terminal\";");
        toolButton->setCheckable(true);
        toolButton->setToolButtonStyle(Qt::ToolButtonTextOnly);
        toolButton->setAutoRaise(true);
        toolButton->setText(text);
        toolButton->setMinimumWidth(30);
        toolButton->setMinimumHeight(30);
        connect(toolButton, SIGNAL(clicked()), &_characterMap, SLOT(map()));
        connect(this, SIGNAL(deselectCharacterTools(bool)), toolButton, SLOT(setChecked(bool)));
        _characterButtons[i] = toolButton;
        _characterMap.setMapping(toolButton, i);
        gridLayout->addWidget(toolButton, y, x);
        x++;
        if (x == 8) {
            x = 0;
            y++;
        }
    }



    layout->addItem(gridLayout);
    layout->addStretch();
    widget->setLayout(layout);
    return widget;
}
