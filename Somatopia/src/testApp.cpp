#include "testApp.h"

using namespace ofxCv;
using namespace cv;

//--------------------------------------------------------------
void testApp::setup(){
    // setup shared data
    
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofSetLogLevel("ofThread", OF_LOG_ERROR);
    
    stateMachine.enableKeyEvents();
    stateMachine.enableMouseEvents();
    
    stateMachine.getSharedData().camWidth = 320;
    stateMachine.getSharedData().camHeight = 240;
    
    stateMachine.getSharedData().wheelCount = 0;
    
    stateMachine.getSharedData().bIsCursorHidden = false;
    
    stateMachine.getSharedData().nameFutura.loadFont("Futura.ttc", 128);
    
    stateMachine.getSharedData().setupCamera(320, 240);
    
//    stateMachine.getSharedData().cam.setup(stateMachine.getSharedData().camWidth, stateMachine.getSharedData().camHeight, true);
    
    stateMachine.getSharedData().performanceOn = false;
    
//    stateMachine.getSharedData().frame = toCv(stateMachine.getSharedData().colImg);
    
    //input our color pallete for the project
    stateMachine.getSharedData().pallete[0] = ofColor(232, 135, 57); //orange
    stateMachine.getSharedData().pallete[1] = ofColor(214, 38, 49); //red
    stateMachine.getSharedData().pallete[2] = ofColor(255, 213, 0); //yellow
    stateMachine.getSharedData().pallete[3] = ofColor(195, 229, 239); //lightBlue
    stateMachine.getSharedData().pallete[4] = ofColor(170, 203, 93); //green
    stateMachine.getSharedData().pallete[5] = ofColor(0, 122, 195); //darkBlue
    stateMachine.getSharedData().pallete[6] = ofColor(177, 84, 194); //purple
    stateMachine.getSharedData().pallete[7] = ofColor(255, 255, 255); //white
    stateMachine.getSharedData().pallete[8] = ofColor(127, 127, 127); //grey
    stateMachine.getSharedData().pallete[9] = ofColor(248, 200, 212); //pink
    
    //load images we are going to use
    stateMachine.getSharedData().images[0].loadImage("Circle.png");
    stateMachine.getSharedData().images[1].loadImage("Cross.png");
    stateMachine.getSharedData().images[2].loadImage("Heart.png");
    stateMachine.getSharedData().images[3].loadImage("Hexagon.png");
    stateMachine.getSharedData().images[4].loadImage("Square.png");
    stateMachine.getSharedData().images[5].loadImage("Triangle.png");
    stateMachine.getSharedData().images[6].loadImage("Asterix.png");
    
    stateMachine.getSharedData().emptyImages[0].loadImage("Circle_rev.png");
    stateMachine.getSharedData().emptyImages[1].loadImage("Cross_rev.png");
    stateMachine.getSharedData().emptyImages[2].loadImage("Heart_rev.png");
    stateMachine.getSharedData().emptyImages[3].loadImage("Hexagon_rev.png");
    stateMachine.getSharedData().emptyImages[4].loadImage("Square_rev.png");
    stateMachine.getSharedData().emptyImages[5].loadImage("Triangle_rev.png");
    stateMachine.getSharedData().emptyImages[6].loadImage("Asterix_rev.png");
    
    ofxJSONElement json;
    
    std::string file = "Users.json";
    bool parsingSuccessful = json.open(file);
    if(parsingSuccessful) {
        ofLogNotice("SoundWheelState::setup") << json.getRawString(true);
        for(int i = 0; i < json["Users"].size(); i++) {
            ofImage portrait;
            portrait.allocate(560, 373, OF_IMAGE_COLOR);
            bool loaded = portrait.loadImage("portraits/"+json["Users"][i]["name"].asString()+".jpg");
            if(!loaded) cout<<"unable to load portrait for "<< json["Users"][i]["name"].asString() << ", ensure your file has a .jpg extension and the name of the file matches the name in Users.json" << endl;
            else cout<<"portrait for "<<json["Users"][i]["name"].asString()<<" loaded successfully"<<endl;
            stateMachine.getSharedData().tmpUser;
            stateMachine.getSharedData().tmpUser.imageIndex = stateMachine.getSharedData().mapShape(json["Users"][i]["shape"].asString());
            stateMachine.getSharedData().tmpUser.portrait = portrait;
            stateMachine.getSharedData().tmpUser.colIndex = stateMachine.getSharedData().mapColor(json["Users"][i]["color"].asString());
            stateMachine.getSharedData().tmpUser.name = json["Users"][i]["name"].asString();
            stateMachine.getSharedData().users.push_back(stateMachine.getSharedData().tmpUser);
        }
    }
    
    std::string settingsFile = "Settings.json";
    parsingSuccessful = json.open(settingsFile);
    if(parsingSuccessful) {
        stateMachine.getSharedData().soundDeviceId = json["soundDeviceId"].asInt();
    }
    
    stateMachine.getSharedData().background = stateMachine.getSharedData().pallete[3];
    
    stateMachine.getSharedData().bDebugOn = false;
    stateMachine.getSharedData().bLearnBackground = true;
    
    stateMachine.getSharedData().threshold = 20.0f;
        
    stateMachine.getSharedData().futura.loadFont("Futura.ttc", 32);
    
    stateMachine.getSharedData().contourFinder.setMinAreaRadius(10);
    stateMachine.getSharedData().contourFinder.setMaxAreaRadius(stateMachine.getSharedData().camWidth/2);
    stateMachine.getSharedData().contourFinder.setInvert(false);
    
    ofBackground(stateMachine.getSharedData().background);
    
    stateMachine.getSharedData().micSensitivity.set(0.7);
    
    // initialise state machine
    stateMachine.addState<SplashState>();
    stateMachine.addState<OptionsState>();
    stateMachine.addState<FlowState>();
    stateMachine.addState<CRState>();
    stateMachine.addState<SpaceState>();
    stateMachine.addState<SoundWheelState>();
    stateMachine.addState<MirrorState>();
    
    stateMachine.changeState("splash");
}

//--------------------------------------------------------------
void testApp::update(){
    
}

void testApp::exit() {
//    if(stateMachine.getSharedData().threadedObject.isThreadRunning()) stateMachine.getSharedData().threadedObject.stop();
    
    cout<<"stopping"<<endl;
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
    cout<<"Mouse Pressed in testApp!"<<endl;
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