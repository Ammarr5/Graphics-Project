#ifndef UNICODE
#define UNICODE
#endif // !UNICODE

#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLu.h>
#include <fstream>
#include <math.h>
#include <iostream>
#include "menu_items.h"
#include "Line.h"
#include "Point.h"
#include "CardinalSpline.h"
#include "LineDrawerDDA.h"
#include "LineDrawerMidpoint.h"
#include "LineDrawerParametric.h"
#include "FilledCircleByLineDrawer.h"
#include "FilledCircle.h"
#include "FilledCircleByCircleDrawer.h"
#include "Clipper.h"
#include "RectanglePointClipper.h"
#include "Rectangle.h"
#include "cmath"
#include "PointData.h"
#include "RectangleLineClipper.h"
#include "RectanglePolygonClipper.h"
#include "CircleDrawerDirect.h"
#include "CircleDrawerPolar.h"
#include "CircleDrawerIterativePolar.h"
#include "CircleDrawerMidpoint.h"
#include "CircleDrawerMidpointModified.h"
#include "Circle.h"
#include "EllipseDrawerDirect.h"
#include "EllipseDrawerPolar.h"
#include "EllipseDrawerMidpoint.h"
#include "Ellipse.h"
#include "Polygon.h"
#include "PolygonDrawer.h"
#include "CirclePointClipper.h"
#include "FloodFill.h"
#include "CircleLineClipper.h"
#include <vector>

#pragma comment(lib,"opengl32")
#pragma comment(lib,"glu32")
using namespace std;

struct Point1{
    int x,y;
};

void populateMenus(HWND);
string browseFile(bool);
void saveToFile(ofstream&);
void loadFromFile(ifstream&);
vector<Shape*> shapes;

