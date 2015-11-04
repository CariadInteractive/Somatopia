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

class SoundWheelState : public itg::ofxState<SharedData>
{
public:
    void setup();
    void stateEnter();
    void update();
    void draw();
    void swap();
    void keyPressed(int key);
    void mousePressed(int x, int y, int button);
    void fillPage();
    string getName();
private:
    int userIndex;
    ofColor col;
    ofImage fullImage;
    ofImage emptyImage;
};