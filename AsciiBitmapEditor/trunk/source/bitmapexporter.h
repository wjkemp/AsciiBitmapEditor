/******************************************************************************
	bitmapexporter.h
 ******************************************************************************/
#ifndef __BITMAPEXPORTER_H__
#define __BITMAPEXPORTER_H__

#include "bitmap.h"


//-----------------------------------------------------------------------------
//	Class Definition
//-----------------------------------------------------------------------------
class BitmapExporter
{
public:
	BitmapExporter();
	~BitmapExporter();
    bool write(const Bitmap& bitmap, const std::string& filename);
};


#endif
