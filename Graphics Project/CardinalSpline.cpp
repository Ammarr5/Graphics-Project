#include "CardinalSpline.h"
#include "CardinalSplineData.h"
#include "CardinalSplineDrawer.h"
CardinalSpline::CardinalSpline(Vector *points, int n, double c, COLORREF color, CardinalSplineDrawer * drawer=new CardinalSplineDrawer()) : Shape(new CardinalSplineData(*points, n, c, color), drawer){
    draw();
}
