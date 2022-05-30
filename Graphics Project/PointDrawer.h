//
// Created by abdal on 5/29/2022.
//

#ifndef GRAPHICS_PROJECT_POINTDRAWER_H
#define GRAPHICS_PROJECT_POINTDRAWER_H


#include "ShapeDrawer.h"
#include "PointData.h"
#include <gl\GLu.h>


class PointDrawer: public ShapeDrawer {
public:
    void draw(ShapeData* data) {
        PointData pd = *(PointData*) data;
        COLORREF color = data->color;
        float r = (float)GetRValue(color)/255;
        float g = (float)GetGValue(color)/255;
        float b = (float)GetBValue(color)/255;
        glBegin(GL_POINTS);
        glColor3f(r, g, b);
        glVertex2d(pd.x, pd.y);
        glEnd();
        glFlush();
    }
};


#endif //GRAPHICS_PROJECT_POINTDRAWER_H
