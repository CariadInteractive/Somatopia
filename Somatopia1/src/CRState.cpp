//
//  Splash.cpp
//  example
//
//  Created by James Bentley on 1/5/15.
//
//

#include "CRState.h"

void CRState::setup()
{
    
}

void CRState::update()
{
    
}

void CRState::draw()
{
    ofDrawBitmapString("Call & Responce is currently under development: press 's' to return the splash page", 0, 10);
}

string CRState::getName()
{
    return "cr";
}

void CRState::mousePressed(int x, int y, int button)
{
    changeState("splash");
}

void CRState::keyPressed(int key)
{
    if(key == 's')
    {
        changeState("splash");
    }
}