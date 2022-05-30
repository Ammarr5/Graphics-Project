#include "LineDrawerMidpoint.h"
#include "LineData.h"

#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLu.h>
#include <iostream>
using namespace std;

#pragma comment(lib,"opengl32")
#pragma comment(lib,"glu32")

void LineDrawerMidpoint::draw(ShapeData* data) {
    cout<<"Line Midpoint algorithm selected."<<endl;
    LineData lData = *(LineData *) data;
    int x1 = lData.x1;
    int y1 = lData.y1;
    int x2 = lData.x2;
    int y2 = lData.y2;
    COLORREF color = lData.color;

    glBegin(GL_POINTS);
    glColor3f((float)GetRValue(color)/255, (float)GetGValue(color)/255, (float) GetBValue(color)/255);
    int x,y,xe,ye,i;
    int dx = x2 - x1;
    int dy = y2 - y1;
    int dx1=abs(dx);
    int dy1=abs(dy);
    int px=2*dy1-dx1;
    int py=2*dx1-dy1;
    if(dy1<=dx1)
    {
        if(dx>=0)
        {
            x=x1;
            y=y1;
            xe=x2;
        }
        else
        {
            x=x2;
            y=y2;
            xe=x1;
        }
        glVertex2d(x,y);
        for(i=0;x<xe;i++)
        {
            x++;
            if(px<0)
            {
                px=px+2*dy1;
            }
            else
            {
                if((dx<0 && dy<0) || (dx>0 && dy>0))
                {
                    y++;
                }
                else
                {
                    y--;
                }
                px=px+2*(dy1-dx1);
            }
            glVertex2d(x,y);
        }
    }
    else
    {
        if(dy>=0)
        {
            x=x1;
            y=y1;
            ye=y2;
        }
        else
        {
            x=x2;
            y=y2;
            ye=y1;
        }
        glVertex2d(x,y);
        for(i=0;y<ye;i++)
        {
            y++;
            if(py<=0)
            {
                py=py+2*dx1;
            }
            else
            {
                if((dx<0 && dy<0) || (dx>0 && dy>0))
                {
                    x++;
                }
                else
                {
                    x--;
                }
                py=py+2*(dx1-dy1);
            }
            glVertex2d(x,y);
        }
    }
    glEnd();
    glFlush();
}