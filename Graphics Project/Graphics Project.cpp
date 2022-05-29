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
#include "CardinalSpline.h"
#include "LineDrawerDDA.h"
#include "LineDrawerMidpoint.h"
#include "LineDrawerParametric.h"
#include <vector>

#pragma comment(lib,"opengl32")
#pragma comment(lib,"glu32")
using namespace std;

struct Point{
    int x,y;
};

void populateMenus(HWND);
string browseFile(bool);
vector<Shape*> shapes;

template<typename Base, typename T>
inline bool instanceof(const T *ptr) {
    return dynamic_cast<const Base*>(ptr) != nullptr;
}

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
    static COLORREF color = RGB(1, 1, 0);
	static Point points[2];
	static int i = 0;
    enum ShapeType{line,cardinalspline, none_selected};
    static ShapeType shapetype = none_selected;
    const int numberOfSplinePoints=8;
    static Vector p[numberOfSplinePoints];
	switch (mcode)
	{
    case WM_SETCURSOR:{
//        HCURSOR cursor = LoadCursorFromFileA("c2.cur");
//        SetCursor(cursor);
        SetCursor(LoadCursor(NULL, IDC_SIZEALL));
        break;}
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
            i++;
            if (i == 2) {
                i = 0;
                Shape *line;
                LineDrawer* ld = (LineDrawerDDA*)shapeDrawer;
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
            else i++;
        }
		break;
    }
	case WM_COMMAND: // When menu option is selected
		switch (LOWORD(wp)) { // switch for various menu options
            case M_WHITE_BG:
                cout << "white bg";
                break;
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
            case M_COLOR:
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
            case M_SAVE:{
                string path = browseFile(true);
                if (path == ""){break;}
                ofstream ofile;
                ofile.open(path);
                for(Shape* shape : shapes) {
                    cout<<instanceof<Line>(shape)<<endl;
                }
                break;}
            case M_LOAD:
                string path = browseFile(false);
                if (path == ""){break;}
                char data[100];
                ifstream infile;
                infile.open(path);

                cout << "Reading from the file" << endl;
                infile.getline(&data[0], 100);

                // write the data at the screen.
                cout << data << endl;
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

// function to add menus to window once created
void populateMenus(HWND hwnd) {

    HMENU hMenubar; // Strip that holds all menus (which is one in our case call "menu")
    HMENU hMenu;
    HMENU hLineMenu; // Line submenu
    HMENU hRectClipping; // Rectangle Clipping submenu
    HMENU hSquClipping; // Square Clipping submenu
    HMENU hCirClipping; // Circle Clipping submenu

    hMenubar = CreateMenu();
    hMenu = CreateMenu();
    hLineMenu = CreateMenu();
    hRectClipping = CreateMenu();
    hSquClipping = CreateMenu();
    hCirClipping = CreateMenu();

    AppendMenuW(hMenu, MF_STRING, M_SAVE, L"&Save");
    AppendMenuW(hMenu, MF_STRING, M_LOAD, L"&Load");
    AppendMenuW(hMenu, MF_SEPARATOR, 0, NULL);
    AppendMenuW(hMenu, MF_STRING, M_COLOR, L"&Select Color");
    AppendMenuW(hMenu, MF_STRING, M_WHITE_BG, L"&White Background");
    AppendMenuW(hMenu, MF_STRING, M_CLEAR_SCREEN, L"&Clear Screen");
    AppendMenuW(hMenu, MF_STRING | MF_POPUP, (UINT_PTR)hLineMenu, L"&Line"); // Line submenu nested to hLineMenu
    AppendMenuW(hLineMenu, MF_STRING, M_LINE_DDA, L"&DDA"); // Notice now we append to hLineMenu not hMenu
    AppendMenuW(hLineMenu, MF_STRING, M_LINE_MP, L"&Midpoint");
    AppendMenuW(hLineMenu, MF_STRING, M_LINE_PARAM, L"&Parametric");
    AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR)hMenu, L"&Menu");
    AppendMenuW(hMenu, MF_STRING, M_CARDINAL_SPLINE, L"&Cardinal Spline Curve");
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