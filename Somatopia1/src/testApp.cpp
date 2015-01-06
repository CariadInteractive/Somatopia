#include "testApp.h"

using namespace ofxCv;
using namespace cv;

//--------------------------------------------------------------
void testApp::setup(){
    // setup shared data

    stateMachine.getSharedData().colorImg.allocate(320,240);
    stateMachine.getSharedData().grayImage.allocate(320,240);
    stateMachine.getSharedData().grayBg.allocate(320,240);
    stateMachine.getSharedData().grayDiff.allocate(320,240);
    
    stateMachine.getSharedData().bDebugOn = false;
    stateMachine.getSharedData().bLearnBackground = true;
    
    stateMachine.getSharedData().threshold = 20.0f;
        
    stateMachine.getSharedData().futura.loadFont("Futura.ttc", 32);
    
    stateMachine.getSharedData().cam.initGrabber(320, 240);
    
    stateMachine.getSharedData().contourFinder.setMinAreaRadius(10);
    stateMachine.getSharedData().contourFinder.setMaxAreaRadius(150);
    stateMachine.getSharedData().contourFinder.setInvert(false);
    
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