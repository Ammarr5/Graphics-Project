#pragma once
#include "ShapeDrawer.h"
#include "LineData.h"
class LineDrawer: public ShapeDrawer
{
public:
	virtual void draw(ShapeData*) = 0;
};

