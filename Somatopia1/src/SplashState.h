//
//  Splash.h
//  example
//
//  Created by James Bentley on 1/5/15.
//
//
#pragma once

#include "ofxState.h"
#include "SharedData.h"
#include "StateButton.h"

class SplashState : public itg::ofxState<SharedData>
{
public:
    void setup();
    void update();
    void draw();
    void mousePressed(int x, int y, int button);
    string getName();
    
private:
    int offSet = ofGetWidth()/100;
    int buttonWidth = ofGetWidth()/2 - offSet*2;
    int buttonHeight = ofGetHeight()/4 - offSet*2;
    
    
    StateButton flow = StateButton(offSet, (int)ofGetHeight()/2 - offSet, buttonWidth, buttonHeight, "flow");
    StateButton cr = StateButton((int)ofGetWidth()/2, (int)ofGetHeight()/2 - offSet, buttonWidth, buttonHeight, "cr");
    StateButton rhythm = StateButton(offSet, (int)ofGetHeight()*3/4 - offSet, buttonWidth, buttonHeight, "rhythm");
    StateButton space = StateButton((int)ofGetWidth()/2, (int)ofGetHeight()*3/4 - offSet, buttonWidth, buttonHeight, "space");
    StateButton options = StateButton(offSet, offSet, buttonWidth/2, buttonHeight/2, "options");
};