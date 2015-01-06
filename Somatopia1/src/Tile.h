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
    void update(ofxCv::ContourFinder);
    void checkContour(ofPolyline countour);
    void toggleVid();
    bool vidIsOn();
    
    Tile(int x, int y, int w, int h);
    
private:
    
    bool vidOn;
    int x, y, w, h, fullWidth;
    ofColor inCol, outCol;
    bool inside, closing, opening;
};