#include "FilledCircle.h"
#include "FilledCircleData.h"
#include "FilledCircleDrawer.h"
#include "FilledCircleByLineDrawer.h"

FilledCircle::FilledCircle(int xc, int yc, int x, int y, COLORREF color, FilledCircleDrawer* drawer=new FilledCircleByLineDrawer())
            :Shape(new FilledCircleData(xc, yc, x, y, color), drawer) {
    draw();
}
