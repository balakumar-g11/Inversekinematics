#include "JacobianTransposeIKSolver.h"

JacobianTransposeIKSolver::JacobianTransposeIKSolver()
{
}

JacobianTransposeIKSolver::~JacobianTransposeIKSolver()
{
}

void JacobianTransposeIKSolver::solve(float dx, float dy)
{
	Eigen::VectorXf dAngles = Eigen::VectorXf::Zero(_vecLinks.size(), 1);
	Eigen::VectorXf dPosition = Eigen::VectorXf(2, 1);

	dPosition(0) = dx;
	dPosition(1) = dy;

	ap::real_2d_array jacobian = getJacobian();

	size_t m = jacobian.gethighbound(1);
	size_t n = jacobian.gethighbound(2);

	Eigen::MatrixXf jacobianEigen = Eigen::MatrixXf::Zero(m, n);

	for (size_t i = 1; i <= m; i++)
	{
		for (size_t j = 1; j <= n; j++)
		{
			jacobianEigen(i - 1, j - 1) = jacobian(i, j);
		}
	}

	float alpha = calculateAlpha(jacobianEigen, dPosition);

	Eigen::MatrixXf solTemp = jacobianEigen.transpose() * dPosition;

	dAngles = solTemp * alpha;

	for (size_t i = 0; i < _vecLinks.size(); i++)
	{
		_vecLinks[i]->_angle += dAngles(i);
	}
}

float JacobianTransposeIKSolver::calculateAlpha(Eigen::MatrixXf& jacobian, Eigen::VectorXf& posMat)
{
	float alpha = 0;

	Eigen::MatrixXf jacTemp = jacobian * jacobian.transpose();

	Eigen::VectorXf vecTemp = jacTemp * posMat;

	float tempVal = powf(vecTemp.norm(), 2);

	alpha = posMat.dot(vecTemp) / tempVal;

	return alpha;
}