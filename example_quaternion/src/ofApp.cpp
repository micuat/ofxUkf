#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ukf.init(0.001, 0.1);
}

//--------------------------------------------------------------
void ofApp::update(){
	m.makeIdentityMatrix();
	m.rotate(ofMap(mouseX, 0, ofGetWidth(), -180, 180), 1, 0, 0);
	m.rotate(ofMap(mouseY, 0, ofGetHeight(), -180, 180), 0, 1, 0);
	m.rotate(ofMap(ofGetElapsedTimef(), 0, 1, 0, 180), 0, 1, 1);
	
	ofQuaternion q;
	q = m.getRotate();
	
	ofVec3f euler = q.getEuler();
	for( int i = 0; i < 3; i++ ) {
		float rev = floorf((eulerPrev[i] + 180) / 360.f) * 360;
		euler[i] += rev;
		if( euler[i] < -90 + rev && eulerPrev[i] > 90 + rev ) euler[i] += 360;
		else if( euler[i] > 90 + rev && eulerPrev[i] < -90 + rev ) euler[i] -= 360;
	}
	
	ukf.update(euler);
	ofVec3f eulerPredicted = ukf.getEstimation();
	
	mPredicted.makeIdentityMatrix();
	mPredicted.rotate(eulerPredicted.x, 1, 0, 0);
	mPredicted.rotate(eulerPredicted.z, 0, 0, 1);
	mPredicted.rotate(eulerPredicted.y, 0, 1, 0);
	
	eulerPrev = euler;
	//ofLogWarning() << q;
	//ofLogWarning() << qPredicted;
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(54);
	
	cam.begin();
	ofPushMatrix();
	//ofTranslate(-100, 0, 0);
	glMultMatrixf((GLfloat*)m.getPtr());
	ofDrawAxis(100);
	ofPopMatrix();
	
	ofPushMatrix();
	//ofTranslate(100, 0, 0);
	glMultMatrixf((GLfloat*)mPredicted.getPtr());
	ofDrawAxis(200);
	ofPopMatrix();
	cam.end();
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
