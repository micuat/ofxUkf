#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ukf.init(0.001, 0.1);
}

//--------------------------------------------------------------
void ofApp::update(){
	point = ofVec2f(mouseX, mouseY);
	line.addVertex(point);
	ukf.update(point);
	ofVec2f w = ukf.getEstimation();
	predicted.addVertex(w);
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0);
	ofSetColor(255);
	predicted.draw();
	ofDrawBitmapString("Prediction", 50, 50);
	
	ofSetColor(ofColor::red);
	line.draw();
	ofNoFill();
	ofCircle(point, 100);
	ofDrawBitmapString("Measurement", 50, 65);
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
