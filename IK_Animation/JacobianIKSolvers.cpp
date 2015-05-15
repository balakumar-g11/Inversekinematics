#include "JacobianIKSolvers.h"


JacobianIKSolvers::JacobianIKSolvers()
{
}


JacobianIKSolvers::~JacobianIKSolvers()
{
}

ap::real_2d_array JacobianIKSolvers::getJacobian()
{
	ap::real_2d_array jacobian;
	jacobian.setbounds(1, 2, 1, _vecLinks.size());

	for (size_t col = 1; col <= _vecLinks.size(); col++)
	{
		jacobian(1, col) = 0.0f;
		jacobian(2, col) = 0.0f;
	}

	for (size_t col = 1; col <= _vecLinks.size(); col++)
	{
		float angle = 0;
		for (size_t i = 1; i <= _vecLinks.size(); i++)
		{
			angle += _vecLinks[i - 1]->_angle;
			if (i >= col)
			{
				jacobian(1, col) += (-_vecLinks[i - 1]->_length * sinf(angle));
				jacobian(2, col) += (_vecLinks[i - 1]->_length * cosf(angle));
			}
		}
	}

	return jacobian;
}
