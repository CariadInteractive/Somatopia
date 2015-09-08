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
    theta = 0;
    col = ofColor(0, 0, 0, 0);
    active = false;
    flipSpeed = 0.15;

}

void Tile::update(ofColor newCol) {
    float thresh = fullWidth - fullWidth*0.02;
    if(abs(w) > thresh && !active) {
        if(w < 0) w = -fullWidth;
        else if(w > 0) w = fullWidth;
    }
    else if(active || abs(w) < thresh) {
        int oldW = w;
        w = (int)(fullWidth * cos(theta));
        if (w < -fullWidth) w = -fullWidth;
        else if(w > fullWidth) w = fullWidth;
        theta += flipSpeed;
        if(oldW < 0) {
            if(w > 0) {
                col = newCol;
            }
        }
        else {
            if(w < 0) {
                col = newCol;
            }
        }
    }
}

void Tile::activate() {
    active = true;
}

void Tile::deactivate() {
    active = false;
}

void Tile::display() {
    ofPushStyle();
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofSetColor(ofColor(col, 127));
    ofRect(x, y, w, h);
    ofPopStyle();
}