#include "CardinalSpline.h"
#include "CardinalSplineData.h"
#include "CardinalSplineDrawer.h"
CardinalSpline::CardinalSpline(Vector *points, int n, double c, COLORREF color, CardinalSplineDrawer * drawer=new CardinalSplineDrawer()) : Shape(new CardinalSplineData(*points, n, c, color), drawer){
    draw();
}

ostream& CardinalSpline::format(ostream &out, const Shape &c) {
    CardinalSplineData data = *(CardinalSplineData*) shapeData;
    out<<"cardinalspline "<<data.n;
    for (int i = 0; i < data.n; ++i) {
        out<<" "<<data.points[i][0]<<" "<<data.points[i][1];
    }
    out<<" - "<<((int)GetRValue(data.color))<<" "<<((int)GetGValue(data.color))<<" "<<((int)GetBValue(data.color));
    return out;
}
