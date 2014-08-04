/*
 https://github.com/micuat/ofxUkf    

 Naoto Hieda <micuat@gmail.com> 2014
 */

#pragma once

#include "ofxUkf.h"
#include "ofxUkfPoint.h"

template <class T>
class ofxUkfEuler_ : public ofxUkfPoint_<T, 3> {
	math::matrix<T> x;
	ofVec3f eulerPrev; // used for finding appropriate dimension
public:
	void init(T smoothness = 0.1, T rapidness = 0.1); // smaller is more smooth/rapid
	void update(const ofQuaternion&);
	ofQuaternion getEstimation();
	
};

typedef ofxUkfEuler_<double> ofxUkfEuler;
