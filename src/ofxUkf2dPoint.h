/*
 https://github.com/micuat/ofxUkf    

 Naoto Hieda <micuat@gmail.com> 2014
 */

#pragma once

#include <ofxUkf.h>

template <class T>
class ofxUkf2dPoint_ : public UKF<T> {
public:
	void init(T smoothness = 0.1, T rapidness = 0.1); // smaller is more smooth/rapid
	math::matrix<T> state_function(math::matrix<T>&);
	math::matrix<T> measurement_function(math::matrix<T>&);
};

typedef ofxUkf2dPoint_<double> ofxUkf2dPoint;
