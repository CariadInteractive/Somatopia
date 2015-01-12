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
    inside = false;
    inCol = ofColor(0);
    outCol = ofColor(255);
    vidOn = false;
    closing = false;
    opening = false;
    flipSpeed = 20;
}

void Tile::setCols(ofColor newInCol, ofColor newOutCol) {
    inCol = inColMem = newInCol;
    outCol = newOutCol;
}

void Tile::update() {
    if(inside) {
        closing = true;
        opening = false;
    }
    else {
        opening = true;
        closing = false;
    }
    
    if(closing) {
        w -= flipSpeed;
        w = max(w, -fullWidth);
    }
    if(opening) {
        w += flipSpeed;
        w = min(w, fullWidth);
    }
    inside = false;
}

void Tile::display() {
    ofPushStyle();
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofColor color;
    if(w < 0) {
        color = inCol;
    }
    else {
        color = outCol;
    }
    ofSetColor(color);
    ofRect(x, y, w, h);
    ofPopStyle();
}

void Tile::checkContour(ofPolyline contour) {
    if(contour.inside(ofMap(x, 0, ofGetWidth(), 0, 320), ofMap(y, 0, ofGetHeight(), 0, 240))) inside = true;
}

void Tile::toggleVid() {
    vidOn = !vidOn;
    if(vidOn) inCol = ofColor(0, 0, 0, 0);
    else inCol = inColMem;
}

bool Tile::vidIsOn() {
    return vidOn;
}