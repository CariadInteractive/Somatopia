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
    void keyPressed(int key);
    void mousePressed(int x, int y, int button);
    string getName();
    
private:
    int offSet; //offset value for button spacing
    int buttonWidth; //width of each state Button (not options)
    int buttonHeight; //height of the State Button (not options)
    
    /*state buttons*/
    StateButton flow;
    StateButton cr;
//    StateButton rhythm;
    StateButton soundWheel;
    StateButton space;
    StateButton options;
    StateButton mirror;
};