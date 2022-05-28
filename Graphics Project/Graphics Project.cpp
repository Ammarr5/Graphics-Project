#ifndef UNICODE
#define UNICODE
#endif // !UNICODE

#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLu.h>
#include <math.h>
#include <iostream>
#include "menu_items.h"
#include "Line.h"
#include "LineDrawerDDA.h"
#include "LineDrawerMidpoint.h"
#include "LineDrawerParametric.h"
#include <vector>

#pragma comment(lib,"opengl32")
#pragma comment(lib,"glu32")
using namespace std;

void populateMenus(HWND);
vector<Shape> shapes;

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
	static int points[2][2];
	static int i = 0;
    enum ShapeType{line};
    static ShapeType shapetype;
	switch (mcode)
	{
	case WM_CREATE:
		hdc = GetDC(hwnd);
		populateMenus(hwnd);
		glrc = InitOpenGl(hdc);
		break;
	case WM_SIZE:
		AdjustWindowFor2D(hdc, LOWORD(lp), HIWORD(lp));
		break;
	case WM_LBUTTONDOWN:
        if(shapetype==line) {
            Shape *line;
            points[i][0] = LOWORD(lp);
            points[i][1] = HIWORD(lp);
            i++;
            if (i == 2) {
                i = 0;
                line = new Line(points[0][0], points[0][1], points[1][0], points[1][1], (LineDrawer*) shapeDrawer);
                shapes.push_back(*line);
                glFlush();
            }
        }
		break;
	case WM_COMMAND: // When menu option is selected
		switch (LOWORD(wp)) { // switch for various menu options
            case M_WHITE_BG:
                cout << "white bg";
                break;
            case M_LINE_DDA:
                shapeDrawer = new LineDrawerDDA();
                shapetype = line;
                break;
            case M_LINE_MP:
                shapeDrawer = new LineDrawerMidpoint();
                shapetype = line;
                break;
            case M_LINE_PARAM:
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
                }
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

// function to add menus to window once created
void populateMenus(HWND hwnd) {

	HMENU hMenubar; // Strip that holds all menus (which is one in our case call "menu")
	HMENU hMenu;
	HMENU hLineMenu; // Line submenu

	hMenubar = CreateMenu();
	hMenu = CreateMenu();
	hLineMenu = CreateMenu();

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
	SetMenu(hwnd, hMenubar);
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