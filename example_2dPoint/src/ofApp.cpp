#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ukf.init(0.1, 0.1);
	x = Matrix(4, 1);
}

//--------------------------------------------------------------
void ofApp::update(){
	Matrix z(2, 1);
	z(0, 0) = mouseX;
	z(1, 0) = mouseY;
	point = ofVec2f(z(0, 0), z(1, 0));
	line.addVertex(point);
	ukf.ukf(x, z);
	Matrix w = ukf.measurement_function(x);
	predicted.addVertex(ofVec2f(w(0, 0), w(1, 0)));
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0);
	ofSetColor(255);
	line.draw();
	ofSetColor(ofColor::red);
	predicted.draw();
	ofNoFill();
	ofCircle(point, 100);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
