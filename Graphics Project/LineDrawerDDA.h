#pragma once
#include "ShapeData.h"
#include "LineDrawer.h"
class LineDrawerDDA: public LineDrawer
{
public:
	void draw(ShapeData*);
};

