//
// Created by abdal on 5/30/2022.
//

#include "PolygonDrawer.h"
#include "PolygonData.h"
#include <gl\GLu.h>

void PolygonDrawer::draw(ShapeData* data) {
    PolygonData pd = *(PolygonData*) data;
    COLORREF color = pd.color;
    std::vector<PointData*> points = pd.points;

    float r = (float)GetRValue(color)/255;
    float g = (float)GetGValue(color)/255;
    float b = (float)GetBValue(color)/255;
    glBegin(GL_POLYGON);
    glColor3f(r, g, b);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glBegin(GL_LINE_LOOP);
    for(PointData* point : points) {
        glVertex2i(point->x, point->y);
    }
    glEnd();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glFlush();
}
