//
//  Button.cpp
//  example
//
//  Created by James Bentley on 1/5/15.
//
//
#include "StateButton.h"

StateButton::StateButton(int x, int y, int w, int h, string link) :
x (x),
y (y),
w (w),
h (h),
link (link)
{ }

StateButton::StateButton()
{
    x = 0;
    y = 0;
    w = 0;
    h = 0;
    link = "null";
}

void StateButton::display()
{
    ofSetColor(255);
    ofFill();
    img.draw(x, y, w, h);
}

bool StateButton::isInside(float xVal, float yVal)
{
    if((xVal < x + w && xVal > x) && (yVal < y + h && yVal > y)) return true;
    else return false;
}

int StateButton::getX()
{
    return x;
}

int StateButton::getY()
{
    return y;
}

int StateButton::getW()
{
    return w;
}

int StateButton::getH()
{
    return h;
}

string StateButton::getLink()
{
    return link;
}

void StateButton::setImage(string imageLink)
{
    img.loadImage(imageLink);
}



