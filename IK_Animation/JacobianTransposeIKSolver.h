#pragma once
#include "JacobianIKSolvers.h"
#include <Eigen/Dense>

class JacobianTransposeIKSolver :
	public JacobianIKSolvers
{
public:
	JacobianTransposeIKSolver();
	~JacobianTransposeIKSolver();
private:
	void solve(float dx, float dy);

	float calculateAlpha(Eigen::MatrixXf& jacobian, Eigen::VectorXf& posMat);
};
