#include "ofApp.h"
//#include "SplashState.h"
//#include "FlowState.h"
//#include "OptionsState.h"
#include "CRState.h"
//#include "SpaceState.h"
//#include "RhythmState.h"


//--------------------------------------------------------------
void ofApp::setup(){
    
    // setup shared data
    stateMachine.getSharedData().futura.loadFont("Futura.ttc", 32);
    ofBackground(195, 229, 239);
    
    // initialise state machine
    //stateMachine.addState<SplashState>();
    //stateMachine.addState<OptionsState>();
    //stateMachine.addState<FlowState>();
    stateMachine.addState<CRState>();
    //stateMachine.addState<SpaceState>();
    //stateMachine.addState<RhythmState>();
    
    stateMachine.changeState("cr");
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(0, 0, 0);
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