//
// Created by abdal on 5/29/2022.
//

#ifndef GRAPHICS_PROJECT_RECTANGLE_H
#define GRAPHICS_PROJECT_RECTANGLE_H

#include "Shape.h"

class Rectangle : public Shape{
public:
    Rectangle(int, int, int, int, COLORREF);
    ostream& format(ostream &out, const Shape &c);
};


#endif //GRAPHICS_PROJECT_RECTANGLE_H
