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

class OptionsState : public itg::ofxState<SharedData>
{
public:
    void update();
    void draw();
    void keyPressed(int key);
    string getName();
};