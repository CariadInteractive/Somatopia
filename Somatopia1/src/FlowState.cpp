//
//  Splash.cpp
//  example
//
//  Created by James Bentley on 1/5/15.
//
//

#include "FlowState.h"

void FlowState::update()
{
    
}

void FlowState::draw()
{
    ofDrawBitmapString("Flow is currently under development: press 's' to return the splash page",  0, 10);
}

string FlowState::getName()
{
    return "flow";
}

void FlowState::mousePressed(int x, int y, int button)
{
    changeState("green");
}

void FlowState::keyPressed(int key)
{
    if(key == 's')
    {
        changeState("splash");
    }
}