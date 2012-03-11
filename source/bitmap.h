/******************************************************************************
	bitmap.h
 ******************************************************************************/
#ifndef __BITMAP_H__
#define __BITMAP_H__

#include <QColor>
#include <vector>


//-----------------------------------------------------------------------------
//	Class Definition
//-----------------------------------------------------------------------------
class Bitmap
{
public:
	Bitmap();
    Bitmap(int width, int height);
    Bitmap(const Bitmap& obj);
    Bitmap& operator = (const Bitmap& obj);
	~Bitmap();

    int width() const { return _width; }
    int height() const { return _height; }

    unsigned char characterAt(int x, int y) const;
    void setCharacterAt(int x, int y, unsigned char ch);

    QColor foregroundColorAt(int x, int y) const;
    void setForegroundColorAt(int x, int y, const QColor& color);

    QColor backgroundColorAt(int x, int y) const;
    void setBackgroundColorAt(int x, int y, const QColor& color);


private:
    int _width;
    int _height;
    std::vector<unsigned char> _characters;
    std::vector<QColor> _foregroundColors;
    std::vector<QColor> _backgroundColors;
};


#endif
