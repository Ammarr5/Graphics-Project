#include "LineDrawerDDA.h"
#include "LineData.h"

#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLu.h>

#pragma comment(lib,"opengl32")
#pragma comment(lib,"glu32")


void swap1(int& x1, int& y1, int& x2, int& y2)
{
	int tmp = x1;
	x1 = x2;
	x2 = tmp;
	tmp = y1;
	y1 = y2;
	y2 = tmp;
}
int Round1(double x)
{
	return (int)(x + 0.5);
}

void LineDrawerDDA::draw(ShapeData* data) {
	LineData lData = *(LineData*)data;
	int x1 = lData.x1; int y1 = lData.y1; int x2 = lData.x2; int y2 = lData.y2;


	glBegin(GL_POINTS);
	glColor3f(1, 0, 0);
	int dx = x2 - x1;
	int dy = y2 - y1;
	if (abs(dy) <= abs(dx))
	{
		if (x1 > x2)swap1(x1, y1, x2, y2);
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
		if (y1 > y2)swap1(x1, y1, x2, y2);
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