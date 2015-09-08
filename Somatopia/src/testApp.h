#pragma once

#include "ofMain.h"
#include "ofxStateMachine.h"
#include "SharedData.h"
#include "SplashState.h"
#include "FlowState.h"
#include "OptionsState.h"
#include "CRState.h"
#include "SpaceState.h"
#include "RhythmState.h"
#include "MirrorState.h"
#include "SoundWheelState.h"

class testApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void exit();
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
private:
    itg::ofxStateMachine<SharedData> stateMachine;

};
