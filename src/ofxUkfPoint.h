/*
 https://github.com/micuat/ofxUkf    

 Naoto Hieda <micuat@gmail.com> 2014
 */

#pragma once

#include "ofxUkf.h"

template <class T, int D>
class ofxUkfPoint_ : public UKF<T> {
	math::matrix<T> x;
public:
	void init(T smoothness = 0.1, T rapidness = 0.1); // smaller is more smooth/rapid
	void update(const ofVec4f&);
	ofVec4f getEstimation();
	
	math::matrix<T> state_function(math::matrix<T>&);
	math::matrix<T> measurement_function(math::matrix<T>&);
};

typedef ofxUkfPoint_<double, 2> ofxUkfPoint2d;
typedef ofxUkfPoint_<double, 3> ofxUkfPoint3d;
