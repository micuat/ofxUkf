#pragma once

#include "matrix.h"

template <class T>
class UKF {
	math::matrix<T> sigmas(math::matrix<T>& x, math::matrix<T>& P, T c);
	math::matrix<T> Cholesky(math::matrix<T>& A);
public:
	void ukf( math::matrix<T>& x, const math::matrix<T>& z);
	virtual math::matrix<T> state_function (math::matrix<T>& x) = 0;
	virtual math::matrix<T> measurement_function (math::matrix<T>& x) = 0;
	
protected:
	int n;      //number of state
	int m;      //number of measurement
	math::matrix<T> Q;	//noise covariance of process	(size must be nxn)
	math::matrix<T> R;	//noise covariance of measurement (size must be mxm)
	math::matrix<T> P;	//state covariance
};
