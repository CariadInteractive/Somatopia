#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    // setup shared data
    
    stateMachine.getSharedData().colImg.allocate(320,240);
    stateMachine.getSharedData().grayImage.allocate(320,240);
    stateMachine.getSharedData().grayBg.allocate(320,240);
    stateMachine.getSharedData().grayDiff.allocate(320,240);
//    stateMachine.getSharedData().colImg.allocate(320, 240, OF_IMAGE_COLOR);
//    stateMachine.getSharedData().greyImg.allocate(320, 240, OF_IMAGE_GRAYSCALE);
//    stateMachine.getSharedData().greyBgImg.allocate(320, 240, OF_IMAGE_GRAYSCALE);
//    stateMachine.getSharedData().greyDiffImg.allocate(320, 240, OF_IMAGE_GRAYSCALE);
    
    stateMachine.getSharedData().pallete[0] = ofColor(232, 135, 57); //orange
    stateMachine.getSharedData().pallete[1] = ofColor(214, 38, 49); //red
    stateMachine.getSharedData().pallete[2] = ofColor(255, 213, 0); //yellow
    stateMachine.getSharedData().pallete[3] = ofColor(195, 229, 239); //lightBlue
    stateMachine.getSharedData().pallete[4] = ofColor(170, 203, 93); //green
    stateMachine.getSharedData().pallete[5] = ofColor(0, 122, 195); //darkBlue
    stateMachine.getSharedData().pallete[6] = ofColor(177, 84, 194); //purple
    
    stateMachine.getSharedData().background = stateMachine.getSharedData().pallete[3];
    
    stateMachine.getSharedData().bDebugOn = false;
    stateMachine.getSharedData().bLearnBackground = true;
    
    stateMachine.getSharedData().threshold = 20.0f;
        
    stateMachine.getSharedData().futura.loadFont("Futura.ttc", 32);
    
    stateMachine.getSharedData().cam.initGrabber(320, 240);
    
    stateMachine.getSharedData().contourFinder.setMinAreaRadius(10);
    stateMachine.getSharedData().contourFinder.setMaxAreaRadius(150);
    stateMachine.getSharedData().contourFinder.setInvert(false);
    
    ofBackground(stateMachine.getSharedData().background);
    
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