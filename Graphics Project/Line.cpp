#include "Line.h"
#include "LineData.h"
#include "LineDrawerDDA.h"
Line::Line(int x1, int y1, int x2, int y2, LineDrawer* drawer = new LineDrawerDDA()) : Shape(new LineData(x1, y1, x2, y2), drawer){
	draw();
}