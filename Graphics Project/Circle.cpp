#include "Circle.h"
#include "CircleData.h"
#include "CircleDrawerDirect.h"

Circle::Circle(int x1, int y1, int x2, int y2, COLORREF color, CircleDrawer* drawer = new CircleDrawerDirect()) : Shape(new CircleData(x1, y1, x2, y2, color), drawer){
    draw();
}

