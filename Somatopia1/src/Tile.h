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
    void setCols(ofColor newInCol, ofColor newOutCol);
    void display();
    void update();
    void checkContour(ofPolyline countour);
    void activateVid();
    void deactivateVid();

    bool vidIsOn();
    
    Tile(int x, int y, int w, int h);
    
private:
    
    bool vidOn; //bool to check if video is on (NOT DEPRECATED! STILL NEEDED!)
    int x, y, w, h, fullWidth; //location and size of tile, fullWidth saves the maximum width for flipping purposes
    ofColor inCol, outCol, inColMem; //inside and outside colors (save inside color for 
    bool inside, closing, opening;
    float flipSpeed;
};