//
//  Tile.cpp
//  Somatopia1
//
//  Created by James Bentley on 1/6/15.
//
//

#include "Tile.h"

Tile::Tile(int x, int y, int w, int h) :
    x (x),
    y (y),
    w (w),
    fullWidth (w),
    h (h)
{
    inside = false; //initialize everything!
    inCol = ofColor(0);
    outCol = ofColor(255);
    vidOn = false;
    closing = false;
    closed = false;
    flipSpeed = 20;
}

void Tile::setCols(ofColor newInCol, ofColor newOutCol) { //set inside and outside colors
    inCol = inColMem = newInCol;
    outCol = newOutCol;
}

void Tile::update() {
    //a bit of complexish logic to check if I should be closing or opening
    if(inside) {
        closing = true;
    }
//    else {
//        closing = false;
//    }
    
    //either close or open based on state
    if(closing) {
        w -= flipSpeed;
        w = max(w, -fullWidth);
    }
    if(w == -fullWidth) closed = true;
//    if(opening) {
//        w += flipSpeed;
//        w = min(w, fullWidth);
//    }
    //set inside to be false at the end of each update loop because it will get set back to true before the next action
    inside = false;
}

void Tile::display() {
    /*display the tiles*/
    ofPushStyle();
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofColor color;
    if(w < 0) {
        color = inCol; //set color to inColor if it's halfway through in flipping animation
    }
    else {
        color = outCol; //set color to outColor if ti;s haflway through out flipping animation
    }
    ofSetColor(color);
    ofRect(x, y, w, h);
    ofPopStyle();
}

void Tile::checkContour(ofPolyline contour) {
    if(contour.inside(ofMap(x, 0, ofGetWidth(), 0, 320), ofMap(y, 0, ofGetHeight(), 0, 240))) inside = true; //check if I'm inside and set inside to true if you are
}

void Tile::activateVid() {
    vidOn = true; //change inColor to having 0 alpha
    if(vidOn) inCol = ofColor(0, 0, 0, 0);
    else inCol = inColMem;
}

void Tile::deactivateVid() {
    vidOn = false; //set inColor back to original inColor
    if(vidOn) inCol = ofColor(0, 0, 0, 0);
    else inCol = inColMem;
}

bool Tile::vidIsOn() {
    return vidOn; //check if tile thinks video should be on
}

void Tile::reset(ofColor newInCol) {
    closed = false;
    closing = false;
    inside = false;
    outCol = inCol;
    w = fullWidth;
    inCol = (newInCol == outCol) ? ofColor(0, 0, 0,0) : newInCol;
}

bool Tile::isClosed() {
    return closed;
}