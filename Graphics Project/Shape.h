#pragma once
#include "ShapeData.h"
#include "ShapeDrawer.h"
class Shape
{
public:
	ShapeData* shapeData;
	ShapeDrawer* shapeDrawer;
public:
	Shape(ShapeData*, ShapeDrawer*);
	void draw();
	virtual ~Shape();
};

