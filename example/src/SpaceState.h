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

class SpaceState : public itg::ofxState<SharedData>
{
public:
    void update();
    void draw();
    void mousePressed(int x, int y, int button);
    void keyPressed(int key);
    string getName();
};
