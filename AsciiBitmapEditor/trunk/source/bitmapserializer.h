/******************************************************************************
	bitmapserializer.h
 ******************************************************************************/
#ifndef __BITMAPSERIALIZER_H__
#define __BITMAPSERIALIZER_H__

#include "bitmap.h"


//-----------------------------------------------------------------------------
//	Class Definition
//-----------------------------------------------------------------------------
class BitmapSerializer
{
public:
	BitmapSerializer();
	~BitmapSerializer();
    Bitmap read(const std::string& filename);
    bool write(const Bitmap& bitmap, const std::string& filename);
};


#endif
