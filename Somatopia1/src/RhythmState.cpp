//
//  Splash.cpp
//  example
//
//  Created by James Bentley on 1/5/15.
//
//

#include "RhythmState.h"

using namespace ofxCv;
using namespace cv;

void RhythmState::setup() {
    getSharedData().noise.loadSound("pongSound.ogg");
    ball.setCol(getSharedData().pallete[1]);
}

void RhythmState::update() {
    ball.update();
    ball.checkEdges();
    
    getSharedData().cam.update();
    if(getSharedData().cam.isFrameNew()) {
        getSharedData().colImg.setFromPixels(getSharedData().cam.getPixels(), 320, 240);
    }
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
        getSharedData().contourFinder.findContours(getSharedData().grayDiff);
    }
//    getSharedData().findContoursMat();

    int n = getSharedData().contourFinder.size();
    for(int i = 0; i < n; i++)
    {
        ofPolyline convexHull;
        convexHull = ofxCv::toOf(getSharedData().contourFinder.getConvexHull(i));
        ball.checkContour(convexHull);
    }
}

void RhythmState::draw()
{
//    ofDrawBitmapString("Rhythm is currently under development: press 's' to return the splash page",  0, 10);
    ofSetColor(255);
    getSharedData().colImg.draw(0, 0, ofGetWidth(), ofGetHeight());
    
    ball.display();
    
    getSharedData().drawDebug();
}

string RhythmState::getName()
{
    return "rhythm";
}

void RhythmState::mousePressed(int x, int y, int button)
{
    
}

void RhythmState::mouseMoved(int x, int y )
{
    mouseX = x;
    mouseY = y;
}


void RhythmState::keyPressed(int key)
{
    if(key == 's')
    {
        changeState("splash");
    }
    
    getSharedData().handleDebug(key);
    getSharedData().handleBackground(key);
    getSharedData().handleThreshold(key);
}