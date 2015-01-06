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
    inCol = ofColor::red;
    outCol = ofColor::blue;
    vidOn = false;
    closing = false;
    opening = false;
}

void Tile::update(ofxCv::ContourFinder contourFinder) {
    if(inside) {
        closing = true;
        opening = false;
    }
    else {
        opening = true;
        closing = false;
    }
    
    if(closing) {
        w -= 10;
        w = max(w, -fullWidth);
    }
    if(opening) {
        w += 10;
        w = min(w, fullWidth);
    }
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
    else inside = false;
}

void Tile::toggleVid() {
    vidOn = !vidOn;
    if(vidOn) inCol = ofColor(0, 0, 0, 0);
    else inCol = ofColor::red;
}

bool Tile::vidIsOn() {
    return vidOn;
}