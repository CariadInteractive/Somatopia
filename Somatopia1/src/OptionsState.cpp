//
//  Splash.cpp
//  example
//
//  Created by James Bentley on 1/5/15.
//
//

#include "OptionsState.h"

using namespace ofxCv;
using namespace cv;

void OptionsState::update() {
    
    getSharedData().cam.update();
    
}

void OptionsState::draw() {
    ofSetColor(255);
    getSharedData().cam.draw(0, 0, ofGetWidth()/2, ofGetHeight());
}

void OptionsState::keyPressed(int key) {
    if(key == 's') {
        changeState("splash");
    }
}

string OptionsState::getName() {
    return "options";
}