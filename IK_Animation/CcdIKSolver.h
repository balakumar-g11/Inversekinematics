#pragma once
#include "IKSolver.h"
class CcdIKSolver :
	public IKSolver
{
public:
	CcdIKSolver();
	~CcdIKSolver();

	void update();
private:
	void solve();

	void solve(float dx, float dy){}
};
