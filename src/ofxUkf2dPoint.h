/*
 https://github.com/micuat/ofxUkf    

 Naoto Hieda <micuat@gmail.com> 2014
 */

#include <ofxUkf.h>

class ofxUkf2dPoint : public UKF {
public:
	void init(double smoothness = 0.1, double rapidness = 0.1); // smaller is more smooth/rapid
	Matrix state_function(Matrix);
	Matrix measurement_function(Matrix);
};
