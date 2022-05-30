#include "FilledCircle.h"
#include "FilledCircleData.h"
#include "FilledCircleDrawer.h"
#include "FilledCircleByLineDrawer.h"

FilledCircle::FilledCircle(int xc, int yc, int x, int y, int q, COLORREF color, FilledCircleDrawer* drawer=new FilledCircleByLineDrawer())
            :Shape(new FilledCircleData(xc, yc, x, y, q, color), drawer) {
    draw();
}

ostream& FilledCircle::format(ostream &out, const Shape &c) {
    FilledCircleData data = *(FilledCircleData*) shapeData;
    out<<"line "<<data.xc<<" "<<data.yc<<" "<<data.x<<" "<<data.y<<" "<<data.q<<" - "<<((int)GetRValue(data.color))<<" "<<((int)GetGValue(data.color))<<" "<<((int)GetBValue(data.color));
    return out;
}