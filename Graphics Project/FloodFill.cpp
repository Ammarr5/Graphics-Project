#include "FloodFill.h"
#include <stack>
#include <gl\GLu.h>
#include <valarray>
#include <iostream>

using namespace std;

#pragma comment(lib, "opengl32")
#pragma comment(lib, "glu32")

FloodFill::FloodFill() {

}

void FloodFill::FloodFillRecursive(HDC hdc, int x, int y, COLORREF Cb, COLORREF Cf)
{
    COLORREF C = GetPixel(hdc, x, y);
    if (C == Cb || C == Cf)return;
    SetPixel(hdc, x, y, Cf);
    FloodFillRecursive(hdc, x + 1, y, Cb, Cf);
    FloodFillRecursive(hdc, x - 1, y, Cb, Cf);
    FloodFillRecursive(hdc, x, y + 1, Cb, Cf);
    return FloodFillRecursive(hdc, x, y - 1, Cb, Cf);
}
struct Vertex
{
    int x,y;
    Vertex(int x,int y):x(x),y(y)
    {
    }
};

void FloodFill::FloodFillNormal(HDC hdc, int x, int y, COLORREF Cb, COLORREF Cf)
{
    stack<pair<int, int>> stk;
    stk.emplace(x, y);
    while (!stk.empty())
    {
        pair<int, int> v = stk.top();
        stk.pop();
        COLORREF c;
        c = GetPixel(hdc, v.first, v.second);
        if (c == Cb || c == Cf)
            continue;
        SetPixel(hdc, v.first, v.second, Cf);
        stk.emplace(v.first + 1, v.second);
        stk.emplace(v.first - 1, v.second);
        stk.emplace(v.first, v.second + 1);
        stk.emplace(v.first, v.second - 1);
    }
}
