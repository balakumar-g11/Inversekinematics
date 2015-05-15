#pragma once

#include "Link.h"
#include <vector>
#include "SVDCpp.h"
#include <glm/glm.hpp>

class IKSolver
{
public:
	IKSolver();

	virtual ~IKSolver();

	void addLink(Link2D* link);

	void draw();

	static void drawMaxArea();

	static void drawTarget();

	static void setTarget(glm::vec2& pos);

	virtual void update();

	static float _maxLength;

	static float _tolerance;

	static float _step;
protected:
	std::vector<Link2D*> _vecLinks;

	glm::vec2 _endEffPos = glm::vec2(0.0f, 0.0f);

	static glm::vec2 _targetPos;
	static glm::vec2 _userTargetPos;

	bool valuePrinted = false;

	virtual void solve(float dx, float dy) = 0;

	bool isTargetResolved();

	void printMatrix(ap::GeneralMatrix& matrix);

	void calcEndEffectorPos();
};