HGLRC InitOpenGl(HDC hdc)
{
    PIXELFORMATDESCRIPTOR pfd = {
            sizeof(PIXELFORMATDESCRIPTOR),   // size of this pfd
            1,                     // version number
            PFD_DRAW_TO_WINDOW |   // support window
            PFD_SUPPORT_OPENGL |   // support OpenGL
            0,      // double buffered
            PFD_TYPE_RGBA,         // RGBA type
            24,                    // 24-bit color depth
            0, 0, 0, 0, 0, 0,      // color bits ignored
            0,                     // no alpha buffer
            0,                     // shift bit ignored
            0,                     // no accumulation buffer
            0, 0, 0, 0,            // accum bits ignored
            32,                    // 32-bit z-buffer
            0,                     // no stencil buffer
            0,                     // no auxiliary buffer
            PFD_MAIN_PLANE,        // main layer
            0,                     // reserved
            0, 0, 0                // layer masks ignored
    };
    int  iPixelFormat;
    iPixelFormat = ChoosePixelFormat(hdc, &pfd);
    SetPixelFormat(hdc, iPixelFormat, &pfd);
    HGLRC glrc = wglCreateContext(hdc);
    wglMakeCurrent(hdc, glrc);
    return glrc;
}
void AdjustWindowFor2D(HDC hdc, int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, h, 0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, w, h);
    glClearColor(0.75, 0.75, 0.75, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void EndOpenGl(HGLRC glrc)
{
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(glrc);
}
LRESULT WINAPI MyWndProc(HWND hwnd, UINT mcode, WPARAM wp, LPARAM lp)
{
    static HDC hdc;
    static HGLRC glrc;
    static ShapeDrawer* shapeDrawer = nullptr;
    static Shape* tempShape = nullptr;
    static Clipper* shapeClipper = nullptr;
    static COLORREF color = RGB(1, 1, 0);
    static COLORREF prev = color; // Previous color.
    static Point1 points[3];
    static int last_x, last_y;
    static int i = 0;
    static int rectVerticesCounter = 0,cirVerticesCounter=0;
    enum ShapeType{line,cardinalspline,FilledCir, none_selected, RECT_CLIP_POINT, RECT_CLIP_LINE, RECT_CLIP_POLYGON, circle,
            ellipse, floodNormal, floodNone,CIR_CLIP_POINT,CIR_CLIP_LINE, SQU_CLIP_LINE, SQU_CLIP_POINT, polyConvex, polyNonConvex,
            FILL_SQR_HER,FILL_REC_BEZ};
    static ShapeType shapetype = none_selected;
    const int numberOfSplinePoints=8;
    static Vector p[numberOfSplinePoints];
    const int polygonPoints = 5;
    static vector<PointData*> polygonLines;
    switch (mcode)
    {
/*    case WM_SETCURSOR:{
//        HCURSOR cursor = LoadCursorFromFileA("c2.cur");
//        SetCursor(cursor);
        SetCursor(LoadCursor(NULL, IDC_SIZEALL));
        break;}*/
        case WM_CREATE:{
            hdc = GetDC(hwnd);
            populateMenus(hwnd);
            glrc = InitOpenGl(hdc);
            break;}
        case WM_SIZE:
            AdjustWindowFor2D(hdc, LOWORD(lp), HIWORD(lp));
            break;
        case WM_LBUTTONDOWN:{
            if(shapetype==line) {
                points[i].x = LOWORD(lp);
                points[i].y = HIWORD(lp);
                last_x = points[i].x, last_y = points[i].y;
                i++;
                if (i == 2) {
                    i = 0;
                    Shape *line;
                    LineDrawer* ld = (LineDrawer*)shapeDrawer;
                    line = new Line(points[0].x, points[0].y, points[1].x, points[1].y, color, ld);
                    shapes.push_back(line);
                }
            }
            else if(shapetype==cardinalspline){
                p[i] = Vector(LOWORD(lp), HIWORD(lp));
                if (i == numberOfSplinePoints-1) {
                    Vector T1(3 * (p[1][0] - p[0][0]), 3 * (p[1][1] - p[0][1]));
                    Vector T2(3 * (p[3][0] - p[2][0]), 3 * (p[3][1] - p[2][1]));
                    Shape *spline;
                    CardinalSplineDrawer* sd = (CardinalSplineDrawer*)shapeDrawer;
                    spline=new CardinalSpline(p,8,0.3,color,sd);
                    i = 0;
                    shapes.push_back(spline);
                }
                else
                    i++;
            }
            else if(shapetype==FilledCir){
                points[i].x = LOWORD(lp);
                points[i].y = HIWORD(lp);
                i++;
                if (i == 2) {
                    i = 0;
                    Shape *fillCir;
                    FilledCircleDrawer* fd = (FilledCircleDrawer*)shapeDrawer;
                    int quarter;
                    cout<<"Enter the number of quarter you want to fill:"<<endl;
                    cin>>quarter;
                    fillCir = new FilledCircle(points[0].x, points[0].y, points[1].x, points[1].y, quarter, color, fd);
                    shapes.push_back(fillCir);
                }
            }
            else if(shapetype == RECT_CLIP_POINT) {
                if (rectVerticesCounter == 2) {
                    Shape* pointClipped = nullptr;
                    if(shapeClipper->clip(new PointData(LOWORD(lp), HIWORD(lp), color), pointClipped)) {
                        shapes.push_back(pointClipped);
//                        cout<<*pointClipped<<endl;
                    }
                }
                else {
                    points[rectVerticesCounter].x = LOWORD(lp);
                    points[rectVerticesCounter].y = HIWORD(lp);
                    rectVerticesCounter++;
                    if (rectVerticesCounter == 2) {
                        shapeClipper = new RectanglePointClipper(min(points[0].x, points[1].x), min(points[0].y, points[1].y), max(points[0].x, points[1].x), max(points[0].y, points[1].y), color);
                        shapes.push_back(shapeClipper->getShape());
                    }
                }
            }
            else if(shapetype == RECT_CLIP_LINE) {
                if(rectVerticesCounter == 2) {
                    points[i].x = LOWORD(lp);
                    points[i].y = HIWORD(lp);
                    i++;
                    if (i == 2) {
                        i = 0;
                        Shape* s = nullptr;
                        if(shapeClipper->clip(new LineData(points[0].x, points[0].y, points[1].x, points[1].y, color), s)) {
                            shapes.push_back(s);
                        }
                    }
                }
                else {
                    points[rectVerticesCounter].x = LOWORD(lp);
                    points[rectVerticesCounter].y = HIWORD(lp);
                    rectVerticesCounter++;
                    if(rectVerticesCounter == 2) {
                        shapeClipper = new RectangleLineClipper(min(points[0].x, points[1].x), min(points[0].y, points[1].y), max(points[0].x, points[1].x), max(points[0].y, points[1].y), color);
                        shapes.push_back(shapeClipper->getShape());
                    }
                }
            }
            else if(shapetype == RECT_CLIP_POLYGON) {
                if(rectVerticesCounter == 2) {
                    polygonLines.push_back(new PointData(LOWORD(lp), HIWORD(lp), color));
                    i++;
                    if (i == 5) {
                        i = 0;
                        Shape* s = nullptr;
                        vector<PointData*> pl = polygonLines;
                        if(shapeClipper->clip(new PolygonData(pl, color), s)) {
                            shapes.push_back(s);
                        }
                        polygonLines.clear();
                    }
                }
                else {
                    points[rectVerticesCounter].x = LOWORD(lp);
                    points[rectVerticesCounter].y = HIWORD(lp);
                    rectVerticesCounter++;
                    if(rectVerticesCounter == 2) {
                        shapeClipper = new RectanglePolygonClipper(min(points[0].x, points[1].x), min(points[0].y, points[1].y), max(points[0].x, points[1].x), max(points[0].y, points[1].y), color);
                        shapes.push_back(shapeClipper->getShape());
                    }
                }
            }
            else if(shapetype == CIR_CLIP_POINT) {
                if (cirVerticesCounter == 2) {
                    Shape* pointClipped = nullptr;
                    if(shapeClipper->clip(new PointData(LOWORD(lp), HIWORD(lp), color), pointClipped)) {
                        shapes.push_back(pointClipped);
//                        cout<<*pointClipped<<endl;
                    }
                }
                else {
                    points[cirVerticesCounter].x = LOWORD(lp);
                    points[cirVerticesCounter].y = HIWORD(lp);
                    cirVerticesCounter++;
                    if (cirVerticesCounter == 2) {
                        CircleDrawer* cd = (CircleDrawer*)new CircleDrawerDirect();
                        shapeClipper = new CirclePointClipper(points[0].x,points[0].y,points[1].x, points[1].y, color,cd);
                        shapes.push_back(shapeClipper->getShape());
                    }
                }
            }
            else if (shapetype == CIR_CLIP_LINE) {
                if (cirVerticesCounter == 2) {
                    points[i].x = LOWORD(lp);
                    points[i].y = HIWORD(lp);
                    i++;
                    if (i == 2) {
                        i = 0;
                        Shape* s = nullptr;
                        if (shapeClipper->clip(new LineData(points[0].x, points[0].y, points[1].x, points[1].y, color), s)) {
                            shapes.push_back(s);
                        }
                    }
                }
                else {
                    points[cirVerticesCounter].x = LOWORD(lp);
                    points[cirVerticesCounter].y = HIWORD(lp);
                    cirVerticesCounter++;
                    if (cirVerticesCounter == 2) {
                        int xc = points[0].x;
                        int yc = points[0].y;
                        int x = points[1].x;
                        int y = points[1].y;
                        CircleDrawer* cd = (CircleDrawer*)new CircleDrawerDirect();
                        shapeClipper = new CircleLineClipper(xc, yc, x, y, color, cd);
                        shapes.push_back(shapeClipper->getShape());
                    }
                }
            }
            else if (shapetype == circle)
            {
                points[i].x = LOWORD(lp);
                points[i].y = HIWORD(lp);
                last_x = points[i].x, last_y = points[i].y;
                i++;
                if (i == 2) {
                    i = 0;
                    Shape *circle;
                    CircleDrawer* cd = (CircleDrawer*)shapeDrawer;
                    circle = new Circle(points[0].x, points[0].y, points[1].x, points[1].y, color, cd);
                    shapes.push_back(circle);
                }
            }
            else if (shapetype == ellipse)
            {
                points[i].x = LOWORD(lp);
                points[i].y = HIWORD(lp);
                i++;
                if (i == 3) {
                    i = 0;
                    Shape *ellipse;
                    EllipseDrawer* ed = (EllipseDrawer*)shapeDrawer;
                    ellipse = new class Ellipse(points[0].x, points[0].y, points[1].x, points[1].y, points[2].x, points[2].y, color, ed);
                    shapes.push_back(ellipse);
                }
            }
            else if(shapetype == SQU_CLIP_LINE) {
                if(rectVerticesCounter == 2) {
                    points[i].x = LOWORD(lp);
                    points[i].y = HIWORD(lp);
                    i++;
                    if (i == 2) {
                        i = 0;
                        Shape* s = nullptr;
                        if(shapeClipper->clip(new LineData(points[0].x, points[0].y, points[1].x, points[1].y, color), s)) {
                            shapes.push_back(s);
                        }
                    }
                }
                else {
                    points[rectVerticesCounter].x = LOWORD(lp);
                    points[rectVerticesCounter].y = HIWORD(lp);
                    rectVerticesCounter++;
                    if(rectVerticesCounter == 2) {
                        int xt = min(points[0].x, points[1].x);
                        int yt = min(points[0].y, points[1].y);
                        int xb = max(points[0].x, points[1].x);
                        int sideLength = xb - xt;
                        shapeClipper = new RectangleLineClipper(xt, yt, xt+sideLength, yt+sideLength, color);
                        shapes.push_back(shapeClipper->getShape());
                    }
                }
            }
            else if(shapetype == SQU_CLIP_POINT) {
                if (rectVerticesCounter == 2) {
                    Shape* pointClipped = nullptr;
                    if(shapeClipper->clip(new PointData(LOWORD(lp), HIWORD(lp), color), pointClipped)) {
                        shapes.push_back(pointClipped);
//                        cout<<*pointClipped<<endl;
                    }
                }
                else {
                    points[rectVerticesCounter].x = LOWORD(lp);
                    points[rectVerticesCounter].y = HIWORD(lp);
                    rectVerticesCounter++;
                    if (rectVerticesCounter == 2) {
                        int xt = min(points[0].x, points[1].x);
                        int yt = min(points[0].y, points[1].y);
                        int xb = max(points[0].x, points[1].x);
                        int sideLength = xb - xt;
                        shapeClipper = new RectanglePointClipper(xt, yt, xt+sideLength, yt+sideLength, color);
                        shapes.push_back(shapeClipper->getShape());
                    }
                }
            }
            else if (shapetype == floodNormal)
            {
                COLORREF Cb = (0, 0, 0);
                points[i].x = LOWORD(lp);
                points[i].y = HIWORD(lp);
                i++;
                if (i == 1) {
                    i = 0;
                    class FloodFill *ff = new class FloodFill();
                    ff->FloodFillRecursive(hdc, points[0].x, points[0].y, prev, color);
                }
            }
            else if (shapetype == floodNone)
            {
                points[i].x = LOWORD(lp);
                points[i].y = HIWORD(lp);
                i++;
                if (i == 1) {
                    i = 0;
                    class FloodFill *ff = new class FloodFill();
                    ff->FloodFillNormal(hdc, points[0].x, points[0].y, prev, color);
                }
            }
            else if (shapetype == polyConvex)
            {
                polygonLines.push_back(new PointData(LOWORD(lp), HIWORD(lp), color));
                if (i == polygonPoints - 1) {
                    Shape *polygon;
                    PolygonDrawer* pd = (PolygonDrawer*)shapeDrawer;
                    vector<PointData*> cur_points = polygonLines;
                    polygon = new class Polygon(cur_points, color);
                    pd->convexFilling(new PolygonData(cur_points, color));
                    i = 0;
                    shapes.push_back(polygon);
                    polygonLines.clear();
                }
                else i++;
            }
            else if (shapetype == polyNonConvex)
            {
                polygonLines.push_back(new PointData(LOWORD(lp), HIWORD(lp), color));
                if (i == polygonPoints - 1) {
                    Shape *polygon;
                    PolygonDrawer* pd = (PolygonDrawer*)shapeDrawer;
                    vector<PointData*> cur_points = polygonLines;
                    polygon = new class Polygon(cur_points, color);
                    pd->nonConvexFilling(new PolygonData(cur_points, color));
                    i = 0;
                    shapes.push_back(polygon);
                    polygonLines.clear();
                }
                else i++;
            }
            else if (shapetype == FILL_SQR_HER)
            {
                    points[rectVerticesCounter].x = LOWORD(lp);
                    points[rectVerticesCounter].y = HIWORD(lp);
                    rectVerticesCounter++;
                    if (rectVerticesCounter == 2) {
                        rectVerticesCounter = 0;
                        int xt = min(points[0].x, points[1].x);
                        int yt = min(points[0].y, points[1].y);
                        int xb = max(points[0].x, points[1].x);
                        int sideLength = xb - xt;
                        class Rectangle* rect = new class Rectangle(xt, yt, xt+sideLength, yt+sideLength, color);
                        shapes.push_back(rect);
                        rect->fillWithHermite();
                    }
            }
            else if (shapetype == FILL_REC_BEZ)
            {
                points[rectVerticesCounter].x = LOWORD(lp);
                points[rectVerticesCounter].y = HIWORD(lp);
                rectVerticesCounter++;
                if(rectVerticesCounter == 2) {
                    rectVerticesCounter = 0;
                    class Rectangle* rect = new class Rectangle(min(points[0].x, points[1].x), min(points[0].y, points[1].y), max(points[0].x, points[1].x), max(points[0].y, points[1].y), color);
                    shapes.push_back(rect);
                    rect->fillWithBezier();
                }
            }
            break;
        }
        case WM_COMMAND: // When menu option is selected
            switch (LOWORD(wp)) { // switch for various menu options
                case M_WHITE_BG: {
                    glClearColor(1, 1, 1, 1);
                    glClear(GL_COLOR_BUFFER_BIT); // Clearing the screen.
                    glShadeModel(GLU_FLAT);
                    glEnd();
                    glFlush();
                    ofstream ofile;
                    ofile.open("D:/tempData.txt");
                    saveToFile(ofile);
                    shapes.clear();
                    ifstream ifile;
                    ifile.open("D:/tempData.txt");
                    loadFromFile(ifile);
//                    new Point(new PointData(0, 0, color));
//                    for (int k = 0; k < shapes.size(); k++)
//                        shapes[k]->draw();
                    cout << "white bg";
                    break;
                }
                case M_LINE_DDA:
                    delete shapeDrawer;
                    shapeDrawer = new LineDrawerDDA();
                    shapetype = line;
                    break;
                case M_LINE_MP:
                    delete shapeDrawer;
                    shapeDrawer = new LineDrawerMidpoint();
                    shapetype = line;
                    break;
                case M_LINE_PARAM:
                    delete shapeDrawer;
                    shapeDrawer = new LineDrawerParametric();
                    shapetype = line;
                    break;
                case M_CIRCLE_DIRECT:
                    delete shapeDrawer;
                    shapeDrawer = new CircleDrawerDirect();
                    shapetype = circle;
                    break;
                case M_CIRCLE_POLAR:
                    delete shapeDrawer;
                    shapeDrawer = new CircleDrawerPolar();
                    shapetype = circle;
                    break;
                case M_CIRCLE_ITER_POLAR:
                    delete shapeDrawer;
                    shapeDrawer = new CircleDrawerIterativePolar();
                    shapetype = circle;
                    break;
                case M_CIRCLE_MIDPOINT:
                    delete shapeDrawer;
                    shapeDrawer = new CircleDrawerMidpoint();
                    shapetype = circle;
                    break;
                case M_CIRCLE_MIDPOINT_MODIFIED:
                    delete shapeDrawer;
                    shapeDrawer = new CircleDrawerMidpointModified();
                    shapetype = circle;
                    break;
                case M_ELLIPSE_DIRECT:
                    delete shapeDrawer;
                    shapeDrawer = new EllipseDrawerDirect();
                    shapetype = ellipse;
                    break;
                case M_ELLIPSE_POLAR:
                    delete shapeDrawer;
                    shapeDrawer = new EllipseDrawerPolar();
                    shapetype = ellipse;
                    break;
                case M_ELLIPSE_MIDPOINT:
                    delete shapeDrawer;
                    shapeDrawer = new EllipseDrawerMidpoint();
                    shapetype = ellipse;
                    break;
                case M_FILL_CIR_LINE:
                    delete shapeDrawer;
                    shapeDrawer = new FilledCircleByLineDrawer();
                    shapetype = FilledCir;
                    break;
                case M_FILL_CIR_CIR:
                    delete shapeDrawer;
                    shapeDrawer = new FilledCircleByCircleDrawer();
                    shapetype = FilledCir;
                    break;
                case M_COLOR:
                    prev = color;
                    CHOOSECOLOR cc;                 // common dialog box structure
                    static COLORREF acrCustClr[16]; // array of custom colors
                    static DWORD rgbCurrent;        // initial color selection
                    ZeroMemory(&cc, sizeof(cc));
                    cc.lStructSize = sizeof(cc);
                    cc.hwndOwner = hwnd;
                    cc.lpCustColors = (LPDWORD) acrCustClr;
                    cc.rgbResult = rgbCurrent;
                    cc.Flags = CC_FULLOPEN | CC_RGBINIT;
                    if (ChooseColor(&cc) == TRUE) {
                        rgbCurrent = cc.rgbResult;
                        color = cc.rgbResult;
                    }
                    break;
                case M_CARDINAL_SPLINE:
                    delete shapeDrawer;
                    shapeDrawer = new CardinalSplineDrawer();
                    shapetype = cardinalspline;
                    break;
                case M_CONVEX:
                    delete shapeDrawer;
                    shapeDrawer = new PolygonDrawer();
                    shapetype = polyConvex;
                    break;
                case M_NON_CONVEX:
                    delete shapeDrawer;
                    shapeDrawer = new PolygonDrawer();
                    shapetype = polyNonConvex;
                    break;
                case M_CLEAR_SCREEN:
                    glClear(GL_COLOR_BUFFER_BIT); // Clearing the screen.
                    glFlush();
                    new Point(new PointData(0,0,color));
                    shapes.clear();
                    break;
                case M_CLIP_RECT_POINT:
                    shapetype = RECT_CLIP_POINT;
                    rectVerticesCounter = 0;
                    delete shapeClipper;
                    break;
                case M_CLIP_RECT_LINE:
                    shapetype = RECT_CLIP_LINE;
                    rectVerticesCounter = 0;
                    delete shapeClipper;
                    break;
                case M_CLIP_RECT_POLYGON:
                    shapetype = RECT_CLIP_POLYGON;
                    rectVerticesCounter = 0;
                    delete shapeClipper;
                    break;
                case M_CLIP_CIR_POINT:
                    shapetype = CIR_CLIP_POINT;
                    cirVerticesCounter = 0;
                    delete shapeClipper;
                    break;
                case M_CLIP_CIR_LINE:
                    shapetype = CIR_CLIP_LINE;
                    cirVerticesCounter = 0;
                    delete shapeClipper;
                    break;
                case M_SAVE:{
                    string path = browseFile(true);
                    if (path == ""){break;}
                    ofstream ofile;
                    ofile.open(path);
                    saveToFile(ofile);
                    break;}
                case M_LOAD:{
                    string path = browseFile(false);
                    if (path == ""){break;}
                    ifstream infile;
                    infile.open(path);
                    glClear(GL_COLOR_BUFFER_BIT); // Clearing the screen.
                    glFlush();
                    new Point(new PointData(0,0,color));
                    shapes.clear();
                    loadFromFile(infile);
                    break;}
                case M_CLIP_SQU_LINE:
                    shapetype = SQU_CLIP_LINE;
                    rectVerticesCounter = 0;
                    delete shapeClipper;
                    break;
                case M_CLIP_SQU_POINT:
                    shapetype = SQU_CLIP_POINT;
                    rectVerticesCounter = 0;
                    delete shapeClipper;
                    break;
                case M_FLOODFILL_NORMAL:
                    shapetype = floodNormal;
                    break;
                case M_FLOODFILL_NONE:
                    shapetype = floodNone;
                    break;
                case M_FILL_SQR_HER:
                    rectVerticesCounter = 0;
                    shapetype = FILL_SQR_HER;
                    break;
                case M_FILL_REC_BEZ:
                    rectVerticesCounter = 0;
                    shapetype = FILL_REC_BEZ;
                    break;
            }
            break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        case WM_DESTROY:
            EndOpenGl(glrc);
            ReleaseDC(hwnd, hdc);
            PostQuitMessage(0);
            break;
        default: return DefWindowProc(hwnd, mcode, wp, lp);
    }
    return 0;
}

int APIENTRY WinMain(HINSTANCE hinst, HINSTANCE pinst, LPSTR cmd, int nsh)
{
    WNDCLASS wc;
    wc.cbClsExtra = wc.cbWndExtra = 0;
    wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hInstance = hinst;
    wc.lpfnWndProc = MyWndProc;
    wc.lpszClassName = L"MyClass";
    wc.lpszMenuName = NULL;
    wc.style = CS_HREDRAW | CS_VREDRAW;
    RegisterClass(&wc);
    HWND hwnd = CreateWindow(L"MyClass", L"My First Window", WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, 0, 0, 800, 600, NULL, NULL, hinst, 0);
    ShowWindow(hwnd, nsh);
    UpdateWindow(hwnd);
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

string browseFile(bool save) {
    OPENFILENAME ofn;       // common dialog box structure
    wchar_t szFile[MAX_PATH];       // buffer for file name
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    wchar_t title[500];  // to hold title
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = szFile;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFilter = L"Text File\0*.txt";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    // Display the Open dialog box.
    WINBOOL res = FALSE;
    if(save) {
        res = GetSaveFileName(&ofn);
    } else {
        res = GetOpenFileName(&ofn);
    }
    if(res != TRUE) {
        return "";
    }

    for(int i=0; i<MAX_PATH; i++){
        if(szFile[i] == '\n'){break;}
        if(szFile[i]=='\\')
            szFile[i]='/';
    };
    wstring ws(szFile);
    string path(ws.begin(), ws.end());
    return path;
}

void saveToFile(ofstream& ofile) {
    for(Shape* shape : shapes) {
        ofile<<(*shape)<<endl;
    }
    ofile.close();
}


void parseLine(ifstream&);
void parseSpline(ifstream&);
void parseCircle(ifstream&);
void parseEllipse(ifstream&);
void parseRectangle(ifstream&);
void parsePoint(ifstream&);
void parsePolygon(ifstream&);
void parseFilledCircle(ifstream&);
void loadFromFile(ifstream& ifile) {
    string shapeName;
    while(ifile>>shapeName && ifile.ignore()) {
        if (shapeName == "line") {
            parseLine(ifile);
        }
        else if(shapeName == "cardinalspline") {
            parseSpline(ifile);
        }
        else if(shapeName == "circle") {
            parseCircle(ifile);
        }
        else if(shapeName == "ellipse") {
            parseEllipse(ifile);
        }
        else if(shapeName == "rectangle") {
            parseRectangle(ifile);
        }
        else if(shapeName == "point") {
            parsePoint(ifile);
        }
        else if(shapeName == "polygon") {
            parsePolygon(ifile);
        }
        else if(shapeName == "filledcircle") {
            parseFilledCircle(ifile);
        }
    }
    ifile.close();
}

void parseLine(ifstream& ifile) {
    int x1; int y1; int x2; int y2;
    int r; int g; int b;
    ifile>>x1>>y1>>x2>>y2;
    ifile.ignore(3);
    ifile>>r>>g>>b;
    shapes.push_back(new Line(x1, y1, x2, y2, RGB(r, g, b), new LineDrawerDDA()));
}

void parseSpline(ifstream& ifile) {
    int n;
    int r; int g; int b;
    ifile>>n;
    Vector p[n];
    for (int i = 0; i < n; ++i) {
        ifile>>p[i][0]>>p[i][1];
    }
    ifile.ignore(3);
    ifile>>r>>g>>b;
    shapes.push_back(new CardinalSpline(p, n, 0.3, RGB(r, g, b), new CardinalSplineDrawer()));
}

void parseCircle(ifstream& ifile) {
    int xc; int yc; int x1; int y1;
    int r; int g; int b;
    ifile>>xc>>yc>>x1>>y1;
    ifile.ignore(3);
    ifile>>r>>g>>b;
    shapes.push_back(new Circle(xc, yc, x1, y1, RGB(r, g, b), new CircleDrawerMidpointModified()));
}

void parseEllipse(ifstream& ifile) {
    int x1; int x2; int x3;
    int y1; int y2; int y3;
    int r; int g; int b;
    ifile>>x1>>y1>>x2>>y2>>x3>>y3;
    ifile.ignore(3);
    ifile>>r>>g>>b;
    shapes.push_back(new class Ellipse(x1, y1, x2, y2, x3, y3, RGB(r, g, b), new EllipseDrawerMidpoint()));
}

void parseRectangle(ifstream& ifile) {
    int xt; int yt; int xb; int yb;
    int r; int g; int b;
    ifile>>xt>>yt>>xb>>yb;
    ifile.ignore(3);
    ifile>>r>>g>>b;
    shapes.push_back(new class Rectangle(xt, yt, xb, yb, RGB(r, g, b)));
}

void parsePoint(ifstream& ifile) {
    int x; int y;
    int r; int g; int b;
    ifile>>x>>y;
    ifile.ignore(3);
    ifile>>r>>g>>b;
    shapes.push_back(new Point(new PointData(x, y, RGB(r, g, b))));
}

void parsePolygon(ifstream& ifile) {
    int x; int y;
    int r; int g; int b;
    vector<PointData*> pd;
    while(ifile>>x) {
        ifile>>y;
        pd.push_back(new PointData(x, y, RGB(0, 0, 0)));
    }
    ifile.clear();
    ifile>>r>>g>>b;
    cout<<r<<" "<<g<<" "<<b<<endl;
    shapes.push_back(new class Polygon(pd, RGB(r, g, b)));
}

void parseFilledCircle(ifstream& ifile) {
    int xc; int yc; int x; int y;
    int q;
    int r; int g; int b;
    ifile>>xc>>yc>>x>>y;
    ifile>>q;
    ifile.ignore(3);
    ifile>>r>>g>>b;
    shapes.push_back(new FilledCircle(xc, yc, x, y, q, RGB(r, g, b), new FilledCircleByLineDrawer()));
}

// function to add menus to window once created
void populateMenus(HWND hwnd) {

    HMENU hMenubar; // Strip that holds all menus (which is one in our case call "menu")
    HMENU hMenu;
    HMENU hLineMenu; // Line submenu
    HMENU hRectClipping; // Rectangle Clipping submenu
    HMENU hSquClipping; // Square Clipping submenu
    HMENU hCirClipping; // Circle Clipping submenu
    HMENU hFillCircleMenu; // Fill Circle submenu
    HMENU hCircleMenu; // Circle submenu
    HMENU hEllipseMenu; // Ellipse submenu
    HMENU hFloodMenu; // Flood Fill submenu
    HMENU hPolyFillMenu; // Polygon Fill submenu

    hMenubar = CreateMenu();
    hMenu = CreateMenu();
    hLineMenu = CreateMenu();
    hRectClipping = CreateMenu();
    hSquClipping = CreateMenu();
    hCirClipping = CreateMenu();
    hFillCircleMenu = CreateMenu();
    hCircleMenu = CreateMenu();
    hEllipseMenu = CreateMenu();
    hFloodMenu = CreateMenu();
    hPolyFillMenu = CreateMenu();

    AppendMenuW(hMenu, MF_STRING, M_SAVE, L"&Save");
    AppendMenuW(hMenu, MF_STRING, M_LOAD, L"&Load");
    AppendMenuW(hMenu, MF_SEPARATOR, 0, NULL);
    AppendMenuW(hMenu, MF_STRING, M_COLOR, L"&Select Color");
    AppendMenuW(hMenu, MF_STRING, M_WHITE_BG, L"&White Background");
    AppendMenuW(hMenu, MF_STRING, M_CLEAR_SCREEN, L"&Clear Screen");
    AppendMenuW(hMenu, MF_SEPARATOR, 0, NULL);
    AppendMenuW(hMenu, MF_STRING | MF_POPUP, (UINT_PTR)hLineMenu, L"&Line"); // Line submenu nested to hLineMenu
    AppendMenuW(hLineMenu, MF_STRING, M_LINE_DDA, L"&DDA"); // Notice now we append to hLineMenu not hMenu
    AppendMenuW(hLineMenu, MF_STRING, M_LINE_MP, L"&Midpoint");
    AppendMenuW(hLineMenu, MF_STRING, M_LINE_PARAM, L"&Parametric");
    AppendMenuW(hMenu, MF_STRING | MF_POPUP, (UINT_PTR)hCircleMenu, L"&Circle"); // Circle submenu nested to hLineMenu
    AppendMenuW(hCircleMenu, MF_STRING, M_CIRCLE_DIRECT, L"&Direct"); // Notice now we append to hCircleMenu not hMenu
    AppendMenuW(hCircleMenu, MF_STRING, M_CIRCLE_POLAR, L"&Polar");
    AppendMenuW(hCircleMenu, MF_STRING, M_CIRCLE_ITER_POLAR, L"&Iterative Polar");
    AppendMenuW(hCircleMenu, MF_STRING, M_CIRCLE_MIDPOINT, L"&Midpoint");
    AppendMenuW(hCircleMenu, MF_STRING, M_CIRCLE_MIDPOINT_MODIFIED, L"&Midpoint modified");
    AppendMenuW(hMenu, MF_STRING | MF_POPUP, (UINT_PTR)hEllipseMenu, L"&Ellipse"); // Ellipse submenu nested to hLineMenu
    AppendMenuW(hEllipseMenu, MF_STRING, M_ELLIPSE_DIRECT, L"&Direct"); // Notice now we append to hEllipseMenu not hMenu
    AppendMenuW(hEllipseMenu, MF_STRING, M_ELLIPSE_POLAR, L"&Polar");
    AppendMenuW(hEllipseMenu, MF_STRING, M_ELLIPSE_MIDPOINT, L"&Midpoint");
    AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR)hMenu, L"&Menu");
    AppendMenuW(hMenu, MF_STRING, M_CARDINAL_SPLINE, L"&Cardinal Spline Curve");
    AppendMenuW(hMenu, MF_SEPARATOR, 0, NULL);
    AppendMenuW(hMenu, MF_STRING, M_FILL_SQR_HER, L"&Fill Square with Hermite curve");
    AppendMenuW(hMenu, MF_STRING, M_FILL_REC_BEZ, L"&Fill Rectangle with Bezier curve");
    AppendMenuW(hMenu, MF_STRING | MF_POPUP, (UINT_PTR)hFillCircleMenu, L"&Fill Circle with"); // Filled Circle submenu nested to hLineMenu
    AppendMenuW(hFillCircleMenu, MF_STRING, M_FILL_CIR_LINE, L"&Lines");
    AppendMenuW(hFillCircleMenu, MF_STRING, M_FILL_CIR_CIR, L"&Circles");
    AppendMenuW(hMenu, MF_STRING | MF_POPUP, (UINT_PTR)hFloodMenu, L"&Flood Fill"); // Flood fill submenu nested to hLineMenu
    AppendMenuW(hFloodMenu, MF_STRING, M_FLOODFILL_NORMAL, L"&Recursive Flood Fill"); // Notice now we append to hFloodMenu not hMenu
    AppendMenuW(hFloodMenu, MF_STRING, M_FLOODFILL_NONE, L"&Non-Recursive Flood Fill"); // Notice now we append to hFloodMenu not hMenu
    AppendMenuW(hMenu, MF_STRING | MF_POPUP, (UINT_PTR)hPolyFillMenu, L"&Polygon Fill");
    AppendMenuW(hPolyFillMenu, MF_STRING, M_CONVEX, L"&Convex Fill");
    AppendMenuW(hPolyFillMenu, MF_STRING, M_NON_CONVEX, L"&Non-Convex Fill");
    AppendMenuW(hMenu, MF_SEPARATOR, 0, NULL);
    AppendMenuW(hMenu, MF_STRING | MF_POPUP, (UINT_PTR)hRectClipping, L"&Rectangle Clipping");
    AppendMenuW(hRectClipping, MF_STRING, M_CLIP_RECT_POINT, L"&Point");
    AppendMenuW(hRectClipping, MF_STRING, M_CLIP_RECT_LINE, L"&Line");
    AppendMenuW(hRectClipping, MF_STRING, M_CLIP_RECT_POLYGON, L"&Polygon");
    AppendMenuW(hMenu, MF_STRING | MF_POPUP, (UINT_PTR)hSquClipping, L"&Square Clipping");
    AppendMenuW(hSquClipping, MF_STRING, M_CLIP_SQU_POINT, L"&Point");
    AppendMenuW(hSquClipping, MF_STRING, M_CLIP_SQU_LINE, L"&Line");
    AppendMenuW(hMenu, MF_STRING | MF_POPUP, (UINT_PTR)hCirClipping, L"&Circle Clipping");
    AppendMenuW(hCirClipping, MF_STRING, M_CLIP_CIR_POINT, L"&Point");
    AppendMenuW(hCirClipping, MF_STRING, M_CLIP_CIR_LINE, L"&Line");
    SetMenu(hwnd, hMenubar);
}