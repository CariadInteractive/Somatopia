//
//  Splash.cpp
//  example
//
//  Created by James Bentley on 1/5/15.
//
//

#include "RhythmState.h"

void RhythmState::update()
{
    
}

void RhythmState::draw()
{
    ofDrawBitmapString("Rhythm is currently under development: press 's' to return the splash page",  0, 10);
}

string RhythmState::getName()
{
    return "rhythm";
}

void RhythmState::mousePressed(int x, int y, int button)
{
    changeState("green");
}

void RhythmState::keyPressed(int key)
{
    if(key == 's')
    {
        changeState("splash");
    }
}