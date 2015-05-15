#pragma once

#include "JacobianIKSolvers.h"

class PinvIKSolver :
	public JacobianIKSolvers
{
public:
	PinvIKSolver(bool enableSec = false);
	~PinvIKSolver();
private:
	void solve(float dx, float dy);

	ap::GeneralMatrix addSecondaryTask(ap::GeneralMatrix& jacobian,
		ap::GeneralMatrix& jacobianInverse);
	
	bool _enableSecTask;
};
