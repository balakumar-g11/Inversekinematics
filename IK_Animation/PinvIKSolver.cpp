#include "PinvIKSolver.h"

PinvIKSolver::PinvIKSolver(bool enableSec)
{
	_enableSecTask = enableSec;
}

PinvIKSolver::~PinvIKSolver()
{
}

void PinvIKSolver::solve(float dx, float dy)
{
	ap::real_2d_array dPosition;
	dPosition.setbounds(1, 2, 1, 1);

	dPosition(1, 1) = dx;
	dPosition(2, 1) = dy;

	ap::real_2d_array jacobian = getJacobian();

	ap::GeneralMatrix jacMat(2, _vecLinks.size(), jacobian);

	ap::GeneralMatrix pinv = jacMat.MatrixInverse();

	ap::GeneralMatrix dPos(2, 1, dPosition);

	ap::GeneralMatrix dAnglesMat = (pinv.Multiply(dPos));

	if (_enableSecTask)
		dAnglesMat = dAnglesMat.Add(addSecondaryTask(jacMat, pinv));

	for (size_t i = 1; i <= _vecLinks.size(); i++)
	{
		_vecLinks[i - 1]->_angle += dAnglesMat.GetMatrix()(i, 1);
	}
}

ap::GeneralMatrix PinvIKSolver::addSecondaryTask(ap::GeneralMatrix& jacobian, ap::GeneralMatrix& jacobianInverse)
{
	ap::GeneralMatrix secTaskVal = jacobianInverse.Multiply(jacobian);

	size_t m = secTaskVal.GetMatrix().gethighbound(1);
	size_t n = secTaskVal.GetMatrix().gethighbound(2);

	ap::real_2d_array identity;
	identity.setbounds(1, m, 1, n);

	for (size_t i = 1; i <= m; i++)
	{
		for (size_t j = 1; j <= n; j++)
		{
			if (i == j)
				identity(i, j) = 1;
			else
				identity(i, j) = 0;
		}
	}

	ap::real_2d_array secondaryTask;
	secondaryTask.setbounds(1, n, 1, 2);

	for (size_t i = 1; i <= n; i++)
	{
		secondaryTask(i, 1) = 0;
		secondaryTask(i, 2) = piVal / 3;
	}

	ap::GeneralMatrix IdentityMatrix(m, n, identity);
	secTaskVal = IdentityMatrix.Subtract(secTaskVal);

	ap::GeneralMatrix SecondaryMatrix(n, 1, secondaryTask);

	secTaskVal = secTaskVal.Multiply(SecondaryMatrix);

	return secTaskVal;
}