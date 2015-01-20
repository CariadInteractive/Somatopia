//
//  SoundWheel.h
//  Somatopia1
//
//  Created by James Bentley on 1/20/15.
//
//

#pragma once

#include "ofxState.h"
#include "SharedData.h"
#include "ofMain.h"

class SoundWheelState : public itg::ofxState<SharedData>, public ofBaseSoundInput
{
public:
    void setup();
    void update();
    void draw();
    void swap();
    void keyPressed(int key);
    void fillPage();
    string getName();
private:
    int photoIndex;
    ofColor col;
    ofImage fullImage;
    ofImage emptyImage;
    ofImage photos[10];
};