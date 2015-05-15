#pragma once
#include "IKSolver.h"
class JacobianIKSolvers :
	public IKSolver
{
public:
	JacobianIKSolvers();
	~JacobianIKSolvers();
protected:
	ap::real_2d_array getJacobian();
};

