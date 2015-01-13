//
//  Splash.cpp
//  example
//
//  Created by James Bentley on 1/5/15.
//
//

#include "SpaceState.h"
#define NUMROWS 10
#define NUMCOLS 10

using namespace ofxCv;
using namespace cv;

void SpaceState::setup()
{
    ofSetRectMode(OF_RECTMODE_CORNER);
    tiles = vector<Tile>();
    int w = ofGetWidth() / NUMCOLS;
    int h = ofGetHeight() / NUMROWS;
    int k = 0;
    for(int i = 0; i < NUMROWS; i++) {
        for(int j = 0; j < NUMCOLS; j++) {
            tiles.push_back(Tile(j*w+w/2, i*h+h/2, w, h));
            tiles[k].setCols(getSharedData().pallete[0], getSharedData().pallete[4]);
            k++;
        }
    }
}

void SpaceState::update()
{
    if(getSharedData().bVidOn) {
        if(!tiles[0].vidIsOn()) {
            for(int i = 0; i < tiles.size(); i++) {
                tiles[i].activateVid();
            }
        }
    }
    else {
        if(tiles[0].vidIsOn()) {
            for(int i = 0; i < tiles.size(); i++) {
                tiles[i].deactivateVid();
            }
        }
    }
    getSharedData().cam.update();
    
    if(getSharedData().cam.isFrameNew()) {
        
        getSharedData().colImg.setFromPixels(getSharedData().cam.getPixels(), 320, 240);
        getSharedData().colImg.mirror(false, true);

        getSharedData().grayImage = getSharedData().colImg;
        if(getSharedData().bLearnBackground) {
            getSharedData().grayBg = getSharedData().grayImage;
            getSharedData().bLearnBackground = false;
        }
        
        getSharedData().grayDiff.absDiff(getSharedData().grayBg, getSharedData().grayImage);
        getSharedData().grayDiff.threshold(getSharedData().threshold);
        
        getSharedData().contourFinder.findContours(getSharedData().grayDiff);
        
//        getSharedData().findContoursMat();
        int n = getSharedData().contourFinder.size();
        for(int i = 0; i < n; i++) {
            ofPolyline convexHull;
            convexHull = ofxCv::toOf(getSharedData().contourFinder.getConvexHull(i));
            for(int j = 0; j < tiles.size(); j++) {
                tiles[j].checkContour(convexHull);
            }
        }
        for(int i = 0; i < tiles.size(); i++)
        {
            tiles[i].update();
        }
    }
}

void SpaceState::draw()
{
    ofSetColor(255);
    if(tiles[0].vidIsOn())
    {
        getSharedData().colImg.draw(0, 0, ofGetWidth(), ofGetHeight());
    }
    for(int i = 0; i < tiles.size(); i++) {
        tiles[i].display();
    }
    
    getSharedData().drawDebug();
}

string SpaceState::getName()
{
    return "space";
}

void SpaceState::mousePressed(int x, int y, int button)
{
    changeState("splash");
}

void SpaceState::keyPressed(int key)
{
    if(key == 's') {
        changeState("splash");
    }
    if(key == 'v') {
        getSharedData().bVidOn = !getSharedData().bVidOn;
    }
    getSharedData().handleDebug(key);
    getSharedData().handleBackground(key);
    getSharedData().handleThreshold(key);
}