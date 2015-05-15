#pragma once

#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <cmath>

namespace ColorCodes{
	GLfloat trackableAreaColor[] = { 0.27, 0.24, 0.26, 1.0 };
	GLfloat pinvArmColor[] = { 0.772, 0.666, 0.960, 0.3 };
	GLfloat dlsArmColor[] = { 0.623, 0.007, 0.317, 0.3 };
	GLfloat ccdArmColor[] = { 0.925, 0.474, 0.603, 0.3 };
	GLfloat jtArmColor[] = { 0.960, 0.639, 0.321, 0.3 };
	GLfloat pinvSecTaskArmColor[] = { 0.772, 0.666, 0.960, 0.3 };
	GLfloat connectorColor[] = { 0.960, 0.639, 0.321, 0.3 };
	GLfloat targetColor[] = { 0.639, 0.796, 0.945, 0.5 };
}

void drawFilledCircle(float radius)
{
	int triangleCnt = radius;
	if (triangleCnt < 10)
		triangleCnt = 10;

	double twicePi = 2.0 * 3.14159265358979323846;
	float x = 0, y = 0;
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y);
	for (int i = 0; i <= triangleCnt; i++)   {
		glVertex2f((x + (radius * cosf(i * twicePi / triangleCnt))),
					(y + (radius * sinf(i * twicePi / triangleCnt))));
	}
	glEnd();
}

void drawFilledRectange(float width, float length)
{
	glBegin(GL_QUADS);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(length, 0.0f);
	glVertex2f(length, width);
	glVertex2f(0.0f, width);
	glEnd();
}
