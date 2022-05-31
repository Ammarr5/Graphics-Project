#pragma once
#include "ShapeData.h"
#include "ShapeDrawer.h"

#include <iostream>
using namespace std;

class Shape
{
public:
	ShapeData* shapeData;
	ShapeDrawer* shapeDrawer;
public:
	Shape(ShapeData*, ShapeDrawer*);
	void draw();
	virtual ~Shape();
    virtual ostream& format(ostream &out, const Shape &c) = 0;
    friend ostream & operator << (ostream &out, Shape &c) {
        return c.format(out, c);
    }
};

