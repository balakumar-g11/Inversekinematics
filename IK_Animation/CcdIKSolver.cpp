#include "CcdIKSolver.h"
#include <iostream>
#include <numeric>

CcdIKSolver::CcdIKSolver()
{
}

CcdIKSolver::~CcdIKSolver()
{
}

void CcdIKSolver::update()
{
	if (!isTargetResolved())
	{
		solve();

		calcEndEffectorPos();
	}
}

void CcdIKSolver::solve()
{
	for (int i = ((_vecLinks.size())-2); i >= 0; i--)
	{
		glm::vec2 curToEnd = _endEffPos - _vecLinks[i]->_pos;
		glm::vec2 curToTgt = _targetPos - _vecLinks[i]->_pos;

		float cosAngle = glm::dot(glm::normalize(curToEnd), glm::normalize(curToTgt));
		float sinAngle = (curToEnd.x*curToTgt.y - curToEnd.y * curToTgt.x) / (glm::length(curToEnd) * glm::length(curToTgt));

		if (cosAngle != cosAngle || 
			sinAngle != sinAngle || 
			cosAngle >= 0.999)
		{
			cosAngle = 1;
			sinAngle = 0;
		}

		
		float angle = acosf(cosAngle);

		if (sinAngle < 0)
			angle = -angle;

		_vecLinks[i]->_angle += angle;

		calcEndEffectorPos();
	}
} 