/*
 https://github.com/micuat/ofxUkf
 
 Naoto Hieda <micuat@gmail.com> 2014
 */

#include "ofxUkfQuaternion.h"

using namespace math;

template <class T>
void ofxUkfQuaternion_<T>::init(T smoothness, T rapidness) {
	UKF<T>::n = 6;
	UKF<T>::m = 3;
	
	matrix<T> In(UKF<T>::n, UKF<T>::n); // nxn Identity Matrix
	for( int i = 0; i < UKF<T>::n; i++ ) {
		In(i, i) = 1;
	}
	matrix<T> Im(UKF<T>::m, UKF<T>::m); // mxm Identity Matrix
	for( int i = 0; i < UKF<T>::m; i++ ) {
		Im(i, i) = 1;
	}
	
	const T q = smoothness; //std of process. "smoothness". lower the value, smoother the curve
	const T r = rapidness; //std of measurement. "tracking". lower the value, faster the track
	UKF<T>::P = In; // state covariance
	UKF<T>::Q = (q * q) * In; // covariance of process	(size must be nxn)
	UKF<T>::R = (r * r) * Im; // covariance of measurement (size must be mxm)
	
	x = math::matrix<T>(UKF<T>::n, 1);
}

template <class T>
void ofxUkfQuaternion_<T>::update(const ofQuaternion& q) {
	ofVec3f rot;
	float angle;
	q.getRotate(angle, rot);
	
	matrix<T> z(3, 1);
	for( int i = 0; i < 3; i++ ) {
		z(i, 0) = rot[i] * angle;
	}
	UKF<T>::ukf(x, z);
}

template <class T>
ofQuaternion ofxUkfQuaternion_<T>::getEstimation()
{
	matrix<T> w = measurement_function(x);
	
	ofQuaternion q;
	ofVec3f axis(w(0, 0), w(1, 0), w(2, 0));
	float angle = axis.length();
	axis.normalize();
	q.makeRotate(angle, axis);
	
	return q;
}

template <class T>
matrix<T> ofxUkfQuaternion_<T>::state_function(matrix<T>& s)
{
	matrix<T> state(UKF<T>::n, 1);
	
	ofQuaternion q;
	ofVec3f axis(s(0, 0), s(1, 0), s(2, 0));
	float angle = axis.length();
	axis.normalize();
	q.makeRotate(angle, axis);
	
	ofQuaternion qd;
	ofVec3f axisd(s(3, 0), s(4, 0), s(5, 0));
	float angled = axisd.length();
	axisd.normalize();
	qd.makeRotate(angled, axisd);
	
	q = q * qd;
	
	q.getRotate(angle, axis);
	
	for( int i = 0; i < 3; i++ ) {
		state(i, 0) = axis[i] * angle;
	}
	
	// velocity
	for( int i = 0; i < 3; i++ ) {
		state(i + 3, 0) = s(i + 3, 0);
	}
	return state;
}

template <class T>
matrix<T> ofxUkfQuaternion_<T>::measurement_function(matrix<T>& m)
{
	matrix<T> measurement(3, 1);
	measurement = m;
	return measurement;
}

template class ofxUkfQuaternion_<double>;
