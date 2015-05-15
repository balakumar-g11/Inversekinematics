#pragma once
#include "JacobianIKSolvers.h"
class DlsIKSolver :
	public JacobianIKSolvers
{
public:
	DlsIKSolver();
	~DlsIKSolver();
	
	static int dampingVal;
private:
	void solve(float dx, float dy);
};
