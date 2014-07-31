/*
 https://github.com/micuat/ofxUkf    

 Naoto Hieda <micuat@gmail.com> 2014
 */

#include <ofxUkf2dPoint.h>

void ofxUkf2dPoint::init(double smoothness, double rapidness) {
	n = 4;
	m = 2;
	
	Matrix I4(n,n);	// 4x4 Identity Matrix
	I4(0,0) = 1;	I4(1,1) = 1;	I4(2,2) = 1;	I4(3,3) = 1;
	Matrix I2(m,m);	// 2x2 Identity Matrix
	I2(0,0) = 1;	I2(1,1) = 1;
	
	const double q=smoothness;	//std of process. "smoothness". lower the value, smoother the curve
	const double r=rapidness;	//std of measurement. "tracking". lower the value, faster the track
	P = I4;	// state covriance
	Q = (q*q) * I4;	// covariance of process	(size must be nxn)
	R = (r*r) * I2;	// covariance of measurement (size must be mxm)
}

Matrix ofxUkf2dPoint::state_function(Matrix s)
{
	Matrix state(4,1);
	state(0,0) = s(0,0)+s(2,0);	// x position in 2D point
	state(1,0) = s(1,0)+s(3,0);	// y position in 2D point
	state(2,0) = s(2,0);	// velocity in x
	state(3,0) = s(3,0);	// velocity in y
	return state;
}

Matrix ofxUkf2dPoint::measurement_function(Matrix m)
{
	Matrix measurement(2,1);
	measurement(0,0) = m(0,0);	// measured x position in 2D point
	measurement(1,0) = m(1,0);	// measured y position in 2D point
	return measurement;
}
