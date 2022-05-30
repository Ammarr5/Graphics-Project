//
// Created by abdal on 5/29/2022.
//

#include "RectangleDrawer.h"
#include "RectangleData.h"
#include <gl\GLu.h>

void RectangleDrawer::draw(ShapeData* data) {
    RectangleData rd = *(RectangleData*) data;
    COLORREF color = rd.color;

    float r = (float)GetRValue(color)/255;
    float g = (float)GetGValue(color)/255;
    float b = (float)GetBValue(color)/255;
    glBegin(GL_POLYGON);
    glColor3f(r, g, b);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glBegin(GL_LINE_LOOP);
    glVertex2i(rd.xt, rd.yt);
    glVertex2i(rd.xb,rd.yt);
    glVertex2i(rd.xb,rd.yb);
    glVertex2i(rd.xt,rd.yb);
    glEnd();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glFlush();
}