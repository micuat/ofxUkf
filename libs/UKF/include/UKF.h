
#include "matrix.h"

typedef math::matrix<double> Matrix;

class UKF {
public:		
	void ukf( Matrix& x, const Matrix z);
	virtual Matrix state_function (Matrix x) = 0;
	virtual Matrix measurement_function (Matrix x) = 0;

	int n;      //number of state
	int m;      //number of measurement
	Matrix Q;	//noise covariance of process	(size must be nxn)
	Matrix R;	//noise covariance of measurement (size must be mxm)
	Matrix P;	//state covariance
};
