//
//  Button.h
//  example
//
//  Created by James Bentley on 1/5/15.
//
//

#pragma once

#include "ofMain.h"

class StateButton
{
public:
    void display();
    bool isInside(float x, float y);
    StateButton(int x, int y, int w, int h, string link);
    StateButton();
    int getX();
    int getY();
    int getW();
    int getH();
    string getLink();
    void setImage(string imageLink);
    void setCol(ofColor newCol);
private:
    int x, y, w, h;
    string link;
    ofImage img;
    ofColor(col);
    bool imgLoaded;
};


