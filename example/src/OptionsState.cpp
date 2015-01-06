//
//  Splash.cpp
//  example
//
//  Created by James Bentley on 1/5/15.
//
//

#include "OptionsState.h"

void OptionsState::update()
{
    
}

void OptionsState::draw()
{
    ofDrawBitmapString("Options is currently under development: press 's' to return the splash page",  0, 10);
}

string OptionsState::getName()
{
    return "options";
}

void OptionsState::mousePressed(int x, int y, int button)
{
    changeState("green");
}

void OptionsState::keyPressed(int key)
{
    if(key == 's')
    {
        changeState("splash");
    }
}