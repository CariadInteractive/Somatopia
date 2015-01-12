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
    int offSet;
    int buttonWidth;
    int buttonHeight;
    
    
    StateButton flow;
    StateButton cr;
    StateButton rhythm;
    StateButton space;
    StateButton options;
};