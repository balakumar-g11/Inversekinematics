#include "DlsIKSolver.h"

int DlsIKSolver::dampingVal;

DlsIKSolver::DlsIKSolver()
{
}

DlsIKSolver::~DlsIKSolver()
{
}

void DlsIKSolver::solve(float dx, float dy)
{
	ap::real_2d_array dPosition;
	dPosition.setbounds(1, 2, 1, 1);

	dPosition(1, 1) = dx;
	dPosition(2, 1) = dy;

	ap::real_2d_array jacobian = getJacobian();

	ap::GeneralMatrix jacMat(2, _vecLinks.size(), jacobian);

	ap::GeneralMatrix jacTemp = jacMat.Multiply(jacMat.Transpose());

	size_t m = jacTemp.GetMatrix().gethighbound(1);
	size_t n = jacTemp.GetMatrix().gethighbound(2);

	ap::real_2d_array identity;
	identity.setbounds(1, m, 1, n);

	for (size_t i = 1; i <= m; i++)
	{
		for (size_t j = 1; j <= n; j++)
		{
			if (i == j)
				identity(i, j) = (dampingVal * dampingVal);
			else
				identity(i, j) = 0;
		}
	}

	ap::GeneralMatrix lambda(m, n, identity);

	jacTemp = jacTemp.Add(lambda);

	jacTemp = jacTemp.MatrixInverse();

	ap::GeneralMatrix dPos(2, 1, dPosition);

	jacTemp = jacTemp.Multiply(dPos);

	ap::GeneralMatrix dAnglesMat = jacMat.Transpose().Multiply(jacTemp);

	for (size_t i = 1; i <= _vecLinks.size(); i++)
	{
		_vecLinks[i - 1]->_angle += dAnglesMat.GetMatrix()(i, 1);
	}
}
