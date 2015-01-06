//
//  Splash.cpp
//  example
//
//  Created by James Bentley on 1/5/15.
//
//

#include "SpaceState.h"

void SpaceState::update()
{
    
}

void SpaceState::draw()
{
    ofDrawBitmapString("Space is currently under development: press 's' to return the splash page",  0, 10);
}

string SpaceState::getName()
{
    return "space";
}

void SpaceState::mousePressed(int x, int y, int button)
{
    changeState("green");
}

void SpaceState::keyPressed(int key)
{
    if(key == 's')
    {
        changeState("splash");
    }
}