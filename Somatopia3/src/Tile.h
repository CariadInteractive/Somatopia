//
//  Tile.h
//  Somatopia1
//
//  Created by James Bentley on 1/6/15.
//
//

#pragma once

#include "ofMain.h"
#include "ofxCv.h"

class Tile
{
public:
    void display();
    void update(ofColor newCol);
    void activate();
    void deactivate();
    Tile(int x, int y, int w, int h);
    
//private:
    int x, y, w, h, fullWidth;
    float theta;
    ofColor col;
    bool active;
    float flipSpeed;
};