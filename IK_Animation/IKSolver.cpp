#include "IKSolver.h"
#include <cmath>
#include <iostream>
#include "GLHelper.h"

glm::vec2 IKSolver::_targetPos = glm::vec2(10.0f, 10.0f);
glm::vec2 IKSolver::_userTargetPos = glm::vec2(10.0f, 10.0f);
float IKSolver::_maxLength = 0.0f;

float IKSolver::_step;
float IKSolver::_tolerance;

IKSolver::IKSolver()
{
}

IKSolver::~IKSolver()
{
}

void IKSolver::addLink(Link2D* link)
{
	_vecLinks.push_back(link);
	calcEndEffectorPos();
}

void IKSolver::calcEndEffectorPos()
{
	float angle = 0.0f;
	glm::vec2 pos(0.0f, 0.0f);

	for (auto i : _vecLinks)
	{
		angle += i->_angle;

		float cosAngle = cosf(angle);
		float sinAngle = cosf(angle);

		pos.x += i->_length * cosf(angle);
		pos.y += i->_length * sinf(angle);
		i->_pos = pos;
	}

	_endEffPos = pos;
}

void IKSolver::printMatrix(ap::GeneralMatrix& matrix)
{
	int m = matrix.GetMatrix().gethighbound(1);
	int n = matrix.GetMatrix().gethighbound(2);

	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			std::cout << matrix.GetMatrix()(i, j) << "\t";
		}
		std::cout << std::endl;
	}
}

bool IKSolver::isTargetResolved()
{
	if (glm::distance(_endEffPos, _targetPos) <= _tolerance)
		return true;

	return false;
}

void IKSolver::update()
{
	if (!isTargetResolved())
	{
		float x = (_targetPos.x - _endEffPos.x > 1) ? _step : -_step;
		float y = (_targetPos.y - _endEffPos.y > 1) ? _step : -_step;

		solve(x, y);

		calcEndEffectorPos();
	}
}

void IKSolver::setTarget(glm::vec2& pos)
{
	_userTargetPos = pos;
	float distance = glm::length(pos);

	_targetPos = pos;

	if (distance > (_maxLength))
	{
		_targetPos = glm::normalize(_targetPos) * _maxLength;
	}
}

void IKSolver::draw()
{
	
	glColor4fv(ColorCodes::connectorColor);
	drawFilledCircle(30.0f);

	glPushMatrix();

	for (auto i : _vecLinks)
	{
		glRotatef(degree(i->_angle), 0.0f, 0.0f, 1.0f);
		glColor4fv(i->_color);
		drawFilledRectange(15.0f, (i->_length - 7.5f));
		glTranslatef((i->_length - 7.5f), 7.5f, 0.0f);
		glColor4fv(i->_color);
		drawFilledCircle(15.0f);
		glTranslatef(7.5f, -7.5f, 0.0f);
	}

	glPopMatrix();
}

void IKSolver::drawMaxArea()
{
	glPushMatrix();
	glColor4fv(ColorCodes::trackableAreaColor);
	drawFilledCircle(_maxLength);
	glPopMatrix();
}

void IKSolver::drawTarget()
{
	glPushMatrix();
	glColor4fv(ColorCodes::targetColor);
	glTranslatef(_userTargetPos.x, _userTargetPos.y, 0.0f);
	drawFilledCircle(20.0f);
	glPopMatrix();
}
