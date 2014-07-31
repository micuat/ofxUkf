/*
 https://github.com/micuat/ofxUkf    

 Naoto Hieda <micuat@gmail.com> 2014
 */

#include <ofxUkf2dPoint.h>

using namespace math;

template <class T>
void ofxUkf2dPoint_<T>::init(T smoothness, T rapidness) {
	UKF<T>::n = 4;
	UKF<T>::m = 2;
	
	matrix<T> In(UKF<T>::n, UKF<T>::n); // 4x4 Identity Matrix
	In(0, 0) = 1;	In(1, 1) = 1;	In(2, 2) = 1;	In(3, 3) = 1;
	matrix<T> Im(UKF<T>::m, UKF<T>::m); // 2x2 Identity Matrix
	Im(0, 0) = 1;	Im(1, 1) = 1;
	
	const T q = smoothness; //std of process. "smoothness". lower the value, smoother the curve
	const T r = rapidness; //std of measurement. "tracking". lower the value, faster the track
	UKF<T>::P = In; // state covariance
	UKF<T>::Q = (q * q) * In; // covariance of process	(size must be nxn)
	UKF<T>::R = (r * r) * Im; // covariance of measurement (size must be mxm)
}

template <class T>
matrix<T> ofxUkf2dPoint_<T>::state_function(matrix<T>& s)
{
	matrix<T> state(4, 1);
	state(0, 0) = s(0, 0) + s(2, 0); // x position in 2D point
	state(1, 0) = s(1, 0) + s(3, 0); // y position in 2D point
	state(2, 0) = s(2, 0); // velocity in x
	state(3, 0) = s(3, 0); // velocity in y
	return state;
}

template <class T>
matrix<T> ofxUkf2dPoint_<T>::measurement_function(matrix<T>& m)
{
	matrix<T> measurement(2, 1);
	measurement(0, 0) = m(0, 0); // measured x position in 2D point
	measurement(1, 0) = m(1, 0); // measured y position in 2D point
	return measurement;
}

template class ofxUkf2dPoint_<double>;
