#pragma once

#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <glm/glm.hpp>

#define piVal 3.14159265358979323846
#define degree(x) x * 180/piVal

class Link2D
{
public:
	Link2D(GLfloat c[])
	{
		_obj = gluNewQuadric();
		gluQuadricDrawStyle(_obj, GLU_FILL);
		gluQuadricOrientation(_obj, GLU_OUTSIDE);
		gluQuadricNormals(_obj, GLU_SMOOTH);
		_color[0] = c[0];
		_color[1] = c[1];
		_color[2] = c[2];
		_color[3] = c[3];
	}

	GLfloat _color[4];
	float _length;
	float _angle;
	GLUquadricObj* _obj;
	glm::vec2 _pos;
};
