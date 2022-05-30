#include "FloodFill.h"
#include <stack>
#include <gl\GLu.h>
#include <valarray>

using namespace std;

#pragma comment(lib, "opengl32")
#pragma comment(lib, "glu32")



void FloodFill::FloodFillNormal(int x, int y, COLORREF Cb, COLORREF Cf)
{
    COLORREF color = Cf, color2;

    float r = (float)GetRValue(color)/255;
    float g = (float)GetGValue(color)/255;
    float b = (float)GetBValue(color)/255;

    glBegin(GL_POINTS);
    glColor3f(r, g, b);

    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, &color2);
    COLORREF C = color2;
    if(C==Cb || C==Cf)return;
    glVertex2d(x, y);
    FloodFillNormal(x+1,y,Cb,Cf);
    FloodFillNormal(x-1,y,Cb,Cf);
    FloodFillNormal(x,y+1,Cb,Cf);
    FloodFillNormal(x,y-1,Cb,Cf);
    glEnd();
    glFlush();
}
struct Vertex
{
    int x,y;
    Vertex(int x,int y):x(x),y(y)
    {
    }
};

void FloodFill::FloodFillRecursive(int x, int y, COLORREF Cb, COLORREF Cf)
{
    COLORREF color = Cf, color2;

    float r = (float)GetRValue(color)/255;
    float g = (float)GetGValue(color)/255;
    float b = (float)GetBValue(color)/255;

    glBegin(GL_POINTS);
    glColor3f(r, g, b);
    stack<Vertex> S;
    S.push(Vertex(x,y));
    while(!S.empty())
    {
        Vertex v=S.top();
        S.pop();
        glReadPixels(v.x, v.y, 1, 1, GL_RGB, GL_FLOAT, &color2);

        COLORREF c = color2;
        if(c == Cb || c == Cf) continue;
        glVertex2d(v.x, v.y);
        S.push(Vertex(v.x+1,v.y));
        S.push(Vertex(v.x-1,v.y));
        S.push(Vertex(v.x,v.y+1));
        S.push(Vertex(v.x,v.y-1));
    }
    glEnd();
    glFlush();
}
