/*
 https://github.com/micuat/ofxUkf
 
 Naoto Hieda <micuat@gmail.com> 2014
 */

#include "ofxUkfEuler.h"

using namespace math;

template <class T>
void ofxUkfEuler_<T>::init(T smoothness, T rapidness) {
	ofxUkfPoint_<T, 3>::init(smoothness, rapidness);
	eulerPrev.x = 0.f;
	eulerPrev.y = 0.f;
	eulerPrev.z = 0.f;
}

template <class T>
void ofxUkfEuler_<T>::update(const ofQuaternion& q) {
	// warp to appropriate dimension
	ofVec3f euler = q.getEuler();
	for( int i = 0; i < 3; i++ ) {
		float rev = floorf((eulerPrev[i] + 180) / 360.f) * 360;
		euler[i] += rev;
		if( euler[i] < -90 + rev && eulerPrev[i] > 90 + rev ) euler[i] += 360;
		else if( euler[i] > 90 + rev && eulerPrev[i] < -90 + rev ) euler[i] -= 360;
	}
	
	ofxUkfPoint_<T, 3>::update(euler);
	eulerPrev = euler;
}

template <class T>
ofQuaternion ofxUkfEuler_<T>::getEstimation()
{
	matrix<T> w = ofxUkfPoint_<T, 3>::measurement_function(x);
	ofVec4f p(0, 0, 0, 0);
	// copy w to p
	for( int i = 0; i < 3; i++ ) {
		p[i] = w(i, 0);
	}
	
	ofQuaternion q;
	q.set(0, 0, 0, 1);
	ofVec3f euler = ofxUkfPoint_<T, 3>::getEstimation();
	
	q.makeRotate(euler.x, ofVec3f(1, 0, 0), euler.z, ofVec3f(0, 0, 1), euler.y, ofVec3f(0, 1, 0));
	
	return q;
}

template class ofxUkfEuler_<double>;
