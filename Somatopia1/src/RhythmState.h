//
//  Splash.h
//  example
//
//  Created by James Bentley on 1/5/15.
//
//
#pragma once

#include "ofxState.h"
#include "ofMain.h"
#include "SharedData.h"
#include "Ball.h"

class RhythmState : public itg::ofxState<SharedData>
{
public:
    void setup();
    void update();
    void draw();
    void mousePressed(int x, int y, int button);
    void keyPressed(int key);
    void mouseMoved(int x, int y );
    string getName();
private:
    Ball ball; //ball the bounces around
    int mouseX, mouseY; //mouse location (deprecated?)
};