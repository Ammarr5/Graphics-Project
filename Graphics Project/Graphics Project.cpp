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

#pragma comment(lib,"opengl32")
#pragma comment(lib,"glu32")
using namespace std;

void populateMenus(HWND);

void swap(int& x1, int& y1, int& x2, int& y2)
{
	int tmp = x1;
	x1 = x2;
	x2 = tmp;
	tmp = y1;
	y1 = y2;
	y2 = tmp;
}
int Round(double x)
{
	return (int)(x + 0.5);
}

// These methods were provided on blackboard, I left them as an opengl example (will be implemented inside classes later)
void DrawLine1(int x1, int y1, int x2, int y2)
{
	glBegin(GL_POINTS);
	glColor3f(1, 0, 0);
	int dx = x2 - x1;
	int dy = y2 - y1;
	if (abs(dy) <= abs(dx))
	{
		if (x1 > x2)swap(x1, y1, x2, y2);
		glVertex2d(x1, y1);
		int x = x1;
		while (x < x2)
		{
			x++;
			double y = y1 + (double)(x - x1)*dy / dx;
			glVertex2d(x, y);
		}
	}
	else {
		if (y1 > y2)swap(x1, y1, x2, y2);
		glVertex2d(x1, y1);
		int y = y1;
		while (y < y2)
		{
			y++;
			double x = x1 + (double)(y - y1)*dx / dy;
			glVertex2d(x, y);
		}
	}
	glEnd();
	glFlush();
}
void Draw8Points(int xc, int yc, int x, int y)
{
	glVertex2d(xc + x, yc + y);
	glVertex2d(xc + x, yc - y);
	glVertex2d(xc - x, yc - y);
	glVertex2d(xc - x, yc + y);
	glVertex2d(xc + y, yc + x);
	glVertex2d(xc + y, yc - x);
	glVertex2d(xc - y, yc - x);
	glVertex2d(xc - y, yc + x);
}
void DrawCircle1(int xc, int yc, int R)
{
	glBegin(GL_POINTS);
	glColor3f(0, 0, 1);
	int x = 0;
	double y = R;
	Draw8Points(xc, yc, 0, R);
	while (x < y)
	{
		x++;
		y = sqrt((double)R*R - x * x);
		Draw8Points(xc, yc, x, Round(y));
	}
	glEnd();
	glFlush();
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
	static int points[2][2];
	static int i = 0;
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
		//DrawCircle1(LOWORD(lp), HIWORD(lp), 100);
		points[i][0] = LOWORD(lp);
		points[i][1] = HIWORD(lp);
		i++;
		if (i == 2) {
			i = 0;
			new Line(points[0][0], points[0][1], points[1][0], points[1][1], new LineDrawerDDA());
		}
		glFlush();
		break;
	case WM_COMMAND: // When menu option is selected
		switch (LOWORD(wp)) { // switch for various menu options
		case M_WHITE_BG:
			cout << "PAAM!! white bg bom el takh";
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