#pragma once
#include "ShapeData.h"
#include "ShapeDrawer.h"
class Shape
{
protected:
	ShapeData* shapeData;
	ShapeDrawer* shapeDrawer;
public:
	Shape(ShapeData*, ShapeDrawer*);
	void draw();
	virtual ~Shape();
};

