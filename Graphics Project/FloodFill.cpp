#include "FloodFill.h"
#include <stack>
#include <gl\GLu.h>
#include <valarray>
#include <iostream>

using namespace std;

#pragma comment(lib, "opengl32")
#pragma comment(lib, "glu32")

void FloodFill::FloodFillRecursive(int x, int y, Color Cb, Color Cf)
{
    Color cur_color;
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, &cur_color);

    //cout << cur_color.red << ' ' << Cb.red << endl;
    if (cur_color.red != Cb.red || cur_color.green != Cb.green || cur_color.blue != Cb.blue)
        return;

    //cout << x << ' ' << y << endl;
    glBegin(GL_POINTS);

    glColor3f(Cf.red, Cf.green, Cf.blue);

    glVertex2d(x, y);

    glEnd();
    glFlush();

    FloodFillRecursive(x + 1, y, Cb, Cf);
    FloodFillRecursive(x - 1, y, Cb, Cf);
    FloodFillRecursive(x, y + 1, Cb, Cf);
    FloodFillRecursive(x, y - 1, Cb, Cf);
}
struct Vertex
{
    int x,y;
    Vertex(int x,int y):x(x),y(y)
    {
    }
};

void FloodFill::FloodFillNormal(int x, int y, COLORREF Cb, COLORREF Cf)
{
    /*
    Color cur_color;
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, &cur_color);

    if (cur_color.red == Cb.red && cur_color.green == Cb.green && cur_color.blue == Cb.blue)
        return;

    glBegin(GL_POINTS);
    glColor3f(Cf.red, Cf.green, Cf.blue);
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
     */
}
