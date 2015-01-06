#include "testApp.h"
#include "SplashState.h"
#include "FlowState.h"
#include "OptionsState.h"
#include "CRState.h"
#include "SpaceState.h"
#include "RhythmState.h"


//--------------------------------------------------------------
void testApp::setup(){
    
	// setup shared data
    stateMachine.getSharedData().futura.loadFont("Futura.ttc", 32);
    ofBackground(195, 229, 239);
    
	// initialise state machine
    stateMachine.addState<SplashState>();
    stateMachine.addState<OptionsState>();
    stateMachine.addState<FlowState>();
    stateMachine.addState<CRState>();
    stateMachine.addState<SpaceState>();
    stateMachine.addState<RhythmState>();

	stateMachine.changeState("splash");
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    ofSetColor(0, 0, 0);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}