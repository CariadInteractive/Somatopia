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
    int x, y, w, h; //location and size of button
    string link; //name of the state that this links to
    ofImage img; //image to be displayed (optional)
    ofColor(col); //color to be displayed (overwritten by image)
    bool imgLoaded; //bool to chekc if hte image has loaded
};


