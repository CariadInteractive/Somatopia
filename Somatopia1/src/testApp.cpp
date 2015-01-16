#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    // setup shared data
    //enable mouse a keyboard interaction (usually on by default)
    stateMachine.enableKeyEvents();
    stateMachine.enableMouseEvents();
    
    //Allocate space for our images
    stateMachine.getSharedData().colImg.allocate(320,240);
    stateMachine.getSharedData().grayImage.allocate(320,240);
    stateMachine.getSharedData().grayBg.allocate(320,240);
    stateMachine.getSharedData().grayDiff.allocate(320,240);
    
    //input our color pallete for the project
    stateMachine.getSharedData().pallete[0] = ofColor(232, 135, 57); //orange
    stateMachine.getSharedData().pallete[1] = ofColor(214, 38, 49); //red
    stateMachine.getSharedData().pallete[2] = ofColor(255, 213, 0); //yellow
    stateMachine.getSharedData().pallete[3] = ofColor(195, 229, 239); //lightBlue
    stateMachine.getSharedData().pallete[4] = ofColor(170, 203, 93); //green
    stateMachine.getSharedData().pallete[5] = ofColor(0, 122, 195); //darkBlue
    stateMachine.getSharedData().pallete[6] = ofColor(177, 84, 194); //purple
    
    //save the 4th color as the background color for reference later
    stateMachine.getSharedData().background = stateMachine.getSharedData().pallete[3];
    
    //turn off debug mode
    stateMachine.getSharedData().bDebugOn = false;
    
    //turn background learning on so the first frame the app recieves will be set as the background image
    stateMachine.getSharedData().bLearnBackground = true;
    
    //set the threshold for blob tracking
    stateMachine.getSharedData().threshold = 20.0f;
    
    //load font futura
    stateMachine.getSharedData().futura.loadFont("Futura.ttc", 32);
    
    //initialize our webcam
    stateMachine.getSharedData().cam.initGrabber(320, 240);
    
    //initialize our blob finder
    stateMachine.getSharedData().contourFinder.setMinAreaRadius(10);
    stateMachine.getSharedData().contourFinder.setMaxAreaRadius(150);
    stateMachine.getSharedData().contourFinder.setInvert(false);
    
    //set the background to our background
    ofBackground(stateMachine.getSharedData().background);
    
    // initialise state machine
    stateMachine.addState<SplashState>();
    stateMachine.addState<OptionsState>();
    stateMachine.addState<FlowState>();
    stateMachine.addState<CRState>();
    stateMachine.addState<SpaceState>();
    stateMachine.addState<RhythmState>();
    
    //set first state
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
    cout<<"Mouse Pressed in Test App"<<endl;
    
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